import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;

public class ExportBmsDecompiled extends GhidraScript {

    @Override
    public void run() throws Exception {
        println("=== BMS Firmware Decompiler Exporter ===");

        File outDir = new File(getProjectRootFolder().getProjectLocator().getProjectDir().getParentFile(), "decompiled");
        if (!outDir.exists()) {
            outDir.mkdirs();
        }

        File outFile = new File(outDir, "bms_firmware_decompiled.c");
        PrintWriter writer = new PrintWriter(new FileWriter(outFile));

        writer.println("// ===========================================================================");
        writer.println("// BMS Firmware Decompiled Output (Ghidra Headless Decompiler)");
        writer.println("// Target: Nations N32G452 (ARM Cortex-M4F @ 144MHz)");
        writer.println("// Firmware: 21S 70Ah NCM Battery Management System");
        writer.println("// ===========================================================================\n");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
        int count = 0;

        while (functions.hasNext() && !monitor.isCancelled()) {
            Function func = functions.next();
            String name = func.getName();
            Address entry = func.getEntryPoint();

            try {
                DecompileResults results = decomp.decompileFunction(func, 60, monitor);
                if (results != null && results.decompileCompleted()) {
                    writer.println("// ---------------------------------------------------------------------------");
                    writer.println(String.format("// Function: %s at 0x%s", name, entry.toString()));
                    writer.println("// ---------------------------------------------------------------------------");
                    writer.println(results.getDecompiledFunction().getC());
                    writer.println();
                    count++;
                } else {
                    writer.println(String.format("// [!] Failed to decompile %s at 0x%s", name, entry.toString()));
                }
            } catch (Exception e) {
                writer.println(String.format("// [ERROR] Exception decompiling %s: %s", name, e.getMessage()));
            }
        }

        writer.close();
        decomp.dispose();

        println(String.format("[✔] Successfully exported %d decompiled functions to: %s", count, outFile.getAbsolutePath()));
    }
}
