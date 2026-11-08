# `pack_hex.py` — BMS Firmware Container Packager Guide

## 1. Overview

[`pack_hex.py`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/pack_hex.py) is the reverse-engineered companion to [`parse_hex.py`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/parse_hex.py). It takes a compiled ARM Cortex-M4F application binary (`.bin`) or standard Intel HEX (`.ihex`) linked at `0x08008000` and packages it into the **proprietary ASCII-hex container format (`.hex`)** required by the BMS vendor's PC flashing tool and on-chip CAN bootloader.

### What `pack_hex.py` Does Step-by-Step

1. **Loads the Application Binary** ([`load_input_binary`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/pack_hex.py#L38-L68)):
   * Accepts a raw binary file (`.bin`) directly, or automatically detects and extracts raw bytes from a standard Intel HEX file (`.ihex` / `.hex` starting with `:`).
2. **Validates the Cortex-M4 Vector Table** ([`validate_vector_table`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/pack_hex.py#L71-L95)):
   * Verifies Word 0 (`Initial_MSP`) points into the Nations Tech N32G45x 144 KB SRAM (`0x20000000 – 0x20024000`).
   * Verifies Word 1 (`Reset_Handler`) has the Thumb state bit (`bit 0 = 1`) set and points into the Application Flash region (`0x08008000 – 0x0807FFFF`).
3. **Pads Application Payload to 64-Byte Alignment** ([`pad_application_binary`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/pack_hex.py#L98-L107)):
   * Because each line of the vendor's `.hex` container encodes exactly 64 bytes (128 hex characters), any trailing partial line is padded with erased-flash bytes (`0xFF`).
4. **Builds the 64-Byte Bootloader Header** ([`build_bootloader_header`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/pack_hex.py#L110-L133)):
   * Prepends the 64-byte header at offset `0x00000 – 0x0003F`:
     * `0x00..0x27` (40 bytes): ASCII Hardware ID string (`SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03`).
     * `0x28` (1 byte): Null terminator (`0x00`).
     * `0x29..0x2C` (4 bytes): **Big-Endian 32-bit unsigned byte-sum checksum** of the padded application binary:
       $$\text{Checksum} = \left(\sum_{i=0}^{N-1} \text{AppBinary}[i]\right) \pmod{2^{32}}$$
     * `0x2D..0x3F` (19 bytes): `0xFF` padding.
5. **Serializes the Container & Computes Outer File CRC32** ([`serialize_custom_hex_container`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/pack_hex.py#L136-L154)):
   * Writes Line 1 as the uppercase hexadecimal byte count of the full payload (`64 + len(padded_app)`).
   * Encodes the full payload as 128 uppercase ASCII hex characters per line with `CRLF` (`\r\n`) line endings.
   * Calculates the **IEEE 802.3 CRC32** across the entire generated ASCII file and embeds the 8-character hex CRC32 into the output filename.

---

## 2. Container Structure Reference

```text
+-----------------------------------------------------------------------------------+
| Vendor .HEX Container File (ASCII text with \r\n line endings)                    |
| Filename suffix: .<CRC32>.hex (IEEE 802.3 CRC32 of entire file)                   |
+-----------------------------------------------------------------------------------+
  Line 1    : Declared total binary size in uppercase hex (e.g., "1B780")
  Line 2    : 64-Byte Bootloader Header (128 ASCII hex chars)
              ├── [0x00..0x27] "SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03"
              ├── [0x28]       0x00 (Null terminator)
              ├── [0x29..0x2C] 32-bit Big-Endian byte-sum of App Binary
              └── [0x2D..0x3F] 19 bytes of 0xFF
  Lines 3..N: Application Binary linked @ 0x08008000 (128 ASCII hex chars / 64B each)
```

---

## 3. How to Use `pack_hex.py`

### 3.1 Verify the Tool (Round-Trip Self-Test)
Before packaging custom firmware, you can verify that `pack_hex.py` reproduces the original factory `.hex` container byte-for-byte from the extracted application binary (`output/firmware_app_0x08008000.bin`):

```powershell
python pack_hex.py --self-test
```

Expected output:
```text
============================================================================
PACK_HEX SELF-TEST (Round-Trip Verification against Original Firmware)
============================================================================
Input App Binary   : output\firmware_app_0x08008000.bin (112,448 bytes, pad added: 0 B)
Inner App Checksum : 0x00B2EF53 (Expected: 0x00B2EF53)
Total Payload Size : 0x1B780 (112,512 bytes)
Generated HEX Size : 228,547 bytes (Expected: 228,547 bytes)
Generated File CRC : 0xB72E0EEC (Expected: 0xB72E0EEC)
Byte-for-Byte Match: EXACT MATCH vs 6495.004615...B72E0EEC.hex
Self-Test Result   : PASSED
```

---

### 3.2 Package a Compiled `.bin` File (Auto-Named Vendor File)
After compiling your custom firmware to a `.bin` file, run:

```powershell
python pack_hex.py firmware_source/build/bms_firmware.bin
```

By default, this outputs a vendor-named file inside `output/` with the current date (`YYMMDD`) and the computed file CRC32:
```text
output/6495.004615.SPB24-DVC24-006-1010-A30.尼泊尔21s70AhNCM.CAN(250k).UART.485(9600).V28.DL.261108.<CRC32>.hex
```

---

### 3.3 Specify a Custom Output Filename with `{CRC32}` Placeholder
If you want a shorter or custom filename while still embedding the outer file CRC32 suffix:

```powershell
python pack_hex.py firmware_source/build/bms_firmware.bin -o output/custom_bms_fw.{CRC32}.hex
```

`pack_hex.py` automatically replaces `{CRC32}` with the 8-digit uppercase CRC32 (e.g., `output/custom_bms_fw.A1B2C3D4.hex`).

---

### 3.4 Customize Version Tag, Build Date, or BMS Hardware ID
You can override metadata fields used in the header or filename:

```powershell
python pack_hex.py firmware_source/build/bms_firmware.bin --version V29 --date 261108
```

All CLI flags:

| Option | Default | Description |
| :--- | :--- | :--- |
| `input` | *(Required)* | Path to compiled `.bin` or standard Intel HEX (`.ihex`) file |
| `-o`, `--output` | *(Auto-named)* | Custom output file path (supports `{CRC32}`) or directory |
| `--output-dir` | `output` | Directory for auto-generated vendor filename |
| `--bms-id` | `SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03` | 40-byte hardware ID string written into the 64-byte header |
| `--version` | `V28` | Firmware version tag in auto-generated filename |
| `--date` | Today (`YYMMDD`) | 6-digit build date in auto-generated filename |
| `--skip-vector-check` | `False` | Bypass Cortex-M4 `Initial_MSP` / `Reset_Handler` address range validation |
| `--self-test` | `False` | Run round-trip check against `output/firmware_app_0x08008000.bin` |

---

### 3.5 Automated Build via `Makefile`
A `vendor_hex` target is included in [`firmware_source/Makefile`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/firmware_source/Makefile#L60-L61). From inside `firmware_source/`, run:

```powershell
cd firmware_source
make vendor_hex
```

This compiles the ELF, extracts `build/bms_firmware.bin`, and runs `pack_hex.py` to generate the ready-to-flash vendor `.hex` container in `firmware_source/build/`.

---

### 3.6 Verify Any Packaged `.hex` File with `parse_hex.py`
You can verify any newly packaged `.hex` file using [`parse_hex.py`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/parse_hex.py) to confirm both checksums (`File CRC32` and `Header Checksum`) and vector table entries report `VALID`:

```powershell
python parse_hex.py
```

---

## 4. Essential Checklist for Custom Firmware Compatibility

Before flashing a custom-built `.hex` onto BMS hardware via CAN:

1. **Linker Flash Origin (`0x08008000`):**
   Ensure your linker script sets `FLASH (rx) : ORIGIN = 0x08008000` (configured in [`n32g45x_flash.ld`](file:///d:/Yatri/battery%20system/projects/BMS_FIRMWARE/firmware_source/n32g45x_flash.ld#L8)).
2. **Relocate `SCB->VTOR` on Startup:**
   Set `SCB->VTOR = 0x08008000` (`*(volatile uint32_t *)0xE000ED08 = 0x08008000`) at the beginning of `SystemInit()` or `main()` before enabling interrupts.
3. **Service the Independent Watchdog (`IWDG`):**
   Periodically reload `IWDG->KEY = 0xAAAA` (`*(volatile uint32_t *)0x40003000 = 0xAAAA`) in your main loop so the hardware watchdog does not reset the MCU.
4. **Bootloader Re-Entry (CAN IAP Upgrade Command):**
   Retain the CAN/UART bootloader jump command handler (or verify that you have SWD debug header access on the PCB) so future firmware updates can re-enter the bootloader at `0x08000000`.

