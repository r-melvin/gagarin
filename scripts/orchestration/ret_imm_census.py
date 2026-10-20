#!/usr/bin/env python3
# SPDX-Provenance: own-binary-via-Ghidra
#
# ret-imm census — calling convention as a lookup, not a judgement call.
#
# `RET n` is callee stack cleanup, so the immediate is ground truth for how many
# argument bytes the callee removed.  Whether ECX / EDX are *read before being
# written* says whether they carried a receiver and a register argument.  Those
# three facts together pin the convention before a line of C++ is written.
#
# Ground truth sources (both are the user's own retail gamemd.exe v1.001,
# sha256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c):
#   * function entry points + sizes  -> `ghidra function list --limit 20000`
#   * instruction stream             -> `objdump -d -M intel` over .text
# objdump is used for the stream because this is a whole-image pass (1.4M
# instructions); it reads the same bytes of the same file the Ghidra CLI does.
#
# Usage:  ret_imm_census.py <gamemd.exe> <ghidra-funcs.json> <out.json>
#                          [--unlisted scripts/data/unlisted_entry_points.json]

import json
import re
import subprocess
import sys
from collections import deque

TEXT_START = 0x401000
TEXT_END = 0x7E038D

# ---------------------------------------------------------------- disassembly

LINE_RE = re.compile(r"^\s*([0-9a-f]+):\t([0-9a-f ]+)\t(\S+)\s*(.*)$")


def disassemble(binary):
    """addr -> (length, mnemonic, operand-string). One linear objdump pass."""
    out = subprocess.run(
        ["objdump", "-d", "-M", "intel",
         "--start-address=0x%x" % TEXT_START,
         "--stop-address=0x%x" % TEXT_END, binary],
        capture_output=True, text=True, check=True).stdout
    # objdump wraps a long instruction's bytes onto an unlabelled continuation
    # line, so the byte count on the first line is NOT the instruction length.
    # Take the length from the next decoded address instead.
    seq = []
    for line in out.split("\n"):
        m = LINE_RE.match(line)
        if not m:
            continue
        addr = int(m.group(1), 16)
        mnem = m.group(3)
        ops = m.group(4).split("#")[0].split("<")[0].strip()
        seq.append((addr, mnem, ops))
    insns = {}
    for i, (addr, mnem, ops) in enumerate(seq):
        nxt = seq[i + 1][0] if i + 1 < len(seq) else addr + 1
        insns[addr] = (nxt - addr, mnem, ops)
    return insns


# ------------------------------------------------------- register read/write
#
# Operand classification is mnemonic-driven.  Any register inside a memory
# operand `[...]` is a READ (it is a base or index).  For a bare register
# operand, whether it is read, written or both depends on mnemonic and position.

REG32 = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"}
ALIAS = {}
for _full, _parts in (("ecx", ("ecx", "cx", "cl", "ch")),
                      ("edx", ("edx", "dx", "dl", "dh")),
                      ("eax", ("eax", "ax", "al", "ah")),
                      ("ebx", ("ebx", "bx", "bl", "bh")),
                      ("esi", ("esi", "si")), ("edi", ("edi", "di")),
                      ("esp", ("esp", "sp")), ("ebp", ("ebp", "bp"))):
    for _p in _parts:
        ALIAS[_p] = _full

_CC = ("o", "no", "b", "nb", "ae", "e", "z", "ne", "nz", "be", "a", "nbe",
       "s", "ns", "p", "np", "l", "ge", "nl", "le", "g", "nle", "c", "nc",
       "na", "nae", "ng", "nge", "nl", "nle", "pe", "po")

# op0 is written and NOT read (pure definition)
WRITE_ONLY_DST = {"mov", "movzx", "movsx", "lea", "pop", "movd", "movq"}
WRITE_ONLY_DST |= {"set" + c for c in _CC}

# op0 is read AND written (read-modify-write)
RMW_DST = {
    "add", "sub", "adc", "sbb", "and", "or", "xor", "inc", "dec", "neg",
    "not", "shl", "shr", "sar", "sal", "rol", "ror", "rcl", "rcr", "xadd",
    "xchg", "btc", "btr", "bts", "shld", "shrd", "bswap", "imul",
}
RMW_DST |= {"cmov" + c for c in _CC}

# every operand is a read
READ_ONLY = {
    "cmp", "test", "push", "jmp", "call", "ret", "retf", "bt", "ucomiss",
    "comiss", "int", "int3", "nop", "leave", "hlt", "cld", "std", "fld",
    "fild", "fadd", "fsub", "fmul", "fdiv", "fcom", "fcomp", "fstp", "fst",
    "fistp", "fist", "fldcw", "fnstcw", "fsubr", "fdivr", "fiadd", "fimul",
    "fisub", "fidiv", "fcompp", "fnstsw", "sahf", "wait", "fwait",
}

BRANCH = {"jmp"} | {"j" + c for c in _CC} | {"jcxz", "jecxz", "loop",
                                             "loope", "loopne", "loopnz",
                                             "loopz"}
COND_BRANCH = BRANCH - {"jmp"}
TERMINAL = {"ret", "retf", "iret", "ud2", "hlt"}

HEXNUM = re.compile(r"^0x[0-9a-f]+$")
REGTOK = re.compile(r"\b([a-z]{2,3})\b")


def split_ops(ops):
    """Split an intel operand string on top-level commas."""
    parts, depth, cur = [], 0, ""
    for ch in ops:
        if ch == "[":
            depth += 1
        elif ch == "]":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        parts.append(cur.strip())
    return parts


def regs_in(tok):
    return {ALIAS[r] for r in REGTOK.findall(tok) if r in ALIAS}


def rw_sets(mnem, ops):
    """Return (reads, writes) as sets of canonical 32-bit register names."""
    reads, writes = set(), set()
    parts = split_ops(ops)

    # implicit-register instructions
    if mnem in ("mul", "imul", "div", "idiv") and len(parts) <= 1:
        reads |= {"eax", "edx"} if mnem in ("div", "idiv") else {"eax"}
        writes |= {"eax", "edx"}
        if parts:
            reads |= regs_in(parts[0])
        return reads, writes
    if mnem in ("cdq", "cwd"):
        return {"eax"}, {"edx"}
    if mnem in ("cwde", "cbw"):
        return {"eax"}, {"eax"}
    if mnem.startswith("rep") or mnem.rstrip("bwdl") in (
            "movs", "stos", "lods", "scas", "cmps"):
        return {"ecx", "esi", "edi", "eax"}, {"ecx", "esi", "edi"}
    if mnem in ("loop", "loope", "loopne", "loopz", "loopnz"):
        return {"ecx"}, {"ecx"}
    if mnem in ("jecxz", "jcxz"):
        return {"ecx"}, set()
    if mnem in ("pushad", "pusha"):
        return set(REG32), set()
    if mnem in ("popad", "popa"):
        return set(), set(REG32)
    if mnem == "leave":
        return {"ebp"}, {"esp", "ebp"}
    if mnem in ("ret", "retf"):
        return {"esp"}, {"esp"}

    # Definition idioms: cl materialises a constant with an arithmetic op whose
    # previous value is irrelevant. These are pure definitions, not reads.
    #   xor r,r   sub r,r   ->  0        or r,0xffffffff -> -1     and r,0 -> 0
    if len(parts) == 2 and "[" not in parts[0] and regs_in(parts[0]):
        if mnem in ("xor", "sub") and parts[0] == parts[1]:
            return set(), regs_in(parts[0])
        if mnem == "or" and parts[1] in ("0xffffffff", "0xffff", "0xff", "-1"):
            return set(), regs_in(parts[0])
        if mnem == "and" and parts[1] == "0x0":
            return set(), regs_in(parts[0])

    for i, p in enumerate(parts):
        rs = regs_in(p)
        if "[" in p:
            reads |= rs          # base/index registers are always read
            continue
        if not rs:
            continue
        if i == 0:
            if mnem in WRITE_ONLY_DST:
                writes |= rs
            elif mnem in RMW_DST:
                reads |= rs
                writes |= rs
            elif mnem in READ_ONLY or mnem in BRANCH:
                reads |= rs
            else:
                # unclassified mnemonic: conservative both ways
                reads |= rs
                writes |= rs
        else:
            reads |= rs
            if mnem == "xchg":
                writes |= rs
    return reads, writes


# ------------------------------------------------------------- body walk

def branch_target(ops):
    ops = ops.strip()
    if HEXNUM.match(ops):
        return int(ops, 16)
    return None


def data_sections(binary):
    """Raw bytes + virtual address of each initialised data section, parsed
    straight out of the PE section table."""
    blob = open(binary, "rb").read()
    import struct
    e_lfanew = struct.unpack_from("<I", blob, 0x3C)[0]
    nsec = struct.unpack_from("<H", blob, e_lfanew + 6)[0]
    opt_size = struct.unpack_from("<H", blob, e_lfanew + 20)[0]
    image_base = struct.unpack_from("<I", blob, e_lfanew + 24 + 28)[0]
    sec0 = e_lfanew + 24 + opt_size
    out = []
    for i in range(nsec):
        off = sec0 + i * 40
        name = blob[off:off + 8].rstrip(b"\0").decode("latin1")
        vaddr = struct.unpack_from("<I", blob, off + 12)[0]
        rsize = struct.unpack_from("<I", blob, off + 16)[0]
        rptr = struct.unpack_from("<I", blob, off + 20)[0]
        if name in (".rdata", ".data"):
            out.append((image_base + vaddr, blob[rptr:rptr + rsize]))
    return out


def inside_listed(addr, starts, ivs):
    """True if addr falls strictly inside an already-listed function body."""
    import bisect
    i = bisect.bisect_right(starts, addr) - 1
    return i >= 0 and starts[i] < addr < ivs[i][1]


def looks_like_entry(insns, addr, prev_end):
    """An address is entry-plausible if it decodes and the byte before it is
    alignment padding or the tail of a previous function."""
    if addr not in insns:
        return False
    prev = prev_end.get(addr)
    if prev is None:
        return True                       # nothing decodes into it: clean start
    return prev[1] in ("ret", "retf", "jmp", "nop", "int3", "leave")


def prologue_run(insns, entry):
    """Addresses of the leading prologue run — register saves, frame set-up and
    stack allocation — where a `push ecx` is an allocation, not an argument."""
    out = set()
    addr = entry
    while addr in insns:
        nbytes, mnem, ops = insns[addr]
        if mnem == "push" and "[" not in ops:
            pass
        elif mnem == "mov" and ops.replace(" ", "") == "ebp,esp":
            pass
        elif mnem == "sub" and ops.startswith("esp,"):
            pass
        else:
            break
        out.add(addr)
        addr += nbytes
    return out


class FuncFacts(object):
    __slots__ = ("ret_imms", "has_ret", "tail_jumps", "indirect_tail",
                 "body_end", "insn_count", "reads_ecx", "reads_edx",
                 "truncated", "has_seh")

    def __init__(self):
        self.ret_imms = set()
        self.has_ret = False
        self.tail_jumps = set()
        self.indirect_tail = False
        self.body_end = 0
        self.insn_count = 0
        self.reads_ecx = False
        self.reads_edx = False
        self.truncated = False
        self.has_seh = False


def walk(insns, entry, limit, entries):
    """CFG walk from `entry`.  The walk state carries which of ECX/EDX are
    already defined on the current path, so a read counts as a parameter read
    only where it is reachable before any write on that same path."""
    f = FuncFacts()
    seen = {}                      # addr -> bitmask of visited states
    work = deque([(entry, 0)])     # state: bit0 = ecx defined, bit1 = edx defined
    prologue = prologue_run(insns, entry)
    while work:
        addr, st = work.popleft()
        while True:
            if addr not in insns:
                f.truncated = True
                break
            if seen.get(addr, 0) & (1 << st):
                break
            seen[addr] = seen.get(addr, 0) | (1 << st)
            nbytes, mnem, ops = insns[addr]
            f.insn_count += 1
            if addr + nbytes > f.body_end:
                f.body_end = addr + nbytes

            if mnem == "push" and "fs:0x0" in ops.replace(" ", ""):
                f.has_seh = True
            reads, writes = rw_sets(mnem, ops)
            if addr in prologue and mnem == "push" and ops in ("ecx", "edx"):
                # cl allocates 4 bytes of frame with `push ecx` / `push edx`;
                # the register's value is dead. Only a push immediately feeding
                # a CALL is a real argument read.
                nb2 = insns[addr][0]
                if insns.get(addr + nb2, (0, "", ""))[1] != "call":
                    reads = set()
            if "ecx" in reads and not (st & 1):
                f.reads_ecx = True
            if "edx" in reads and not (st & 2):
                f.reads_edx = True
            if mnem == "call":
                st |= 3            # ECX/EDX volatile across a call
            else:
                if "ecx" in writes:
                    st |= 1
                if "edx" in writes:
                    st |= 2

            if mnem in TERMINAL:
                if mnem in ("ret", "retf"):
                    f.has_ret = True
                    t = ops.strip()
                    f.ret_imms.add(int(t, 16) if t else 0)
                break

            nxt = addr + nbytes
            if mnem in COND_BRANCH:
                t = branch_target(ops)
                if t is not None:
                    if limit is None or (entry <= t < limit):
                        work.append((t, st))
                    else:
                        f.tail_jumps.add(t)
                addr = nxt
                continue
            if mnem == "jmp":
                t = branch_target(ops)
                if t is None:
                    f.indirect_tail = True
                    break
                if limit is None:
                    if t in entries and t != entry:
                        f.tail_jumps.add(t)
                        break
                    if t < entry:
                        f.tail_jumps.add(t)
                        break
                    addr = t
                    continue
                if entry <= t < limit:
                    addr = t
                    continue
                f.tail_jumps.add(t)
                break
            addr = nxt
    return f


# ------------------------------------------------------------- inference

def infer(f):
    """Map the three facts onto a convention plus a confidence."""
    if not f.has_ret:
        if f.tail_jumps or f.indirect_tail:
            return "tail-jump", "excluded", \
                "terminates in JMP, not RET; the convention belongs to the jump target"
        return "no-ret", "excluded", \
            "no RET reached (noreturn, or a function-boundary error)"

    if len(f.ret_imms) > 1:
        return "conflicting-ret", "excluded", \
            ("returns disagree on the immediate (%s): a misidentified boundary, "
             "or a case worth reading by hand"
             % ", ".join(str(i) for i in sorted(f.ret_imms)))

    n = next(iter(f.ret_imms))
    ecx, edx = f.reads_ecx, f.reads_edx

    if ecx and not edx:
        return "__thiscall", "high", \
            "ECX read before write, EDX not; RET %d = %d stack argument bytes" % (n, n)
    if ecx and edx:
        return "__fastcall", "high", \
            ("ECX and EDX both read before write; RET %d counts only the remaining "
             "stack arguments. Free __fastcall and __fastcall member are "
             "indistinguishable here." % n)
    if n:
        return "__stdcall", "high", \
            "no register parameters; RET %d = %d stack argument bytes" % (n, n)
    return "__cdecl", "ambiguous", \
        ("bare RET with no register parameters: __cdecl, or a __stdcall / "
         "__thiscall with no stack arguments and no receiver use")


# ------------------------------------------------------------------- main

def main():
    binary, funcs_path, out_path = sys.argv[1], sys.argv[2], sys.argv[3]
    unlisted_path = None
    if "--unlisted" in sys.argv:
        unlisted_path = sys.argv[sys.argv.index("--unlisted") + 1]

    sys.stderr.write("disassembling ...\n")
    insns = disassemble(binary)
    sys.stderr.write("  %d instructions\n" % len(insns))

    listed = json.load(open(funcs_path))
    ranges = {}
    for fn in listed:
        a = int(fn["entry_point"], 16)
        ranges[a] = (a + int(fn["size"]), "ghidra-function-list", fn.get("name"))

    sweep = {}
    if unlisted_path:
        for s in json.load(open(unlisted_path)):
            a = int(s, 16)
            if a not in ranges:
                sweep[a] = "sweep-unlisted-entry-points"

    # additional sweep: direct CALL targets inside .text that nobody listed
    for addr, (_, mnem, ops) in insns.items():
        if mnem != "call":
            continue
        t = branch_target(ops)
        if t is None or not (TEXT_START <= t < TEXT_END):
            continue
        if t not in ranges and t not in sweep:
            sweep[t] = "sweep-call-target"

    # third sweep: code addresses stored in .rdata/.data — vtable slots and
    # comparator / callback pointers are never direct CALL targets.
    prev_end = {}
    for a, (n, m, o) in insns.items():
        prev_end[a + n] = (a, m)
    ivs = sorted((a, lim) for a, (lim, _, _) in ranges.items())
    starts = [a for a, _ in ivs]
    import struct
    for base, blob in data_sections(binary):
        for off in range(0, len(blob) - 3, 4):
            t = struct.unpack_from("<I", blob, off)[0]
            if not (TEXT_START <= t < TEXT_END):
                continue
            if t in ranges or t in sweep:
                continue
            if inside_listed(t, starts, ivs):
                continue        # a mid-function label, not an entry point
            # cl aligns function entries to 16 bytes; requiring that as well as
            # a padding/terminator predecessor keeps stray integers that happen
            # to land in .text out of the census.
            if t % 16 == 0 and looks_like_entry(insns, t, prev_end):
                sweep[t] = "sweep-data-reference"

    # fourth sweep: 16-byte-aligned addresses that begin immediately after
    # alignment padding. cl pads between functions and never inside one, so a
    # padded, aligned boundary is an entry point even when nothing references it
    # directly (constructors reached only through inlined or indirect callers).
    for addr in sorted(insns):
        if addr % 16 or addr in ranges or addr in sweep:
            continue
        prev = prev_end.get(addr)
        if prev is None or prev[1] not in ("nop", "int3"):
            continue
        if inside_listed(addr, starts, ivs):
            continue
        sweep[addr] = "sweep-aligned-after-padding"

    entries = set(ranges) | set(sweep)
    sys.stderr.write("  %d listed + %d swept entry points\n"
                     % (len(ranges), len(sweep)))

    records = []
    for addr in sorted(entries):
        if addr in ranges:
            limit, src, name = ranges[addr]
        else:
            limit, src, name = None, sweep[addr], None
        f = walk(insns, addr, limit, entries)
        conv, conf, why = infer(f)
        rec = {
            "addr": "0x%X" % addr,
            "ret_imm": (sorted(f.ret_imms)[0] if len(f.ret_imms) == 1
                        else (sorted(f.ret_imms) if f.ret_imms else None)),
            "ret_imms": sorted(f.ret_imms),
            "conflicting_returns": len(f.ret_imms) > 1,
            "reads_ecx_before_write": f.reads_ecx,
            "reads_edx_before_write": f.reads_edx,
            "inferred": conv,
            "confidence": conf,
            "entry_source": src,
            "entry_point_is_lead": src != "ghidra-function-list",
            "insn_count": f.insn_count,
        }
        if f.has_seh:
            rec["seh_frame"] = True
        if f.tail_jumps:
            rec["tail_jump_targets"] = ["0x%X" % t for t in sorted(f.tail_jumps)]
        if f.indirect_tail:
            rec["indirect_tail_jump"] = True
        if f.truncated:
            rec["truncated_stream"] = True
        if name:
            rec["ghidra_name"] = name
        records.append(rec)

    raw_ret_imm = sum(1 for _, m, o in insns.values()
                      if m == "ret" and o.strip())
    raw_ret = sum(1 for _, m, o in insns.values() if m == "ret")

    dist = {}
    for r in records:
        dist[r["inferred"]] = dist.get(r["inferred"], 0) + 1

    header = {
        "schema": "gagarin/ret_imm_census/1",
        "target": "GAMEMD gamemd.exe v1.001",
        "sha256": "1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c",
        "provenance": "own-binary-via-Ghidra (entry points) + objdump -d -M intel "
                      "(instruction stream, same file)",
        "generated_by": "scripts/orchestration/ret_imm_census.py",
        "status": "leads — every record is read straight off the instruction stream; "
                  "confirm against the disassembly before it enters a header",
        "what_this_is": (
            "RET n is callee stack cleanup, so the immediate is ground truth for how "
            "many argument bytes the callee removed. Whether ECX/EDX are read before "
            "being written says whether they carried a receiver and a register "
            "argument. Together they pin the calling convention before a line of C++ "
            "is written."),
        "inference_rules": [
            "ECX read before write, EDX not, RET n -> __thiscall; n = stack argument bytes.",
            "ECX and EDX both read before write, RET n -> __fastcall; n counts only the "
            "REMAINING arguments. This may be a free __fastcall or a __fastcall member; "
            "the census cannot distinguish those and does not pretend to.",
            "neither read before write, RET n -> __stdcall; n = stack argument bytes.",
            "neither read before write, bare RET -> __cdecl, OR a __stdcall/__thiscall "
            "with no stack arguments. AMBIGUOUS, marked confidence=ambiguous.",
        ],
        "excluded_kinds": {
            "tail-jump": "terminates in JMP, not RET; the convention belongs to the "
                         "jump target (follow tail_jump_targets)",
            "no-ret": "no RET reached: noreturn, or a function-boundary error",
            "conflicting-ret": "several RETs disagree on the immediate; read by hand",
        },
        "caveats": [
            "A RET inside a __try region, or after a stack-cleanup thunk, can mislead; "
            "such functions are not separately flagged here.",
            "reads_ecx/edx_before_write is computed over the CFG from the entry point, "
            "with ECX and EDX treated as clobbered by any CALL.",
            "__fastcall vs __thiscall is decided by EDX, not by argument count. See "
            "docs/matching_methodology_and_toolchain.md batch fifty.",
            "A __thiscall verdict says ECX carried a receiver-shaped value; it does not "
            "prove the function is a non-static member (it may be a static __fastcall "
            "member or a free __fastcall whose second parameter is unused).",
        ],
        "field_notes": {
            "ret_imm": "the single distinct terminating RET immediate, or the LIST "
                       "of distinct immediates when the returns disagree "
                       "(conflicting_returns=true). 0 means a bare RET.",
            "ret_imms": "every distinct terminating RET immediate reached from the entry.",
            "confidence": "high | ambiguous (bare RET, convention underdetermined) | "
                          "excluded (not a data point: see excluded_kinds).",
            "entry_point_is_lead": "true when the entry point itself came from a sweep "
                                   "rather than Ghidra's function list, so the boundary "
                                   "is unconfirmed even where the convention reads cleanly.",
            "seh_frame": "the prologue installs an SEH handler; a RET inside a __try "
                         "region can mislead, so read this one by hand.",
        },
        "counts": {
            "entry_points": len(records),
            "ret_instruction_sites_in_text": raw_ret,
            "ret_imm_instruction_sites_in_text": raw_ret_imm,
            "ret_imm_sites": sum(len(r["ret_imms"]) for r in records),
            "nonzero_ret_imm_sites": sum(1 for r in records
                                         for i in r["ret_imms"] if i),
            "by_inferred": dict(sorted(dist.items(), key=lambda kv: -kv[1])),
        },
    }

    with open(out_path, "w") as fh:
        json.dump({"header": header, "functions": records}, fh, indent=1)
    sys.stderr.write(json.dumps(header["counts"], indent=1) + "\n")


if __name__ == "__main__":
    main()
