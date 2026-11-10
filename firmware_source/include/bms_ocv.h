/**
 * @file bms_ocv.h
 * @brief 2D Open Circuit Voltage (OCV) vs. SOC & Temperature Engine
 * @note Reverse-Engineered from Flash addresses 0x08010000 - 0x08014000
 *       (FUN_08010654, FUN_080103c8, Scatterload Table 0x08023184)
 */

#ifndef __BMS_OCV_H__
#define __BMS_OCV_H__

#include <stdint.h>
#include <stdbool.h>
#include "bms_types.h"

#define BMS_OCV_SOC_POINTS               21   /**< 0% to 100% in 5% increments */
#define BMS_OCV_TEMP_BANDS_AVAIL         12   /**< 12 temperature columns in FUN_08010654 */
#define BMS_OCV_TEMP_BANDS_THERMAL       13   /**< 13 temperature columns in FUN_080103c8 */
#define BMS_OCV_QUIESCENT_CURRENT_MA     800  /**< Polarization decay threshold (0.8A from Flash 0x08020858) */
#define BMS_OCV_RELAX_DURATION_SEC       20   /**< 20 seconds consecutive rest for OCV latch (Flash 0x0801B55C) */

/**
 * @brief Initialize Hybrid SOC Estimator with chemical 2D OCV curve
 */
void bms_soc_estimator_init(BmsContext_t *ctx);

/**
 * @brief Periodic dynamic update: Coulomb Counting under load + 2D OCV Recalibration at rest
 * @param ctx BMS context
 * @param delta_ms Elapsed time in milliseconds since last update
 */
void bms_soc_estimator_update(BmsContext_t *ctx, uint32_t delta_ms);

/**
 * @brief Look up chemical State of Charge (SOC %) from cell voltage and temperature
 * @param cell_mv Lowest cell voltage in millivolts
 * @param temp_c Pack temperature in Celsius (-20°C to +65°C)
 * @return Estimated chemical SOC percentage (0 - 100%)
 */
uint8_t bms_ocv_lookup_soc(uint16_t cell_mv, int16_t temp_c);

/**
 * @brief Look up expected Open Circuit Voltage (mV) from SOC and temperature
 * @param soc_pct State of Charge percentage (0 - 100%)
 * @param temp_c Pack temperature in Celsius
 * @return Expected open circuit cell voltage in mV
 */
uint16_t bms_ocv_lookup_voltage(uint8_t soc_pct, int16_t temp_c);

/**
 * @brief Look up chemical capacity availability derating factor from 21x12 matrix
 * @note Reconstructed from FUN_08010654 (Flash 0x08010654, Table 0x20020572)
 * @param soc_pct Current SOC (0 - 100%)
 * @param temp_c Battery temperature in Celsius
 * @return Capacity derating coefficient in Ah
 */
float bms_ocv_get_capacity_derate(uint8_t soc_pct, int16_t temp_c);

/**
 * @brief Look up thermal voltage relaxation derating factor from 21x13 matrix
 * @note Reconstructed from FUN_080103c8 (Flash 0x080103c8, Table 0x20020720)
 * @param soc_pct Current SOC (0 - 100%)
 * @param temp_c Battery temperature in Celsius
 * @return Thermal relaxation coefficient
 */
float bms_ocv_get_thermal_derate(uint8_t soc_pct, int16_t temp_c);

/**
 * @brief Apply parasitic BMS quiescent drain + temperature-dependent self-discharge (FUN_0801fc8c)
 * @param ctx BMS context
 * @return Deducted capacity in mAh
 */
uint32_t bms_ocv_apply_self_discharge(BmsContext_t *ctx);

#endif /* __BMS_OCV_H__ */

