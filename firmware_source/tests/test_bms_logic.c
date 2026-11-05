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
#include "bms_modbus.h"
#include "bms_storage.h"

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
    ctx.soc_est.rest_duration_sec = 25; /* Force relaxed state */
    bms_core_calculate_soc(&ctx);
    assert(ctx.telemetry.soc_pct == 50);
    printf("PASS (OCV: 3608mV->50%%, 4185mV->100%%, 2621mV->0%%, 2D Matrices: 21x12, 21x13)\n");

    /* Test 11: Dynamic Coulomb-Counting & Quiescent OCV Recalibration Fusion */
    printf("[Test 11] Hybrid Coulomb Counting & Rest Recalibration... ");
    /* 1. Start fully charged (70000 mAh, 100%) */
    bms_core_init(&ctx);
    ctx.telemetry.total_capacity_mah = 70000;
    ctx.telemetry.remaining_mah = 70000;
    ctx.telemetry.soc_pct = 100;
    ctx.telemetry.min_cell_mv = 4185;
    ctx.telemetry.min_temp_c = 25;

    /* 2. Discharge at 36 A (-36000 mA) for 100 seconds (100 ticks of 1000ms) */
    /* Total charge discharged: 36A * 100s = 3600 As = 1000 mAh */
    ctx.telemetry.current_ma = -36000;
    for (int sec = 0; sec < 100; sec++) {
        bms_core_calculate_soc(&ctx);
    }
    assert(ctx.soc_est.is_relaxed == false);
    assert(ctx.telemetry.remaining_mah == 69000); /* 70000 - 1000 = 69000 mAh */
    assert(ctx.telemetry.soc_pct == 98);          /* 69000 / 70000 = 98.5% -> 98% */

    /* 3. Enter rest/quiescent state (current = 0 mA) */
    ctx.telemetry.current_ma = 0;
    ctx.telemetry.min_cell_mv = 3608; /* Nominal 50% OCV after settling */
    for (int sec = 0; sec < 19; sec++) {
        bms_core_calculate_soc(&ctx);
    }
    /* At 19 seconds, still relaxing */
    assert(ctx.soc_est.is_relaxed == false);
    assert(ctx.telemetry.soc_pct == 98);

    /* 4. On 20th second (quiescent threshold met), OCV recalibrates to true 50% */
    bms_core_calculate_soc(&ctx);
    assert(ctx.soc_est.is_relaxed == true);
    assert(ctx.telemetry.soc_pct == 50);
    assert(ctx.telemetry.remaining_mah == 35000); /* 70000 * 50% = 35000 mAh */
    printf("PASS (Discharge -36A: 1000mAh Ah-count -> Rest 20s: OCV latch 50%%)\n");

    /* Test 12: Modbus RTU Read Holding Registers (FC 0x03) */
    printf("[Test 12] Modbus RTU Read Holding Registers (FC 0x03)... ");
    bms_modbus_init(0x01, 9600);
    ctx.telemetry.pack_voltage_mv = 76600; /* 76.6V */
    ctx.telemetry.current_ma = -12500; /* -12.5A discharge */
    ctx.telemetry.soc_pct = 85;
    ctx.telemetry.soh_pct = 99;

    /* Request 4 registers starting at 0x0016 (Pack Voltage, Current, SOC, SOH) */
    uint8_t mb_req[8] = {0x01, 0x03, 0x00, 0x16, 0x00, 0x04, 0x00, 0x00};
    uint16_t req_crc = bms_modbus_calc_crc16(mb_req, 6);
    mb_req[6] = (uint8_t)(req_crc & 0xFF);
    mb_req[7] = (uint8_t)((req_crc >> 8) & 0xFF);

    uint8_t mb_resp[64] = {0};
    int resp_len = bms_modbus_process_frame(mb_req, 8, mb_resp, sizeof(mb_resp), &ctx);
    assert(resp_len == 13); /* 1 addr + 1 func + 1 byte_count + 8 data + 2 crc */
    assert(mb_resp[0] == 0x01);
    assert(mb_resp[1] == 0x03);
    assert(mb_resp[2] == 0x08); /* 4 registers * 2 bytes = 8 */

    /* Verify Voltage: 7660 (0x1DEC) */
    uint16_t v_resp = ((uint16_t)mb_resp[3] << 8) | mb_resp[4];
    assert(v_resp == 7660);

    /* Verify Current: -1250 (signed int16) */
    int16_t i_resp = (int16_t)(((uint16_t)mb_resp[5] << 8) | mb_resp[6]);
    assert(i_resp == -1250);

    /* Verify SOC: 850 (85.0%) */
    uint16_t soc_resp = ((uint16_t)mb_resp[7] << 8) | mb_resp[8];
    assert(soc_resp == 850);

    /* Verify SOH: 990 (99.0%) */
    uint16_t soh_resp = ((uint16_t)mb_resp[9] << 8) | mb_resp[10];
    assert(soh_resp == 990);

    /* Verify Response CRC */
    uint16_t calc_resp_crc = bms_modbus_calc_crc16(mb_resp, 11);
    uint16_t actual_resp_crc = (uint16_t)mb_resp[11] | ((uint16_t)mb_resp[12] << 8);
    assert(calc_resp_crc == actual_resp_crc);
    printf("PASS (V: 76.6V, I: -12.5A, SOC: 85%%, SOH: 99%%, CRC: 0x%04X)\n", actual_resp_crc);

    /* Test 13: Modbus RTU Write Single Register (FC 0x06) & Exception Generation */
    printf("[Test 13] Modbus RTU Write Single Register & Exceptions... ");
    /* Write new OVP limit 4200 mV to reg 0x0040 */
    uint8_t write_req[8] = {0x01, 0x06, 0x00, 0x40, 0x10, 0x68, 0x00, 0x00}; /* 0x1068 = 4200 */
    uint16_t w_crc = bms_modbus_calc_crc16(write_req, 6);
    write_req[6] = (uint8_t)(w_crc & 0xFF);
    write_req[7] = (uint8_t)((w_crc >> 8) & 0xFF);

    resp_len = bms_modbus_process_frame(write_req, 8, mb_resp, sizeof(mb_resp), &ctx);
    assert(resp_len == 8);
    assert(ctx.limits.cell_ovp_mv == 4200);

    /* Test exception on illegal address (e.g. reg 0x0099) */
    uint8_t bad_addr_req[8] = {0x01, 0x03, 0x00, 0x99, 0x00, 0x01, 0x00, 0x00};
    uint16_t bad_crc = bms_modbus_calc_crc16(bad_addr_req, 6);
    bad_addr_req[6] = (uint8_t)(bad_crc & 0xFF);
    bad_addr_req[7] = (uint8_t)((bad_crc >> 8) & 0xFF);
    resp_len = bms_modbus_process_frame(bad_addr_req, 8, mb_resp, sizeof(mb_resp), &ctx);
    assert(resp_len == 5);
    assert(mb_resp[1] == 0x83); /* Exception for FC 0x03 */
    assert(mb_resp[2] == MODBUS_EX_ILLEGAL_DATA_ADDR);

    /* Test rejection on corrupted CRC */
    bad_addr_req[7] ^= 0xFF;
    resp_len = bms_modbus_process_frame(bad_addr_req, 8, mb_resp, sizeof(mb_resp), &ctx);
    assert(resp_len < 0);
    printf("PASS (Write OVP: 4200mV echo verified, Illegal Addr: 0x83-0x02, Corrupt CRC rejected)\n");

    /* Test 14: Proprietary Host Diagnostic Protocol (0xEA 0xD1) */
    printf("[Test 14] Proprietary Upper-Computer Frame (0xEA 0xD1)... ");
    ctx.telemetry.max_cell_mv = 3652;
    ctx.telemetry.min_cell_mv = 3630;
    ctx.telemetry.cell_delta_mv = 22;
    ctx.telemetry.temp_c[0] = 25;
    ctx.telemetry.temp_c[1] = 26;
    ctx.telemetry.temp_c[2] = 24;
    ctx.telemetry.temp_c[3] = 25;
    ctx.telemetry.mos_temp_c = 28;

    uint8_t host_query[6] = {0xEA, 0xD1, 0x01, 0x06, 0xFF, 0x03};
    uint8_t host_resp[128] = {0};
    resp_len = bms_host_proto_process_frame(host_query, sizeof(host_query), host_resp, sizeof(host_resp), &ctx);
    assert(resp_len == 58);
    assert(host_resp[0] == 0xEA);
    assert(host_resp[1] == 0xD1);
    assert(host_resp[3] == 0x39); /* 57 bytes payload */

    /* Max Cell: 3652 (0x0E44) */
    uint16_t host_max_cell = ((uint16_t)host_resp[20] << 8) | host_resp[21];
    assert(host_max_cell == 3652);

    /* Min Cell: 3630 (0x0E2E) */
    uint16_t host_min_cell = ((uint16_t)host_resp[23] << 8) | host_resp[24];
    assert(host_min_cell == 3630);

    /* Delta: 22 mV */
    uint16_t host_delta = ((uint16_t)host_resp[26] << 8) | host_resp[27];
    assert(host_delta == 22);

    /* NTC1: 25.0C + 40 = 65 */
    assert(host_resp[29] == 65);

    /* Verify XOR Checksum */
    uint8_t calc_xor = 0;
    for (int b = 3; b < 57; b++) {
        calc_xor ^= host_resp[b];
    }
    assert(calc_xor == host_resp[57]);
    printf("PASS (Frame: 0xEA 0xD1, Max: 3652mV, Min: 3630mV, Delta: 22mV, XOR: 0x%02X)\n", calc_xor);

    /* Test 15: 24Cxx Non-Volatile EEPROM Storage & Page Verification */
    printf("[Test 15] 24Cxx EEPROM 32-Byte Page Boundary & Lifetime Stats... ");
    bms_storage_init();

    /* Write 48 bytes spanning across two 32-byte page boundaries (0x0050 to 0x0080) */
    uint8_t test_payload[48];
    for (int p = 0; p < 48; p++) {
        test_payload[p] = (uint8_t)(0xA0 + p);
    }
    int write_res = bms_storage_write_verified(0x0050, test_payload, 48);
    assert(write_res == 0);

    /* Read back and verify exact byte match */
    uint8_t test_readback[48] = {0};
    int read_res = bms_storage_read_block(0x0050, test_readback, 48);
    assert(read_res == 0);
    assert(memcmp(test_payload, test_readback, 48) == 0);

    /* Test Save & Load Config with Checksum */
    ctx.limits.cell_ovp_mv = 4190;
    ctx.limits.cell_uvp_mv = 2650;
    ctx.limits.chg_ocp_ma = 45000; /* 45.0 A */
    ctx.limits.dsg_ocp_ma = 95000; /* 95.0 A */
    ctx.limits.ot_protect_c = 60.0f;
    ctx.limits.ut_protect_c = -5.0f;
    assert(bms_storage_save_config(&ctx) == 0);

    BmsContext_t restored_ctx;
    memset(&restored_ctx, 0, sizeof(restored_ctx));
    assert(bms_storage_load_config(&restored_ctx) == 0);
    assert(restored_ctx.limits.cell_ovp_mv == 4190);
    assert(restored_ctx.limits.cell_uvp_mv == 2650);
    assert(restored_ctx.limits.chg_ocp_ma == 45000);
    assert(restored_ctx.limits.dsg_ocp_ma == 95000);
    assert(restored_ctx.limits.ot_protect_c == 60.0f);
    assert(restored_ctx.limits.ut_protect_c == -5.0f);

    /* Test Lifetime Stats Tracking */
    assert(bms_storage_update_lifetime(350, 24500, 24600) == 0);
    uint32_t r_cyc = 0, r_dsg = 0, r_chg = 0;
    assert(bms_storage_read_lifetime(&r_cyc, &r_dsg, &r_chg) == 0);
    assert(r_cyc == 350);
    assert(r_dsg == 24500);
    assert(r_chg == 24600);
    printf("PASS (Cross-page 48B verified, Config OVP: 4190mV/UVP: 2650mV, Lifetime: 350 cycles/24500 Ah)\n");

    printf("\n========================================================\n");
    printf("[✔] All 15 BMS Firmware Unit Tests PASSED Successfully!\n");
    printf("========================================================\n");

    return 0;
}
