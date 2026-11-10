/**
 * @file bms_parallel.h
 * @brief Multi-Pack Dual Battery Parallel Arbitration & Switching Logic
 * @note Implements 5% switching strategy and Master/Slave negotiation
 */

#ifndef __BMS_PARALLEL_H__
#define __BMS_PARALLEL_H__

#include <stdint.h>
#include <stdbool.h>
#include "bms_types.h"

/* Dual-Pack Discharge Switching Stage */
typedef enum {
    PARALLEL_STAGE_MASTER_ACTIVE = 0,   /**< Master discharges down to 5% */
    PARALLEL_STAGE_SWITCHING_TO_SLAVE,  /**< Handshake and transition to Slave */
    PARALLEL_STAGE_SLAVE_ACTIVE,        /**< Slave discharges from 100% down to 0% */
    PARALLEL_STAGE_SWITCHING_TO_MASTER, /**< Handshake back to Master */
    PARALLEL_STAGE_MASTER_REMAINDER,    /**< Master exhausts final 5% */
    PARALLEL_STAGE_PACKS_DEPLETED       /**< Both packs empty (shutdown) */
} ParallelStage_t;

/* Parallel Management Context */
typedef struct {
    ParallelStage_t stage;
    uint8_t         active_pack_id;      /**< 0x14 (Master) or 0x1D (Slave) */
    uint8_t         peer_soc_pct;        /**< Remote pack SOC */
    uint32_t        peer_pack_voltage_mv;/**< Remote pack voltage */
    bool            peer_connected;      /**< Heartbeat received from second pack */
    bool            peer_in_uvp;         /**< Remote pack in under-voltage protection */
    uint32_t        last_peer_heartbeat_ms;
} BmsParallelManager_t;

/* Internal Multi-Pack Parallel Bus Frame IDs (reconstructed from FUN_0801ca08 / FUN_0801f044) */
#define BMS_PARALLEL_CAN_ID_HEARTBEAT   0x141DF001UL
#define BMS_PARALLEL_CAN_ID_SYNC_BASE   0x00000101UL /* 0x101..0x106 Master->Slave sync */
#define BMS_PARALLEL_CAN_ID_STATUS_BASE 0x00000201UL /* 0x201..0x203 Slave->Master status */

/* Function Prototypes */
void bms_parallel_init(BmsContext_t *ctx);
void bms_parallel_evaluate_role(BmsContext_t *ctx, const char *local_sn, const char *peer_sn);
void bms_parallel_process_tick(BmsContext_t *ctx);
bool bms_parallel_request_switch(BmsContext_t *ctx, uint8_t target_pack_id);
void bms_parallel_send_heartbeat(const BmsContext_t *ctx);
bool bms_parallel_process_can_rx(BmsContext_t *ctx, uint32_t can_id, const uint8_t *data, uint8_t dlc);
const BmsParallelManager_t *bms_parallel_get_manager(void);

#endif /* __BMS_PARALLEL_H__ */
