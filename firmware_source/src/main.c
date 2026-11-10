/**
 * @file main.c
 * @brief Application Entry Point for 21S 70Ah NCM BMS Firmware
 * @note Matches the main entry point at 0x08022FE0 decompiled from firmware
 */

#include "bms_core.h"
#include "bms_can.h"
#include "bms_parallel.h"
#include "dvc1124_afe.h"
#include "bms_hal.h"

static BmsContext_t g_bms_ctx;

int main(void) {
    /* 1. Low-level Hardware Initialization */
    bms_hal_init();

    /* 2. Subsystem Initialization */
    bms_core_init(&g_bms_ctx);
    dvc1124_init();
    bms_can_init(g_bms_ctx.can_sid);
    bms_parallel_init(&g_bms_ctx);

    /* 3. Task Timers */
    uint32_t last_10ms = 0;
    uint32_t last_100ms = 0;
    uint32_t last_1000ms = 0;

    /* 4. Main Superloop */
    while (1) {
        uint32_t now = bms_hal_get_tick_ms();

        /* High-speed 10ms task: current sampling & fast protection */
        if ((now - last_10ms) >= 10) {
            last_10ms = now;
            bms_core_process_10ms_tick(&g_bms_ctx);
        }

        /* Standard 100ms task: cell voltage polling, temperatures, state machine, CAN periodic scheduler */
        if ((now - last_100ms) >= 100) {
            last_100ms = now;
            bms_core_process_100ms_tick(&g_bms_ctx);
            bms_parallel_process_tick(&g_bms_ctx);
            bms_can_periodic_step(&g_bms_ctx, 100);
        }

        /* Low-speed 1000ms task: SOC integration, SOH update, uptime */
        if ((now - last_1000ms) >= 1000) {
            last_1000ms = now;
            bms_core_process_1s_tick(&g_bms_ctx);
        }

        /* Event-driven CAN reception */
        CanMessage_t rx_msg;
        if (bms_hal_can_receive(&rx_msg.id, rx_msg.data, &rx_msg.dlc)) {
            bms_can_process_rx(&rx_msg, &g_bms_ctx);
        }
    }

    return 0;
}
