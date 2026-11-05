/**
 * @file bms_core.h
 * @brief Core State Machine and Protection Supervisor
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

#endif /* __BMS_CORE_H__ */
