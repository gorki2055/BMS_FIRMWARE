/**
 * @file bms_config.h
 * @brief BMS Configuration & Factory Calibrated Thresholds
 * @note Extracted from scatterload tables and hardware schematics
 */

#ifndef __BMS_CONFIG_H__
#define __BMS_CONFIG_H__

#include <stdint.h>

/* ========================================================================== */
/* Battery Pack Specifications (21S 70Ah NCM - Nepal Market)                  */
/* ========================================================================== */
#define BMS_SERIES_CELLS             21        /**< Number of cells in series */
#define BMS_NOMINAL_CAPACITY_AH      70        /**< Pack capacity rating: 70 Ah */
#define BMS_NOMINAL_CAPACITY_MAH     70000     /**< Pack capacity in mAh */
#define BMS_NTC_TEMP_SENSORS         4         /**< 4 external temperature sensors */

/* ========================================================================== */
/* Calibrated Voltage Protection Limits (in Millivolts)                       */
/* Extracted from decompress table at Flash 0x08023184 -> SRAM 0x20020000      */
/* ========================================================================== */
#define BMS_CELL_OVP_MV              4185      /**< Over-Voltage Protection cutoff (4.185V) */
#define BMS_CELL_OVP_RELEASE_MV      4100      /**< Over-Voltage Protection release */
#define BMS_CELL_BALANCE_START_MV    4120      /**< Passive balancing start threshold */
#define BMS_CELL_BALANCE_DELTA_MV    20        /**< Delta between min/max cell to balance */
#define BMS_CELL_NOMINAL_MV          3608      /**< Nominal cell voltage (3.608V) */
#define BMS_CELL_UVW_WARNING_MV      2831      /**< Under-Voltage Warning threshold */
#define BMS_CELL_UVC_CUTOFF_MV       2621      /**< Hard Under-Voltage Cutoff (contactor trip) */
#define BMS_CELL_SHUTDOWN_MV         2500      /**< Deep sleep / hibernate trigger */

/* ========================================================================== */
/* Current Protection Limits (in Amperes)                                     */
/* ========================================================================== */
#define BMS_MAX_CONTINUOUS_DSG_A     70        /**< Max continuous discharge current (1C) */
#define BMS_MAX_PEAK_DSG_A           120       /**< Peak discharge current (schematic rating) */
#define BMS_MAX_CHARGE_CURRENT_A     35        /**< Max charge current (0.5C) */
#define BMS_AUX_ACC_MAX_CURRENT_A    2         /**< ACC limited auxiliary discharge */

/* ========================================================================== */
/* Temperature Protection Limits (in Celsius)                                 */
/* ========================================================================== */
#define BMS_CHG_OT_PROTECT_C        55        /**< Charge over-temperature cutoff */
#define BMS_DSG_OT_PROTECT_C        65        /**< Discharge over-temperature cutoff */
#define BMS_MOS_OT_PROTECT_C        85        /**< Power MOSFET over-temperature */
#define BMS_CHG_UT_PROTECT_C        0         /**< Charge under-temperature (0°C) */
#define BMS_DSG_UT_PROTECT_C        -20       /**< Discharge under-temperature (-20°C) */

/* ========================================================================== */
/* CAN Network Identification                                                 */
/* ========================================================================== */
#define BMS_CAN_BAUDRATE             250000    /**< 250 kbps */
#define BMS_CAN_MASTER_SID           0x14      /**< Master Pack Battery #1 SID */
#define BMS_CAN_SLAVE_SID            0x1D      /**< Slave Pack Battery #2 SID */
#define BMS_CAN_VCU_SID              0x00      /**< Vehicle Control Unit SID */

/* ========================================================================== */
/* Hardware Board Pinout (SPB24-DVC24-006-0606-A03)                          */
/* ========================================================================== */
/* Communication Pins */
#define PIN_CAN_RX                   11        /**< PA11: CAN1_RX */
#define PIN_CAN_TX                   12        /**< PA12: CAN1_TX */
#define PIN_AFE_SCL                  6         /**< PB6:  I2C1_SCL (to DVC1124) */
#define PIN_AFE_SDA                  7         /**< PB7:  I2C1_SDA (to DVC1124) */
#define PIN_RS485_TX                 9         /**< PA9:  USART1_TX */
#define PIN_RS485_RX                 10        /**< PA10: USART1_RX */

/* Control & Sensing Pins */
#define PIN_ACC_WAKE                 0         /**< PA0:  ACC Ignition Wake input */
#define PIN_CIN_DETECT               1         /**< PB1:  CIN Charger detect input */
#define PIN_DIN_DETECT               2         /**< PC2:  DIN Discharge request input */
#define PIN_CHG_EN                   8         /**< PA8:  Main Charge MOSFET Drive */
#define PIN_DSG_EN                   9         /**< PC9:  Main Discharge MOSFET Drive */
#define PIN_PRECHARGE_EN             4         /**< PC4:  Pre-charge MOSFET Drive */

#endif /* __BMS_CONFIG_H__ */
