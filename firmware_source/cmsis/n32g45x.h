/**
 * @file n32g45x.h
 * @brief Nations Technologies N32G45x Microcontroller Register Map (ARM Cortex-M4F)
 * @note Reconstructed for 21S 70Ah NCM BMS Firmware
 */

#ifndef __N32G45X_H__
#define __N32G45X_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Memory Map Base Addresses */
#define FLASH_BASE            ((uint32_t)0x08000000)
#define SRAM_BASE             ((uint32_t)0x20000000)
#define RETENTION_SRAM_BASE   ((uint32_t)0x20020000)
#define PERIPH_BASE           ((uint32_t)0x40000000)

/* Peripheral Bus Bases */
#define APB1PERIPH_BASE       (PERIPH_BASE + 0x00000000)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000)

/* APB1 Peripherals */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE            (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x6400)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)

/* APB2 Peripherals */
#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)

/* AHB Peripherals */
#define DMA1_BASE             (AHBPERIPH_BASE + 0x0000)
#define DMA2_BASE             (AHBPERIPH_BASE + 0x0400)
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000)
#define CRC_BASE              (AHBPERIPH_BASE + 0x3000)

/* --- GPIO Struct --- */
typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

/* --- RCC Struct --- */
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t CFG;
    volatile uint32_t CIR;
    volatile uint32_t APB2RST;
    volatile uint32_t APB1RST;
    volatile uint32_t AHBPCLKEN;
    volatile uint32_t APB2PCLKEN;
    volatile uint32_t APB1PCLKEN;
    volatile uint32_t BDCTRL;
    volatile uint32_t CSR;
} RCC_TypeDef;

/* --- CAN Mailbox & Filter Structs --- */
typedef struct {
    volatile uint32_t TIR;
    volatile uint32_t TDTR;
    volatile uint32_t TDLR;
    volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;

typedef struct {
    volatile uint32_t RIR;
    volatile uint32_t RDTR;
    volatile uint32_t RDLR;
    volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;

typedef struct {
    volatile uint32_t FR1;
    volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;

typedef struct {
    volatile uint32_t MCR;
    volatile uint32_t MSR;
    volatile uint32_t TSR;
    volatile uint32_t RF0R;
    volatile uint32_t RF1R;
    volatile uint32_t IER;
    volatile uint32_t ESR;
    volatile uint32_t BTR;
    uint32_t RESERVED0[88];
    CAN_TxMailBox_TypeDef sTxMailBox[3];
    CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
    uint32_t RESERVED1[12];
    volatile uint32_t FMR;
    volatile uint32_t FM1R;
    uint32_t RESERVED2;
    volatile uint32_t FS1R;
    uint32_t RESERVED3;
    volatile uint32_t FFA1R;
    uint32_t RESERVED4;
    volatile uint32_t FA1R;
    uint32_t RESERVED5[8];
    CAN_FilterRegister_TypeDef sFilterRegister[14];
} CAN_TypeDef;

/* --- I2C Struct --- */
typedef struct {
    volatile uint32_t CTRL1;
    volatile uint32_t CTRL2;
    volatile uint32_t OADDR1;
    volatile uint32_t OADDR2;
    volatile uint32_t DAT;
    volatile uint32_t STS1;
    volatile uint32_t STS2;
    volatile uint32_t CLKCTRL;
    volatile uint32_t TMRISE;
} I2C_TypeDef;

/* --- USART Struct --- */
typedef struct {
    volatile uint32_t STS;
    volatile uint32_t DAT;
    volatile uint32_t BRR;
    volatile uint32_t CTRL1;
    volatile uint32_t CTRL2;
    volatile uint32_t CTRL3;
    volatile uint32_t GTPR;
} USART_TypeDef;

/* Peripheral Declarations */
#define GPIOA                 ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB                 ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC                 ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD                 ((GPIO_TypeDef *)GPIOD_BASE)
#define RCC                   ((RCC_TypeDef *)RCC_BASE)
#define CAN1                  ((CAN_TypeDef *)CAN1_BASE)
#define I2C1                  ((I2C_TypeDef *)I2C1_BASE)
#define USART1                ((USART_TypeDef *)USART1_BASE)
#define USART2                ((USART_TypeDef *)USART2_BASE)

#ifdef __cplusplus
}
#endif

#endif /* __N32G45X_H__ */
