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
