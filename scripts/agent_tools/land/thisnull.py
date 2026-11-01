#!/usr/bin/env python3
"""thisnull.py: the evidence rule for a null test of `this` in matched source.

A null test of `this` is allowed only on a line (or the line directly above it) that carries

    // THISNULL: GAMEMD 0xADDR

where 0xADDR is a retail out-of-line function that is a matched (100%, strict) manifest row and whose own
retail bytes test the this register (ECX, or a register copied from it) before anything else uses it.
The out-of-line copy is the proof that the original source tested `this`.

Used by pktlint (annotation + matched row) and by the `thisnull` land gate (the same, plus the retail bytes).
"""
import os
import re
import subprocess

ANNOT = re.compile(r"//\s*THISNULL:\s*GAMEMD\s+(0[xX][0-9A-Fa-f]+)\b")
_PROLOGUE = {"push", "nop"}


def annotation_addr(lines, idx):
    """Address cited by an annotation on lines[idx] or lines[idx-1] (0-based), else None."""
    for j in (idx, idx - 1):
        if 0 <= j < len(lines):
            m = ANNOT.search(lines[j])
            if m:
                return int(m.group(1), 16)
    return None


def is_matched(row):
    return bool(row) and row.get("status") == "matched" and float(row.get("pct", 100) or 0) >= 100.0


def _disasm(binary, addr, n=48):
    out = subprocess.run(["objdump", "-d", "-M", "intel", "--start-address=0x%X" % addr, "--stop-address=0x%X" % (addr + n), binary],
                         capture_output=True, text=True).stdout
    res = []
    for ln in out.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\t(?:[0-9a-f]{2} )+\s*\t?(\S+)\s*(.*)$", ln)
        if m:
            res.append((int(m.group(1), 16), m.group(2), [o.strip().lower() for o in m.group(3).split(",")] if m.group(3) else []))
    return res


def entry_tests_this(binary, addr):
    """True when the function at addr tests the this register (ECX or a register copied from it) before any other
    use: only `push r`, `mov r,ecx` / `mov r,r` copies and nops may precede `test r,r`."""
    alias = {"ecx"}
    for a, mn, ops in _disasm(binary, addr)[:10]:
        if mn == "test" and len(ops) == 2 and ops[0] == ops[1] and ops[0] in alias:
            return True
        if mn == "cmp" and len(ops) == 2 and ops[0] in alias and ops[1] in ("0x0", "0"):
            return True
        if mn == "mov" and len(ops) == 2 and ops[1] in alias and re.fullmatch(r"e?[a-ds][xi]|e[sd]i|ebx", ops[0]):
            alias.add(ops[0])
            continue
        if mn in _PROLOGUE:
            continue
        return False
    return False
