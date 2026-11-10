/**
 * @file bms_core.h
 * @brief Core State Machine, Protection Supervisor, Pre-Charge, Body-Diode Protection & Balancing
 */

#ifndef __BMS_CORE_H__
#define __BMS_CORE_H__

#include "bms_types.h"

void bms_core_init(BmsContext_t *ctx);
void bms_core_process_10ms_tick(BmsContext_t *ctx);
void bms_core_process_100ms_tick(BmsContext_t *ctx);
void bms_core_process_1s_tick(BmsContext_t *ctx);
void bms_core_check_protections(BmsContext_t *ctx);
void bms_core_calculate_soc(BmsContext_t *ctx);
void bms_core_calculate_soh(BmsContext_t *ctx);
void bms_core_update_balancing(BmsContext_t *ctx);
void bms_core_record_cycles(BmsContext_t *ctx, uint16_t new_cycle_count);

/* Newly Reconstructed Hardware & Runtime Subsystems (Tasks 1.1 - 1.10 & 2.1 - 2.6) */
void bms_core_apply_cell_calibration(BmsContext_t *ctx);
void bms_core_update_hybrid_temperatures(BmsContext_t *ctx);
void bms_core_apply_mosfet_control(BmsContext_t *ctx, bool base_chg_en, bool base_dsg_en);
void bms_core_enter_deep_sleep(BmsContext_t *ctx, uint32_t wake_alarm_sec);
void bms_core_wake_from_sleep(BmsContext_t *ctx);
uint8_t bms_core_get_led_bar_stage(const BmsContext_t *ctx, bool *blink_out);

#endif /* __BMS_CORE_H__ */
