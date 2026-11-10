/**
 * @file factory_symbols.h
 * @brief Exact Factory Firmware Flash Function Pointers & SRAM Symbols (0x08008000 Binary)
 *
 * Allows custom C logic compiled at 0x08023800 to call untouched factory drivers
 * and read/write live BMS telemetry in SRAM without risking CAN or Bootloader lockout.
 */

#ifndef FACTORY_SYMBOLS_H
#define FACTORY_SYMBOLS_H

#include <stdint.h>
#include <stdbool.h>

/* ==========================================================================
 * 1. N32G45x Hardware Reset & Watchdog Registers (For Safe-Mode Fail-Safe)
 * ========================================================================== */
#define N32_RCC_CSR_REG         (*(volatile uint32_t *)0x40021024UL)
#define N32_RCC_CSR_IWDGRSTF    (1UL << 29) /* Independent Watchdog Reset Flag */
#define N32_RCC_CSR_WWDGRSTF    (1UL << 30) /* Window Watchdog Reset Flag */
#define N32_RCC_CSR_SFTRSTF     (1UL << 28) /* Software Reset Flag */
#define N32_RCC_CSR_RMVF        (1UL << 24) /* Clear Reset Flags Bit */

#define N32_IWDG_KEY_REG        (*(volatile uint32_t *)0x40003000UL)
#define N32_IWDG_RELOAD_MAGIC   0x0000AAAAUL

/* Backup Register 1 (Persists across Watchdog & Software Resets) */
#define N32_BKP_DR1_REG         (*(volatile uint16_t *)0x40006C04UL)
#define SAFE_MODE_MAGIC_LOCKOUT 0xDEADU

/* ==========================================================================
 * 2. Untouched Factory Functions (Thumb-2 addresses have bit 0 = 1 for BLX)
 * ========================================================================== */
typedef void (*factory_void_fn_t)(void);
typedef void (*factory_delay_ms_fn_t)(uint32_t ms);
typedef bool (*factory_can_tx_fn_t)(uint32_t data_ptr, uint8_t dlc, uint32_t can_id,
                                    uint8_t frame_type, uint8_t proto);

/* 10 ms Fast Protection, Current Sensing & MOSFET Body-Diode Handler (0x0801F580) */
#define FACTORY_TASK_10MS       ((factory_void_fn_t)(0x0801F580UL | 1UL))

/* 100 ms Periodic CAN Broadcasts & State Machine Handler (0x0801F654) */
#define FACTORY_TASK_100MS      ((factory_void_fn_t)(0x0801F654UL | 1UL))

/* 400 ms Slow Balancing, Temperature, OCV-SOC & Watchdog Handler (0x0801F6CC) */
#define FACTORY_TASK_400MS      ((factory_void_fn_t)(0x0801F6CCUL | 1UL))

/* Factory CAN Bus Frame Transmitter (FUN_08023084 @ 0x08023084) */
#define FACTORY_CAN_TRANSMIT    ((factory_can_tx_fn_t)(0x08023084UL | 1UL))

/* Factory Hardware Watchdog Kick (FUN_0801806C @ 0x0801806C) */
#define FACTORY_FEED_WATCHDOG   ((factory_void_fn_t)(0x0801806CUL | 1UL))

/* ==========================================================================
 * 3. Live Factory SRAM Telemetry & Control Addresses
 *    (Extracted from literal pools 0x0801B500..0x0801BF48 & 0x08021838..0x08021854)
 * ========================================================================== */

/* Array of 21 Individual Cell Voltages in mV (uint16_t[24] @ 0x20021344) */
#define FACTORY_SRAM_CELL_MV        ((volatile uint16_t *)0x20021344UL)

/* MainBMS Protection & MOSFET State Struct Base (0x200212F0) */
#define FACTORY_SRAM_STATE_BASE     ((volatile uint8_t  *)0x200212F0UL)

/* Pack Voltage, Current, SOC, SOH & Capacity Struct Base (0x20021560) */
#define FACTORY_SRAM_PACK_BASE      ((volatile uint8_t  *)0x20021560UL)

/* Temperature & NTC Sensor Struct Base (0x2002054C) */
#define FACTORY_SRAM_TEMP_BASE      ((volatile int8_t   *)0x2002054CUL)

/* Super-Loop Scheduler Tick Structure (0x20020AE4: +4=10ms, +6=100ms, +8=400ms) */
#define FACTORY_SRAM_SCHED_BASE     ((volatile uint8_t  *)0x20020AE4UL)

#endif /* FACTORY_SYMBOLS_H */

