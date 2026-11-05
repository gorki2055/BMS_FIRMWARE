/**
 * @file bms_modbus.h
 * @brief BMS RS-485 / Modbus RTU & Diagnostic Communication Protocol
 *
 * Reverse-engineered from N32G45x BMS Firmware binary (0x08014000 - 0x08019000).
 * Handles:
 *  - USART1/USART2 @ 9600 baud, 8N1 serial communication.
 *  - Standard Modbus RTU Protocol (Address 0x01, FC 0x03, 0x04, 0x06, 0x10).
 *  - Standard Modbus CRC-16 (Polynomial 0xA001, seed 0xFFFF, FUN_0800c754).
 *  - Proprietary PC Upper-Computer Diagnostic Protocol (0xEA 0xD1, 0xEB 0x01).
 *  - Bluetooth Module AT command framing ("AT+NAME ...\r\n").
 */

#ifndef BMS_MODBUS_H
#define BMS_MODBUS_H

#include <stdint.h>
#include <stdbool.h>
#include "bms_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Default Communication Settings */
#define BMS_MODBUS_DEFAULT_SLAVE_ID     0x01
#define BMS_MODBUS_DEFAULT_BAUDRATE     9600

/* Modbus RTU Function Codes */
#define MODBUS_FC_READ_COILS            0x01
#define MODBUS_FC_READ_DISCRETE_INPUTS  0x02
#define MODBUS_FC_READ_HOLDING_REGS     0x03
#define MODBUS_FC_READ_INPUT_REGS       0x04
#define MODBUS_FC_WRITE_SINGLE_COIL     0x05
#define MODBUS_FC_WRITE_SINGLE_REG      0x06
#define MODBUS_FC_WRITE_MULTIPLE_REGS   0x10

/* Modbus RTU Exception Codes */
#define MODBUS_EX_ILLEGAL_FUNCTION      0x01
#define MODBUS_EX_ILLEGAL_DATA_ADDR     0x02
#define MODBUS_EX_ILLEGAL_DATA_VALUE    0x03
#define MODBUS_EX_SLAVE_DEVICE_FAILURE  0x04

/* Proprietary Host Protocol Headers */
#define BMS_HOST_FRAME_HEADER_EA        0xEA
#define BMS_HOST_FRAME_HEADER_EB        0xEB
#define BMS_HOST_FRAME_CMD_TELEMETRY    0xD1
#define BMS_HOST_FRAME_CMD_CONFIG       0x01

/* Modbus Register Map Offsets */
#define MODBUS_REG_CELL1_VOLTAGE        0x0001 /* Cell 1 Voltage (mV) */
#define MODBUS_REG_CELL21_VOLTAGE       0x0015 /* Cell 21 Voltage (mV) */
#define MODBUS_REG_PACK_VOLTAGE         0x0016 /* Total Pack Voltage (10mV scale) */
#define MODBUS_REG_PACK_CURRENT         0x0017 /* Pack Current (signed, 10mA scale) */
#define MODBUS_REG_SOC                  0x0018 /* State of Charge (0.1%, 0-1000) */
#define MODBUS_REG_SOH                  0x0019 /* State of Health (0.1%, 0-1000) */
#define MODBUS_REG_REMAINING_CAP        0x001A /* Remaining Capacity (0.1 Ah) */
#define MODBUS_REG_NOMINAL_CAP          0x001B /* Nominal Pack Capacity (700 = 70.0 Ah) */
#define MODBUS_REG_CYCLE_COUNT          0x001C /* Discharge Cycle Count */
#define MODBUS_REG_CELL_MAX_VOLT        0x001D /* Highest Cell Voltage (mV) */
#define MODBUS_REG_CELL_MIN_VOLT        0x001E /* Lowest Cell Voltage (mV) */
#define MODBUS_REG_CELL_DELTA_VOLT      0x001F /* Cell Imbalance Delta (mV) */

#define MODBUS_REG_TEMP_NTC1            0x0020 /* Cell Temp 1 (0.1 C, signed) */
#define MODBUS_REG_TEMP_NTC2            0x0021 /* Cell Temp 2 (0.1 C, signed) */
#define MODBUS_REG_TEMP_NTC3            0x0022 /* Cell Temp 3 (0.1 C, signed) */
#define MODBUS_REG_TEMP_NTC4            0x0023 /* Cell Temp 4 (0.1 C, signed) */
#define MODBUS_REG_TEMP_MOSFET          0x0024 /* Power MOSFET Temp (0.1 C) */
#define MODBUS_REG_TEMP_AMBIENT         0x0025 /* Ambient Temp (0.1 C) */

#define MODBUS_REG_BMS_STATE            0x0030 /* Operating State (0:INIT, 1:STANDBY, 2:CHG, 3:DSG, 4:FAULT) */
#define MODBUS_REG_FAULT_FLAGS          0x0031 /* Protection Alarm Bitmask */
#define MODBUS_REG_MOSFET_STATUS        0x0032 /* Bit 0: CHG MOS, Bit 1: DSG MOS */

#define MODBUS_REG_OVP_THRESHOLD        0x0040 /* Cell Over-Voltage Protection (mV) */
#define MODBUS_REG_UVP_THRESHOLD        0x0041 /* Cell Under-Voltage Protection (mV) */
#define MODBUS_REG_OCP_CHG_THRESHOLD    0x0042 /* Charge Over-Current (10mA) */
#define MODBUS_REG_OCP_DSG_THRESHOLD    0x0043 /* Discharge Over-Current (10mA) */
#define MODBUS_REG_OTP_THRESHOLD        0x0044 /* Over-Temperature (0.1 C) */
#define MODBUS_REG_UTP_THRESHOLD        0x0045 /* Under-Temperature (0.1 C) */

/**
 * @brief Initialize Modbus RTU / RS-485 interface
 * @param slave_id Slave device address (default: 0x01)
 * @param baud_rate Serial baud rate (default: 9600)
 */
void bms_modbus_init(uint8_t slave_id, uint32_t baud_rate);

/**
 * @brief Compute Modbus CRC16 checksum (reconstructed from FUN_0800c754)
 * @param buffer Input data pointer
 * @param length Byte length
 * @return 16-bit CRC with polynomial 0xA001
 */
uint16_t bms_modbus_calc_crc16(const uint8_t *buffer, uint16_t length);

/**
 * @brief Process an incoming Modbus RTU request frame
 * @param rx_buf Pointer to received raw packet bytes
 * @param rx_len Length of received packet
 * @param tx_buf Buffer to store response packet
 * @param tx_buf_size Maximum size of tx buffer
 * @param ctx Pointer to active BMS context
 * @return Number of bytes written to tx_buf (>0 on response, 0 on no response, <0 on error)
 */
int bms_modbus_process_frame(const uint8_t *rx_buf, uint16_t rx_len,
                             uint8_t *tx_buf, uint16_t tx_buf_size,
                             BmsContext_t *ctx);

/**
 * @brief Process proprietary PC upper-computer diagnostic frame (0xEA / 0xEB)
 * @param rx_buf Raw input packet
 * @param rx_len Input packet length
 * @param tx_buf Output response buffer
 * @param tx_buf_size Maximum output buffer capacity
 * @param ctx Pointer to active BMS context
 * @return Response length, or <= 0
 */
int bms_host_proto_process_frame(const uint8_t *rx_buf, uint16_t rx_len,
                                 uint8_t *tx_buf, uint16_t tx_buf_size,
                                 const BmsContext_t *ctx);

#ifdef __cplusplus
}
#endif

#endif /* BMS_MODBUS_H */
