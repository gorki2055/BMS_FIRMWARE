/**
 * @file bms_ocv.c
 * @brief 2D Open Circuit Voltage (OCV) vs. SOC & Temperature Engine
 * @note Reconstructed directly from decompiled routines:
 *       - FUN_08010654 (Flash 0x08010654)
 *       - FUN_080103c8 (Flash 0x080103c8)
 *       - Scatterload Decompression Tables (Flash 0x08023184 -> SRAM 0x20020572, 0x20020720)
 */

#include "bms_ocv.h"
#include "bms_config.h"

/* ========================================================================== */
/* 21S 70Ah NCM Battery Chemistry OCV Baseline at 25°C                        */
/* Breakpoints match factory calibrated limits:                               */
/* 100% = 4185mV, 50% = 3608mV, 5% = 2831mV, 0% = 2621mV                      */
/* ========================================================================== */
static const uint16_t s_ncm_ocv_table_mv[BMS_OCV_SOC_POINTS] = {
    4185,  /* 100% SOC - Hard Over-Voltage Cutoff */
    4100,  /*  95% SOC - OVP Release */
    4040,  /*  90% SOC */
    3980,  /*  85% SOC */
    3920,  /*  80% SOC */
    3870,  /*  75% SOC */
    3820,  /*  70% SOC */
    3770,  /*  65% SOC */
    3720,  /*  60% SOC */
    3670,  /*  55% SOC */
    3608,  /*  50% SOC - Calibrated Nominal Cell Voltage */
    3560,  /*  45% SOC */
    3510,  /*  40% SOC */
    3460,  /*  35% SOC */
    3400,  /*  30% SOC */
    3340,  /*  25% SOC */
    3260,  /*  20% SOC */
    3160,  /*  15% SOC */
    3020,  /*  10% SOC */
    2831,  /*   5% SOC - Calibrated Under-Voltage Warning */
    2621   /*   0% SOC - Calibrated Under-Voltage Cutoff */
};

/* ========================================================================== */
/* Table 1: Chemical Capacity Availability Derating Matrix (21 x 12)          */
/* Extracted from Scatterload Decompression (SRAM 0x20020572, FUN_08010654)    */
/* Rows: SOC [100% down to 0% in 5% steps]                                    */
/* Cols: Temp [<-20, -10, 0, 10, 15, 25, 40, 45, 50, 55, 60, >=60 °C]        */
/* Unit: 0.1 Ah (scaled by 0.1 in FUN_08010654)                              */
/* ========================================================================== */
static const uint8_t s_capacity_avail_matrix_21x12[BMS_OCV_SOC_POINTS][BMS_OCV_TEMP_BANDS_AVAIL] = {
    /* 100% */ { 0,  5,  5,  7, 15, 20, 20, 20, 15, 10,  5,  0 },
    /*  95% */ { 0,  5,  5,  7, 15, 20, 20, 20, 15, 10,  5,  0 },
    /*  90% */ { 0,  5,  5,  7, 15, 20, 20, 20, 15, 10,  5,  0 },
    /*  85% */ { 0,  5,  5,  7, 15, 20, 20, 20, 15, 10,  5,  0 },
    /*  80% */ { 0,  5,  5,  7, 12, 20, 20, 20, 12, 10,  5,  0 },
    /*  75% */ { 0,  5,  5,  7, 12, 20, 20, 20, 12, 10,  5,  0 },
    /*  70% */ { 0,  5,  5,  7, 12, 20, 20, 20, 12, 10,  5,  0 },
    /*  65% */ { 0,  5,  5,  7, 10, 20, 20, 20, 12, 10,  5,  0 },
    /*  60% */ { 0,  5,  5,  7, 10, 15, 20, 20, 12, 10,  5,  0 },
    /*  55% */ { 0,  5,  5,  7, 10, 15, 20, 20,  5,  5,  5,  0 },
    /*  50% */ { 0,  5,  5,  7, 10, 15, 20, 15,  5,  5,  5,  0 },
    /*  45% */ { 0,  2,  2,  4, 10, 12, 15, 15,  5,  5,  2,  0 },
    /*  40% */ { 0,  2,  2,  4, 10, 12, 15, 12,  5,  5,  2,  0 },
    /*  35% */ { 0,  2,  2,  4, 10, 12, 12, 10,  5,  5,  2,  0 },
    /*  30% */ { 0,  2,  2,  4,  7, 10, 10,  5,  3,  2,  2,  0 },
    /*  25% */ { 0,  2,  2,  4,  7, 10, 10,  5,  3,  2,  2,  0 },
    /*  20% */ { 0,  2,  2,  4,  7, 10, 10,  5,  3,  2,  2,  0 },
    /*  15% */ { 0,  2,  2,  4,  7, 10, 10,  5,  3,  2,  2,  0 },
    /*  10% */ { 0,  2,  2,  2,  5,  5,  5,  5,  3,  2,  2,  0 },
    /*   5% */ { 0,  2,  2,  2,  5,  5,  5,  5,  3,  2,  2,  0 },
    /*   0% */ { 0,  2,  2,  2,  5,  5,  5,  5,  3,  2,  2,  0 }
};

/* ========================================================================== */
/* Table 2: Thermal Voltage Relaxation Derating Matrix (21 x 13)              */
/* Extracted from Scatterload Decompression (SRAM 0x20020720, FUN_080103c8)    */
/* Rows: SOC [100% down to 0% in 5% steps]                                    */
/* Cols: Temp [<0, 5, 10, 15, 20, 25, 30, 35, 40, 44, 46, 51, >=51 °C]       */
/* Scale: 0.01 in FUN_080103c8                                               */
/* ========================================================================== */
static const uint8_t s_thermal_relax_matrix_21x13[BMS_OCV_SOC_POINTS][BMS_OCV_TEMP_BANDS_THERMAL] = {
    /* 100% */ { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    /*  95% */ { 0, 10, 10, 18, 18, 30, 30, 30, 20, 18, 10, 10,  0 },
    /*  90% */ { 0, 10, 10, 18, 18, 30, 30, 30, 20, 18, 10, 10,  0 },
    /*  85% */ { 0, 10, 10, 30, 30, 30, 30, 30, 30, 30, 20, 10,  0 },
    /*  80% */ { 0, 10, 10, 30, 30, 30, 30, 30, 30, 30, 20, 10,  0 },
    /*  75% */ { 0, 10, 20, 30, 30, 30, 40, 40, 40, 30, 20, 10,  0 },
    /*  70% */ { 0, 10, 20, 30, 30, 30, 40, 40, 40, 30, 20, 10,  0 },
    /*  65% */ { 0, 10, 20, 30, 30, 30, 50, 50, 50, 40, 30, 10,  0 },
    /*  60% */ { 0, 10, 20, 30, 30, 50, 50, 50, 50, 40, 30, 10,  0 },
    /*  55% */ { 0, 10, 20, 30, 30, 50, 50, 50, 50, 40, 30, 10,  0 },
    /*  50% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 40, 30, 10,  0 },
    /*  45% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 10,  0 },
    /*  40% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 10,  0 },
    /*  35% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 10,  0 },
    /*  30% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 10,  0 },
    /*  25% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 20,  0 },
    /*  20% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 20,  0 },
    /*  15% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 20,  0 },
    /*  10% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 20,  0 },
    /*   5% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 20,  0 },
    /*   0% */ { 0, 20, 20, 30, 40, 50, 50, 50, 50, 50, 40, 20,  0 }
};

/**
 * @brief Map temperature to column index in Table 1 (FUN_08010654 ladder)
 */
static uint8_t get_temp_col_avail(int16_t temp_c) {
    if (temp_c < -20) return 0;
    if (temp_c < -10) return 1;
    if (temp_c < 0)   return 2;
    if (temp_c < 10)  return 3;
    if (temp_c < 15)  return 4;
    if (temp_c < 25)  return 5;
    if (temp_c < 40)  return 6;
    if (temp_c < 45)  return 7;
    if (temp_c < 50)  return 8;
    if (temp_c < 55)  return 9;
    if (temp_c < 60)  return 10;
    return 11;
}

/**
 * @brief Map temperature to column index in Table 2 (FUN_080103c8 ladder)
 */
static uint8_t get_temp_col_thermal(int16_t temp_c) {
    if (temp_c < 0)  return 0;
    if (temp_c < 5)  return 1;
    if (temp_c < 10) return 2;
    if (temp_c < 15) return 3;
    if (temp_c < 20) return 4;
    if (temp_c < 25) return 5;
    if (temp_c < 30) return 6;
    if (temp_c < 35) return 7;
    if (temp_c < 40) return 8;
    if (temp_c < 44) return 9;
    if (temp_c < 46) return 10;
    if (temp_c < 51) return 11;
    return 12;
}

/**
 * @brief Map SOC percentage (0-100) to row index (0-20)
 */
static uint8_t get_soc_row(uint8_t soc_pct) {
    if (soc_pct >= 100) return 0;
    uint8_t inv = 100 - soc_pct;
    uint8_t row = inv / 5;
    if (row >= BMS_OCV_SOC_POINTS) row = BMS_OCV_SOC_POINTS - 1;
    return row;
}

float bms_ocv_get_capacity_derate(uint8_t soc_pct, int16_t temp_c) {
    uint8_t row = get_soc_row(soc_pct);
    uint8_t col = get_temp_col_avail(temp_c);
    uint8_t raw_val = s_capacity_avail_matrix_21x12[row][col];
    /* FUN_08010654 scales entry by 0.1 (0.1 Ah units) */
    return (float)raw_val * 0.1f;
}

float bms_ocv_get_thermal_derate(uint8_t soc_pct, int16_t temp_c) {
    uint8_t row = get_soc_row(soc_pct);
    uint8_t col = get_temp_col_thermal(temp_c);
    uint8_t raw_val = s_thermal_relax_matrix_21x13[row][col];
    /* FUN_080103c8 scales entry by 0.01 */
    return (float)raw_val * 0.01f;
}

uint16_t bms_ocv_lookup_voltage(uint8_t soc_pct, int16_t temp_c) {
    if (soc_pct >= 100) return s_ncm_ocv_table_mv[0];
    if (soc_pct == 0)   return s_ncm_ocv_table_mv[BMS_OCV_SOC_POINTS - 1];

    uint8_t row = get_soc_row(soc_pct);
    uint8_t next_row = (row < BMS_OCV_SOC_POINTS - 1) ? row + 1 : row;

    uint8_t upper_soc = 100 - (row * 5);
    uint8_t lower_soc = (upper_soc >= 5) ? upper_soc - 5 : 0;

    uint16_t v_high = s_ncm_ocv_table_mv[row];
    uint16_t v_low  = s_ncm_ocv_table_mv[next_row];

    /* Linear interpolation between the two 5% brackets */
    uint16_t v_interp = v_low + (uint16_t)(((uint32_t)(v_high - v_low) * (soc_pct - lower_soc)) / 5);

    /* Temperature relaxation compensation from Table 2 */
    float thermal_derate = bms_ocv_get_thermal_derate(soc_pct, temp_c);
    int16_t temp_offset_mv = (int16_t)(thermal_derate * 10.0f);

    if (temp_c < 25) {
        v_interp -= temp_offset_mv;
    } else {
        v_interp += temp_offset_mv;
    }

    return v_interp;
}

uint8_t bms_ocv_lookup_soc(uint16_t cell_mv, int16_t temp_c) {
    /* Clamping to hard boundary limits */
    if (cell_mv >= s_ncm_ocv_table_mv[0]) return 100;
    if (cell_mv <= s_ncm_ocv_table_mv[BMS_OCV_SOC_POINTS - 1]) return 0;

    /* Temperature compensation on lookup voltage */
    int16_t temp_shift = 0;
    if (temp_c < 20) {
        /* Cold shift: Cell voltage drops ~1.5mV per degree below 20°C */
        temp_shift = (20 - temp_c) * 2;
    }

    uint16_t effective_mv = cell_mv + temp_shift;
    if (effective_mv > s_ncm_ocv_table_mv[0]) effective_mv = s_ncm_ocv_table_mv[0];

    /* Binary search or linear scan across 21 points */
    for (uint8_t i = 0; i < BMS_OCV_SOC_POINTS - 1; i++) {
        uint16_t v_upper = s_ncm_ocv_table_mv[i];
        uint16_t v_lower = s_ncm_ocv_table_mv[i + 1];

        if (effective_mv <= v_upper && effective_mv >= v_lower) {
            uint8_t soc_upper = 100 - (i * 5);
            uint8_t soc_lower = soc_upper - 5;
            uint32_t v_range = v_upper - v_lower;

            if (v_range == 0) return soc_lower;

            uint32_t delta_v = effective_mv - v_lower;
            uint8_t interp_soc = (uint8_t)(soc_lower + ((delta_v * 5) / v_range));

            if (interp_soc > 100) interp_soc = 100;
            return interp_soc;
        }
    }

    return 0;
}

/* ========================================================================== */
/* Hybrid SOC Estimator: Coulomb Counting + 2D OCV Quiescent Fusion          */
/* ========================================================================== */

void bms_soc_estimator_init(BmsContext_t *ctx) {
    if (!ctx) return;
    BmsTelemetry_t *t = &ctx->telemetry;
    BmsSocEstimator_t *est = &ctx->soc_est;

    uint8_t ocv_soc = bms_ocv_lookup_soc(t->min_cell_mv, t->min_temp_c);
    if (ocv_soc == 0 && t->min_cell_mv == 0) {
        /* Default to 100% on cold uninitialized boot */
        ocv_soc = 100;
    }

    t->soc_pct = ocv_soc;
    est->last_ocv_soc = ocv_soc;
    est->is_relaxed = true;
    est->accum_coulombs_mas = 0;
    est->rest_duration_sec = BMS_OCV_RELAX_DURATION_SEC;

    t->remaining_mah = (t->total_capacity_mah * (uint32_t)ocv_soc) / 100;
}

void bms_soc_estimator_update(BmsContext_t *ctx, uint32_t delta_ms) {
    if (!ctx || delta_ms == 0) return;
    BmsTelemetry_t *t = &ctx->telemetry;
    BmsSocEstimator_t *est = &ctx->soc_est;

    int32_t current_ma = t->current_ma;
    int32_t abs_curr = (current_ma < 0) ? -current_ma : current_ma;

    /* Check for polarization relaxation (quiescent current < 800mA from Flash 0x08020858) */
    if (abs_curr < BMS_OCV_QUIESCENT_CURRENT_MA) {
        est->rest_duration_sec += (delta_ms / 1000);
        if (est->rest_duration_sec >= BMS_OCV_RELAX_DURATION_SEC) {
            est->is_relaxed = true;
            /* Battery is fully relaxed: perform chemical 2D OCV recalibration */
            uint8_t ocv_soc = bms_ocv_lookup_soc(t->min_cell_mv, t->min_temp_c);
            est->last_ocv_soc = ocv_soc;
            t->soc_pct = ocv_soc;
            t->remaining_mah = (t->total_capacity_mah * (uint32_t)ocv_soc) / 100;
            est->accum_coulombs_mas = 0;
            return;
        }
    } else {
        /* Current flowing under charge or discharge: reset relaxation timer */
        est->rest_duration_sec = 0;
        est->is_relaxed = false;
    }

    /* Under load: Perform Coulomb integration (Ah counting) */
    /* delta_mas = mA * ms */
    int64_t delta_mas = (int64_t)current_ma * (int64_t)delta_ms;
    est->accum_coulombs_mas += delta_mas;

    /* 1 mAh = 3,600,000 mA*ms */
    int32_t delta_mah = (int32_t)(est->accum_coulombs_mas / 3600000LL);
    if (delta_mah != 0) {
        int32_t new_rem = (int32_t)t->remaining_mah + delta_mah;
        if (new_rem < 0) new_rem = 0;
        if (new_rem > (int32_t)t->total_capacity_mah) new_rem = t->total_capacity_mah;

        t->remaining_mah = (uint32_t)new_rem;
        if (t->total_capacity_mah > 0) {
            t->soc_pct = (uint8_t)((t->remaining_mah * 100) / t->total_capacity_mah);
        }
        est->accum_coulombs_mas %= 3600000LL;
    }
}

/**
 * @brief Apply parasitic BMS board quiescent drain + temperature-dependent cell self-discharge
 * @note Reconstructed from FUN_0801fc8c (Flash 0x0801FC8C):
 *       Executed every 75 rest intervals:
 *       loss_mah = (bms_quiescent_mah + self_dsg_rate * total_capacity_mah) / 12
 */
uint32_t bms_ocv_apply_self_discharge(BmsContext_t *ctx) {
    if (!ctx) return 0;
    BmsTelemetry_t *t = &ctx->telemetry;

    /* Base BMS quiescent current (~15 mA) + temperature-dependent cell self-discharge factor */
    float temp_factor = (t->max_temp_c > 35) ? 0.0004f : 0.0002f;
    float loss_f = (15.0f + (temp_factor * (float)t->total_capacity_mah)) / 12.0f;
    uint32_t loss_mah = (uint32_t)(loss_f + 0.5f);
    if (loss_mah == 0U) loss_mah = 1U;

    if (t->remaining_mah >= loss_mah) {
        t->remaining_mah -= loss_mah;
    } else {
        t->remaining_mah = 0U;
    }

    if (t->total_capacity_mah > 0U) {
        t->soc_pct = (uint8_t)((t->remaining_mah * 100U) / t->total_capacity_mah);
    }
    return loss_mah;
}


