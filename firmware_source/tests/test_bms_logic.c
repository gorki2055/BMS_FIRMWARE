/**
 * @file test_bms_logic.c
 * @brief Native Host Unit Test Runner for BMS Firmware Logic
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "bms_core.h"
#include "bms_can.h"
#include "bms_parallel.h"
#include "dvc1124_afe.h"

int main(void) {
    printf("========================================================\n");
    printf("Running BMS Firmware Core Unit Tests (Native Host)\n");
    printf("========================================================\n\n");

    /* Test 1: DVC1124 CRC8 Calculation */
    printf("[Test 1] DVC1124 CRC8 Algorithm... ");
    uint8_t sample_data[] = {0x00, 0x12, 0x34};
    uint8_t crc8 = dvc1124_calc_crc8(sample_data, sizeof(sample_data));
    assert(crc8 != 0x00);
    printf("PASS (CRC8 = 0x%02X)\n", crc8);

    /* Test 2: CAN Modbus CRC16 Calculation */
    printf("[Test 2] Modbus CRC16 Algorithm... ");
    uint8_t modbus_data[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x0A};
    uint16_t crc16 = bms_crc16_modbus(modbus_data, sizeof(modbus_data));
    assert(crc16 == 0xCDC5);
    printf("PASS (CRC16 = 0x%04X)\n", crc16);

    /* Test 3: BMS Context Initialization & Calibrated Limits */
    printf("[Test 3] BMS Initialization & Calibration Thresholds... ");
    BmsContext_t ctx;
    bms_core_init(&ctx);
    assert(ctx.state == BMS_STATE_STANDBY);
    assert(ctx.telemetry.total_capacity_mah == 70000);
    assert(ctx.can_sid == BMS_CAN_MASTER_SID);
    printf("PASS (State: STANDBY, Capacity: 70Ah, SID: 0x%02X)\n", ctx.can_sid);

    /* Test 4: Over-Voltage Protection (OVP) Check */
    printf("[Test 4] Cell Over-Voltage Protection (OVP @ 4185 mV)... ");
    ctx.telemetry.max_cell_mv = 4190;
    bms_core_check_protections(&ctx);
    assert(ctx.faults.bits.cell_ovp == 1);
    /* Test hysteresis release */
    ctx.telemetry.max_cell_mv = 4090;
    bms_core_check_protections(&ctx);
    assert(ctx.faults.bits.cell_ovp == 0);
    printf("PASS (OVP tripped at 4190mV, released at 4090mV)\n");

    /* Test 5: Under-Voltage Cutoff (UVC @ 2621 mV) */
    printf("[Test 5] Cell Under-Voltage Protection (UVC @ 2621 mV)... ");
    ctx.telemetry.min_cell_mv = 2600;
    bms_core_check_protections(&ctx);
    assert(ctx.faults.bits.cell_uvp == 1);
    printf("PASS (UVP tripped at 2600mV)\n");

    /* Test 6: Multi-Pack Role Arbitration via Serial Number */
    printf("[Test 6] Multi-Pack Serial Number Arbitration... ");
    bms_parallel_evaluate_role(&ctx, "6495-SPB24-006-A01", "6495-SPB24-006-A02");
    assert(ctx.role == BMS_ROLE_MASTER);
    assert(ctx.can_sid == 0x14);

    bms_parallel_evaluate_role(&ctx, "6495-SPB24-006-A05", "6495-SPB24-006-A02");
    assert(ctx.role == BMS_ROLE_SLAVE);
    assert(ctx.can_sid == 0x1D);
    printf("PASS (Master = 0x14, Slave = 0x1D)\n");

    printf("\n========================================================\n");
    printf("[✔] All 6 BMS Firmware Unit Tests PASSED Successfully!\n");
    printf("========================================================\n");

    return 0;
}
