#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the developer-supplied pinned PE
# (GAMEMD_BINARY) and tracked census data. Output holds addresses, lengths,
# class tags and counts only; no retail bytes, strings or instruction text.
"""Tag every large (>= 1024 bytes) engine function with no manifest row by
shape class and by the source idioms its code contains.

Shape classes (one primary, chosen by evidence, others listed when strong):
  static-initialiser  listed in a .CRT$XCU-style pointer table or called from a
                      tiny thunk that is, else a long run of stores/ctor calls
                      into global data
  ini-reader          many calls to the CCINIClass read helpers
  persist             IStream Read/Write calls and SwizzleManager calls
  window-proc         WM_ constants, DefWindowProc/CallWindowProc/SendMessage
  ctor-dtor           stores of known vtable addresses into a member
  string-lookup       jump tables / compare chains returning constants
  state-machine       jump table indexed by a member field
  math                high x87 fraction
  generic             none of the above

Idioms (counts; each corresponds to a known source construct): assert_site,
vec_add / vec_remove (DynamicVectorClass inline expansion), counted_loop,
rtti_check, cdtimer_read, coord_cell (shifts by 8), str_push, jump_table,
x87 ratio and matched/unmatched callee counts. Detectors are heuristics over
objdump text; counts are evidence for triage, not proof.

Usage:
  GAMEMD_BINARY=/path/gamemd.exe scripts/vc6/shape_classify.py \
      [--out scripts/data/large_function_shapes.json] [--wl FILE.tsv] [--jobs N]
"""

import argparse
import bisect
from collections import Counter
import json
from multiprocessing import Pool
import os
from pathlib import Path
import re
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / "scripts/data"
MIN_LEN = 1024
DEFAULT_WL = Path("/home/richard/Projects/gagarin/.coordination/claude-orch/wl/large_shapes.tsv")

INI_HELPERS = {0x5276D0: "int", 0x5295F0: "bool", 0x528A10: "string", 0x5283D0: "double", 0x474620: "fraction"}
WM_BIG = {0x10, 0x0F, 0x14, 0x20, 0x24, 0x46, 0x47, 0x81, 0x100, 0x101, 0x102, 0x104, 0x105, 0x110, 0x111,
          0x112, 0x113, 0x114, 0x115, 0x200, 0x201, 0x202, 0x203, 0x204, 0x205, 0x206, 0x207, 0x208, 0x209,
          0x20A, 0x219, 0x231, 0x232, 0x2A3}
WIN_DEFAULT = ("DefWindowProc", "CallWindowProc", "DefDlgProc", "DefMDIChildProc")
WIN_IMPORTS = ("DefWindowProc", "CallWindowProc", "SendMessage", "PostMessage", "DefDlgProc", "GetWindowLong",
               "SetWindowLong", "BeginPaint", "EndPaint", "DefMDIChildProc")

# generation-score base per class (how mechanical the source is to write)
BASE = {"static-initialiser": 90, "ini-reader": 85, "string-lookup": 75, "persist": 70, "ctor-dtor": 55,
        "state-machine": 40, "window-proc": 35, "math": 30, "generic": 15}
PRIORITY = ["static-initialiser", "ini-reader", "persist", "window-proc", "ctor-dtor", "string-lookup",
            "state-machine", "math", "generic"]
THRESHOLD = 0.35

HEX = re.compile(r"^(?:0x)?[0-9a-f]+$")
IMM = re.compile(r"^0x[0-9a-f]+$")
ABS = re.compile(r"ds:(0x[0-9a-f]+)")
MEM = re.compile(r"\[([^\]]+)\]")
JT = re.compile(r"^jmp\s+DWORD PTR \[\w+\*4\+0x[0-9a-f]+\]$")


# ---- instruction parsing ----------------------------------------------------

def split(text):
    parts = text.split(None, 1)
    mn = parts[0]
    while mn in ("rep", "repe", "repz", "repne", "repnz", "lock") and len(parts) > 1:
        parts = parts[1].split(None, 1)
        mn = parts[0]
    ops = [o.strip() for o in parts[1].split(",")] if len(parts) > 1 else []
    return mn, ops


def imm(op):
    return int(op, 16) if IMM.match(op) else None


def mem_disp(op):
    """(base register or None, displacement) of a [reg+disp] operand, else None."""
    m = MEM.search(op)
    if not m or "*" in m.group(1):
        return None
    base, disp = None, 0
    for t in re.split(r"(?=[+-])", m.group(1)):
        t = t.strip()
        if not t:
            continue
        sign = -1 if t.startswith("-") else 1
        t = t.lstrip("+-")
        if t.startswith("0x"):
            disp += sign * int(t, 16)
        else:
            base = t
    return base, disp


def is_member(op):
    md = mem_disp(op)
    return bool(md and md[0] and md[0] not in ("esp",) and md[1] != 0)


class Ctx:
    """Everything the detectors need from outside the function body."""

    def __init__(self, is_string=None, imports=None, status=None, vtables=(), writable=None, engine=None,
                 swizzle=(), ini_extra=()):
        self.is_string = is_string or (lambda va: None)      # -> None | "str" | "file"
        self.imports = imports or {}                          # IAT slot VA -> name
        self.status = status or {}                            # entry VA -> matched|partial
        self.vtables = set(vtables)
        self.writable = writable or (lambda va: False)        # .data/.bss VA
        self.engine = engine or (lambda va: True)             # direct-call target is engine code
        self.swizzle = set(swizzle)
        self.ini = dict(INI_HELPERS)
        for a in ini_extra:
            self.ini.setdefault(a, "read")


# ---- feature extraction -----------------------------------------------------

def features(insns, ctx, length=None):
    """insns: [(addr, size, text)] in address order -> dict of counts/flags."""
    n = len(insns)
    parsed = [split(t) for _, _, t in insns]
    f = Counter()
    targets = []
    imports = Counter()
    jt_member = 0
    jt_sizes = []
    glob_addrs = set()
    xcu_hint = 0

    def prev(i, k):
        return parsed[max(0, i - k):i]

    for i, (mn, ops) in enumerate(parsed):
        a = insns[i][0]
        o0 = ops[0] if ops else ""
        o1 = ops[1] if len(ops) > 1 else ""
        if mn.startswith("f") and mn not in ("fwait",):
            f["x87"] += 1
        if mn == "call":
            m = ABS.search(o0)
            if HEX.match(o0) and not o0.startswith("DWORD"):
                targets.append(int(o0, 16))
            elif m and "DWORD PTR" in o0:
                imports[str(ctx.imports.get(int(m.group(1), 16), "?"))] += 1
            else:
                f["call_indirect"] += 1
                md = mem_disp(o0)
                if md and md[1] == 0x2C:
                    nxt = parsed[i + 1:i + 5]
                    if any(m2 in ("cmp", "test") and (len(p) > 1 and (imm(p[1]) is not None or p[0] == p[1]))
                           for m2, p in nxt):
                        f["rtti_check"] += 1
                if md and md[1] in (0x0C, 0x10):
                    win = [x for x in prev(i, 8)]
                    pushes = [p for mm, p in win if mm == "push"]
                    if len(pushes) >= 3 and any(imm(p[0]) is not None and imm(p[0]) <= 0x400 for p in pushes if p):
                        f["istream_rw"] += 1
        if mn == "jmp" and JT.match(f"{mn} {', '.join(ops)}"):
            f["jump_table"] += 1
            back = prev(i, 8)
            if any(mm in ("mov", "movzx", "movsx") and len(p) > 1 and is_member(p[1]) for mm, p in back):
                jt_member += 1
            for mm, p in back:
                if mm == "cmp" and len(p) > 1 and imm(p[1]) is not None:
                    jt_sizes.append(imm(p[1]) + 1)
        if mn.startswith("j") and mn != "jmp":
            f["jcc"] += 1
        # string / constant pushes and loads
        for op in ([o0] if mn == "push" else [o1] if mn in ("mov", "lea") else []):
            v = imm(op)
            if v is None:
                continue
            kind = ctx.is_string(v)
            if kind:
                f["str_push"] += 1
                if kind == "file":
                    f["file_str"] += 1
                    near = parsed[max(0, i - 3):i] + parsed[i + 1:i + 4]
                    line = any(mm == "push" and p and imm(p[0]) is not None and 1 <= imm(p[0]) <= 0xFFFF
                               and not ctx.is_string(imm(p[0])) for mm, p in near)
                    call = any(mm == "call" for mm, p in parsed[i + 1:i + 5])
                    if line and call:
                        f["assert_site"] += 1
        # constant returns (switch / lookup returning a constant)
        if mn == "mov" and o0 == "eax" and imm(o1) is not None and i + 1 < n and parsed[i + 1][0] in ("ret", "jmp"):
            f["const_ret"] += 1
        if mn in ("cmp", "sub") and len(ops) > 1 and imm(o1) is not None and ops[0] in ("eax", "ecx", "edx", "ebx", "esi", "edi", "al", "cl", "dl", "bl"):
            f["cmp_imm"] += 1
            if imm(o1) in WM_BIG:
                f["wm_const"] += 1
        # static-initialiser evidence
        m = ABS.search(o0) if mn == "mov" else None
        if m and "PTR" in o0 and ctx.writable(int(m.group(1), 16)):
            f["glob_store"] += 1
            glob_addrs.add(int(m.group(1), 16))
        if mn == "mov" and o0 == "ecx" and imm(o1) is not None and ctx.writable(imm(o1)):
            if i + 1 < n and parsed[i + 1][0] in ("call", "push", "mov", "lea", "xor"):
                f["glob_ecx"] += 1
                glob_addrs.add(imm(o1))
        # vtable store into a member
        if mn == "mov" and "PTR [" in o0 and imm(o1) in ctx.vtables and imm(o1) is not None:
            f["vtable_store"] += 1
        # coord/cell
        if mn in ("sar", "shr", "shl", "sal") and len(ops) > 1 and imm(o1) == 8:
            f["coord_cell"] += 1
        # CDTimer reads: global load, member operand, sub, within a short window
        if mn == "sub" and len(ops) > 1:
            back = prev(i, 5)
            has_glob = any(mm == "mov" and len(p) > 1 and ABS.search(p[1]) and ctx.writable(int(ABS.search(p[1]).group(1), 16))
                           for mm, p in back + [(mn, ops)])
            has_mem = is_member(o1) or any(mm == "mov" and len(p) > 1 and is_member(p[1]) for mm, p in back)
            if has_glob and has_mem:
                f["cdtimer_read"] += 1
        # backward conditional jump with a memory-bounded compare = counted loop
        if mn.startswith("j") and mn != "jmp" and HEX.match(o0):
            t = int(o0, 16)
            if t < a:
                f["loop"] += 1
                for mm, p in prev(i, 4):
                    if mm == "cmp" and len(p) > 1 and (is_member(p[0]) or is_member(p[1])):
                        f["counted_loop"] += 1
                        break
        # DynamicVectorClass inline: member compare + jcc, then call and an increment/decrement of a member
        if mn == "cmp" and len(ops) > 1 and (is_member(o0) or is_member(o1)) and not (imm(o1) is not None):
            ahead = parsed[i + 1:i + 16]
            if ahead and ahead[0][0].startswith("j"):
                has_call = any(mm == "call" for mm, p in ahead)
                inc = any((mm == "inc" and p and is_member(p[0])) or
                          (mm == "add" and len(p) > 1 and is_member(p[0]) and imm(p[1]) == 1) for mm, p in ahead)
                dec = any((mm == "dec" and p and is_member(p[0])) or
                          (mm == "sub" and len(p) > 1 and is_member(p[0]) and imm(p[1]) == 1) for mm, p in ahead)
                if has_call and inc:
                    f["vec_add"] += 1
                elif dec:
                    f["vec_remove"] += 1

    tset = Counter(targets)
    eng = [t for t in tset if ctx.engine(t)]
    f["call_direct"] = len(targets)
    f["callee_distinct"] = len(eng)
    f["callee_matched"] = sum(1 for t in eng if ctx.status.get(t) == "matched")
    f["callee_partial"] = sum(1 for t in eng if ctx.status.get(t) == "partial")
    f["callee_unmatched"] = f["callee_distinct"] - f["callee_matched"] - f["callee_partial"]
    f["ini_calls"] = sum(c for t, c in tset.items() if t in ctx.ini)
    f["swizzle_calls"] = sum(c for t, c in tset.items() if t in ctx.swizzle)
    f["win_imports"] = sum(c for nme, c in imports.items() if nme.startswith(WIN_IMPORTS))
    f["win_default"] = sum(c for nme, c in imports.items() if nme.startswith(WIN_DEFAULT))
    f["import_calls"] = sum(imports.values())
    f["jump_table_member"] = jt_member
    f["jump_table_max_cases"] = max(jt_sizes) if jt_sizes else 0
    f["glob_addrs"] = len(glob_addrs)
    f["n_insns"] = n
    f["bytes"] = length if length is not None else (insns[-1][0] + insns[-1][1] - insns[0][0] if insns else 0)
    return f


# ---- classification ---------------------------------------------------------

def class_scores(f, xcu=False):
    n = max(1, f["n_insns"])
    s = {c: 0.0 for c in PRIORITY}
    ev = f["glob_store"] + f["glob_ecx"]
    if xcu:
        s["static-initialiser"] = 1.0
    elif ev >= 8 and f["glob_addrs"] >= 6 and f["jcc"] <= n * 0.05 and not f["assert_site"]:
        s["static-initialiser"] = min(1.0, ev / (n * 0.25))
    calls = max(1, f["call_direct"])
    if f["ini_calls"] >= 5:
        s["ini-reader"] = min(1.0, f["ini_calls"] / 8) * min(1.0, 2 * f["ini_calls"] / calls)
    pers = f["istream_rw"] + f["swizzle_calls"]
    if pers >= 2:
        s["persist"] = min(1.0, pers / 6)
    if f["win_default"] and f["wm_const"] >= 2:
        s["window-proc"] = min(1.0, 0.5 + f["wm_const"] / 8)
    elif f["win_imports"] and f["wm_const"] >= 5:
        s["window-proc"] = min(1.0, 0.3 + f["wm_const"] / 8)
    if f["vtable_store"]:
        s["ctor-dtor"] = min(1.0, 0.6 + 0.1 * f["vtable_store"])
    lk = f["const_ret"]
    if lk >= 6 or (f["jump_table"] and lk >= 3):
        s["string-lookup"] = min(1.0, lk / 10) * (1.0 if f["call_direct"] < n * 0.1 else 0.6)
    elif f["cmp_imm"] >= 20 and f["call_direct"] < n * 0.05 and lk >= 3:
        s["string-lookup"] = 0.4
    if f["jump_table_member"]:
        s["state-machine"] = 0.7 if f["jump_table_max_cases"] >= 3 else 0.4
    ratio = f["x87"] / n
    if ratio >= 0.07:
        s["math"] = min(1.0, ratio / 0.2)
    s["generic"] = 0.1
    return s


def classify(f, xcu=False):
    s = class_scores(f, xcu)
    best = max(PRIORITY, key=lambda c: (s[c] >= THRESHOLD, s[c], -PRIORITY.index(c)))
    primary = best if s[best] >= THRESHOLD else "generic"
    others = [c for c in PRIORITY if c != primary and c != "generic" and s[c] >= THRESHOLD]
    return primary, others, s


def callee_ratio(f):
    return f["callee_matched"] / f["callee_distinct"] if f["callee_distinct"] else 0.0


def gen_score(primary, f):
    base = BASE[primary]
    size_pen = 1 - min(0.25, max(0, f["bytes"] - MIN_LEN) / 40000)
    return round(base * (0.4 + 0.6 * callee_ratio(f)) * size_pen)


IDIOMS = ("assert_site", "vec_add", "vec_remove", "counted_loop", "rtti_check", "cdtimer_read", "coord_cell",
          "str_push", "jump_table", "ini_calls", "swizzle_calls", "istream_rw", "vtable_store", "wm_const",
          "glob_store", "glob_ecx", "const_ret")


def record(addr, length, insns, ctx, xcu=False, rtti=None):
    f = features(insns, ctx, length)
    primary, others, scores = classify(f, xcu)
    n = max(1, f["n_insns"])
    rec = {
        "addr": f"0x{addr:X}", "len": length, "primary": primary, "also": others,
        "idioms": {k: f[k] for k in IDIOMS if f[k]},
        "x87_ratio": round(f["x87"] / n, 3), "n_insns": f["n_insns"],
        "callees": {"distinct": f["callee_distinct"], "matched": f["callee_matched"],
                    "partial": f["callee_partial"], "unmatched": f["callee_unmatched"]},
        "matched_callee_ratio": round(callee_ratio(f), 3),
        "gen_score": gen_score(primary, f),
    }
    if xcu:
        rec["xcu"] = True
    if rtti:
        rec["rtti"] = rtti
    return rec


# ---- binary-dependent part --------------------------------------------------

def _disasm(job):
    addr, blob = job
    from extent_census import objdump
    insns = objdump(blob, addr)
    return addr, [(a, s, t) for a, (s, t) in sorted(insns.items())]


def load_inputs():
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from verify_vtable import load_pe
    ext = json.loads((DATA / "function_extents.json").read_text())
    binary = os.environ.get("GAMEMD_BINARY")
    if not binary:
        sys.exit("GAMEMD_BINARY is not set")
    data, _, sections = load_pe(binary, ext["binary_sha256"])
    return ext, data, sections


def va_reader(data, sections):
    def read(va, n):
        for _, start, vsize, rawptr, rawsize in sections:
            if start <= va and va + n <= start + min(vsize, rawsize):
                return data[rawptr + va - start: rawptr + va - start + n]
        return None
    return read


def string_kind(read):
    def kind(va):
        b = read(va, 64)
        if b is None:
            b = read(va, 8)
            if b is None:
                return None
        end = b.find(b"\0")
        if end < 3:
            return None
        s = b[:end]
        if not all(32 <= c < 127 or c in (9, 10, 13) for c in s):
            return None
        low = s.lower()
        if low.endswith((b".cpp", b".h", b".c", b".hpp")):
            return "file"
        return "str"
    return kind


def text_pointer_runs(data, sections, entries, vtables, minrun=100):
    """Entry VAs in a very long run of consecutive function pointers outside any vtable.

    In the pinned image this is the single .CRT$XCU initialiser table (about 3900 entries, mostly tiny
    thunks); vtable fragments and short dispatch tables are far shorter."""
    listed = set()
    es = set(entries)
    for name, start, vsize, rawptr, rawsize in sections:
        if name != ".data":      # the initialiser table lives in .data; .rdata holds adjacent vtables
            continue
        size = min(vsize, rawsize)
        blob = data[rawptr:rawptr + size]
        vals = struct.unpack_from(f"<{size // 4}I", blob, 0)
        i = 0
        while i < len(vals):
            j = i
            while j < len(vals) and vals[j] in es:
                j += 1
            if j - i >= minrun and (start + 4 * i) not in vtables:
                listed.update(vals[i:j])
            i = max(j, i + 1)
    return listed


def rtti_owners(read, text_lo, text_hi):
    from collections import defaultdict
    owners = defaultdict(list)
    vts = set()
    classes = json.loads((DATA / "rtti_classes.json").read_text())["classes"]
    for c in classes.values():
        for loc in c["locators"]:
            vt = loc.get("vtable_va")
            if not vt:
                continue
            vt = int(vt, 16)
            vts.add(vt)
            for slot in range(512):
                raw = read(vt + 4 * slot, 4)
                if raw is None:
                    break
                tgt = struct.unpack("<I", raw)[0]
                if not text_lo <= tgt < text_hi:
                    break
                if c["demangled_name"] not in owners[tgt]:
                    owners[tgt].append(c["demangled_name"])
    return owners, vts


def build(jobs):
    ext, data, sections = load_inputs()
    read = va_reader(data, sections)
    text = next(s for s in sections if s[0] == ".text")
    tlo, thi = text[1], text[1] + text[2]
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import tail_layout
    manifest = json.loads((DATA / "match_manifest.json").read_text())
    rows = {}
    for r in manifest:
        a = int(r["addr"], 16)
        if a not in rows or r["status"] == "matched":
            rows[a] = r
    status = {a: r["status"] for a, r in rows.items()}
    swizzle = {a for a, r in rows.items() if "Swizzle" in (r.get("name") or "") + r["sym"]}
    ini_extra = {a for a, r in rows.items() if re.match(r"(CC)?INIClass::Read", r.get("name") or "")}
    entries = [(int(a, 16), int(n, 16), k) for a, n, _, _, k, _ in ext["entries"]]
    engine = [(a, n) for a, n, k in entries if k == "engine"]
    eng_set = {a for a, _ in engine}
    owners, vts = rtti_owners(read, tlo, thi)
    vtable_starts = set(vts)
    writable = [(s[1], s[1] + s[2]) for s in sections if s[0] in (".data",) or s[0].startswith(".bss")]
    if not writable:
        writable = [(s[1], s[1] + s[2]) for s in sections if s[0] != ".text" and s[0] != ".rdata"]
    wsec = lambda va: any(lo <= va < hi for lo, hi in writable)
    imports = {va: nm for va, (_, nm) in tail_layout.import_slots(data, 0x400000, sections).items()}
    ctx = Ctx(is_string=string_kind(read), imports=imports, status=status, vtables=vts, writable=wsec,
              engine=lambda va: va in eng_set, swizzle=swizzle, ini_extra=ini_extra)
    listed = text_pointer_runs(data, sections, eng_set, vtable_starts)
    # tiny thunks that are listed and call a target
    tiny_calls = {}
    for a, n in engine:
        if n <= 0x20 and a in listed:
            blob = read(a, n)
            for k in range(0, n - 4):
                if blob[k] == 0xE8:
                    t = (a + k + 5 + struct.unpack_from("<i", blob, k + 1)[0]) & 0xFFFFFFFF
                    tiny_calls.setdefault(t, a)
    cands = [(a, n) for a, n in engine if n >= MIN_LEN and a not in rows]
    work = [(a, read(a, n)) for a, n in cands]
    with Pool(jobs) as pool:
        dis = dict(pool.imap_unordered(_disasm, work, chunksize=8))
    out = []
    for a, n in cands:
        insns = dis.get(a) or []
        if not insns:
            continue
        xcu = a in listed or a in tiny_calls
        out.append(record(a, n, insns, ctx, xcu, owners.get(a, [None])[0]))
    out.sort(key=lambda r: int(r["addr"], 16))
    return out, len(listed)


def summarise(recs):
    by = {}
    for r in recs:
        c = by.setdefault(r["primary"], {"count": 0, "bytes": 0})
        c["count"] += 1
        c["bytes"] += r["len"]
    for c in by.values():
        c["kb"] = round(c["bytes"] / 1024, 1)
    return dict(sorted(by.items(), key=lambda kv: -kv[1]["bytes"]))


def idiom_totals(recs):
    t = Counter()
    for r in recs:
        for k, v in r["idioms"].items():
            t[k] += v
    return dict(t)


def worklist_tsv(recs):
    rows = ["addr\tlen\tclass\ttop_idioms\trtti_class\tmatched_callee_ratio\tgen_score"]
    for r in sorted(recs, key=lambda r: (-r["gen_score"], -r["len"], r["addr"])):
        top = sorted(r["idioms"].items(), key=lambda kv: -kv[1])[:3]
        rows.append("\t".join([r["addr"], str(r["len"]), r["primary"],
                               ",".join(f"{k}={v}" for k, v in top) or "-",
                               r.get("rtti") or "-", f"{r['matched_callee_ratio']:.2f}", str(r["gen_score"])]))
    return "\n".join(rows) + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=str(DATA / "large_function_shapes.json"))
    ap.add_argument("--wl", default=str(DEFAULT_WL))
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 1)
    args = ap.parse_args()
    recs, nlisted = build(args.jobs)
    doc = {
        "schema": "gagarin/large_function_shapes/1",
        "generated_by": "scripts/vc6/shape_classify.py",
        "note": f"engine functions >= {MIN_LEN} bytes with no manifest row; addresses, lengths, class tags and "
                "idiom counts only. Detectors are heuristics over objdump output.",
        "functions": len(recs), "initialiser_table_entries": nlisted,
        "totals_by_class": summarise(recs), "idiom_totals": idiom_totals(recs), "entries": recs,
    }
    Path(args.out).write_text(json.dumps(doc, indent=1) + "\n")
    wl = Path(args.wl)
    wl.parent.mkdir(parents=True, exist_ok=True)
    wl.write_text(worklist_tsv(recs))
    print(f"{len(recs)} functions")
    for c, v in doc["totals_by_class"].items():
        print(f"  {c:20s} {v['count']:4d}  {v['kb']:8.1f} KB")
    print("top 30 by generation score:")
    for r in sorted(recs, key=lambda r: (-r["gen_score"], -r["len"], r["addr"]))[:30]:
        print(f"  {r['addr']} len {r['len']:5d} {r['primary']:19s} score {r['gen_score']:3d} "
              f"ratio {r['matched_callee_ratio']:.2f} {r.get('rtti') or ''}")


if __name__ == "__main__":
    main()
