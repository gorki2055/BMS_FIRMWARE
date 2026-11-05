/**
 * @file dvc1124_afe.h
 * @brief Devechip DVC1124-1 24S Precision Battery Analog Front-End Driver
 * @note Reverse-Engineered from Flash addresses 0x0800A000 - 0x08010000
 *       7-bit I2C Address: 0x20 (Write 0x40, Read 0x41), Bit-Banged on GPIOB, PEC CRC8
 */

#ifndef __DVC1124_AFE_H__
#define __DVC1124_AFE_H__

#include <stdint.h>
#include <stdbool.h>

/* ========================================================================== */
/* I2C Communication Addressing                                               */
/* ========================================================================== */
#define DVC1124_I2C_7BIT_ADDR            0x20
#define DVC1124_I2C_ADDR_WRITE           0x40  /**< (0x20 << 1) | 0 */
#define DVC1124_I2C_ADDR_READ            0x41  /**< (0x20 << 1) | 1 */

/* ========================================================================== */
/* Recovered DVC1124 Internal Register Map                                    */
/* ========================================================================== */
#define DVC_REG_SYS_CTRL                 0x00  /**< System Control (Reset, Sleep, Wake) */
#define DVC_REG_CELL_MODE                0x01  /**< Cell Count Mode: 0x0D=21S, 0x0E=22S, 0x0F=24S */
#define DVC_REG_CURRENT                  0x02  /**< Pack Current ADC (Signed 16-bit) */
#define DVC_REG_ADC_CTRL                 0x06  /**< ADC Channel Sequencing & Clock Enable */
#define DVC_REG_ADC_CONFIG               0x07  /**< ADC Filter & Sample Timing */
#define DVC_REG_CELL_STATUS              0x0B  /**< Cell Measurement Alert & Ready Flags */
#define DVC_REG_NTC_BASE                 0x0F  /**< NTC Thermistor ADC Base Register */
#define DVC_REG_CELL_VOLTAGES            0x1D  /**< Cell Voltage Buffer (2 bytes/cell) */
#define DVC_REG_PACK_VOLTAGE             0x4F  /**< High-Voltage Stack Voltage ADC (2 bytes) */
#define DVC_REG_MEAS_CTRL                0x51  /**< Measurement Trigger (Bit 7: trigger scan) */
#define DVC_REG_BURST_CELLS              0x52  /**< Burst Read Cell Data (0x28 bytes) / Write (3B) */
#define DVC_REG_BALANCING_CTRL           0x56  /**< Passive Balancing Control & Config (0x24 bytes) */
#define DVC_REG_FAULT_STATUS             0x5A  /**< Hardware Fault Alert Register (clear with 0xFE) */
#define DVC_REG_OVP_THRESH               0x5E  /**< Hardware Over-Voltage Threshold */
#define DVC_REG_OVP_DELAY                0x5F  /**< Hardware Over-Voltage Delay */
#define DVC_REG_UVP_THRESH               0x60  /**< Hardware Under-Voltage Threshold */
#define DVC_REG_UVP_DELAY                0x61  /**< Hardware Under-Voltage Delay */
#define DVC_REG_TEMP_CONFIG              0x62  /**< Temperature Sensing Channel Configuration */
#define DVC_REG_CHG_OCP                  0x63  /**< Hardware Charge Over-Current Threshold */
#define DVC_REG_DSG_OCP1                 0x67  /**< Hardware Discharge Over-Current Level 1 */
#define DVC_REG_DSG_OCP2                 0x68  /**< Hardware Discharge Short-Circuit Level 2 */
#define DVC_REG_OCP_DELAY                0x69  /**< Over-Current Trip Filter Delay */
#define DVC_REG_AFE_CONFIG               0x6E  /**< Core AFE Config (0xCD normal, 0x8D) */
#define DVC_REG_CHIP_ID_VREF             0x7E  /**< Chip ID & Internal VREF Trim Calibration */
#define DVC_REG_RESET_DIAG               0x8E  /**< Soft Reset & Diagnostics Control (0x80) */

/* Legacy compatibility aliases */
#define DVC_REG_MOS_CTRL                 0x00
#define DVC_REG_SYS_STATUS               0x0B

/* ========================================================================== */
/* Hardware ADC Conversion Constants (Recovered from Flash Literal Pools)      */
/* ========================================================================== */
#define DVC1124_VOLTAGE_SCALE_MV_PER_LSB 0.1f   /**< Flash 0x0800D3BC: 0.0001V = 0.1 mV / count */
#define DVC1124_VOLTAGE_OFFSET_MV        0.5f   /**< Flash 0x0800D3C0: 0.0005V = 0.5 mV */
#define DVC1124_CURRENT_SCALE_MA_PER_LSB 5.0f   /**< Flash 0x0800D52C: 0.005A = 5 mA / count */
#define DVC1124_TEMP_OFFSET_DEG_C        40     /**< Temperature decoding offset (+40°C in CAN / -40°C raw) */

/* ========================================================================== */
/* Driver Function Prototypes                                                 */
/* ========================================================================== */
bool dvc1124_init(void);
bool dvc1124_read_cell_voltages(uint16_t *cell_mv, uint8_t cell_count);
bool dvc1124_read_pack_current(int32_t *current_ma);
bool dvc1124_read_temperatures(int16_t *temps_c, uint8_t count, int16_t *mos_temp);
bool dvc1124_set_balancing(uint32_t cell_mask);
bool dvc1124_write_reg(uint8_t reg, uint8_t val);
bool dvc1124_read_reg(uint8_t reg, uint8_t *val);
bool dvc1124_read_burst(uint8_t reg, uint8_t *buf, uint8_t len);
bool dvc1124_write_burst(uint8_t reg, const uint8_t *buf, uint8_t len);

/* Math & Conversion Helpers */
uint16_t dvc1124_raw_to_cell_mv(uint16_t raw_adc);
int32_t dvc1124_raw_to_current_ma(int16_t raw_adc, int16_t zero_offset);
uint8_t dvc1124_calc_crc8(const uint8_t *data, uint16_t len);

#endif /* __DVC1124_AFE_H__ */
