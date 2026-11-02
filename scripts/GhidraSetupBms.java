// Ghidra Native Java Script to configure BMS Firmware
// - Sets up RAM memory blocks (Main SRAM 128KB, Retention SRAM 16KB, Peripherals)
// - Sets the TMode register (Thumb mode) for ARM Cortex-M
// - Labels the Vector Table (Reset, HardFault, SysTick, CAN, USART, EXTI handlers)
// - Labels CRT and application entry points (__main, scatterload, main, SystemInit)
// - Disassembles key functions
//
// @category Embedded.ARM.BMS
// @author Antigravity Pair Programmer

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.lang.Register;
import java.math.BigInteger;

import ghidra.program.model.listing.ProgramContext;

public class GhidraSetupBms extends GhidraScript {

    private void addMemBlock(String name, long startAddr, long size, boolean r, boolean w, boolean x, boolean vol) {
        Memory mem = currentProgram.getMemory();
        Address addr = toAddr(startAddr);
        MemoryBlock existing = mem.getBlock(addr);
        if (existing == null) {
            try {
                MemoryBlock block = mem.createUninitializedBlock(name, addr, size, false);
                block.setRead(r);
                block.setWrite(w);
                block.setExecute(x);
                block.setVolatile(vol);
                println("[+] Created memory block: " + name + " @ 0x" + Long.toHexString(startAddr).toUpperCase());
            } catch (Exception e) {
                printerr("[-] Error creating block " + name + ": " + e.getMessage());
            }
        } else {
            println("[i] Memory block " + name + " already exists @ 0x" + Long.toHexString(startAddr).toUpperCase());
        }
    }

    private void setThumbMode(long startAddr, long endAddr) {
        ProgramContext ctx = currentProgram.getProgramContext();
        Register tReg = ctx.getRegister("T");
        if (tReg != null) {
            Address start = toAddr(startAddr);
            Address end = toAddr(endAddr);
            AddressSet set = new AddressSet(start, end);
            try {
                ctx.setValue(tReg, start, end, BigInteger.ONE);
                println("[+] Set Thumb mode (T=1) from 0x" + Long.toHexString(startAddr) + " to 0x" + Long.toHexString(endAddr));
            } catch (Exception e) {
                printerr("[-] Error setting T-reg: " + e.getMessage());
            }
        }
    }

    private void setLabel(long addrLong, String name) {
        try {
            SymbolTable st = currentProgram.getSymbolTable();
            Address addr = toAddr(addrLong);
            st.createLabel(addr, name, SourceType.USER_DEFINED);
            println("    Labeled 0x" + Long.toHexString(addrLong).toUpperCase() + " -> " + name);
        } catch (Exception e) {
            printerr("[-] Error labeling " + name + ": " + e.getMessage());
        }
    }

    private void createFunc(long addrLong, String name) {
        Address addr = toAddr(addrLong);
        disassemble(addr);
        Function func = getFunctionAt(addr);
        if (func == null) {
            try {
                createFunction(addr, name);
            } catch (Exception e) {
                // ignore
            }
        } else {
            try {
                func.setName(name, SourceType.USER_DEFINED);
            } catch (Exception e) {
                // ignore
            }
        }
        println("    Function 0x" + Long.toHexString(addrLong).toUpperCase() + " -> " + name);
    }

    @Override
    public void run() throws Exception {
        println("==================================================");
        println("Configuring BMS Firmware (N32G452 - 21S 70Ah NCM)");
        println("==================================================");

        // 1. Create Memory Blocks
        addMemBlock("SRAM_MAIN", 0x20000000L, 0x00020000L, true, true, true, false);      // 128 KB Main SRAM
        addMemBlock("SRAM_RETENTION", 0x20020000L, 0x00004000L, true, true, true, false); // 16 KB Retention SRAM
        addMemBlock("PERIPH_APB1", 0x40000000L, 0x00008000L, true, true, false, true);
        addMemBlock("PERIPH_APB2", 0x40010000L, 0x00008000L, true, true, false, true);
        addMemBlock("PERIPH_AHB", 0x40018000L, 0x00020000L, true, true, false, true);
        addMemBlock("PPB_SYSTEM", 0xE0000000L, 0x00100000L, true, true, false, true);     // NVIC, SysTick, SCB

        // 2. Set Thumb Mode
        setThumbMode(0x08008000L, 0x0802373FL);

        // 3. Label Vector Table
        setLabel(0x08008000L, "Vector_Initial_MSP");
        setLabel(0x08008004L, "Vector_Reset_Handler");
        setLabel(0x08008008L, "Vector_NMI_Handler");
        setLabel(0x0800800CL, "Vector_HardFault_Handler");
        setLabel(0x08008010L, "Vector_MemManage_Handler");
        setLabel(0x08008014L, "Vector_BusFault_Handler");
        setLabel(0x08008018L, "Vector_UsageFault_Handler");
        setLabel(0x0800802CL, "Vector_SVC_Handler");
        setLabel(0x08008030L, "Vector_DebugMon_Handler");
        setLabel(0x08008038L, "Vector_PendSV_Handler");
        setLabel(0x0800803CL, "Vector_SysTick_Handler");
        setLabel(0x0800804CL, "Vector_RTC_IRQHandler");
        setLabel(0x08008058L, "Vector_EXTI0_IRQHandler");
        setLabel(0x0800805CL, "Vector_EXTI1_IRQHandler");
        setLabel(0x08008060L, "Vector_EXTI2_IRQHandler");
        setLabel(0x08008064L, "Vector_EXTI3_IRQHandler");
        setLabel(0x08008068L, "Vector_EXTI4_IRQHandler");
        setLabel(0x08008090L, "Vector_CAN1_TX_IRQHandler");
        setLabel(0x0800809CL, "Vector_CAN1_SCE_IRQHandler");
        setLabel(0x080080B0L, "Vector_TIM1_CC_IRQHandler");
        setLabel(0x080080B4L, "Vector_TIM2_IRQHandler");
        setLabel(0x080080D4L, "Vector_SPI2_IRQHandler");
        setLabel(0x080080D8L, "Vector_USART1_IRQHandler");
        setLabel(0x080080DCL, "Vector_USART2_IRQHandler");
        setLabel(0x080080E0L, "Vector_USART3_IRQHandler");
        setLabel(0x080080E4L, "Vector_EXTI15_10_IRQHandler");
        setLabel(0x08008110L, "Vector_UART5_IRQHandler");
        setLabel(0x08008140L, "Vector_CAN2_RX1_IRQHandler");

        // 4. Create and Label Handlers
        createFunc(0x080081B0L, "Reset_Handler");
        createFunc(0x080173ACL, "NMI_Handler");
        createFunc(0x08011470L, "HardFault_Handler");
        createFunc(0x08017220L, "MemManage_Handler");
        createFunc(0x0800A504L, "BusFault_Handler");
        createFunc(0x08020F18L, "UsageFault_Handler");
        createFunc(0x08019540L, "SVC_Handler");
        createFunc(0x0800D9C8L, "DebugMon_Handler");
        createFunc(0x080081C6L, "PendSV_Handler");
        createFunc(0x0801F468L, "SysTick_Handler");
        createFunc(0x0801821CL, "RTC_IRQHandler");
        createFunc(0x0800F35CL, "EXTI0_IRQHandler");
        createFunc(0x0800F392L, "EXTI1_IRQHandler");
        createFunc(0x0800F398L, "EXTI2_IRQHandler");
        createFunc(0x0800F39EL, "EXTI3_IRQHandler");
        createFunc(0x0800F3A4L, "EXTI4_IRQHandler");
        createFunc(0x080207E0L, "CAN1_TX_IRQHandler");
        createFunc(0x0800F3AAL, "CAN1_SCE_IRQHandler");
        createFunc(0x0801F804L, "TIM1_CC_IRQHandler");
        createFunc(0x0801F81CL, "TIM2_IRQHandler");
        createFunc(0x0802057CL, "SPI2_IRQHandler");
        createFunc(0x080205C4L, "USART1_IRQHandler");
        createFunc(0x0802060CL, "USART2_IRQHandler");
        createFunc(0x0800F362L, "USART3_IRQHandler");
        createFunc(0x08017E7CL, "EXTI15_10_IRQHandler");
        createFunc(0x0801FE34L, "UART5_IRQHandler");
        createFunc(0x0800A6E0L, "CAN2_RX1_IRQHandler");

        // 5. Entry points
        createFunc(0x08008198L, "__main");
        createFunc(0x080087FCL, "__scatterload");
        createFunc(0x08008820L, "__decompress_keil");
        createFunc(0x08022F94L, "__scatterload_zeroinit");
        createFunc(0x0801F4A8L, "SystemInit");
        createFunc(0x08022FE0L, "main");

        println("\n[✔] BMS Firmware Setup Complete!");
    }
}
