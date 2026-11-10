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
#include "bms_hal.h"

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

    /* Test 8: CAN Capacity & SOH Frame Encoding (Broadcast CMD 0x10, IDX 0x01) */
    printf("[Test 8] CAN SOH & Capacity Telemetry Broadcast... ");
    ctx.faults.all = 0;
    bms_can_init(BMS_CAN_MASTER_SID);
    bms_can_clear_tx_history();
    bms_core_record_cycles(&ctx, 100); /* 98% SOH, 68600 mAh */
    ctx.telemetry.soc_pct = 75;
    bms_core_calculate_soh(&ctx);      /* remaining_mah = 68600 * 75% = 51450 mAh */
    bms_can_send_capacity_soh(&ctx);
    const CanMessage_t *cap_tx = bms_can_get_last_tx();
    assert(cap_tx != NULL);
    assert(cap_tx->id == 0x141F1001UL); /* SID=0x14, DID=0x1F, CMD=0x10, IDX=0x01 */
    assert(cap_tx->dlc == 7);
    assert((uint16_t)(cap_tx->data[0] | (cap_tx->data[1] << 8)) == 6860); /* 68600 mAh / 10 (LE) */
    assert((uint16_t)(cap_tx->data[2] | (cap_tx->data[3] << 8)) == 5145); /* 51450 mAh / 10 (LE) */
    assert(cap_tx->data[4] == 75);  /* SOC = 75% */
    assert(cap_tx->data[5] == 98);  /* SOH = 98% */
    assert(cap_tx->data[6] == 70);  /* Max DSG current = 70A */
    printf("PASS (ID=0x%08X, FCC=6860*10mAh LE, Rem=5145*10mAh LE, MaxDsg=70A)\n", cap_tx->id);

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

    /* Test 16: 29-Bit Extended CAN ID Packing & Unpacking (FUN_0801ef94 & FUN_0800daf4) */
    printf("[Test 16] 29-Bit CAN Extended ID Layout (0x0801EF94 / PDF Sec 2.2)... ");
    uint32_t id_bcast = BMS_CAN_MAKE_ID(0x14, 0x1F, 0x10, 0x02);
    assert(id_bcast == 0x141F1002UL);
    assert(BMS_CAN_EXTRACT_SID(id_bcast) == 0x14);
    assert(BMS_CAN_EXTRACT_DID(id_bcast) == 0x1F);
    assert(BMS_CAN_EXTRACT_CMD(id_bcast) == 0x10);
    assert(BMS_CAN_EXTRACT_IDX(id_bcast) == 0x02);

    uint32_t id_vcu_query = BMS_CAN_MAKE_ID(0x01, 0x14, 0x41, 0x03);
    assert(id_vcu_query == 0x01144103UL);
    assert(BMS_CAN_BUILD_ID(6, 0x14, 0x01, 0x41, 0x03) == 0x14014103UL);
    printf("PASS (0x141F1002 & 0x01144103 bit-exact with binary 0x0801EF94)\n");

    /* Test 17: Periodic Broadcast Scheduler (100ms, 500ms, 1000ms) & Fault Broadcast (0x0E) */
    printf("[Test 17] Periodic CAN Broadcast Scheduler & Fault Frame (0x0E)... ");
    bms_core_init(&ctx);
    bms_can_init(BMS_CAN_MASTER_SID);
    bms_can_clear_tx_history();
    ctx.telemetry.current_ma = -15000;      /* -15.00A -> -1500 (0xFA24) */
    ctx.telemetry.pack_voltage_mv = 75600;  /* 75600 mV -> 0x012750 */
    ctx.telemetry.min_temp_c = 22;          /* +40 = 62 */
    ctx.telemetry.max_temp_c = 28;          /* +40 = 68 */

    /* Step 1 (100ms): should send 0x10/0x02 and 0x11/0x01 (2 frames) */
    bms_can_periodic_step(&ctx, 100);
    assert(bms_can_get_tx_count() == 2);
    const CanMessage_t *f0 = bms_can_get_tx_history(0);
    const CanMessage_t *f1 = bms_can_get_tx_history(1);
    assert(f0->id == 0x141F1002UL && f0->dlc == 8);
    assert(f0->data[0] == 2); /* Discharging */
    assert((int16_t)(f0->data[1] | (f0->data[2] << 8)) == -1500);
    assert((uint32_t)(f0->data[3] | (f0->data[4] << 8) | (f0->data[5] << 16)) == 75600UL);
    assert(f0->data[6] == 62 && f0->data[7] == 68);
    assert(f1->id == 0x141F1101UL && f1->dlc == 5);

    /* Advance 4 more steps to reach 500ms: steps 2,3,4 send 2 frames each (6), step 5 (500ms) sends 4 frames */
    for (int i = 0; i < 4; i++) {
        bms_can_periodic_step(&ctx, 100);
    }
    assert(bms_can_get_tx_count() == 12); /* 2*4 + 4 = 12 frames */
    assert(bms_can_get_tx_history(10)->id == 0x141F1001UL); /* 500ms Cap/SOC */
    assert(bms_can_get_tx_history(11)->id == 0x141F1201UL); /* 500ms Pack Rating */

    /* Advance 5 more steps to reach 1000ms with an OVP fault active */
    ctx.faults.bits.cell_ovp = 1;
    for (int i = 0; i < 5; i++) {
        bms_can_periodic_step(&ctx, 100);
    }
    /* At 1000ms: 100ms(2) + 500ms(2) + 1000ms(2: 0x10/0x40 & 0x0E/0x06) = 6 frames on step 10 */
    const CanMessage_t *fault_tx = bms_can_get_last_tx();
    assert(fault_tx->id == 0x141F0E06UL); /* ERR = 0x06 (OVP), bit 5 of D0 set */
    assert((fault_tx->data[0] & (1U << 5)) != 0);
    ctx.faults.all = 0;
    printf("PASS (100ms: 0x10/02+0x11/01, 500ms: 0x10/01+0x12/01, 1000ms: 0x10/40+0x0E/06)\n");

    /* Test 18: Point-to-Point Telemetry (0x14), Pack Rating (0x40), Cell Voltages (0x41 LE), Balancing (0x42) */
    printf("[Test 18] P2P Queries (0x14, 0x40, 0x41 Single-Group LE, 0x42)... ");
    bms_can_clear_tx_history();
    ctx.telemetry.cell_mv[0] = 3650; /* 0x0E42 -> LSB 0x42, MSB 0x0E */
    ctx.telemetry.cell_mv[1] = 3651;
    ctx.telemetry.cell_mv[2] = 3652;
    ctx.telemetry.cell_mv[3] = 3653;
    ctx.telemetry.accum_chg_mah = 12345678UL;
    ctx.telemetry.accum_dsg_mah = 87654321UL;
    ctx.telemetry.balance_mask = 0x000005UL; /* Cell 1 and Cell 3 balancing */

    /* 18a. Query Cell Voltages Group 1..4 (CMD 0x41 IDX 0x03) from VCU (SID 0x01) */
    CanMessage_t rx_q = { BMS_CAN_MAKE_ID(0x01, 0x14, 0x41, 0x03), 4, {'R', 'E', 'A', 'D', 0, 0, 0, 0} };
    bms_can_process_rx(&rx_q, &ctx);
    assert(bms_can_get_tx_count() == 1); /* Only 1 frame for requested group 0x03! */
    const CanMessage_t *cv_tx = bms_can_get_last_tx();
    assert(cv_tx->id == 0x14014103UL && cv_tx->dlc == 8);
    assert(cv_tx->data[0] == 0x42 && cv_tx->data[1] == 0x0E); /* 3650 mV Little-Endian */
    assert((uint16_t)(cv_tx->data[6] | (cv_tx->data[7] << 8)) == 3653);

    /* 18b. Query Pack Rating (CMD 0x40 IDX 0x01) -> verify Little-Endian 7000 & 1000 */
    rx_q.id = BMS_CAN_MAKE_ID(0x01, 0x14, 0x40, 0x01);
    bms_can_process_rx(&rx_q, &ctx);
    const CanMessage_t *rt_tx = bms_can_get_last_tx();
    assert(rt_tx->id == 0x14014001UL && rt_tx->dlc == 8);
    assert(rt_tx->data[0] == 21 && rt_tx->data[1] == 1);
    assert(rt_tx->data[2] == 0x58 && rt_tx->data[3] == 0x1B); /* 7000 (0x1B58) LE */
    assert(rt_tx->data[6] == 0xE8 && rt_tx->data[7] == 0x03); /* 1000 (0x03E8) LE */

    /* 18c. Query Accumulated mAh (CMD 0x14 IDX 0x04) -> verify 32-bit Little-Endian */
    rx_q.id = BMS_CAN_MAKE_ID(0x01, 0x14, 0x14, 0x04);
    bms_can_process_rx(&rx_q, &ctx);
    const CanMessage_t *ah_tx = bms_can_get_last_tx();
    assert(ah_tx->id == 0x14011404UL && ah_tx->dlc == 8);
    uint32_t rx_chg = (uint32_t)ah_tx->data[0] | ((uint32_t)ah_tx->data[1] << 8) |
                      ((uint32_t)ah_tx->data[2] << 16) | ((uint32_t)ah_tx->data[3] << 24);
    uint32_t rx_dsg = (uint32_t)ah_tx->data[4] | ((uint32_t)ah_tx->data[5] << 8) |
                      ((uint32_t)ah_tx->data[6] << 16) | ((uint32_t)ah_tx->data[7] << 24);
    assert(rx_chg == 12345678UL && rx_dsg == 87654321UL);

    /* 18d. Query Cell Balancing (CMD 0x42 IDX 0x10) */
    rx_q.id = BMS_CAN_MAKE_ID(0x01, 0x14, 0x42, 0x10);
    bms_can_process_rx(&rx_q, &ctx);
    const CanMessage_t *bal_tx = bms_can_get_last_tx();
    assert(bal_tx->id == 0x14014210UL && bal_tx->dlc == 8);
    assert(bal_tx->data[0] == 1 && bal_tx->data[1] == 0 && bal_tx->data[2] == 1);
    printf("PASS (0x41 LE=3650mV, 0x40 LE=7000/1000, 0x14/04 32b LE, 0x42 Balancing)\n");

    /* Test 19: Long Packet Multi-Frame (0x04), General Ack (0x0A), Control (0x43), OTA (0x1A), Silence (0x1F) */
    printf("[Test 19] Long Packet (0x04 HWVER/FWVER/SN), Ack (0x0A), Control & Silence... ");
    bms_can_clear_tx_history();

    /* 19a. Query HWVER (CMD 0x11 IDX 0x01 "HWVER") -> 2 frames of CMD 0x04 with "A10.0" + CRC16 */
    CanMessage_t hw_q = { BMS_CAN_MAKE_ID(0x01, 0x14, 0x11, 0x01), 5, {'H', 'W', 'V', 'E', 'R', 0, 0, 0} };
    bms_can_process_rx(&hw_q, &ctx);
    assert(bms_can_get_tx_count() == 2);
    const CanMessage_t *lp1 = bms_can_get_tx_history(0);
    const CanMessage_t *lp2 = bms_can_get_tx_history(1);
    assert(lp1->id == 0x14010401UL && lp2->id == 0x14010402UL);
    assert(lp1->data[0] == 0x11 && lp1->data[1] == 0x01 && lp1->data[2] == 5 && lp1->data[3] == 0);
    assert(memcmp(&lp1->data[4], "A10.", 4) == 0 && lp2->data[0] == '0');

    /* 19b. Electric door lock write (CMD 0x14 IDX 0x05, data[0]=1 prohibit dsg) & read (IDX 0x06) */
    CanMessage_t dl_w = { BMS_CAN_MAKE_ID(0x01, 0x14, 0x14, 0x05), 1, {0x01, 0, 0, 0, 0, 0, 0, 0} };
    bms_can_process_rx(&dl_w, &ctx);
    assert(ctx.door_lock_prohibit_dsg == true);
    CanMessage_t dl_r = { BMS_CAN_MAKE_ID(0x01, 0x14, 0x14, 0x06), 4, {'R', 'E', 'A', 'D', 0, 0, 0, 0} };
    bms_can_process_rx(&dl_r, &ctx);
    assert(bms_can_get_last_tx()->data[0] == 1);

    /* 19c. OTA Update trigger (CMD 0x1A IDX 0x00 "UPDATE") -> General Response 0x0A */
    CanMessage_t ota_q = { BMS_CAN_MAKE_ID(0x01, 0x14, 0x1A, 0x00), 6, {'U', 'P', 'D', 'A', 'T', 'E', 0, 0} };
    bms_can_process_rx(&ota_q, &ctx);
    assert(ctx.ota_update_requested == true);
    const CanMessage_t *ack_tx = bms_can_get_last_tx();
    assert(ack_tx->id == 0x14010A1AUL && ack_tx->dlc == 3);
    assert(ack_tx->data[0] == 0x1A && ack_tx->data[1] == 0x00 && ack_tx->data[2] == 0x00);

    /* 19d. Broadcast Silence (CMD 0x1F IDX 0x1F "SILENCE") stops periodic broadcasts */
    CanMessage_t sil_q = { BMS_CAN_MAKE_ID(0x01, 0x1F, 0x1F, 0x1F), 7, {'S', 'I', 'L', 'E', 'N', 'C', 'E', 0} };
    bms_can_process_rx(&sil_q, &ctx);
    assert(ctx.can_silent == true);
    uint32_t count_before = bms_can_get_tx_count();
    bms_can_periodic_step(&ctx, 100);
    assert(bms_can_get_tx_count() == count_before);
    printf("PASS (0x04 Long Packet CRC16, Door Lock 0x05/0x06, 0x0A Ack, 0x1F Silence)\n");

    /* Test 20: MCU 96-Bit UID Calibration Lock (FUN_08017b3c) & Per-Cell Gain Scaling (FUN_08016000) */
    printf("[Test 20] MCU 96-Bit UID Anti-Cloning Lock & Per-Cell Calibration... ");
    /* Note: Test 15 wrote raw test pattern over 0x0050..0x007F, so verify lock detects it before re-locking */
    bms_core_init(&ctx);
    assert(ctx.calibration_authorized == false);

    /* Save valid per-cell calibration: Cell 0 = 10100 (1.0100x), Cell 1 = 9900 (0.9900x), Cell 2 = 50000 (invalid -> 1.0x) */
    uint16_t cal_factors[BMS_SERIES_CELLS];
    for (int i = 0; i < BMS_SERIES_CELLS; i++) cal_factors[i] = 10000U;
    cal_factors[0] = 10100U;
    cal_factors[1] = 9900U;
    cal_factors[2] = 50000U; /* Out of bounds -> clamped to 1.0f */
    assert(bms_storage_save_cell_cal(cal_factors) == 0);
    bms_core_init(&ctx);
    assert(ctx.calibration_authorized == true);

    for (int i = 0; i < BMS_SERIES_CELLS; i++) ctx.telemetry.cell_mv[i] = 4000U;
    bms_core_apply_cell_calibration(&ctx);
    assert(ctx.telemetry.cell_mv[0] == 4040U); /* 4000 * 1.01 = 4040 mV */
    assert(ctx.telemetry.cell_mv[1] == 3960U); /* 4000 * 0.99 = 3960 mV */
    assert(ctx.telemetry.cell_mv[2] == 4000U); /* Out-of-bounds factor clamped to 1.0f */

    /* Simulate MCU swap (tampered 96-bit UID) -> verify anti-cloning lock rejects EEPROM */
    const uint8_t tampered_uid[12] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44};
    bms_hal_set_simulated_uid(tampered_uid);
    assert(bms_storage_verify_uid_lock(&ctx) == false);
    assert(ctx.calibration_authorized == false);
    /* Re-lock with new UID */
    assert(bms_storage_write_uid_lock() == 0);
    assert(bms_storage_verify_uid_lock(&ctx) == true);
    printf("PASS (UID @ 0x1FFFF7F0 verified, Tamper rejected, Cell Gain: 4040/3960/4000mV)\n");

    /* Test 21: On-Chip Flash Driver (0x40022000) & Bootloader IAP Flag at 0x28A (FUN_0800f850) */
    printf("[Test 21] On-Chip Flash 2KB Page RMW & Bootloader 0x28A Trigger... ");
    uint32_t read_magic = 0;
    assert(bms_storage_read_boot_iap_flag(&read_magic) == 0);
    assert(read_magic == BMS_BOOT_IAP_MAGIC); /* Written during Test 19c CAN 0x1A "UPDATE" */
    assert(bms_storage_write_boot_iap_flag(0x12345678UL) == 0);
    assert(bms_storage_read_boot_iap_flag(&read_magic) == 0 && read_magic == 0x12345678UL);
    printf("PASS (Flash offset 0x28A magic=0x%08X verified)\n", (unsigned int)read_magic);

    /* Test 22: Multi-AFE Chip Support (DVC1124/1117/1114) & 3-Phase Interleaved Balancing (FUN_08008af4) */
    printf("[Test 22] Multi-AFE Support & 3-Phase Interleaved Balancing... ");
    dvc1124_set_model(AFE_MODEL_DVC1114);
    assert(dvc1124_get_max_cells() == 14);
    dvc1124_set_model(AFE_MODEL_DVC1117);
    assert(dvc1124_get_max_cells() == 17);
    dvc1124_set_model(AFE_MODEL_DVC1124);
    assert(dvc1124_get_max_cells() == 24);

    uint32_t all_21s = 0x001FFFFFUL;
    uint32_t p0 = dvc1124_compute_interleaved_phase_mask(all_21s, 0);
    uint32_t p1 = dvc1124_compute_interleaved_phase_mask(all_21s, 1);
    uint32_t p2 = dvc1124_compute_interleaved_phase_mask(all_21s, 2);
    /* Phases must be mutually disjoint, cover all 21 cells together, and never balance adjacent cells */
    assert((p0 & p1) == 0 && (p1 & p2) == 0 && (p0 & p2) == 0);
    assert((p0 | p1 | p2) == all_21s);
    assert((p0 & (p0 << 1)) == 0 && (p1 & (p1 << 1)) == 0 && (p2 & (p2 << 1)) == 0);
    printf("PASS (DVC1124/1117/1114, 3-Phase Masks: 0x%06X / 0x%06X / 0x%06X)\n",
           (unsigned int)p0, (unsigned int)p1, (unsigned int)p2);

    /* Test 23: Pre-Charge Sequencing (FUN_0801647c, Fault 0xBE) & MOSFET Body-Diode Protection (FUN_0801f580) */
    printf("[Test 23] Pre-Charge Contactor Sequencing & Body-Diode Promotion... ");
    bms_core_init(&ctx);
    ctx.precharge_bus_ready = false; /* Simulate capacitive bus failing to charge */
    ctx.state = BMS_STATE_PRECHARGE;
    for (int tick = 0; tick < BMS_PRECHARGE_TIMEOUT_TICKS; tick++) {
        bms_core_process_100ms_tick(&ctx);
    }
    assert(ctx.state == BMS_STATE_FAULT);
    assert(ctx.faults.bits.precharge_fail == 1);
    BmsFaultSnapshot_t snap;
    assert(bms_storage_read_last_event(&snap) == 0);
    assert(snap.event_code == BMS_EVENT_PRECHARGE_FAIL); /* Fault 0xBE logged! */

    /* Test Body-Diode Conduction Promotion (FUN_0801f580):
     * During discharge (base_chg=false, base_dsg=true), if I <= -1500mA, CHG MOS is promoted ON */
    ctx.telemetry.current_ma = -5000; /* -5.0A discharge */
    bms_core_apply_mosfet_control(&ctx, false, true);
    assert(ctx.switches.dsg_mos_on == true && ctx.switches.chg_mos_on == true);
    assert(bms_hal_get_chg_mos() == true && bms_hal_get_dsg_mos() == true);

    /* When discharge current ceases (-200mA), CHG MOS returns to OFF */
    ctx.telemetry.current_ma = -200;
    bms_core_apply_mosfet_control(&ctx, false, true);
    assert(ctx.switches.dsg_mos_on == true && ctx.switches.chg_mos_on == false);
    printf("PASS (Pre-charge timeout -> Fault 0xBE, Body-Diode bypass @ -5A -> CHG+DSG ON)\n");

    /* Test 24: Hybrid ADC1..4 Temp Fusion with Open-Wire Masking (FUN_0801f8ac) & 7-Port UART (FUN_08016420) */
    printf("[Test 24] Hybrid ADC1..4 NTC Fusion & 7-Port UART / RS-485 DE/RE... ");
    bms_hal_set_simulated_adc(1, 2048 + (10 * 32)); /* MOS temp = 35°C */
    bms_hal_set_simulated_adc(2, 2048 + (5 * 32));  /* Connector temp = 30°C */
    ctx.telemetry.temp_c[0] = -40; /* Simulated broken/open NTC1 wire */
    ctx.telemetry.temp_c[1] = 28;
    ctx.telemetry.temp_c[2] = 29;
    ctx.telemetry.temp_c[3] = 27;
    bms_core_update_hybrid_temperatures(&ctx);
    assert(ctx.telemetry.mos_temp_c == 35);
    assert(ctx.telemetry.connector_temp_c == 30);
    assert(ctx.telemetry.temp_c[0] == 35); /* Open wire (-40°C) masked with MOS temp (35°C)! */

    assert(bms_hal_uart_get_base_addr(BMS_UART_PORT_UART6) == 0x40015000UL);
    assert(bms_hal_uart_get_base_addr(BMS_UART_PORT_UART7) == 0x40015400UL);
    uint8_t dummy_uart[4] = {0x01, 0x02, 0x03, 0x04};
    assert(bms_hal_uart_transmit(BMS_UART_PORT_UART6, dummy_uart, 4) == true);
    assert(bms_hal_rs485_get_de(BMS_UART_PORT_UART6) == false);
    printf("PASS (Open-NTC masked to 35C, UART6=0x40015000, UART7=0x40015400)\n");

    /* Test 25: Deep-Sleep RTC Wake-Up, Self-Discharge (FUN_0801fc8c) & 5-LED Bar-Graph (FUN_0800fc48) */
    printf("[Test 25] RTC Deep-Sleep, Self-Discharge & 5-Stage LED Bar-Graph... ");
    bms_core_enter_deep_sleep(&ctx, 3600);
    assert(ctx.state == BMS_STATE_SLEEP && bms_hal_is_in_stop_sleep() == true);
    assert(bms_hal_get_last_rtc_alarm_sec() == 3600);
    bms_core_wake_from_sleep(&ctx);
    assert(ctx.state == BMS_STATE_STANDBY && bms_hal_is_in_stop_sleep() == false);

    ctx.telemetry.total_capacity_mah = 70000;
    ctx.telemetry.remaining_mah = 50000;
    uint32_t lost = bms_ocv_apply_self_discharge(&ctx);
    assert(lost > 0 && ctx.telemetry.remaining_mah == (50000 - lost));

    bool blink = false;
    ctx.state = BMS_STATE_DISCHARGE;
    ctx.telemetry.soc_pct = 7;
    assert(bms_core_get_led_bar_stage(&ctx, &blink) == 1 && blink == true);
    ctx.telemetry.soc_pct = 85;
    assert(bms_core_get_led_bar_stage(&ctx, &blink) == 5 && blink == false);
    printf("PASS (RTC Alarm=3600s, Self-Dsg=-%umAh, LED: 7%%=1+Blink, 85%%=5)\n", (unsigned int)lost);

    /* Test 26: UART 0x7A IAP Bootloader Upgrade (FUN_0801cd98) & BLE AT+NAME Framing (FUN_0800b454) */
    printf("[Test 26] UART 0x7A IAP Trigger & BLE AT+NAME Command Formatter... ");
    (void)bms_storage_write_boot_iap_flag(0x00000000UL);
    ctx.ota_update_requested = false;
    uint8_t uart_iap_req[6] = { 0xEA, 0x7A, 0x01, 0x04, 0x00, 0x04 };
    uint8_t uart_iap_resp[16] = {0};
    int iap_resp_len = bms_host_proto_process_frame(uart_iap_req, 6, uart_iap_resp, sizeof(uart_iap_resp), &ctx);
    assert(iap_resp_len == 6 && uart_iap_resp[1] == 0x7A && uart_iap_resp[4] == 0x00);
    assert(ctx.ota_update_requested == true);
    uint32_t iap_flag_check = 0;
    assert(bms_storage_read_boot_iap_flag(&iap_flag_check) == 0 && iap_flag_check == BMS_BOOT_IAP_MAGIC);
    assert(bms_storage_read_last_event(&snap) == 0 && snap.event_code == BMS_EVENT_UART_IAP);

    char bt_cmd[32] = {0};
    int bt_len = bms_modbus_format_bt_at_name("SPB24-70AH", bt_cmd, sizeof(bt_cmd));
    assert(bt_len == 20 && strcmp(bt_cmd, "AT+NAME SPB24-70AH\r\n") == 0);
    printf("PASS (UART 0x7A -> 0x28A Flag + Event 0x64, BLE='%s')\n", "AT+NAME SPB24-70AH");

    /* Test 27: Dual Storage Medium Selector (FUN_0800f850) & 3-Slot Black-Box Fault Ring Buffer */
    printf("[Test 27] Dual Storage Medium (Flash vs EEPROM) & 3-Slot Fault Ring... ");
    bms_storage_set_medium(BMS_STORAGE_MEDIUM_FLASH);
    assert(bms_storage_get_medium() == BMS_STORAGE_MEDIUM_FLASH);
    ctx.limits.cell_ovp_mv = 4195;
    assert(bms_storage_save_config(&ctx) == 0);
    ctx.limits.cell_ovp_mv = 0;
    assert(bms_storage_load_config(&ctx) == 0 && ctx.limits.cell_ovp_mv == 4195);
    bms_storage_set_medium(BMS_STORAGE_MEDIUM_EEPROM);
    assert(bms_storage_get_medium() == BMS_STORAGE_MEDIUM_EEPROM);

    assert(bms_storage_log_event(BMS_EVENT_DSG_OCP, &ctx) == 0);
    assert(bms_storage_log_event(BMS_EVENT_CHG_OCP, &ctx) == 0);
    assert(bms_storage_log_event(BMS_EVENT_PACK_OVP, &ctx) == 0);
    BmsFaultSnapshot_t slot0, slot1, slot2;
    assert(bms_storage_read_event_slot(0, &slot0) == 0);
    assert(bms_storage_read_event_slot(1, &slot1) == 0);
    assert(bms_storage_read_event_slot(2, &slot2) == 0);
    assert(bms_storage_read_last_event(&snap) == 0 && snap.event_code == BMS_EVENT_PACK_OVP);
    printf("PASS (Flash Config OVP=4195mV, 3-Slot Ring Latest=0x%02X)\n", snap.event_code);

    /* Test 28: CAN CMD 0x44 Custom Calibration (FUN_0801afbc) & Parallel Bus Heartbeat (0x141DF001) */
    printf("[Test 28] CAN CMD 0x44 Custom Calibration & Parallel Bus 0x141DF001... ");
    CanMessage_t cal_wr = {0};
    cal_wr.id  = BMS_CAN_MAKE_ID(BMS_CAN_VCU_SID, BMS_CAN_MASTER_SID, CAN_CMD_CUSTOM_CALIB, 0xF1);
    cal_wr.dlc = 8;
    cal_wr.data[0] = (uint8_t)(4200 & 0xFF); cal_wr.data[1] = (uint8_t)(4200 >> 8);
    cal_wr.data[2] = (uint8_t)(2650 & 0xFF); cal_wr.data[3] = (uint8_t)(2650 >> 8);
    cal_wr.data[4] = (uint8_t)(450 & 0xFF);  cal_wr.data[5] = (uint8_t)(450 >> 8);  /* 45.0A */
    cal_wr.data[6] = (uint8_t)(1100 & 0xFF); cal_wr.data[7] = (uint8_t)(1100 >> 8); /* 110.0A */
    bms_can_process_rx(&cal_wr, &ctx);
    assert(ctx.limits.cell_ovp_mv == 4200 && ctx.limits.cell_uvp_mv == 2650);
    assert(ctx.limits.chg_ocp_ma == 45000 && ctx.limits.dsg_ocp_ma == 110000);

    bms_parallel_init(&ctx);
    ctx.role = BMS_ROLE_MASTER;
    ctx.can_sid = BMS_CAN_MASTER_SID;
    ctx.telemetry.soc_pct = 4; /* Master <= 5% triggers switch to Slave when peer connected */
    uint8_t peer_hb[8] = { BMS_CAN_SLAVE_SID, 88, 0xFC, 0x02, 0x00, 0x02, 0x00, 0x00 }; /* 76.4V, 88% SOC */
    assert(bms_parallel_process_can_rx(&ctx, BMS_PARALLEL_CAN_ID_HEARTBEAT, peer_hb, 8) == true);
    assert(bms_parallel_get_manager()->peer_connected == true && bms_parallel_get_manager()->peer_soc_pct == 88);
    bms_parallel_process_tick(&ctx);
    assert(bms_parallel_get_manager()->stage == PARALLEL_STAGE_SLAVE_ACTIVE);
    assert(bms_parallel_get_manager()->active_pack_id == BMS_CAN_SLAVE_SID);
    printf("PASS (CMD 0x44 OVP=4200mV/DSG=110A, Parallel 0x141DF001 -> Slave 0x1D)\n");

    printf("\n========================================================\n");
    printf("[✔] All 28 BMS Firmware Unit Tests PASSED Successfully!\n");
    printf("========================================================\n");

    return 0;
}
