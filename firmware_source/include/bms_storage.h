/**
 * @file bms_storage.h
 * @brief BMS 24Cxx Non-Volatile EEPROM Storage & Parameter Calibration Manager
 *
 * Reverse-engineered from N32G45x BMS Firmware binary (0x08012000 - 0x08014000).
 * Handles:
 *  - External 24C32 / 24C64 I2C EEPROM on GPIOC (0x40011400) with IWDG keep-alive.
 *  - 32-byte page boundary write algorithm with 5-retry read-back verification (FUN_080127e0).
 *  - Checksum validation for protected calibration & configuration blocks.
 *  - Lifetime cycle counting, cumulative charge/discharge Ah, and fault logging.
 */

#ifndef BMS_STORAGE_H
#define BMS_STORAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "bms_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 24Cxx EEPROM Device Addresses */
#define EEPROM_I2C_ADDR_WRITE           0xA0
#define EEPROM_I2C_ADDR_READ            0xA1
#define EEPROM_PAGE_SIZE                32   /* 32 bytes per physical write page */
#define EEPROM_MAX_RETRIES              5    /* Retry limit in FUN_080127e0 */

/* EEPROM Memory Map Allocation (extracted from literal pools & call sites) */
#define EEPROM_ADDR_SYS_CONFIG          0x0020 /* Protection limits (27 bytes) */
#define EEPROM_LEN_SYS_CONFIG           27

#define EEPROM_ADDR_CELL_COUNT          0x0048 /* Number of series cells (1 byte = 21) */
#define EEPROM_ADDR_BATTERY_RATING      0x004E /* Capacity (70Ah) & Voltage rating (16 bytes) */
#define EEPROM_LEN_BATTERY_RATING       16

#define EEPROM_ADDR_CELL_CAL_1_16       0x0060 /* Cell 1-16 Voltage Multipliers (32 bytes) */
#define EEPROM_ADDR_CELL_CAL_17_21      0x0080 /* Cell 17-21 Voltage Multipliers (10 bytes) */
#define EEPROM_ADDR_CURRENT_CAL         0x00A0 /* Current sensor shunt zero/gain (20 bytes) */
#define EEPROM_ADDR_NTC_CAL             0x00B4 /* NTC temperature offsets (11 bytes) */
#define EEPROM_ADDR_SERIAL_NUMBER       0x00C0 /* Pack Serial Number / Barcode (32 bytes) */
#define EEPROM_ADDR_BT_NAME             0x00E0 /* Bluetooth module device name */
#define EEPROM_ADDR_COMM_CONFIG         0x0120 /* CAN & RS-485 configuration (30 bytes) */
#define EEPROM_ADDR_MFG_DATA            0x0140 /* Hardware revision & manufacturer (24 bytes) */

/* Checksum byte storage addresses (reconstructed from FUN_0801cd98 / FUN_080127e0) */
#define EEPROM_ADDR_CHECKSUM_RATING     0x005E /* Battery rating checksum */
#define EEPROM_ADDR_CHECKSUM_SERIAL     0x015B /* Serial number checksum */
#define EEPROM_ADDR_CHECKSUM_NTC        0x015C /* NTC calibration checksum */
#define EEPROM_ADDR_CHECKSUM_MFG        0x015D /* Manufacturer data checksum */
#define EEPROM_ADDR_CHECKSUM_COMM       0x015E /* Communication config checksum */
#define EEPROM_ADDR_CHECKSUM_CONFIG     0x015F /* System config checksum */
#define EEPROM_ADDR_CHECKSUM_BT         0x0162 /* Bluetooth config checksum */

/* Lifetime Operating & Degradation Counters */
#define EEPROM_ADDR_LIFETIME_DSG_AH     0x0180 /* Cumulative discharge Ah (uint32_t) */
#define EEPROM_ADDR_LIFETIME_CHG_AH     0x0184 /* Cumulative charge Ah (uint32_t) */
#define EEPROM_ADDR_CYCLE_COUNT         0x0188 /* Total cycle count (uint32_t) */
#define EEPROM_ADDR_OPERATING_HOURS     0x018C /* Total run time (uint32_t) */
#define EEPROM_ADDR_TEMP_EXTREMES       0x018E /* Historical Max/Min temperatures (uint16_t) */

/* Historical Fault Event Logs */
#define EEPROM_ADDR_FAULT_LOG_1         0x01A8 /* Fault event block 1 (24 bytes) */
#define EEPROM_ADDR_FAULT_LOG_2         0x01C0 /* Fault event block 2 (32 bytes) */
#define EEPROM_ADDR_FAULT_LOG_3         0x01E0 /* Fault event block 3 (32 bytes) */

/**
 * @brief Initialize Non-Volatile Storage Manager
 */
void bms_storage_init(void);

/**
 * @brief Calculate block checksum (reconstructed from FUN_0800ba48 / FUN_08016658)
 * @param data Pointer to data block
 * @param len Length in bytes
 * @return 8-bit checksum
 */
uint8_t bms_storage_calc_checksum(const uint8_t *data, uint16_t len);

/**
 * @brief Read arbitrary data block from EEPROM (reconstructed from FUN_08012330)
 * @param addr EEPROM memory start address
 * @param dest Output buffer
 * @param len Number of bytes to read
 * @return 0 on success, <0 on failure
 */
int bms_storage_read_block(uint16_t addr, uint8_t *dest, uint16_t len);

/**
 * @brief Write page to EEPROM with 5-retry read-back verification (FUN_080127e0)
 * @param addr EEPROM memory address (handles 32-byte page boundary)
 * @param src Data to write
 * @param len Number of bytes to write
 * @return 0 on verified success, <0 on failure
 */
int bms_storage_write_verified(uint16_t addr, const uint8_t *src, uint16_t len);

/**
 * @brief Load saved protection limits & parameters into BMS context
 * @param ctx Target BMS context
 * @return 0 on success, <0 if checksum invalid or uninitialized (falls back to defaults)
 */
int bms_storage_load_config(BmsContext_t *ctx);

/**
 * @brief Save current protection limits & parameters to EEPROM with verified checksum
 * @param ctx Source BMS context
 * @return 0 on success, <0 on error
 */
int bms_storage_save_config(const BmsContext_t *ctx);

/**
 * @brief Update lifetime cycle count and cumulative Ah in EEPROM
 * @param cycle_count Battery cycle counter
 * @param dsg_ah Cumulative discharge Ah
 * @param chg_ah Cumulative charge Ah
 * @return 0 on success, <0 on error
 */
int bms_storage_update_lifetime(uint32_t cycle_count, uint32_t dsg_ah, uint32_t chg_ah);

/**
 * @brief Read lifetime cycle count and cumulative Ah from EEPROM
 * @param cycle_count Output cycle counter
 * @param dsg_ah Output cumulative discharge Ah
 * @param chg_ah Output cumulative charge Ah
 * @return 0 on success, <0 on error
 */
int bms_storage_read_lifetime(uint32_t *cycle_count, uint32_t *dsg_ah, uint32_t *chg_ah);

#ifdef __cplusplus
}
#endif

#endif /* BMS_STORAGE_H */
