# IDA Pro Python script (IDAPython) to configure the BMS firmware image:
# - Creates RAM segments (Main SRAM 128KB, Retention SRAM 16KB)
# - Sets Thumb mode (T=1)
# - Labels the Vector Table
# - Creates functions for Reset_Handler, Handlers, and main()
#
# Usage in IDA:
# 1. Load the binary into IDA (ARM Little-endian, Base: 0x08008000)
# 2. File -> Script file... (Alt+F7) -> select this script.

import idc
import idautils
import ida_segment
import ida_bytes
import ida_funcs
import ida_entry

def add_segment(name, start, end, perm):
    s = ida_segment.get_segm_by_name(name)
    if not s:
        ida_segment.add_segm(0, start, end, name, "DATA")
        s = ida_segment.get_segm_by_name(name)
        if s:
            s.perm = perm
            ida_segment.update_segm(s)
            print(f"[+] Added segment {name}: 0x{start:08X} - 0x{end:08X}")
    else:
        print(f"[i] Segment {name} already exists")

print("==================================================")
print("Configuring BMS Firmware in IDA (N32G452 - 21S)")
print("==================================================")

# 1. Add RAM Segments
add_segment("SRAM_MAIN", 0x20000000, 0x20020000, ida_segment.SEGPERM_READ | ida_segment.SEGPERM_WRITE | ida_segment.SEGPERM_EXEC)
add_segment("SRAM_RETENTION", 0x20020000, 0x20024000, ida_segment.SEGPERM_READ | ida_segment.SEGPERM_WRITE | ida_segment.SEGPERM_EXEC)

# 2. Set Thumb Mode (Register T = 1) across the flash segment
for s in idautils.Segments():
    seg = ida_segment.getseg(s)
    if seg.start_ea >= 0x08008000 and seg.end_ea <= 0x08030000:
        idc.split_sreg_range(seg.start_ea, "T", 1)
        print(f"[+] Set Thumb mode (T=1) on segment at 0x{seg.start_ea:08X}")

# 3. Vector Table Labels
VECTORS = [
    (0x08008000, "Vector_Initial_MSP"),
    (0x08008004, "Vector_Reset_Handler"),
    (0x08008008, "Vector_NMI_Handler"),
    (0x0800800C, "Vector_HardFault_Handler"),
    (0x08008010, "Vector_MemManage_Handler"),
    (0x08008014, "Vector_BusFault_Handler"),
    (0x08008018, "Vector_UsageFault_Handler"),
    (0x0800802C, "Vector_SVC_Handler"),
    (0x08008030, "Vector_DebugMon_Handler"),
    (0x08008038, "Vector_PendSV_Handler"),
    (0x0800803C, "Vector_SysTick_Handler"),
    (0x0800804C, "Vector_RTC_IRQHandler"),
    (0x08008058, "Vector_EXTI0_IRQHandler"),
    (0x0800805C, "Vector_EXTI1_IRQHandler"),
    (0x08008060, "Vector_EXTI2_IRQHandler"),
    (0x08008064, "Vector_EXTI3_IRQHandler"),
    (0x08008068, "Vector_EXTI4_IRQHandler"),
    (0x08008090, "Vector_CAN1_TX_IRQHandler"),
    (0x0800809C, "Vector_CAN1_SCE_IRQHandler"),
    (0x080080B0, "Vector_TIM1_CC_IRQHandler"),
    (0x080080B4, "Vector_TIM2_IRQHandler"),
    (0x080080D4, "Vector_SPI2_IRQHandler"),
    (0x080080D8, "Vector_USART1_IRQHandler"),
    (0x080080DC, "Vector_USART2_IRQHandler"),
    (0x080080E0, "Vector_USART3_IRQHandler"),
    (0x080080E4, "Vector_EXTI15_10_IRQHandler"),
    (0x08008110, "Vector_UART5_IRQHandler"),
    (0x08008140, "Vector_CAN2_RX1_IRQHandler"),
]

for addr, name in VECTORS:
    idc.set_name(addr, name, idc.SN_CHECK)
    idc.create_dword(addr)

# 4. Functions
HANDLERS = [
    (0x080081B0, "Reset_Handler"),
    (0x080173AC, "NMI_Handler"),
    (0x08011470, "HardFault_Handler"),
    (0x08017220, "MemManage_Handler"),
    (0x0800A504, "BusFault_Handler"),
    (0x08020F18, "UsageFault_Handler"),
    (0x08019540, "SVC_Handler"),
    (0x0800D9C8, "DebugMon_Handler"),
    (0x080081C6, "PendSV_Handler"),
    (0x0801F468, "SysTick_Handler"),
    (0x0801821C, "RTC_IRQHandler"),
    (0x0800F35C, "EXTI0_IRQHandler"),
    (0x0800F392, "EXTI1_IRQHandler"),
    (0x0800F398, "EXTI2_IRQHandler"),
    (0x0800F39E, "EXTI3_IRQHandler"),
    (0x0800F3A4, "EXTI4_IRQHandler"),
    (0x080207E0, "CAN1_TX_IRQHandler"),
    (0x0800F3AA, "CAN1_SCE_IRQHandler"),
    (0x0801F804, "TIM1_CC_IRQHandler"),
    (0x0801F81C, "TIM2_IRQHandler"),
    (0x0802057C, "SPI2_IRQHandler"),
    (0x080205C4, "USART1_IRQHandler"),
    (0x0802060C, "USART2_IRQHandler"),
    (0x0800F362, "USART3_IRQHandler"),
    (0x08017E7C, "EXTI15_10_IRQHandler"),
    (0x0801FE34, "UART5_IRQHandler"),
    (0x0800A6E0, "CAN2_RX1_IRQHandler"),
    (0x08008198, "__main"),
    (0x080087FC, "__scatterload"),
    (0x08008820, "__decompress_keil"),
    (0x08022F94, "__scatterload_zeroinit"),
    (0x0801F4A8, "SystemInit"),
    (0x08022FE0, "main"),
]

for addr, name in HANDLERS:
    idc.auto_mark_range(addr, addr + 4, idc.AU_CODE)
    ida_funcs.add_func(addr)
    idc.set_name(addr, name, idc.SN_CHECK)

ida_entry.add_entry(0x080081B0, 0x080081B0, "Reset_Handler", 1)
print("[✔] IDA BMS Setup Complete!")
