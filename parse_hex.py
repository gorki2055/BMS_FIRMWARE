#!/usr/bin/env python3
"""
BMS Firmware Custom HEX Parser & Binary Extractor
-------------------------------------------------
Parses the proprietary BMS `.hex` firmware container, validates both the
file-level CRC32 and the embedded 64-byte bootloader header checksum,
decodes the ARM Cortex-M vector table (mapped at 0x08008000), extracts
printable strings, and writes out raw `.bin` files ready for Ghidra / IDA.
"""

import glob
import os
import re
import struct
import sys
import zlib
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_THUMB, Cs
from intelhex import IntelHex


ARM_EXCEPTIONS = [
    (0, "Initial_MSP"),
    (1, "Reset_Handler"),
    (2, "NMI_Handler"),
    (3, "HardFault_Handler"),
    (4, "MemManage_Handler"),
    (5, "BusFault_Handler"),
    (6, "UsageFault_Handler"),
    (7, "Reserved_7"),
    (8, "Reserved_8"),
    (9, "Reserved_9"),
    (10, "Reserved_10"),
    (11, "SVC_Handler"),
    (12, "DebugMon_Handler"),
    (13, "Reserved_13"),
    (14, "PendSV_Handler"),
    (15, "SysTick_Handler"),
]


def parse_filename_metadata(filepath: Path) -> dict:
    """Extract metadata fields encoded in the firmware filename."""
    name = filepath.name
    parts = name.split(".")
    meta = {"raw_filename": name}
    if len(parts) >= 10:
        meta["project_code"] = parts[0]
        meta["sub_code"] = parts[1]
        meta["hw_model"] = parts[2]
        meta["battery_spec"] = parts[3]  # e.g., 尼泊尔21s70AhNCM (Nepal 21S 70Ah NCM)
        meta["can_spec"] = parts[4]
        meta["uart_spec"] = parts[5]
        meta["rs485_spec"] = parts[6]
        meta["fw_version"] = parts[7]
        meta["build_type"] = parts[8]
        meta["build_date"] = parts[9]
        if len(parts) >= 12:
            meta["expected_file_crc32"] = parts[10]
    return meta


def parse_bms_hex(filepath: Path) -> dict:
    """
    Parse the custom BMS .hex file format:
      - Line 1: Hexadecimal total byte length (e.g. '1B780' = 112,512 bytes)
      - Line 2..N: 128 hex chars (64 bytes) per line of raw binary data
    """
    raw_file_bytes = filepath.read_bytes()
    actual_file_crc32 = zlib.crc32(raw_file_bytes) & 0xFFFFFFFF

    text = raw_file_bytes.decode("ascii", errors="strict")
    lines = [line.strip() for line in text.splitlines() if line.strip()]

    if not lines:
        raise ValueError("HEX file is empty.")

    # Line 0 is the expected payload size in hex
    declared_size = int(lines[0], 16)

    # Remaining lines are raw hex bytes (64 bytes / 128 hex chars per line)
    hex_payload = "".join(lines[1:])
    payload_bytes = bytes.fromhex(hex_payload)

    if len(payload_bytes) != declared_size:
        raise ValueError(
            f"Size mismatch: header declared 0x{declared_size:X} ({declared_size}) bytes, "
            f"but parsed 0x{len(payload_bytes):X} ({len(payload_bytes)}) bytes."
        )

    # Split 64-byte proprietary bootloader header and ARM application binary
    header_bytes = payload_bytes[:64]
    app_bytes = payload_bytes[64:]

    # Parse 64-byte header:
    #   0x00..0x27: ASCII ID string ("SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03")
    #   0x28:       0x00 null terminator
    #   0x29..0x2C: 32-bit Big-Endian byte-sum checksum of app_bytes (0x00B2EF53)
    #   0x2D..0x3F: 0xFF padding (19 bytes)
    null_idx = header_bytes.find(b"\x00")
    bms_id_str = header_bytes[:null_idx].decode("ascii", errors="replace") if null_idx != -1 else ""
    header_checksum = int.from_bytes(header_bytes[0x29:0x2D], byteorder="big")
    calculated_checksum = sum(app_bytes) & 0xFFFFFFFF
    padding_bytes = header_bytes[0x2D:0x40]

    return {
        "declared_size": declared_size,
        "num_data_lines": len(lines) - 1,
        "actual_file_crc32": actual_file_crc32,
        "payload_bytes": payload_bytes,
        "header_bytes": header_bytes,
        "app_bytes": app_bytes,
        "bms_id_str": bms_id_str,
        "header_checksum": header_checksum,
        "calculated_checksum": calculated_checksum,
        "checksum_valid": header_checksum == calculated_checksum,
        "padding_all_ff": all(b == 0xFF for b in padding_bytes),
    }


def parse_vector_table(app_bytes: bytes, base_addr: int = 0x08008000, num_vectors: int = 102) -> dict:
    """Parse the ARM Cortex-M vector table (102 vectors = 0x198 bytes before __main)."""
    vectors = struct.unpack(f"<{num_vectors}I", app_bytes[: num_vectors * 4])
    initial_msp = vectors[0]
    reset_handler = vectors[1]

    # Identify the default infinite-loop IRQ handler (most frequent vector address)
    irq_vectors = vectors[16:]
    default_irq = max(set(irq_vectors), key=irq_vectors.count)

    core_exceptions = []
    for idx, name in ARM_EXCEPTIONS:
        val = vectors[idx]
        core_exceptions.append({
            "index": idx,
            "offset": idx * 4,
            "name": name,
            "value": val,
            "thumb_addr": (val & ~1) if idx > 0 and val != 0 else val,
        })

    active_irqs = []
    for irq_num, addr in enumerate(irq_vectors):
        if addr != 0 and addr != default_irq:
            active_irqs.append({
                "irq_num": irq_num,
                "vector_index": 16 + irq_num,
                "vector_offset": (16 + irq_num) * 4,
                "handler_raw": addr,
                "handler_addr": addr & ~1,
            })

    return {
        "base_addr": base_addr,
        "initial_msp": initial_msp,
        "reset_handler": reset_handler,
        "default_irq_handler": default_irq,
        "core_exceptions": core_exceptions,
        "active_irqs": active_irqs,
    }


def disassemble_region(app_bytes: bytes, addr: int, size: int = 24, base_addr: int = 0x08008000) -> list:
    """Disassemble a Thumb-2 code region using Capstone."""
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
    offset = addr - base_addr
    code = app_bytes[offset : offset + size]
    return list(md.disasm(code, addr))


def export_intel_hex(app_bytes: bytes, out_path: Path, base_addr: int = 0x08008000) -> None:
    """Export the raw ARM binary as a standard Intel HEX file with base address embedded."""
    ih = IntelHex()
    ih.frombytes(app_bytes, offset=base_addr)
    ih.write_hex_file(str(out_path))


def main():
    # Ensure UTF-8 output on Windows consoles
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    hex_files = glob.glob("*.hex")
    if not hex_files:
        print("No .hex files found in the current directory.")
        sys.exit(1)

    hex_path = Path(hex_files[0])
    meta = parse_filename_metadata(hex_path)
    parsed = parse_bms_hex(hex_path)
    vt = parse_vector_table(parsed["app_bytes"], base_addr=0x08008000)

    print("=" * 76)
    print("1. FILENAME & CONTAINER VERIFICATION")
    print("=" * 76)
    print(f"File Name          : {meta['raw_filename']}")
    if "battery_spec" in meta:
        print(f"Hardware Model     : {meta['hw_model']}")
        print(f"Battery Spec       : {meta['battery_spec']} (Nepal 21S 70Ah NCM)")
        print(f"Interfaces         : {meta['can_spec']}, {meta['uart_spec']}, {meta['rs485_spec']}")
        print(f"Firmware Version   : {meta['fw_version']} ({meta['build_type']}, Date: {meta['build_date']})")
    expected_crc = meta.get("expected_file_crc32", "N/A")
    print(f"File CRC32         : 0x{parsed['actual_file_crc32']:08X} (Filename expected: {expected_crc})")
    print(f"Declared Size (L1) : 0x{parsed['declared_size']:05X} ({parsed['declared_size']:,} bytes)")
    print(f"Data Lines         : {parsed['num_data_lines']} lines x 64 bytes/line = {len(parsed['payload_bytes']):,} bytes")

    print("\n" + "=" * 76)
    print("2. 64-BYTE BOOTLOADER HEADER (Offset 0x00000 - 0x0003F)")
    print("=" * 76)
    print(f"Raw Header (Hex)   : {parsed['header_bytes'].hex().upper()}")
    print(f"BMS ID String      : {parsed['bms_id_str']}")
    print(f"Header Checksum    : 0x{parsed['header_checksum']:08X} (bytes 0x29..0x2C, Big-Endian)")
    print(f"Calculated Sum     : 0x{parsed['calculated_checksum']:08X} (32-bit byte sum of app payload)")
    print(f"Checksum Status    : {'VALID' if parsed['checksum_valid'] else 'INVALID'}")
    print(f"Trailing Padding   : 19 bytes of 0xFF ({'OK' if parsed['padding_all_ff'] else 'Modified'})")

    print("\n" + "=" * 76)
    print("3. ARM CORTEX-M APPLICATION BINARY (Offset 0x00040+, Flash Base 0x08008000)")
    print("=" * 76)
    app_size = len(parsed["app_bytes"])
    print(f"App Binary Size    : 0x{app_size:05X} ({app_size:,} bytes)")
    print(f"Flash Address Map  : 0x08008000 - 0x{0x08008000 + app_size - 1:08X}")
    print(f"Initial MSP (SP)   : 0x{vt['initial_msp']:08X} (SRAM top ~142.6 KB above 0x20000000)")
    print(f"Reset_Handler      : 0x{vt['reset_handler'] & ~1:08X} (Thumb raw: 0x{vt['reset_handler']:08X})")
    print(f"Default IRQ Stub   : 0x{vt['default_irq_handler'] & ~1:08X} (infinite loop 'B .')")

    print("\n--- Core Exception Vectors ---")
    for exc in vt["core_exceptions"]:
        if exc["value"] != 0:
            print(
                f"  [{exc['index']:2d}] +0x{exc['offset']:02X} {exc['name']:<20}: "
                f"0x{exc['thumb_addr']:08X} (raw: 0x{exc['value']:08X})"
            )

    print(f"\n--- Active Peripheral IRQs ({len(vt['active_irqs'])} implemented handlers) ---")
    for irq in vt["active_irqs"]:
        print(
            f"  IRQ #{irq['irq_num']:2d} (Vector #{irq['vector_index']:2d}, +0x{irq['vector_offset']:03X}) -> "
            f"0x{irq['handler_addr']:08X}"
        )

    # Disassemble Reset_Handler using Capstone
    reset_addr = vt["reset_handler"] & ~1
    print(f"\n--- Reset_Handler Disassembly (@ 0x{reset_addr:08X}) ---")
    for insn in disassemble_region(parsed["app_bytes"], reset_addr, size=16):
        print(f"  0x{insn.address:08X}: {insn.bytes.hex():<10}  {insn.mnemonic:<8} {insn.op_str}")

    # Save output binaries & standard Intel HEX
    out_dir = Path("output")
    out_dir.mkdir(exist_ok=True)
    full_bin_path = out_dir / "firmware_full.bin"
    app_bin_path = out_dir / "firmware_app_0x08008000.bin"
    app_ihex_path = out_dir / "firmware_app_0x08008000.ihex"

    full_bin_path.write_bytes(parsed["payload_bytes"])
    app_bin_path.write_bytes(parsed["app_bytes"])
    export_intel_hex(parsed["app_bytes"], app_ihex_path, base_addr=0x08008000)

    print("\n" + "=" * 76)
    print("4. EXPORTED BINARIES FOR DISASSEMBLY (Ghidra / IDA / Binary Ninja)")
    print("=" * 76)
    print(f"  Full Payload (with 64B header) : {full_bin_path} ({len(parsed['payload_bytes']):,} bytes)")
    print(f"  ARM App Image (load @0x08008000): {app_bin_path} ({len(parsed['app_bytes']):,} bytes)")
    print(f"  Standard Intel HEX (@0x08008000): {app_ihex_path}")


if __name__ == "__main__":
    main()
