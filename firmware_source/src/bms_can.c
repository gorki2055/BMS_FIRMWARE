/**
 * @file bms_can.c
 * @brief CAN Communication Protocol Engine (250 kbps, 29-bit Extended IDs)
 * @note Verified against both "CAN documentation.pdf" (V1.1) and the actual
 *       vendor binary firmware (output/firmware_app_0x08008000.bin).
 */

#include "bms_can.h"
#include "bms_hal.h"
#include "bms_storage.h"
#include <string.h>

static uint8_t s_own_sid = BMS_CAN_MASTER_SID;
static uint32_t s_periodic_accum_ms = 0;

/* Transmit history ring buffer for diagnostics and unit test verification */
#define BMS_CAN_TX_HISTORY_SIZE 32U
static CanMessage_t s_tx_history[BMS_CAN_TX_HISTORY_SIZE];
static uint32_t s_tx_count = 0;

/**
 * @brief Standard Modbus CRC16 implementation from BMS documentation & binary (0x0801EFB8)
 */
uint16_t bms_crc16_modbus(const uint8_t *buf, uint16_t len) {
    uint16_t crc = 0xFFFFU;
    for (uint16_t i = 0; i < len; i++) {
        crc ^= buf[i];
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x0001U) {
                crc = (crc >> 1) ^ 0xA001U;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void bms_can_init(uint8_t own_sid) {
    s_own_sid = own_sid;
    s_periodic_accum_ms = 0;
}

void bms_can_transmit(const CanMessage_t *msg) {
    if (!msg) return;
    s_tx_history[s_tx_count % BMS_CAN_TX_HISTORY_SIZE] = *msg;
    s_tx_count++;
    bms_hal_can_transmit(msg->id, msg->data, msg->dlc);
}

uint32_t bms_can_get_tx_count(void) {
    return s_tx_count;
}

const CanMessage_t *bms_can_get_last_tx(void) {
    if (s_tx_count == 0) return NULL;
    return &s_tx_history[(s_tx_count - 1U) % BMS_CAN_TX_HISTORY_SIZE];
}

const CanMessage_t *bms_can_get_tx_history(uint32_t index) {
    if (index >= s_tx_count || index >= BMS_CAN_TX_HISTORY_SIZE) return NULL;
    return &s_tx_history[index];
}

void bms_can_clear_tx_history(void) {
    memset(s_tx_history, 0, sizeof(s_tx_history));
    s_tx_count = 0;
}

/* -------------------------------------------------------------------------
 * Internal Frame Builders (shared by Broadcast and Point-to-Point responses)
 * ------------------------------------------------------------------------- */

static void send_capacity_soc_frame(const BmsContext_t *ctx, uint8_t did, uint8_t cmd) {
    const BmsTelemetry_t *t = &ctx->telemetry;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    /* Verified in FUN_0801b55c (0x0801B55C) and PDF CMD 0x10/0x01 & 0x14/0x01 */
    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, cmd, CAN_IDX_TEL_CAPACITY_SOC);
    msg.dlc = 7;

    uint16_t fcc_10mah = (uint16_t)(t->total_capacity_mah / 10U);
    uint16_t rem_10mah = (uint16_t)(t->remaining_mah / 10U);

    /* Little-Endian 16-bit capacity values (10 mAh / LSB) */
    msg.data[0] = (uint8_t)(fcc_10mah & 0xFFU);
    msg.data[1] = (uint8_t)((fcc_10mah >> 8) & 0xFFU);
    msg.data[2] = (uint8_t)(rem_10mah & 0xFFU);
    msg.data[3] = (uint8_t)((rem_10mah >> 8) & 0xFFU);
    msg.data[4] = t->soc_pct;
    msg.data[5] = t->soh_pct;

    /* D6: Max allowable discharge current in 1A units (0 if discharge prohibited) */
    if (ctx->door_lock_prohibit_dsg || ctx->faults.all != 0) {
        msg.data[6] = 0;
    } else {
        uint32_t max_dsg_a = (ctx->limits.dsg_ocp_ma > 0)
                           ? ((uint32_t)ctx->limits.dsg_ocp_ma / 1000U)
                           : BMS_MAX_CONTINUOUS_DSG_A;
        msg.data[6] = (uint8_t)(max_dsg_a > 255U ? 255U : max_dsg_a);
    }

    bms_can_transmit(&msg);
}

static void send_mos_status_frame(const BmsContext_t *ctx, uint8_t did, uint8_t cmd, uint8_t idx) {
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    /* Verified in FUN_0801ba30 (0x0801BA30) and PDF CMD 0x10/0x40 & 0x14/0x10 */
    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, cmd, idx);
    msg.dlc = 7;

    msg.data[0] = ctx->switches.din_active ? 1U : 0U;      /* Discharge switch line connected */
    msg.data[1] = 1U;                                      /* Address recognition line access */
    msg.data[2] = ctx->switches.cin_active ? 1U : 0U;      /* Charger connected */
    msg.data[3] = ctx->switches.din_active ? 1U : 0U;      /* Load connected */
    msg.data[4] = ctx->switches.dsg_mos_on ? 1U : 0U;      /* Discharge MOS state */
    msg.data[5] = ctx->switches.chg_mos_on ? 1U : 0U;      /* Charge MOS state */
    msg.data[6] = ctx->switches.acc_wake_active ? 1U : 0U; /* Key line (ACC) access */

    bms_can_transmit(&msg);
}

static void send_temperatures_frame(const BmsContext_t *ctx, uint8_t did, uint8_t cmd) {
    const BmsTelemetry_t *t = &ctx->telemetry;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    /* Verified at 0x0801B860 in binary and PDF CMD 0x14/0x03 */
    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, cmd, CAN_IDX_TEL_TEMPS);
    msg.dlc = 7;

    msg.data[0] = BMS_NTC_TEMP_SENSORS;
    for (uint8_t i = 0; i < 4; i++) {
        msg.data[1 + i] = (uint8_t)(t->temp_c[i] + 40);    /* +40 deg C offset */
    }
    msg.data[5] = (uint8_t)(t->mos_temp_c + 40);           /* MOS temperature (+40 offset) */
    msg.data[6] = (uint8_t)(t->connector_temp_c + 40);     /* Connector temperature (+40 offset) */

    bms_can_transmit(&msg);
}

/* -------------------------------------------------------------------------
 * Public Broadcast & Point-to-Point Transmit Functions
 * ------------------------------------------------------------------------- */

/**
 * @brief Broadcast Fault Code & Protection Bitmask (CMD 0x0E, Index = ERR, 1000 ms)
 * @note Verified in FUN_0801f842 (0x0801F842) and PDF Section 4.1 (CMD 0x0E)
 */
void bms_can_send_fault_broadcast(const BmsContext_t *ctx) {
    if (!ctx) return;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    const BmsFaultFlags_t *f = &ctx->faults;
    uint8_t err_code = 0x00U;

    /* Determine primary fault code for Index (ERR) per PDF Fault Code Table */
    if (f->bits.dsg_ocp1 || f->bits.dsg_ocp2) {
        err_code = 0x02U; /* Discharge overcurrent */
    } else if (f->bits.chg_otp || f->bits.chg_utp || f->bits.dsg_otp || f->bits.dsg_utp) {
        err_code = 0x05U; /* Temperature fault */
    } else if (f->bits.cell_ovp || f->bits.pack_ovp) {
        err_code = 0x06U; /* Overcharge protection */
    } else if (f->bits.cell_uvp || f->bits.pack_uvp) {
        err_code = 0x07U; /* Overdischarge protection */
    } else if (f->bits.cell_unbalance) {
        err_code = 0x0DU; /* Cell voltage unbalance */
    } else if (f->bits.chg_ocp) {
        err_code = 0x12U; /* Charge overcurrent */
    } else if (f->bits.afe_comm_fail) {
        err_code = 0x42U; /* AFE communication fault */
    } else if (f->bits.mos_otp) {
        err_code = 0x48U; /* MOS over-temperature */
    }

    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, BMS_CAN_DID_BROADCAST, CAN_CMD_FAULT_BCAST, err_code);
    msg.dlc = 8;

    /* D0: Bit1=DsgOCP, Bit4=TempFault, Bit5=OVP, Bit6=UVP */
    if (f->bits.dsg_ocp1 || f->bits.dsg_ocp2) msg.data[0] |= (1U << 1);
    if (f->bits.chg_otp || f->bits.chg_utp || f->bits.dsg_otp || f->bits.dsg_utp) msg.data[0] |= (1U << 4);
    if (f->bits.cell_ovp || f->bits.pack_ovp) msg.data[0] |= (1U << 5);
    if (f->bits.cell_uvp || f->bits.pack_uvp) msg.data[0] |= (1U << 6);

    /* D1: Bit4=Unbalance */
    if (f->bits.cell_unbalance) msg.data[1] |= (1U << 4);

    /* D2: Bit1=ChgOCP */
    if (f->bits.chg_ocp) msg.data[2] |= (1U << 1);

    /* D5: Bit1=AFE Error, Bit7=MOS OTP */
    if (f->bits.afe_comm_fail) msg.data[5] |= (1U << 1);
    if (f->bits.mos_otp)       msg.data[5] |= (1U << 7);

    bms_can_transmit(&msg);
}

/**
 * @brief Broadcast Dynamic Capacity, SOC, SOH, and Max DSG Current (CMD 0x10, IDX 0x01)
 */
void bms_can_send_capacity_soh(const BmsContext_t *ctx) {
    if (!ctx) return;
    send_capacity_soc_frame(ctx, BMS_CAN_DID_BROADCAST, CAN_CMD_BCAST_STATUS);
}

/**
 * @brief Transmit Battery State, Current, 24-bit Pack Voltage, and Min/Max Temp
 * @note Verified in FUN_0801b764 (0x0801B764) and PDF CMD 0x10/0x02 & 0x14/0x02
 */
void bms_can_send_volt_curr_temp(const BmsContext_t *ctx, uint8_t did, uint8_t cmd) {
    if (!ctx) return;
    const BmsTelemetry_t *t = &ctx->telemetry;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, cmd, CAN_IDX_TEL_VOLT_CURR_TEMP);
    msg.dlc = 8;

    /* D0: Battery status (0 = Stationary, 1 = Charging, 2 = Discharging) */
    if (t->current_ma > 100 || ctx->state == BMS_STATE_CHARGE) {
        msg.data[0] = 1U;
    } else if (t->current_ma < -100 || ctx->state == BMS_STATE_DISCHARGE) {
        msg.data[0] = 2U;
    } else {
        msg.data[0] = 0U;
    }

    /* D1..D2: Current in 0.01A (10mA) units, signed 16-bit Little-Endian */
    int16_t curr_10ma = (int16_t)(t->current_ma / 10);
    msg.data[1] = (uint8_t)((uint16_t)curr_10ma & 0xFFU);
    msg.data[2] = (uint8_t)(((uint16_t)curr_10ma >> 8) & 0xFFU);

    /* D3..D5: Total pack voltage in 1mV units, 24-bit Little-Endian */
    msg.data[3] = (uint8_t)(t->pack_voltage_mv & 0xFFU);
    msg.data[4] = (uint8_t)((t->pack_voltage_mv >> 8) & 0xFFU);
    msg.data[5] = (uint8_t)((t->pack_voltage_mv >> 16) & 0xFFU);

    /* D6: Lowest cell temperature (+40 deg C offset) */
    msg.data[6] = (uint8_t)(t->min_temp_c + 40);
    /* D7: Highest cell temperature (+40 deg C offset) */
    msg.data[7] = (uint8_t)(t->max_temp_c + 40);

    bms_can_transmit(&msg);
}

/**
 * @brief Broadcast Switch / MOS / Key Status (CMD 0x10, IDX 0x40, 1000 ms)
 */
void bms_can_send_status(const BmsContext_t *ctx) {
    if (!ctx) return;
    send_mos_status_frame(ctx, BMS_CAN_DID_BROADCAST, CAN_CMD_BCAST_STATUS, CAN_IDX_BCAST_MOS_STATUS);
}

/**
 * @brief Broadcast Parallel Connection & Power Supply Status (CMD 0x11, IDX 0x01, 100 ms)
 * @note Verified in FUN_0801badc (0x0801BADC) and PDF CMD 0x11/0x01
 */
void bms_can_send_parallel_status(const BmsContext_t *ctx) {
    if (!ctx) return;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, BMS_CAN_DID_BROADCAST, CAN_CMD_BCAST_PARALLEL_HW, 0x01U);
    msg.dlc = 5;

    bool is_parallel = (ctx->role != BMS_ROLE_STANDALONE);
    uint8_t active_bat = ctx->active_power_battery;
    if (active_bat != 1U && active_bat != 2U) {
        active_bat = (ctx->role == BMS_ROLE_SLAVE) ? 2U : 1U;
    }

    msg.data[0] = is_parallel ? 1U : 0U;                /* D0: Parallel connection flag */
    msg.data[1] = active_bat;                           /* D1: Current discharge battery (1=Master, 2=Slave) */
    msg.data[2] = ctx->switches.cin_active ? 1U : 0U;   /* D2: Charger status */
    msg.data[3] = ctx->parallel_switch_status;          /* D3: Switching status (0..3) */
    msg.data[4] = is_parallel ? 2U : 1U;                /* D4: Parallel battery count */

    bms_can_transmit(&msg);
}

/**
 * @brief Transmit Pack Rating Frame (Broadcast CMD 0x12 IDX 0x01 or P2P CMD 0x40 IDX 0x01)
 * @note Verified in FUN_0801bc04 (0x0801BC04) and PDF CMD 0x12/0x01 & 0x40/0x01:
 *       All 16-bit fields (Design Capacity & Design Cycles) are Little-Endian!
 */
void bms_can_send_pack_rating(const BmsContext_t *ctx, uint8_t did, uint8_t cmd) {
    (void)ctx;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, cmd, CAN_IDX_CFG_RATING);
    msg.dlc = 8;

    uint16_t design_cap_10mah = (uint16_t)(BMS_NOMINAL_CAPACITY_MAH / 10U); /* 7000 = 0x1B58 */
    uint16_t design_cycles    = 1000U;                                      /* 1000 = 0x03E8 */

    msg.data[0] = BMS_SERIES_CELLS;                                         /* D0: 21 strings */
    msg.data[1] = BMS_PARALLEL_STRINGS;                                     /* D1: 1 parallel */
    msg.data[2] = (uint8_t)(design_cap_10mah & 0xFFU);                      /* D2: 0x58 (LSB) */
    msg.data[3] = (uint8_t)((design_cap_10mah >> 8) & 0xFFU);               /* D3: 0x1B (MSB) */
    msg.data[4] = (uint8_t)((BMS_MAX_CHARGE_CURRENT_A * 10U) / 4U);         /* D4: 0.4A units (87) */
    msg.data[5] = (uint8_t)BMS_MAX_CONTINUOUS_DSG_A;                        /* D5: 1A units (70) */
    msg.data[6] = (uint8_t)(design_cycles & 0xFFU);                         /* D6: 0xE8 (LSB) */
    msg.data[7] = (uint8_t)((design_cycles >> 8) & 0xFFU);                  /* D7: 0x03 (MSB) */

    bms_can_transmit(&msg);
}

/**
 * @brief Transmit Cycle Count & Uncharged/Charge Time Stats (CMD 0x40 IDX 0x02)
 * @note Verified at 0x0801BD28 in binary and PDF CMD 0x40/0x02
 */
void bms_can_send_cycle_stats(const BmsContext_t *ctx, uint8_t did, uint8_t cmd) {
    if (!ctx) return;
    const BmsTelemetry_t *t = &ctx->telemetry;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, cmd, CAN_IDX_CFG_CYCLES);
    msg.dlc = 8;

    uint16_t chg_time_01min = (uint16_t)(t->est_chg_time_min * 10U);

    msg.data[0] = (uint8_t)(t->cycle_count & 0xFFU);
    msg.data[1] = (uint8_t)((t->cycle_count >> 8) & 0xFFU);
    msg.data[2] = (uint8_t)(t->max_uncharged_hours & 0xFFU);
    msg.data[3] = (uint8_t)((t->max_uncharged_hours >> 8) & 0xFFU);
    msg.data[4] = (uint8_t)(t->recent_uncharged_hours & 0xFFU);
    msg.data[5] = (uint8_t)((t->recent_uncharged_hours >> 8) & 0xFFU);
    msg.data[6] = (uint8_t)(chg_time_01min & 0xFFU);
    msg.data[7] = (uint8_t)((chg_time_01min >> 8) & 0xFFU);

    bms_can_transmit(&msg);
}

/**
 * @brief Transmit Temperatures Frame (CMD 0x14 IDX 0x03)
 */
void bms_can_send_temperatures(const BmsContext_t *ctx) {
    if (!ctx) return;
    send_temperatures_frame(ctx, BMS_CAN_DID_VCU, CAN_CMD_TELEMETRY);
}

/**
 * @brief Transmit Accumulated Charge & Discharge Capacity in mAh (CMD 0x14 IDX 0x04)
 * @note Verified at 0x0801B926 in binary and PDF CMD 0x14/0x04 (32-bit Little-Endian)
 */
void bms_can_send_accum_mah(const BmsContext_t *ctx, uint8_t did, uint8_t cmd) {
    if (!ctx) return;
    const BmsTelemetry_t *t = &ctx->telemetry;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));

    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, cmd, CAN_IDX_TEL_ACCUM_MAH);
    msg.dlc = 8;

    msg.data[0] = (uint8_t)(t->accum_chg_mah & 0xFFU);
    msg.data[1] = (uint8_t)((t->accum_chg_mah >> 8) & 0xFFU);
    msg.data[2] = (uint8_t)((t->accum_chg_mah >> 16) & 0xFFU);
    msg.data[3] = (uint8_t)((t->accum_chg_mah >> 24) & 0xFFU);

    msg.data[4] = (uint8_t)(t->accum_dsg_mah & 0xFFU);
    msg.data[5] = (uint8_t)((t->accum_dsg_mah >> 8) & 0xFFU);
    msg.data[6] = (uint8_t)((t->accum_dsg_mah >> 16) & 0xFFU);
    msg.data[7] = (uint8_t)((t->accum_dsg_mah >> 24) & 0xFFU);

    bms_can_transmit(&msg);
}

/**
 * @brief Transmit a Single 4-Cell Voltage Group (CMD 0x41, IDX 0x03..0x08)
 * @note Verified at 0x0801BE1A in binary and PDF CMD 0x41:
 *       Cell voltages are 16-bit Little-Endian in mV (LSB first, MSB second).
 */
void bms_can_send_cell_voltage_group(const BmsContext_t *ctx, uint8_t did, uint8_t idx) {
    if (!ctx || idx < CAN_IDX_CELL_VOLT_1_4 || idx > CAN_IDX_CELL_VOLT_21_24) return;
    const BmsTelemetry_t *t = &ctx->telemetry;
    uint8_t frame = idx - CAN_IDX_CELL_VOLT_1_4;

    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));
    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, CAN_CMD_CELL_VOLTAGES, idx);
    msg.dlc = 8;

    for (uint8_t c = 0; c < 4; c++) {
        uint8_t cell_num = frame * 4U + c;
        if (cell_num < BMS_SERIES_CELLS) {
            uint16_t v = t->cell_mv[cell_num];
            msg.data[c * 2U]      = (uint8_t)(v & 0xFFU);        /* LSB */
            msg.data[c * 2U + 1U] = (uint8_t)((v >> 8) & 0xFFU); /* MSB */
        }
    }
    bms_can_transmit(&msg);
}

/**
 * @brief Transmit All 6 Cell Voltage Frames (CMD 0x41, IDX 0x03..0x08)
 */
void bms_can_send_cell_voltages(const BmsContext_t *ctx) {
    if (!ctx) return;
    for (uint8_t idx = CAN_IDX_CELL_VOLT_1_4; idx <= CAN_IDX_CELL_VOLT_21_24; idx++) {
        bms_can_send_cell_voltage_group(ctx, BMS_CAN_DID_VCU, idx);
    }
}

/**
 * @brief Transmit an 8-Cell Balancing Status Group (CMD 0x42, IDX 0x10..0x12)
 * @note Verified at 0x0801BFDC in binary and PDF CMD 0x42
 */
void bms_can_send_balancing_group(const BmsContext_t *ctx, uint8_t did, uint8_t cmd, uint8_t idx) {
    if (!ctx || idx < CAN_IDX_BAL_CELL_1_8 || idx > CAN_IDX_BAL_CELL_17_24) return;
    uint8_t group = idx - CAN_IDX_BAL_CELL_1_8;

    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));
    msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, cmd, idx);
    msg.dlc = 8;

    for (uint8_t b = 0; b < 8; b++) {
        uint8_t cell_idx = group * 8U + b;
        if (cell_idx < BMS_SERIES_CELLS) {
            msg.data[b] = ((ctx->telemetry.balance_mask >> cell_idx) & 0x01U) ? 1U : 0U;
        }
    }
    bms_can_transmit(&msg);
}

/**
 * @brief Send General Response Frame (CMD 0x0A, DLC = 3)
 * @note Verified in PDF Section 4.1 (CMD 0x0A)
 */
void bms_can_send_general_response(uint8_t did, uint8_t ack_cmd, uint8_t ack_idx, uint8_t status) {
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));
    msg.id      = BMS_CAN_MAKE_ID(s_own_sid, did, CAN_CMD_GENERAL_RESP, ack_cmd);
    msg.dlc     = 3;
    msg.data[0] = ack_cmd;
    msg.data[1] = ack_idx;
    msg.data[2] = status; /* 0x00 = Success, 0x01 = Fail */
    bms_can_transmit(&msg);
}

/**
 * @brief Send Multi-Frame Long Packet (CMD 0x04, Index = 1..N) with Modbus CRC16
 * @note Verified in FUN_0801c154 / FUN_0801c228 / FUN_0801c2fa and PDF Section 4.1 (CMD 0x04):
 *       Stream layout:
 *         Byte 0: Original Command (e.g., 0x11)
 *         Byte 1: Sub-Command (e.g., 0x01=HWVER, 0x02=FWVER, 0x03=SN)
 *         Byte 2..3: Payload length in bytes (Little-Endian)
 *         Byte 4..4+len-1: Payload bytes
 *         Byte 4+len..5+len: CRC16 (Little-Endian) over Bytes [0 .. 4+len-1]
 */
void bms_can_send_long_packet(uint8_t did, uint8_t orig_cmd, uint8_t sub_cmd, const uint8_t *payload, uint16_t len) {
    if (!payload || len > 56U) return;

    uint8_t stream[64];
    memset(stream, 0, sizeof(stream));

    stream[0] = orig_cmd;
    stream[1] = sub_cmd;
    stream[2] = (uint8_t)(len & 0xFFU);
    stream[3] = (uint8_t)((len >> 8) & 0xFFU);
    memcpy(&stream[4], payload, len);

    uint16_t crc = bms_crc16_modbus(stream, (uint16_t)(4U + len));
    stream[4U + len] = (uint8_t)(crc & 0xFFU);
    stream[5U + len] = (uint8_t)((crc >> 8) & 0xFFU);

    uint16_t total_bytes = (uint16_t)(6U + len);
    uint8_t total_frames = (uint8_t)((total_bytes + 7U) / 8U);

    for (uint8_t seq = 0; seq < total_frames; seq++) {
        CanMessage_t msg;
        memset(&msg, 0, sizeof(msg));
        msg.id  = BMS_CAN_MAKE_ID(s_own_sid, did, CAN_CMD_LONG_PACKET, (uint8_t)(seq + 1U));
        msg.dlc = 8;
        memcpy(msg.data, &stream[seq * 8U], 8U);
        bms_can_transmit(&msg);
    }
}

/**
 * @brief Periodic Broadcast Scheduler (100 ms, 500 ms, and 1000 ms intervals)
 * @note Implements the broadcast schedule from PDF Section 4.1 and FUN_0801f842:
 *       - Every 100 ms : CMD 0x10 IDX 0x02 (State/Current/Volt/Temp) & CMD 0x11 IDX 0x01 (Parallel Status)
 *       - Every 500 ms : CMD 0x10 IDX 0x01 (Cap/SOC/SOH/MaxDsgI) & CMD 0x12 IDX 0x01 (Pack Rating)
 *       - Every 1000 ms: CMD 0x10 IDX 0x40 (Switch/MOS/Key Status) & CMD 0x0E IDX ERR (Fault Broadcast)
 */
void bms_can_periodic_step(const BmsContext_t *ctx, uint32_t elapsed_ms) {
    if (!ctx || ctx->can_silent) return;

    s_periodic_accum_ms += elapsed_ms;

    /* 100 ms broadcasts */
    bms_can_send_volt_curr_temp(ctx, BMS_CAN_DID_BROADCAST, CAN_CMD_BCAST_STATUS);
    bms_can_send_parallel_status(ctx);

    /* 500 ms broadcasts */
    if ((s_periodic_accum_ms % 500U) == 0U) {
        bms_can_send_capacity_soh(ctx);
        bms_can_send_pack_rating(ctx, BMS_CAN_DID_BROADCAST, CAN_CMD_BCAST_RATING);
    }

    /* 1000 ms broadcasts */
    if ((s_periodic_accum_ms % 1000U) == 0U) {
        bms_can_send_status(ctx);
        bms_can_send_fault_broadcast(ctx);
    }
}

/* -------------------------------------------------------------------------
 * Point-to-Point & Broadcast RX Command Dispatcher
 * Verified against both PDF Section 4.2 and FUN_08020f1c (0x08020F1C)
 * ------------------------------------------------------------------------- */
void bms_can_process_rx(const CanMessage_t *msg, BmsContext_t *ctx) {
    if (!msg || !ctx) return;

    uint8_t req_sid = BMS_CAN_EXTRACT_SID(msg->id);
    uint8_t did     = BMS_CAN_EXTRACT_DID(msg->id);
    uint8_t cmd     = BMS_CAN_EXTRACT_CMD(msg->id);
    uint8_t idx     = BMS_CAN_EXTRACT_IDX(msg->id);

    /* Only process frames addressed to this BMS or Broadcast (0x1F) */
    if (did != s_own_sid && did != BMS_CAN_DID_BROADCAST) return;

    bool is_read = (msg->dlc >= 4U && memcmp(msg->data, "READ", 4) == 0);

    switch (cmd) {
        case CAN_CMD_SET_ID: /* CMD 0x00: Set Equipment ID */
            if (idx == 0x01U && msg->dlc >= 1U) {
                s_own_sid = msg->data[0] & 0x1FU;
                ctx->can_sid = s_own_sid;
                bms_can_send_general_response(req_sid, cmd, idx, 0x00U);
            }
            break;

        case CAN_CMD_BCAST_PARALLEL_HW: /* CMD 0x11: HWVER / FWVER / SN Query -> Long Packet 0x04 */
            if (did == s_own_sid) {
                if (idx == CAN_IDX_INFO_HWVER &&
                    (msg->dlc == 0 || is_read || (msg->dlc >= 5U && memcmp(msg->data, "HWVER", 5) == 0))) {
                    /* Verified at 0x0801C154: Hardware Version = "A10.0" */
                    bms_can_send_long_packet(req_sid, cmd, idx, (const uint8_t *)"A10.0", 5U);
                } else if (idx == CAN_IDX_INFO_FWVER &&
                           (msg->dlc == 0 || is_read || (msg->dlc >= 5U && memcmp(msg->data, "FWVER", 5) == 0))) {
                    /* Verified at 0x0801C228: Firmware Version = "V02.0" */
                    bms_can_send_long_packet(req_sid, cmd, idx, (const uint8_t *)"V02.0", 5U);
                } else if (idx == CAN_IDX_INFO_SN) {
                    /* Verified at 0x0801C2FA: Serial Number / Barcode */
                    uint16_t sn_len = (uint16_t)strlen(ctx->serial_number);
                    if (sn_len == 0U) sn_len = 1U;
                    bms_can_send_long_packet(req_sid, cmd, idx, (const uint8_t *)ctx->serial_number, sn_len);
                }
            }
            break;

        case CAN_CMD_TELEMETRY: /* CMD 0x14: Point-to-Point Telemetry Read/Write */
            if (idx == CAN_IDX_TEL_CAPACITY_SOC) {
                send_capacity_soc_frame(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_TEL_VOLT_CURR_TEMP) {
                bms_can_send_volt_curr_temp(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_TEL_TEMPS) {
                send_temperatures_frame(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_TEL_ACCUM_MAH) {
                bms_can_send_accum_mah(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_TEL_DOOR_LOCK_WRITE && msg->dlc >= 1U && !is_read) {
                /* Verified at 0x0801B99E: 1 = prohibit discharge, 2 = allow discharge */
                if (msg->data[0] == 1U) {
                    ctx->door_lock_prohibit_dsg = true;
                } else if (msg->data[0] == 2U) {
                    ctx->door_lock_prohibit_dsg = false;
                }
                CanMessage_t resp;
                memset(&resp, 0, sizeof(resp));
                resp.id      = BMS_CAN_MAKE_ID(s_own_sid, req_sid, cmd, idx);
                resp.dlc     = 1;
                resp.data[0] = msg->data[0];
                bms_can_transmit(&resp);
            } else if (idx == CAN_IDX_TEL_DOOR_LOCK_READ) {
                CanMessage_t resp;
                memset(&resp, 0, sizeof(resp));
                resp.id      = BMS_CAN_MAKE_ID(s_own_sid, req_sid, cmd, idx);
                resp.dlc     = 1;
                resp.data[0] = ctx->door_lock_prohibit_dsg ? 1U : 0U;
                bms_can_transmit(&resp);
            } else if (idx == CAN_IDX_TEL_MOS_STATUS) {
                send_mos_status_frame(ctx, req_sid, cmd, idx);
            }
            break;

        case CAN_CMD_FIRMWARE_UPDATE: /* CMD 0x1A: Online Firmware Update ("UPDATE") */
            if (idx == 0x00U && msg->dlc >= 6U && memcmp(msg->data, "UPDATE", 6) == 0) {
                ctx->ota_update_requested = true;
                (void)bms_storage_write_boot_iap_flag(BMS_BOOT_IAP_MAGIC);
                (void)bms_storage_log_event(BMS_EVENT_CAN_IAP, ctx);
                bms_can_send_general_response(req_sid, cmd, idx, 0x00U);
            }
            break;

        case CAN_CMD_BUS_SILENCE: /* CMD 0x1F: Broadcast Silence ("SILENCE") */
            if (idx == 0x1FU && msg->dlc >= 7U && memcmp(msg->data, "SILENCE", 7) == 0) {
                ctx->can_silent = true;
            }
            break;

        case CAN_CMD_PACK_CONFIG: /* CMD 0x40: Pack Rating & Cycles (PDF) + Binary 0x40 Telemetry Aliases */
            if (idx == CAN_IDX_CFG_RATING) {
                bms_can_send_pack_rating(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_CFG_CYCLES) {
                bms_can_send_cycle_stats(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_TEL_TEMPS) {
                send_temperatures_frame(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_TEL_ACCUM_MAH) {
                bms_can_send_accum_mah(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_TEL_MOS_STATUS) {
                send_mos_status_frame(ctx, req_sid, cmd, idx);
            }
            break;

        case CAN_CMD_CELL_VOLTAGES: /* CMD 0x41: Cell Voltages (0x03..0x08) + Binary 0x41 Aliases */
            if (idx >= CAN_IDX_CELL_VOLT_1_4 && idx <= CAN_IDX_CELL_VOLT_21_24) {
                bms_can_send_cell_voltage_group(ctx, req_sid, idx);
            } else if (idx == CAN_IDX_CFG_RATING) {
                bms_can_send_pack_rating(ctx, req_sid, cmd);
            } else if (idx == CAN_IDX_CFG_CYCLES) {
                bms_can_send_cycle_stats(ctx, req_sid, cmd);
            } else if (idx >= CAN_IDX_BAL_CELL_1_8 && idx <= CAN_IDX_BAL_CELL_17_24) {
                bms_can_send_balancing_group(ctx, req_sid, cmd, idx);
            }
            break;

        case CAN_CMD_BALANCING_STATE: /* CMD 0x42: Cell Balancing (0x10..0x12) + Binary 0x42 Aliases */
            if (idx >= CAN_IDX_BAL_CELL_1_8 && idx <= CAN_IDX_BAL_CELL_17_24) {
                bms_can_send_balancing_group(ctx, req_sid, cmd, idx);
            } else if (idx == CAN_IDX_CTRL_PROTOCOL_VER) {
                CanMessage_t resp = { BMS_CAN_MAKE_ID(s_own_sid, req_sid, cmd, idx), 4, {0x00, 0x00, 0x01, 0x03, 0, 0, 0, 0} };
                bms_can_transmit(&resp);
            } else if (idx == CAN_IDX_CTRL_IDLE_TIME) {
                CanMessage_t resp = {
                    BMS_CAN_MAKE_ID(s_own_sid, req_sid, cmd, idx), 2,
                    { (uint8_t)(ctx->telemetry.idle_hours & 0xFFU), (uint8_t)((ctx->telemetry.idle_hours >> 8) & 0xFFU), 0, 0, 0, 0, 0, 0 }
                };
                bms_can_transmit(&resp);
            }
            break;

        case CAN_CMD_CONTROL: /* CMD 0x43: Protocol Ver (0x01), Switch Pack (0x03), Idle (0x04), Reset/Sleep (0xF2) */
            if (idx == CAN_IDX_CTRL_PROTOCOL_VER) {
                /* Verified at 0x0801C0AC in binary: returns 00 00 01 03 (v1.3) */
                CanMessage_t resp = { BMS_CAN_MAKE_ID(s_own_sid, req_sid, cmd, idx), 4, {0x00, 0x00, 0x01, 0x03, 0, 0, 0, 0} };
                bms_can_transmit(&resp);
            } else if (idx == CAN_IDX_CTRL_SWITCH_PACK && msg->dlc >= 1U) {
                if (!is_read && (msg->data[0] == 0x01U || msg->data[0] == 0x02U)) {
                    ctx->active_power_battery = msg->data[0];
                    ctx->parallel_switch_status = 3U; /* Switch success */
                }
                uint8_t cur_bat = (ctx->active_power_battery == 1U || ctx->active_power_battery == 2U)
                                ? ctx->active_power_battery
                                : ((ctx->role == BMS_ROLE_SLAVE) ? 2U : 1U);
                CanMessage_t resp = { BMS_CAN_MAKE_ID(s_own_sid, req_sid, cmd, idx), 1, {cur_bat, 0, 0, 0, 0, 0, 0, 0} };
                bms_can_transmit(&resp);
            } else if (idx == CAN_IDX_CTRL_IDLE_TIME) {
                CanMessage_t resp = {
                    BMS_CAN_MAKE_ID(s_own_sid, req_sid, cmd, idx), 2,
                    { (uint8_t)(ctx->telemetry.idle_hours & 0xFFU), (uint8_t)((ctx->telemetry.idle_hours >> 8) & 0xFFU), 0, 0, 0, 0, 0, 0 }
                };
                bms_can_transmit(&resp);
            } else if (idx == CAN_IDX_CTRL_RESET_SLEEP && msg->dlc >= 1U) {
                if (msg->data[0] == 0x01U) {
                    ctx->state = BMS_STATE_INIT;  /* Soft reset */
                    bms_can_send_general_response(req_sid, cmd, idx, 0x00U);
                } else if (msg->data[0] == 0x02U) {
                    ctx->state = BMS_STATE_SLEEP; /* Sleep mode */
                    bms_can_send_general_response(req_sid, cmd, idx, 0x00U);
                }
            }
            break;

        /* ==============================================================
         * CMD 0x44: Custom Calibration Read/Write (FUN_0801afbc, 0x01..0x03 / 0xF1..0xF3)
         * ============================================================== */
        case CAN_CMD_CUSTOM_CALIB: {
            CanMessage_t tx;
            memset(&tx, 0, sizeof(tx));
            tx.id  = BMS_CAN_MAKE_ID(s_own_sid, req_sid, CAN_CMD_CUSTOM_CALIB, idx);
            tx.dlc = 8;

            if (idx == 0xF1U && msg->dlc >= 8U) {
                /* Write Cell OVP/UVP & CHG/DSG OCP thresholds */
                ctx->limits.cell_ovp_mv = (uint16_t)(msg->data[0] | (msg->data[1] << 8));
                ctx->limits.cell_uvp_mv = (uint16_t)(msg->data[2] | (msg->data[3] << 8));
                ctx->limits.chg_ocp_ma  = (int32_t)((uint16_t)(msg->data[4] | (msg->data[5] << 8))) * 100;
                ctx->limits.dsg_ocp_ma  = (int32_t)((uint16_t)(msg->data[6] | (msg->data[7] << 8))) * 100;
                (void)bms_storage_save_config(ctx);
                bms_can_send_general_response(req_sid, CAN_CMD_CUSTOM_CALIB, idx, 0x00U);
                break;
            }

            if (idx == 0x01U || idx == 0xF1U) {
                uint16_t chg_ocp_0_1a = (uint16_t)(ctx->limits.chg_ocp_ma / 100);
                uint16_t dsg_ocp_0_1a = (uint16_t)(ctx->limits.dsg_ocp_ma / 100);
                tx.data[0] = (uint8_t)(ctx->limits.cell_ovp_mv & 0xFFU);
                tx.data[1] = (uint8_t)((ctx->limits.cell_ovp_mv >> 8) & 0xFFU);
                tx.data[2] = (uint8_t)(ctx->limits.cell_uvp_mv & 0xFFU);
                tx.data[3] = (uint8_t)((ctx->limits.cell_uvp_mv >> 8) & 0xFFU);
                tx.data[4] = (uint8_t)(chg_ocp_0_1a & 0xFFU);
                tx.data[5] = (uint8_t)((chg_ocp_0_1a >> 8) & 0xFFU);
                tx.data[6] = (uint8_t)(dsg_ocp_0_1a & 0xFFU);
                tx.data[7] = (uint8_t)((dsg_ocp_0_1a >> 8) & 0xFFU);
                bms_can_transmit(&tx);
            } else {
                bms_can_send_general_response(req_sid, CAN_CMD_CUSTOM_CALIB, idx, 0x00U);
            }
            break;
        }

        default:
            break;
    }
}
