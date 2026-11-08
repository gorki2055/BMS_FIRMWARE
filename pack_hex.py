#!/usr/bin/env python3
"""
BMS Firmware Proprietary HEX Container Packager (pack_hex.py)
-------------------------------------------------------------
Converts a compiled ARM Cortex-M4F application binary (.bin) or standard
Intel HEX (.ihex) linked at 0x08008000 into the vendor's proprietary
ASCII-hex container format (.hex) for flashing via the vendor PC software
and CAN bootloader.

Container Layout Produced:
  - Line 1: Uppercase hex total payload length (64-byte header + padded app binary)
  - Lines 2..N: 128 uppercase ASCII hex chars (64 raw bytes) per line, CRLF (\r\n)
  - Offset 0x00..0x3F (Line 2): 64-byte Bootloader Header
      * 0x00..0x27 (40B): ASCII string "SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03"
      * 0x28       (1B) : Null terminator (0x00)
      * 0x29..0x2C (4B) : Big-Endian 32-bit byte-sum checksum of padded app binary
      * 0x2D..0x3F (19B): 0xFF padding
  - Offset 0x40..End (Lines 3..N): Application binary padded with 0xFF to 64B boundary
  - Filename Suffix: Standard IEEE 802.3 CRC32 of the entire ASCII .hex file
"""

from __future__ import annotations

import argparse
from datetime import datetime
import glob
from pathlib import Path
import struct
import sys
import zlib

DEFAULT_BMS_ID = "SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03"
FLASH_BASE_ADDR = 0x08008000
FLASH_MAX_ADDR = 0x08080000  # 512 KB total flash (480 KB app region)
SRAM_BASE_ADDR = 0x20000000
SRAM_MAX_ADDR = 0x20024000   # 144 KB SRAM on N32G45x
LINE_BYTE_WIDTH = 64         # 64 raw bytes (128 hex chars) per line


def load_input_binary(input_path: Path, base_addr: int = FLASH_BASE_ADDR) -> bytes:
    """
    Load an application binary from a raw .bin file or standard Intel HEX file.
    Automatically detects Intel HEX if the file starts with ':'.
    """
    raw = input_path.read_bytes()
    if not raw:
        raise ValueError(f"Input file is empty: {input_path}")

    # Detect standard Intel HEX format (starts with ':' record mark)
    if raw.lstrip().startswith(b":"):
        try:
            from intelhex import IntelHex
        except ImportError as exc:
            raise RuntimeError(
                "Input looks like an Intel HEX file, but 'intelhex' is not installed. "
                "Install it via 'pip install intelhex' or pass a raw .bin file."
            ) from exc

        ih = IntelHex(str(input_path))
        min_addr = ih.minaddr()
        max_addr = ih.maxaddr()
        if min_addr is None or max_addr is None:
            raise ValueError(f"Intel HEX file contains no data: {input_path}")
        if min_addr != base_addr:
            print(
                f"[WARNING] Intel HEX start address is 0x{min_addr:08X} "
                f"(expected 0x{base_addr:08X}). Extracting from 0x{min_addr:08X}."
            )
        ih.padding = 0xFF
        return bytes(ih.tobinarray(start=min_addr, end=max_addr))

    return raw


def validate_vector_table(app_bytes: bytes) -> dict:
    """
    Validate the ARM Cortex-M4 vector table at the start of the application binary.
    Checks Initial_MSP (Word 0) and Reset_Handler (Word 1).
    """
    if len(app_bytes) < 64:
        raise ValueError(
            f"Application binary is too small ({len(app_bytes)} bytes) to contain a valid vector table."
        )

    initial_msp, reset_handler = struct.unpack("<2I", app_bytes[:8])
    reset_thumb_addr = reset_handler & ~1
    is_thumb = (reset_handler & 1) == 1

    msp_valid = SRAM_BASE_ADDR <= initial_msp <= SRAM_MAX_ADDR
    reset_valid = is_thumb and (FLASH_BASE_ADDR <= reset_thumb_addr < FLASH_MAX_ADDR)

    return {
        "initial_msp": initial_msp,
        "reset_handler": reset_handler,
        "reset_thumb_addr": reset_thumb_addr,
        "is_thumb": is_thumb,
        "msp_valid": msp_valid,
        "reset_valid": reset_valid,
        "valid": msp_valid and reset_valid,
    }


def pad_application_binary(app_bytes: bytes, alignment: int = LINE_BYTE_WIDTH) -> tuple[bytes, int]:
    """
    Pad the application binary with 0xFF so its length is a multiple of 64 bytes.
    Returns (padded_bytes, num_padding_bytes_added).
    """
    remainder = len(app_bytes) % alignment
    if remainder == 0:
        return app_bytes, 0
    pad_len = alignment - remainder
    return app_bytes + (b"\xFF" * pad_len), pad_len


def build_bootloader_header(app_bytes_padded: bytes, bms_id: str = DEFAULT_BMS_ID) -> tuple[bytes, int]:
    """
    Construct the 64-byte proprietary bootloader header:
      - 0x00..0x27 (40 bytes): ASCII BMS ID string
      - 0x28       (1 byte)  : 0x00 null terminator
      - 0x29..0x2C (4 bytes) : Big-Endian 32-bit byte sum of app_bytes_padded
      - 0x2D..0x3F (19 bytes): 0xFF padding
    """
    id_bytes = bms_id.encode("ascii")
    if len(id_bytes) > 40:
        raise ValueError(f"BMS ID string exceeds 40 bytes ({len(id_bytes)} bytes): {bms_id!r}")

    # Pad ID field with 0x00 up to offset 0x29 (41 bytes total including null terminator)
    id_field = id_bytes + b"\x00" * (41 - len(id_bytes))

    # 32-bit unsigned byte-sum checksum across all application binary bytes
    app_checksum = sum(app_bytes_padded) & 0xFFFFFFFF
    checksum_field = app_checksum.to_bytes(4, byteorder="big")

    # Remaining 19 bytes (0x2D..0x3F) are 0xFF padding
    padding_field = b"\xFF" * (64 - len(id_field) - len(checksum_field))
    header = id_field + checksum_field + padding_field

    assert len(header) == 64, f"Internal error: header size is {len(header)}, expected 64"
    return header, app_checksum


def serialize_custom_hex_container(payload_bytes: bytes) -> tuple[bytes, int]:
    """
    Encode the full payload (64B header + padded app binary) into the vendor's
    ASCII-hex container format with CRLF (\r\n) line endings and compute its CRC32.
    """
    if len(payload_bytes) % LINE_BYTE_WIDTH != 0:
        raise ValueError(
            f"Total payload size ({len(payload_bytes)}) must be a multiple of {LINE_BYTE_WIDTH} bytes."
        )

    lines = [f"{len(payload_bytes):X}"]
    for offset in range(0, len(payload_bytes), LINE_BYTE_WIDTH):
        chunk = payload_bytes[offset : offset + LINE_BYTE_WIDTH]
        lines.append(chunk.hex().upper())

    # Join with CRLF and include trailing CRLF to match vendor format exactly
    ascii_text = "\r\n".join(lines) + "\r\n"
    raw_file_bytes = ascii_text.encode("ascii")
    file_crc32 = zlib.crc32(raw_file_bytes) & 0xFFFFFFFF
    return raw_file_bytes, file_crc32


def format_output_path(
    output_arg: str | None,
    output_dir: Path,
    file_crc32: int,
    version: str,
    build_date: str | None,
) -> Path:
    """
    Determine the final output .hex path and embed the 8-character uppercase CRC32 suffix.
    """
    crc_str = f"{file_crc32:08X}"

    if output_arg:
        out_path = Path(output_arg)
        # If user passed a directory, generate vendor filename inside that directory
        if out_path.exists() and out_path.is_dir():
            output_dir = out_path
        else:
            # Replace placeholder {CRC32} if provided, or insert CRC32 before .hex if requested
            name = out_path.name
            if "{CRC32}" in name:
                name = name.replace("{CRC32}", crc_str)
                return out_path.with_name(name)
            return out_path

    date_str = build_date or datetime.now().strftime("%y%m%d")
    filename = (
        f"6495.004615.SPB24-DVC24-006-1010-A30."
        f"尼泊尔21s70AhNCM.CAN(250k).UART.485(9600)."
        f"{version}.DL.{date_str}.{crc_str}.hex"
    )
    output_dir.mkdir(parents=True, exist_ok=True)
    return output_dir / filename


def run_self_test() -> int:
    """
    Verify that repacking output/firmware_app_0x08008000.bin reproduces the
    exact 228,547-byte original vendor .hex file with CRC32 0xB72E0EEC.
    """
    app_bin_path = Path("output/firmware_app_0x08008000.bin")
    orig_hex_matches = glob.glob("*B72E0EEC.hex")

    if not app_bin_path.exists():
        print(f"[ERROR] Self-test requires {app_bin_path}. Run 'python parse_hex.py' first.")
        return 1

    app_bytes = load_input_binary(app_bin_path)
    padded_app, pad_len = pad_application_binary(app_bytes)
    header, app_checksum = build_bootloader_header(padded_app, DEFAULT_BMS_ID)
    payload = header + padded_app
    raw_hex_bytes, file_crc32 = serialize_custom_hex_container(payload)

    print("=" * 76)
    print("PACK_HEX SELF-TEST (Round-Trip Verification against Original Firmware)")
    print("=" * 76)
    print(f"Input App Binary   : {app_bin_path} ({len(app_bytes):,} bytes, pad added: {pad_len} B)")
    print(f"Inner App Checksum : 0x{app_checksum:08X} (Expected: 0x00B2EF53)")
    print(f"Total Payload Size : 0x{len(payload):05X} ({len(payload):,} bytes)")
    print(f"Generated HEX Size : {len(raw_hex_bytes):,} bytes (Expected: 228,547 bytes)")
    print(f"Generated File CRC : 0x{file_crc32:08X} (Expected: 0xB72E0EEC)")

    checks_passed = (
        app_checksum == 0x00B2EF53
        and len(payload) == 0x1B780
        and len(raw_hex_bytes) == 228547
        and file_crc32 == 0xB72E0EEC
    )

    if orig_hex_matches:
        orig_bytes = Path(orig_hex_matches[0]).read_bytes()
        byte_exact = raw_hex_bytes == orig_bytes
        print(f"Byte-for-Byte Match: {'EXACT MATCH' if byte_exact else 'MISMATCH'} vs {orig_hex_matches[0]}")
        checks_passed = checks_passed and byte_exact

    print(f"Self-Test Result   : {'PASSED' if checks_passed else 'FAILED'}")
    return 0 if checks_passed else 1


def main() -> int:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    parser = argparse.ArgumentParser(
        description="Package an ARM Cortex-M4F .bin/.ihex image into the vendor BMS .hex container."
    )
    parser.add_argument(
        "input",
        nargs="?",
        help="Path to compiled application binary (.bin) or Intel HEX (.ihex) linked at 0x08008000.",
    )
    parser.add_argument(
        "-o",
        "--output",
        help="Output .hex file path (supports '{CRC32}' placeholder) or output directory.",
    )
    parser.add_argument(
        "--output-dir",
        default="output",
        help="Directory for auto-named vendor .hex file when -o is not specified (default: output).",
    )
    parser.add_argument(
        "--bms-id",
        default=DEFAULT_BMS_ID,
        help=f"40-byte BMS hardware ID string (default: '{DEFAULT_BMS_ID}').",
    )
    parser.add_argument(
        "--version",
        default="V28",
        help="Firmware version tag for auto-generated filename (default: V28).",
    )
    parser.add_argument(
        "--date",
        default=None,
        help="6-digit YYMMDD build date for auto-generated filename (default: today's date).",
    )
    parser.add_argument(
        "--skip-vector-check",
        action="store_true",
        help="Do not fail if the Cortex-M4 vector table check fails.",
    )
    parser.add_argument(
        "--self-test",
        action="store_true",
        help="Run a round-trip verification against output/firmware_app_0x08008000.bin and exit.",
    )

    args = parser.parse_args()

    if args.self_test:
        return run_self_test()

    if not args.input:
        parser.error("the following arguments are required: input (or use --self-test)")

    input_path = Path(args.input)
    if not input_path.exists():
        print(f"[ERROR] Input file not found: {input_path}", file=sys.stderr)
        return 1

    # 1. Load raw application binary
    app_bytes = load_input_binary(input_path)

    # 2. Validate ARM Cortex-M4 vector table at 0x08008000
    vt_info = validate_vector_table(app_bytes)
    if not vt_info["valid"]:
        msg = (
            f"Vector table check failed:\n"
            f"  Initial_MSP   = 0x{vt_info['initial_msp']:08X} "
            f"({'OK' if vt_info['msp_valid'] else 'OUT OF SRAM RANGE 0x20000000..0x20024000'})\n"
            f"  Reset_Handler = 0x{vt_info['reset_handler']:08X} "
            f"({'OK' if vt_info['reset_valid'] else 'NOT IN APP FLASH 0x08008000..0x0807FFFF OR THUMB BIT CLEAR'})"
        )
        if args.skip_vector_check:
            print(f"[WARNING] {msg}")
        else:
            print(f"[ERROR] {msg}\nUse --skip-vector-check to override.", file=sys.stderr)
            return 1

    # 3. Pad application binary to 64-byte alignment
    padded_app, pad_len = pad_application_binary(app_bytes)

    # 4. Build 64-byte bootloader header with 32-bit Big-Endian byte-sum checksum
    header_bytes, app_checksum = build_bootloader_header(padded_app, bms_id=args.bms_id)

    # 5. Assemble full payload and serialize to ASCII-hex container
    payload_bytes = header_bytes + padded_app
    raw_hex_bytes, file_crc32 = serialize_custom_hex_container(payload_bytes)

    # 6. Write output file
    out_path = format_output_path(
        output_arg=args.output,
        output_dir=Path(args.output_dir),
        file_crc32=file_crc32,
        version=args.version,
        build_date=args.date,
    )
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_bytes(raw_hex_bytes)

    num_data_lines = len(payload_bytes) // LINE_BYTE_WIDTH

    print("=" * 76)
    print("BMS CUSTOM FIRMWARE CONTAINER PACKAGER")
    print("=" * 76)
    print(f"Input Binary       : {input_path} ({len(app_bytes):,} bytes)")
    print(f"Alignment Padding  : +{pad_len} bytes of 0xFF -> {len(padded_app):,} bytes (0x{len(padded_app):05X})")
    print(f"Flash Address Map  : 0x{FLASH_BASE_ADDR:08X} - 0x{FLASH_BASE_ADDR + len(padded_app) - 1:08X}")
    print(f"Initial MSP (SP)   : 0x{vt_info['initial_msp']:08X} ({'VALID' if vt_info['msp_valid'] else 'WARNING'})")
    print(f"Reset_Handler      : 0x{vt_info['reset_thumb_addr']:08X} (Thumb raw: 0x{vt_info['reset_handler']:08X})")
    print("-" * 76)
    print(f"BMS Header ID      : {args.bms_id}")
    print(f"Inner App Checksum : 0x{app_checksum:08X} (32-bit Big-Endian byte sum @ header 0x29..0x2C)")
    print(f"Raw Header (64B)   : {header_bytes.hex().upper()}")
    print("-" * 76)
    print(f"Declared Size (L1) : 0x{len(payload_bytes):05X} ({len(payload_bytes):,} bytes)")
    print(f"ASCII Data Lines   : {num_data_lines} lines x 64 bytes/line")
    print(f"Outer File CRC32   : 0x{file_crc32:08X} (IEEE 802.3)")
    print(f"Output HEX File    : {out_path} ({len(raw_hex_bytes):,} bytes)")
    print("=" * 76)

    return 0


if __name__ == "__main__":
    sys.exit(main())
