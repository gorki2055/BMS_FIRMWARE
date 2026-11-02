/*
 * Linker script for Nations Technologies N32G452 (ARM Cortex-M4F)
 * Application Flash mapped at 0x08008000 (after 32KB bootloader)
 */

MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08008000, LENGTH = 480K   /* 0x08008000 to 0x08080000 */
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K   /* Main SRAM */
  RET_RAM (xrw)   : ORIGIN = 0x20020000, LENGTH = 16K    /* Retention SRAM */
}

ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);    /* End of Main RAM = 0x20020000 */

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
    _etext = .;
  } >FLASH

  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM AT> FLASH

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  /* Reserved region for retention data matching Keil decompress table */
  .retention_data :
  {
    . = ALIGN(4);
    *(.retention_data*)
    . = ALIGN(4);
  } >RET_RAM
}
