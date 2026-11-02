/**
 * @file bms_hal.h
 * @brief Hardware Abstraction Layer for Nations N32G452 on SPB24 Board
 */

#ifndef __BMS_HAL_H__
#define __BMS_HAL_H__

#include <stdint.h>
#include <stdbool.h>

void bms_hal_init(void);

/* Discrete Input Sensing */
bool bms_hal_read_acc_wake(void);
bool bms_hal_read_cin_detect(void);
bool bms_hal_read_din_detect(void);

/* Power Switching Outputs */
void bms_hal_set_chg_mos(bool enable);
void bms_hal_set_dsg_mos(bool enable);
void bms_hal_set_precharge_mos(bool enable);

/* I2C Peripheral Communication */
bool bms_hal_i2c_write(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len);
bool bms_hal_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/* CAN Peripheral Communication */
bool bms_hal_can_transmit(uint32_t ext_id, const uint8_t *payload, uint8_t dlc);
bool bms_hal_can_receive(uint32_t *ext_id, uint8_t *payload, uint8_t *dlc);

/* Timing & Utilities */
uint32_t bms_hal_get_tick_ms(void);
void bms_hal_delay_ms(uint32_t ms);

#endif /* __BMS_HAL_H__ */
