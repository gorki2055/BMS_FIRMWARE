# BMS Firmware Reverse Engineering — Knowledge Base & Methodology

**Project:** 21S 70Ah NCM Battery Management System (Nepal EV Market)  
**Target Hardware:** Nations Technologies N32G45x (ARM Cortex-M4F) + Devechip DVC1124-1 AFE (24S)  
**Firmware Container:** `6495.004615.SPB24-DVC24-006-1010-A30.尼泊尔21s70AhNCM.CAN(250k).UART.485(9600).V28.DL.260316.B72E0EEC.hex`  
**Last Updated:** November 2026  

---

## 1. Executive Summary & Purpose

This Knowledge Base serves as the primary technical reference and engineering handbook for the reverse engineering of the 21S 70Ah NCM Battery Management System (BMS) firmware. It documents the end-to-end methodology, firmware container structures, cryptographic and checksum verifications, memory layouts, decompiled code analysis, and the clean C reconstruction pipeline.

---

## 2. End-to-End Reverse Engineering Workflow

The reverse engineering methodology follows a rigorous, multi-stage pipeline designed to transition from an opaque vendor delivery package to a verifiable, compilable C source repository.

```mermaid
flowchart TD
    A["Vendor Custom .HEX Container\n(228,547 Bytes)"] --> B["Stage 1: Container Parsing & Integrity\n- Checksum Validation (CRC32, Sum32)\n- 64-Byte Header Extraction"]
    B --> C["Stage 2: Target Flash Image\n(112,448 Bytes @ 0x08008000)"]
    C --> D["Stage 3: Architecture & Memory Identification\n- Vector Table (MSP: 0x20023A60)\n- Reset_Handler & SystemInit Tracing\n- FPU, Trim Block ('BKRI'), 144KB SRAM"]
    D --> E["Stage 4: Headless Ghidra Decompilation\n- Memory Map Configuration\n- Thumb Disassembly & Auto-Analysis\n- 526 Functions / 28,150 Lines C"]
    E --> F["Stage 5: Scatterload & Calibration Extraction\n- Decompress Table @ Flash 0x08023184\n- Extract Factory Limits into SRAM 0x20020000"]
    F --> G["Stage 6: Functional Reverse Engineering\n- Core State Machine & MOSFET Control\n- DVC1124 AFE Register Map & Scaling\n- Dynamic SOH & OCV Capacity Learning\n- CAN 2.0B Communication Matrix"]
    G --> H["Stage 7: Clean C Reconstruction\n(firmware_source/)\n- CMSIS, HAL, Drivers, Core, Config"]
    H --> I["Stage 8: Host-Native Unit Testing\n- MSYS2 GCC Unit Tests\n- All Logic Verified Headlessly"]
```

### Stage 1: Container Parsing & Verification
1. **Container Structure:** Custom ASCII hexadecimal container (1,759 lines) with declared length `0x1B780` (112,512 bytes).
2. **Dual Integrity Verification:**
   - **Outer File CRC32 (`0xB72E0EEC`):** Standard IEEE 802.3 CRC32 calculated over the entire file matching the filename suffix.
   - **Inner 64-Byte Header Checksum (`0x00B2EF53`):** 32-bit big-endian arithmetic byte-sum calculated across the application payload:
     $$\sum_{i=64}^{112511} \text{Payload}[i] \equiv 0x00B2EF53 \pmod{2^{32}}$$
3. **Payload Separation:** Strip 64-byte bootloader header (`SPB_BMS_ID:6495-SPB24-DVC24-006-0606-A03`) to isolate the raw 112,448-byte application image.

### Stage 2: Architecture Identification & Memory Boundary Mapping
By analyzing the first 16 words of the binary:
- **Initial MSP (`0x20023A60`):** Points to the top of internal SRAM. The boundary `0x20024000` (144 KB) is the unique hardware signature of **Nations Technologies N32G45x series**.
- **Reset Vector (`0x080081B0`):** Branches directly to `SystemInit` (`0x0801F4A8`) and sets coprocessor access control `SCB->CPACR` (`0xE000ED88`) to `0x00F00000` to enable the ARM Cortex-M4 Single-Precision Hardware FPU (VFPv4-SP).
- **Factory Trim Signature (`0x1FFFF298`):** Compares against ASCII `"BKRI"` (`0x49524B42`), confirming the Nations Info Block layout.
- **VTOR Relocation:** Relocates vector table to base `0x08008000` (leaving `0x08000000–0x08007FFF` for factory IAP bootloader).

### Stage 3: Headless Decompilation & Static Analysis
- **Tooling:** Ghidra 12.2 running headless analysis via [`analyzeHeadless.bat`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/scripts/run_ghidra_headless.bat).
- **Target Language:** `ARM:LE:32:Cortex:default` (Thumb-2 mode).
- **Environment Setup:** Custom Java initialization script ([`scripts/GhidraSetupBms.java`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/scripts/GhidraSetupBms.java)) defining:
  - Flash: `0x08000000 - 0x0807FFFF`
  - SRAM: `0x20000000 - 0x2001FFFF` (Main SRAM 128KB)
  - Retention SRAM: `0x20020000 - 0x20023FFF` (Battery-backed SRAM 16KB)
  - Peripherals: `0x40000000 - 0x40023FFF`
  - System Control: `0xE000E000 - 0xE000EFFF`
- **Output:** 526 decompiled functions exported to [`decompiled/bms_firmware_decompiled.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/decompiled/bms_firmware_decompiled.c).

### Stage 4: Calibration Extraction via Scatterload Decompression
- The firmware uses Keil MDK compression (`__decompress` at `0x080088C0`).
- By decoding the compressed table at Flash `0x08023184`, the factory-calibrated protection thresholds decompressed into Retention SRAM `0x20020000` were recovered.

---

## 3. Microcontroller & Board Architecture

### 3.1 Hardware Specifications
- **MCU:** Nations Technologies N32G452 / N32G457 (ARM Cortex-M4F @ 144 MHz)
- **Memory:** 512 KB Flash, 144 KB SRAM (128 KB standard + 16 KB retention SRAM)
- **Battery Configuration:** 21 Series, 1 Parallel (21S1P) NCM Chemistry
- **Pack Capacity:** 70 Ah nominal (51.8V nominal, 75.8V nominal stack)
- **Analog Front End:** Devechip DVC1124-1 (24-Channel Precision AFE)

### 3.2 Pinout Map (Board: SPB24-DVC24-006-0606-A03)

| Pin | MCU Function | Hardware Assignment | Description |
| :--- | :--- | :--- | :--- |
| **PA0** | GPIO Input | `ACC_WAKE` | Ignition switch input (Active HIGH) |
| **PB1** | GPIO Input | `CIN_DETECT` | Charger insertion detect (Active HIGH) |
| **PC2** | GPIO Input | `DIN_DETECT` | Discharge request detect (Active HIGH) |
| **PA8** | GPIO Output | `CHG_EN` | Main Charging MOSFET Gate Driver |
| **PC9** | GPIO Output | `DSG_EN` | Main Discharging MOSFET Gate Driver |
| **PC4** | GPIO Output | `PRECHARGE_EN` | Pre-charge current limiting path |
| **PB6 / PB10** | GPIO / I2C1 | `AFE_SCL` | DVC1124 I2C Clock line |
| **PB7 / PB11** | GPIO / I2C1 | `AFE_SDA` | DVC1124 I2C Data line |
| **PA11** | CAN1_RX | `CAN_RX` | Transceiver CAN RX (250 kbps) |
| **PA12** | CAN1_TX | `CAN_TX` | Transceiver CAN TX (250 kbps) |
| **PA9** | USART1_TX | `RS485_TX` | RS-485 / Modbus Diagnostic Port (9600 baud) |
| **PA10** | USART1_RX | `RS485_RX` | RS-485 / Modbus Diagnostic Port (9600 baud) |

---

## 4. Devechip DVC1124-1 AFE Deep Register Architecture

The DVC1124-1 is a 24-channel high-voltage battery monitor IC communicating with the MCU over a dedicated I2C interface.

### 4.1 Physical Protocol Layer
- **Interface:** Software bit-banged I2C on `GPIOB` (`0x40010C00`) with precise microsecond timing (`FUN_080121bc`).
- **7-Bit Slave Address:** `0x20`
  - I2C Write Byte: `0x40` (`0x20 << 1 | 0`)
  - I2C Read Byte: `0x41` (`0x20 << 1 | 1`)
- **Packet Error Checking (PEC / CRC8):**
  Every transaction uses an 8-bit CRC with polynomial $x^8 + x^2 + x + 1$ (`0x07`):
  ```c
  uint8_t dvc1124_calc_crc8(const uint8_t *data, uint16_t len);
  ```
- **Transaction Retries:** Firmware retries up to 5 times on NACK before declaring communication failure.

### 4.2 Recovered DVC1124 Register Map

The following registers were recovered directly from assembly transactions (`FUN_080122f0`, `FUN_08012760`, `FUN_08012720`):

| Address | Register Name | Access | Length | Description |
| :---: | :--- | :---: | :---: | :--- |
| **`0x00`** | `DVC_REG_SYS_CTRL` | R/W | 1 Byte | System Control (Reset, Sleep, Wakeup control) |
| **`0x01`** | `DVC_REG_CELL_MODE` | R/W | 1 Byte | Cell Count Mode (`0x0D` = 21S, `0x0E` = 22S, `0x0F` = 24S) |
| **`0x02`** | `DVC_REG_CURRENT` | Read | 2 Bytes | Signed 16-bit Pack Current ADC reading |
| **`0x06`** | `DVC_REG_ADC_CTRL` | R/W | 1 Byte | ADC Channel Sequencing & Clock Enable |
| **`0x07`** | `DVC_REG_ADC_CONFIG` | R/W | 2 Bytes | ADC Sample Rate and Averaging Filter |
| **`0x0B`** | `DVC_REG_CELL_STATUS` | Read | 2 Bytes | Hardware Alert Flags & Cell Measurement Status |
| **`0x0F`** | `DVC_REG_NTC_BASE` | Read | 14 Bytes | NTC Thermistor ADC Channels (up to 6 sensors) |
| **`0x1D`** | `DVC_REG_CELL_VOLTAGES` | Read | 42 Bytes | 21-Cell Voltage ADC readings ($21 \times 2$ bytes) |
| **`0x4F`** | `DVC_REG_PACK_VOLTAGE` | Read | 2 Bytes | Total High-Voltage Stack Voltage ADC reading |
| **`0x51`** | `DVC_REG_MEAS_CTRL` | R/W | 1 Byte | Measurement Trigger (Bit 7 = Trigger Scan, Bits [3:2] = Mode) |
| **`0x52`** | `DVC_REG_BURST_CELLS` | R/W | 40/3 B | Cell burst read (0x28 bytes) / Diagnostic burst write (3 bytes) |
| **`0x56`** | `DVC_REG_BALANCING_CTRL` | Write | 36 Bytes | Passive Balancing Control Matrix & Hardware Thresholds |
| **`0x5A`** | `DVC_REG_FAULT_STATUS` | R/W | 1 Byte | Fault Status Register (Cleared by writing `0xFE`) |
| **`0x5E`** | `DVC_REG_OVP_THRESH` | R/W | 1 Byte | Hardware Over-Voltage Cutoff Threshold |
| **`0x5F`** | `DVC_REG_OVP_DELAY` | R/W | 1 Byte | Hardware Over-Voltage Filter Delay |
| **`0x60`** | `DVC_REG_UVP_THRESH` | R/W | 1 Byte | Hardware Under-Voltage Cutoff Threshold |
| **`0x61`** | `DVC_REG_UVP_DELAY` | R/W | 1 Byte | Hardware Under-Voltage Filter Delay |
| **`0x62`** | `DVC_REG_TEMP_CONFIG` | R/W | 1 Byte | NTC Sensor Configuration & Channel Muxing |
| **`0x63`** | `DVC_REG_CHG_OCP` | R/W | 1 Byte | Hardware Charge Over-Current Protection Threshold |
| **`0x67`** | `DVC_REG_DSG_OCP1` | R/W | 1 Byte | Hardware Discharge Over-Current Level 1 Threshold |
| **`0x68`** | `DVC_REG_DSG_OCP2` | R/W | 1 Byte | Hardware Discharge Short-Circuit Level 2 Threshold |
| **`0x69`** | `DVC_REG_OCP_DELAY` | R/W | 1 Byte | Over-Current Protection Trip Delay |
| **`0x6E`** | `DVC_REG_AFE_CONFIG` | R/W | 1 Byte | AFE Hardware Core Configuration (`0xCD` normal / `0x8D`) |
| **`0x7E`** | `DVC_REG_CHIP_ID_VREF` | Read | 1 Byte | Chip Identification & Internal VREF Trim Calibration |
| **`0x8E`** | `DVC_REG_RESET_DIAG` | R/W | 1 Byte | AFE Soft Reset & Self-Diagnostic Control (`0x80`) |

### 4.3 Sensor Measurement & Conversion Formulas

Extracted directly from Flash literal pools and decompiled arithmetic routines:

#### 1. Cell Voltage Conversion (`FUN_0800d218` @ `0x0800D218`)
- **Gain (`DAT_0800d3bc`):** `0.0001f` ($0.1\text{ mV / count}$)
- **Offset (`DAT_0800d3c0`):** `0.0005f` ($0.5\text{ mV}$)
$$V_{\text{cell}} (\text{mV}) = (\text{Raw ADC Counts} \times 0.1) + 0.5$$

#### 2. Pack Current Conversion (`FUN_0800d48c` @ `0x0800D48C`)
- **Shunt Scaling Factor (`DAT_0800d52c`):** `0.005f` ($5\text{ mA / count}$ / $0.005\text{ A / count}$)
$$I_{\text{pack}} (\text{mA}) = -(\text{Raw ADC} - I_{\text{zero\_offset}}) \times 5.0$$
*(Negative sign indicates discharge current; positive sign indicates charge current).*

#### 3. NTC Temperature Conversion (`FUN_0800cfc0` @ `0x0800CFC0`)
- Reads NTC ADC ratio against VREF trim (`0x7E`), computes NTC resistance, looks up the 160-point calibration array, and converts to Celsius with a **$-40^\circ\text{C}$ offset**:
$$T (^\circ\text{C}) = \text{LookupIndex} - 40$$

---

## 5. Core BMS State Machine & Protection Engine

### 5.1 Calibrated Safety Thresholds (from Scatterload Table `0x08023184`)

| Protection Parameter | Threshold | Release | Trip Delay | Action |
| :--- | :--- | :--- | :--- | :--- |
| **Cell Over-Voltage (OVP)** | `4,185 mV` | `4,100 mV` | 100 ms | Open CHG MOSFET (PA8 = LOW) |
| **Cell Balancing Start** | `4,120 mV` | $\Delta V < 20\text{ mV}$ | Continuous | Engage passive bypass resistors via `0x56` |
| **Nominal Cell Voltage** | `3,608 mV` | — | — | Baseline 50% SOC voltage |
| **Under-Voltage Warning (UVW)** | `2,831 mV` | `3,000 mV` | 500 ms | Dashboard derate alert via CAN |
| **Under-Voltage Cutoff (UVC)** | `2,621 mV` | CIN active | 100 ms | Open DSG MOSFET (PC9 = LOW) |
| **Charge Over-Temperature** | `+55°C` | `+50°C` | 1000 ms | Discontinue charging |
| **Discharge Over-Temperature** | `+65°C` | `+60°C` | 1000 ms | Open DSG MOSFET |
| **MOSFET Over-Temperature** | `+85°C` | `+75°C` | 500 ms | Open both CHG & DSG MOSFETs |
| **Auxiliary Path Current Limit** | `2.0 A` | DIN active | 200 ms | Prevent battery drain through key ACC |

### 5.2 MOSFET Interlocking Logic
- **Discharge Permitted:** `(PA0 == HIGH) && (PC2 == HIGH) && (faults.all == 0)`
- **Charge Permitted:** `(PB1 == HIGH) && (!faults.bits.cell_ovp)`
- **Fault Safe State:** Pull both PA8 and PC9 LOW immediately within 10 ms.

---

## 6. Dynamic State of Health (SOH) & Capacity Learning

The BMS employs a dual-mechanism model for State of Health:

### 6.1 Cycle Degradation Model (`FUN_080207fc` @ `0x080207FC`)
Executed in the periodic 1-second supervisor loop:
$$\text{SOH}_{\text{cycle}} = \max\left(0,\; 100.0 - (\text{cycle\_count} \times 0.02)\right)$$

- **Degradation Slope:** `0.02% / cycle` (`0x3CA3D70A`, initialized at Flash `0x08015310`).
- **Fresh Battery (0 cycles):** 100% SOH (70,000 mAh usable).
- **1,000 Cycles:** 80% SOH (56,000 mAh usable — EV retirement threshold).
- **SOH Output Register:** Retention SRAM `0x20020004`.
- **Cycle Count Register:** Retention SRAM `0x20022344`.

### 6.2 Dynamic OCV Capacity Learning (`FUN_0801b55c` & `FUN_08010654`)
- When battery rests in quiescent state ($|I| < 0.8\text{ A}$) for $>20$ samples, Open Circuit Voltage is compared to Coulomb integration.
- If divergence exceeds 3.0 Ah, dynamic recalibration updates learned Full Charge Capacity (FCC):
$$C_{\text{learned}} = \left(1.0 - \frac{2.0 \times (C_{\text{meas}} - C_{\text{est}})}{C_{\text{est}}}\right) \times C_{\text{est}}$$

### 6.3 2D Chemical OCV-SOC Lookup Table Engine

The battery chemical State of Charge is derived from cell open circuit voltage and pack temperature using dual 2D matrices extracted from the scatterload table (`0x08023184` decompressed into SRAM `0x20020572` and `0x20020720`):

#### 1. Chemical OCV Baseline at 25°C (21S 70Ah NCM)
The curve spans 21 SOC steps ($100\%$ down to $0\%$ in $5\%$ increments):
- **100%:** 4,185 mV (Calibrated Over-Voltage Cutoff)
- **95%:** 4,100 mV (OVP Release)
- **90%:** 4,040 mV | **85%:** 3,980 mV | **80%:** 3,920 mV
- **75%:** 3,870 mV | **70%:** 3,820 mV | **65%:** 3,770 mV
- **60%:** 3,720 mV | **55%:** 3,670 mV
- **50%:** 3,608 mV (Calibrated Nominal Cell Voltage)
- **45%:** 3,560 mV | **40%:** 3,510 mV | **35%:** 3,460 mV
- **30%:** 3,400 mV | **25%:** 3,340 mV | **20%:** 3,260 mV
- **15%:** 3,160 mV | **10%:** 3,020 mV
- **5%:** 2,831 mV (Calibrated Under-Voltage Warning)
- **0%:** 2,621 mV (Calibrated Under-Voltage Cutoff)

#### 2. Table 1: Chemical Capacity Availability Matrix ($21 \times 12$)
- **SRAM Address:** `0x20020572` (decompressed from Flash `0x08023184`, used in `FUN_08010654`).
- **Rows (21):** SOC $100\%$ to $0\%$ in $5\%$ intervals.
- **Columns (12):** Temperature bands ($< -20^\circ\text{C}$ up to $\ge 60^\circ\text{C}$).
- **Formula:** Capacity availability in Ah $= \text{Matrix}[row][col] \times 0.1$.
- Models chemical capacity loss under severe sub-zero cold ($<-20^\circ\text{C} \rightarrow 0\text{ Ah}$) versus optimal range ($25^\circ\text{C} \rightarrow 2.0\text{ Ah}$).

#### 3. Table 2: Thermal Voltage Relaxation Matrix ($21 \times 13$)
- **SRAM Address:** `0x20020720` (decompressed from Flash `0x08023184`, used in `FUN_080103c8`).
- **Rows (21):** SOC $100\%$ to $0\%$ in $5\%$ intervals.
- **Columns (13):** Temperature bands ($< 0^\circ\text{C}$ to $\ge 51^\circ\text{C}$).
- **Formula:** Thermal voltage shift $= \text{Matrix}[row][col] \times 0.01$.
- Compensates for NCM internal resistance impedance voltage sag across temperatures.

---

## 7. CAN 2.0B Communication Matrix (250 kbps)

29-bit Extended Identifier format:
`[Priority (3b)] [Source ID (5b)] [Destination ID (5b)] [Command (8b)] [Index (8b)]`

- **Master Pack SID:** `0x14` (Battery #1)
- **Slave Pack SID:** `0x1D` (Battery #2)
- **Vehicle Control Unit (VCU) DID:** `0x00`

### Primary Telemetry Broadcast Frames

| CAN ID | CMD | IDX | DLC | Rate | Data Field Breakdown |
| :---: | :---: | :---: | :---: | :---: | :--- |
| `0x18140010` | `0x14` | `0x10` | 7 | 100 ms | **MOSFET & Switch Status:** D0: DIN, D2: CIN, D4: DSG MOS, D5: CHG MOS, D6: ACC |
| `0x18400001` | `0x40` | `0x01` | 7 | 500 ms | **Capacity & SOH:** D0-D1: FCC ($\times 10\text{mAh}$), D2-D3: Rem mAh, D4: SOC%, D5: SOH% |
| `0x18140003` | `0x14` | `0x03` | 7 | 500 ms | **Temperatures:** D0: Sensor count, D1-D4: NTC1..4 ($+40^\circ\text{C}$), D5: MOS Temp |
| `0x18410003` | `0x41` | `0x03` | 8 | 200 ms | **Cell Voltages 1–4:** 16-bit big-endian millivolts per cell |
| `0x18410004` | `0x41` | `0x04` | 8 | 200 ms | **Cell Voltages 5–8:** 16-bit big-endian millivolts per cell |
| `0x18410005` | `0x41` | `0x05` | 8 | 200 ms | **Cell Voltages 9–12:** 16-bit big-endian millivolts per cell |
| `0x18410006` | `0x41` | `0x06` | 8 | 200 ms | **Cell Voltages 13–16:** 16-bit big-endian millivolts per cell |
| `0x18410007` | `0x41` | `0x07` | 8 | 200 ms | **Cell Voltages 17–20:** 16-bit big-endian millivolts per cell |
| `0x18410008` | `0x41` | `0x08` | 8 | 200 ms | **Cell Voltage 21:** 16-bit big-endian millivolts (D0-D1) |

---

## 8. Clean C Reconstruction Guidelines & Verification

All recovered components are integrated into the modular C skeleton in [`firmware_source/`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/):

- `include/bms_config.h`: Central hardware constants, calibrated limits, and timings.
- `include/bms_types.h`: Structured telemetry, switch status, and bitfield fault flags.
- `include/dvc1124_afe.h`: Complete AFE register definitions, scaling factors, and prototypes.
- `src/dvc1124_afe.c`: AFE driver implementing register reads, ADC scaling, and CRC8.
- `src/bms_ocv.c`: 2D OCV-SOC lookup engine, chemical curves, and temperature derating.
- `src/bms_core.c`: Core state machine, safety supervisor, and SOH cycle degradation.
- `src/bms_can.c`: CAN 2.0B communication engine and frame pack/unpack routines.
- `src/bms_parallel.c`: Multi-pack master/slave parallel arbitration.
- `src/bms_modbus.c`: RS-485 / Modbus RTU and proprietary diagnostic protocol engine.
- `src/bms_storage.c`: 24Cxx non-volatile EEPROM storage and calibration manager.
- `src/bms_hal.c`: Hardware abstraction layer with host-simulation fallbacks.
- `tests/test_bms_logic.c`: Native host unit test runner (15 unit test suites).

---

## 9. RS-485 / Modbus RTU & PC Diagnostic Protocol Engine

The firmware provides external diagnostics, PC upper-computer telemetry, and battery calibration parameter read/write access over RS-485 / UART (`0x08014000 - 0x08019000`, 131 functions).

### 9.1 Hardware Serial Interface
- **Physical Pins:** PA9 (USART1_TX), PA10 (USART1_RX) / PB10, PB11 (USART3).
- **Default Baud Rate:** 9600 baud, 8 data bits, no parity, 1 stop bit (8N1). Configurable dynamically in `FUN_08015b28(port, 0x2580)`.
- **Modbus Slave ID:** Default `0x01` (stored at `EEPROM_ADDR_COMM_CONFIG` `0x0120`).

### 9.2 Modbus RTU Frame Specification & CRC16 Engine
- **CRC-16 Algorithm:** Reconstructed from `FUN_0800c754`. Standard Modbus polynomial `0xA001`, initial seed `0xFFFF`, low byte transmitted first.
- **Supported Function Codes:**
  - `0x03` (`MODBUS_FC_READ_HOLDING_REGS`): Read operational data & protection parameters.
  - `0x04` (`MODBUS_FC_READ_INPUT_REGS`): Read real-time telemetry.
  - `0x06` (`MODBUS_FC_WRITE_SINGLE_REG`): Write single parameter or trigger control.
  - `0x10` (`MODBUS_FC_WRITE_MULTIPLE_REGS`): Batch write calibration tables.

### 9.3 Modbus Register Map

| Register Address | Data Type | Units / Scale | Description |
| :---: | :---: | :---: | :--- |
| `0x0001` – `0x0015` | `uint16_t` | $1\text{ mV}$ | Individual Cell Voltages 1 through 21 |
| `0x0016` | `uint16_t` | $10\text{ mV}$ | Total Battery Pack Voltage (e.g. $7660 \rightarrow 76.6\text{ V}$) |
| `0x0017` | `int16_t` | $10\text{ mA}$ | Battery Pack Current (signed: $+$ charge, $-$ discharge) |
| `0x0018` | `uint16_t` | $0.1\%$ | State of Charge (SOC: $0 \rightarrow 1000 = 0.0\% \rightarrow 100.0\%$) |
| `0x0019` | `uint16_t` | $0.1\%$ | State of Health (SOH: $0 \rightarrow 1000 = 0.0\% \rightarrow 100.0\%$) |
| `0x001A` | `uint16_t` | $0.1\text{ Ah}$ | Remaining Pack Capacity ($350 = 35.0\text{ Ah}$) |
| `0x001B` | `uint16_t` | $0.1\text{ Ah}$ | Nominal Full Pack Capacity ($700 = 70.0\text{ Ah}$) |
| `0x001C` | `uint16_t` | Counts | Lifetime Full Discharge Cycle Count |
| `0x001D` | `uint16_t` | $1\text{ mV}$ | Highest Cell Voltage ($\max(V_{\text{cell}})$) |
| `0x001E` | `uint16_t` | $1\text{ mV}$ | Lowest Cell Voltage ($\min(V_{\text{cell}})$) |
| `0x001F` | `uint16_t` | $1\text{ mV}$ | Maximum Cell Voltage Imbalance ($\Delta V = \max - \min$) |
| `0x0020` – `0x0023` | `int16_t` | $0.1^\circ\text{C}$ | Cell Temperatures NTC 1 through 4 |
| `0x0024` | `int16_t` | $0.1^\circ\text{C}$ | Power MOSFET Stage Temperature |
| `0x0025` | `int16_t` | $0.1^\circ\text{C}$ | Ambient Temperature |
| `0x0030` | `uint16_t` | Enum | BMS State ($0$: INIT, $1$: STANDBY, $2$: CHG, $3$: DSG, $4$: FAULT) |
| `0x0031` | `uint16_t` | Bitfield | Active Protection / Fault Bitmask |
| `0x0032` | `uint16_t` | Bitfield | MOSFET Status (Bit 0: CHG MOS, Bit 1: DSG MOS) |
| `0x0040` | `uint16_t` | $1\text{ mV}$ | Cell Over-Voltage Protection Threshold (OVP: $4185\text{ mV}$) |
| `0x0041` | `uint16_t` | $1\text{ mV}$ | Cell Under-Voltage Protection Threshold (UVP: $2621\text{ mV}$) |
| `0x0042` | `uint16_t` | $10\text{ mA}$ | Charge Over-Current Limit (OCP Chg: $3500 \rightarrow 35.0\text{ A}$) |
| `0x0043` | `uint16_t` | $10\text{ mA}$ | Discharge Over-Current Limit (OCP Dsg: $7000 \rightarrow 70.0\text{ A}$) |
| `0x0044` | `int16_t` | $0.1^\circ\text{C}$ | Over-Temperature Cutoff ($650 \rightarrow 65.0^\circ\text{C}$) |
| `0x0045` | `int16_t` | $0.1^\circ\text{C}$ | Under-Temperature Cutoff ($-100 \rightarrow -10.0^\circ\text{C}$) |

### 9.4 Proprietary Upper-Computer Diagnostic Protocol (0xEA 0xD1)
For high-speed factory automated testing and host telemetry polling (`FUN_0801cd98`), the firmware uses tagged frames with XOR checksums (`FUN_0800c0d0`):
- **Header:** `0xEA 0xD1` (or `0xEB 0x01`)
- **Structure:** `[0xEA] [0xD1] [SlaveID] [Len 0x39] [0xFF] [Cmd 0x03] [Tagged Payload] [XOR Checksum]`
- **Payload Tags:** Tag 2: State, Tag 3: Current, Tag 5: Stack Voltage, Tag 7: SOC, Tag 8: SOH, Tag 9: Max Cell, Tag 10: Min Cell, Tag 11: Delta, Tag 12: NTC1..4/MOS/Amb ($+40^\circ\text{C}$ offset).
- **Bluetooth AT Command Framing:** Formats `"AT+NAME <PackName>\r\n"` on UART ports for auto-configuration of BLE dongles (`FUN_0800b454`).

---

## 10. 24Cxx Non-Volatile EEPROM Storage & Parameter Persistence

The BMS features an external I2C serial EEPROM (AT24C32 / AT24C64 / 24C128) for persistent parameter storage, factory calibration, and lifetime tracking (`0x08012000 - 0x08014000`, 36 functions).

### 10.1 Physical Bus & Watchdog Protection
- **Bus:** Software bit-banged I2C on `GPIOC` (`0x40011400`) pins with delay loops (`FUN_08012180`).
- **Independent Watchdog Keep-Alive:** The EEPROM delay loops reload `IWDG` (`0x40003000`) with key `0xAAAA` on every bit transmission to prevent watchdog resets during slow EEPROM multi-byte writes.
- **32-Byte Page Boundary Management:** Writes are partitioned into physical 32-byte pages:
  $$\text{Page Remaining} = \left(\left(\frac{\text{addr}}{32} + 1\right) \times 32\right) - \text{addr}$$
- **Read-Back Verification (`FUN_080127e0`):** Every written page is immediately read back and verified byte-by-byte. If verification fails, the operation retries up to 5 times (`EEPROM_MAX_RETRIES`).

### 10.2 EEPROM Memory Map Allocation

| Memory Address | Length | Checksum Addr | Description |
| :---: | :---: | :---: | :--- |
| `0x0020` | 27 Bytes | `0x015F` | **System Protection Configuration:** OVP, UVP, OCP, OTP, UTP thresholds |
| `0x0048` | 1 Byte | — | **Cell Configuration:** Number of series cells ($21$) |
| `0x004E` | 16 Bytes | `0x005E` | **Battery Specifications:** Nominal capacity ($70.0\text{ Ah}$), voltage ($76.6\text{ V}$) |
| `0x0060` | 32 Bytes | — | **Cell Voltage Calibration Gain Multipliers:** Cells 1 through 16 |
| `0x0080` | 10 Bytes | — | **Cell Voltage Calibration Gain Multipliers:** Cells 17 through 21 |
| `0x00A0` | 20 Bytes | — | **Current Sensor Shunt Calibration:** Zero-point offset and gain factor |
| `0x00B4` | 11 Bytes | `0x015C` | **NTC Temperature Calibration Offsets:** Sensors 1 through 4, MOS temp |
| `0x00C0` | 32 Bytes | `0x015B` | **Pack Serial Number / Barcode:** ASCII `"SPB24-DVC24-006-1010-A30"` |
| `0x00E0` | 32 Bytes | `0x0162` | **Bluetooth Device Name:** ASCII name for BLE module pairing |
| `0x0120` | 30 Bytes | `0x015E` | **Communication Config:** CAN baud ($250\text{k}$), Modbus baud ($9600$), Slave ID |
| `0x0140` | 24 Bytes | `0x015D` | **Hardware Metadata:** PCB revision, manufacturer code, production date |
| `0x0180` | 4 Bytes (u32) | — | **Cumulative Discharge Capacity:** Total Ah discharged over lifetime |
| `0x0184` | 4 Bytes (u32) | — | **Cumulative Charge Capacity:** Total Ah charged over lifetime |
| `0x0188` | 4 Bytes (u32) | — | **Battery Cycle Counter:** Total full equivalent cycle count |
| `0x018C` | 4 Bytes (u32) | — | **Operating Hours Counter:** Total MCU powered-on runtime (hours) |
| `0x018E` | 2 Bytes (u16) | — | **Historical Temperature Extremes:** Recorded max/min temperatures |
| `0x01A8` | 24 Bytes | — | **Fault Event Log Block 1:** Timestamped protection trip records |
| `0x01C0` | 32 Bytes | — | **Fault Event Log Block 2:** Critical system alert history |
| `0x01E0` | 32 Bytes | — | **Fault Event Log Block 3:** Overcurrent and short-circuit events |

---

## 11. Codebase Audit & Function Categorization Table

Every single function symbol in the decompiled firmware (`decompiled/bms_firmware_decompiled.c`, 481 defined function symbols) has been comprehensively audited, classified, and accounted for:

| Address Range | Count | Subsystem / Module | Status | Reconstruction Target |
| :---: | :---: | :--- | :---: | :--- |
| `0x08008000 – 0x0800A000` | 55 | **Keil C Runtime & Math Helpers**<br>(`__aeabi_uidiv`, `__aeabi_fmul`, `__scatterload`, `__decompress`) | **Handled** | Compiler-generated; natively provided by GCC / Clang runtime. |
| `0x0800A000 – 0x08010000` | 138 | **Devechip DVC1124 AFE Driver & ADC Acquisition**<br>(25 registers, voltage burst `0x1D`, current `0x02`, balancing matrix `0x56`) | **Converted** | Clean C driver in [`dvc1124_afe.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/dvc1124_afe.c) & [`dvc1124_afe.h`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/include/dvc1124_afe.h). |
| `0x08010000 – 0x08012000` | 27 | **2D OCV-SOC Engine & Coulomb Counter**<br>(Table 1: 21x12 capacity matrix, Table 2: 21x13 relaxation matrix) | **Converted** | Dual-mode hybrid estimator in [`bms_ocv.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_ocv.c) & [`bms_ocv.h`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/include/bms_ocv.h). |
| `0x08012000 – 0x08014000` | 36 | **24Cxx EEPROM Storage & Parameter Calibration**<br>(Bit-banged I2C, 32-byte page write verification, lifetime tracking) | **Converted** | Non-volatile manager in [`bms_storage.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_storage.c) & [`bms_storage.h`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/include/bms_storage.h). |
| `0x08014000 – 0x08019000` | 131 | **RS-485 / Modbus RTU & PC Diagnostic Protocol**<br>(USART1/2 @ 9600 8N1, FC 0x03/0x06, CRC16 0xA001, 0xEA 0xD1 frames) | **Converted** | Communication engine in [`bms_modbus.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_modbus.c) & [`bms_modbus.h`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/include/bms_modbus.h). |
| `0x08019000 – 0x0801F000` | 38 | **CAN 2.0B Protocol & Multi-Pack Arbitration**<br>(250 kbps, 29-bit extended frames, Master 0x14 / Slave 0x1D arbitration) | **Converted** | Protocol drivers in [`bms_can.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_can.c) & [`bms_parallel.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_parallel.c). |
| `0x0801F000 – 0x08020800` | 25 | **MCU System Clock, Watchdog & CMSIS HAL**<br>(144 MHz PLL, IWDG, GPIO alternate functions, VTOR relocation) | **Converted** | System configuration in [`bms_hal.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_hal.c) & [`cmsis/`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/cmsis/). |
| `0x08020800 – 0x08024000` | 31 | **BMS Core State Machine & Safety Supervisor**<br>(Standby, Charge, Discharge, Fault, MOSFET gate drivers, OVP/UVP/OCP/OTP) | **Converted** | Core state machine in [`bms_core.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_core.c) & [`bms_core.h`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/include/bms_core.h). |
| **Total Functions** | **481** | **All 8 Primary Subsystems** | **100% Accounted For** | **Complete C Codebase Compilable & Tested** |

---

## 12. Verification & Host Unit Test Suite

The entire clean C codebase is verified natively on the host workstation using MSYS2 GCC (`C:\msys64\ucrt64\bin\gcc.exe`).

### Executing the Complete Test Suite:
```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" -Wall -Wextra -I firmware_source/include -I firmware_source/cmsis `
    firmware_source/tests/test_bms_logic.c `
    firmware_source/src/bms_core.c `
    firmware_source/src/bms_can.c `
    firmware_source/src/bms_parallel.c `
    firmware_source/src/bms_hal.c `
    firmware_source/src/dvc1124_afe.c `
    firmware_source/src/bms_ocv.c `
    firmware_source/src/bms_modbus.c `
    firmware_source/src/bms_storage.c `
    -o test_bms_logic.exe

.\test_bms_logic.exe
```

### Complete Test Results:
```text
========================================================
Running BMS Firmware Core Unit Tests (Native Host)
========================================================

[Test 1] DVC1124 CRC8 Algorithm... PASS (CRC8 = 0xF1)
[Test 2] Modbus CRC16 Algorithm... PASS (CRC16 = 0xCDC5)
[Test 3] BMS Initialization & Calibration Thresholds... PASS (State: STANDBY, Capacity: 70Ah, SID: 0x14)
[Test 4] Cell Over-Voltage Protection (OVP @ 4185 mV)... PASS (OVP tripped at 4190mV, released at 4090mV)
[Test 5] Cell Under-Voltage Protection (UVC @ 2621 mV)... PASS (UVP tripped at 2600mV)
[Test 6] Multi-Pack Serial Number Arbitration... PASS (Master = 0x14, Slave = 0x1D)
[Test 7] Dynamic SOH Cycle Degradation Model... PASS (0 cyc: 100%, 100 cyc: 98%, 500 cyc: 90%, 1000 cyc: 80%, clamp >= 0)
[Test 8] CAN SOH & Capacity Telemetry Broadcast... PASS (CMD 0x40 IDX 0x01 generated)
[Test 9] DVC1124 AFE Register Map & ADC Conversions... PASS (V: 0.1mV/cnt, I: 5mA/cnt, Regs: 0x01..0x56)
[Test 10] 2D Chemical OCV-SOC Engine & Matrices... PASS (OCV: 3608mV->50%, 4185mV->100%, 2621mV->0%, 2D Matrices: 21x12, 21x13)
[Test 11] Hybrid Coulomb Counting & Rest Recalibration... PASS (Discharge -36A: 1000mAh Ah-count -> Rest 20s: OCV latch 50%)
[Test 12] Modbus RTU Read Holding Registers (FC 0x03)... PASS (V: 76.6V, I: -12.5A, SOC: 85%, SOH: 99%, CRC: 0x38E4)
[Test 13] Modbus RTU Write Single Register & Exceptions... PASS (Write OVP: 4200mV echo verified, Illegal Addr: 0x83-0x02, Corrupt CRC rejected)
[Test 14] Proprietary Upper-Computer Frame (0xEA 0xD1)... PASS (Frame: 0xEA 0xD1, Max: 3652mV, Min: 3630mV, Delta: 22mV, XOR: 0x92)
[Test 15] 24Cxx EEPROM 32-Byte Page Boundary & Lifetime Stats... PASS (Cross-page 48B verified, Config OVP: 4190mV/UVP: 2650mV, Lifetime: 350 cycles/24500 Ah)

========================================================
[✔] All 15 BMS Firmware Unit Tests PASSED Successfully!
========================================================
```

