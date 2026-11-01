#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads only the user's retail gamemd.exe (GAMEMD_BINARY) and
#   scripts/data/{function_extents,match_manifest}.json (through inline_sites.py's cached disassembly).
"""Census of VectorClass/DynamicVectorClass member expansions in the retail .text.

For each member the report lists the out-of-line instantiations (functions whose whole body is the
member), the direct call sites that reach them, and the sites where the same body is expanded inline
in another function. Detection is on the register-abstracted instruction stream of
inline_sites.py, anchored on the field offsets the layout fixes (+4 Items, +8 Capacity, +0xC
IsInitialized, +0xD IsAllocated, +0x10 Count, +0x14 CapacityIncrement), so it is element-size
agnostic for scalar/pointer elements and counts other shapes under their own heading.

    vector_census.py [--member M ...] [--sites] [--json OUT]

Report only; nothing is edited.
"""
import argparse, collections, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import inline_sites as IS

JN = re.compile(r" [+-]\d+$")


def view(d):
    """Per function: (addr, length, token strings with jump distances reduced to direction)."""
    table = [JN.sub(lambda m: " back" if m.group(0)[1] == "-" else " fwd", s) for s in d["table"]]
    out = []
    for a, n, toks, addrs, sizes in d["funcs"]:
        out.append((a, n, [table[t] for t in toks], addrs))
    return out


SHIFT = re.compile(r"^mov DWORD PTR \[R32\+R32\*(\d)-0x(\d)\],R32$")


def find_delete(fv):
    """Inline or whole-function Delete(int): decrement Count, shift the tail down one element."""
    res = []
    for i, s in enumerate(fv):
        m = SHIFT.match(s)
        if not m or m.group(1) != m.group(2):
            continue
        win = fv[max(0, i - 10):i]
        if any(w == "dec R32" for w in win) and any(w == "mov DWORD PTR [R32+0x10],R32" for w in win):
            res.append(i)
    return res


def find_additem(fv):
    """AddItem growth test: IsAllocated byte test, then push 0 / push newcap / call [vt+8]."""
    res = []
    for i, s in enumerate(fv):
        if s == "call DWORD PTR [R32+0x8]" and i >= 3 and fv[i - 1].startswith("mov R32,R32") or s == "call DWORD PTR [R32+0x8]":
            win = fv[max(0, i - 14):i]
            if "push 0x0" in win and any(w == "mov R8,BYTE PTR [R32+0xd]" or w == "cmp BYTE PTR [R32+0xd],R8" or w == "cmp BYTE PTR [R32+0xd],0x0" for w in win):
                res.append(i)
    return res


def find_find_virtual(fv):
    """Virtual FindItemIndex dispatch (slot +0x10) followed by the -1 test."""
    return [i for i, s in enumerate(fv) if s == "call DWORD PTR [R32+0x10]" and any(w == "cmp R32,0xffffffff" for w in fv[i + 1:i + 3])]


def find_ctor_base(fv):
    """Inline VectorClass(int, T*) body: Capacity, IsInitialized=1, IsAllocated stores and operator new[]."""
    res = []
    for i, s in enumerate(fv):
        if s == "mov BYTE PTR [R32+0xc],0x1":
            win = fv[max(0, i - 6):i + 8]
            if any(w.startswith("mov DWORD PTR [R32+0x8],") for w in win) and any(w.startswith("mov BYTE PTR [R32+0xd],") for w in win):
                res.append(i)
    return res


def find_ctor_dyn_tail(fv):
    """Dynamic ctor tail: vptr store then CapacityIncrement/Count init."""
    res = []
    for i, s in enumerate(fv):
        if re.fullmatch(r"mov DWORD PTR \[R32\],0x7[ef][0-9a-f]{4}", s):
            win = fv[i + 1:i + 4]
            if any(w.startswith("mov DWORD PTR [R32+0x14],") for w in win) and any(w.startswith("mov DWORD PTR [R32+0x10],") for w in win):
                res.append(i)
    return res


def find_clear_inline(fv):
    """Clear body: IsAllocated test then operator delete, Capacity/IsAllocated reset."""
    res = []
    for i, s in enumerate(fv):
        if s == "call 0x7c8b3d":
            win = fv[max(0, i - 5):i]
            if any(w.startswith("cmp BYTE PTR [R32+0xd],") or w.startswith("test BYTE PTR [R32+0xd]") for w in win):
                res.append(i)
    return res


DETECT = [
    ("Delete(int)", find_delete),
    ("AddItem growth", find_additem),
    ("FindItemIndex virtual dispatch", find_find_virtual),
    ("VectorClass ctor body", find_ctor_base),
    ("Dynamic ctor tail", find_dyn_tail := find_ctor_dyn_tail),
    ("Clear body (IsAllocated test + delete)", find_clear_inline),
]


def census(d, status):
    fvs = view(d)
    funcs = {a: (n, fv, addrs) for a, n, fv, addrs in fvs}
    calls = collections.defaultdict(list)          # target -> [caller]
    for a, n, fv, addrs in fvs:
        for s in fv:
            if re.fullmatch(r"call 0x[0-9a-f]+", s):
                calls[int(s[5:], 16)].append(a)
    out = {}
    for name, det in DETECT:
        hits = {}
        for a, n, fv, addrs in fvs:
            h = det(fv)
            if h:
                hits[a] = [addrs[i] for i in h]
        # an out-of-line copy: a short function whose body is dominated by the member
        ool = {a: h for a, h in hits.items() if len(funcs[a][1]) <= (45 if "ctor" in name or "AddItem" in name else 26)}
        inl = {a: h for a, h in hits.items() if a not in ool}
        reached = {a: calls.get(a, []) for a in ool}
        out[name] = {
            "out_of_line": [{"addr": a, "status": status.get(a, "unclaimed"), "insns": len(funcs[a][1]),
                             "direct_callers": len(reached[a])} for a in sorted(ool)],
            "direct_call_sites": sum(len(v) for v in reached.values()),
            "inline_functions": len(inl),
            "inline_sites": sum(len(v) for v in inl.values()),
            "inline_in": {a: v for a, v in sorted(inl.items())},
        }
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--member", action="append")
    ap.add_argument("--sites", action="store_true", help="list the inline functions")
    ap.add_argument("--json")
    ap.add_argument("--rebuild", action="store_true")
    o = ap.parse_args(argv)
    class O:  # options inline_sites.load_data needs
        kinds = ("engine",); keep_stack = False; rebuild = o.rebuild
    d = IS.load_data(O)
    st, _ = IS.status_map()
    res = census(d, st)
    for name, r in res.items():
        if o.member and not any(m.lower() in name.lower() for m in o.member):
            continue
        print(f"{name}: out-of-line copies {len(r['out_of_line'])}, direct call sites to them {r['direct_call_sites']}, "
              f"inline sites {r['inline_sites']} in {r['inline_functions']} functions")
        for c in r["out_of_line"][:40]:
            print(f"   ool {c['addr']:#x} [{c['status']}] {c['insns']} insns, {c['direct_callers']} direct callers")
        if len(r["out_of_line"]) > 40:
            print(f"   ... {len(r['out_of_line']) - 40} more")
        if o.sites:
            print("   inline in:", " ".join(f"{a:#x}x{len(v)}" for a, v in r["inline_in"].items()))
    if o.json:
        json.dump({k: {**v, "inline_in": {hex(a): [hex(x) for x in s] for a, s in v["inline_in"].items()}} for k, v in res.items()},
                  open(o.json, "w"), indent=1)


if __name__ == "__main__":
    main()
