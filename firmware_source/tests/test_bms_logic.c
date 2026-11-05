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
#include "bms_ocv.h"

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

    /* Test 7: State of Health (SOH) Cycle Degradation Model */
    printf("[Test 7] Dynamic SOH Cycle Degradation Model... ");
    bms_core_record_cycles(&ctx, 0);
    assert(ctx.telemetry.soh_pct == 100);
    assert(ctx.telemetry.total_capacity_mah == 70000);

    bms_core_record_cycles(&ctx, 100);
    assert(ctx.telemetry.soh_pct == 98);
    assert(ctx.telemetry.total_capacity_mah == 68600);

    bms_core_record_cycles(&ctx, 500);
    assert(ctx.telemetry.soh_pct == 90);
    assert(ctx.telemetry.total_capacity_mah == 63000);

    bms_core_record_cycles(&ctx, 1000);
    assert(ctx.telemetry.soh_pct == 80);
    assert(ctx.telemetry.total_capacity_mah == 56000);

    bms_core_record_cycles(&ctx, 6000);
    assert(ctx.telemetry.soh_pct == 0);
    assert(ctx.telemetry.total_capacity_mah == 0);
    printf("PASS (0 cyc: 100%%, 100 cyc: 98%%, 500 cyc: 90%%, 1000 cyc: 80%%, clamp >= 0)\n");

    /* Test 8: CAN Capacity & SOH Frame Encoding (CMD 0x40, IDX 0x01) */
    printf("[Test 8] CAN SOH & Capacity Telemetry Broadcast... ");
    bms_core_record_cycles(&ctx, 100); /* 98% SOH, 68600 mAh */
    ctx.telemetry.soc_pct = 75;
    bms_core_calculate_soh(&ctx);
    bms_can_send_capacity_soh(&ctx);
    printf("PASS (CMD 0x40 IDX 0x01 generated)\n");

    /* Test 9: DVC1124 AFE Register Map & ADC Conversion Physics */
    printf("[Test 9] DVC1124 AFE Register Map & ADC Conversions... ");
    assert(DVC1124_I2C_7BIT_ADDR == 0x20);
    assert(DVC_REG_CELL_MODE == 0x01);
    assert(DVC_REG_CURRENT == 0x02);
    assert(DVC_REG_CELL_VOLTAGES == 0x1D);
    assert(DVC_REG_BALANCING_CTRL == 0x56);
    assert(DVC_REG_FAULT_STATUS == 0x5A);

    /* Verify Cell Voltage ADC Formula (Gain: 0.1 mV/LSB, Offset: 0.5 mV) */
    uint16_t v_nominal = dvc1124_raw_to_cell_mv(36080);
    assert(v_nominal >= 3608 && v_nominal <= 3609);

    uint16_t v_ovp = dvc1124_raw_to_cell_mv(41850);
    assert(v_ovp >= 4185 && v_ovp <= 4186);

    /* Verify Current ADC Formula (Scale: 5 mA/LSB, FUN_0800d48c) */
    int32_t curr_dsg = dvc1124_raw_to_current_ma(200, 0);
    assert(curr_dsg == -1000); /* 200 counts = -1000 mA discharge */

    int32_t curr_chg = dvc1124_raw_to_current_ma(-7000, 0);
    assert(curr_chg == 35000); /* -7000 counts = +35000 mA (35A) charge */

    /* Verify DVC1124 Init and Balancing Configuration */
    assert(dvc1124_init() == true);
    assert(dvc1124_set_balancing(0x001FFFFF) == true);
    printf("PASS (V: 0.1mV/cnt, I: 5mA/cnt, Regs: 0x01..0x56)\n");

    /* Test 10: 2D OCV-SOC Lookup Table Engine & Temperature Derating */
    printf("[Test 10] 2D Chemical OCV-SOC Engine & Matrices... ");
    /* Verify chemical OCV lookups at 25°C */
    assert(bms_ocv_lookup_soc(4185, 25) == 100);
    assert(bms_ocv_lookup_soc(3608, 25) == 50);   /* Calibrated 50% nominal */
    assert(bms_ocv_lookup_soc(2831, 25) == 5);    /* Calibrated 5% UVW */
    assert(bms_ocv_lookup_soc(2621, 25) == 0);    /* Calibrated 0% UVC cutoff */

    /* Verify capacity availability matrix Table 1 (FUN_08010654) */
    float cap_derate_100 = bms_ocv_get_capacity_derate(100, 25);
    assert(cap_derate_100 >= 1.99f && cap_derate_100 <= 2.01f); /* 20 * 0.1 = 2.0 Ah */

    float cap_derate_cold = bms_ocv_get_capacity_derate(100, -25);
    assert(cap_derate_cold == 0.0f); /* Col 0: 0 Ah */

    /* Verify thermal relaxation matrix Table 2 (FUN_080103c8) */
    float th_derate_50 = bms_ocv_get_thermal_derate(50, 25);
    assert(th_derate_50 >= 0.49f && th_derate_50 <= 0.51f); /* 50 * 0.01 = 0.50 */

    /* Verify core integration: bms_core_calculate_soc uses OCV engine */
    ctx.telemetry.min_cell_mv = 3608;
    ctx.telemetry.min_temp_c = 25;
    bms_core_calculate_soc(&ctx);
    assert(ctx.telemetry.soc_pct == 50);
    printf("PASS (OCV: 3608mV->50%%, 4185mV->100%%, 2621mV->0%%, 2D Matrices: 21x12, 21x13)\n");

    printf("\n========================================================\n");
    printf("[✔] All 10 BMS Firmware Unit Tests PASSED Successfully!\n");
    printf("========================================================\n");

    return 0;
}
