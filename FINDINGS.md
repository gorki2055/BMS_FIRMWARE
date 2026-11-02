# BMS Firmware Reverse Engineering — Technical Findings Report

**Date of Report:** November 2, 2026  
**Project Workspace:** `bms firmware reverse engineering`  
**Target Firmware:** `6495.004615.SPB24-DVC24-006-1010-A30.尼泊尔21s70AhNCM.CAN(250k).UART.485(9600).V28.DL.260316.B72E0EEC.hex`

---

## 1. Summary of Analysis to Date

All technical findings from initial container inspection to disassembling core firmware routines are consolidated below. We have confirmed the exact container structure, validated all integrity checks, deduced the microcontroller model and memory layout, resolved the interrupt vector table, and mapped the communication entry points.

```
+--------------------------------------------------------------------------------------------------+
| Custom .HEX Container (228,547 Bytes)                                                            |
| File CRC32: 0xB72E0EEC (IEEE 802.3 matching filename suffix)                                    |
+--------------------------------------------------------------------------------------------------+
   |
   +--> Line 1: Declared size 0x1B780 (112,512 bytes)
   +--> Lines 2..1759: 1,758 lines of 128 ASCII hex chars (64 bytes/line)
        |
        +--> [0x00000 - 0x0003F] 64-Byte Bootloader Header:
        |      - ID: "SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03"
        |      - Checksum: 0x00B2EF53 (Big-Endian byte-sum of application binary)
        |      - Padding: 19 bytes of 0xFF
        |
        +--> [0x00040 - 0x1B77F] Application Binary (112,448 Bytes / 0x1B740):
               - Target Flash: 0x08008000 - 0x0802373F
               - Architecture: Nations Tech N32G45x (ARM Cortex-M4F, 144 KB SRAM)
               - Initial MSP: 0x20023A60
               - Reset Handler: 0x080081B0 -> SystemInit @ 0x0801F4A8 -> main @ 0x08022FE0
```

---

## 2. Firmware Packaging & Checksum Verification

### 2.1 File Container Format
The firmware is delivered as a custom ASCII-hex formatted container (not standard Intel HEX or Motorola S-Record):
- **Line 1:** `1B780` — Specifies the total binary payload size in hexadecimal (`0x1B780` = 112,512 bytes).
- **Lines 2 to 1759:** 1,758 lines, each containing exactly 128 hexadecimal characters (representing 64 raw binary bytes per line).
- **Total Decoded Payload:** 112,512 bytes.

### 2.2 Dual-Layer Integrity Checks
The vendor uses two distinct checksum verification layers:

1. **Outer File-Level CRC32 (`0xB72E0EEC`):**
   - The trailing tag in the filename `.B72E0EEC.hex` corresponds to the standard IEEE 802.3 CRC32 calculated across the entire file.
   - **Status:** **VALID** (matches `zlib.crc32(raw_file_bytes)`).

2. **Inner 64-Byte Bootloader Header Checksum (`0x00B2EF53`):**
   - Located at header byte offsets `0x29` to `0x2C` (big-endian).
   - Algorithm: Arithmetic sum of all bytes in the application binary:
     $$\text{Checksum} = \left(\sum_{i=64}^{112511} \text{Payload}[i]\right) \pmod{2^{32}}$$
   - Calculated sum: `0x00B2EF53`. Header value: `0x00B2EF53`.
   - **Status:** **VALID**.

---

## 3. Hardware & Microcontroller Identification

### 3.1 Target MCU: Nations Technologies N32G45x
Through disassembly of the vector table and the low-level hardware initialization routine `SystemInit` (`0x0801F4A8`), the microcontroller was positively identified as a **Nations Technologies (国民技术) N32G45x series** (Cortex-M4F):

1. **SRAM Configuration (144 KB):**
   - Initial Stack Pointer (`MSP`): `0x20023A60`.
   - The memory range is `0x20000000` to `0x20023FFF` (144 KB). Most standard Cortex-M4 chips (e.g., STM32F4) offer 64K, 128K, or 192K; the 144 KB SRAM boundary is a signature characteristic of the N32G45x series.
2. **Hardware Floating Point Unit (FPU):**
   - `SystemInit` writes `0x00F00000` to `SCB->CPACR` (`0xE000ED88`) to enable full access to coprocessors CP10 and CP11 (ARM Single-Precision VFPv4-SP).
3. **Factory Trim & Information Block Signature:**
   - At `0x0801F516`, the initialization code inspects memory address `0x1FFFF298` (inside the N32G45x Info Block / System Memory `0x1FFFF000`) and compares it against literal constant `0x49524B42` (`"BKRI"`), which is Nations Technologies' proprietary factory calibration key.
4. **Vector Table Relocation (`VTOR`):**
   - At address `0x08022FE8`, the firmware sets `SCB->VTOR` (`0xE000ED08`) to `0x08008000`, confirming the application runs from `0x08008000` while `0x08000000–0x08007FFF` (32 KB) is occupied by the factory bootloader.

---

## 4. Memory Layout & Peripheral Map

| Memory Region | Address Range | Size | Description |
| :--- | :--- | :--- | :--- |
| **Bootloader Flash** | `0x08000000 – 0x08007FFF` | 32 KB | Factory IAP bootloader |
| **Application Flash** | `0x08008000 – 0x0802373F` | 112,448 B | BMS Application Code & Constant Tables |
| **System Info / Trim** | `0x1FFFF000 – 0x1FFFF7FF` | 2 KB | N32G45x Factory Calibration & Trim registers |
| **Internal SRAM** | `0x20000000 – 0x20023FFF` | 144 KB | System RAM (`MSP` initializes at `0x20023A60`) |
| **Watchdog (IWDG)** | `0x40003000` | — | Independent Watchdog (reloaded with `0xAAAA` at `0x0802300C`) |
| **CAN1 Controller** | `0x40006400` | — | CAN 2.0B Controller (configured for 250 kbps) |
| **USART1 / RS-485** | `0x40013800` | — | Primary serial interface (configured for 9600 baud) |
| **RCC Registers** | `0x40021000` | — | Clock control & peripheral gating |
| **Embedded FPU / SCB** | `0xE000ED00 – 0xE000ED88` | — | System Control Block (`VTOR`, `CPACR`) |

---

## 5. Vector Table & Peripheral Interrupt Map

The vector table at `0x08008000` consists of 102 entries (`0x198` bytes: 16 core exceptions + 86 peripheral IRQs):

### 5.1 Core System Vectors
- **`+0x00` (Vector 0):** `Initial_MSP` = `0x20023A60`
- **`+0x04` (Vector 1):** `Reset_Handler` = `0x080081B0`
  - Loads PC literal and branches to `SystemInit` (`0x0801F4A8`).
  - Upon return, branches to Keil runtime `__main` (`0x08008198`).
  - Calls application entry `main()` (`0x08022FE0`).
- **`+0x08` (Vector 2):** `NMI_Handler` = `0x080173AC`
- **`+0x0C` (Vector 3):** `HardFault_Handler` = `0x08011470`
- **`+0x10` (Vector 4):** `MemManage_Handler` = `0x08017220`
- **`+0x14` (Vector 5):** `BusFault_Handler` = `0x0800A504`
- **`+0x18` (Vector 6):** `UsageFault_Handler` = `0x08020F18`
- **`+0x2C` (Vector 11):** `SVC_Handler` = `0x08019540`
- **`+0x3C` (Vector 15):** `SysTick_Handler` = `0x0801F468`

### 5.2 Active Peripheral Handlers & Subsystems
- **IRQ 3 (`+0x04C`):** `0x0801821C` — RTC Wakeup / Real-Time Clock
- **IRQ 6–10 (`+0x058..0x068`):** `0x0800F35C` to `0x0800F3A4` — `EXTI0` through `EXTI4` (AFE interrupt signals, charger connect detection, wake-up switch)
- **IRQ 20 (`+0x090`):** `0x080207E0` — **`CAN1_RX0_IRQHandler`**
  - Receives CAN frames at 250 kbps.
  - Calls CAN message extraction at `0x0800A828` and posts to event queue `0x08017224`.
  - Computes floating-point voltage/current metrics (`vmls.f32`, `vcvt.f32.u32`).
- **IRQ 23 (`+0x09C`):** `0x0800F3AA` — `EXTI9_5_IRQHandler`
- **IRQ 28 (`+0x0B0`):** `0x0801F804` — `TIM2_IRQHandler` (Periodic task timer)
- **IRQ 29 (`+0x0B4`):** `0x0801F81C` — `TIM3_IRQHandler`
- **IRQ 37 (`+0x0D4`):** `0x0802057C` — **`USART1_IRQHandler`**
  - Handles RS-485 / UART reception (status register test `0x28` for RXNE/idle).
  - Routes received bytes to parser at `0x0801D5E8` and transmitter at `0x0801DB50`.
- **IRQ 38 (`+0x0D8`):** `0x080205C4` — `USART2_IRQHandler`
- **IRQ 39 (`+0x0DC`):** `0x0802060C` — `USART3_IRQHandler`
- **IRQ 40 (`+0x0E0`):** `0x0800F362` — `EXTI15_10_IRQHandler`
- **IRQ 52 (`+0x110`):** `0x0801FE34` — `UART4_IRQHandler`
- **IRQ 64 (`+0x140`):** `0x0800A6E0` — `CAN2_RX0` / Analog Comparator

---

## 6. Battery System Specifications & Embedded Data

### 6.1 Battery Pack Configuration
- **Chemistry:** NCM (Lithium Nickel Cobalt Manganese Oxide)
- **Cell Count:** **21S** (21 cells in series: ~75.6 V nominal, ~88.2 V charge cutoff)
- **Capacity:** **70 Ah**
- **Target Project:** Tagged for Nepal market (`尼泊尔21s70AhNCM`)
- **Internal Firmware Tag:** `6495.004615.A22.260316` (located in flash at `0x080151C3`)

### 6.2 Data Tables at Flash Tail (`0x08023400 – 0x0802373F`)
The upper flash region contains lookup tables and calibration constants:
- **State-of-Charge (SOC) vs. Open-Circuit Voltage (OCV):** IEEE 754 32-bit single-precision floating point tables used for cell capacity estimation.
- **Thermistor (NTC) Resistance-to-Temperature Tables:** Calibration coefficients for battery temperature probes.
- **Protection Limit Arrays:** Over-voltage protection (OVP), under-voltage protection (UVP), over-current protection (OCP), and cell balancing activation deltas.

---

## 7. Current Project Artifacts & Tooling

1. **Virtual Environment (`.venv/`):**
   - Python environment initialized with `capstone` (5.0.9) and `intelhex` (2.3.0).
2. **Parser & Extractor ([`parse_hex.py`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/parse_hex.py)):**
   - Automatically parses container length, validates file CRC32 and header byte-sum checksums, decodes vector tables, disassembles `Reset_Handler`, and exports images.
3. **Exported Binaries (`output/`):**
   - [`firmware_app_0x08008000.bin`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/output/firmware_app_0x08008000.bin) (112,448 bytes) — Clean application code for disassemblers.
   - [`firmware_app_0x08008000.ihex`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/output/firmware_app_0x08008000.ihex) — Standard Intel HEX with base address `0x08008000` embedded for Ghidra / IDA Pro.
   - [`firmware_full.bin`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/output/firmware_full.bin) (112,512 bytes) — Full payload with 64-byte header.
4. **Project Overview Document:**
   - [`PROJECT_OVERVIEW.md`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/PROJECT_OVERVIEW.md) — Comprehensive high-level documentation and reverse engineering roadmap.
5. **Ghidra Reverse Engineering Project (`ghidra_project/`):**
   - [`ghidra_project/BMS_Project.gpr`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/ghidra_project/BMS_Project.gpr) — Ghidra 12.2 project with full memory maps, labeled vector tables, and ARM Cortex-M4F auto-analysis.
   - [`scripts/GhidraSetupBms.java`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/scripts/GhidraSetupBms.java) — Native Java Ghidra script configuring memory blocks, vector labels, and Cortex-M Thumb registers.
   - [`scripts/export_decompiled.bat`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/scripts/export_decompiled.bat) — Automation script for headless decompilation.
6. **Decompiled C Source Code (`decompiled/`):**
   - [`decompiled/bms_firmware_decompiled.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/decompiled/bms_firmware_decompiled.c) (819 KB, 28,150 lines) — Complete decompiler output for all 526 firmware functions, including CAN message handling, peripheral drivers, and arithmetic algorithms.

---

## 8. Extracted Calibrated Battery Parameters & Memory Decompression

By emulating the Keil MDK scatter-loading routine (`__scatterload` at `0x080087FC`) and decompressing the packed data table at `0x08023184` into Retention SRAM (`0x20020000`), we recovered the factory-calibrated protection thresholds:

| Parameter | Calibrated Value | Engineering Unit | Purpose |
| :--- | :--- | :--- | :--- |
| **Over-Voltage Protection (OVP)** | `4,185` | mV (4.185 V) | Hard charging cutoff per cell |
| **Cell Balancing Trigger** | `4,120` | mV (4.120 V) | Threshold to start passive balancing |
| **Nominal Cell Voltage** | `3,608` | mV (3.608 V) | NCM standard nominal cell rating |
| **Under-Voltage Warning (UVW)** | `2,831` | mV (2.831 V) | Low battery dashboard alert / power derating |
| **Under-Voltage Cutoff (UVC)** | `2,621` | mV (2.621 V) | Hard discharge cutoff (contactor open) |
| **Nominal Pack Capacity** | `70` | Ah | Full battery charge capacity rating |

