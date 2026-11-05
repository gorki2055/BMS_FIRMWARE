/**
 * @file bms_hal.c
 * @brief Hardware Abstraction Layer for Nations N32G452 on SPB24 Board
 */

#include "bms_hal.h"
#include "n32g45x.h"

static volatile uint32_t s_tick_ms = 0;

void bms_hal_init(void) {
#ifdef __arm__
    /* 1. Enable peripheral clocks on AHB/APB buses */
    RCC->APB2PCLKEN |= (1 << 2) | (1 << 3) | (1 << 4); /* GPIOA, GPIOB, GPIOC */
    RCC->APB1PCLKEN |= (1 << 25);                      /* CAN1 */
    RCC->APB1PCLKEN |= (1 << 21);                      /* I2C1 */

    /* 2. Configure Output Drive Pins */
    /* PA8 (CHG_EN), PC9 (DSG_EN), PC4 (PRECHARGE_EN) as General Purpose Push-Pull Outputs */
    GPIOA->CRH = (GPIOA->CRH & ~0x0000000F) | 0x00000003; /* PA8 Output 50MHz */
    GPIOC->CRH = (GPIOC->CRH & ~0x000000F0) | 0x00000030; /* PC9 Output 50MHz */
    GPIOC->CRL = (GPIOC->CRL & ~0x000F0000) | 0x00030000; /* PC4 Output 50MHz */

    /* 3. Configure Input Sensing Pins */
    /* PA0 (ACC_WAKE), PB1 (CIN_DETECT), PC2 (DIN_DETECT) as Floating Inputs */
    GPIOA->CRL = (GPIOA->CRL & ~0x0000000F) | 0x00000004; /* PA0 Input */
    GPIOB->CRL = (GPIOB->CRL & ~0x000000F0) | 0x00000040; /* PB1 Input */
    GPIOC->CRL = (GPIOC->CRL & ~0x00000F00) | 0x00000400; /* PC2 Input */
#endif

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
#ifdef __arm__
    if (enable) {
        GPIOA->BSRR = (1 << 8);  /* Set PA8 High */
    } else {
        GPIOA->BRR  = (1 << 8);  /* Reset PA8 Low */
    }
#else
    (void)enable;
#endif
}

void bms_hal_set_dsg_mos(bool enable) {
#ifdef __arm__
    if (enable) {
        GPIOC->BSRR = (1 << 9);  /* Set PC9 High */
    } else {
        GPIOC->BRR  = (1 << 9);  /* Reset PC9 Low */
    }
#else
    (void)enable;
#endif
}

void bms_hal_set_precharge_mos(bool enable) {
#ifdef __arm__
    if (enable) {
        GPIOC->BSRR = (1 << 4);  /* Set PC4 High */
    } else {
        GPIOC->BRR  = (1 << 4);  /* Reset PC4 Low */
    }
#else
    (void)enable;
#endif
}

/* --- Software / Hardware I2C Driver for DVC1124 on PB6 (SCL) / PB7 (SDA) --- */

bool bms_hal_i2c_write(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len) {
    (void)dev_addr;
    (void)reg_addr;
    (void)data;
    (void)len;
    /* Hardware I2C transaction routine */
    return true;
}

bool bms_hal_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    (void)dev_addr;
    (void)reg_addr;
    if (data && len > 0) {
        /* Mock / placeholder for hardware simulation */
        for (uint16_t i = 0; i < len; i++) {
            data[i] = 0x00;
        }
    }
    return true;
}

/* --- CAN Peripheral Interface on PA11 (RX) / PA12 (TX) --- */

bool bms_hal_can_transmit(uint32_t ext_id, const uint8_t *payload, uint8_t dlc) {
#ifdef __arm__
    /* Check for an empty transmit mailbox (0, 1, or 2) */
    uint32_t tsr = CAN1->TSR;
    uint8_t mailbox = 0xFF;

    if (tsr & (1 << 26)) mailbox = 0;
    else if (tsr & (1 << 27)) mailbox = 1;
    else if (tsr & (1 << 28)) mailbox = 2;
    else return false; /* All mailboxes full */

    /* Setup Extended ID and DLC */
    CAN1->sTxMailBox[mailbox].TIR = (ext_id << 3) | (1 << 2); /* IDE = 1 (Extended) */
    CAN1->sTxMailBox[mailbox].TDTR = dlc & 0x0F;

    /* Write data words */
    uint32_t low = 0, high = 0;
    if (payload && dlc > 0) {
        for (uint8_t i = 0; i < 4 && i < dlc; i++) low |= ((uint32_t)payload[i] << (i * 8));
        for (uint8_t i = 4; i < 8 && i < dlc; i++) high |= ((uint32_t)payload[i] << ((i - 4) * 8));
    }
    CAN1->sTxMailBox[mailbox].TDLR = low;
    CAN1->sTxMailBox[mailbox].TDHR = high;

    /* Request transmission */
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
        return false; /* FIFO 0 is empty */
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

    /* Release FIFO 0 */
    CAN1->RF0R |= (1 << 5);
    return true;
#else
    (void)ext_id;
    (void)payload;
    (void)dlc;
    return false;
#endif
}

uint32_t bms_hal_get_tick_ms(void) {
    return s_tick_ms;
}

void bms_hal_delay_ms(uint32_t ms) {
    uint32_t start = s_tick_ms;
    while ((s_tick_ms - start) < ms);
}
