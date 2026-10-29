#!/usr/bin/env python3
# Provenance: original. Calling-convention evidence from a callee's own retail bytes.
"""sig(addr) -> Sig(pops, reads_ecx, reads_edx, size) from the callee's retail instructions.

pops: the single `ret n` value over the CFG-closed extent (None if returns disagree or the
extent could not be bounded).  reads_ecx/reads_edx: a forward dataflow over the callee's
decoded control-flow graph finds a read of the register on some path before any write
(calls clobber ECX/EDX, partial 8/16-bit writes do not count as writes).
"""
import functools
import re
from dataclasses import dataclass

import x86


@dataclass
class Sig:
    pops: object
    reads_ecx: bool
    reads_edx: bool
    size: int


FULL = {"ecx": "ecx", "cl": "ecx", "cx": "ecx", "ch": "ecx", "edx": "edx", "dl": "edx", "dx": "edx", "dh": "edx",
        "eax": "eax", "al": "eax", "ax": "eax", "ah": "eax", "ebx": "ebx", "bl": "ebx", "bx": "ebx", "bh": "ebx",
        "esi": "esi", "si": "esi", "edi": "edi", "di": "edi", "ebp": "ebp", "bp": "ebp"}
FULL32 = {"ecx", "edx", "eax", "ebx", "esi", "edi", "ebp"}
PARTIAL = {"cl", "ch", "cx", "dl", "dh", "dx", "al", "ah", "ax", "bl", "bh", "bx", "si", "di", "bp"}
WRITES_DST = {"mov", "movzx", "movsx", "lea", "pop", "setne", "sete", "setl", "setg", "setle", "setge", "seta",
              "setb", "setae", "setbe", "setnz", "setz", "sets", "setns", "cvttsd2si", "movd", "movss", "movsd"}
RMW = {"add", "sub", "and", "or", "xor", "adc", "sbb", "inc", "dec", "neg", "not", "shl", "shr", "sar", "sal",
       "rol", "ror", "imul", "xchg"}
NO_WRITE = {"cmp", "test", "push", "call", "jmp", "ret", "nop"}


def rw(i):
    """(entry-registers read, registers fully written) among ecx/edx for one instruction."""
    reads, writes = set(), set()
    if i.ops is None:
        return reads, writes
    mn = i.mn
    ops = i.ops
    for k, o in enumerate(ops):
        if o.kind == "mem":
            for r in (o.base, o.index):
                if r in FULL:
                    reads.add(FULL[r])
    if mn.startswith("rep") or mn.startswith("movs") or mn.startswith("stos") or mn.startswith("lods"):
        reads.update(("ecx", "esi", "edi", "eax"))
    if mn in ("mul", "div", "idiv", "cdq"):
        reads.update(("eax", "edx") if mn in ("div", "idiv") else ("eax",))
        writes.update(("edx", "eax"))
    if mn == "xor" and len(ops) == 2 and ops[0].kind == "reg" and ops[1].kind == "reg" and ops[0].reg == ops[1].reg:
        if ops[0].reg in FULL32:
            writes.add(FULL[ops[0].reg])
        return reads, writes
    if not ops:
        return reads, writes
    dst = ops[0]
    # sources
    for o in (ops[1:] if mn in WRITES_DST or mn in RMW or mn in ("cmp", "test") else ops):
        if o.kind == "reg" and o.reg in FULL:
            reads.add(FULL[o.reg])
    if mn in ("cmp", "test", "push"):
        for o in ops[:1]:
            if o.kind == "reg" and o.reg in FULL:
                reads.add(FULL[o.reg])
    elif mn in RMW and dst.kind == "reg" and dst.reg in FULL:
        reads.add(FULL[dst.reg])
        if dst.reg in FULL32:
            writes.add(FULL[dst.reg])
    elif mn in WRITES_DST and dst.kind == "reg" and dst.reg in FULL32:
        writes.add(FULL[dst.reg])
    elif mn in ("call", "jmp") and dst.kind == "reg" and dst.reg in FULL:
        reads.add(FULL[dst.reg])
    if mn == "call":
        writes.update(("ecx", "edx", "eax"))
        reads.update(("ecx", "edx"))
    if mn.startswith("ret"):
        reads.add("eax")
    return reads, writes


BR = re.compile(r"^(j[a-z]+|jmp) (?:0x)?([0-9a-f]+)$")


@functools.lru_cache(None)
def sig(addr, window=0x600):
    try:
        size, insns = x86.extent(addr, window, bound=False)
    except SystemExit:
        return None
    if not insns:
        return None
    by = {i.addr: i for i in insns}
    pops = set()
    for i in insns:
        if i.mn == "ret":
            pops.add(i.ops[0].val if i.ops else 0)
    p = next(iter(pops)) if len(pops) == 1 else None
    # forward must-written analysis over the decoded CFG
    state = {}
    reads = set()
    work = [(addr, frozenset())]
    while work:
        a, cur = work.pop()
        while a in by:
            old = state.get(a)
            new = cur if old is None else (old & cur)
            if old is not None and new == old:
                break
            state[a] = cur = new
            i = by[a]
            r, w = rw(i)
            reads |= ((r & {"ecx", "edx"}) - cur)
            cur = cur | w
            m = BR.match(i.text)
            if m:
                t = int(m.group(2), 16)
                if t in by:
                    work.append((t, cur))
            if i.mn.startswith("ret") or i.mn == "jmp" or i.mn == "int3":
                break
            a += i.size
    return Sig(p, "ecx" in reads, "edx" in reads, size)


def live_after(insns_by_addr, start, reg, window_end=None):
    """True if `reg` (full 32-bit name) is read before being written on some path from `start`.
    `ret` counts as a read of eax; a call reads ecx/edx (possible arguments)."""
    state = {}
    work = [(start, False)]
    seen = set()
    while work:
        a, _ = work.pop()
        while a in insns_by_addr and a not in seen:
            seen.add(a)
            i = insns_by_addr[a]
            r, w = rw(i)
            if reg in r:
                return True
            if reg in w:
                break
            m = BR.match(i.text)
            if m:
                t = int(m.group(2), 16)
                if t in insns_by_addr:
                    work.append((t, False))
            if i.mn.startswith("ret") or i.mn == "jmp" or i.mn == "int3":
                break
            a += i.size
    return False
