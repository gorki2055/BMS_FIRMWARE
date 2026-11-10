/**
 * @file bms_core.c
 * @brief Core State Machine, Protection Supervisor, Pre-Charge, Body-Diode Protection & Balancing
 */

#include "bms_core.h"
#include "bms_config.h"
#include "bms_hal.h"
#include "dvc1124_afe.h"
#include "bms_ocv.h"
#include "bms_storage.h"
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
    ctx->precharge_bus_ready = true; /* Default ready unless capacitive load hold-off simulated */

    /* Initialize default protection thresholds from calibrated configuration */
    ctx->limits.cell_ovp_mv   = BMS_CELL_OVP_MV;
    ctx->limits.cell_uvp_mv   = BMS_CELL_UVC_CUTOFF_MV;
    ctx->limits.chg_ocp_ma    = BMS_MAX_CHARGE_CURRENT_A * 1000;
    ctx->limits.dsg_ocp_ma    = BMS_MAX_CONTINUOUS_DSG_A * 1000;
    ctx->limits.ot_protect_c  = BMS_DSG_OT_PROTECT_C;
    ctx->limits.ut_protect_c  = BMS_DSG_UT_PROTECT_C;

    /* Load per-cell calibration gain multipliers (FUN_08016000) & verify MCU 96-bit UID lock (FUN_08017b3c) */
    (void)bms_storage_load_cell_cal(ctx->cell_cal_gain);
    (void)bms_storage_verify_uid_lock(ctx);

    strncpy(ctx->serial_number, "6495-SPB24-DVC24-006", sizeof(ctx->serial_number) - 1);

    bms_soc_estimator_init(ctx);

    ctx->state = BMS_STATE_STANDBY;
}

/**
 * @brief Scale raw cell voltages by per-cell calibration factors from EEPROM 0x0060 (FUN_08016000)
 */
void bms_core_apply_cell_calibration(BmsContext_t *ctx) {
    if (!ctx) return;
    BmsTelemetry_t *t = &ctx->telemetry;
    t->min_cell_mv = 0xFFFFU;
    t->max_cell_mv = 0U;
    uint32_t sum = 0U;

    for (uint8_t i = 0; i < BMS_SERIES_CELLS; i++) {
        float gain = ctx->cell_cal_gain[i];
        if (gain < 0.80f || gain > 1.20f) {
            gain = 1.0f;
        }
        uint32_t scaled = (uint32_t)(((float)t->cell_mv[i] * gain) + 0.5f);
        if (scaled > 65535U) scaled = 65535U;
        t->cell_mv[i] = (uint16_t)scaled;

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
    t->cell_delta_mv = (t->max_cell_mv >= t->min_cell_mv) ? (uint16_t)(t->max_cell_mv - t->min_cell_mv) : 0U;
}

/**
 * @brief Merge AFE NTC readings with MCU internal 12-bit ADC1..ADC4 & mask open-wire sensors (FUN_0801f8ac)
 */
void bms_core_update_hybrid_temperatures(BmsContext_t *ctx) {
    if (!ctx) return;
    BmsTelemetry_t *t = &ctx->telemetry;

    /* Poll MCU internal 12-bit ADC1/ADC2 for MOSFET (ch 1) & Connector (ch 2) thermistors */
    uint16_t raw_mos_adc  = bms_hal_read_internal_adc(1, 1);
    uint16_t raw_conn_adc = bms_hal_read_internal_adc(1, 2);

    /* Convert 12-bit ADC counts (2048 counts -> 25°C, ~32 counts/°C) */
    t->mos_temp_c       = (int16_t)(25 + (((int32_t)raw_mos_adc - 2048) / 32));
    t->connector_temp_c = (int16_t)(25 + (((int32_t)raw_conn_adc - 2048) / 32));

    t->min_temp_c = 127;
    t->max_temp_c = -128;

    for (uint8_t i = 0; i < BMS_NTC_TEMP_SENSORS; i++) {
        /* Open-wire sensor fault masking (FUN_0801f8ac lines 25253-25266):
         * If an NTC reads open-circuit (<= -35°C) while MOSFET temp is > 10°C warmer,
         * substitute MOSFET temperature to prevent false UTP trips. */
        if (t->temp_c[i] <= -35 && (t->mos_temp_c - t->temp_c[i]) > 10) {
            t->temp_c[i] = t->mos_temp_c;
        }
        if (t->temp_c[i] < t->min_temp_c) t->min_temp_c = t->temp_c[i];
        if (t->temp_c[i] > t->max_temp_c) t->max_temp_c = t->temp_c[i];
    }
}

/**
 * @brief Drive CHG and DSG MOSFETs with body-diode conduction promotion (FUN_0801f580)
 * @note If one MOSFET is OFF (e.g., CHG_MOS off during OVP or DISCHARGE mode) while current
 *       exceeds BMS_BODY_DIODE_PROTECT_MA in the opposite permitted direction, the inhibited
 *       MOSFET is promoted ON to prevent thermal destruction of its parasitic body diode.
 */
void bms_core_apply_mosfet_control(BmsContext_t *ctx, bool base_chg_en, bool base_dsg_en) {
    if (!ctx) return;

    bool final_chg = base_chg_en;
    bool final_dsg = base_dsg_en;

    /* If DSG is enabled and discharge current exceeds -1.5A, promote CHG MOS ON */
    if (base_dsg_en && !base_chg_en && ctx->telemetry.current_ma <= -BMS_BODY_DIODE_PROTECT_MA) {
        final_chg = true;
    }

    /* If CHG is enabled and charge current exceeds +1.5A, promote DSG MOS ON */
    if (base_chg_en && !base_dsg_en && ctx->telemetry.current_ma >= BMS_BODY_DIODE_PROTECT_MA) {
        final_dsg = true;
    }

    ctx->switches.chg_mos_on = final_chg;
    ctx->switches.dsg_mos_on = final_dsg;
    bms_hal_set_chg_mos(final_chg);
    bms_hal_set_dsg_mos(final_dsg);
}

void bms_core_check_protections(BmsContext_t *ctx) {
    BmsTelemetry_t *t = &ctx->telemetry;
    BmsFaultFlags_t *f = &ctx->faults;

    /* 1. Cell Voltage Protection */
    if (t->max_cell_mv >= BMS_CELL_OVP_MV) {
        if (!f->bits.cell_ovp) {
            f->bits.cell_ovp = 1;
            (void)bms_storage_log_event(BMS_EVENT_PACK_OVP, ctx);
        }
    } else if (t->max_cell_mv <= BMS_CELL_OVP_RELEASE_MV) {
        f->bits.cell_ovp = 0;
    }

    if (t->min_cell_mv > 0U && t->min_cell_mv <= BMS_CELL_UVC_CUTOFF_MV) {
        f->bits.cell_uvp = 1;
    }

    /* 2. Temperature Protection (Reconstructed from FUN_0800db98, FUN_0800e5f0 & FUN_08017104)
     *    - Charge OTP:    Trips >= 55°C (BMS_CHG_OT_PROTECT_C), releases <= 45°C (-10°C hysteresis)
     *    - Charge UTP:    Trips <=  0°C (BMS_CHG_UT_PROTECT_C), releases >= 10°C (+10°C hysteresis)
     *    - Discharge OTP: Trips >= 65°C (BMS_DSG_OT_PROTECT_C), releases <= 55°C (-10°C hysteresis)
     *    - Discharge UTP: Trips <= -20°C (BMS_DSG_UT_PROTECT_C), releases >= -10°C (+10°C hysteresis)
     *    - MOSFET OTP:    Trips >= 85°C (BMS_MOS_OT_PROTECT_C), releases <= 75°C (-10°C hysteresis)
     */
    if (ctx->state == BMS_STATE_CHARGE || ctx->switches.cin_active || t->current_ma > 0) {
        if (t->max_temp_c >= BMS_CHG_OT_PROTECT_C) {
            if (!f->bits.chg_otp) {
                f->bits.chg_otp = 1;
                (void)bms_storage_log_event(BMS_EVENT_TEMP_FAULT, ctx);
            }
        } else if (t->max_temp_c <= (BMS_CHG_OT_PROTECT_C - 10)) {
            f->bits.chg_otp = 0;
        }

        if (t->min_temp_c <= BMS_CHG_UT_PROTECT_C) {
            if (!f->bits.chg_utp) {
                f->bits.chg_utp = 1;
                (void)bms_storage_log_event(BMS_EVENT_TEMP_FAULT, ctx);
            }
        } else if (t->min_temp_c >= (BMS_CHG_UT_PROTECT_C + 10)) {
            f->bits.chg_utp = 0;
        }
    } else {
        if (t->max_temp_c <= (BMS_CHG_OT_PROTECT_C - 10)) f->bits.chg_otp = 0;
        if (t->min_temp_c >= (BMS_CHG_UT_PROTECT_C + 10)) f->bits.chg_utp = 0;
    }

    if (t->max_temp_c >= BMS_DSG_OT_PROTECT_C) {
        if (!f->bits.dsg_otp) {
            f->bits.dsg_otp = 1;
            (void)bms_storage_log_event(BMS_EVENT_TEMP_FAULT, ctx);
        }
    } else if (t->max_temp_c <= (BMS_DSG_OT_PROTECT_C - 10)) {
        f->bits.dsg_otp = 0;
    }

    if (t->min_temp_c <= BMS_DSG_UT_PROTECT_C) {
        if (!f->bits.dsg_utp) {
            f->bits.dsg_utp = 1;
            (void)bms_storage_log_event(BMS_EVENT_TEMP_FAULT, ctx);
        }
    } else if (t->min_temp_c >= (BMS_DSG_UT_PROTECT_C + 10)) {
        f->bits.dsg_utp = 0;
    }

    if (t->mos_temp_c >= BMS_MOS_OT_PROTECT_C) {
        if (!f->bits.mos_otp) {
            f->bits.mos_otp = 1;
            (void)bms_storage_log_event(BMS_EVENT_TEMP_FAULT, ctx);
        }
    } else if (t->mos_temp_c <= (BMS_MOS_OT_PROTECT_C - 10)) {
        f->bits.mos_otp = 0;
    }

    /* 3. Auxiliary ACC Overload (> 2A without DIN active) */
    if (!ctx->switches.din_active && t->current_ma < -2200) {
        f->bits.aux_overload = 1;
    } else {
        f->bits.aux_overload = 0;
    }
}

/**
 * @brief Update 3-phase odd/even interleaved cell balancing (FUN_08008af4)
 */
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
    dvc1124_set_balancing_phased(mask, ctx->balance_phase);
    ctx->balance_phase = (uint8_t)((ctx->balance_phase + 1U) % 3U);
}

void bms_core_calculate_soc(BmsContext_t *ctx) {
    if (!ctx) return;

    /* Hybrid Coulomb Counting under load + 2D Chemical OCV Recalibration at rest */
    bms_soc_estimator_update(ctx, 1000);
}

/**
 * @brief Dynamic State of Health (SOH) calculation
 * @note Reconstructed directly from FUN_080207fc (Flash 0x080207FC):
 *       SOH = max(0.0f, 100.0f - (cycle_count * 0.02f))
 */
void bms_core_calculate_soh(BmsContext_t *ctx) {
    if (!ctx) return;
    BmsTelemetry_t *t = &ctx->telemetry;

    float soh = 100.0f - ((float)t->cycle_count * BMS_SOH_DEGRADE_PER_CYCLE);
    if (soh < 0.0f) {
        soh = 0.0f;
    } else if (soh > 100.0f) {
        soh = 100.0f;
    }

    t->soh_pct = (uint8_t)soh;

    /* Dynamically adjust usable pack capacity based on degraded SOH */
    t->total_capacity_mah = (BMS_NOMINAL_CAPACITY_MAH * (uint32_t)t->soh_pct) / 100;
    t->remaining_mah = (t->total_capacity_mah * (uint32_t)t->soc_pct) / 100;
}

void bms_core_record_cycles(BmsContext_t *ctx, uint16_t new_cycle_count) {
    if (!ctx) return;
    ctx->telemetry.cycle_count = new_cycle_count;
    bms_core_calculate_soh(ctx);
}

/**
 * @brief Enter Deep-Sleep (PWR STOP) with RTC wake-up alarm (FUN_080161bc / FUN_0801f7b8)
 */
void bms_core_enter_deep_sleep(BmsContext_t *ctx, uint32_t wake_alarm_sec) {
    if (!ctx) return;
    bms_core_apply_mosfet_control(ctx, false, false);
    ctx->switches.precharge_mos_on = false;
    bms_hal_set_precharge_mos(false);
    ctx->state = BMS_STATE_SLEEP;
    bms_hal_enter_stop_sleep(wake_alarm_sec);
}

/**
 * @brief Restore clocks and transition back to STANDBY after RTC/EXTI wake-up (FUN_08016360)
 */
void bms_core_wake_from_sleep(BmsContext_t *ctx) {
    if (!ctx) return;
    bms_hal_restore_clocks_after_wake();
    ctx->state = BMS_STATE_STANDBY;
}

/**
 * @brief Compute 5-stage LED capacity bar-graph level and blink state (FUN_0800fc48 @ 0x0800FC48)
 */
uint8_t bms_core_get_led_bar_stage(const BmsContext_t *ctx, bool *blink_out) {
    if (blink_out) *blink_out = false;
    if (!ctx) return 0;

    uint8_t soc = ctx->telemetry.soc_pct;
    bool is_discharging = (ctx->state == BMS_STATE_DISCHARGE || ctx->telemetry.current_ma < -100);

    if (is_discharging && soc < 10U) {
        if (blink_out) *blink_out = true; /* Low-battery <10% blink alert */
        return 1U;
    }
    if (soc < 20U) return 1U;
    if (soc < 40U) return 2U;
    if (soc < 60U) return 3U;
    if (soc < 80U) return 4U;
    return 5U;
}

void bms_core_process_10ms_tick(BmsContext_t *ctx) {
    /* Read analog signals from DVC1124 AFE */
    dvc1124_read_pack_current(&ctx->telemetry.current_ma);
}

void bms_core_process_100ms_tick(BmsContext_t *ctx) {
    BmsTelemetry_t *t = &ctx->telemetry;

    /* Read cell voltages and apply per-cell gain calibration (FUN_08016000) */
    if (dvc1124_read_cell_voltages(t->cell_mv, BMS_SERIES_CELLS)) {
        bms_core_apply_cell_calibration(ctx);
    }

    /* Read AFE temperatures and fuse with MCU internal 12-bit ADC1..ADC4 (FUN_0801f8ac) */
    dvc1124_read_temperatures(t->temp_c, BMS_NTC_TEMP_SENSORS, &t->mos_temp_c);
    bms_core_update_hybrid_temperatures(ctx);

    /* Check discrete control inputs */
    ctx->switches.acc_wake_active = bms_hal_read_acc_wake();
    ctx->switches.cin_active = bms_hal_read_cin_detect();
    ctx->switches.din_active = bms_hal_read_din_detect();

    /* Safety Protection Checks */
    bms_core_check_protections(ctx);

    /* State Machine Execution */
    switch (ctx->state) {
        case BMS_STATE_STANDBY:
            ctx->precharge_ticks = 0;
            ctx->switches.precharge_mos_on = false;
            bms_hal_set_precharge_mos(false);
            bms_core_apply_mosfet_control(ctx, false, false);

            if (ctx->faults.all != 0) {
                ctx->state = BMS_STATE_FAULT;
            } else if (ctx->switches.cin_active) {
                ctx->state = BMS_STATE_CHARGE;
            } else if (ctx->switches.acc_wake_active && ctx->switches.din_active && !ctx->door_lock_prohibit_dsg) {
                /* Enter timed pre-charge sequence (FUN_0801647c) */
                ctx->state = BMS_STATE_PRECHARGE;
                ctx->precharge_ticks = 0;
                ctx->switches.precharge_mos_on = true;
                bms_hal_set_precharge_mos(true);
            }
            break;

        case BMS_STATE_PRECHARGE:
            /* Timed pre-charge monitoring (FUN_0801647c @ 0x0801647C) */
            ctx->precharge_ticks++;
            if (ctx->faults.all != 0) {
                ctx->switches.precharge_mos_on = false;
                bms_hal_set_precharge_mos(false);
                bms_core_apply_mosfet_control(ctx, false, false);
                ctx->state = BMS_STATE_FAULT;
            } else if (ctx->precharge_bus_ready) {
                /* Bus voltage rose within timeout: close main DSG MOSFET & release pre-charge */
                ctx->switches.precharge_mos_on = false;
                bms_hal_set_precharge_mos(false);
                bms_core_apply_mosfet_control(ctx, false, true);
                ctx->state = BMS_STATE_DISCHARGE;
            } else if (ctx->precharge_ticks >= BMS_PRECHARGE_TIMEOUT_TICKS) {
                /* Pre-charge failed after 10 ticks: open MOSFETs and log Fault 0xBE */
                ctx->switches.precharge_mos_on = false;
                bms_hal_set_precharge_mos(false);
                bms_core_apply_mosfet_control(ctx, false, false);
                ctx->faults.bits.precharge_fail = 1;
                (void)bms_storage_log_event(BMS_EVENT_PRECHARGE_FAIL, ctx);
                ctx->state = BMS_STATE_FAULT;
            }
            break;

        case BMS_STATE_CHARGE:
            if (ctx->faults.bits.cell_ovp || !ctx->switches.cin_active) {
                ctx->state = BMS_STATE_STANDBY;
                bms_core_apply_mosfet_control(ctx, false, false);
            } else {
                bms_core_apply_mosfet_control(ctx, true, false);
                bms_core_update_balancing(ctx);
            }
            break;

        case BMS_STATE_DISCHARGE:
            if (ctx->faults.bits.cell_uvp || ctx->faults.bits.aux_overload ||
                !ctx->switches.din_active || ctx->door_lock_prohibit_dsg) {
                ctx->state = BMS_STATE_STANDBY;
                bms_core_apply_mosfet_control(ctx, false, false);
            } else {
                bms_core_apply_mosfet_control(ctx, false, true);
            }
            break;

        case BMS_STATE_FAULT:
            ctx->switches.precharge_mos_on = false;
            bms_hal_set_precharge_mos(false);
            bms_core_apply_mosfet_control(ctx, false, false);
            if (ctx->faults.all == 0) {
                ctx->state = BMS_STATE_STANDBY;
            }
            break;

        case BMS_STATE_SLEEP:
            bms_core_apply_mosfet_control(ctx, false, false);
            break;

        default:
            ctx->state = BMS_STATE_STANDBY;
            break;
    }
}

void bms_core_process_1s_tick(BmsContext_t *ctx) {
    ctx->uptime_seconds++;
    bms_core_calculate_soc(ctx);
    bms_core_calculate_soh(ctx);

    /* Apply parasitic self-discharge every 75 rest seconds (FUN_0801fc8c) */
    if (ctx->soc_est.rest_duration_sec > 0U &&
        (ctx->soc_est.rest_duration_sec % BMS_SELF_DSG_INTERVAL_SEC) == 0U) {
        (void)bms_ocv_apply_self_discharge(ctx);
    }
}
