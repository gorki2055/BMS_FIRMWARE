/**
 * @file startup_n32g45x.c
 * @brief Cortex-M4 Vector Table and Reset Handler for N32G452 BMS Firmware
 */

#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

void Reset_Handler(void);
void Default_Handler(void) {
    while (1);
}

/* Cortex-M4 Core System Handlers */
void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__((weak, alias("Default_Handler")));

/* N32G452 Peripheral Interrupt Handlers */
void RTC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void UART5_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));

/* Vector Table placed in .isr_vector section */
__attribute__((section(".isr_vector"), used))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))(&_estack),           /* Initial Stack Pointer */
    Reset_Handler,                         /* Reset Handler */
    NMI_Handler,                           /* NMI Handler */
    HardFault_Handler,                     /* Hard Fault Handler */
    MemManage_Handler,                     /* MPU Fault Handler */
    BusFault_Handler,                      /* Bus Fault Handler */
    UsageFault_Handler,                    /* Usage Fault Handler */
    0, 0, 0, 0,                            /* Reserved */
    SVC_Handler,                           /* SVCall Handler */
    DebugMon_Handler,                      /* Debug Monitor Handler */
    0,                                     /* Reserved */
    PendSV_Handler,                        /* PendSV Handler */
    SysTick_Handler,                       /* SysTick Handler */

    /* Peripheral Interrupts */
    0, 0, 0,
    RTC_IRQHandler,                        /* RTC */
    0, 0,
    EXTI0_IRQHandler,                      /* EXTI Line 0 */
    EXTI1_IRQHandler,                      /* EXTI Line 1 */
    EXTI2_IRQHandler,                      /* EXTI Line 2 */
    EXTI3_IRQHandler,                      /* EXTI Line 3 */
    EXTI4_IRQHandler,                      /* EXTI Line 4 */
    0, 0, 0, 0, 0,
    CAN1_TX_IRQHandler,                    /* CAN1 TX */
    0, 0,
    CAN1_SCE_IRQHandler,                   /* CAN1 SCE */
    0, 0, 0, 0,
    TIM1_CC_IRQHandler,                    /* TIM1 CC */
    TIM2_IRQHandler,                       /* TIM2 */
    0, 0, 0, 0, 0, 0, 0,
    SPI2_IRQHandler,                       /* SPI2 */
    USART1_IRQHandler,                     /* USART1 */
    USART2_IRQHandler,                     /* USART2 */
    USART3_IRQHandler,                     /* USART3 */
    EXTI15_10_IRQHandler,                  /* EXTI Lines 10-15 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    UART5_IRQHandler,                      /* UART5 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    CAN2_RX1_IRQHandler                    /* CAN2 RX1 */
};

void Reset_Handler(void) {
    /* Copy data segment from Flash to SRAM */
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* Zero fill the bss segment */
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    /* Call application main */
    main();

    /* Trap if main returns */
    while (1);
}
