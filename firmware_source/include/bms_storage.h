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

/* Historical Fault Event Logs & Persistent AFE Fault Counters (FUN_080196d0 / FUN_08019844) */
#define EEPROM_ADDR_FAULT_LOG_1         0x01A8 /* Fault event block 1 (24 bytes) */
#define EEPROM_ADDR_FAULT_LOG_2         0x01C0 /* Fault event ring index & metadata (4 bytes) */
#define EEPROM_ADDR_FAULT_LOG_3         0x01E0 /* Fault event block 3 (32 bytes) */

#define EEPROM_ADDR_CNT_AFE_TEMP_1      0x01C4 /* AFE Temp / NTC Fault 1 Counter (uint16_t) */
#define EEPROM_ADDR_CNT_AFE_TEMP_2      0x01C6 /* AFE Temp / NTC Fault 2 Counter (uint16_t) */
#define EEPROM_ADDR_CNT_AFE_TEMP_3      0x01C8 /* AFE Temp / NTC Fault 3 Counter (uint16_t) */
#define EEPROM_ADDR_CNT_AFE_TEMP_4      0x01CA /* AFE Temp / NTC Fault 4 Counter (uint16_t) */
#define EEPROM_ADDR_CNT_MOSFET_OTP      0x01CC /* MOSFET Over-Temperature Trip Counter (uint16_t) */
#define EEPROM_ADDR_CNT_CELL_SENSE_ERR  0x01D6 /* Cell Sense Open-Wire / Extreme Delta Counter (uint16_t) */
#define EEPROM_ADDR_CNT_AFE_HW_OV       0x01D8 /* DVC1124 Reg 0x00 Bit 3 HW Cell OV Counter (uint16_t) */
#define EEPROM_ADDR_CNT_AFE_HW_UV       0x01DA /* DVC1124 Reg 0x00 Bit 4 HW Cell UV Counter (uint16_t) */
#define EEPROM_ADDR_CNT_AFE_HW_OCD      0x01DC /* DVC1124 Reg 0x00 Bit 1 HW Discharge OCD Counter (uint16_t) */
#define EEPROM_ADDR_CNT_AFE_HW_SCD      0x01E0 /* DVC1124 Reg 0x00 Bit 0 HW Short-Circuit SCD Counter (uint16_t) */
#define EEPROM_ADDR_CNT_AFE_HW_OCC      0x01E2 /* DVC1124 Reg 0x00 Bit 2 HW Charge OCC Counter (uint16_t) */

/* MCU 96-Bit UID + Calibration Lock Word (FUN_08017b3c / FUN_08018768) */
#define EEPROM_ADDR_UID_LOCK            0x0100 /* 16-bit UID + cell calibration lock word */
#define EEPROM_LEN_CELL_CAL_TOTAL       42     /* 21 cells * 2 bytes (0x0060..0x0089) */
#define BMS_CELL_CAL_REF_DIVISOR        10000.0f /* Reference constant DAT_08016140 (10000 = 1.0000x) */

/* On-Chip Flash Bootloader IAP Upgrade Trigger Offset (FUN_0800f850) */
#define BMS_FLASH_BOOT_IAP_OFFSET       0x028AU
#define BMS_BOOT_IAP_MAGIC              0x5AA5F00FUL

/* Dual Non-Volatile Storage Medium Selector (*DAT_0800f950 in FUN_0800f850) */
typedef enum {
    BMS_STORAGE_MEDIUM_EEPROM = 0,  /* External 24C32/24C64 I2C EEPROM (0xA0/0xA1) */
    BMS_STORAGE_MEDIUM_FLASH  = 1   /* On-Chip N32G45x Flash User Partition (0x08028000) */
} BmsStorageMedium_t;

#define BMS_FAULT_LOG_SLOTS             3U     /* 3 historical fault log slots (0x01A8, 0x01C0, 0x01E0) */

/* Black-Box Fault Snapshot Event Codes (param_2 of FUN_08019844) */
#define BMS_EVENT_PROT_TRIGGERED        0x08U  /* Hardware/AFE comparator protection triggered */
#define BMS_EVENT_PROT_LATCHED          0x09U  /* Hardware/AFE comparator protection latched */
#define BMS_EVENT_DSG_OCP               0x1EU  /* Discharge over-current trip */
#define BMS_EVENT_CHG_OCP               0x1FU  /* Charge over-current trip */
#define BMS_EVENT_PACK_OVP              0x20U  /* Over-voltage trip */
#define BMS_EVENT_TEMP_FAULT            0x22U  /* Over/under temperature trip */
#define BMS_EVENT_AFE_WATCHDOG_TIMEOUT  0x32U  /* AFE state / protection recovery timeout (FUN_080097a4) */
#define BMS_EVENT_UART_IAP              0x64U  /* UART firmware upgrade reset */
#define BMS_EVENT_AFE_COMM_RECOVERY     0x83U  /* DVC1124 I2C comm failure & chip re-init (FUN_0800d620) */
#define BMS_EVENT_CAN_IAP               0x84U  /* CAN firmware upgrade reset */
#define BMS_EVENT_AFE_ALERT_TRIP        0xA0U  /* DVC1124 hardware ALERT pin asserted >4 ticks (FUN_08009024) */
#define BMS_EVENT_AFE_ALERT_CLEAR       0xA1U  /* DVC1124 hardware ALERT pin cleared >4 ticks (FUN_08009024) */
#define BMS_EVENT_PRECHARGE_FAIL        0xBEU  /* Pre-charge timeout fault (FUN_0801647c) */

/* Black-Box Fault Bit Indices (param_1 of FUN_08019844 -> bytes 0x17..0x19) */
#define BMS_FAULT_IDX_AFE_HW_OV         0x01U  /* DVC1124 Reg 0x00 Bit 3: Hardware Cell OV */
#define BMS_FAULT_IDX_AFE_HW_UV         0x03U  /* DVC1124 Reg 0x00 Bit 4: Hardware Cell UV */
#define BMS_FAULT_IDX_AFE_HW_OCD        0x09U  /* DVC1124 Reg 0x00 Bit 1: Hardware Discharge OCD */
#define BMS_FAULT_IDX_AFE_HW_SCD        0x0AU  /* DVC1124 Reg 0x00 Bit 0: Hardware Short-Circuit SCD */
#define BMS_FAULT_IDX_AFE_HW_OCC        0x0BU  /* DVC1124 Reg 0x00 Bit 2: Hardware Charge OCC */
#define BMS_FAULT_IDX_MOSFET_OTP        0x13U  /* Power MOSFET Over-Temperature Trip */
#define BMS_FAULT_IDX_CELL_SENSE_DROP   0x15U  /* Broken Cell Sense Wire / Extreme Imbalance */

/* Black-Box Telemetry Snapshot Record (24 bytes at EEPROM 0x01A8, FUN_08019844) */
typedef struct {
    uint8_t  event_code;        /* Event ID (0x1E, 0x1F, 0x20, 0x22, 0x64, 0x84, 0xBE) */
    uint8_t  soc_pct;           /* SOC at event time */
    uint16_t min_cell_mv;       /* Lowest cell voltage (mV) */
    uint16_t max_cell_mv;       /* Highest cell voltage (mV) */
    int16_t  max_temp_c;        /* Highest temperature (°C) */
    uint32_t uptime_sec;        /* Timestamp (seconds) */
    uint32_t pack_voltage_mv;   /* Total pack voltage (mV) */
    int32_t  current_ma;        /* Pack current (mA) */
    uint32_t fault_flags;       /* Active BmsFaultFlags_t bitmask */
} BmsFaultSnapshot_t;

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

/**
 * @brief Compute 16-bit hardware-bound checksum across EEPROM cell calibration + 96-bit MCU UID (FUN_08017b04)
 */
uint16_t bms_storage_calc_uid_lock_crc(const uint8_t *cal_bytes, uint16_t cal_len, const uint8_t uid[12]);

/**
 * @brief Write hardware-bound UID + calibration lock word to EEPROM 0x0100 (FUN_08017b3c)
 */
int bms_storage_write_uid_lock(void);

/**
 * @brief Verify EEPROM 0x0100 lock word against current MCU 96-bit UID & calibration table (FUN_08017b3c)
 */
bool bms_storage_verify_uid_lock(BmsContext_t *ctx);

/**
 * @brief Save and load per-cell voltage gain multipliers at EEPROM 0x0060 (FUN_08016000)
 */
int bms_storage_save_cell_cal(const uint16_t gain_milli[BMS_SERIES_CELLS]);
int bms_storage_load_cell_cal(float gain_out[BMS_SERIES_CELLS]);

/**
 * @brief Write/Read 4-byte bootloader IAP upgrade flag at on-chip Flash offset 0x28A (FUN_0800f850)
 */
int bms_storage_write_boot_iap_flag(uint32_t magic);
int bms_storage_read_boot_iap_flag(uint32_t *magic_out);

/**
 * @brief Record and retrieve black-box fault/event snapshot at EEPROM 0x01A8..0x01E0 (FUN_08019844)
 */
int bms_storage_log_event(uint8_t event_code, const BmsContext_t *ctx);
int bms_storage_read_last_event(BmsFaultSnapshot_t *out);
int bms_storage_read_event_slot(uint8_t slot_idx, BmsFaultSnapshot_t *out);

/**
 * @brief Select active non-volatile storage medium (EEPROM vs On-Chip Flash, FUN_0800f850)
 */
void bms_storage_set_medium(BmsStorageMedium_t medium);
BmsStorageMedium_t bms_storage_get_medium(void);

#ifdef __cplusplus
}
#endif

#endif /* BMS_STORAGE_H */

