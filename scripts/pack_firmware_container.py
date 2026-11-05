#!/usr/bin/env python3
"""
pack_firmware_container.py
==========================
Packages compiled BMS application binary (0x08008000) into the proprietary
vendor ASCII-Hex container format compatible with the vendor PC CAN Flasher tool.

Verified Format:
- Line 1: Declared total length in hexadecimal (Payload + 64 bytes)
- Line 2: 64-byte Header containing:
    * ASCII Hardware Model: "SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03"
    * 2 null bytes (0000)
    * Arithmetic sum32 of the binary payload formatted as hex
    * 0xFF padding up to 128 hex characters
- Line 3..N: Application Flash payload formatted at 64 bytes (128 hex chars) per line (CRLF)
- Filename suffix: IEEE 802.3 CRC32 of the generated container file
"""

import sys
import os
import binascii
import struct
import argparse

DEFAULT_MODEL_ID = "SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03"
DEFAULT_BASE_NAME = "6495.004615.SPB24-DVC24-006-1010-A30.Nepal21s70AhNCM.CAN(250k).UART.485(9600)"

def pack_firmware(bin_path, output_dir="output", version="V28", model_id=DEFAULT_MODEL_ID, base_name=DEFAULT_BASE_NAME):
    if not os.path.exists(bin_path):
        print(f"[Error] Binary file not found: {bin_path}")
        return None

    with open(bin_path, "rb") as f:
        app_bin = f.read()

    payload_len = len(app_bin)
    print(f"[*] Input binary size: {payload_len} bytes ({payload_len / 1024:.2f} KB)")

    # 1. Sanity Check: Verify Cortex-M4 Initial MSP and Reset Vector
    if payload_len >= 8:
        msp, reset_vec = struct.unpack("<II", app_bin[:8])
        print(f"[*] Initial MSP: 0x{msp:08X} (SRAM boundary: 0x20024000)")
        print(f"[*] Reset Vector: 0x{reset_vec:08X} (Application Base: 0x08008000)")
        if not (0x20000000 <= msp <= 0x20024000):
            print(f"[Warning] MSP 0x{msp:08X} is outside N32G45x 144KB SRAM boundary!")
        if not (0x08008000 <= reset_vec <= 0x08080000):
            print(f"[Warning] Reset Vector 0x{reset_vec:08X} is outside application flash boundary (0x08008000)!")

    # 2. Line 1: Declared Length (Payload + 64 bytes)
    total_declared_len = payload_len + 64
    line1 = f"{total_declared_len:X}\r\n".encode("ascii")

    # 3. Line 2: 64-Byte Model Authentication Header
    model_hex = model_id.encode("ascii").hex().upper().encode("ascii")
    sum32 = sum(app_bin) & 0xFFFFFFFF
    sum_hex = f"{sum32:X}".encode("ascii")
    
    # Structure: [ModelHex] + "0000" + [SumHex] + Padding "F"
    fixed_len = len(model_hex) + 4 + len(sum_hex)
    if fixed_len > 128:
        print("[Error] Model ID is too long for 64-byte container header!")
        return None
    padding_f = b"F" * (128 - fixed_len)
    line2 = model_hex + b"0000" + sum_hex + padding_f + b"\r\n"

    # 4. Line 3..N: 64 bytes (128 hex characters) per line
    payload_lines = []
    for i in range(0, payload_len, 64):
        chunk = app_bin[i:i+64]
        payload_lines.append(chunk.hex().upper().encode("ascii") + b"\r\n")

    container_bytes = line1 + line2 + b"".join(payload_lines)

    # 5. Compute IEEE 802.3 CRC32 of container
    file_crc32 = binascii.crc32(container_bytes) & 0xFFFFFFFF
    crc_str = f"{file_crc32:08X}"
    print(f"[*] Payload Sum32: 0x{sum32:08X}")
    print(f"[*] Container CRC32: {crc_str}")

    # 6. Generate standard vendor filename
    os.makedirs(output_dir, exist_ok=True)
    out_filename = f"{base_name}.{version}.DL.{crc_str}.hex"
    out_path = os.path.join(output_dir, out_filename)

    with open(out_path, "wb") as f:
        f.write(container_bytes)

    print("[OK] Successfully generated vendor-compatible firmware container:")
    print(f"    Path: {out_path}")
    print(f"    Lines: {len(payload_lines) + 2}")
    print(f"    Total File Size: {len(container_bytes)} bytes")

    return out_path

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package binary into vendor CAN Flasher container format")
    parser.add_argument("binary", nargs="?", default="output/firmware_app_0x08008000.bin", help="Path to raw application binary")
    parser.add_argument("--outdir", default="output", help="Output directory")
    parser.add_argument("--version", default="V28", help="Firmware version tag (e.g. V28)")
    args = parser.parse_args()

    pack_firmware(args.binary, output_dir=args.outdir, version=args.version)
