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
| **Bootloader Flash** | `0x08000000 – 0x08007FFF` | 32 KB | Factory IAP bootloader (checks upgrade flag at Flash offset `0x28A`) |
| **Application Flash** | `0x08008000 – 0x0802373F` | 112,448 B | BMS Application Code, Scatterload Tables & Constant Pools |
| **On-Chip Data Flash** | `0x08028000 – 0x0807FFFF` | Up to 352 KB | Non-volatile Flash emulation (2 KB pages via `0x40022000`, shadow buffer `0x2001B662`) |
| **System Info / Trim** | `0x1FFFF000 – 0x1FFFF7FF` | 2 KB | N32G45x Factory Trim (`0x1FFFF298` = `"BKRI"`) & **96-Bit MCU UID (`0x1FFFF7F0`)** |
| **Internal SRAM** | `0x20000000 – 0x20023FFF` | 144 KB | Main SRAM (`0x20000000`, 128 KB) + Retention SRAM (`0x20020000`, 16 KB, `MSP` = `0x20023A60`) |
| **RTC & Backup (BKP)** | `0x40002800 / 0x40006C00` | — | Real-Time Clock (unlock `0xCA`/`0x53`) & Backup Registers (`0xA5A5`) for sleep wake-up |
| **Watchdog (IWDG)** | `0x40003000` | — | Independent Watchdog (reloaded with `0xAAAA` at `0x0802300C`) |
| **USART2..3 / UART4..5** | `0x40004400 – 0x40005000` | — | APB1 Serial Ports (`USART2`, `USART3`, `UART4`, `UART5`) |
| **CAN1 Controller** | `0x40006400` | — | CAN 2.0B Controller (configured for 250 kbps) |
| **PWR Controller** | `0x40007000` | — | Low-Power `STOP` / Deep-Sleep mode entry (`FUN_0801f7b8`, `FUN_08021748`) |
| **USART1 / RS-485** | `0x40013800` | — | Primary serial interface (configured for 9600 baud) |
| **UART6 & UART7** | `0x40015000 / 0x40015400` | — | APB2 Serial Ports `UART6` (`0x40015000`) & `UART7` (`0x40015400`) with RS-485 DE/RE (`FUN_08016420`) |
| **ADC1 – ADC4** | `0x40020800 / 0x40020C00` | — | On-chip 12-bit ADCs for MOSFET, connector, and hybrid NTC sensing (`FUN_08008914`) |
| **RCC Registers** | `0x40021000` | — | Clock control & peripheral gating (144 MHz PLL) |
| **Flash Controller (FMC)**| `0x40022000` | — | On-chip Flash erase/program controller (`FUN_0800f4f8 – FUN_0800fc44`) |
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
- **IRQ 64 (`+0x140`):** `0x0800A6E0` — `CAN2_RX1_IRQHandler` (Empty `bx lr` stub `return;`; note that peripheral base `0x40015000` is `UART6` and `0x40015400` is `UART7` on N32G45x, not an Analog Comparator).

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

## 8. Extracted Calibrated Battery Parameters & Complete 3-Region Keil Scatter-Loading Table

### 8.1 Complete 3-Region Keil `RegionTable` (`0x08023154 – 0x08023184`)
Decoding the full 48-byte Keil MDK scatter-loading descriptor table at `0x08023154..0x08023184` (invoked by `__scatterload` at `0x080087FC`) reveals the exact three-region SRAM layout initialized prior to `main()`:

| Entry | Flash Descriptor | Source (Flash) | Destination (SRAM) | Size | Handler | Purpose |
| :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| **0** | `0x08023154` | `0x0802318C` | `0x20020000` | `2,960 B` (`0x0B90`) | `__decompress` (`0x08008820`) | Calibrated parameters, 2D OCV & NTC tables in Retention SRAM |
| **1** | `0x08023164` | `0x0802371C` | `0x20000000` | `6,040 B` (`0x1798`) | `__decompress` (`0x08008820`) | Initialized `.data` variables in Main SRAM |
| **2** | `0x08023174` | — | `0x20020B90` | `11,984 B` (`0x2ED0`) | `__scatterload_zeroinit` (`0x08022F94`) | Zero-initialized `.bss` state structs right up to `Initial_MSP` (`0x20023A60`) |

### 8.2 Factory-Calibrated Protection Thresholds (`0x20020000`)
By decompressing Region 0 (`0x0802318C` into Retention SRAM `0x20020000`), we recovered the factory-calibrated protection thresholds:

| Parameter | Calibrated Value | Engineering Unit | Purpose |
| :--- | :--- | :--- | :--- |
| **Over-Voltage Protection (OVP)** | `4,185` | mV (4.185 V) | Hard charging cutoff per cell |
| **Cell Balancing Trigger** | `4,120` | mV (4.120 V) | Threshold to start passive balancing |
| **Nominal Cell Voltage** | `3,608` | mV (3.608 V) | NCM standard nominal cell rating |
| **Under-Voltage Warning (UVW)** | `2,831` | mV (2.831 V) | Low battery dashboard alert / power derating |
| **Under-Voltage Cutoff (UVC)** | `2,621` | mV (2.621 V) | Hard discharge cutoff (contactor open) |
| **Nominal Pack Capacity** | `70` | Ah | Full battery charge capacity rating |

---

## 9. Power MOSFET Switching, Pre-Charge Sequencing & Body-Diode Protection

From schematic analysis and disassembly of `FUN_0801647c` (`0x0801647C`) and `FUN_0801f580` (`0x0801F580`), the power MOSFET switching circuitry operates through dedicated GPIO pins:

- **PA8 (`CHG_EN`):** Controls the Charge Power MOSFET stage via high-side driver.
- **PC9 (`DSG_EN`):** Controls the Discharge Power MOSFET stage.
- **PC4 (`PRECHARGE_EN`):** Controls the current-limiting pre-charge path to prevent inrush contactor/MOSFET arcing.

### 9.1 Safety Interlocking Logic
- **Discharge Enable Condition:** Requires ACC ignition signal active (`PA0 == HIGH`) **AND** DIN discharge request active (`PC2 == HIGH`) with **zero** critical fault flags (`faults.all == 0`).
- **Charge Enable Condition:** Requires CIN charger detect signal active (`PB1 == HIGH`) with no over-voltage fault (`cell_ovp == 0`).
- **Protection Trip:** Any fault (OVP, UVP, OCP, OTP) immediately pulls PA8 and PC9 LOW through `bms_hal_set_chg_mos(false)` and `bms_hal_set_dsg_mos(false)` within 10 ms.

### 9.2 Pre-Charge Sequencing & Fault `0xBE` (`FUN_0801647c` @ `0x0801647C`)
- Before closing the main discharge MOSFET (`PC9`), the firmware engages the pre-charge path (`state == 0x01`).
- If the capacitive load bus voltage fails to rise within 10 ticks, `FUN_0801647c` transitions to pre-charge fault state `0x11`, opens all MOSFETs (`FUN_0800c8f4`), and records black-box fault code **`0xBE`** (`FUN_08019844(0, 0xBE)`).

### 9.3 MOSFET Body-Diode Conduction Promotion (`FUN_0801f580` @ `0x0801F580`)
- When one MOSFET is turned OFF due to a unilateral protection event (e.g., `CHG_EN` is OFF due to cell OVP, or `DSG_EN` is OFF due to cell UVP) and current flows in the permitted opposite direction (`local_18 > *DAT_08017164`), that current would otherwise flow through the inhibited MOSFET's parasitic body diode ($V_f \approx 0.7\text{ V}$), causing severe heating.
- `FUN_0801f580` detects reverse current above threshold `*DAT_08017164` and dynamically turns the inhibited MOSFET **ON** while current is flowing to bypass its body diode, then turns it back **OFF** immediately when current ceases.

---

## 10. Dynamic State of Health (SOH) & Capacity Recalibration Engine

### 10.1 Cycle-Degradation SOH Algorithm (`FUN_080207fc` @ Flash `0x080207FC`)
The core State of Health calculation is executed in the periodic background loop (`FUN_0802302c`):

```c
void FUN_080207fc(void) {
    float cycles = (float)*(ushort *)(0x20022344);   // Cycle counter in Retention SRAM
    float slope  = *(float *)(0x20020A14);           // Degradation slope: 0.02f (Flash 0x08015310)
    float soh    = 100.0f - (cycles * slope);        // Base aging degradation formula
    if (soh < 0.0f) {
        soh = 0.0f;
    }
    *(uint8_t *)(0x20020004) = (uint8_t)soh;         // Saved to SOH register in Retention SRAM
}
```

#### Analytical Breakdown:
- **Degradation Coefficient:** $0.02\%$ per complete cycle ($\approx 0.0002$).
- **Fresh Battery (0 cycles):** $\text{SOH} = 100\%$.
- **100 Cycles:** $\text{SOH} = 98\%$.
- **500 Cycles:** $\text{SOH} = 90\%$.
- **1,000 Cycles (Design Cycle Life):** $\text{SOH} = 80\%$ (standard EV end-of-life battery retirement threshold).
- **Lower Clamp:** Clamped at $0\%$ using single-precision FPU instructions (`0x08020844`).

### 10.2 Dynamic Capacity Recalibration (`FUN_0801b55c` & `FUN_08010654`)
During battery operation, Coulomb integration is periodically cross-referenced against the 2D Open Circuit Voltage (OCV) vs. Temperature lookup table (`FUN_08010654`):
1. When pack current remains quiescent ($<0.8\text{ A}$) for $>20$ consecutive sample intervals, an OCV-estimated capacity $C_{\text{est}}$ is sampled.
2. If the integrated Coulomb counter $C_{\text{meas}}$ deviates by $>3.0\text{ Ah}$, dynamic recalibration is applied:
   $$C_{\text{learned}} = \left(1.0 - \frac{2.0 \times (C_{\text{meas}} - C_{\text{est}})}{C_{\text{est}}}\right) \times C_{\text{est}}$$
3. The learned Full Charge Capacity (FCC) is written back to battery-backed Retention SRAM (`0x20022334`).

### 10.3 CAN Telemetry Broadcast Frame (`CMD 0x10 / 0x40, IDX 0x01`) & 29-Bit ID Verification
Disassembling the raw Thumb-2 instructions of `FUN_0801ef94` (`0x0801EF94`, 29-bit CAN ID packer) and `FUN_0800daf4` (`0x0800DAF4`, 29-bit CAN ID unpacker) confirmed the exact hardware identifier layout:
$$\text{CAN\_ID}_{29} = (\text{SID}_{4:0} \ll 24) \;\mid\; (\text{DID}_{4:0} \ll 16) \;\mid\; (\text{CMD}_{7:0} \ll 8) \;\mid\; \text{Index}_{7:0}$$
*(Bits `[23:21]` are always `0b000`, matching both `0x0801EF94` and Section 2.2 of `CAN documentation.pdf`).*

The calculated SOH, learned capacity, and max allowable discharge current are broadcast onto the 250 kbps CAN bus (`FUN_0801b55c` @ `0x0801B55C`, CAN ID `0x141F1001` in PDF / `0x141F4001` in binary, DLC 7):

| Byte | Field | Scaling / Unit | Description |
| :--- | :--- | :--- | :--- |
| **D0 - D1** | Full Charge Capacity (FCC) | $10\text{ mAh / LSB}$ (Little-Endian) | Learned total battery capacity |
| **D2 - D3** | Remaining Capacity | $10\text{ mAh / LSB}$ (Little-Endian) | Dynamically tracked usable charge |
| **D4** | Relative SOC | $1\% / \text{LSB}$ ($0 - 100\%$) | State of Charge relative to usable FCC |
| **D5** | State of Health (SOH) | $1\% / \text{LSB}$ ($0 - 100\%$) | Absolute capacity health from `0x20020004` |
| **D6** | Max Discharge Current | $1\text{ A / LSB}$ (`70 A` or `0 A`) | Max allowable discharge current (`0` when faulted/locked) |

---

## 11. Deep-Dive Binary Audit: 10 Additional Hardware & Firmware Subsystems

A complete machine-code audit of all 526 functions in `output/firmware_app_0x08008000.bin` and `decompiled/bms_firmware_decompiled.c` uncovered 10 additional hardware mechanisms and firmware subsystems:

### 11.1 Hardware-Bound Calibration & Anti-Cloning Lock (`MCU 96-Bit UID @ 0x1FFFF7F0`)
- **UID Reader (`FUN_08018708` @ `0x08018708`):** Reads 12 bytes (`3 × uint32_t`) from `0x1FFFF7F0` (`DAT_08018764`), the Nations N32G45x 96-bit factory Unique Device ID register block.
- **Anti-Cloning Verification (`FUN_08017b3c` @ `0x08017B3C`):** Called during boot (`FUN_0802302c`) and factory calibration (`case 0x7A`). It computes a 16-bit checksum (`FUN_08017b04`) over the EEPROM cell calibration table (`0x0060`) **concatenated with** the 12-byte MCU UID, and compares the result against the 16-bit lock word stored at EEPROM address **`0x0100`** (`FUN_08018768(0x100)`).
- **Security Impact:** If an EEPROM chip is copied to another BMS board or the MCU is replaced without re-executing the factory calibration lock command, `*DAT_08017bb0` is cleared to `0` (uncalibrated/unauthorized state).

### 11.2 Dual Non-Volatile Storage: On-Chip Flash Driver (`0x0800F4F8 – 0x0800FC44`) & Bootloader `0x28A` Trigger
- **Flash Controller Driver (`FUN_0800f4f8` – `FUN_0800fc44`):** Interfaces directly with the N32G45x Flash Memory Controller (`0x40022000`, unlock keys `0x45670123` and `0xCDEF89AB`).
- **Dynamic Partition Sizing:** Inspects `*DAT_0800f950` (storage medium selector) and `*DAT_0800f954` (Flash size indicator: `0x200` = 512 KB, `0x100` = 256 KB, else 128 KB), mapping 2 KB (`0x800`) Flash pages from **`0x08028000`** (or `0x0801E000`) up to `0x08040000` / `0x08080000` via a 2 KB SRAM shadow buffer at `0x2001B662`.
- **Bootloader IAP Handshake at Offset `0x28A`:** Before executing `NVIC_SystemReset()` for firmware update (`case 0x7A` at `0x0801D130`), the application calls `FUN_0800f850(0x28a, pbVar38, 4)` to write a 4-byte upgrade trigger into **on-chip Flash offset `0x28A`** so the bootloader at `0x08000000` remains in IAP flashing mode upon reset.

### 11.3 Multi-AFE Chip Support (`DVC1124` / `DVC1117` / `DVC1114`) & 3-Phase Interleaved Balancing
- **Multi-AFE Family Dispatch (`FUN_08008af4` @ `0x08008AF4` & `FUN_08013a04` @ `0x08013A04`):** Dynamically branches on the configured AFE model ID (`*DAT_08009bd4`):
  - `0x0464` ($1124_{10}$) $\rightarrow$ **Devechip DVC1124** (up to 24S)
  - `0x045D` ($1117_{10}$) $\rightarrow$ **Devechip DVC1117** (up to 17S)
  - `0x045A` ($1114_{10}$) $\rightarrow$ **Devechip DVC1114** (up to 14S)
- **3-Phase Odd/Even Interleaved Balancing (`FUN_08008af4`):** Masks the active balancing bitmask (`*DAT_08008c34`, `*DAT_08008c38`, `*DAT_08008c3c`) into **3 alternating phase groups** (cycling every 20 s / 50 s) and writes them to AFE registers **`0x67`, `0x68`, and `0x69`**. This prevents adjacent cells from balancing simultaneously, eliminating sense-wire voltage measurement droop and PCB thermal hotspots.

### 11.4 Hybrid Temperature Sensing: MCU Internal 12-Bit `ADC1`–`ADC4` (`0x40020800` / `0x40020C00`)
- **MCU Internal ADC Driver (`FUN_08008914` @ `0x08008914` & `FUN_080089c0` @ `0x080089C0`):** Initializes, calibrates, and polls the N32G45x on-chip 12-bit ADCs (`ADC1 @ 0x40020800`, `ADC2 @ 0x40020C00`, `ADC3`, `ADC4`).
- **Sensor Fusion & Open-Wire Masking (`FUN_0801f8ac` @ `0x0801F8AC`):** Merges DVC1124 NTC channels (`FUN_08009bd8`) with MCU internal ADC thermistor channels (`FUN_08016cfc`) to measure **MOSFET temperature** (`iVar8 + 0x118`), **ambient/connector temperature** (`iVar6 + 0x40`), and upper cell NTCs. Includes open-sensor fault masking that substitutes MOSFET temperature if a cell NTC is disconnected (`< 25` raw counts and `> 10°C` divergence).

### 11.5 Deep-Sleep (`PWR STOP`) & RTC Alarm Wake-Up Subsystem (`0x08016148 – 0x08018330`)
- **RTC & BKP Configuration (`FUN_08016148` & `FUN_080161bc`):** Configures the N32G45x Real-Time Clock (`RTC @ 0x40002800`, write-unlock keys `0xCA` / `0x53`) and Backup Registers (`BKP @ 0x40006C00`, magic `0xA5A5`).
- **Low-Power Entry & Recovery (`FUN_0801f7b8`, `FUN_08021748`, `FUN_08016360`):** Disables peripheral clocks, arms wake-up interrupts (`EXTI0..4`, `EXTI9_5`, `EXTI15_10`, and `RTCAlarm_IRQn` on `EXTI17`), and enters `PWR` low-power mode (`0x40007000`). Upon wake-up, `FUN_08016360` restores the 144 MHz PLL, GPIOs, CAN1, and UARTs.

### 11.6 Pre-Charge Contactor Sequencing (`FUN_0801647c`) & MOSFET Body-Diode Protection (`FUN_0801f580`)
- Documented in Sections 9.2 and 9.3 above: timed pre-charge monitoring with fault `0xBE` trip (`FUN_0801647c`) and reverse-current body-diode bypass (`FUN_0801f580`).

### 11.7 Unified 7-Port UART Architecture (`USART1..3`, `UART4..7`) & RS-485 DE/RE Control
- **7-Port Driver (`0x08015EA8 – 0x08015EF0` & `0x08020060 – 0x08020088`):** Supports `USART1` (`0x40013800`), `USART2` (`0x40004400`), `USART3` (`0x40004800`), `UART4` (`0x40004C00`), `UART5` (`0x40005000`), `UART6` (`0x40015000`), and `UART7` (`0x40015400`), with dedicated RS-485 DE/RE direction-pin toggling in `FUN_08016420` (`0x08016420`).

### 11.8 Complete 3-Region Keil Scatter-Loading Table (`0x08023154 – 0x08023184`)
- Documented in Section 8.1 above: two LZSS-compressed regions (`0x20020000` and `0x20000000`) and one zero-initialized `.bss` region (`0x20020B90 – 0x20023A60`).

### 11.9 Per-Cell Voltage Gain Calibration (`FUN_08016000`) & Parasitic Self-Discharge Model (`FUN_0801fc8c`)
- **Per-Cell ADC Gain Multipliers (`FUN_08016000` @ `0x08016000`):** Reads 21 individual 16-bit calibration words from EEPROM `0x0060`, divides by reference constant `DAT_08016140`, validates bounds (defaulting to `1.0f` / `0x3F800000` on out-of-range), and scales each cell voltage individually.
- **Parasitic Self-Discharge Model (`FUN_0801fc8c` @ `0x0801FC8C`):** Every 75 rest intervals, computes cumulative BMS board quiescent drain plus temperature-dependent cell self-discharge (`(fVar10 + pfVar6[0x18] * *pfVar5) / 12.0`) and decrements remaining capacity (`pfVar5[2]`).

### 11.10 5-Stage LED SOC Bar-Graph (`FUN_0800fc48`) & Black-Box Fault Snapshot Logger (`FUN_08019844`)
- **5-LED SOC Indicator (`FUN_0800fc48` @ `0x0800FC48`):** Maps `SOC%` into 5 LED bar levels (`1..5`) with separate hysteresis bands for charging (`<20%, <40%, <60%, <80%, >=80%`) vs. discharging (`<10%` blink, `<20%, <40%, <60%, <80%, >=80%`).
- **Black-Box Event Snapshot Logger (`FUN_08019844` @ `0x08019844`) & AFE Fault Root-Causes:** Logs a 32-byte timestamped telemetry record (`puVar3[0x00..0x1F]`) into non-volatile storage (`uVar14 << 5`) containing RTC time, pack/cell voltages, current, temperatures, Max/Min cell numbers (`1..21`), a 24-bit fault bitmask (`0x17..0x19` from `param_1`), and the trigger event code (`0x1B` from `param_2`). Specifically captures all DVC1124 AFE hardware and communication errors:
  - **`Event 0x83` (`FUN_0800d620`):** *AFE I2C Communication Failure & Chip Re-Init* — Triggered when writing the 36-byte protection block (`0x56..0x79`) to the DVC1124 fails due to I2C NACK, bus noise, or CRC-8 error, forcing an AFE soft-reset (`Reg 0x55 = 0xAD, 0xAC`).
  - **`Fault Index 10 / 9 / 11` (`FUN_08008d40` $\rightarrow$ `DVC1124 Reg 0x00` Bits 0–2):** *AFE Hardware SCD (`10`, counter `0x01E0`), OCD (`9`, counter `0x01DC`), and OCC (`11`, counter `0x01E2`)* — Triggered when the DVC1124's internal high-speed analog comparator detects a shunt voltage drop exceeding hardware short-circuit or over-current thresholds (caused by external short circuit, un-precharged inverter capacitance, or sustained overload).
  - **`Fault Index 1 / 3` (`FUN_08008d40` $\rightarrow$ `DVC1124 Reg 0x00` Bits 3–4):** *AFE Hardware Cell OV (`1`, counter `0x01D8`) and UV (`3`, counter `0x01DA`)* — Triggered when any cell tap (`VC1..VC24`) crosses the hardware comparator limits in `Reg 0x56..0x58` (caused by cell overcharge/deep-discharge or an open sense wire pulling a tap to $0\text{ mV}$ or adjacent cell potential).
  - **`Event 0xA0 / 0xA1` (`FUN_08009024`):** *AFE Hardware `ALERT` Pin Asserted (`0xA0`) / Cleared (`0xA1`)* — Triggered when the physical alert GPIO from the DVC1124 remains asserted for $>4$ consecutive ticks, forcing emergency MOSFET turn-off (`FUN_08015efc()`).
  - **`Fault Index 21` (`0x15`, `FUN_080207fc`, counter `0x01D6`):** *Cell Sense Open-Wire / Extreme Voltage Imbalance* — Triggered when `max_cell_mv - min_cell_mv` exceeds the severe imbalance threshold due to a broken sense harness wire, blown balance trace, or shorted cell.
  - **`Event 0x32` (`FUN_080097a4`):** *AFE Protection Latch Timeout* — Triggered when an AFE fault state remains latched for $>21,600$ / $64,801$ ticks, invoking an automatic AFE state recovery reset (`FUN_0800b2a8()`).



