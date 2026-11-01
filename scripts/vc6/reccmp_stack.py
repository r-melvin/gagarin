#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""reccmp-stackcmp over a list of functions, paired by address, with a structured summary.

Run with reccmp's own interpreter (reccmp_image.py finds it from the reccmp-reccmp script).

reccmp-stackcmp compares the stack-frame offsets two builds of a function use and ties each rebuilt offset to the
local variable name in the PDB. It needs the function's rebuilt body in the image, so the image must have been
linked with those partials promoted (link_m1.py --promote): the retail-identical image holds retail's own bytes in
every partial's slot, where the comparison would be vacuous. Functions are paired with the rebuilt function at the
same address, as reccmp_audit.py --pair-by-address does.

Per function the summary gives reccmp's match ratio, the number of differing instruction lines, the stack offsets
used on each side and how they correspond: identical (every pair equal), reordered (1:1 but different offsets),
non_bijective (one offset corresponds to several), structural (the instruction streams differ in length in a
block, so the comparison is incomplete).

Usage:  reccmp_stack.py ORIG EXE PDB MANIFEST ADDRS.txt OUT.json OUT.txt
"""

import contextlib
import io
import json
from pathlib import Path
import re
import struct
import sys

from reccmp.compare import Compare
from reccmp.compare.diff import raw_diff_to_udiff
from reccmp.project.detect import GhidraConfig, RecCmpTarget, ReportConfig
from reccmp.tools import stackcmp
from reccmp.types import EntityType, ImageId

ANSI = re.compile(r"\x1b\[[0-9;]*m")


def analyse(match, compare):
    udiff = raw_diff_to_udiff(match.result.diff, grouped=False)
    node = next((n for n in compare.cvdump_analysis.nodes if n.addr == match.recomp_addr), None)
    warnings = stackcmp.Warnings()
    pairs = set()
    for block in udiff:
        for diff in block[1]:
            pairs |= stackcmp.analyze_diff(diff, warnings)
    symbols = {}
    if node is not None and node.symbol_entry is not None:
        for sym in node.symbol_entry.symbols:
            if sym.symbol_type == "S_BPREL32":
                symbols[struct.unpack(">l", bytes.fromhex(sym.location[1:-1]))[0]] = sym.name
    orig_to = {}
    recomp_to = {}
    for p in pairs:
        orig_to.setdefault((p.orig.register, p.orig.offset), set()).add((p.recomp.register, p.recomp.offset))
        recomp_to.setdefault((p.recomp.register, p.recomp.offset), set()).add((p.orig.register, p.orig.offset))
    non_bijective = any(len(v) > 1 for v in orig_to.values()) or any(len(v) > 1 for v in recomp_to.values())
    moved = sorted((p.orig.register, p.orig.offset, p.recomp.offset) for p in pairs if p.orig != p.recomp)
    if warnings.structural_mismatches_present:
        verdict = "structural"
    elif non_bijective:
        verdict = "non_bijective"
    elif moved:
        verdict = "reordered"
    else:
        verdict = "identical"
    text = io.StringIO()
    with contextlib.redirect_stdout(text):
        if node is not None and node.symbol_entry is not None:
            stackcmp.compare_function_stacks(udiff, node.symbol_entry)
    diff = match.result.diff
    differing = sum(1 for a, b in zip(diff.orig_inst, diff.recomp_inst) if a[1] != b[1])
    return {"ratio": round(match.ratio, 4), "stack_offsets_orig": len({k for k in orig_to}), "pairs": len(pairs),
            "moved": [list(m) for m in moved], "verdict": verdict, "locals_in_pdb": len(symbols),
            "differing_lines": differing, "instructions": [len(diff.orig_inst), len(diff.recomp_inst)]}, ANSI.sub("", text.getvalue())


def main(argv=None):
    orig, exe, pdb, manifest, addrs, out_json, out_txt = (Path(a) for a in (argv or sys.argv[1:]))
    target = RecCmpTarget(target_id="GAMEMD", filename=orig.name, sha256="", original_path=orig, recompiled_path=exe,
                          recompiled_pdb=pdb, encoding="utf-8", source_paths=(out_json.parent,),
                          ghidra_config=GhidraConfig(), report_config=ReportConfig())
    compare = Compare.from_target(target)
    db = compare._db
    rows = {int(r["addr"], 16): r for r in json.loads(manifest.read_text())}
    wanted = [int(a, 16) for a in addrs.read_text().split()]
    with db.batch() as batch:
        for addr in wanted:
            if db.get(ImageId.RECOMP, addr) is not None:
                row = rows.get(addr)
                batch.set(ImageId.ORIG, addr, type=EntityType.FUNCTION, name=row["name"] if row else f"FUN_{addr:08X}",
                          size=int(row["len"], 16) if row else None)
                batch.match(addr, addr)
    results, report = {}, []
    for addr in wanted:
        match = compare.compare_address(addr)
        if match is None:
            results[f"0x{addr:X}"] = {"verdict": "no_match"}
            continue
        summary, text = analyse(match, compare)
        summary["name"] = rows.get(addr, {}).get("name")
        results[f"0x{addr:X}"] = summary
        report.append(f"===== 0x{addr:X} {summary['name']}: {summary['verdict']}, ratio {summary['ratio']}\n{text}")
    out_json.write_text(json.dumps(results, indent=1) + "\n")
    out_txt.write_text("\n".join(report))
    tally = {}
    for r in results.values():
        tally[r["verdict"]] = tally.get(r["verdict"], 0) + 1
    print(json.dumps(tally))
    return 0


if __name__ == "__main__":
    sys.exit(main())
