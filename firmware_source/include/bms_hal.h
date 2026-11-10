/**
 * @file bms_hal.h
 * @brief Hardware Abstraction Layer for Nations N32G45x on SPB24 Board
 * @note Includes support for:
 *       - GPIO MOSFET gate drivers (PA8 CHG, PC9 DSG, PC4 PRECHARGE)
 *       - 96-bit MCU Factory UID reader (0x1FFFF7F0, FUN_08018708)
 *       - On-chip Flash Controller driver (0x40022000, FUN_0800f4f8 - FUN_0800fc44)
 *       - Internal 12-bit ADC1..ADC4 thermistor sensing (0x40020800/0x40020C00, FUN_08008914)
 *       - Unified 7-port UART driver (USART1..3, UART4..7 @ 0x40015000/0x40015400) & RS-485 DE/RE (FUN_08016420)
 *       - RTC Alarm (0x40002800 / BKP 0x40006C00) & PWR STOP sleep entry/recovery (FUN_080161bc / FUN_08016360)
 */

#ifndef __BMS_HAL_H__
#define __BMS_HAL_H__

#include <stdint.h>
#include <stdbool.h>

/* 7-Port Serial Driver Identifiers (Literal pool 0x08015EA8 - 0x08015EF0) */
typedef enum {
    BMS_UART_PORT_USART1 = 0, /* 0x40013800 (APB2) */
    BMS_UART_PORT_USART2 = 1, /* 0x40004400 (APB1) */
    BMS_UART_PORT_USART3 = 2, /* 0x40004800 (APB1) */
    BMS_UART_PORT_UART4  = 3, /* 0x40004C00 (APB1) */
    BMS_UART_PORT_UART5  = 4, /* 0x40005000 (APB1) */
    BMS_UART_PORT_UART6  = 5, /* 0x40015000 (APB2 - N32G45x UART6) */
    BMS_UART_PORT_UART7  = 6, /* 0x40015400 (APB2 - N32G45x UART7) */
    BMS_UART_PORT_COUNT  = 7
} BmsUartPort_t;

void bms_hal_init(void);

/* Discrete Input Sensing */
bool bms_hal_read_acc_wake(void);
bool bms_hal_read_cin_detect(void);
bool bms_hal_read_din_detect(void);

/* Power Switching Outputs & State Inspection */
void bms_hal_set_chg_mos(bool enable);
void bms_hal_set_dsg_mos(bool enable);
void bms_hal_set_precharge_mos(bool enable);
bool bms_hal_get_chg_mos(void);
bool bms_hal_get_dsg_mos(void);
bool bms_hal_get_precharge_mos(void);

/* I2C Peripheral Communication */
bool bms_hal_i2c_write(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len);
bool bms_hal_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/* CAN Peripheral Communication */
bool bms_hal_can_transmit(uint32_t ext_id, const uint8_t *payload, uint8_t dlc);
bool bms_hal_can_receive(uint32_t *ext_id, uint8_t *payload, uint8_t *dlc);

/* MCU 96-Bit Unique Device ID (0x1FFFF7F0, FUN_08018708) */
void bms_hal_read_mcu_uid(uint8_t uid_out[12]);
void bms_hal_set_simulated_uid(const uint8_t uid[12]);

/* On-Chip Flash Controller (0x40022000, 2KB pages @ 0x08028000, FUN_0800f850) */
bool bms_hal_flash_read(uint32_t offset, uint8_t *buf, uint16_t len);
bool bms_hal_flash_write(uint32_t offset, const uint8_t *data, uint16_t len);

/* Internal 12-Bit ADC1..ADC4 (0x40020800 / 0x40020C00, FUN_08008914 / FUN_080089c0) */
uint16_t bms_hal_read_internal_adc(uint8_t adc_num, uint8_t channel);
void bms_hal_set_simulated_adc(uint8_t channel, uint16_t raw_12b);

/* Unified 7-Port UART & RS-485 DE/RE Direction Control (FUN_08016420) */
uint32_t bms_hal_uart_get_base_addr(BmsUartPort_t port);
void bms_hal_rs485_set_de(BmsUartPort_t port, bool tx_enable);
bool bms_hal_rs485_get_de(BmsUartPort_t port);
bool bms_hal_uart_transmit(BmsUartPort_t port, const uint8_t *buf, uint16_t len);

/* Deep-Sleep (PWR STOP @ 0x40007000) & RTC Alarm Wake-Up (FUN_080161bc / FUN_08016360) */
void bms_hal_enter_stop_sleep(uint32_t wake_alarm_sec);
void bms_hal_restore_clocks_after_wake(void);
uint32_t bms_hal_get_last_rtc_alarm_sec(void);
bool bms_hal_is_in_stop_sleep(void);

/* Timing & Utilities */
uint32_t bms_hal_get_tick_ms(void);
void bms_hal_delay_ms(uint32_t ms);

#endif /* __BMS_HAL_H__ */
