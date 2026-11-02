/**
 * @file dvc1124_afe.c
 * @brief Devechip DVC1124-1 21S Battery Analog Front-End Driver
 */

#include "dvc1124_afe.h"
#include "bms_hal.h"
#include <string.h>

/**
 * @brief Calculate CRC8 according to DVC1124 datasheet (poly 0x07, init 0x00)
 * Polynomial: x^8 + x^2 + x + 1 (0x07)
 */
uint8_t dvc1124_calc_crc8(const uint8_t *data, uint16_t len) {
    uint8_t crc = 0x00;
    for (uint16_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x07;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

bool dvc1124_init(void) {
    /* Initialize DVC1124 internal registers */
    uint8_t ctrl_val = 0x00;
    return bms_hal_i2c_write(DVC1124_I2C_ADDR_WRITE, DVC_REG_MOS_CTRL, &ctrl_val, 1);
}

bool dvc1124_read_cell_voltages(uint16_t *cell_mv, uint8_t cell_count) {
    if (!cell_mv || cell_count > 24) return false;

    uint8_t raw_buf[48]; /* 2 bytes per cell */
    if (!bms_hal_i2c_read(DVC1124_I2C_ADDR_WRITE, DVC_REG_CELL1_V_HI, raw_buf, cell_count * 2)) {
        return false;
    }

    for (uint8_t i = 0; i < cell_count; i++) {
        /* Big-endian: High byte then Low byte */
        uint16_t val = ((uint16_t)raw_buf[i * 2] << 8) | raw_buf[i * 2 + 1];
        /* Scale: ADC counts to mV (1 count = ~1mV) */
        cell_mv[i] = val;
    }

    return true;
}

bool dvc1124_read_pack_current(int32_t *current_ma) {
    if (!current_ma) return false;

    uint8_t raw[2];
    if (!bms_hal_i2c_read(DVC1124_I2C_ADDR_WRITE, DVC_REG_CURRENT_HI, raw, 2)) {
        return false;
    }

    int16_t val = (int16_t)(((uint16_t)raw[0] << 8) | raw[1]);
    /* Shunt conversion factor */
    *current_ma = (int32_t)val * 10;
    return true;
}

bool dvc1124_read_temperatures(int16_t *temps_c, uint8_t count, int16_t *mos_temp) {
    if (!temps_c) return false;

    uint8_t raw[8];
    if (!bms_hal_i2c_read(DVC1124_I2C_ADDR_WRITE, DVC_REG_TEMP1_HI, raw, count * 2)) {
        return false;
    }

    for (uint8_t i = 0; i < count; i++) {
        int16_t adc = (int16_t)(((uint16_t)raw[i * 2] << 8) | raw[i * 2 + 1]);
        /* Rough conversion to Celsius with 40-deg positive offset */
        temps_c[i] = (adc / 10) - 40;
    }

    if (mos_temp) {
        *mos_temp = temps_c[0]; /* Channel 0 typically MOS thermistor */
    }

    return true;
}

bool dvc1124_set_balancing(uint32_t cell_mask) {
    uint8_t bal_bytes[3];
    bal_bytes[0] = (uint8_t)(cell_mask & 0xFF);          /* Cells 1..8 */
    bal_bytes[1] = (uint8_t)((cell_mask >> 8) & 0xFF);   /* Cells 9..16 */
    bal_bytes[2] = (uint8_t)((cell_mask >> 16) & 0x1F);  /* Cells 17..21 */

    return bms_hal_i2c_write(DVC1124_I2C_ADDR_WRITE, DVC_REG_BAL_CTRL1, bal_bytes, 3);
}

bool dvc1124_set_fet_output(bool chg_on, bool dsg_on) {
    uint8_t reg = 0;
    if (chg_on) reg |= DVC_MOS_CHG_EN;
    if (dsg_on) reg |= DVC_MOS_DSG_EN;

    return bms_hal_i2c_write(DVC1124_I2C_ADDR_WRITE, DVC_REG_MOS_CTRL, &reg, 1);
}
