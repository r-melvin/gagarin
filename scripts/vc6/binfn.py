#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: own-binary-via-Ghidra
#
# binfn.py -- shared plumbing for layout_recover.py and ctor_gen.py: read the user's own
# gamemd.exe (GAMEMD_BINARY), disassemble one function with objdump, parse the listing into
# instructions, and follow which registers still hold the receiver (`this`).
#
# Nothing from the binary is stored: every query reads the pinned file at run time.
# Parsing and tracking work on plain objdump text, so tests feed them fixture text.

import json
import os
import re
import struct
import subprocess

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))

REG32 = ('eax', 'ebx', 'ecx', 'edx', 'esi', 'edi', 'ebp', 'esp')
_SUB = {'ax': 'eax', 'bx': 'ebx', 'cx': 'ecx', 'dx': 'edx', 'si': 'esi', 'di': 'edi', 'bp': 'ebp', 'sp': 'esp',
        'al': 'eax', 'ah': 'eax', 'bl': 'ebx', 'bh': 'ebx', 'cl': 'ecx', 'ch': 'ecx', 'dl': 'edx', 'dh': 'edx'}


def norm_reg(r):
    r = r.strip().lower()
    if r in REG32:
        return r
    return _SUB.get(r)


class Insn(object):
    __slots__ = ('addr', 'mn', 'ops', 'raw')

    def __init__(self, addr, mn, ops, raw=''):
        self.addr, self.mn, self.ops, self.raw = addr, mn, ops, raw

    def __repr__(self):
        return '%x: %s %s' % (self.addr, self.mn, ','.join(self.ops))


_LINE = re.compile(r'^\s*([0-9a-f]+):\t((?:[0-9a-f]{2} )+)\s*\t?(.*)$')


def split_ops(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch == '[':
            depth += 1
        elif ch == ']':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_objdump(text):
    """objdump -d -M intel text -> list of Insn (bytes-only continuation lines are merged)."""
    out = []
    for line in text.splitlines():
        m = _LINE.match(line)
        if not m:
            continue
        addr = int(m.group(1), 16)
        rest = m.group(3).split('#')[0].strip()
        if not rest:
            continue
        parts = rest.split(None, 1)
        mn = parts[0]
        # prefixes (rep, repnz, lock) belong to the mnemonic that follows
        while mn in ('rep', 'repz', 'repnz', 'lock') and len(parts) > 1:
            parts = parts[1].split(None, 1)
            mn = parts[0]
        ops = split_ops(parts[1]) if len(parts) > 1 else []
        out.append(Insn(addr, mn, ops, rest))
    return out


_MEM = re.compile(r'^(?:(BYTE|WORD|DWORD|QWORD|TBYTE|XMMWORD) PTR )?(?:[a-z]s:)?\[([a-z]{2,3})(?:([+-])(0x[0-9a-f]+))?\]$')
_WIDTH = {'BYTE': 1, 'WORD': 2, 'DWORD': 4, 'QWORD': 8, 'TBYTE': 10, 'XMMWORD': 16}


def mem(op):
    """'DWORD PTR [esi+0x10]' -> (width|None, 'esi', 0x10); None if not a simple reg+disp ref."""
    m = _MEM.match(op.strip())
    if not m:
        return None
    d = int(m.group(4), 16) if m.group(4) else 0
    if m.group(3) == '-':
        d = -d
    return (_WIDTH.get(m.group(1)), m.group(2), d)


def imm(op):
    op = op.strip()
    try:
        if op.startswith('-0x'):
            return -int(op[3:], 16) & 0xFFFFFFFF
        if op.startswith('0x'):
            return int(op, 16)
        if re.match(r'^-?\d+$', op):
            return int(op) & 0xFFFFFFFF
    except ValueError:
        pass
    return None


def call_target(i):
    if i.mn == 'call' and i.ops:
        t = i.ops[0]
        if t.startswith('0x'):
            return int(t, 16)
    return None


_NOWRITE = ('cmp', 'test', 'push', 'call', 'jmp', 'ret', 'nop', 'fld', 'fstp', 'fst', 'fild', 'fcom', 'fcomp', 'fxch')


def written_reg(i):
    """The 32-bit register an instruction overwrites (first operand), or None."""
    if not i.ops or i.mn in _NOWRITE or i.mn.startswith('j') or i.mn.startswith('f'):
        return None
    if i.mn in ('xchg',):
        return norm_reg(i.ops[0])
    if i.mn == 'pop':
        return norm_reg(i.ops[0])
    return norm_reg(i.ops[0])


class Tracker(object):
    """Registers that provably hold the receiver, linear scan (no path merge).

    held[r] = displacement d such that r == this + d.  `lea r,[recv+d]` therefore keeps
    r at d, a `mov r,[recv+d]` load drops it.
    """

    def __init__(self, mode):
        self.held = {'ecx': 0} if mode == 'ecx' else {}
        self.mode = mode
        self.sp = 0                 # bytes pushed since entry (prologue arg location)
        self.loads = {}             # reg -> (disp, width) value loaded from [recv+disp]
        self.args = []              # pushed operands since the last call: ('imm', v) etc.

    def recv_mem(self, op):
        m = mem(op)
        if m and m[1] in self.held:
            return (m[0], self.held[m[1]] + m[2])
        return None

    def describe(self, op):
        """What a pushed operand is, resolved against the state at the push."""
        r = norm_reg(op)
        if r is not None and op.strip().lower() == r:
            if r in self.held:
                return ('addr', self.held[r], r)
            if r in self.loads:
                return ('load',) + self.loads[r]
            return ('other', op)
        v = imm(op)
        if v is not None:
            return ('imm', v)
        m = self.recv_mem(op)
        if m is not None:
            return ('load', m[1], m[0] or 4)
        return ('other', op)

    def step(self, i):
        """Update state for one instruction; returns None. Call before inspecting effects."""
        mn, ops = i.mn, i.ops
        if mn == 'push':
            self.sp += 4
            self.args.append(self.describe(ops[0]) if ops else ('other', ''))
            return
        if mn == 'call':
            for r in ('eax', 'ecx', 'edx'):
                self.held.pop(r, None)
                self.loads.pop(r, None)
            self.args = []
            return
        if mn == 'sub' and ops and ops[0] == 'esp':
            v = imm(ops[1])
            if v is not None:
                self.sp += v
            return
        w = written_reg(i)
        if w is None:
            return
        src = ops[1] if len(ops) > 1 else ''
        newheld = None
        newload = None
        if mn == 'mov' and len(ops) == 2:
            sreg = norm_reg(src)
            if sreg is not None and ops[0] == w and src == sreg and sreg in self.held:
                newheld = self.held[sreg]
            elif self.mode == 'stack' and ops[0] == w:
                m = mem(src)
                if m and m[1] == 'esp' and m[0] in (4, None) and m[2] - self.sp == 4:
                    newheld = 0
            if newheld is None:
                m = self.recv_mem(src)
                if m is not None:
                    newload = (m[1], m[0] or 4)
        elif mn == 'lea' and len(ops) == 2:
            m = mem(src.replace('DWORD PTR ', ''))
            if m and m[1] in self.held:
                newheld = self.held[m[1]] + m[2]
        elif mn in ('movzx', 'movsx') and len(ops) == 2:
            m = self.recv_mem(src)
            if m is not None:
                newload = (m[1], m[0] or 1)
        self.held.pop(w, None)
        self.loads.pop(w, None)
        if newheld is not None:
            self.held[w] = newheld
        if newload is not None:
            self.loads[w] = newload
        if mn == 'pop':
            self.sp -= 4


def disasm_range(binary, start, stop):
    out = subprocess.check_output(['objdump', '-d', '-M', 'intel', '--start-address=0x%X' % start,
                                   '--stop-address=0x%X' % stop, binary], universal_newlines=True)
    return parse_objdump(out)


class Binary(object):
    """The retail image: sections, dwords, C strings, per-function disassembly."""

    def __init__(self, path=None):
        path = path or os.environ.get('GAMEMD_BINARY')
        if not path or not os.path.exists(path):
            raise SystemExit('set GAMEMD_BINARY to the user-owned gamemd.exe')
        self.path = path
        b = open(path, 'rb').read()
        pe = struct.unpack_from('<I', b, 0x3C)[0]
        nsec = struct.unpack_from('<H', b, pe + 6)[0]
        optsz = struct.unpack_from('<H', b, pe + 20)[0]
        base = struct.unpack_from('<I', b, pe + 24 + 28)[0]
        self.b, self.secs = b, []
        for k in range(nsec):
            name, vsize, va, rsize, roff = struct.unpack_from('<8sIIII', b, pe + 24 + optsz + 40 * k)
            self.secs.append((name.rstrip(b'\0').decode(), base + va, vsize, roff, rsize))
        self._extents = None
        self._cache = {}

    def dword(self, va):
        for _, s, vs, ro, rs in self.secs:
            if s <= va < s + min(vs, rs) - 3:
                return struct.unpack_from('<I', self.b, ro + va - s)[0]
        return None

    def cstring(self, va, maxlen=96):
        for _, s, vs, ro, rs in self.secs:
            if s <= va < s + rs:
                o = ro + va - s
                e = self.b.find(b'\0', o, o + maxlen)
                if e < 0:
                    return None
                t = self.b[o:e]
                if len(t) >= 2 and all(32 <= c < 127 for c in t):
                    return t.decode('ascii')
                return None
        return None

    def extent(self, addr):
        if self._extents is None:
            fe = json.load(open(os.path.join(REPO, 'scripts', 'data', 'function_extents.json')))
            self._extents = {int(e[0], 16): int(e[1], 16) for e in fe['entries']}
        return self._extents.get(addr)

    def func(self, addr, length=None):
        if addr in self._cache:
            return self._cache[addr]
        n = length or self.extent(addr) or 0x400
        ins = disasm_range(self.path, addr, addr + n)
        self._cache[addr] = ins
        return ins
