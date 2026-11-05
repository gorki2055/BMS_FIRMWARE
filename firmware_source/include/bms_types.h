/**
 * @file bms_types.h
 * @brief Core Data Types for 21S BMS Firmware
 */

#ifndef __BMS_TYPES_H__
#define __BMS_TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include "bms_config.h"

/* Operational States */
typedef enum {
    BMS_STATE_INIT = 0,
    BMS_STATE_STANDBY,
    BMS_STATE_DISCHARGE,
    BMS_STATE_CHARGE,
    BMS_STATE_BALANCING,
    BMS_STATE_FAULT,
    BMS_STATE_SLEEP
} BmsState_t;

/* Multi-pack Dual Role */
typedef enum {
    BMS_ROLE_STANDALONE = 0,
    BMS_ROLE_MASTER,        /* ID 0x14 */
    BMS_ROLE_SLAVE          /* ID 0x1D */
} BmsRole_t;

/* Fault and Protection Flags */
typedef union {
    uint32_t all;
    struct {
        uint32_t cell_ovp      : 1;  /* Cell Over-Voltage Protection */
        uint32_t cell_uvp      : 1;  /* Cell Under-Voltage Protection */
        uint32_t pack_ovp      : 1;  /* Total Pack Over-Voltage */
        uint32_t pack_uvp      : 1;  /* Total Pack Under-Voltage */
        uint32_t chg_ocp       : 1;  /* Charge Over-Current */
        uint32_t dsg_ocp1      : 1;  /* Discharge Over-Current Level 1 */
        uint32_t dsg_ocp2      : 1;  /* Discharge Over-Current Level 2 / Short */
        uint32_t chg_otp       : 1;  /* Charge Over-Temperature */
        uint32_t chg_utp       : 1;  /* Charge Under-Temperature */
        uint32_t dsg_otp       : 1;  /* Discharge Over-Temperature */
        uint32_t dsg_utp       : 1;  /* Discharge Under-Temperature */
        uint32_t mos_otp       : 1;  /* Power MOSFET Over-Temperature */
        uint32_t afe_comm_fail : 1;  /* DVC1124 I2C communication error */
        uint32_t cell_unbalance: 1;  /* Excessive voltage divergence */
        uint32_t aux_overload  : 1;  /* ACC auxiliary path current > 2A */
        uint32_t reserved      : 17;
    } bits;
} BmsFaultFlags_t;

/* MOSFET & Contactor Status */
typedef struct {
    bool chg_mos_on;         /* Main charging MOSFET state */
    bool dsg_mos_on;         /* Main discharging MOSFET state */
    bool precharge_mos_on;   /* Pre-charge circuit state */
    bool acc_wake_active;    /* ACC input line active */
    bool cin_active;         /* CIN charger input line active */
    bool din_active;         /* DIN discharge request line active */
} BmsSwitchState_t;

/* Complete Battery Pack Telemetry */
typedef struct {
    uint16_t cell_mv[BMS_SERIES_CELLS];  /* Cell voltages in mV */
    uint16_t min_cell_mv;                /* Lowest cell voltage */
    uint16_t max_cell_mv;                /* Highest cell voltage */
    uint8_t  min_cell_idx;               /* Index of lowest cell */
    uint8_t  max_cell_idx;               /* Index of highest cell */
    uint16_t cell_delta_mv;              /* Difference (max - min) */

    int16_t  temp_c[BMS_NTC_TEMP_SENSORS]; /* NTC Temperatures in °C */
    int16_t  min_temp_c;
    int16_t  max_temp_c;
    int16_t  mos_temp_c;                 /* Power stage temperature */

    int32_t  current_ma;                 /* Pack current in mA (+ charge, - discharge) */
    uint32_t pack_voltage_mv;            /* Total stack voltage in mV */

    uint8_t  soc_pct;                    /* State of Charge (0 - 100%) */
    uint8_t  soh_pct;                    /* State of Health (0 - 100%) */
    uint32_t remaining_mah;              /* Remaining capacity in mAh */
    uint32_t total_capacity_mah;         /* Total calibrated capacity (70000 mAh) */

    uint16_t cycle_count;                /* Charge/discharge cycle count */
    uint32_t balance_mask;               /* Bitmask of active balancing cells (bits 0..20) */
} BmsTelemetry_t;

/* Runtime Protection Limits & Thresholds (Stored in EEPROM 0x0020) */
typedef struct {
    uint16_t cell_ovp_mv;         /* Cell Over-Voltage Protection (default: 4185 mV) */
    uint16_t cell_uvp_mv;         /* Cell Under-Voltage Protection (default: 2621 mV) */
    int32_t  chg_ocp_ma;          /* Charge Over-Current (default: 35000 mA) */
    int32_t  dsg_ocp_ma;          /* Discharge Over-Current (default: 70000 mA) */
    float    ot_protect_c;        /* Over-Temperature Cutoff (default: 65.0 C) */
    float    ut_protect_c;        /* Under-Temperature Cutoff (default: -10.0 C) */
} BmsLimits_t;

/* Dynamic SOC Estimator State (Coulomb Counter + 2D OCV Fusion) */
typedef struct {
    int64_t  accum_coulombs_mas;   /* Accumulated milliampere-seconds (mAs) */
    uint32_t rest_duration_sec;    /* Consecutive seconds in quiescent state (< 0.8A) */
    bool     is_relaxed;           /* True when polarization voltage has decayed */
    uint8_t  last_ocv_soc;         /* Last chemical OCV calibration anchor (0-100%) */
} BmsSocEstimator_t;

/* Overall BMS Runtime Context */
typedef struct {
    BmsState_t        state;
    BmsRole_t         role;
    uint8_t           can_sid;            /* 0x14 for Master, 0x1D for Slave */
    BmsFaultFlags_t   faults;
    BmsSwitchState_t  switches;
    BmsTelemetry_t    telemetry;
    BmsLimits_t       limits;             /* Runtime / EEPROM protection limits */
    BmsSocEstimator_t soc_est;            /* Hybrid Coulomb-Counting / 2D OCV estimator */
    uint32_t          uptime_seconds;
    char              serial_number[32];
} BmsContext_t;

#endif /* __BMS_TYPES_H__ */
