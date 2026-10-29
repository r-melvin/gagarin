#!/usr/bin/env python3
# Provenance: original; reads our pinned PE, our manifest/annotations, and Ghidra over our exe.
"""ctx.py — one context packet for one retail function.

Usage: ctx.py 0x552060 [--json] [--no-xref] [--max-insns N]

Prints, for the function at ADDR:
  extent     function_extent_audit.json corrected size if listed, else the
             CFG-closed span: every instruction reachable from the entry
             (fall-through + intra-window branches) inside [entry, next known
             entry); the extent ends at the last reachable instruction (RET/JMP).
             Manifest len and Ghidra size are shown alongside for comparison.
  manifest   rows, status/pct, owning TU, and source annotations (claims)
  disasm     linear objdump of the extent; call/jmp targets named from the
             manifest, annotations (incl. LIBRARY), library_map.json, or Ghidra
  refs       absolute operands that land in .data/.rdata/.bss: globals, and
             strings when the target holds printable text
  callers    ghidra x-ref to ADDR
  vtables    every RTTI vtable slot holding ADDR (cache/vtable_slots.json, made
             by scripts/orchestration/vtable_slots.py)
  attempts   rows from attempts.jsonl
  vc6flags   the owning TU's // VC6FLAGS line (or the locked default)
"""
import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common  # noqa: E402
import attempts  # noqa: E402

BRANCH = re.compile(r"^(j\w+|call|loop\w*)\s+(?:0x)?([0-9a-f]+)\s*$")
HEX = re.compile(r"0x([0-9a-f]{6,8})\b")
DEFAULT_FLAGS = "/nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2 (project default)"


def audit_extent(va):
    for f in common.load_json("function_extent_audit.json")["functions"]:
        if int(f["address"], 16) == va:
            return f["corrected_size"], f"function_extent_audit ({f['reason']})"
    return None


def cfg_extent(va):
    nxt = common.next_entry(va) or va + 0x1000
    window = min(nxt - va, 0x4000)
    insns = common.disasm(va, window)
    by_addr = {a: (a, b, t) for a, b, t in insns}
    seen, work = set(), [va]
    while work:
        a = work.pop()
        while a in by_addr and a not in seen:
            seen.add(a)
            _, b, t = by_addr[a]
            mn = t.split(" ")[0]
            m = BRANCH.match(t)
            if m and mn != "call":
                tgt = int(m.group(2), 16)
                if va <= tgt < va + window:
                    work.append(tgt)
            if mn.startswith("ret") or mn == "jmp" or t.startswith("(bad)") or mn == "int3":
                break
            a += len(b) // 2
    if not seen:
        return 0, "cfg (nothing decoded)"
    last = max(seen)
    return last + len(by_addr[last][1]) // 2 - va, f"cfg-closed to next entry {nxt:#x}"


def tu_flags(tu):
    p = common.WORKTREE / tu
    if not p.exists():
        p = common.MAIN / tu
    f = attempts.tu_flags(p)
    return f or DEFAULT_FLAGS


def classify_ref(va):
    img = common.pe()
    sec = img.section_of(va)
    if sec not in (".data", ".rdata", ".bss", ".idata"):
        return None
    kind = "global"
    s = img.cstring(va, 120) if sec != ".bss" else None
    if s and len(s) >= 3 and all(32 <= ord(c) < 127 or c in "\r\n\t" for c in s):
        kind = "string"
    return dict(addr=f"{va:#x}", section=sec, kind=kind, name=common.name_of(va),
                text=s if kind == "string" else None)


def packet(va, want_xref=True, max_insns=400):
    out = {"addr": f"{va:#x}"}
    ext = audit_extent(va)
    cfg = cfg_extent(va)
    size, src = ext if ext else cfg
    rows = common.manifest_by_addr().get(va, [])
    g = common.ghidra_functions().get(va)
    out["extent"] = dict(size=hex(size), source=src, cfg_size=hex(cfg[0]),
                         manifest_len=[r["len"] for r in rows] or None,
                         ghidra_size=hex(g["size"]) if g else None,
                         ghidra_name=g["name"] if g else None)
    out["manifest"] = rows
    out["annotations"] = [dict(kind=k, file=p, line=l, rest=r) for k, p, l, r in common.annotations().get(va, [])]
    try:
        import subprocess
        cl = subprocess.run(["python3", str(common.WORKTREE / "scripts/vc6/claimed.py"), hex(va)],
                            capture_output=True, text=True, cwd=common.WORKTREE)
        out["claimed"] = cl.stdout.strip()
    except OSError:
        out["claimed"] = None
    tus = sorted({r["tu"] for r in rows} | {a["file"] for a in out["annotations"] if a["file"].endswith(".cpp")})
    out["tus"] = [dict(tu=t, vc6flags=tu_flags(t)) for t in tus]

    insns = common.disasm(va, size) if size else []
    lines, refs = [], {}
    for a, b, t in insns[:max_insns]:
        note = ""
        m = BRANCH.match(t)
        if m:
            tgt = int(m.group(2), 16)
            if not (va <= tgt < va + size):
                note = common.name_of(tgt) or ""
        for hm in HEX.finditer(t):
            r = classify_ref(int(hm.group(1), 16))
            if r:
                refs[r["addr"]] = r
                note = (note + " " if note else "") + (repr(r["text"][:40]) if r["text"] else (r["name"] or r["kind"]))
        lines.append(dict(addr=f"{a:#x}", bytes=b, text=t, note=note or None))
    out["disasm"] = lines
    out["disasm_truncated"] = len(insns) > max_insns
    out["refs"] = sorted(refs.values(), key=lambda r: r["addr"])
    if want_xref:
        out["callers"] = [dict(frm=f"{int(x['from'], 16):#x}", func=x.get("from_function"), type=x["ref_type"])
                          for x in common.ghidra_json("x-ref", "to", hex(va))]
    vt = json.loads((common.CACHE / "vtable_slots.json").read_text()) if (common.CACHE / "vtable_slots.json").exists() else {"vtables": []}
    target = f"0x{va:08X}"
    out["vtable_slots"] = [dict(cls=v["class"], base_offset=v["base_offset"], vtable=v["vtable_va"], slot=i)
                           for v in vt["vtables"] for i, s in enumerate(v["slots"]) if s.upper() == target.upper()]
    out["attempts"] = attempts.for_addr(attempts.load(attempts.LEDGER), hex(va))
    return out


def show(p):
    e = p["extent"]
    print(f"== {p['addr']}  extent {e['size']} [{e['source']}]  cfg={e['cfg_size']} manifest={e['manifest_len']} "
          f"ghidra={e['ghidra_size']} ({e['ghidra_name']})")
    for r in p["manifest"]:
        print(f"  manifest: {r['status']} {r.get('pct')}%  {r['name']}  {r['sym']}  len={r['len']}  tu={r['tu']}")
    if not p["manifest"]:
        print("  manifest: (no row)")
    for a in p["annotations"]:
        print(f"  annot: {a['kind']} {a['file']}:{a['line']} {a['rest'][:60]}")
    if p.get("claimed"):
        print("  claimed.py: " + p["claimed"].replace("\n", "\n    "))
    for t in p["tus"]:
        print(f"  TU {t['tu']}  VC6FLAGS: {t['vc6flags']}")
    print("-- disasm")
    for l in p["disasm"]:
        print(f"  {l['addr'][2:]:>8}  {l['bytes']:<22} {l['text']:<44}" + (f" ; {l['note']}" if l["note"] else ""))
    if p["disasm_truncated"]:
        print("  ... (truncated; --max-insns)")
    print("-- globals / strings")
    for r in p["refs"]:
        print(f"  {r['addr']} {r['section']:<6} {r['kind']:<6} " + (repr(r["text"][:60]) if r["text"] else str(r["name"] or "")))
    if "callers" in p:
        print(f"-- callers ({len(p['callers'])})")
        for c in p["callers"]:
            print(f"  {c['frm']} in {c['func']} [{c['type']}]")
    print("-- vtable slots")
    for v in p["vtable_slots"]:
        print(f"  {v['cls']} (+{v['base_offset']}) vtable {v['vtable']} slot {v['slot']}")
    print(f"-- attempts ({len(p['attempts'])})")
    for r in p["attempts"]:
        print("  " + attempts.fmt(r).replace("\n", "\n  "))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("addr")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--no-xref", action="store_true")
    ap.add_argument("--max-insns", type=int, default=400)
    a = ap.parse_args(argv)
    p = packet(int(a.addr, 16), not a.no_xref, a.max_insns)
    if a.json:
        print(json.dumps(p, indent=1))
    else:
        show(p)


if __name__ == "__main__":
    main()
