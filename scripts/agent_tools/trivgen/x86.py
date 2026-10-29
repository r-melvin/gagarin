#!/usr/bin/env python3
# Provenance: original. Instruction normaliser over objdump's Intel output, used by trivgen.
"""Small structured view of objdump -M intel text for the retail image.

Insn: addr, size, mn, ops (list of Op), text.  Op: kind in {reg, imm, mem}.
mem fields: size (1/2/4/8/None), seg, base, index, scale, disp (signed int).
Only what trivgen's patterns need; anything unparsed leaves ops == None.
"""
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
import common  # noqa: E402

REG32 = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"}
REG16 = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"}
REG8 = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"}
SIZES = {"BYTE": 1, "WORD": 2, "DWORD": 4, "QWORD": 8, "TBYTE": 10}


@dataclass
class Op:
    kind: str                 # reg | imm | mem
    reg: str = None
    val: int = None           # imm value (unsigned 32 as printed)
    size: int = None
    seg: str = None
    base: str = None
    index: str = None
    scale: int = 1
    disp: int = 0

    @property
    def regsize(self):
        if self.kind != "reg":
            return None
        return 4 if self.reg in REG32 else 2 if self.reg in REG16 else 1

    def absolute(self):
        return self.kind == "mem" and self.base is None and self.index is None


@dataclass
class Insn:
    addr: int
    size: int
    mn: str
    ops: list
    text: str
    raw: str = ""


MEM = re.compile(r"^(?:(BYTE|WORD|DWORD|QWORD|TBYTE) PTR )?(?:([a-z]s):)?\[?([^\]]*)\]?$")


def parse_op(s):
    s = s.strip()
    if s in REG32 | REG16 | REG8:
        return Op("reg", reg=s)
    if re.fullmatch(r"0x[0-9a-f]+", s):
        return Op("imm", val=int(s, 16))
    if re.fullmatch(r"-?\d+", s):
        return Op("imm", val=int(s) & 0xFFFFFFFF)
    m = re.match(r"^(?:(BYTE|WORD|DWORD|QWORD|TBYTE) PTR )?(?:([a-z]s):)?(.*)$", s)
    if not m:
        return None
    size = SIZES.get(m.group(1))
    seg = m.group(2)
    body = m.group(3).strip()
    if body.startswith("["):
        body = body[1:-1]
    elif not re.fullmatch(r"0x[0-9a-f]+", body):
        return None
    base = index = None
    scale = 1
    disp = 0
    for term in re.findall(r"[+-]?[^+-]+", body):
        sign = -1 if term.startswith("-") else 1
        t = term.lstrip("+-").strip()
        if re.fullmatch(r"0x[0-9a-f]+", t):
            disp += sign * int(t, 16)
        elif "*" in t:
            r, sc = t.split("*")
            if r in REG32:
                index, scale = r, int(sc)
            else:
                return None
        elif t in REG32:
            if base is None:
                base = t
            else:
                index, scale = t, 1
        else:
            return None
    return Op("mem", size=size, seg=seg, base=base, index=index, scale=scale, disp=disp)


def parse_insn(addr, hexbytes, text):
    text = re.sub(r"\s+", " ", text.strip())
    parts = text.split(" ", 1)
    mn = parts[0]
    if mn in ("rep", "repz", "repnz", "lock") and len(parts) > 1:
        mn, rest = parts[1].split(" ", 1) if " " in parts[1] else (parts[1], "")
        mn = parts[0] + " " + mn
        parts = [mn, rest]
    ops = []
    if len(parts) > 1 and parts[1]:
        raw = parts[1]
        # split on top-level commas
        for piece in re.split(r",(?![^\[]*\])", raw):
            o = parse_op(piece)
            if o is None:
                ops = None
                break
            ops.append(o)
    return Insn(addr, len(hexbytes) // 2, mn, ops, text, hexbytes)


def decode(va, n):
    return [parse_insn(a, b, t) for a, b, t in common.disasm(va, n)]


BRANCH = re.compile(r"^(?:j[a-z]+|call|loop[a-z]*) (?:0x)?([0-9a-f]+)(?: <.*>)?$")


def extent(va, window=0x80, bound=True):
    """CFG-closed extent (bytes) of the function at va, excluding trailing padding.
    Returns (size, insns).  With bound=True the decode window stops at the next known
    function entry (a `jmp` to it is then a tail call, not part of this function)."""
    if bound:
        try:
            nxt = common.next_entry(va)
        except Exception:
            nxt = None
        if nxt and va < nxt:
            window = min(window, nxt - va)
    insns = decode(va, window)
    by = {i.addr: i for i in insns}
    seen, work = set(), [va]
    while work:
        a = work.pop()
        while a in by and a not in seen:
            seen.add(a)
            i = by[a]
            m = re.match(r"^(j[a-z]+|jmp) (?:0x)?([0-9a-f]+)$", i.text)
            if m:
                t = int(m.group(2), 16)
                if va <= t < va + window:
                    work.append(t)
            if i.mn.startswith("ret") or i.mn == "jmp" or i.mn == "int3" or i.text.startswith("(bad)"):
                break
            a += i.size
    if not seen:
        return 0, []
    last = max(seen)
    end = last + by[last].size
    return end - va, [by[a] for a in sorted(seen)]
