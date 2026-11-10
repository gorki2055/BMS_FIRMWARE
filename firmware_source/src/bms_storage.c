/**
 * @file bms_storage.c
 * @brief BMS 24Cxx Non-Volatile EEPROM Storage & Parameter Calibration Manager
 *
 * Reconstructed from N32G45x BMS Firmware binary (0x08012000 - 0x08014000).
 */

#include "bms_storage.h"
#include "bms_hal.h"
#include <string.h>

#define SIMULATED_EEPROM_SIZE 4096
static uint8_t s_eeprom_storage[SIMULATED_EEPROM_SIZE];
static bool s_storage_initialized = false;
static BmsStorageMedium_t s_storage_medium = BMS_STORAGE_MEDIUM_EEPROM;
static uint8_t s_fault_log_write_idx = 0;
static const uint16_t k_fault_log_addrs[BMS_FAULT_LOG_SLOTS] = {
    EEPROM_ADDR_FAULT_LOG_1,
    EEPROM_ADDR_FAULT_LOG_2,
    EEPROM_ADDR_FAULT_LOG_3
};

void bms_storage_set_medium(BmsStorageMedium_t medium)
{
    s_storage_medium = medium;
}

BmsStorageMedium_t bms_storage_get_medium(void)
{
    return s_storage_medium;
}

/**
 * @brief Calculate block 8-bit checksum (reconstructed from FUN_0800ba48)
 * Sum of all bytes modulo 256.
 */
uint8_t bms_storage_calc_checksum(const uint8_t *data, uint16_t len)
{
    if (data == NULL || len == 0) {
        return 0;
    }
    uint32_t sum = 0;
    for (uint16_t i = 0; i < len; i++) {
        sum += data[i];
    }
    return (uint8_t)(sum & 0xFF);
}

/**
 * @brief Initialize Non-Volatile Storage Manager with default values
 */
void bms_storage_init(void)
{
    if (s_storage_initialized) {
        return;
    }

    memset(s_eeprom_storage, 0xFF, sizeof(s_eeprom_storage));

    /* Initialize Cell Count = 21 */
    s_eeprom_storage[EEPROM_ADDR_CELL_COUNT] = 21;

    /* Initialize Battery Rating: 70Ah nominal, 76.6V nominal */
    uint16_t nominal_cap_0_1ah = 700; /* 70.0 Ah */
    uint16_t nominal_volt_0_1v = 766; /* 76.6 V */
    s_eeprom_storage[EEPROM_ADDR_BATTERY_RATING + 0] = (uint8_t)(nominal_cap_0_1ah & 0xFF);
    s_eeprom_storage[EEPROM_ADDR_BATTERY_RATING + 1] = (uint8_t)((nominal_cap_0_1ah >> 8) & 0xFF);
    s_eeprom_storage[EEPROM_ADDR_BATTERY_RATING + 2] = (uint8_t)(nominal_volt_0_1v & 0xFF);
    s_eeprom_storage[EEPROM_ADDR_BATTERY_RATING + 3] = (uint8_t)((nominal_volt_0_1v >> 8) & 0xFF);
    s_eeprom_storage[EEPROM_ADDR_CHECKSUM_RATING] =
        bms_storage_calc_checksum(&s_eeprom_storage[EEPROM_ADDR_BATTERY_RATING], EEPROM_LEN_BATTERY_RATING);

    /* Initialize Default Serial Number: "SPB24-DVC24-006-1010-A30" */
    const char *default_sn = "SPB24-DVC24-006-1010-A30";
    strncpy((char *)&s_eeprom_storage[EEPROM_ADDR_SERIAL_NUMBER], default_sn, 32);
    s_eeprom_storage[EEPROM_ADDR_CHECKSUM_SERIAL] =
        bms_storage_calc_checksum(&s_eeprom_storage[EEPROM_ADDR_SERIAL_NUMBER], 32);

    /* Initialize Default System Configuration (Protection Limits) */
    uint8_t config_buf[EEPROM_LEN_SYS_CONFIG] = {0};
    /* OVP = 4185 mV */
    config_buf[0] = (uint8_t)(4185 & 0xFF);
    config_buf[1] = (uint8_t)((4185 >> 8) & 0xFF);
    /* UVP = 2621 mV */
    config_buf[2] = (uint8_t)(2621 & 0xFF);
    config_buf[3] = (uint8_t)((2621 >> 8) & 0xFF);
    /* CHG OCP = 4000 (40.0A) */
    config_buf[4] = (uint8_t)(4000 & 0xFF);
    config_buf[5] = (uint8_t)((4000 >> 8) & 0xFF);
    /* DSG OCP = 10000 (100.0A) */
    config_buf[6] = (uint8_t)(10000 & 0xFF);
    config_buf[7] = (uint8_t)((10000 >> 8) & 0xFF);
    /* OT Protect = 65 C */
    config_buf[8] = 65;
    /* UT Protect = -10 C */
    config_buf[9] = (uint8_t)(-10);

    memcpy(&s_eeprom_storage[EEPROM_ADDR_SYS_CONFIG], config_buf, EEPROM_LEN_SYS_CONFIG);
    s_eeprom_storage[EEPROM_ADDR_CHECKSUM_CONFIG] =
        bms_storage_calc_checksum(config_buf, EEPROM_LEN_SYS_CONFIG);

    /* Initialize Lifetime Counters to Zero */
    uint32_t zero32 = 0;
    memcpy(&s_eeprom_storage[EEPROM_ADDR_LIFETIME_DSG_AH], &zero32, 4);
    memcpy(&s_eeprom_storage[EEPROM_ADDR_LIFETIME_CHG_AH], &zero32, 4);
    memcpy(&s_eeprom_storage[EEPROM_ADDR_CYCLE_COUNT], &zero32, 4);
    memcpy(&s_eeprom_storage[EEPROM_ADDR_OPERATING_HOURS], &zero32, 4);

    /* Initialize Default Per-Cell Calibration Multipliers (10000 = 1.0000f) at 0x0060..0x0089 */
    for (uint8_t c = 0; c < BMS_SERIES_CELLS; c++) {
        uint16_t unity_cal = 10000U;
        s_eeprom_storage[EEPROM_ADDR_CELL_CAL_1_16 + (c * 2U)]      = (uint8_t)(unity_cal & 0xFFU);
        s_eeprom_storage[EEPROM_ADDR_CELL_CAL_1_16 + (c * 2U) + 1U] = (uint8_t)((unity_cal >> 8) & 0xFFU);
    }

    s_storage_initialized = true;

    /* Compute and write initial MCU 96-bit UID lock word at EEPROM 0x0100 */
    (void)bms_storage_write_uid_lock();
}

/**
 * @brief Read arbitrary block from EEPROM (reconstructed from FUN_08012330)
 */
int bms_storage_read_block(uint16_t addr, uint8_t *dest, uint16_t len)
{
    if (dest == NULL || len == 0) {
        return -1;
    }
    if ((uint32_t)addr + len > SIMULATED_EEPROM_SIZE) {
        return -2; /* Out of bounds */
    }

    bms_storage_init();
    if (s_storage_medium == BMS_STORAGE_MEDIUM_FLASH) {
        return bms_hal_flash_read(addr, dest, len) ? 0 : -3;
    }
    memcpy(dest, &s_eeprom_storage[addr], len);
    return 0;
}

/**
 * @brief Write page to EEPROM with 5-retry read-back verification (reconstructed from FUN_080127e0)
 *
 * Implements exact page boundary splitting:
 *   bytes_in_page = ((addr >> 5) + 1) * 32 - addr
 * and verifies that readback data matches source byte-for-byte.
 */
int bms_storage_write_verified(uint16_t addr, const uint8_t *src, uint16_t len)
{
    if (src == NULL || len == 0) {
        return -1;
    }
    if ((uint32_t)addr + len > SIMULATED_EEPROM_SIZE) {
        return -2;
    }

    bms_storage_init();

    if (s_storage_medium == BMS_STORAGE_MEDIUM_FLASH) {
        return bms_hal_flash_write(addr, src, len) ? 0 : -3;
    }

    uint16_t bytes_written = 0;
    while (bytes_written < len) {
        uint16_t curr_addr = addr + bytes_written;
        /* Calculate remaining space in the current 32-byte physical page */
        uint16_t page_boundary_remaining = (uint16_t)(((curr_addr >> 5) + 1) * EEPROM_PAGE_SIZE - curr_addr);
        uint16_t chunk_len = len - bytes_written;
        if (chunk_len > page_boundary_remaining) {
            chunk_len = page_boundary_remaining;
        }

        /* 5-retry loop from decompiled FUN_080127e0 */
        bool verified = false;
        for (uint8_t retry = 0; retry < EEPROM_MAX_RETRIES; retry++) {
            /* Physical write emulation */
            memcpy(&s_eeprom_storage[curr_addr], &src[bytes_written], chunk_len);

            /* Immediate read-back verification */
            uint8_t readback_buf[EEPROM_PAGE_SIZE];
            memcpy(readback_buf, &s_eeprom_storage[curr_addr], chunk_len);

            if (memcmp(&src[bytes_written], readback_buf, chunk_len) == 0) {
                verified = true;
                break;
            }
        }

        if (!verified) {
            return -3; /* Verification failed after 5 retries */
        }

        bytes_written += chunk_len;
    }

    return 0;
}

/**
 * @brief Load saved protection limits & parameters into BMS context
 */
int bms_storage_load_config(BmsContext_t *ctx)
{
    if (ctx == NULL) {
        return -1;
    }

    bms_storage_init();

    /* Read System Config Block */
    uint8_t config_buf[EEPROM_LEN_SYS_CONFIG];
    if (bms_storage_read_block(EEPROM_ADDR_SYS_CONFIG, config_buf, EEPROM_LEN_SYS_CONFIG) != 0) {
        return -1;
    }

    /* Verify Checksum against stored value at 0x015F */
    uint8_t stored_chk = 0;
    bms_storage_read_block(EEPROM_ADDR_CHECKSUM_CONFIG, &stored_chk, 1);
    uint8_t calc_chk = bms_storage_calc_checksum(config_buf, EEPROM_LEN_SYS_CONFIG);

    if (stored_chk != calc_chk) {
        /* Checksum invalid - fall back to defaults */
        return -2;
    }

    /* Unpack limits */
    ctx->limits.cell_ovp_mv   = (uint16_t)config_buf[0] | ((uint16_t)config_buf[1] << 8);
    ctx->limits.cell_uvp_mv   = (uint16_t)config_buf[2] | ((uint16_t)config_buf[3] << 8);
    ctx->limits.chg_ocp_ma    = ((int32_t)((uint16_t)config_buf[4] | ((uint16_t)config_buf[5] << 8))) * 10;
    ctx->limits.dsg_ocp_ma    = ((int32_t)((uint16_t)config_buf[6] | ((uint16_t)config_buf[7] << 8))) * 10;
    ctx->limits.ot_protect_c  = (float)((int8_t)config_buf[8]);
    ctx->limits.ut_protect_c  = (float)((int8_t)config_buf[9]);

    return 0;
}

/**
 * @brief Save current protection limits & parameters to EEPROM with verified checksum
 */
int bms_storage_save_config(const BmsContext_t *ctx)
{
    if (ctx == NULL) {
        return -1;
    }

    uint8_t config_buf[EEPROM_LEN_SYS_CONFIG] = {0};
    config_buf[0] = (uint8_t)(ctx->limits.cell_ovp_mv & 0xFF);
    config_buf[1] = (uint8_t)((ctx->limits.cell_ovp_mv >> 8) & 0xFF);
    config_buf[2] = (uint8_t)(ctx->limits.cell_uvp_mv & 0xFF);
    config_buf[3] = (uint8_t)((ctx->limits.cell_uvp_mv >> 8) & 0xFF);

    uint16_t chg_ocp_10ma = (uint16_t)(ctx->limits.chg_ocp_ma / 10);
    config_buf[4] = (uint8_t)(chg_ocp_10ma & 0xFF);
    config_buf[5] = (uint8_t)((chg_ocp_10ma >> 8) & 0xFF);

    uint16_t dsg_ocp_10ma = (uint16_t)(ctx->limits.dsg_ocp_ma / 10);
    config_buf[6] = (uint8_t)(dsg_ocp_10ma & 0xFF);
    config_buf[7] = (uint8_t)((dsg_ocp_10ma >> 8) & 0xFF);

    config_buf[8] = (uint8_t)((int8_t)ctx->limits.ot_protect_c);
    config_buf[9] = (uint8_t)((int8_t)ctx->limits.ut_protect_c);

    /* Write configuration block with 5-retry page verification */
    if (bms_storage_write_verified(EEPROM_ADDR_SYS_CONFIG, config_buf, EEPROM_LEN_SYS_CONFIG) != 0) {
        return -2;
    }

    /* Compute and write checksum byte */
    uint8_t chk = bms_storage_calc_checksum(config_buf, EEPROM_LEN_SYS_CONFIG);
    if (bms_storage_write_verified(EEPROM_ADDR_CHECKSUM_CONFIG, &chk, 1) != 0) {
        return -3;
    }

    return 0;
}

/**
 * @brief Update lifetime cycle count and cumulative Ah in EEPROM
 */
int bms_storage_update_lifetime(uint32_t cycle_count, uint32_t dsg_ah, uint32_t chg_ah)
{
    uint8_t buf[12];
    memcpy(&buf[0], &dsg_ah, 4);
    memcpy(&buf[4], &chg_ah, 4);
    memcpy(&buf[8], &cycle_count, 4);

    return bms_storage_write_verified(EEPROM_ADDR_LIFETIME_DSG_AH, buf, 12);
}

/**
 * @brief Read lifetime cycle count and cumulative Ah from EEPROM
 */
int bms_storage_read_lifetime(uint32_t *cycle_count, uint32_t *dsg_ah, uint32_t *chg_ah)
{
    uint8_t buf[12];
    if (bms_storage_read_block(EEPROM_ADDR_LIFETIME_DSG_AH, buf, 12) != 0) {
        return -1;
    }

    if (dsg_ah)      memcpy(dsg_ah, &buf[0], 4);
    if (chg_ah)      memcpy(chg_ah, &buf[4], 4);
    if (cycle_count) memcpy(cycle_count, &buf[8], 4);

    return 0;
}

/**
 * @brief Compute 16-bit hardware-bound checksum across EEPROM cell calibration + 96-bit MCU UID
 * @note Reconstructed from FUN_08017b04 / FUN_08017b3c (Flash 0x08017B04)
 */
uint16_t bms_storage_calc_uid_lock_crc(const uint8_t *cal_bytes, uint16_t cal_len, const uint8_t uid[12])
{
    uint16_t hash = 0x5A5AU;
    if (cal_bytes) {
        for (uint16_t i = 0; i < cal_len; i++) {
            hash = (uint16_t)((hash << 5) + hash + cal_bytes[i]);
        }
    }
    if (uid) {
        for (uint8_t j = 0; j < 12U; j++) {
            hash = (uint16_t)((hash << 5) + hash + uid[j]);
        }
    }
    return hash;
}

/**
 * @brief Write hardware-bound UID + calibration lock word to EEPROM 0x0100 (FUN_08017b3c)
 */
int bms_storage_write_uid_lock(void)
{
    bms_storage_init();
    uint8_t cal_bytes[EEPROM_LEN_CELL_CAL_TOTAL];
    uint8_t uid[12];

    if (bms_storage_read_block(EEPROM_ADDR_CELL_CAL_1_16, cal_bytes, EEPROM_LEN_CELL_CAL_TOTAL) != 0) {
        return -1;
    }
    bms_hal_read_mcu_uid(uid);

    uint16_t lock_word = bms_storage_calc_uid_lock_crc(cal_bytes, EEPROM_LEN_CELL_CAL_TOTAL, uid);
    uint8_t lock_buf[2] = { (uint8_t)(lock_word & 0xFFU), (uint8_t)((lock_word >> 8) & 0xFFU) };
    return bms_storage_write_verified(EEPROM_ADDR_UID_LOCK, lock_buf, 2);
}

/**
 * @brief Verify EEPROM 0x0100 lock word against current MCU 96-bit UID & calibration table (FUN_08017b3c)
 */
bool bms_storage_verify_uid_lock(BmsContext_t *ctx)
{
    bms_storage_init();
    uint8_t cal_bytes[EEPROM_LEN_CELL_CAL_TOTAL];
    uint8_t uid[12];
    uint8_t lock_buf[2] = {0};

    if (bms_storage_read_block(EEPROM_ADDR_CELL_CAL_1_16, cal_bytes, EEPROM_LEN_CELL_CAL_TOTAL) != 0) {
        if (ctx) ctx->calibration_authorized = false;
        return false;
    }
    if (bms_storage_read_block(EEPROM_ADDR_UID_LOCK, lock_buf, 2) != 0) {
        if (ctx) ctx->calibration_authorized = false;
        return false;
    }

    bms_hal_read_mcu_uid(uid);
    uint16_t expected = bms_storage_calc_uid_lock_crc(cal_bytes, EEPROM_LEN_CELL_CAL_TOTAL, uid);
    uint16_t stored   = (uint16_t)lock_buf[0] | ((uint16_t)lock_buf[1] << 8);
    bool match = (expected == stored);

    if (ctx) {
        ctx->calibration_authorized = match;
    }
    return match;
}

/**
 * @brief Save per-cell 16-bit calibration multipliers to EEPROM 0x0060 and re-lock UID (FUN_08016000)
 */
int bms_storage_save_cell_cal(const uint16_t gain_milli[BMS_SERIES_CELLS])
{
    if (!gain_milli) return -1;
    uint8_t raw[EEPROM_LEN_CELL_CAL_TOTAL];
    for (uint8_t i = 0; i < BMS_SERIES_CELLS; i++) {
        raw[i * 2U]      = (uint8_t)(gain_milli[i] & 0xFFU);
        raw[i * 2U + 1U] = (uint8_t)((gain_milli[i] >> 8) & 0xFFU);
    }
    int res = bms_storage_write_verified(EEPROM_ADDR_CELL_CAL_1_16, raw, EEPROM_LEN_CELL_CAL_TOTAL);
    if (res == 0) {
        res = bms_storage_write_uid_lock();
    }
    return res;
}

/**
 * @brief Load per-cell voltage gain multipliers from EEPROM 0x0060 (FUN_08016000)
 * @note Divides each 16-bit word by 10000.0f; clamps out-of-range values (<0.80f or >1.20f) to 1.0f.
 */
int bms_storage_load_cell_cal(float gain_out[BMS_SERIES_CELLS])
{
    if (!gain_out) return -1;
    uint8_t raw[EEPROM_LEN_CELL_CAL_TOTAL];
    if (bms_storage_read_block(EEPROM_ADDR_CELL_CAL_1_16, raw, EEPROM_LEN_CELL_CAL_TOTAL) != 0) {
        for (uint8_t i = 0; i < BMS_SERIES_CELLS; i++) gain_out[i] = 1.0f;
        return -1;
    }

    for (uint8_t i = 0; i < BMS_SERIES_CELLS; i++) {
        uint16_t word = (uint16_t)raw[i * 2U] | ((uint16_t)raw[i * 2U + 1U] << 8);
        float g = (float)word / BMS_CELL_CAL_REF_DIVISOR;
        if (g < 0.80f || g > 1.20f) {
            g = 1.0f; /* Fallback to 1.0f (0x3F800000) per FUN_08016000 */
        }
        gain_out[i] = g;
    }
    return 0;
}

/**
 * @brief Write 4-byte bootloader IAP upgrade flag at on-chip Flash offset 0x28A (FUN_0800f850)
 */
int bms_storage_write_boot_iap_flag(uint32_t magic)
{
    uint8_t buf[4] = {
        (uint8_t)(magic & 0xFFU),
        (uint8_t)((magic >> 8) & 0xFFU),
        (uint8_t)((magic >> 16) & 0xFFU),
        (uint8_t)((magic >> 24) & 0xFFU)
    };
    return bms_hal_flash_write(BMS_FLASH_BOOT_IAP_OFFSET, buf, 4U) ? 0 : -1;
}

/**
 * @brief Read 4-byte bootloader IAP upgrade flag from on-chip Flash offset 0x28A
 */
int bms_storage_read_boot_iap_flag(uint32_t *magic_out)
{
    if (!magic_out) return -1;
    uint8_t buf[4] = {0};
    if (!bms_hal_flash_read(BMS_FLASH_BOOT_IAP_OFFSET, buf, 4U)) return -1;
    *magic_out = (uint32_t)buf[0] | ((uint32_t)buf[1] << 8) |
                 ((uint32_t)buf[2] << 16) | ((uint32_t)buf[3] << 24);
    return 0;
}

/**
 * @brief Record black-box fault/event snapshot at EEPROM 0x01A8..0x01E0 (FUN_08019844)
 * @note Rotates across the 3 historical fault log slots (0x01A8, 0x01C0, 0x01E0) and mirrors the latest to slot 0.
 */
int bms_storage_log_event(uint8_t event_code, const BmsContext_t *ctx)
{
    if (!ctx) return -1;
    BmsFaultSnapshot_t snap;
    memset(&snap, 0, sizeof(snap));

    snap.event_code      = event_code;
    snap.soc_pct         = ctx->telemetry.soc_pct;
    snap.min_cell_mv     = ctx->telemetry.min_cell_mv;
    snap.max_cell_mv     = ctx->telemetry.max_cell_mv;
    snap.max_temp_c      = ctx->telemetry.max_temp_c;
    snap.uptime_sec      = ctx->uptime_seconds;
    snap.pack_voltage_mv = ctx->telemetry.pack_voltage_mv;
    snap.current_ma      = ctx->telemetry.current_ma;
    snap.fault_flags     = ctx->faults.all;

    uint16_t slot_addr = k_fault_log_addrs[s_fault_log_write_idx % BMS_FAULT_LOG_SLOTS];
    s_fault_log_write_idx = (uint8_t)((s_fault_log_write_idx + 1U) % BMS_FAULT_LOG_SLOTS);

    int res = bms_storage_write_verified(slot_addr, (const uint8_t *)&snap, sizeof(BmsFaultSnapshot_t));
    if (slot_addr != EEPROM_ADDR_FAULT_LOG_1) {
        (void)bms_storage_write_verified(EEPROM_ADDR_FAULT_LOG_1, (const uint8_t *)&snap, sizeof(BmsFaultSnapshot_t));
    }
    return res;
}

/**
 * @brief Retrieve most recent black-box fault/event snapshot from EEPROM 0x01A8
 */
int bms_storage_read_last_event(BmsFaultSnapshot_t *out)
{
    if (!out) return -1;
    return bms_storage_read_block(EEPROM_ADDR_FAULT_LOG_1, (uint8_t *)out, sizeof(BmsFaultSnapshot_t));
}

/**
 * @brief Retrieve black-box fault/event snapshot from specific historical slot (0..2)
 */
int bms_storage_read_event_slot(uint8_t slot_idx, BmsFaultSnapshot_t *out)
{
    if (!out || slot_idx >= BMS_FAULT_LOG_SLOTS) return -1;
    return bms_storage_read_block(k_fault_log_addrs[slot_idx], (uint8_t *)out, sizeof(BmsFaultSnapshot_t));
}


