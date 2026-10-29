#!/usr/bin/env python3
"""skeleton.py: a compilable, scored first draft per function from binary facts only.

    skeleton.py ADDR... [--tree WT] [--out FILE.cpp] [--class NAME] [--rows READY/rows.tsv]

For each address (ctx.py facts: CFG-closed extent, linear disassembly, named call targets,
global/string refs, RTTI vtable slots, manifest status) the draft carries:
  - the signature: receiver class and slot from the RTTI vtable tables (`vf_<slot>` override on the
    most-base class that has the slot, with the canonical header included when one exists),
    convention from the entry (ECX read before write -> __thiscall, else __fastcall default under
    /Gr), RET n -> stack-argument count, return register use -> int/void;
  - every `[reg+off]` access as a GG_STATIC_ASSERT line (offset and width, from the instruction),
    against the receiver class when the register is `this`, else noted;
  - call targets as `(decl; reloc)` declarations named from the manifest, globals as externs,
    strings as STRING markers;
  - the disassembly as a comment block, and an empty body marked TODO.
It writes rows.tsv lines (addr, sym placeholder, len) so `pkt.py score` works at once. The draft
decides nothing: every name is a placeholder (FUN_/DAT_/vf_N/unknown_XX) and the model's work is
the body. The oracle stays raw_match/diff_retail.
"""
import argparse
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402

MEM = re.compile(r"(BYTE|WORD|DWORD|QWORD) PTR \[(e[a-d]x|e[sd]i|ebp|esp)(?:\+0x([0-9a-f]+)|-0x([0-9a-f]+))?\]")
WIDTH = {"BYTE": 1, "WORD": 2, "DWORD": 4, "QWORD": 8}
CTYPE = {1: "unsigned char", 2: "short", 4: "int", 8: "double"}


def ctx(addr):
    p = subprocess.run([sys.executable, os.path.join(D.TOOLS, "ctx.py"), "0x%X" % addr, "--json", "--no-xref"],
                       capture_output=True, text=True, cwd=D.TOOLS)
    return json.loads(p.stdout)


def base_class(slots, tree):
    """Most-base class among the RTTI classes whose vtable holds this address (smallest derived set)."""
    if not slots:
        return None, None
    rtti = D.read_json(os.path.join(tree.repo, "scripts/data/rtti_classes.json"))["classes"]
    depth = {}
    for m, info in rtti.items():
        n = re.match(r"\.\?A[UV](\w+)@@", m)
        if n:
            depth[n.group(1)] = info.get("num_base_classes", 99)
    best = min(slots, key=lambda s: depth.get(s["cls"], 99))
    return best["cls"], best["slot"]


def analyse(c):
    """Convention, stack args, this-relative accesses, callees, globals from the disassembly."""
    ins = c["disasm"]
    ecx_read_first, ecx_written = False, False
    ret_n = 0
    this_regs = {"ecx"}
    accesses, callees, globals_, strings, vcalls = {}, [], {}, {}, []
    for i in ins:
        t = i["text"]
        mn = t.split(" ")[0]
        if re.match(r"mov (e[a-d]x|e[sd]i),ecx$", t) and not ecx_written:
            this_regs.add(t.split(" ")[1].split(",")[0])
        if "ecx" in t and not ecx_written:
            if re.match(r"mov ecx,|lea ecx,|pop ecx|xor ecx,ecx", t):
                ecx_written = True
            else:
                ecx_read_first = True
        if mn == "ret" and len(t.split()) > 1:
            ret_n = int(t.split()[1], 16)
        for m in MEM.finditer(t):
            w, reg, plus, minus = m.groups()
            if reg in this_regs and plus is not None:
                accesses.setdefault(int(plus, 16), set()).add(WIDTH[w])
        if mn == "call":
            m = re.match(r"call 0x([0-9a-f]+)$", t)
            if m:
                callees.append((int(m.group(1), 16), i.get("note")))
            else:
                mm = re.search(r"call DWORD PTR \[(\w+)\+0x([0-9a-f]+)\]", t)
                if mm:
                    vcalls.append((mm.group(1), int(mm.group(2), 16)))
    for r in c.get("refs") or []:
        try:
            va = D.hx(r["addr"])
        except Exception:
            continue
        if r.get("kind") == "string" or r.get("text"):
            strings[va] = r.get("text") or ""
        else:
            globals_[va] = (r.get("name") or r.get("section") or "")
    return dict(thiscall=ecx_read_first, ret_n=ret_n, accesses=accesses, callees=callees, globals=globals_, strings=strings, vcalls=vcalls)


def emit(addr, c, tree, force_class=None):
    a = analyse(c)
    cls, slot = (force_class, None) if force_class else base_class(c.get("vtable_slots"), tree)
    canon = tree.canonical_classes().get(cls or "", [])
    n = a["ret_n"] // 4
    args = ", ".join("int a%d" % (i + 1) for i in range(n)) or ("" if a["thiscall"] else "")
    out = []
    span, why = D.cfg_span(addr)
    out.append("// FUNCTION: GAMEMD 0x%X" % addr)
    out.append("// span 0x%x (%s); ghidra size %s; convention %s; RET %d" % (
        span, why.split(" (")[0], (c.get("extent") or {}).get("ghidra_size", "?"), "__thiscall (ECX receiver)" if a["thiscall"] else "__fastcall/__stdcall (ECX not read first)", a["ret_n"]))
    if c.get("vtable_slots"):
        out.append("// vtable slot %s of %s" % (slot, ", ".join(sorted({s["cls"] for s in c["vtable_slots"]}))))
    out.append("// --- disassembly (objdump over the pinned PE) ---")
    for i in c["disasm"][:400]:
        out.append("//   %s  %-24s %s%s" % (i["addr"], i["bytes"], i["text"], ("  ; " + i["note"]) if i.get("note") else ""))
    if a["thiscall"] and cls:
        name = "vf_%d" % slot if slot is not None else "FUN_%08X" % addr
        out.append("int %s::%s(%s)" % (cls, name, args))
    elif a["thiscall"]:
        out.append("int Obj_%08X::FUN_%08X(%s)" % (addr, addr, args))
    else:
        out.append("int __fastcall FUN_%08X(%s)" % (addr, args))
    out.append("{")
    out.append("    // TODO: body. Member accesses through this: %s" % ", ".join(
        "+0x%X/%s" % (o, "|".join(str(w) for w in sorted(ws))) for o, ws in sorted(a["accesses"].items())))
    for reg, off in a["vcalls"]:
        out.append("    // virtual call through [%s+0x%X] = slot %d (vf_%d)" % (reg, off, off // 4, off // 4))
    out.append("    return 0;")
    out.append("}")
    decls = []
    for off, ws in sorted(a["accesses"].items()):
        decls.append("GG_STATIC_ASSERT(offsetof(%s, unknown_%X) == 0x%X);  // 0x%X, width %s" % (
            cls or "Obj_%08X" % addr, off, off, addr, "/".join(str(w) for w in sorted(ws))))
    for va, note in dict.fromkeys(a["callees"]):
        row = tree.by_addr.get(va)
        decls.append("// FUNCTION: GAMEMD 0x%X (decl; reloc)%s" % (va, (" -- " + (row["name"] if row else note)) if (row or note) else ""))
        if row:
            decls.append("//   manifest: %s %s (%s)" % (row["sym"], row["status"], row["tu"]))
        else:
            decls.append("extern int __fastcall FUN_%08X();" % va)
    for va, hint in sorted(a["globals"].items()):
        decls.append("// GLOBAL: GAMEMD 0x%X%s\nextern int DAT_%08X;" % (va, (" -- " + hint) if hint else "", va))
    for va, s in sorted(a["strings"].items()):
        decls.append("// STRING: GAMEMD 0x%X -- %r" % (va, s[:60]))
    view = []
    if cls and not canon:
        view.append("// No canonical header for %s: placeholder view (members at the asserted offsets)." % cls)
    if not cls and a["thiscall"]:
        view.append("class Obj_%08X {\npublic:" % addr)
        for off, ws in sorted(a["accesses"].items()):
            view.append("    // +0x%X\n    %s unknown_%X;" % (off, CTYPE[max(ws)], off))
        view.append("};")
    return dict(addr=addr, cls=cls, canon=canon, body="\n".join(out), decls="\n".join(decls), view="\n".join(view), span=span, slot=slot)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("addrs", nargs="+")
    ap.add_argument("--tree", default=D.MAIN_REPO)
    ap.add_argument("--out")
    ap.add_argument("--class", dest="cls")
    ap.add_argument("--rows", help="append addr/len lines to this rows.tsv")
    a = ap.parse_args(argv)
    tree = D.Tree(a.tree, "HEAD")
    parts = [emit(D.hx(x), ctx(D.hx(x)), tree, a.cls) for x in a.addrs]
    parts.sort(key=lambda p: p["addr"])
    incs = sorted({h for p in parts for h in p["canon"]})
    text = ["// SPDX-License-Identifier: GPL-3.0-or-later", "// Provenance: own-binary-via-Ghidra",
            "//   Skeleton generated by skeleton.py from the pinned PE: signatures, offsets, callees and",
            "//   globals are read from the instructions; bodies are TODO. Names are placeholders.",
            '#include "../_rt/gg_static_assert.h"']
    text += ['#include "%s"' % os.path.relpath(h, "match/core") for h in incs]
    text.append("")
    for p in parts:
        if p["view"]:
            text += [p["view"], ""]
    for p in parts:
        if p["decls"]:
            text += [p["decls"], ""]
    for p in parts:
        text += [p["body"], ""]
    src = "\n".join(text)
    if a.out:
        open(a.out, "w").write(src)
        print("wrote", a.out, "(%d functions, classes %s, headers %s)" % (len(parts), sorted({p["cls"] for p in parts if p["cls"]}), incs))
    else:
        print(src)
    if a.rows:
        with open(a.rows, "a") as f:
            for p in parts:
                f.write("0x%X\t\t0x%x\t\n" % (p["addr"], p["span"]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
