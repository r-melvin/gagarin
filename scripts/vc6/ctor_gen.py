#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: own-binary-via-Ghidra
#
# ctor_gen.py -- first-draft constructor and destructor skeleton for a class with a known layout.
#
# The draft is read from the retail constructor's own instructions:
#   - the call on `this` before any store is the base constructor (initialiser list);
#   - a call on `this + d` is a member constructor (initialiser list, named by the layout header);
#   - `[this + d]` stores become `Field = value;` in store order (constants tracked through
#     registers; floats via fld1/fldz or a constant read from the image);
#   - vtable-pointer stores are implicit and appear only as comments;
#   - `rep stos` becomes a zero-fill comment.
# It is a starting point for scripts/vc6/match.sh, not a matcher: argument expressions and
# control flow are left as comments.  Names come from the class's match/_layout header
# (and its bases); anything unnamed prints as an offset comment.  Output goes to stdout;
# nothing is written to the tree.
#
#   GAMEMD_BINARY=... ctor_gen.py DriveLocomotionClass [--ctor 0x4AF540] [--dtor]
#   GAMEMD_BINARY=... ctor_gen.py --compare match/movement/drive_locomotion.cpp DriveLocomotionClass --ctor 0x4AF540

import argparse
import json
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import binfn  # noqa: E402
import layout_recover as lr  # noqa: E402
from binfn import Tracker, call_target, imm, mem, norm_reg  # noqa: E402

REPO = binfn.REPO


class Names(object):
    """Function and field names for the draft."""

    def __init__(self, data, hidx, cls):
        d = os.path.join(REPO, 'scripts', 'data')
        self.fn = {}
        for m in json.load(open(os.path.join(d, 'match_manifest.json'))):
            self.fn[int(m['addr'], 16)] = m['name']
        b = json.load(open(os.path.join(d, 'symbol_bindings.json')))
        self.bind = {}
        for sym, addr in b.items():
            a = int(addr, 16) if isinstance(addr, str) else addr
            self.bind.setdefault(a, sym)
        self.vtables = {}
        for v in data.rtti.values():
            for lc in v['locators']:
                if lc['vtable_va']:
                    self.vtables[int(lc['vtable_va'], 16)] = v['demangled_name']
        self.chain = (data.rtti.get(cls) or {}).get('base_chain', [cls])
        self.fields = []     # (off, name, ctype, elsize, count, owner)
        seen = set()
        for c in self.chain:
            if c in seen or c.startswith('I') and c[1:2].isupper():
                continue
            seen.add(c)
            f, ms, _ = hidx.members(c)
            for m in ms:
                sz = hidx.type_size(m.ctype)
                self.fields.append((m.off, m.name, m.ctype, sz, m.count if getattr(m, 'array', False) else None, c))
        self.fields.sort(key=lambda x: x[0])
        self.hidx = hidx

    def func(self, a):
        if a in self.fn:
            return self.fn[a]
        if a in self.bind:
            return self.bind[a]
        return 'FUN_%08X' % a

    def field(self, off):
        """C++ lvalue text for the member at `off`, plus its declared type."""
        best = None
        for o, name, ctype, sz, cnt, owner in self.fields:
            if o == off:
                return (name if not cnt else '%s[0]' % name), ctype
            if o < off and (best is None or o > best[0]):
                best = (o, name, ctype, sz, cnt)
        if best:
            o, name, ctype, sz, cnt = best
            if cnt and sz and off < o + sz * cnt:
                return '%s[%d]' % (name, (off - o) // sz), ctype
            if sz is None or off < o + sz * (cnt or 1):
                sub = self._sub(ctype.replace('const ', '').strip(), off - o)
                if sub:
                    return '%s.%s' % (name, sub[0]), sub[1]
                return '%s /* +0x%X */' % (name, off - o), ctype
        return '/* +0x%X */ unknown_%X' % (off, off), None

    def _sub(self, ctype, rel):
        """Member of a nested struct type at relative offset `rel`, if its header names one."""
        if ctype in self._subcache:
            ms = self._subcache[ctype]
        else:
            f, ms, _ = self.hidx.members(ctype)
            self._subcache[ctype] = ms
        for m in ms:
            if m.off == rel:
                return m.name, m.ctype
        return None

    _subcache = {}


_SUBREG = {'al': 'eax', 'bl': 'ebx', 'cl': 'ecx', 'dl': 'edx', 'ax': 'eax', 'bx': 'ebx', 'cx': 'ecx', 'dx': 'edx'}


def _const(op, consts):
    v = imm(op)
    if v is not None:
        return v
    op = op.strip()
    r = norm_reg(op)
    if r is not None and (op == r or op in _SUBREG) and r in consts:
        c = consts[r]
        return c & (0xFF if op.endswith('l') and len(op) == 2 else 0xFFFF if len(op) == 2 else 0xFFFFFFFF) \
            if isinstance(c, int) else c
    return None


def _fmt(v, ctype=None):
    if v is None:
        return None
    if isinstance(v, str):
        return v
    if v >= 0x80000000:
        s = -(0x100000000 - v)
        return str(s)
    if v < 10:
        return str(v)
    return '0x%X' % v


def float_text(f):
    return repr(float(f)).rstrip('0').rstrip('.') + ('f' if True else '') if f == f else 'nan'


def draft(binary, data, hidx, cls, ctor):
    names = Names(data, hidx, cls)
    ins = binary.func(ctor)
    tr = Tracker('ecx')
    consts = {}
    fpu = []
    init_list = []     # (text)
    body = []
    vptrs = []
    first_call_pending = True
    stores_seen = False
    unk_calls = 0
    for n, i in enumerate(ins):
        mn, ops = i.mn, i.ops
        if mn == 'ret':
            break
        if mn == 'call':
            t = call_target(i)
            args = list(reversed(tr.args))
            held = tr.held.get('ecx')
            if t is not None and held is not None:
                argtxt = ', '.join(_arg(a, names, consts) for a in args if a[0] != 'other' or True)
                nm = names.func(t)
                if held == 0 and not stores_seen and first_call_pending:
                    init_list.append(('base', '%s(%s)' % (nm.split('::')[0], argtxt), i.addr))
                    first_call_pending = False
                elif held == 0:
                    body.append('// %s(%s);  // call on this @0x%X' % (nm, argtxt, i.addr))
                else:
                    fld, ctype = names.field(held)
                    init_list.append(('member', '%s(%s)' % (fld.split(' ')[0], argtxt), i.addr, nm))
            elif t is not None:
                body.append('// %s(...);  // @0x%X' % (names.func(t), i.addr))
                unk_calls += 1
            consts = {k: v for k, v in consts.items() if k not in ('eax', 'ecx', 'edx')}
            tr.step(i)
            continue
        if mn == 'mov' and len(ops) == 2:
            dst = tr.recv_mem(ops[0])
            if dst is not None:
                width = dst[0] or 4
                val = _const(ops[1], consts)
                fld, ctype = names.field(dst[1])
                v = imm(ops[1])
                if v is not None and v in names.vtables and width == 4:
                    vptrs.append((dst[1], names.vtables[v]))
                    body.append('// vptr @0x%X = %s (implicit)' % (dst[1], names.vtables[v]))
                else:
                    if val is None:
                        txt = '/* %s */' % ops[1]
                    elif ctype in ('bool',):
                        txt = 'true' if val else 'false'
                    else:
                        txt = _fmt(val)
                    stores_seen = True
                    body.append('%s = %s;' % (fld, txt))
            else:
                r = norm_reg(ops[0])
                gm = re.match(r'^(?:DWORD PTR )?ds:(0x[0-9a-f]+)$', ops[1]) if r else None
                if r and gm and ops[0] == r:
                    consts[r] = 'DAT_%08X' % int(gm.group(1), 16)
                elif r and ops[0] == r:
                    v = _const(ops[1], consts)
                    if v is not None:
                        consts[r] = v
                    else:
                        consts.pop(r, None)
        elif mn == 'xor' and len(ops) == 2 and ops[0] == ops[1] and norm_reg(ops[0]):  # xor r,r
            consts[norm_reg(ops[0])] = 0
        elif mn == 'or' and len(ops) == 2 and imm(ops[1]) == 0xFFFFFFFF and norm_reg(ops[0]) == ops[0]:
            consts[ops[0]] = 0xFFFFFFFF
        elif mn == 'fld1':
            fpu.append(1.0)
        elif mn == 'fldz':
            fpu.append(0.0)
        elif mn == 'fld' and ops:
            m = re.match(r'(DWORD|QWORD) PTR ds:(0x[0-9a-f]+)$', ops[0])
            fpu.append(_read_float(binary, int(m.group(2), 16), m.group(1) == 'QWORD') if m else None)
        elif mn == 'fstp' and ops:
            dst = tr.recv_mem(ops[0])
            v = fpu.pop() if fpu else None
            if dst is not None:
                fld, ctype = names.field(dst[1])
                stores_seen = True
                body.append('%s = %s;' % (fld, float_text(v) if v is not None else '/* x87 value */'))
        elif mn == 'stos' or mn.startswith('stos'):
            body.append('// rep stos: zero fill of an array at ecx/edi  // @0x%X' % i.addr)
        tr.step(i)
    return {'cls': cls, 'names': names, 'init': init_list, 'body': body, 'vptrs': vptrs, 'ctor': ctor, 'unk_calls': unk_calls}


def _read_float(binary, va, dbl):
    try:
        for _, s, vs, ro, rs in binary.secs:
            if s <= va < s + rs:
                o = ro + va - s
                if dbl:
                    return struct.unpack_from('<d', binary.b, o)[0]
                return struct.unpack_from('<f', binary.b, o)[0]
    except Exception:
        pass
    return None


def _arg(a, names, consts):
    k = a[0]
    if k == 'imm':
        return _fmt(a[1])
    if k == 'load':
        return names.field(a[1])[0]
    if k == 'addr':
        return '&' + names.field(a[1])[0]
    return '/* %s */' % a[1]


def render(cls, d, with_header=True):
    out = []
    if with_header:
        out.append('// FUNCTION: GAMEMD 0x%X' % d['ctor'])
    inits = []
    for it in d['init']:
        inits.append(it[1])
    sig = '%s::%s()' % (cls, cls)
    out.append(sig)
    if inits:
        out.append('    : ' + ',\n      '.join(inits))
    out.append('{')
    for ln in d['body']:
        out.append('    ' + ln)
    out.append('}')
    return '\n'.join(out)


def dtor_skeleton(binary, data, hidx, cls):
    names = Names(data, hidx, cls)
    r = data.rtti.get(cls)
    slot0 = target = None
    for lc in (r or {}).get('locators', []):
        if not lc['vtable_va']:
            continue
        for k in range(0, 16):
            f = binary.dword(int(lc['vtable_va'], 16) + 4 * k)
            if not f or not (0x401000 <= f < 0x800000):
                break
            th = binary.func(f, 0x60)
            # the scalar deleting destructor tests the delete flag and calls operator delete
            if any(i.mn == 'test' and len(i.ops) == 2 and 'esp+0x4]' in i.ops[0] and imm(i.ops[1]) == 1 for i in th[:12]):
                target = next((call_target(i) for i in th if call_target(i)), None)
                slot0 = f
                break
        if target:
            break
    if target is None:
        return '// no scalar deleting destructor found for %s' % cls
    ins = binary.func(target)
    tr = Tracker('ecx')
    lines = []
    for i in ins:
        if i.mn == 'ret':
            break
        t = call_target(i)
        if t is not None:
            held = tr.held.get('ecx')
            nm = names.func(t)
            if held is None:
                lines.append('// %s(...);  // @0x%X' % (nm, i.addr))
            elif held == 0:
                lines.append('// base/own teardown %s @0x%X (the base destructor runs implicitly after the body)' % (nm, i.addr))
            else:
                lines.append('// member %s torn down by %s @0x%X' % (names.field(held)[0], nm, i.addr))
        else:
            dst = tr.recv_mem(i.ops[0]) if i.mn == 'mov' and i.ops else None
            if dst is not None:
                v = imm(i.ops[1]) if len(i.ops) > 1 else None
                if v in names.vtables:
                    lines.append('// vptr @0x%X reset to %s (implicit)' % (dst[1], names.vtables[v]))
        tr.step(i)
    return '// FUNCTION: GAMEMD 0x%X (scalar deleting destructor 0x%X)\n%s::~%s()\n{\n%s\n}' % (
        target, slot0, cls, cls, '\n'.join('    ' + l for l in lines))


def find_ctors(data, cls):
    return sorted(int(c['constructor'], 16) for c in data.ctors if c.get('class') == cls)


# -- comparison with a matched source -----------------------------------------------------------

def matched_body(path, addr):
    t = open(path, encoding='utf-8', errors='replace').read()
    m = re.search(r'//\s*FUNCTION:\s*GAMEMD\s*0x%X\b' % addr, t, re.I)
    if not m:
        return None
    i = t.index('{', m.end())
    depth, j = 0, i
    while j < len(t):
        depth += {'{': 1, '}': -1}.get(t[j], 0)
        j += 1
        if depth == 0:
            break
    return t[m.end():j]


_ASSIGN = re.compile(r'(?<![=!<>])\b([A-Za-z_][\w.]*(?:\[\d+\])?)\s*=\s*([^;=]+);')
_INIT = re.compile(r'\b([A-Za-z_]\w*)\(([^()]*)\)')


def _norm(v):
    v = v.strip()
    v = {'true': '1', 'false': '0', 'NULL': '0'}.get(v, v)
    if re.match(r'^-?[\d.]+f$', v):
        v = v[:-1]
    try:
        return str(int(v, 0))
    except ValueError:
        return v


def _top(name):
    return re.split(r'[.\[]', name.replace('this->', ''))[0]


def assignments(text):
    """[(top-level field, value)] from statement assignments and the initialiser list."""
    text = re.sub(r'//[^\n]*', '', text)
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    head, _, body = text.partition('{')
    head = head.split('\n', 1)[-1] if '::' in head.split('\n', 1)[0] else head
    out = []
    if ':' in head:
        for m in _INIT.finditer(head.split(':', 1)[1]):
            out.append((m.group(1), _norm(m.group(2))))
    for m in _ASSIGN.finditer(body):
        out.append((_top(m.group(1)), _norm(m.group(2))))
    return out


def compare(d, src_text):
    gen_all = assignments(render(d['cls'], d, False))
    # the draft's init list holds base and member constructors: names only
    gen_names = [a for a, _ in gen_all]
    ref = assignments(src_text)
    ref_names = [a for a, _ in ref]
    gset, rset = set(gen_names), set(ref_names)
    common = [a for a in gen_names if a in rset]
    rcommon = [a for a in ref_names if a in gset]
    return {'draft_fields': len(gset), 'source_fields': len(rset), 'common': len(gset & rset),
            'missing_in_draft': sorted(rset - gset), 'extra_in_draft': sorted(gset - rset),
            'order_same': [a for i, a in enumerate(common) if a not in common[:i]] ==
                          [a for i, a in enumerate(rcommon) if a not in rcommon[:i]]}


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('cls')
    ap.add_argument('--ctor', help='constructor address (default: every mined constructor of the class)')
    ap.add_argument('--dtor', action='store_true', help='also print a destructor skeleton')
    ap.add_argument('--compare', metavar='SRC.cpp', help='diff the draft against a matched source body')
    a = ap.parse_args(argv)
    binary = binfn.Binary()
    data = lr.Data()
    hidx = lr.HeaderIndex()
    ctors = [int(a.ctor, 16)] if a.ctor else find_ctors(data, a.cls)
    if not ctors:
        raise SystemExit('no constructor known for %s; pass --ctor' % a.cls)
    for c in ctors:
        d = draft(binary, data, hidx, a.cls, c)
        if a.compare:
            body = matched_body(a.compare, c)
            if body is None:
                print('0x%X: no FUNCTION marker in %s' % (c, a.compare))
                continue
            print('0x%X %s' % (c, json.dumps(compare(d, body))))
        else:
            print(render(a.cls, d))
            print()
    if a.dtor:
        print(dtor_skeleton(binary, data, hidx, a.cls))
    return 0


if __name__ == '__main__':
    sys.exit(main())
