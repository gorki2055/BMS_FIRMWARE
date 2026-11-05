/**
 * @file bms_can.c
 * @brief CAN Communication Protocol Engine (250 kbps, 29-bit Extended IDs)
 */

#include "bms_can.h"
#include "bms_hal.h"
#include <string.h>

static uint8_t s_own_sid = BMS_CAN_MASTER_SID;

/**
 * @brief Standard Modbus CRC16 implementation from BMS documentation
 */
uint16_t bms_crc16_modbus(const uint8_t *buf, uint16_t len) {
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < len; i++) {
        crc ^= buf[i];
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void bms_can_init(uint8_t own_sid) {
    s_own_sid = own_sid;
}

void bms_can_transmit(const CanMessage_t *msg) {
    if (!msg) return;
    bms_hal_can_transmit(msg->id, msg->data, msg->dlc);
}

void bms_can_send_status(const BmsContext_t *ctx) {
    CanMessage_t msg;
    /* ID: Priority 6, SID = own_sid, DID = VCU (0x00), CMD = 0x14, IDX = 0x10 */
    msg.id = BMS_CAN_BUILD_ID(6, s_own_sid, 0x00, CAN_CMD_TELEMETRY, CAN_IDX_TEL_MOS_STATUS);
    msg.dlc = 7;

    msg.data[0] = ctx->switches.din_active ? 1 : 0;        /* Discharge line connected */
    msg.data[1] = 1;                                       /* Address line access */
    msg.data[2] = ctx->switches.cin_active ? 1 : 0;        /* Charger connected */
    msg.data[3] = ctx->switches.din_active ? 1 : 0;        /* Load connected */
    msg.data[4] = ctx->switches.dsg_mos_on ? 1 : 0;        /* DSG MOS state */
    msg.data[5] = ctx->switches.chg_mos_on ? 1 : 0;        /* CHG MOS state */
    msg.data[6] = ctx->switches.acc_wake_active ? 1 : 0;   /* Key line (ACC) access */

    bms_can_transmit(&msg);
}

/**
 * @brief Transmit Dynamic Capacity, SOC, and SOH Frame
 * @note Reconstructed directly from FUN_0801b55c (Flash 0x0801B55C, CMD 0x40 Index 0x01):
 *       - D0, D1: Total Full Charge Capacity (FCC) in 10 mAh units (Little-Endian)
 *       - D2, D3: Remaining Capacity in 10 mAh units (Little-Endian)
 *       - D4:     Relative SOC percentage (0 - 100%)
 *       - D5:     State of Health (SOH) / Absolute Capacity percentage (0 - 100%)
 *       - D6:     Status flags
 */
void bms_can_send_capacity_soh(const BmsContext_t *ctx) {
    const BmsTelemetry_t *t = &ctx->telemetry;
    CanMessage_t msg;

    /* ID: Priority 6, SID = own_sid, DID = VCU (0x00), CMD = 0x40, IDX = 0x01 */
    msg.id = BMS_CAN_BUILD_ID(6, s_own_sid, 0x00, CAN_CMD_PACK_CONFIG, CAN_IDX_CFG_CAPACITY_SOH);
    msg.dlc = 7;

    uint16_t fcc_10mah = (uint16_t)(t->total_capacity_mah / 10);
    uint16_t rem_10mah = (uint16_t)(t->remaining_mah / 10);

    msg.data[0] = (uint8_t)(fcc_10mah & 0xFF);
    msg.data[1] = (uint8_t)((fcc_10mah >> 8) & 0xFF);
    msg.data[2] = (uint8_t)(rem_10mah & 0xFF);
    msg.data[3] = (uint8_t)((rem_10mah >> 8) & 0xFF);
    msg.data[4] = t->soc_pct;
    msg.data[5] = t->soh_pct;
    msg.data[6] = 0;

    bms_can_transmit(&msg);
}

void bms_can_send_cell_voltages(const BmsContext_t *ctx) {
    const BmsTelemetry_t *t = &ctx->telemetry;

    /* Frames 0x41 Index 0x03 to 0x08 (4 cells per frame) */
    for (uint8_t frame = 0; frame < 6; frame++) {
        CanMessage_t msg;
        uint8_t idx = 0x03 + frame;
        msg.id = BMS_CAN_BUILD_ID(6, s_own_sid, 0x00, CAN_CMD_CELL_VOLTAGES, idx);
        msg.dlc = 8;
        memset(msg.data, 0, 8);

        for (uint8_t c = 0; c < 4; c++) {
            uint8_t cell_num = frame * 4 + c;
            if (cell_num < BMS_SERIES_CELLS) {
                uint16_t v = t->cell_mv[cell_num];
                msg.data[c * 2]     = (uint8_t)((v >> 8) & 0xFF);
                msg.data[c * 2 + 1] = (uint8_t)(v & 0xFF);
            }
        }
        bms_can_transmit(&msg);
    }
}

void bms_can_send_temperatures(const BmsContext_t *ctx) {
    const BmsTelemetry_t *t = &ctx->telemetry;
    CanMessage_t msg;
    msg.id = BMS_CAN_BUILD_ID(6, s_own_sid, 0x00, CAN_CMD_TELEMETRY, CAN_IDX_TEL_TEMPS);
    msg.dlc = 7;

    msg.data[0] = BMS_NTC_TEMP_SENSORS;
    for (uint8_t i = 0; i < 4; i++) {
        msg.data[1 + i] = (uint8_t)(t->temp_c[i] + 40); /* +40 deg offset */
    }
    msg.data[5] = (uint8_t)(t->mos_temp_c + 40);
    msg.data[6] = 40; /* Connector temp */

    bms_can_transmit(&msg);
}

void bms_can_process_rx(const CanMessage_t *msg, BmsContext_t *ctx) {
    if (!msg || !ctx) return;

    uint8_t did = BMS_CAN_EXTRACT_DID(msg->id);
    /* Only process messages addressed to this BMS */
    if (did != s_own_sid && did != 0x1F /* broadcast */) return;

    uint8_t cmd = BMS_CAN_EXTRACT_CMD(msg->id);
    uint8_t idx = BMS_CAN_EXTRACT_IDX(msg->id);

    /* Check for "READ" query from VCU */
    bool is_read = (msg->dlc >= 4 && memcmp(msg->data, "READ", 4) == 0);

    if (is_read) {
        if (cmd == CAN_CMD_TELEMETRY) {
            if (idx == CAN_IDX_TEL_MOS_STATUS) bms_can_send_status(ctx);
            else if (idx == CAN_IDX_TEL_TEMPS) bms_can_send_temperatures(ctx);
        } else if (cmd == CAN_CMD_CELL_VOLTAGES) {
            bms_can_send_cell_voltages(ctx);
        } else if (cmd == CAN_CMD_PACK_CONFIG) {
            if (idx == CAN_IDX_CFG_CAPACITY_SOH) {
                bms_can_send_capacity_soh(ctx);
            } else if (idx == CAN_IDX_CFG_RATING) {
                CanMessage_t resp;
                resp.id = BMS_CAN_BUILD_ID(6, s_own_sid, BMS_CAN_EXTRACT_SID(msg->id), CAN_CMD_PACK_CONFIG, CAN_IDX_CFG_RATING);
                resp.dlc = 8;
                resp.data[0] = BMS_SERIES_CELLS;                      /* 21 strings */
                resp.data[1] = 1;                                     /* 1 parallel */
                resp.data[2] = (uint8_t)((7000 >> 8) & 0xFF);        /* 7000 * 10mAh = 70Ah */
                resp.data[3] = (uint8_t)(7000 & 0xFF);
                resp.data[4] = (uint8_t)(BMS_MAX_CHARGE_CURRENT_A * 2.5f);
                resp.data[5] = (uint8_t)BMS_MAX_CONTINUOUS_DSG_A;
                resp.data[6] = 0x03;                                  /* Design cycle (1000) */
                resp.data[7] = 0xE8;
                bms_can_transmit(&resp);
            }
        }
    } else if (cmd == CAN_CMD_CONTROL) {
        if (idx == CAN_IDX_CTRL_SWITCH_PACK && msg->dlc >= 1) {
            /* VCU requested power supply switch */
            uint8_t target = msg->data[0];
            if (target == 0x01) {
                /* Power supply battery 1 */
            } else if (target == 0x02) {
                /* Power supply battery 2 */
            }
        }
    }
}
