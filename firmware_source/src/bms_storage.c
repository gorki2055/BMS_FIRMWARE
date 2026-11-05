/**
 * @file bms_storage.c
 * @brief BMS 24Cxx Non-Volatile EEPROM Storage & Parameter Calibration Manager
 *
 * Reconstructed from N32G45x BMS Firmware binary (0x08012000 - 0x08014000).
 */

#include "bms_storage.h"
#include <string.h>

#define SIMULATED_EEPROM_SIZE 4096
static uint8_t s_eeprom_storage[SIMULATED_EEPROM_SIZE];
static bool s_storage_initialized = false;

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

    s_storage_initialized = true;
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
