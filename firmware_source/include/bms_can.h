/**
 * @file bms_can.h
 * @brief CAN Communication Protocol Engine (250 kbps, 29-bit Extended IDs)
 * @note Verified against both "CAN documentation.pdf" (V1.1) and the actual
 *       vendor binary firmware (output/firmware_app_0x08008000.bin:
 *       ID packer FUN_0801ef94 @ 0x0801EF94, unpacker FUN_0800daf4 @ 0x0800DAF4,
 *       periodic scheduler FUN_0801f842 @ 0x0801F842, RX dispatcher FUN_08020f1c @ 0x08020F1C).
 */

#ifndef __BMS_CAN_H__
#define __BMS_CAN_H__

#include <stdint.h>
#include <stdbool.h>
#include "bms_types.h"

/* -------------------------------------------------------------------------
 * 29-bit Extended CAN Identifier Structure
 * Verified at 0x0801EF94 (FUN_0801ef94) & 0x0800DAF4 (FUN_0800daf4) and PDF Sec 2.2:
 *   Bits [28:24] Source ID (SID)      : Master BMS = 0x14, Slave BMS = 0x1D, VCU = 0x01
 *   Bits [23:21] Reserved             : 0b000
 *   Bits [20:16] Destination ID (DID) : Target node ID, or Broadcast = 0x1F
 *   Bits [15:8]  Command (CMD)        : Primary command code
 *   Bits [7:0]   Sub-command / Index  : Parameter index or frame sequence number
 * ------------------------------------------------------------------------- */
#define BMS_CAN_MAKE_ID(sid, did, cmd, idx) \
    ((((uint32_t)(sid) & 0x1FU) << 24) | \
     (((uint32_t)(did) & 0x1FU) << 16) | \
     (((uint32_t)(cmd) & 0xFFU) << 8)  | \
     ((uint32_t)(idx)  & 0xFFU))

/* Backward-compatible 5-arg macro (bits [23:21] are reserved 0 per spec & binary) */
#define BMS_CAN_BUILD_ID(prio, sid, did, cmd, idx) \
    ((void)(prio), BMS_CAN_MAKE_ID((sid), (did), (cmd), (idx)))

#define BMS_CAN_EXTRACT_SID(can_id)  ((uint8_t)(((uint32_t)(can_id) >> 24) & 0x1FU))
#define BMS_CAN_EXTRACT_DID(can_id)  ((uint8_t)(((uint32_t)(can_id) >> 16) & 0x1FU))
#define BMS_CAN_EXTRACT_CMD(can_id)  ((uint8_t)(((uint32_t)(can_id) >> 8)  & 0xFFU))
#define BMS_CAN_EXTRACT_IDX(can_id)  ((uint8_t)((uint32_t)(can_id) & 0xFFU))

/* Standard CAN Node Identifiers */
#define BMS_CAN_DID_VCU              0x01U
#define BMS_CAN_DID_BROADCAST        0x1FU

/* -------------------------------------------------------------------------
 * Primary Command Identifiers (CMD, bits [15:8])
 * ------------------------------------------------------------------------- */
#define CAN_CMD_SET_ID               0x00U  /* Set equipment ID */
#define CAN_CMD_LONG_PACKET          0x04U  /* Multi-frame long packet transfer (CRC16) */
#define CAN_CMD_GENERAL_RESP         0x0AU  /* General acknowledgment response */
#define CAN_CMD_FAULT_BCAST          0x0EU  /* Fault code & protection bitmask broadcast (1000 ms) */
#define CAN_CMD_BCAST_STATUS         0x10U  /* Periodic status broadcasts (0x01, 0x02, 0x40) */
#define CAN_CMD_BCAST_PARALLEL_HW    0x11U  /* Broadcast Parallel Status (0x01) OR P2P HW/FW/SN Query (0x01..0x03) */
#define CAN_CMD_BCAST_RATING         0x12U  /* Periodic Pack Rating broadcast (0x01, 500 ms) */
#define CAN_CMD_TELEMETRY            0x14U  /* Point-to-point Telemetry Read/Write (0x01..0x06, 0x10) */
#define CAN_CMD_FIRMWARE_UPDATE      0x1AU  /* Online OTA upgrade trigger ("UPDATE", IDX 0x00) */
#define CAN_CMD_BUS_SILENCE          0x1FU  /* Broadcast CAN silence command ("SILENCE", IDX 0x1F) */
#define CAN_CMD_PACK_CONFIG          0x40U  /* PDF: Pack Rating (0x01) & Cycles (0x02); Binary alias for 0x10/0x14 */
#define CAN_CMD_CELL_VOLTAGES        0x41U  /* Cell voltages (0x03..0x08); Binary alias for 0x40 (0x01..0x02) & 0x42 (0x10..0x12) */
#define CAN_CMD_BALANCING_STATE      0x42U  /* PDF: Balancing status (0x10..0x12); Binary alias for 0x43 (0x01, 0x03, 0x04) */
#define CAN_CMD_CONTROL              0x43U  /* Protocol Ver (0x01), Switch Pack (0x03), Idle (0x04), Reset/Sleep (0xF2) */
#define CAN_CMD_CUSTOM_CALIB         0x44U  /* Binary-only: Custom calibration/protection params (0x01..0x03, 0xF1..0xF3) */

/* -------------------------------------------------------------------------
 * Sub-Command / Index Identifiers (IDX, bits [7:0])
 * ------------------------------------------------------------------------- */
/* CMD 0x10 (Periodic Broadcast) & CMD 0x14 (Point-to-Point Telemetry) */
#define CAN_IDX_TEL_CAPACITY_SOC     0x01U  /* Total cap, Rem cap, SOC, SOH, Max DSG I */
#define CAN_IDX_TEL_STATUS           0x01U  /* Backward-compatible alias */
#define CAN_IDX_TEL_VOLT_CURR_TEMP   0x02U  /* State, Current, Pack Voltage (24b), Max/Min Temp */
#define CAN_IDX_TEL_TEMPS            0x03U  /* Sensor count, NTC1..4, MOS temp, Connector temp */
#define CAN_IDX_TEL_ACCUM_MAH        0x04U  /* Accumulated Charge mAh (32b) & Discharge mAh (32b) */
#define CAN_IDX_TEL_DOOR_LOCK_WRITE  0x05U  /* Electric door lock discharge prohibit control (Write) */
#define CAN_IDX_TEL_DOOR_LOCK_READ   0x06U  /* Electric door lock discharge prohibit status (Read) */
#define CAN_IDX_TEL_MOS_STATUS       0x10U  /* P2P Switch/MOS/Key status (CMD 0x14 IDX 0x10) */
#define CAN_IDX_BCAST_MOS_STATUS     0x40U  /* Broadcast Switch/MOS/Key status (CMD 0x10 IDX 0x40) */

/* CMD 0x11 (Hardware / Firmware / Serial Number Query -> Long Packet 0x04) */
#define CAN_IDX_INFO_HWVER           0x01U  /* "HWVER" -> "A10.0" */
#define CAN_IDX_INFO_FWVER           0x02U  /* "FWVER" -> "V02.0" */
#define CAN_IDX_INFO_SN              0x03U  /* "READ"  -> Serial Number / Barcode */

/* CMD 0x40 (Pack Rating & Cycles) */
#define CAN_IDX_CFG_CAPACITY_SOH     0x01U  /* Backward-compatible alias */
#define CAN_IDX_CFG_RATING           0x01U  /* Strings (21), Parallels (1), Design Cap, Max I, Design Cycles */
#define CAN_IDX_CFG_CYCLES           0x02U  /* Cycle count, Uncharged hours, Est charge time */

/* CMD 0x41 (Cell Voltages) */
#define CAN_IDX_CELL_VOLT_1_4        0x03U  /* Cells 1..4 (mV, LE) */
#define CAN_IDX_CELL_VOLT_5_8        0x04U  /* Cells 5..8 (mV, LE) */
#define CAN_IDX_CELL_VOLT_9_12       0x05U  /* Cells 9..12 (mV, LE) */
#define CAN_IDX_CELL_VOLT_13_16      0x06U  /* Cells 13..16 (mV, LE) */
#define CAN_IDX_CELL_VOLT_17_20      0x07U  /* Cells 17..20 (mV, LE) */
#define CAN_IDX_CELL_VOLT_21_24      0x08U  /* Cells 21..24 (mV, LE) */

/* CMD 0x42 (Cell Balancing Status) */
#define CAN_IDX_BAL_CELL_1_8         0x10U  /* Cells 1..8 balancing flags */
#define CAN_IDX_BAL_CELL_9_16        0x11U  /* Cells 9..16 balancing flags */
#define CAN_IDX_BAL_CELL_17_24       0x12U  /* Cells 17..24 balancing flags */

/* CMD 0x43 (Control & System Status) */
#define CAN_IDX_CTRL_PROTOCOL_VER    0x01U  /* Protocol version query (returns 00 00 01 03 = v1.3) */
#define CAN_IDX_CTRL_SWITCH_PACK     0x03U  /* Dual-pack power supply switch command (0x01=Bat1, 0x02=Bat2) */
#define CAN_IDX_CTRL_IDLE_TIME       0x04U  /* Pack idle time in hours */
#define CAN_IDX_CTRL_RESET_SLEEP     0xF2U  /* Soft reset (0x01) / sleep trigger (0x02) */

/* CAN Raw Frame Structure */
typedef struct {
    uint32_t id;             /* 29-bit extended CAN ID */
    uint8_t  dlc;            /* Data length code (1 to 8) */
    uint8_t  data[8];        /* Data bytes */
} CanMessage_t;

/* CAN Driver & Protocol Prototypes */
void bms_can_init(uint8_t own_sid);
void bms_can_process_rx(const CanMessage_t *msg, BmsContext_t *ctx);
void bms_can_transmit(const CanMessage_t *msg);

/* Periodic Broadcast Scheduler (call every 100 ms from main loop) */
void bms_can_periodic_step(const BmsContext_t *ctx, uint32_t elapsed_ms);

/* Broadcast & Point-to-Point Frame Generators */
void bms_can_send_fault_broadcast(const BmsContext_t *ctx);
void bms_can_send_capacity_soh(const BmsContext_t *ctx);
void bms_can_send_volt_curr_temp(const BmsContext_t *ctx, uint8_t did, uint8_t cmd);
void bms_can_send_status(const BmsContext_t *ctx);
void bms_can_send_parallel_status(const BmsContext_t *ctx);
void bms_can_send_pack_rating(const BmsContext_t *ctx, uint8_t did, uint8_t cmd);
void bms_can_send_cycle_stats(const BmsContext_t *ctx, uint8_t did, uint8_t cmd);
void bms_can_send_temperatures(const BmsContext_t *ctx);
void bms_can_send_accum_mah(const BmsContext_t *ctx, uint8_t did, uint8_t cmd);
void bms_can_send_cell_voltage_group(const BmsContext_t *ctx, uint8_t did, uint8_t idx);
void bms_can_send_cell_voltages(const BmsContext_t *ctx);
void bms_can_send_balancing_group(const BmsContext_t *ctx, uint8_t did, uint8_t cmd, uint8_t idx);
void bms_can_send_general_response(uint8_t did, uint8_t ack_cmd, uint8_t ack_idx, uint8_t status);
void bms_can_send_long_packet(uint8_t did, uint8_t orig_cmd, uint8_t sub_cmd, const uint8_t *payload, uint16_t len);

/* CRC16 & Test Inspection Helpers */
uint16_t bms_crc16_modbus(const uint8_t *buf, uint16_t len);
uint32_t bms_can_get_tx_count(void);
const CanMessage_t *bms_can_get_last_tx(void);
const CanMessage_t *bms_can_get_tx_history(uint32_t index);
void bms_can_clear_tx_history(void);

#endif /* __BMS_CAN_H__ */
