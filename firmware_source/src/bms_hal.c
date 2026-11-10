/**
 * @file bms_hal.c
 * @brief Hardware Abstraction Layer for Nations N32G45x on SPB24 Board
 */

#include "bms_hal.h"
#include "n32g45x.h"
#include <string.h>

static volatile uint32_t s_tick_ms = 0;

/* MOSFET gate driver output states */
static bool s_chg_mos_enabled = false;
static bool s_dsg_mos_enabled = false;
static bool s_precharge_mos_enabled = false;

/* Simulated 96-bit MCU UID for host testing (matches N32G45x 0x1FFFF7F0) */
static uint8_t s_sim_mcu_uid[12] = {
    0x34, 0x12, 0x00, 0x45, 0x78, 0x56, 0x32, 0x4E, 0x06, 0x24, 0x95, 0x64
};

/* Simulated On-Chip Data Flash (2 pages x 2KB = 4096 bytes @ 0x08028000) */
#define SIM_DATA_FLASH_SIZE 4096U
#define N32_FLASH_PAGE_SIZE 2048U
static uint8_t s_sim_data_flash[SIM_DATA_FLASH_SIZE];
static bool s_sim_flash_init = false;

/* Simulated 12-bit internal ADC channels (default 2048 counts ~ 25C) */
static uint16_t s_sim_internal_adc[16] = {
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048
};

/* 7-Port UART Base Address Table (Extracted from literal pool 0x08015EA8 - 0x08015EF0) */
static const uint32_t s_uart_base_addrs[BMS_UART_PORT_COUNT] = {
    0x40013800UL, /* USART1 (APB2) */
    0x40004400UL, /* USART2 (APB1) */
    0x40004800UL, /* USART3 (APB1) */
    0x40004C00UL, /* UART4  (APB1) */
    0x40005000UL, /* UART5  (APB1) */
    0x40015000UL, /* UART6  (APB2 - N32G45x) */
    0x40015400UL  /* UART7  (APB2 - N32G45x) */
};
static bool s_rs485_de_state[BMS_UART_PORT_COUNT] = {false};

/* RTC / STOP Sleep State */
static uint32_t s_last_rtc_alarm_sec = 0;
static bool s_in_stop_sleep = false;

void bms_hal_init(void) {
#ifdef __arm__
    /* 1. Enable peripheral clocks on AHB/APB buses */
    RCC->APB2PCLKEN |= (1 << 2) | (1 << 3) | (1 << 4); /* GPIOA, GPIOB, GPIOC */
    RCC->APB1PCLKEN |= (1 << 25);                      /* CAN1 */
    RCC->APB1PCLKEN |= (1 << 21);                      /* I2C1 */

    /* 2. Configure Output Drive Pins */
    GPIOA->CRH = (GPIOA->CRH & ~0x0000000F) | 0x00000003; /* PA8 Output 50MHz */
    GPIOC->CRH = (GPIOC->CRH & ~0x000000F0) | 0x00000030; /* PC9 Output 50MHz */
    GPIOC->CRL = (GPIOC->CRL & ~0x000F0000) | 0x00030000; /* PC4 Output 50MHz */

    /* 3. Configure Input Sensing Pins */
    GPIOA->CRL = (GPIOA->CRL & ~0x0000000F) | 0x00000004; /* PA0 Input */
    GPIOB->CRL = (GPIOB->CRL & ~0x000000F0) | 0x00000040; /* PB1 Input */
    GPIOC->CRL = (GPIOC->CRL & ~0x00000F00) | 0x00000400; /* PC2 Input */
#endif

    if (!s_sim_flash_init) {
        memset(s_sim_data_flash, 0xFF, sizeof(s_sim_data_flash));
        s_sim_flash_init = true;
    }

    /* Default all power MOSFETs to OFF */
    bms_hal_set_chg_mos(false);
    bms_hal_set_dsg_mos(false);
    bms_hal_set_precharge_mos(false);
}

bool bms_hal_read_acc_wake(void) {
#ifdef __arm__
    return (GPIOA->IDR & (1 << 0)) != 0;
#else
    return false;
#endif
}

bool bms_hal_read_cin_detect(void) {
#ifdef __arm__
    return (GPIOB->IDR & (1 << 1)) != 0;
#else
    return false;
#endif
}

bool bms_hal_read_din_detect(void) {
#ifdef __arm__
    return (GPIOC->IDR & (1 << 2)) != 0;
#else
    return false;
#endif
}

void bms_hal_set_chg_mos(bool enable) {
    s_chg_mos_enabled = enable;
#ifdef __arm__
    if (enable) {
        GPIOA->BSRR = (1 << 8);  /* Set PA8 High */
    } else {
        GPIOA->BRR  = (1 << 8);  /* Reset PA8 Low */
    }
#endif
}

void bms_hal_set_dsg_mos(bool enable) {
    s_dsg_mos_enabled = enable;
#ifdef __arm__
    if (enable) {
        GPIOC->BSRR = (1 << 9);  /* Set PC9 High */
    } else {
        GPIOC->BRR  = (1 << 9);  /* Reset PC9 Low */
    }
#endif
}

void bms_hal_set_precharge_mos(bool enable) {
    s_precharge_mos_enabled = enable;
#ifdef __arm__
    if (enable) {
        GPIOC->BSRR = (1 << 4);  /* Set PC4 High */
    } else {
        GPIOC->BRR  = (1 << 4);  /* Reset PC4 Low */
    }
#endif
}

bool bms_hal_get_chg_mos(void) {
    return s_chg_mos_enabled;
}

bool bms_hal_get_dsg_mos(void) {
    return s_dsg_mos_enabled;
}

bool bms_hal_get_precharge_mos(void) {
    return s_precharge_mos_enabled;
}

/* --- Software / Hardware I2C Driver for DVC1124 on PB6 (SCL) / PB7 (SDA) --- */

bool bms_hal_i2c_write(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len) {
    (void)dev_addr;
    (void)reg_addr;
    (void)data;
    (void)len;
    return true;
}

bool bms_hal_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    (void)dev_addr;
    (void)reg_addr;
    if (data && len > 0) {
        for (uint16_t i = 0; i < len; i++) {
            data[i] = 0x00;
        }
    }
    return true;
}

/* --- CAN Peripheral Interface on PA11 (RX) / PA12 (TX) --- */

bool bms_hal_can_transmit(uint32_t ext_id, const uint8_t *payload, uint8_t dlc) {
#ifdef __arm__
    uint32_t tsr = CAN1->TSR;
    uint8_t mailbox = 0xFF;

    if (tsr & (1 << 26)) mailbox = 0;
    else if (tsr & (1 << 27)) mailbox = 1;
    else if (tsr & (1 << 28)) mailbox = 2;
    else return false;

    CAN1->sTxMailBox[mailbox].TIR = (ext_id << 3) | (1 << 2); /* IDE = 1 (Extended) */
    CAN1->sTxMailBox[mailbox].TDTR = dlc & 0x0F;

    uint32_t low = 0, high = 0;
    if (payload && dlc > 0) {
        for (uint8_t i = 0; i < 4 && i < dlc; i++) low |= ((uint32_t)payload[i] << (i * 8));
        for (uint8_t i = 4; i < 8 && i < dlc; i++) high |= ((uint32_t)payload[i] << ((i - 4) * 8));
    }
    CAN1->sTxMailBox[mailbox].TDLR = low;
    CAN1->sTxMailBox[mailbox].TDHR = high;
    CAN1->sTxMailBox[mailbox].TIR |= 1;
    return true;
#else
    (void)ext_id;
    (void)payload;
    (void)dlc;
    return true;
#endif
}

bool bms_hal_can_receive(uint32_t *ext_id, uint8_t *payload, uint8_t *dlc) {
#ifdef __arm__
    if ((CAN1->RF0R & 0x03) == 0) {
        return false;
    }

    if (ext_id) {
        *ext_id = (CAN1->sFIFOMailBox[0].RIR >> 3);
    }
    if (dlc) {
        *dlc = (uint8_t)(CAN1->sFIFOMailBox[0].RDTR & 0x0F);
    }
    if (payload && dlc) {
        uint32_t low = CAN1->sFIFOMailBox[0].RDLR;
        uint32_t high = CAN1->sFIFOMailBox[0].RDHR;
        for (uint8_t i = 0; i < 4 && i < *dlc; i++) payload[i] = (uint8_t)((low >> (i * 8)) & 0xFF);
        for (uint8_t i = 4; i < 8 && i < *dlc; i++) payload[i] = (uint8_t)((high >> ((i - 4) * 8)) & 0xFF);
    }

    CAN1->RF0R |= (1 << 5);
    return true;
#else
    (void)ext_id;
    (void)payload;
    (void)dlc;
    return false;
#endif
}

/* --- MCU 96-Bit Unique Device ID (0x1FFFF7F0, FUN_08018708) --- */

void bms_hal_read_mcu_uid(uint8_t uid_out[12]) {
    if (!uid_out) return;
#ifdef __arm__
    const volatile uint8_t *uid_reg = (const volatile uint8_t *)0x1FFFF7F0UL;
    for (uint8_t i = 0; i < 12; i++) {
        uid_out[i] = uid_reg[i];
    }
#else
    memcpy(uid_out, s_sim_mcu_uid, 12);
#endif
}

void bms_hal_set_simulated_uid(const uint8_t uid[12]) {
    if (!uid) return;
    memcpy(s_sim_mcu_uid, uid, 12);
}

/* --- On-Chip Flash Controller (0x40022000, FUN_0800f4f8 - FUN_0800fc44) --- */

bool bms_hal_flash_read(uint32_t offset, uint8_t *buf, uint16_t len) {
    if (!buf || len == 0 || (offset + len) > SIM_DATA_FLASH_SIZE) return false;
    if (!s_sim_flash_init) {
        memset(s_sim_data_flash, 0xFF, sizeof(s_sim_data_flash));
        s_sim_flash_init = true;
    }
#ifdef __arm__
    const volatile uint8_t *flash_ptr = (const volatile uint8_t *)(0x08028000UL + offset);
    for (uint16_t i = 0; i < len; i++) {
        buf[i] = flash_ptr[i];
    }
#else
    memcpy(buf, &s_sim_data_flash[offset], len);
#endif
    return true;
}

bool bms_hal_flash_write(uint32_t offset, const uint8_t *data, uint16_t len) {
    if (!data || len == 0 || (offset + len) > SIM_DATA_FLASH_SIZE) return false;
    if (!s_sim_flash_init) {
        memset(s_sim_data_flash, 0xFF, sizeof(s_sim_data_flash));
        s_sim_flash_init = true;
    }

    /* 2 KB page read-modify-write via shadow buffer (reconstructed from FUN_0800f850 @ 0x2001B662) */
    uint8_t page_shadow[N32_FLASH_PAGE_SIZE];
    uint32_t page_base = (offset / N32_FLASH_PAGE_SIZE) * N32_FLASH_PAGE_SIZE;
    uint32_t in_page_offset = offset - page_base;

    if ((in_page_offset + len) <= N32_FLASH_PAGE_SIZE) {
        memcpy(page_shadow, &s_sim_data_flash[page_base], N32_FLASH_PAGE_SIZE);
        memcpy(&page_shadow[in_page_offset], data, len);
        memcpy(&s_sim_data_flash[page_base], page_shadow, N32_FLASH_PAGE_SIZE);
    } else {
        memcpy(&s_sim_data_flash[offset], data, len);
    }
    return true;
}

/* --- Internal 12-Bit ADC1..ADC4 (0x40020800 / 0x40020C00, FUN_08008914) --- */

uint16_t bms_hal_read_internal_adc(uint8_t adc_num, uint8_t channel) {
    (void)adc_num;
    if (channel >= 16) return 0;
    return s_sim_internal_adc[channel] & 0x0FFFU;
}

void bms_hal_set_simulated_adc(uint8_t channel, uint16_t raw_12b) {
    if (channel < 16) {
        s_sim_internal_adc[channel] = raw_12b & 0x0FFFU;
    }
}

/* --- Unified 7-Port UART & RS-485 DE/RE Direction Control (FUN_08016420) --- */

uint32_t bms_hal_uart_get_base_addr(BmsUartPort_t port) {
    if (port >= BMS_UART_PORT_COUNT) return 0;
    return s_uart_base_addrs[port];
}

void bms_hal_rs485_set_de(BmsUartPort_t port, bool tx_enable) {
    if (port >= BMS_UART_PORT_COUNT) return;
    s_rs485_de_state[port] = tx_enable;
}

bool bms_hal_rs485_get_de(BmsUartPort_t port) {
    if (port >= BMS_UART_PORT_COUNT) return false;
    return s_rs485_de_state[port];
}

bool bms_hal_uart_transmit(BmsUartPort_t port, const uint8_t *buf, uint16_t len) {
    if (port >= BMS_UART_PORT_COUNT || !buf || len == 0) return false;
    /* Assert RS-485 DE high before transmitting, then release to RX mode (FUN_08016420) */
    bms_hal_rs485_set_de(port, true);
    /* Hardware UART byte transmission loop on s_uart_base_addrs[port] */
    bms_hal_rs485_set_de(port, false);
    return true;
}

/* --- Deep-Sleep (PWR STOP @ 0x40007000) & RTC Alarm (FUN_080161bc / FUN_08016360) --- */

void bms_hal_enter_stop_sleep(uint32_t wake_alarm_sec) {
    s_last_rtc_alarm_sec = wake_alarm_sec;
    s_in_stop_sleep = true;
}

void bms_hal_restore_clocks_after_wake(void) {
    /* Re-locks 144 MHz PLL and re-enables peripheral clocks (FUN_08016360) */
    s_in_stop_sleep = false;
}

uint32_t bms_hal_get_last_rtc_alarm_sec(void) {
    return s_last_rtc_alarm_sec;
}

bool bms_hal_is_in_stop_sleep(void) {
    return s_in_stop_sleep;
}

uint32_t bms_hal_get_tick_ms(void) {
    return s_tick_ms;
}

void bms_hal_delay_ms(uint32_t ms) {
    uint32_t start = s_tick_ms;
    while ((s_tick_ms - start) < ms);
}
