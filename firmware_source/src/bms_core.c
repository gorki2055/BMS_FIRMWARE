/**
 * @file bms_core.c
 * @brief Core State Machine, Protection Supervisor, and Balancing Logic
 */

#include "bms_core.h"
#include "bms_config.h"
#include "bms_hal.h"
#include "dvc1124_afe.h"
#include <string.h>

void bms_core_init(BmsContext_t *ctx) {
    if (!ctx) return;
    memset(ctx, 0, sizeof(BmsContext_t));

    ctx->state = BMS_STATE_INIT;
    ctx->role = BMS_ROLE_STANDALONE;
    ctx->can_sid = BMS_CAN_MASTER_SID;
    ctx->telemetry.total_capacity_mah = BMS_NOMINAL_CAPACITY_MAH;
    ctx->telemetry.soc_pct = 100;
    ctx->telemetry.soh_pct = 100;

    strncpy(ctx->serial_number, "6495-SPB24-DVC24-006", sizeof(ctx->serial_number) - 1);

    ctx->state = BMS_STATE_STANDBY;
}

void bms_core_check_protections(BmsContext_t *ctx) {
    BmsTelemetry_t *t = &ctx->telemetry;
    BmsFaultFlags_t *f = &ctx->faults;

    /* 1. Cell Voltage Protection */
    if (t->max_cell_mv >= BMS_CELL_OVP_MV) {
        f->bits.cell_ovp = 1;
    } else if (t->max_cell_mv <= BMS_CELL_OVP_RELEASE_MV) {
        f->bits.cell_ovp = 0;
    }

    if (t->min_cell_mv <= BMS_CELL_UVC_CUTOFF_MV) {
        f->bits.cell_uvp = 1;
    }

    /* 2. Temperature Protection */
    if (t->max_temp_c >= BMS_DSG_OT_PROTECT_C) {
        f->bits.dsg_otp = 1;
    } else {
        f->bits.dsg_otp = 0;
    }

    if (t->mos_temp_c >= BMS_MOS_OT_PROTECT_C) {
        f->bits.mos_otp = 1;
    } else {
        f->bits.mos_otp = 0;
    }

    /* 3. Auxiliary ACC Overload (> 2A without DIN active) */
    if (!ctx->switches.din_active && t->current_ma < -2200) {
        f->bits.aux_overload = 1;
    } else {
        f->bits.aux_overload = 0;
    }
}

void bms_core_update_balancing(BmsContext_t *ctx) {
    BmsTelemetry_t *t = &ctx->telemetry;
    uint32_t mask = 0;

    /* Only balance during charging or standby when cells are near full */
    if (t->max_cell_mv >= BMS_CELL_BALANCE_START_MV) {
        for (uint8_t i = 0; i < BMS_SERIES_CELLS; i++) {
            if (t->cell_mv[i] > (t->min_cell_mv + BMS_CELL_BALANCE_DELTA_MV)) {
                mask |= (1UL << i);
            }
        }
    }

    t->balance_mask = mask;
    dvc1124_set_balancing(mask);
}

void bms_core_calculate_soc(BmsContext_t *ctx) {
    BmsTelemetry_t *t = &ctx->telemetry;

    /* Simple linear interpolation between nominal and cutoff for baseline */
    if (t->min_cell_mv >= BMS_CELL_OVP_RELEASE_MV) {
        t->soc_pct = 100;
    } else if (t->min_cell_mv <= BMS_CELL_UVC_CUTOFF_MV) {
        t->soc_pct = 0;
    } else {
        uint32_t range = BMS_CELL_OVP_RELEASE_MV - BMS_CELL_UVC_CUTOFF_MV;
        uint32_t delta = t->min_cell_mv - BMS_CELL_UVC_CUTOFF_MV;
        t->soc_pct = (uint8_t)((delta * 100) / range);
    }
}

void bms_core_process_10ms_tick(BmsContext_t *ctx) {
    /* Read analog signals from DVC1124 AFE */
    dvc1124_read_pack_current(&ctx->telemetry.current_ma);
}

void bms_core_process_100ms_tick(BmsContext_t *ctx) {
    BmsTelemetry_t *t = &ctx->telemetry;

    /* Read cell voltages */
    if (dvc1124_read_cell_voltages(t->cell_mv, BMS_SERIES_CELLS)) {
        t->min_cell_mv = 0xFFFF;
        t->max_cell_mv = 0;
        uint32_t sum = 0;

        for (uint8_t i = 0; i < BMS_SERIES_CELLS; i++) {
            sum += t->cell_mv[i];
            if (t->cell_mv[i] < t->min_cell_mv) {
                t->min_cell_mv = t->cell_mv[i];
                t->min_cell_idx = i;
            }
            if (t->cell_mv[i] > t->max_cell_mv) {
                t->max_cell_mv = t->cell_mv[i];
                t->max_cell_idx = i;
            }
        }
        t->pack_voltage_mv = sum;
        t->cell_delta_mv = t->max_cell_mv - t->min_cell_mv;
    }

    /* Read temperatures */
    dvc1124_read_temperatures(t->temp_c, BMS_NTC_TEMP_SENSORS, &t->mos_temp_c);

    /* Check discrete control inputs */
    ctx->switches.acc_wake_active = bms_hal_read_acc_wake();
    ctx->switches.cin_active = bms_hal_read_cin_detect();
    ctx->switches.din_active = bms_hal_read_din_detect();

    /* Safety Protection Checks */
    bms_core_check_protections(ctx);

    /* State Machine Execution */
    switch (ctx->state) {
        case BMS_STATE_STANDBY:
            if (ctx->faults.all != 0) {
                ctx->state = BMS_STATE_FAULT;
            } else if (ctx->switches.cin_active) {
                ctx->state = BMS_STATE_CHARGE;
            } else if (ctx->switches.acc_wake_active && ctx->switches.din_active) {
                ctx->state = BMS_STATE_DISCHARGE;
            }
            bms_hal_set_chg_mos(false);
            bms_hal_set_dsg_mos(false);
            break;

        case BMS_STATE_CHARGE:
            if (ctx->faults.bits.cell_ovp || !ctx->switches.cin_active) {
                ctx->state = BMS_STATE_STANDBY;
                bms_hal_set_chg_mos(false);
            } else {
                bms_hal_set_chg_mos(true);
                bms_core_update_balancing(ctx);
            }
            break;

        case BMS_STATE_DISCHARGE:
            if (ctx->faults.bits.cell_uvp || ctx->faults.bits.aux_overload || !ctx->switches.din_active) {
                ctx->state = BMS_STATE_STANDBY;
                bms_hal_set_dsg_mos(false);
            } else {
                bms_hal_set_dsg_mos(true);
            }
            break;

        case BMS_STATE_FAULT:
            bms_hal_set_chg_mos(false);
            bms_hal_set_dsg_mos(false);
            if (ctx->faults.all == 0) {
                ctx->state = BMS_STATE_STANDBY;
            }
            break;

        default:
            ctx->state = BMS_STATE_STANDBY;
            break;
    }
}

void bms_core_process_1s_tick(BmsContext_t *ctx) {
    ctx->uptime_seconds++;
    bms_core_calculate_soc(ctx);
}
