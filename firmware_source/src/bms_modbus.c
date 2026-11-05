/**
 * @file bms_modbus.c
 * @brief BMS RS-485 / Modbus RTU & Diagnostic Communication Protocol
 *
 * Reconstructed from N32G45x BMS Firmware binary (0x08014000 - 0x08019000).
 */

#include "bms_modbus.h"
#include <string.h>

static uint8_t s_slave_id = BMS_MODBUS_DEFAULT_SLAVE_ID;
static uint32_t s_baud_rate = BMS_MODBUS_DEFAULT_BAUDRATE;

/**
 * @brief Modbus CRC16 Calculation (reconstructed from FUN_0800c754)
 * Standard Modbus polynomial 0xA001 with 0xFFFF initial seed.
 */
uint16_t bms_modbus_calc_crc16(const uint8_t *buffer, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < length; i++) {
        crc ^= buffer[i];
        for (uint8_t b = 0; b < 8; b++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/**
 * @brief Initialize Modbus RTU / RS-485 interface
 */
void bms_modbus_init(uint8_t slave_id, uint32_t baud_rate)
{
    s_slave_id = (slave_id > 0) ? slave_id : BMS_MODBUS_DEFAULT_SLAVE_ID;
    s_baud_rate = (baud_rate > 0) ? baud_rate : BMS_MODBUS_DEFAULT_BAUDRATE;
}

/**
 * @brief Read holding / input register internal helper
 */
static int read_register_value(uint16_t reg_addr, uint16_t *value, const BmsContext_t *ctx)
{
    if (value == NULL || ctx == NULL) {
        return -1;
    }

    /* 0x0001 - 0x0015: Individual Cell Voltages (mV) */
    if (reg_addr >= MODBUS_REG_CELL1_VOLTAGE && reg_addr <= MODBUS_REG_CELL21_VOLTAGE) {
        uint8_t cell_idx = (uint8_t)(reg_addr - MODBUS_REG_CELL1_VOLTAGE);
        if (cell_idx < BMS_SERIES_CELLS) {
            *value = ctx->telemetry.cell_mv[cell_idx];
            return 0;
        }
    }

    switch (reg_addr) {
        case MODBUS_REG_PACK_VOLTAGE:
            /* Pack voltage in 10mV resolution (e.g. 76600 mV -> 7660) */
            *value = (uint16_t)(ctx->telemetry.pack_voltage_mv / 10);
            return 0;

        case MODBUS_REG_PACK_CURRENT:
            /* Pack current in 10mA resolution (signed 16-bit) */
            *value = (uint16_t)((int16_t)(ctx->telemetry.current_ma / 10));
            return 0;

        case MODBUS_REG_SOC:
            /* SOC in 0.1% resolution (e.g. 50% -> 500) */
            *value = (uint16_t)(ctx->telemetry.soc_pct * 10);
            return 0;

        case MODBUS_REG_SOH:
            /* SOH in 0.1% resolution (e.g. 100% -> 1000) */
            *value = (uint16_t)(ctx->telemetry.soh_pct * 10);
            return 0;

        case MODBUS_REG_REMAINING_CAP:
            /* Remaining capacity in 0.1 Ah resolution (e.g. 35000 mAh -> 350) */
            *value = (uint16_t)(ctx->telemetry.remaining_mah / 100);
            return 0;

        case MODBUS_REG_NOMINAL_CAP:
            /* Nominal capacity in 0.1 Ah (70000 mAh -> 700) */
            *value = (uint16_t)(ctx->telemetry.total_capacity_mah / 100);
            return 0;

        case MODBUS_REG_CYCLE_COUNT:
            *value = ctx->telemetry.cycle_count;
            return 0;

        case MODBUS_REG_CELL_MAX_VOLT:
            *value = ctx->telemetry.max_cell_mv;
            return 0;

        case MODBUS_REG_CELL_MIN_VOLT:
            *value = ctx->telemetry.min_cell_mv;
            return 0;

        case MODBUS_REG_CELL_DELTA_VOLT:
            *value = ctx->telemetry.cell_delta_mv;
            return 0;

        case MODBUS_REG_TEMP_NTC1:
            *value = (uint16_t)((int16_t)(ctx->telemetry.temp_c[0] * 10));
            return 0;

        case MODBUS_REG_TEMP_NTC2:
            *value = (uint16_t)((int16_t)(ctx->telemetry.temp_c[1] * 10));
            return 0;

        case MODBUS_REG_TEMP_NTC3:
            *value = (uint16_t)((int16_t)(ctx->telemetry.temp_c[2] * 10));
            return 0;

        case MODBUS_REG_TEMP_NTC4:
            *value = (uint16_t)((int16_t)(ctx->telemetry.temp_c[3] * 10));
            return 0;

        case MODBUS_REG_TEMP_MOSFET:
            *value = (uint16_t)((int16_t)(ctx->telemetry.mos_temp_c * 10));
            return 0;

        case MODBUS_REG_TEMP_AMBIENT:
            /* Ambient estimated as average of NTC1 & NTC2 */
            *value = (uint16_t)((int16_t)((ctx->telemetry.temp_c[0] + ctx->telemetry.temp_c[1]) * 5));
            return 0;

        case MODBUS_REG_BMS_STATE:
            *value = (uint16_t)ctx->state;
            return 0;

        case MODBUS_REG_FAULT_FLAGS:
            *value = (uint16_t)ctx->faults.all;
            return 0;

        case MODBUS_REG_MOSFET_STATUS: {
            uint16_t mos_stat = 0;
            if (ctx->switches.chg_mos_on) mos_stat |= 0x0001;
            if (ctx->switches.dsg_mos_on) mos_stat |= 0x0002;
            *value = mos_stat;
            return 0;
        }

        case MODBUS_REG_OVP_THRESHOLD:
            *value = ctx->limits.cell_ovp_mv;
            return 0;

        case MODBUS_REG_UVP_THRESHOLD:
            *value = ctx->limits.cell_uvp_mv;
            return 0;

        case MODBUS_REG_OCP_CHG_THRESHOLD:
            *value = (uint16_t)(ctx->limits.chg_ocp_ma / 10);
            return 0;

        case MODBUS_REG_OCP_DSG_THRESHOLD:
            *value = (uint16_t)(ctx->limits.dsg_ocp_ma / 10);
            return 0;

        case MODBUS_REG_OTP_THRESHOLD:
            *value = (uint16_t)((int16_t)(ctx->limits.ot_protect_c * 10.0f));
            return 0;

        case MODBUS_REG_UTP_THRESHOLD:
            *value = (uint16_t)((int16_t)(ctx->limits.ut_protect_c * 10.0f));
            return 0;

        default:
            return -1; /* Illegal Data Address */
    }
}

/**
 * @brief Write holding register internal helper
 */
static int write_register_value(uint16_t reg_addr, uint16_t value, BmsContext_t *ctx)
{
    if (ctx == NULL) {
        return -1;
    }

    switch (reg_addr) {
        case MODBUS_REG_OVP_THRESHOLD:
            if (value >= 3500 && value <= 4400) {
                ctx->limits.cell_ovp_mv = value;
                return 0;
            }
            return -2; /* Illegal Value */

        case MODBUS_REG_UVP_THRESHOLD:
            if (value >= 2000 && value <= 3200) {
                ctx->limits.cell_uvp_mv = value;
                return 0;
            }
            return -2;

        case MODBUS_REG_OCP_CHG_THRESHOLD:
            ctx->limits.chg_ocp_ma = (int32_t)value * 10;
            return 0;

        case MODBUS_REG_OCP_DSG_THRESHOLD:
            ctx->limits.dsg_ocp_ma = (int32_t)value * 10;
            return 0;

        case MODBUS_REG_MOSFET_STATUS:
            /* Manual MOSFET override control */
            ctx->switches.chg_mos_on = (value & 0x0001) ? true : false;
            ctx->switches.dsg_mos_on = (value & 0x0002) ? true : false;
            return 0;

        default:
            return -1; /* Illegal Data Address */
    }
}

/**
 * @brief Build Modbus RTU exception response
 */
static int build_exception_response(uint8_t slave_id, uint8_t func_code,
                                    uint8_t exception_code, uint8_t *tx_buf)
{
    tx_buf[0] = slave_id;
    tx_buf[1] = func_code | 0x80;
    tx_buf[2] = exception_code;
    uint16_t crc = bms_modbus_calc_crc16(tx_buf, 3);
    tx_buf[3] = (uint8_t)(crc & 0xFF);
    tx_buf[4] = (uint8_t)((crc >> 8) & 0xFF);
    return 5;
}

/**
 * @brief Process an incoming Modbus RTU request frame
 */
int bms_modbus_process_frame(const uint8_t *rx_buf, uint16_t rx_len,
                             uint8_t *tx_buf, uint16_t tx_buf_size,
                             BmsContext_t *ctx)
{
    if (rx_buf == NULL || tx_buf == NULL || ctx == NULL || rx_len < 4) {
        return -1;
    }

    /* 1. Validate Slave Address (accept unit's ID or broadcast address 0) */
    uint8_t slave_id = rx_buf[0];
    if (slave_id != s_slave_id && slave_id != 0x00) {
        return 0; /* Not for this device, ignore silently */
    }

    /* 2. Validate Modbus CRC16 */
    uint16_t received_crc = (uint16_t)rx_buf[rx_len - 2] | ((uint16_t)rx_buf[rx_len - 1] << 8);
    uint16_t computed_crc = bms_modbus_calc_crc16(rx_buf, rx_len - 2);
    if (received_crc != computed_crc) {
        return -1; /* CRC Error */
    }

    uint8_t func_code = rx_buf[1];

    /* 3. Handle Function Code 0x03 & 0x04: Read Holding / Input Registers */
    if (func_code == MODBUS_FC_READ_HOLDING_REGS || func_code == MODBUS_FC_READ_INPUT_REGS) {
        if (rx_len < 8) {
            return -1;
        }

        uint16_t start_reg = ((uint16_t)rx_buf[2] << 8) | rx_buf[3];
        uint16_t reg_count = ((uint16_t)rx_buf[4] << 8) | rx_buf[5];

        if (reg_count < 1 || reg_count > 125) {
            return build_exception_response(slave_id, func_code,
                                            MODBUS_EX_ILLEGAL_DATA_VALUE, tx_buf);
        }

        uint16_t byte_count = reg_count * 2;
        if (3 + byte_count + 2 > tx_buf_size) {
            return -1; /* Buffer overflow */
        }

        tx_buf[0] = slave_id;
        tx_buf[1] = func_code;
        tx_buf[2] = (uint8_t)byte_count;

        for (uint16_t i = 0; i < reg_count; i++) {
            uint16_t reg_val = 0;
            if (read_register_value(start_reg + i, &reg_val, ctx) != 0) {
                return build_exception_response(slave_id, func_code,
                                                MODBUS_EX_ILLEGAL_DATA_ADDR, tx_buf);
            }
            tx_buf[3 + (i * 2)]     = (uint8_t)((reg_val >> 8) & 0xFF);
            tx_buf[3 + (i * 2) + 1] = (uint8_t)(reg_val & 0xFF);
        }

        uint16_t resp_len = 3 + byte_count;
        uint16_t crc = bms_modbus_calc_crc16(tx_buf, resp_len);
        tx_buf[resp_len]     = (uint8_t)(crc & 0xFF);
        tx_buf[resp_len + 1] = (uint8_t)((crc >> 8) & 0xFF);
        return resp_len + 2;
    }

    /* 4. Handle Function Code 0x06: Write Single Register */
    if (func_code == MODBUS_FC_WRITE_SINGLE_REG) {
        if (rx_len < 8) {
            return -1;
        }

        uint16_t reg_addr = ((uint16_t)rx_buf[2] << 8) | rx_buf[3];
        uint16_t reg_val  = ((uint16_t)rx_buf[4] << 8) | rx_buf[5];

        int res = write_register_value(reg_addr, reg_val, ctx);
        if (res == -1) {
            return build_exception_response(slave_id, func_code,
                                            MODBUS_EX_ILLEGAL_DATA_ADDR, tx_buf);
        } else if (res == -2) {
            return build_exception_response(slave_id, func_code,
                                            MODBUS_EX_ILLEGAL_DATA_VALUE, tx_buf);
        }

        /* Echo request back as standard Modbus write confirmation */
        memcpy(tx_buf, rx_buf, 6);
        uint16_t crc = bms_modbus_calc_crc16(tx_buf, 6);
        tx_buf[6] = (uint8_t)(crc & 0xFF);
        tx_buf[7] = (uint8_t)((crc >> 8) & 0xFF);
        return 8;
    }

    /* Unsupported function code */
    return build_exception_response(slave_id, func_code,
                                    MODBUS_EX_ILLEGAL_FUNCTION, tx_buf);
}

/**
 * @brief Process proprietary PC upper-computer diagnostic frame (0xEA / 0xEB)
 * Reconstructed from FUN_0801cd98 / FUN_0801e174.
 */
int bms_host_proto_process_frame(const uint8_t *rx_buf, uint16_t rx_len,
                                 uint8_t *tx_buf, uint16_t tx_buf_size,
                                 const BmsContext_t *ctx)
{
    if (rx_buf == NULL || tx_buf == NULL || ctx == NULL || rx_len < 4) {
        return -1;
    }

    /* Check Header 0xEA 0xD1 or 0xEB 0x01 */
    if (rx_buf[0] != BMS_HOST_FRAME_HEADER_EA && rx_buf[0] != BMS_HOST_FRAME_HEADER_EB) {
        return 0; /* Not a proprietary diagnostic frame */
    }

    /* Telemetry Polling Frame (Header 0xEA, Command 0xD1, Subcmd 0x03) */
    if (rx_buf[0] == BMS_HOST_FRAME_HEADER_EA && rx_buf[1] == BMS_HOST_FRAME_CMD_TELEMETRY) {
        if (tx_buf_size < 58) {
            return -1;
        }

        tx_buf[0] = BMS_HOST_FRAME_HEADER_EA;
        tx_buf[1] = BMS_HOST_FRAME_CMD_TELEMETRY;
        tx_buf[2] = s_slave_id;
        tx_buf[3] = 0x39; /* Frame length 57 bytes */
        tx_buf[4] = 0xFF;
        tx_buf[5] = 0x03;

        /* Field 2: State */
        tx_buf[6]  = 0x02;
        tx_buf[7]  = 0x00;
        tx_buf[8]  = (uint8_t)ctx->state;

        /* Field 3: Pack Current (signed, 10mA) */
        int32_t curr_10ma = ctx->telemetry.current_ma / 10;
        tx_buf[9]  = 0x03;
        tx_buf[10] = (uint8_t)((curr_10ma >> 8) & 0xFF);
        tx_buf[11] = (uint8_t)(curr_10ma & 0xFF);

        /* Field 5: Pack Voltage (10mV) */
        uint32_t volt_10mv = ctx->telemetry.pack_voltage_mv / 10;
        tx_buf[12] = 0x05;
        tx_buf[13] = (uint8_t)((volt_10mv >> 8) & 0xFF);
        tx_buf[14] = (uint8_t)(volt_10mv & 0xFF);

        /* Field 7: SOC */
        tx_buf[15] = 0x07;
        tx_buf[16] = ctx->telemetry.soc_pct;

        /* Field 8: SOH */
        tx_buf[17] = 0x08;
        tx_buf[18] = ctx->telemetry.soh_pct;

        /* Field 9: Max Cell Voltage */
        tx_buf[19] = 0x09;
        tx_buf[20] = (uint8_t)((ctx->telemetry.max_cell_mv >> 8) & 0xFF);
        tx_buf[21] = (uint8_t)(ctx->telemetry.max_cell_mv & 0xFF);

        /* Field 10: Min Cell Voltage */
        tx_buf[22] = 0x0A;
        tx_buf[23] = (uint8_t)((ctx->telemetry.min_cell_mv >> 8) & 0xFF);
        tx_buf[24] = (uint8_t)(ctx->telemetry.min_cell_mv & 0xFF);

        /* Field 11: Imbalance Delta */
        uint16_t delta = (ctx->telemetry.max_cell_mv >= ctx->telemetry.min_cell_mv) ?
                         (ctx->telemetry.max_cell_mv - ctx->telemetry.min_cell_mv) : 0;
        tx_buf[25] = 0x0B;
        tx_buf[26] = (uint8_t)((delta >> 8) & 0xFF);
        tx_buf[27] = (uint8_t)(delta & 0xFF);

        /* Field 12: Temperatures (T1..T4, MOS, AMB) */
        tx_buf[28] = 0x0C;
        tx_buf[29] = (uint8_t)((int8_t)ctx->telemetry.temp_c[0] + 40);
        tx_buf[30] = (uint8_t)((int8_t)ctx->telemetry.temp_c[1] + 40);
        tx_buf[31] = (uint8_t)((int8_t)ctx->telemetry.temp_c[2] + 40);
        tx_buf[32] = (uint8_t)((int8_t)ctx->telemetry.temp_c[3] + 40);
        tx_buf[33] = (uint8_t)((int8_t)ctx->telemetry.mos_temp_c + 40);
        tx_buf[34] = (uint8_t)((int8_t)((ctx->telemetry.temp_c[0] + ctx->telemetry.temp_c[1]) / 2) + 40);

        /* XOR Checksum over bytes 3..56 (FUN_0800c0d0) */
        uint8_t xor_sum = 0;
        for (uint16_t i = 3; i < 57; i++) {
            xor_sum ^= tx_buf[i];
        }
        tx_buf[57] = xor_sum;
        return 58;
    }

    return 0;
}
