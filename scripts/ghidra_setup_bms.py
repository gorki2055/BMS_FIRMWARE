# Ghidra Python script to automatically configure the BMS firmware image:
# - Sets up RAM memory blocks (Main SRAM 128KB, Retention SRAM 16KB, Peripherals)
# - Sets the TMode register (Thumb mode) for ARM Cortex-M
# - Labels the Vector Table (Reset, HardFault, SysTick, CAN, USART, EXTI handlers)
# - Labels CRT entry points (__main, scatterload, main, SystemInit)
# - Disassembles key entry points
#
# Usage in Ghidra:
# 1. Open the BMS binary in Ghidra CodeBrowser
# 2. Open Window -> Script Manager
# 3. Create a new script or add this folder, and run this script.
#
# @category Embedded.ARM.BMS
# @author Antigravity Pair Programmer

from ghidra.program.model.address import AddressSet
from ghidra.program.model.symbol import SourceType

try:
    from java.math import BigInteger
    ONE = BigInteger.ONE
except Exception:
    ONE = 1

def add_mem_block(name, start_addr, size, r, w, x, vol=False):
    mem = currentProgram.getMemory()
    addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(start_addr)
    existing = mem.getBlock(addr)
    if existing is None:
        try:
            block = mem.createUninitializedBlock(name, addr, size, False)
            block.setRead(r)
            block.setWrite(w)
            block.setExecute(x)
            block.setVolatile(vol)
            print("[+] Created memory block: %s @ 0x%08X (size: 0x%X)" % (name, start_addr, size))
        except Exception as e:
            print("[-] Error creating block %s: %s" % (name, e))
    else:
        print("[i] Memory block %s already exists @ 0x%08X" % (name, start_addr))

def set_thumb_mode(start_addr, end_addr):
    # Set ARM T-flag (register T = 1) for Cortex-M Thumb execution
    t_reg = currentProgram.getProgramRegisterContext().getRegister("T")
    if t_reg is not None:
        start = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(start_addr)
        end = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(end_addr)
        addr_set = AddressSet(start, end)
        try:
            currentProgram.getProgramRegisterContext().setValue(t_reg, start, end, ONE)
            print("[+] Set Thumb mode (T=1) from 0x%08X to 0x%08X" % (start_addr, end_addr))
        except Exception as e:
            print("[-] Error setting T-reg: %s" % e)

def set_label(addr_int, name):
    st = currentProgram.getSymbolTable()
    addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addr_int)
    st.createLabel(addr, name, SourceType.USER_DEFINED)
    print("    Labeled 0x%08X -> %s" % (addr_int, name))

def create_func(addr_int, name):
    addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addr_int)
    disassemble(addr)
    func = getFunctionAt(addr)
    if func is None:
        createFunction(addr, name)
    else:
        func.setName(name, SourceType.USER_DEFINED)
    print("    Function: 0x%08X -> %s" % (addr_int, name))

print("==================================================")
print("Configuring BMS Firmware (N32G452 - 21S 70Ah NCM)")
print("==================================================")

# 1. Create Memory Blocks
add_mem_block("SRAM_MAIN", 0x20000000, 0x00020000, True, True, True)       # 128 KB Main SRAM
add_mem_block("SRAM_RETENTION", 0x20020000, 0x00004000, True, True, True)  # 16 KB Retention SRAM
add_mem_block("PERIPH_APB1", 0x40000000, 0x00008000, True, True, False, True)
add_mem_block("PERIPH_APB2", 0x40010000, 0x00008000, True, True, False, True)
add_mem_block("PERIPH_AHB", 0x40018000, 0x00020000, True, True, False, True)
add_mem_block("PPB_SYSTEM", 0xE0000000, 0x00100000, True, True, False, True)  # NVIC, SysTick, SCB

# 2. Set Thumb Mode
set_thumb_mode(0x08008000, 0x0802373F)

# 3. Label Cortex-M Vector Table Entries
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

print("\n--- Labeling Vector Table ---")
for addr, name in VECTORS:
    set_label(addr, name)

# 4. Create and Label Exception and Peripheral Handlers
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
    # CRT and Application entry points
    (0x08008198, "__main"),
    (0x080087FC, "__scatterload"),
    (0x08008820, "__decompress_keil"),
    (0x08022F94, "__scatterload_zeroinit"),
    (0x0801F4A8, "SystemInit"),
    (0x08022FE0, "main"),
]

print("\n--- Disassembling and Creating Functions ---")
for addr, name in HANDLERS:
    try:
        create_func(addr, name)
    except Exception as e:
        print("[-] Error creating function %s @ 0x%08X: %s" % (name, addr, e))

print("\n[✔] BMS Firmware Setup Complete!")
