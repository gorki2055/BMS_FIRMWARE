# Remaining Reverse-Engineering & Firmware Implementation Tasks

This document tracks all documentation updates (`FINDINGS.md`, `knowledge_base.md`) and C source implementation tasks (`firmware_source/`) identified during the full machine-code audit of `output/firmware_app_0x08008000.bin` and `decompiled/bms_firmware_decompiled.c`.

---

## Status Summary: ALL TASKS COMPLETED (28/28 Unit Tests Passing)

- [x] **CAN Protocol Engine & Binary Verification (`bms_can.h`, `bms_can.c`, `bms_types.h`, `main.c`, `test_bms_logic.c`):**
  - Verified 29-bit Extended CAN ID bit-field layout against raw machine code at `0x0801EF94` (`FUN_0801ef94`) and `0x0800DAF4` (`FUN_0800daf4`) and `document/CAN documentation.pdf` (`SID` at bits `28:24`, `DID` at `20:16`, `CMD` at `15:8`, `Index` at `7:0`).
  - Verified Little-Endian multi-byte payload encoding across all frames (`0x0801B55C`, `0x0801B764`, `0x0801B926`, `0x0801BC04`, `0x0801BE1A`).
  - Implemented 100 ms / 500 ms / 1000 ms periodic broadcasts (`0x0E`, `0x10`, `0x11`, `0x12`), Long Packet multi-frame transfers (`0x04` with Modbus CRC16 for `HWVER` `"A10.0"`, `FWVER` `"V02.0"`, and `SN`), General Response (`0x0A`), and full point-to-point command handling (`0x00`, `0x11`, `0x14`, `0x1A`, `0x1F`, `0x40`, `0x41`, `0x42`, `0x43`, `0x44`) plus binary command aliases.
- [x] **Part 1 — Documentation Updates (`FINDINGS.md` & `knowledge_base.md`):** All 10 subsystems (`Tasks 1.1 – 1.10`) documented in detail.
- [x] **Part 2 — Firmware Source Implementation (`firmware_source/`):** All missing hardware and runtime behaviors (`Tasks 2.1 – 2.6`) reconstructed in C and verified by `Tests 20 – 28` in `firmware_source/tests/test_bms_logic.c`.

---

## Part 1: Documentation Updates (`FINDINGS.md` & `knowledge_base.md`) — [COMPLETED]

- [x] **Task 1.1: Document Hardware-Bound Calibration & Anti-Cloning Lock (`MCU 96-Bit UID @ 0x1FFFF7F0`)**
  - **Binary Location:** `FUN_08018708` (`0x08018708`), `FUN_08017b3c` (`0x08017B3C`), `FUN_08017b04` (`0x08017B04`), `FUN_0802302c` (`0x0802302C`).
  - **Documented in:** `FINDINGS.md` (Section 4 & Section 11.1) and `knowledge_base.md` (Section 10.3).
  - **Implemented in Codebase:** `bms_hal_read_mcu_uid()`, `bms_storage_calc_uid_lock_crc()`, `bms_storage_write_uid_lock()`, `bms_storage_verify_uid_lock()` (Verified in `[Test 20]`).

- [x] **Task 1.2: Document Dual Non-Volatile Storage & On-Chip Flash Driver (`0x0800F4F8 – 0x0800FC44`)**
  - **Binary Location:** `FUN_0800f4f8` through `FUN_0800fc44` (`0x0800F4F8 – 0x0800FC44`), Flash controller registers at `0x40022000`.
  - **Documented in:** `FINDINGS.md` (Section 4 & Section 11.2) and `knowledge_base.md` (Section 10.4 & Section 11).
  - **Implemented in Codebase:** `bms_hal_flash_read()`, `bms_hal_flash_write()` (2 KB page RMW), `bms_storage_write_boot_iap_flag()`, `bms_storage_read_boot_iap_flag()` at offset `0x28A` (Verified in `[Test 21]`).

- [x] **Task 1.3: Document Multi-AFE Chip Support (`DVC1124` / `DVC1117` / `DVC1114`) & 3-Phase Interleaved Balancing**
  - **Binary Location:** `FUN_08008af4` (`0x08008AF4`), `FUN_08013a04` (`0x08013A04`).
  - **Documented in:** `FINDINGS.md` (Section 11.3) and `knowledge_base.md` (Section 4.4).
  - **Implemented in Codebase:** `dvc1124_set_model()`, `dvc1124_get_max_cells()`, `dvc1124_compute_interleaved_phase_mask()`, `dvc1124_set_balancing_phased()` on registers `0x67..0x69` (Verified in `[Test 22]`).

- [x] **Task 1.4: Document Hybrid Temperature Sensing (MCU Internal 12-Bit `ADC1`–`ADC4` + AFE NTCs)**
  - **Binary Location:** `FUN_08008914` (`0x08008914`), `FUN_080089c0` (`0x080089C0`), `FUN_08016cfc` (`0x08016CFC`), `FUN_0801f8ac` (`0x0801F8AC`).
  - **Documented in:** `FINDINGS.md` (Section 4 & Section 11.4) and `knowledge_base.md` (Section 4.5).
  - **Implemented in Codebase:** `bms_hal_read_internal_adc()` & `bms_core_update_hybrid_temperatures()` with open-wire NTC fault masking (Verified in `[Test 24]`).

- [x] **Task 1.5: Document Deep-Sleep (`PWR STOP`) & RTC Alarm Wake-Up Subsystem (`0x08016148 – 0x08018330`)**
  - **Binary Location:** `FUN_08016148` (`0x08016148`), `FUN_080161bc` (`0x080161BC`), `FUN_08016360` (`0x08016360`), `FUN_0801f7b8` (`0x0801F7B8`), `FUN_08021748` (`0x08021748`).
  - **Documented in:** `FINDINGS.md` (Section 4 & Section 11.5) and `knowledge_base.md` (Section 5.4).
  - **Implemented in Codebase:** `bms_hal_enter_stop_sleep()`, `bms_hal_restore_clocks_after_wake()`, `bms_core_enter_deep_sleep()`, `bms_core_wake_from_sleep()` (Verified in `[Test 25]`).

- [x] **Task 1.6: Document Pre-Charge Contactor Sequencing & MOSFET Body-Diode Protection**
  - **Binary Location:** `FUN_0801647c` (`0x0801647C`), `FUN_0801f580` (`0x0801F580`).
  - **Documented in:** `FINDINGS.md` (Section 9.2, 9.3 & Section 11.6) and `knowledge_base.md` (Section 5.3).
  - **Implemented in Codebase:** `BMS_STATE_PRECHARGE` with 10-tick timeout logging Fault `0xBE` & `bms_core_apply_mosfet_control()` body-diode bypass (Verified in `[Test 23]`).

- [x] **Task 1.7: Document 7-Port UART Architecture (`USART1..3`, `UART4..7`) & Correct `0x40015000` Mapping**
  - **Binary Location:** Literal pools `0x08015EA8 – 0x08015EF0` and `0x08020060 – 0x08020088`, RS-485 DE/RE toggle `FUN_08016420` (`0x08016420`), `IRQ 64` stub at `0x0800A6E0`.
  - **Documented in:** `FINDINGS.md` (Section 4, Section 5.2 & Section 11.7) and `knowledge_base.md` (Section 9.1).
  - **Implemented in Codebase:** `BmsUartPort_t`, `bms_hal_uart_get_base_addr()`, `bms_hal_rs485_set_de()`, `bms_hal_uart_transmit()` (Verified in `[Test 24]`).

- [x] **Task 1.8: Document Complete 3-Region Keil Scatter-Loading Table (`0x08023154 – 0x08023184`)**
  - **Binary Location:** `0x08023154 – 0x08023184`, `__decompress` (`0x08008820`), `__scatterload_zeroinit` (`0x08022F94`).
  - **Documented in:** `FINDINGS.md` (Section 8.1 & Section 11.8) and `knowledge_base.md` (Stage 4 & Section 11).

- [x] **Task 1.9: Document Per-Cell ADC Gain Calibration (`FUN_08016000`) & Self-Discharge Model (`FUN_0801fc8c`)**
  - **Binary Location:** `FUN_08016000` (`0x08016000`), `FUN_0801fc8c` (`0x0801FC8C`).
  - **Documented in:** `FINDINGS.md` (Section 11.9) and `knowledge_base.md` (Section 4.3.4 & Section 6.4).
  - **Implemented in Codebase:** `bms_storage_save_cell_cal()`, `bms_storage_load_cell_cal()`, `bms_core_apply_cell_calibration()`, and `bms_ocv_apply_self_discharge()` (Verified in `[Test 20]` & `[Test 25]`).

- [x] **Task 1.10: Document 5-Stage LED SOC Bar-Graph (`FUN_0800fc48`) & Black-Box Fault Logger (`FUN_08019844`)**
  - **Binary Location:** `FUN_0800fc48` (`0x0800FC48`), `FUN_08019844` (`0x08019844`), CAN internal parallel bus frames (`0x101..0x106`, `0x201..0x203`, `0x141DF001`).
  - **Documented in:** `FINDINGS.md` (Section 11.10) and `knowledge_base.md` (Section 5.5, Section 7.2 & Section 10.5).
  - **Implemented in Codebase:** `bms_core_get_led_bar_stage()`, `bms_storage_log_event()`, `bms_storage_read_last_event()` (Verified in `[Test 23]` & `[Test 25]`).

---

## Part 2: Firmware Source Implementation Tasks (`firmware_source/`) — [COMPLETED]

- [x] **Task 2.1: Pre-Charge Contactor Sequencing & Fault `0xBE` (`bms_core.c`, `bms_types.h`)**
  - Added `BMS_STATE_PRECHARGE`, `precharge_mos_on`, and `precharge_fail` fault bit (`Fault 0xBE`) with 10-tick timeout (`FUN_0801647c`). Verified in `[Test 23]`.
- [x] **Task 2.2: MOSFET Body-Diode Conduction Protection (`bms_core.c`, `bms_config.h`)**
  - Implemented `bms_core_apply_mosfet_control()` (`FUN_0801f580`) to automatically close the opposing MOSFET when current exceeds $\pm 1.5\text{ A}$ (`BMS_BODY_DIODE_PROTECT_MA`). Verified in `[Test 23]`.
- [x] **Task 2.3: 3-Phase Interleaved Cell Balancing & Multi-AFE Support (`dvc1124_afe.h`, `dvc1124_afe.c`, `bms_core.c`)**
  - Added runtime AFE model selector (`AFE_MODEL_DVC1124 = 0x0464`, `AFE_MODEL_DVC1117 = 0x045D`, `AFE_MODEL_DVC1114 = 0x045A`) and 3-phase odd/even interleaved balancing across registers `0x67..0x69` (`FUN_08013a04`). Verified in `[Test 22]`.
- [x] **Task 2.4: Dual Non-Volatile Storage, On-Chip Flash Driver & Bootloader IAP Trigger at `0x28A` (`bms_storage.h`, `bms_storage.c`, `bms_hal.h`, `bms_hal.c`, `bms_can.c`, `bms_modbus.c`)**
  - Added 2 KB page read-modify-write Flash driver (`bms_hal_flash_read` / `bms_hal_flash_write`), dual storage medium selector (`BMS_STORAGE_MEDIUM_EEPROM` vs `BMS_STORAGE_MEDIUM_FLASH`, `*DAT_0800f950`), and bootloader IAP magic trigger at Flash offset `0x28A` (`FUN_0800f850`) on both CAN `CMD 0x1A` (`"UPDATE"`) and UART `CMD 0x7A` (`BMS_HOST_FRAME_CMD_IAP`). Verified in `[Test 21]`, `[Test 26]`, and `[Test 27]`.
- [x] **Task 2.5: MCU 96-Bit UID Calibration Lock & Per-Cell Voltage Gain Scaling (`bms_storage.h`, `bms_storage.c`, `bms_core.c`, `bms_can.c`)**
  - Implemented `bms_hal_read_mcu_uid()` (`0x1FFFF7F0`), `bms_storage_verify_uid_lock()` (`EEPROM 0x0100`, `FUN_08017b3c`), per-cell voltage gain scaling (`EEPROM 0x0060 / 10000.0f`, `FUN_08016000`), and CAN `CMD 0x44` custom calibration read/write (`FUN_0801afbc`). Verified in `[Test 20]` and `[Test 28]`.
- [x] **Task 2.6: Quiescent Self-Discharge Compensation, 3-Slot Black-Box Fault Logger, 5-Stage LED Driver & Parallel Bus Heartbeat (`bms_ocv.c`, `bms_storage.c`, `bms_core.c`, `bms_parallel.c`, `n32g45x.h`, `Makefile`)**
  - Implemented quiescent self-discharge (`bms_ocv_apply_self_discharge()`, `FUN_0801fc8c`), 3-slot Black-Box fault snapshot ring buffer (`0x01A8`, `0x01C0`, `0x01E0`, `FUN_08019844`), 5-stage LED SOC bar-graph (`bms_core_get_led_bar_stage()`, `FUN_0800fc48`), internal parallel-bus heartbeat (`0x141DF001`, `0x101..0x106`, `0x201..0x203`), and updated N32G45x CMSIS peripheral mappings (`UART6`, `UART7`, `FMC`, `PWR`, `RTC`, `BKP`, `ADC1..4`) and `Makefile`. Verified in `[Test 23]` through `[Test 28]`.
