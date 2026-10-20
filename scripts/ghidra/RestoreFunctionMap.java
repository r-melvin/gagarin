// Restore function definitions lost from the project's function map.
//
// Each address comes from a sweep over the user's own binary that is
// independent of Ghidra's own analysis: CALL targets, code pointers resident in
// .rdata/.data (vtable slots, comparators), and 16-byte-aligned addresses after
// NOP/INT3 padding. Ghidra holds these as unanalyzed bytes, so the bytes are
// disassembled first and only then promoted to a function.
//
// Args: <address-list-file> [--dry-run]
// The file holds one hex address per line. Output is one TSV line per address
// so the whole operation is auditable and reversible.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import java.io.*;
import java.util.*;

public class RestoreFunctionMap extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 1) { println("RESULT\tusage: <addr-file> [--dry-run]"); return; }
        boolean dry = args.length > 1 && args[1].equals("--dry-run");

        List<String> lines = new ArrayList<>();
        BufferedReader r = new BufferedReader(new FileReader(args[0]));
        for (String l = r.readLine(); l != null; l = r.readLine()) {
            l = l.trim();
            if (!l.isEmpty() && !l.startsWith("#")) lines.add(l);
        }
        r.close();

        Listing listing = currentProgram.getListing();
        int created = 0, already = 0, disasmFail = 0, createFail = 0;

        for (String s : lines) {
            if (monitor.isCancelled()) break;
            Address a;
            try { a = toAddr(Long.parseLong(s.replace("0x","").replace("0X",""), 16)); }
            catch (Exception e) { println("BAD\t" + s); continue; }

            if (listing.getFunctionAt(a) != null) { already++; println("ALREADY\t" + s); continue; }
            if (dry) { println("WOULD\t" + s); continue; }

            // Disassemble first: these addresses are undefined bytes, and a
            // function cannot be created over data.
            if (listing.getInstructionAt(a) == null) {
                DisassembleCommand dc = new DisassembleCommand(a, null, true);
                dc.applyTo(currentProgram, monitor);
                if (listing.getInstructionAt(a) == null) { disasmFail++; println("NODISASM\t" + s); continue; }
            }

            CreateFunctionCmd cf = new CreateFunctionCmd(a);
            if (cf.applyTo(currentProgram, monitor) && listing.getFunctionAt(a) != null) {
                Function f = listing.getFunctionAt(a);
                created++;
                println("CREATED\t" + s + "\t" + f.getName() + "\t" + f.getBody().getNumAddresses());
            } else {
                createFail++;
                println("NOFUNC\t" + s + "\t" + cf.getStatusMsg());
            }
        }
        println("RESULT\tcreated=" + created + "\talready=" + already +
                "\tnodisasm=" + disasmFail + "\tnofunc=" + createFail +
                "\ttotal=" + lines.size());
    }
}
