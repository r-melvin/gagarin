#!/usr/bin/env python3
# SPDX-Provenance: own-binary-via-Ghidra
#
# layout_mine.py — two whole-image extractions that feed every future layout
# header, both read straight off the user's own retail gamemd.exe:
#
#   1. class_sizes.json        `PUSH <n>; CALL operator new` before a ctor call
#                              gives the object's exact size.
#   2. ctor_field_offsets.json every [receiver+disp] store inside a constructor,
#                              with the instruction address that proves it.
#
# THE TRAP (docs/residual_census.md #4): UnitClass::TryToDeploy writes
# [EBX+0x6CA] where EBX is the BuildingClass being deployed, not the unit. A
# naive "collect every [reg+disp] in this class's methods" sweep invents members.
# Two defences are built in, not bolted on:
#   * constructors ONLY — never arbitrary methods;
#   * a forward dataflow tracks which locations still provably hold the receiver
#     (entry ECX), and a store through a register that has since been reloaded
#     from anywhere else is dropped on the spot.
#
# Ground truth:
#   entry points + sizes -> `ghidra function list --limit 25000 --json`
#   instruction stream   -> objdump -d -M intel over .text (same file)
#   class identity       -> scripts/data/rtti_classes.json (vtable VA -> name)
#
# Usage: layout_mine.py <gamemd.exe> <funcs.json> <rtti_classes.json> <outdir>

import json
import re
import subprocess
import sys
from collections import defaultdict

TEXT_START = 0x401000
TEXT_END = 0x7E038D

OPERATOR_NEW = 0x7C8E17           # ??2@YAPAXI@Z

REG32 = ("eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi")
SUBREG = {}
for _f, _p in (("eax", ("ax", "al", "ah")), ("ecx", ("cx", "cl", "ch")),
               ("edx", ("dx", "dl", "dh")), ("ebx", ("bx", "bl", "bh")),
               ("esi", ("si",)), ("edi", ("di",)),
               ("esp", ("sp",)), ("ebp", ("bp",))):
    SUBREG[_f] = _f
    for _q in _p:
        SUBREG[_q] = _f

LINE_RE = re.compile(r"^\s*([0-9a-f]+):\t([0-9a-f ]+)\t(\S+)\s*(.*)$")
# [reg], [reg+0xNN], [reg-0xNN]  — a single base register, no index, no scale
MEM_RE = re.compile(r"^(?:(BYTE|WORD|DWORD|QWORD|TBYTE|FWORD) PTR )?"
                    r"\[(e[a-z]{2})([+-]0x[0-9a-f]+)?\]$")
WIDTH = {"BYTE": 1, "WORD": 2, "DWORD": 4, "QWORD": 8, "TBYTE": 10, "FWORD": 6}


def disassemble(binary):
    out = subprocess.run(
        ["objdump", "-d", "-M", "intel",
         "--start-address=0x%x" % TEXT_START,
         "--stop-address=0x%x" % TEXT_END, binary],
        capture_output=True, text=True, check=True).stdout
    seq = []
    for line in out.split("\n"):
        m = LINE_RE.match(line)
        if not m:
            continue
        seq.append((int(m.group(1), 16), m.group(3),
                    m.group(4).split("#")[0].split("<")[0].strip()))
    insns = {}
    order = []
    for i, (addr, mnem, ops) in enumerate(seq):
        nxt = seq[i + 1][0] if i + 1 < len(seq) else addr + 1
        insns[addr] = (nxt - addr, mnem, ops)
        order.append(addr)
    return insns, order


def split_ops(ops):
    """Split an operand string on top-level commas."""
    out, depth, cur = [], 0, ""
    for ch in ops:
        if ch == "[":
            depth += 1
        elif ch == "]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def mem_parts(op):
    """-> (base_reg, disp, width) for a simple [base+disp], else None."""
    m = MEM_RE.match(op)
    if not m:
        return None
    disp = int(m.group(3), 16) if m.group(3) else 0
    return m.group(2), disp, WIDTH.get(m.group(1) or "", 0)


def imm_of(op):
    try:
        return int(op, 16) if op.startswith("0x") else int(op)
    except ValueError:
        return None


def branch_target(ops):
    o = ops.strip()
    if o.startswith("0x"):
        try:
            return int(o, 16)
        except ValueError:
            return None
    return None


COND_JMP = re.compile(r"^j(?!mp$)[a-z]{1,3}$")

# mnemonics whose FIRST operand is written when it is a memory reference
STORE = {"mov", "fstp", "fst", "fistp", "fisttp", "movsd", "movss", "movq",
         "movd", "fbstp"}
RMW = {"and", "or", "xor", "add", "sub", "adc", "sbb", "inc", "dec", "neg",
       "not", "shl", "shr", "sar", "rol", "ror", "btr", "bts", "xadd"}


# --------------------------------------------------------------- receiver DFA

class CtorScan(object):
    """Forward dataflow over one function: which locations still hold ECX-at-entry."""

    def __init__(self, insns, entry, limit):
        self.insns = insns
        self.entry = entry
        self.limit = limit

    def run(self):
        insns, entry, limit = self.insns, self.entry, self.limit
        # state: frozenset of holder tokens. registers 'esi'; frames 'ebp-0x10'
        start = frozenset([("ecx", 0)])
        state = {entry: start}
        work = [entry]
        stores = []          # (addr, disp, width, mnem, kind, srcdesc)
        vptrs = []           # (addr, disp, vtable_va)
        callees = set()      # direct CALL targets, for base-ctor detection
        returns_this = False # MSVC constructors return `this` in EAX
        seen_pairs = set()
        steps = 0
        while work:
            steps += 1
            if steps > 60000:
                break
            pc = work.pop()
            cur = state[pc]
            while True:
                if pc not in insns or pc >= limit:
                    break
                n, mnem, ops = insns[pc]
                nxt = pc + n
                out, rec = self.step(pc, mnem, ops, cur)
                for r in rec:
                    if (r[0], r[1]) not in seen_pairs:
                        seen_pairs.add((r[0], r[1]))
                        if r[4] == "vptr":
                            vptrs.append((r[0], r[1], r[5]))
                        stores.append(r)
                if mnem == "call":
                    t = branch_target(ops)
                    if t is not None:
                        callees.add(t)
                if mnem == "ret" or mnem.startswith("ret") or mnem in ("ud2", "hlt"):
                    if ("eax", 0) in cur:
                        returns_this = True
                    break
                succs = []
                if mnem == "jmp":
                    t = branch_target(ops)
                    if t is None:
                        break
                    succs = [t]
                elif COND_JMP.match(mnem):
                    t = branch_target(ops)
                    succs = ([t] if t is not None else []) + [nxt]
                else:
                    succs = [nxt]
                live = []
                for s in succs:
                    if not (entry <= s < limit):
                        continue
                    old = state.get(s)
                    merged = out if old is None else (old & out)
                    if old is None or merged != old:
                        state[s] = merged
                        live.append(s)
                if not live:
                    break
                pc = live[0]
                cur = state[pc]
                for extra in live[1:]:
                    work.append(extra)
        return stores, vptrs, callees, returns_this

    def step(self, pc, mnem, ops, cur):
        """-> (state after, [records])"""
        recs = []
        o = split_ops(ops)
        new = set(cur)

        def kill(tok):
            for e in [e for e in new if e[0] == tok]:
                new.discard(e)

        # --- receiver-relative memory reference in operand 0 (a store)
        cm = dict(cur)
        if o and (mnem in STORE or mnem in RMW):
            mp = mem_parts(o[0])
            if mp:
                base, disp, w = mp
                if base in cm and 0 <= disp + cm[base] < 0x10000:
                    disp = disp + cm[base]
                    src = o[1] if len(o) > 1 else ""
                    iv = imm_of(src) if src else None
                    kind = "store" if mnem in STORE else "rmw"
                    if (mnem == "mov" and w == 4 and iv is not None
                            and 0x400000 <= iv < 0x1000000):
                        kind = "vptr"
                    recs.append((pc, disp, w, mnem, kind, iv if kind == "vptr" else src))
        # --- lea reg,[receiver+disp]: proves a sub-object / array offset
        if mnem == "lea" and len(o) == 2:
            mp = mem_parts(o[1])
            if mp and mp[0] in cm and 0 <= mp[1] + cm[mp[0]] < 0x10000:
                recs.append((pc, mp[1] + cm[mp[0]], 0, "lea", "lea", o[0]))

        # --- transfer function
        if mnem == "mov" and len(o) == 2:
            dst, src = o
            sd = SUBREG.get(dst)
            if sd and dst in REG32:                    # full 32-bit reg dest
                kill(dst)
                if src in cm:
                    new.add((dst, cm[src]))
            elif sd:                                   # partial write destroys it
                kill(sd)
            else:
                mp = mem_parts(dst)
                if mp and mp[0] == "ebp" and mp[2] == 4:
                    tok = "ebp%+#x" % mp[1] if mp[1] else "ebp+0x0"
                    tok = "ebp[%d]" % mp[1]
                    kill(tok)
                    if src in cm:
                        new.add((tok, cm[src]))
            # reload from a frame slot
            if dst in REG32:
                mp = mem_parts(src)
                if mp and mp[0] == "ebp" and mp[2] == 4:
                    tok = "ebp[%d]" % mp[1]
                    kill(dst)
                    if tok in cm:
                        new.add((dst, cm[tok]))
        elif mnem == "lea" and len(o) == 2 and o[0] in REG32:
            # lea r,[recv+K] keeps a PROVABLE receiver-relative pointer: r is
            # then the receiver displaced by K, and a later [r+d] store is the
            # member at K+d. This is how MSVC reaches an embedded sub-object.
            mp = mem_parts(o[1])
            kill(o[0])
            if mp and mp[0] in cm and 0 <= mp[1] + cm[mp[0]] < 0x10000:
                new.add((o[0], mp[1] + cm[mp[0]]))
        elif mnem in ("pop",) and o and o[0] in REG32:
            kill(o[0])
        elif mnem in ("xchg",) and len(o) == 2:
            for x in o:
                if x in REG32:
                    kill(x)
        elif mnem == "call":
            # __thiscall/__cdecl: EAX/ECX/EDX are volatile across the call.
            for r in ("eax", "ecx", "edx"):
                kill(r)
        elif mnem in ("div", "idiv", "mul", "imul", "cdq", "cwd"):
            for r in ("eax", "edx"):
                kill(r)
        elif mnem.startswith("rep") or mnem.startswith("stos") or mnem.startswith("movs") \
                or mnem.startswith("scas") or mnem.startswith("lods") or mnem.startswith("cmps"):
            # string ops advance EDI (stos/movs/scas) and ESI (movs/lods/cmps);
            # a REP prefix also consumes ECX. Killing ESI on a `rep stosd`
            # would lose every later receiver store -- it does not touch ESI.
            body = (ops or "") + " " + mnem
            if mnem.startswith("rep"):
                kill("ecx")
            if "stos" in body or "movs" in body or "scas" in body:
                kill("edi")
            if "movs" in body or "lods" in body or "cmps" in body:
                kill("esi")
        elif o and o[0] in REG32 and mnem not in ("push", "cmp", "test", "nop"):
            kill(o[0])
        elif o and SUBREG.get(o[0]) and mnem not in ("push", "cmp", "test", "nop"):
            kill(SUBREG[o[0]])
        return frozenset(new), recs


# ------------------------------------------------------------ allocation sites

def mine_alloc_sites(insns, order, funcs, vtset=()):
    """PUSH <n>; CALL operator new; ... MOV ECX,<ptr>; CALL <ctor>."""
    idx = {a: i for i, a in enumerate(order)}
    sites = []
    for addr, (n, mnem, ops) in insns.items():
        if mnem != "call" or branch_target(ops) != OPERATOR_NEW:
            continue
        i = idx[addr]
        # the single argument is the last PUSH before the call
        size = None
        push_at = None
        for j in range(i - 1, max(0, i - 10), -1):
            a2 = order[j]
            _, m2, o2 = insns[a2]
            if m2 == "call":
                break
            if m2 == "push":
                v = imm_of(o2.strip())
                if v is not None:
                    size, push_at = v, a2
                break
            if m2 in ("jmp",) or COND_JMP.match(m2):
                break
        if size is None or not (1 <= size <= 0x40000):
            continue
        # forward: follow the returned pointer to the ctor called on it
        holders = set(["eax"])
        ctor = None
        ctor_at = None
        for j in range(i + 1, min(len(order), i + 40)):
            a2 = order[j]
            _, m2, o2 = insns[a2]
            oo = split_ops(o2)
            if m2 == "call":
                t = branch_target(o2)
                if "ecx" in holders and t is not None and t != OPERATOR_NEW:
                    ctor, ctor_at = t, a2
                break
            if m2 == "ret" or m2.startswith("ret"):
                break
            if m2 == "mov" and len(oo) == 2:
                dst, src = oo
                if dst in REG32:
                    if src in holders:
                        holders.add(dst)
                    else:
                        holders.discard(dst)
                elif SUBREG.get(dst):
                    holders.discard(SUBREG[dst])
                else:
                    mp = mem_parts(dst)
                    if mp and mp[0] in ("ebp", "esp") and mp[2] == 4:
                        tok = "%s[%d]" % (mp[0], mp[1])
                        if src in holders:
                            holders.add(tok)
                        else:
                            holders.discard(tok)
                if dst in REG32:
                    mp = mem_parts(src)
                    if mp and mp[0] in ("ebp", "esp") and mp[2] == 4:
                        tok = "%s[%d]" % (mp[0], mp[1])
                        if tok in holders:
                            holders.add(dst)
                        else:
                            holders.discard(dst)
            elif m2 == "pop" and oo and oo[0] in REG32:
                holders.discard(oo[0])
            elif oo and oo[0] in REG32 and m2 not in ("push", "cmp", "test"):
                holders.discard(oo[0])
        if ctor is None:
            # no ctor call: either a raw buffer, or a constructor the compiler
            # inlined. An inlined ctor still stores its vptr through the new
            # pointer, which recovers both the size and the class identity.
            holders = set(["eax"])
            vp = None
            for j in range(i + 1, min(len(order), i + 60)):
                a2 = order[j]
                _, m2, o2 = insns[a2]
                oo = split_ops(o2)
                if m2 == "ret" or m2.startswith("ret"):
                    break
                if m2 == "mov" and len(oo) == 2:
                    dst, src = oo
                    mp = mem_parts(dst)
                    iv = imm_of(src)
                    if (mp and mp[0] in holders and mp[1] == 0 and mp[2] == 4
                            and iv in vtset):
                        vp = (a2, iv)
                        break
                    if dst in REG32:
                        if src in holders:
                            holders.add(dst)
                        else:
                            holders.discard(dst)
                        mp2 = mem_parts(src)
                        if mp2 and mp2[0] in ("ebp", "esp") and mp2[2] == 4:
                            tok = "%s[%d]" % (mp2[0], mp2[1])
                            if tok in holders:
                                holders.add(dst)
                    elif SUBREG.get(dst):
                        holders.discard(SUBREG[dst])
                    elif mp and mp[0] in ("ebp", "esp") and mp[2] == 4:
                        tok = "%s[%d]" % (mp[0], mp[1])
                        if src in holders:
                            holders.add(tok)
                        else:
                            holders.discard(tok)
                elif m2 == "call":
                    for r in ("eax", "ecx", "edx"):
                        holders.discard(r)
                elif oo and oo[0] in REG32 and m2 not in ("push", "cmp", "test"):
                    holders.discard(oo[0])
            sites.append({"kind": "inlined-ctor" if vp else "no-ctor",
                          "new_at": addr, "push_at": push_at,
                          "size": size, "ctor": None,
                          "vptr_at": vp[0] if vp else None,
                          "vtable": vp[1] if vp else None})
        else:
            sites.append({"kind": "ok", "new_at": addr, "push_at": push_at,
                          "size": size, "ctor": ctor, "ctor_call_at": ctor_at})
    return sites


# --------------------------------------------------------------------- driver

def load_rtti(path):
    d = json.load(open(path))
    vt2cls = {}
    cls_meta = {}
    for mangled, c in d["classes"].items():
        name = c.get("demangled_name") or mangled
        cls_meta[name] = {"mangled": mangled,
                          "base_offsets": sorted(set(
                              l["base_offset"] for l in c["locators"])),
                          "base_chain": c.get("base_chain")}
        for loc in c["locators"]:
            vt = loc.get("vtable_va")
            if vt:
                vt2cls.setdefault(int(vt, 16), []).append((name, loc["base_offset"]))
    return vt2cls, cls_meta


def containing(starts, ranges, a):
    import bisect
    i = bisect.bisect_right(starts, a) - 1
    if i < 0:
        return None
    s = starts[i]
    if a < ranges[s][0]:
        return s
    return None


def main():
    binary, funcs_path, rtti_path, outdir = sys.argv[1:5]
    sys.stderr.write("disassembling ...\n")
    insns, order = disassemble(binary)
    sys.stderr.write("  %d instructions\n" % len(insns))

    vt2cls, cls_meta = load_rtti(rtti_path)
    vtset = set(vt2cls)

    funcs = {}
    for f in json.load(open(funcs_path)):
        a = int(f["entry_point"], 16)
        funcs[a] = (a + int(f["size"]), f.get("name"))
    starts = sorted(funcs)

    # ---- 1. allocation sites
    sys.stderr.write("mining allocation sites ...\n")
    sites = mine_alloc_sites(insns, order, funcs, vtset)
    sys.stderr.write("  %d operator-new sites, %d bound to a ctor\n"
                     % (len(sites), sum(1 for s in sites if s["kind"] == "ok")))

    # ---- 2. candidate constructors: alloc-bound + every vptr writer
    cand = set(s["ctor"] for s in sites if s["kind"] == "ok")
    cand = set(a for a in cand if containing(starts, funcs, a) == a or a in funcs)
    vptr_writers = set()
    for addr, (n, mnem, ops) in insns.items():
        if mnem != "mov":
            continue
        o = split_ops(ops)
        if len(o) != 2:
            continue
        iv = imm_of(o[1])
        if iv is None or iv not in vtset:
            continue
        mp = mem_parts(o[0])
        if not mp or mp[2] != 4:
            continue
        fn = containing(starts, funcs, addr)
        if fn is not None:
            vptr_writers.add(fn)
    cand |= vptr_writers
    cand = set(a for a in cand if a in funcs)
    sys.stderr.write("  %d candidate constructors (%d vptr writers)\n"
                     % (len(cand), len(vptr_writers)))

    # operator delete: the callee every scalar deleting destructor passes to
    delete_callees = set()
    for addr, (n, mnem, ops) in insns.items():
        pass

    # ---- 3. mine each candidate
    alloc_ctors = set(s["ctor"] for s in sites if s["kind"] == "ok")
    results = {}
    for k, ctor in enumerate(sorted(cand)):
        if k % 500 == 0:
            sys.stderr.write("  ctor %d/%d\n" % (k, len(cand)))
        limit, gname = funcs[ctor]
        stores, vptrs, callees, rthis = CtorScan(insns, ctor, limit).run()
        results[ctor] = (stores, vptrs, limit, gname, callees, rthis)

    json.dump({"sites": sites,
               "results": {("0x%X" % a): {
                   "stores": [[("0x%X" % r[0]), r[1], r[2], r[3], r[4],
                               (("0x%X" % r[5]) if isinstance(r[5], int) else r[5])]
                              for r in v[0]],
                   "vptrs": [["0x%X" % x[0], x[1], "0x%X" % x[2]] for x in v[1]],
                   "limit": "0x%X" % v[2], "ghidra_name": v[3],
                   "callees": ["0x%X" % c for c in sorted(v[4])],
                   "returns_this": v[5],
                   "alloc_bound": a in alloc_ctors}
                   for a, v in results.items()}},
              open(outdir + "/raw_mine.json", "w"))
    sys.stderr.write("raw written\n")


if __name__ == "__main__":
    main()
