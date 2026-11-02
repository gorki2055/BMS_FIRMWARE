# BMS_FIRMWARE — 21S 70Ah NCM Battery Management System Reverse Engineering

Reverse engineering analysis, hardware documentation, Ghidra decompilation, and clean-room reconstructed C source code for a proprietary **21S 70Ah NCM** Battery Management System (BMS) firmware image (`V28`).

---

## 1. System Overview

| Parameter | Specification |
| :--- | :--- |
| **Target Microcontroller** | **Nations Technologies N32G452** (ARM Cortex-M4F @ 144MHz, 512KB Flash, 144KB SRAM) |
| **Analog Front-End (AFE)** | **Nanjing Devechip DVC1124-1** (21-series cell monitor, I2C 100kHz, CRC8 poly `0x07`) |
| **Battery Chemistry** | Lithium Nickel Cobalt Manganese Oxide (**NCM**) |
| **Pack Configuration** | **21S 70Ah** (~75.6 V nominal, 88.2 V max charge cutoff) |
| **Communication Protocols** | **CAN 2.0B** @ 250 kbps (29-bit extended IDs), **RS-485** / UART @ 9600 baud |
| **Target Application** | Nepal Electric Vehicle Fleet (`尼泊尔21s70AhNCM`) |
| **Original Firmware Tag** | `6495.004615.SPB24-DVC24-006-1010-A30.尼泊尔21s70AhNCM.CAN(250k).UART.485(9600).V28.DL.260316.B72E0EEC.hex` |

---

## 2. Factory Calibrated Thresholds

Extracted from Keil scatter-load decompression tables (`0x08023184` $\rightarrow$ Retention SRAM `0x20020000`):

| Parameter | Calibrated Threshold | Description |
| :--- | :--- | :--- |
| **Cell Over-Voltage Protection (OVP)** | **4,185 mV** | Hard charging cutoff per cell |
| **Cell Balancing Trigger** | **4,120 mV** | Threshold to initiate passive cell balancing ($\Delta > 20\text{ mV}$) |
| **Nominal Cell Rating** | **3,608 mV** | Standard nominal voltage |
| **Under-Voltage Warning (UVW)** | **2,831 mV** | Dashboard alert & power derating |
| **Under-Voltage Cutoff (UVC)** | **2,621 mV** | Hard discharge cutoff (contactor open) |
| **Nominal Pack Capacity** | **70 Ah** | Full charge capacity rating |

---

## 3. Repository Structure

```
├── README.md                   # Repository landing page and project overview
├── PROJECT_OVERVIEW.md         # Comprehensive reverse engineering technical specification
├── FINDINGS.md                 # Technical findings log & memory mapping analysis
├── parse_hex.py                # Python container parser and binary extractor
├── requirements.txt            # Python dependencies (capstone, intelhex, pymupdf)
│
├── firmware_source/            # Reconstructed, modular, buildable C source project
│   ├── CMakeLists.txt          # CMake cross-compilation configuration
│   ├── Makefile                # GNU Makefile for arm-none-eabi-gcc
│   ├── n32g45x_flash.ld        # Linker script (Flash @ 0x08008000, 144 KB SRAM)
│   ├── cmsis/                  # Nations N32G452 register maps & Cortex-M4 vector table
│   ├── include/                # Typed headers (config, telemetry, CAN, AFE, parallel)
│   ├── src/                    # Core BMS logic, CAN handler, DVC1124 driver, HAL
│   └── tests/                  # Native host unit test runner (validates all algorithms)
│
├── decompiled/                 # Full decompiled C source output from Ghidra
│   └── bms_firmware_decompiled.c # 526 decompiled functions (819 KB, 28,150 lines)
│
├── ghidra_project/             # Ready-to-open Ghidra 12.2 project database
│   ├── BMS_Project.gpr         # Project descriptor file
│   └── BMS_Project.rep/        # Program database with memory maps & labeled symbols
│
├── output/                     # Extracted bare-metal firmware binaries
│   ├── firmware_app_0x08008000.bin  # Clean application binary (112,448 bytes)
│   └── firmware_app_0x08008000.ihex # Intel HEX with base address 0x08008000
│
├── document/                   # Hardware schematics, datasheets & protocol docs
│   ├── CAN documentation.pdf   # 29-bit CAN ID protocol specification
│   ├── High level BMS logic.pdf# Dual-pack 5% switching & MOS control logic
│   ├── data sheets/            # MCU (N32G452), AFE (DVC1124-1), and MOSFET datasheets
│   └── schematic/              # Board schematics (SPB24-DVC24-006-0606/1010)
│
└── scripts/                    # Automation scripts for analysis and tooling
    ├── GhidraSetupBms.java     # Headless Ghidra script (memory maps, vectors, Thumb mode)
    ├── run_ghidra_headless.bat # Batch automation for Ghidra analysis
    └── export_decompiled.bat   # Script to re-export decompiled C code
```

---

## 4. Getting Started

### Inspecting in Ghidra GUI
1. Open Ghidra (`ghidraRun.bat`).
2. Select **File $\rightarrow$ Open Project...**
3. Navigate to `ghidra_project/` and open `BMS_Project.gpr`.
4. Double click `firmware_app_0x08008000.ihex` to browse all labeled vectors, peripheral memory maps, and decompiled routines.

### Building the Reconstructed Source Code
See [`firmware_source/README.md`](firmware_source/README.md) for full build instructions with `arm-none-eabi-gcc` or `CMake`.
