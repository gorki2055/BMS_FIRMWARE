/**
 * @file bms_can.h
 * @brief CAN Communication Protocol Engine (250 kbps, 29-bit IDs)
 * @note Implements protocol specified in CAN documentation & decompiled code
 */

#ifndef __BMS_CAN_H__
#define __BMS_CAN_H__

#include <stdint.h>
#include <stdbool.h>
#include "bms_types.h"

/* 29-bit Extended CAN Identifier Structure:
 * Bits [28:26] Priority (default 0x6 / 0x7)
 * Bits [25:21] Source ID (SID): Master 0x14, Slave 0x1D, VCU 0x00..0x1E
 * Bits [20:16] Destination ID (DID)
 * Bits [15:8]  Command (CMD)
 * Bits [7:0]   Sub-command / Index
 */
#define BMS_CAN_BUILD_ID(prio, sid, did, cmd, idx) \
    (((uint32_t)((prio) & 0x07) << 26) | \
     ((uint32_t)((sid)  & 0x1F) << 21) | \
     ((uint32_t)((did)  & 0x1F) << 16) | \
     ((uint32_t)((cmd)  & 0xFF) << 8)  | \
     ((uint32_t)((idx)  & 0xFF)))

#define BMS_CAN_EXTRACT_SID(can_id)  (((can_id) >> 21) & 0x1F)
#define BMS_CAN_EXTRACT_DID(can_id)  (((can_id) >> 16) & 0x1F)
#define BMS_CAN_EXTRACT_CMD(can_id)  (((can_id) >> 8)  & 0xFF)
#define BMS_CAN_EXTRACT_IDX(can_id)  ((can_id) & 0xFF)

/* Command Identifiers */
#define CAN_CMD_TELEMETRY            0x14
#define CAN_CMD_PACK_CONFIG          0x40
#define CAN_CMD_CELL_VOLTAGES        0x41
#define CAN_CMD_BALANCING_STATE      0x42
#define CAN_CMD_CONTROL              0x43

/* Sub-Command Indexes for CMD 0x14 */
#define CAN_IDX_TEL_STATUS           0x01
#define CAN_IDX_TEL_TEMPS            0x03
#define CAN_IDX_TEL_ACCUM_MAH        0x04
#define CAN_IDX_TEL_MOS_STATUS       0x10

/* Sub-Command Indexes for CMD 0x40 */
#define CAN_IDX_CFG_CAPACITY_SOH     0x01  /* Total capacity, Remaining capacity, SOC, SOH */
#define CAN_IDX_CFG_RATING           0x01  /* Strings, Parallels, Design Capacity */
#define CAN_IDX_CFG_CYCLES           0x02  /* Cycle count, Remaining time */

/* Sub-Command Indexes for CMD 0x43 */
#define CAN_IDX_CTRL_SWITCH_PACK     0x03  /* Dual-pack switch command */
#define CAN_IDX_CTRL_RESET_SLEEP     0xF2  /* Soft reset / sleep trigger */

/* CAN Raw Frame Structure */
typedef struct {
    uint32_t id;             /* 29-bit extended CAN ID */
    uint8_t  dlc;            /* Data length code (1 to 8) */
    uint8_t  data[8];        /* Data bytes */
} CanMessage_t;

/* CAN Driver Prototypes */
void bms_can_init(uint8_t own_sid);
void bms_can_process_rx(const CanMessage_t *msg, BmsContext_t *ctx);
void bms_can_transmit(const CanMessage_t *msg);
void bms_can_send_status(const BmsContext_t *ctx);
void bms_can_send_capacity_soh(const BmsContext_t *ctx);
void bms_can_send_cell_voltages(const BmsContext_t *ctx);
void bms_can_send_temperatures(const BmsContext_t *ctx);
uint16_t bms_crc16_modbus(const uint8_t *buf, uint16_t len);

#endif /* __BMS_CAN_H__ */
