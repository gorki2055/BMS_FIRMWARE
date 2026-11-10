/**
 * @file bms_parallel.c
 * @brief Multi-Pack Dual Battery Parallel Arbitration & 5% Switching Strategy
 */

#include "bms_parallel.h"
#include "bms_can.h"
#include <string.h>

static BmsParallelManager_t s_parallel_mgr;

void bms_parallel_init(BmsContext_t *ctx) {
    memset(&s_parallel_mgr, 0, sizeof(BmsParallelManager_t));
    s_parallel_mgr.stage = PARALLEL_STAGE_MASTER_ACTIVE;
    s_parallel_mgr.active_pack_id = BMS_CAN_MASTER_SID;
    ctx->role = BMS_ROLE_STANDALONE;
}

void bms_parallel_evaluate_role(BmsContext_t *ctx, const char *local_sn, const char *peer_sn) {
    if (!ctx || !local_sn || !peer_sn) return;

    /*
     * Rule: Compare Serial Numbers:
     * 1. Determine capacity level in SN (larger capacity = Master 0x14).
     * 2. If equal, compare production date & sequence (smaller number = Master 0x14).
     */
    int cmp = strcmp(local_sn, peer_sn);
    if (cmp <= 0) {
        ctx->role = BMS_ROLE_MASTER;
        ctx->can_sid = BMS_CAN_MASTER_SID;
    } else {
        ctx->role = BMS_ROLE_SLAVE;
        ctx->can_sid = BMS_CAN_SLAVE_SID;
    }

    bms_can_init(ctx->can_sid);
}

void bms_parallel_process_tick(BmsContext_t *ctx) {
    if (ctx->role != BMS_ROLE_MASTER) {
        /* Slave packs respond to commands but do not initiate switches */
        return;
    }

    uint8_t local_soc = ctx->telemetry.soc_pct;

    switch (s_parallel_mgr.stage) {
        case PARALLEL_STAGE_MASTER_ACTIVE:
            /* Master discharges until SOC drops below 5% */
            if (local_soc <= 5 && s_parallel_mgr.peer_connected && !s_parallel_mgr.peer_in_uvp) {
                bms_parallel_request_switch(ctx, BMS_CAN_SLAVE_SID);
                s_parallel_mgr.stage = PARALLEL_STAGE_SLAVE_ACTIVE;
            }
            break;

        case PARALLEL_STAGE_SLAVE_ACTIVE:
            /* Slave discharges until its SOC reaches 0% or UVP trips */
            if (s_parallel_mgr.peer_soc_pct == 0 || s_parallel_mgr.peer_in_uvp) {
                /* Switch back to Master to utilize the final 5% */
                bms_parallel_request_switch(ctx, BMS_CAN_MASTER_SID);
                s_parallel_mgr.stage = PARALLEL_STAGE_MASTER_REMAINDER;
            }
            break;

        case PARALLEL_STAGE_MASTER_REMAINDER:
            if (local_soc == 0 || ctx->faults.bits.cell_uvp) {
                s_parallel_mgr.stage = PARALLEL_STAGE_PACKS_DEPLETED;
            }
            break;

        default:
            break;
    }
}

bool bms_parallel_request_switch(BmsContext_t *ctx, uint8_t target_pack_id) {
    CanMessage_t msg;
    msg.id = BMS_CAN_BUILD_ID(6, ctx->can_sid, target_pack_id, CAN_CMD_CONTROL, CAN_IDX_CTRL_SWITCH_PACK);
    msg.dlc = 1;
    msg.data[0] = (target_pack_id == BMS_CAN_MASTER_SID) ? 0x01 : 0x02;

    bms_can_transmit(&msg);
    s_parallel_mgr.active_pack_id = target_pack_id;
    return true;
}

/**
 * @brief Transmit internal parallel-bus heartbeat frame (0x141DF001, FUN_0801f044)
 */
void bms_parallel_send_heartbeat(const BmsContext_t *ctx) {
    if (!ctx) return;
    CanMessage_t msg;
    memset(&msg, 0, sizeof(msg));
    msg.id  = BMS_PARALLEL_CAN_ID_HEARTBEAT;
    msg.dlc = 8;
    msg.data[0] = ctx->can_sid;
    msg.data[1] = ctx->telemetry.soc_pct;
    uint16_t pack_0_1v = (uint16_t)(ctx->telemetry.pack_voltage_mv / 100U);
    msg.data[2] = (uint8_t)(pack_0_1v & 0xFFU);
    msg.data[3] = (uint8_t)((pack_0_1v >> 8) & 0xFFU);
    msg.data[4] = ctx->faults.bits.cell_uvp ? 1U : 0U;
    msg.data[5] = (uint8_t)ctx->role;
    bms_can_transmit(&msg);
}

/**
 * @brief Process internal parallel-bus CAN frame (0x141DF001, 0x101..0x106, 0x201..0x203, FUN_0801ca08)
 */
bool bms_parallel_process_can_rx(BmsContext_t *ctx, uint32_t can_id, const uint8_t *data, uint8_t dlc) {
    if (!ctx || !data || dlc < 4) return false;

    if (can_id == BMS_PARALLEL_CAN_ID_HEARTBEAT ||
        (can_id >= BMS_PARALLEL_CAN_ID_SYNC_BASE && can_id <= (BMS_PARALLEL_CAN_ID_SYNC_BASE + 5U)) ||
        (can_id >= BMS_PARALLEL_CAN_ID_STATUS_BASE && can_id <= (BMS_PARALLEL_CAN_ID_STATUS_BASE + 2U))) {
        s_parallel_mgr.peer_connected       = true;
        s_parallel_mgr.peer_soc_pct         = data[1];
        s_parallel_mgr.peer_pack_voltage_mv = (uint32_t)((uint16_t)data[2] | ((uint16_t)data[3] << 8)) * 100UL;
        if (dlc >= 5) {
            s_parallel_mgr.peer_in_uvp = (data[4] != 0U);
        }
        s_parallel_mgr.last_peer_heartbeat_ms = ctx->uptime_seconds * 1000UL;
        return true;
    }
    return false;
}

const BmsParallelManager_t *bms_parallel_get_manager(void) {
    return &s_parallel_mgr;
}
