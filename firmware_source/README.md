# 21S 70Ah NCM Battery Management System (BMS) — Clean Source Project

This directory contains the reconstructed, modular C source code for the proprietary BMS firmware (`V28`), reverse-engineered from the original container `6495.004615.SPB24-DVC24-006-1010-A30.尼泊尔21s70AhNCM.CAN(250k).UART.485(9600).V28.DL.260316.B72E0EEC.hex`.

---

## 1. System Specifications

| Parameter | Value |
| :--- | :--- |
| **Target MCU** | Nations Technologies **N32G452** (ARM Cortex-M4F @ 144MHz) |
| **Battery Chemistry** | Lithium Nickel Cobalt Manganese Oxide (**NCM**) |
| **Cell Configuration** | **21S** (21 series cells, nominal ~75.6 V, max 88.2 V) |
| **Nominal Capacity** | **70 Ah** (70,000 mAh) |
| **Analog Front-End (AFE)** | Nanjing Devechip **DVC1124-1** (I2C on PB6/PB7, 100 kHz, CRC8) |
| **Communication Bus** | **CAN 2.0B** @ 250 kbps (PA11/PA12, 29-bit extended frames) |
| **RS-485 / Debug** | USART1 @ 9600 baud (PA9/PA10) |
| **Target Market** | Nepal Electric Vehicle Fleet (`尼泊尔21s70AhNCM`) |

---

## 2. Factory Calibrated Thresholds (`include/bms_config.h`)

Extracted directly from the firmware's decompressed scatter-load table:

- **Over-Voltage Protection (OVP):** `4,185 mV` (4.185 V per cell cutoff)
- **Cell Balancing Trigger:** `4,120 mV` (balancing starts with $>20\text{ mV}$ delta)
- **Nominal Cell Rating:** `3,608 mV`
- **Under-Voltage Warning (UVW):** `2,831 mV` (VCU alert / power derating)
- **Under-Voltage Cutoff (UVC):** `2,621 mV` (hard discharge disconnect)
- **Deep Sleep Shutdown:** `2,500 mV`

---

## 3. Directory Structure

```
firmware_source/
├── CMakeLists.txt          # CMake cross-compilation definition
├── Makefile                # Standard GNU Makefile for arm-none-eabi-gcc
├── n32g45x_flash.ld        # Linker script (Flash @ 0x08008000, SRAM 144KB)
├── cmsis/
│   ├── n32g45x.h           # Complete Nations N32G452 register map
│   └── startup_n32g45x.c   # Interrupt vector table & Reset_Handler
├── include/
│   ├── bms_config.h        # Factory thresholds & hardware pin assignments
│   ├── bms_types.h         # Telemetry, faults, and state machine types
│   ├── bms_core.h          # Core protection supervisor prototypes
│   ├── bms_can.h           # CAN 250k protocol parser & frame builders
│   ├── bms_parallel.h      # Dual-pack 5% switching logic prototypes
│   ├── dvc1124_afe.h       # Devechip DVC1124-1 register definitions
│   └── bms_hal.h           # GPIO, CAN, and I2C hardware abstraction
└── src/
    ├── main.c              # Application superloop (10ms, 100ms, 1s tasks)
    ├── bms_core.c          # Protections, balancing decision, and state machine
    ├── bms_can.c           # CAN packet reception, "READ" dispatch, Modbus CRC16
    ├── bms_parallel.c      # Dual battery parallel arbitration (Master 5% -> Slave -> Master)
    ├── dvc1124_afe.c       # DVC1124 I2C read/write with CRC8 check
    └── bms_hal.c           # N32G452 GPIO and peripheral control
```

---

## 4. How to Build

### Using GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`)

1. Install `gcc-arm-none-eabi` (via `choco install make gcc-arm-embedded -y` or manual download).
2. Run:
   ```bash
   make all
   ```
3. Outputs will be generated in `build/`:
   - `build/bms_firmware.elf`
   - `build/bms_firmware.hex`
   - `build/bms_firmware.bin`

### Using CMake & Ninja

```bash
mkdir build && cd build
cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=../arm-toolchain.cmake ..
ninja
```
