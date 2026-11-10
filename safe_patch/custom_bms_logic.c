/**
 * @file custom_bms_logic.c
 * @brief Safe C-Hook Extension for Sealed BMS Pack (Linked at 0x08023800)
 *
 * SAFETY GUARANTEES FOR SEALED BATTERY PACKS (NO ST-LINK REQUIRED):
 *  1. 100% of the factory startup, clock tree, CAN1 driver, and CMD 0x1A ("UPDATE")
 *     bootloader trigger (FUN_0801f77c -> FUN_0800f850) remain untouched.
 *  2. Automatic Watchdog Safe-Mode Guard: If custom logic ever hangs or triggers a
 *     Watchdog reset (RCC->CSR IWDGRSTF/WWDGRSTF), the hook automatically bypasses
 *     all custom logic on reboot and runs pure stock factory code so CAN flashing
 *     always remains responsive.
 */

#include "factory_symbols.h"

/* Persistent state stored in isolated SRAM (0x2001F000 - 0x2001FFFF) */
static uint32_t s_custom_100ms_counter = 0;

/**
 * @brief Check if the MCU rebooted due to a Watchdog timeout (Safe-Mode Bypass)
 * @return true if Safe-Mode is active (skip custom logic and run 100% stock code)
 */
static inline bool is_watchdog_safe_mode(void)
{
    uint32_t csr = N32_RCC_CSR_REG;
    if ((csr & (N32_RCC_CSR_IWDGRSTF | N32_RCC_CSR_WWDGRSTF)) != 0UL) {
        return true; /* Hardware watchdog reset detected -> bypass custom code! */
    }
    if (N32_BKP_DR1_REG == SAFE_MODE_MAGIC_LOCKOUT) {
        return true;
    }
    return false;
}

/* ==========================================================================
 * USER CUSTOMIZABLE BMS LOGIC FUNCTIONS
 * Add your custom C algorithms, state rules, or custom CAN frames below!
 * ========================================================================== */

/**
 * @brief Custom 10 ms Fast Logic (Runs right after factory current/protection check)
 */
static void user_custom_10ms_logic(void)
{
    /* Example: Read live cell 1 voltage from factory SRAM (0x20021344) */
    volatile uint16_t *cell_mv = FACTORY_SRAM_CELL_MV;
    (void)cell_mv;
}

/**
 * @brief Custom 100 ms Logic (Runs right after factory 100 ms state machine & CAN tx)
 */
static void user_custom_100ms_logic(void)
{
    s_custom_100ms_counter++;

    /* Example: Send a custom heartbeat or apply custom SOC/current derating every 1s (10 * 100ms) */
    if ((s_custom_100ms_counter % 10UL) == 0UL) {
        /* Custom 1-second periodic logic here */
    }
}

/**
 * @brief Custom 400 ms Slow Logic (Runs right after factory balancing & OCV-SOC check)
 */
static void user_custom_400ms_logic(void)
{
    /* Custom slow balancing / thermal logic here */
}

/* ==========================================================================
 * FIXED-ADDRESS TRAMPOLINE ENTRY POINTS (Hooked from FUN_08021748)
 * Do not change section names or addresses below.
 * ========================================================================== */

/**
 * @brief Trampoline at 0x08023800 (Hooked from 0x08021798: BL 0x0801F580)
 */
__attribute__((section(".text.hook_10ms"), used, noinline))
void hook_entry_10ms(void)
{
    /* 1. Always run stock factory 10ms protection & hardware sensing first */
    FACTORY_TASK_10MS();

    /* 2. Run custom 10ms logic only if no Watchdog reset occurred */
    if (!is_watchdog_safe_mode()) {
        user_custom_10ms_logic();
    }
}

/**
 * @brief Trampoline at 0x08023840 (Hooked from 0x080217AA: BL 0x0801F654)
 */
__attribute__((section(".text.hook_100ms"), used, noinline))
void hook_entry_100ms(void)
{
    /* 1. Always run stock factory 100ms CAN broadcast & state machine first */
    FACTORY_TASK_100MS();

    /* 2. Run custom 100ms logic only if no Watchdog reset occurred */
    if (!is_watchdog_safe_mode()) {
        user_custom_100ms_logic();
    }
}

/**
 * @brief Trampoline at 0x08023880 (Hooked from 0x080217E0: BL 0x0801F6CC)
 */
__attribute__((section(".text.hook_400ms"), used, noinline))
void hook_entry_400ms(void)
{
    /* 1. Always run stock factory 400ms balancing & temperature task first */
    FACTORY_TASK_400MS();

    /* 2. Run custom 400ms logic only if no Watchdog reset occurred */
    if (!is_watchdog_safe_mode()) {
        user_custom_400ms_logic();
    }
}
