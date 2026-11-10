/* ==========================================================================
 * Linker Script for Safe C-Hook Extension in Unused Flash (0x08023800)
 *
 * Memory Layout:
 *  - Factory Binary:      0x08008000 - 0x0802373F (112,448 bytes - UNTOUCHED)
 *  - Safe C-Hook Region:  0x08023800 - 0x08027FFF (18,432 bytes free Flash)
 *  - User Data Partition: 0x08028000 - 0x0803FFFF (UNTOUCHED - holds 0x28A IAP flag)
 *  - Isolated Patch SRAM: 0x2001F000 - 0x2001FFFF (4 KB untouched SRAM block,
 *                         completely separate from factory .bss and 0x20023A60 MSP stack)
 * ========================================================================== */

MEMORY
{
    PATCH_FLASH (rx)  : ORIGIN = 0x08023800, LENGTH = 18K
    PATCH_SRAM  (rwx) : ORIGIN = 0x2001F000, LENGTH = 4K
}

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.text.hook_10ms))
        . = 0x00000040;
        KEEP(*(.text.hook_100ms))
        . = 0x00000080;
        KEEP(*(.text.hook_400ms))
        . = ALIGN(4);
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > PATCH_FLASH

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
    } > PATCH_SRAM
}
