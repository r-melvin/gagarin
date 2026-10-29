#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: own-binary-via-Ghidra
#
# layout_recover.py -- propose class layout fields by merging four kinds of evidence.
#
#   ctor    constructor stores (scripts/data/ctor_field_offsets.json, class_sizes.json)
#   swizzle pointer fields registered with the SwizzleManager in the class's Load
#           (IPersistStream::Load = slot 5 of the primary vtable)
#   stream  IStream Read/Write calls and sub-object calls in Load/Save (slots 5 and 6)
#   crc     the checksum feed (slot 13): typed field order and sizes
#   ini     INI keys in the class's ReadINI (slot 25 of an AbstractTypeClass): names and reader types
#
# It diffs the proposals against the class's match/_layout header and lists the gaps
# (unknown_XX members and unaccounted holes) it can fill.  It prints proposals only and never
# edits a header.  Every proposed field carries the instruction addresses that justify it, but
# per AGENTS.md they are leads: read the instruction back before it enters a header.
#
#   GAMEMD_BINARY=... layout_recover.py TechnoClass [--json] [--all]
#   GAMEMD_BINARY=... layout_recover.py --summary TechnoClass FootClass ...

import argparse
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import binfn  # noqa: E402
from binfn import Tracker, call_target, imm, mem  # noqa: E402

REPO = binfn.REPO
SWIZZLE_VTABLE = 0x7F4108            # SwizzleManagerClass vtable; slot 4 registers a pointer field
SWIZZLE_SLOT = 4
ISTREAM_READ_SLOT, ISTREAM_WRITE_SLOT = 3, 4
SLOT_LOAD, SLOT_SAVE, SLOT_CRC, SLOT_INI = 5, 6, 13, 25

PRIM = {'int': 4, 'unsigned int': 4, 'unsigned long': 4, 'long': 4, 'short': 2, 'unsigned short': 2,
        'char': 1, 'unsigned char': 1, 'signed char': 1, 'bool': 1, 'BYTE': 1, 'float': 4, 'double': 8,
        'DWORD': 4, 'WORD': 2, 'HRESULT': 4, 'size_t': 4, '__int64': 8, 'unsigned __int64': 8}


class Ev(object):
    def __init__(self, off, width, source, detail, at=None, key=None, typ=None, pointer=False):
        self.off, self.width, self.source, self.detail = off, width, source, detail
        self.at, self.key, self.typ, self.pointer = at, key, typ, pointer

    def as_dict(self):
        return {'off': self.off, 'width': self.width, 'source': self.source, 'detail': self.detail,
                'at': self.at, 'key': self.key, 'type': self.typ, 'pointer': self.pointer}


# ---------------------------------------------------------------------------------------------
# Extractors.  Each takes a parsed instruction list and returns [Ev]; no binary access needed
# beyond the callbacks passed in, so tests can use fixture text.
# ---------------------------------------------------------------------------------------------

def _loop_count(ins, idx, reg):
    """If ins[idx] (a call) sits in a counted loop that strides `reg`, return (count, stride)."""
    back = None
    for j in range(idx + 1, min(idx + 8, len(ins))):
        t = ins[j]
        if t.mn.startswith('j') and t.mn != 'jmp' and t.ops and t.ops[0].startswith('0x'):
            tgt = int(t.ops[0], 16)
            if tgt <= ins[idx].addr:
                back = (j, tgt)
                break
    if back is None:
        return None
    j, tgt = back
    stride = None
    for k in range(idx, j):
        t = ins[k]
        if t.mn == 'add' and len(t.ops) == 2 and t.ops[0] == reg and imm(t.ops[1]):
            stride = imm(t.ops[1])
    top = next((n for n, t in enumerate(ins) if t.addr >= tgt), None)
    if stride is None or top is None:
        return None
    for k in range(top - 1, max(top - 6, -1), -1):
        t = ins[k]
        if t.mn == 'mov' and len(t.ops) == 2 and not t.ops[0].startswith(('DWORD', 'BYTE', 'WORD')):
            v = imm(t.ops[1])
            if v is not None and 2 <= v <= 64 and t.ops[0] in ('ebp', 'ebx', 'edi', 'esi', 'ecx', 'edx', 'eax'):
                return (v, stride)
    return None


def extract_swizzle(ins, swizzle_target, mode='stack'):
    out = []
    tr = Tracker(mode)
    for n, i in enumerate(ins):
        t = call_target(i)
        if t == swizzle_target and len(tr.args) >= 2:
            d = tr.args[-2]
            if d[0] == 'addr':
                lp = _loop_count(ins, n, d[2])
                if lp:
                    for e in range(lp[0]):
                        out.append(Ev(d[1] + e * lp[1], 4, 'swizzle', 'pointer registered in loop x%d' % lp[0],
                                      at=i.addr, pointer=True))
                else:
                    out.append(Ev(d[1], 4, 'swizzle', 'pointer registered with the SwizzleManager', at=i.addr,
                                  pointer=True))
        tr.step(i)
    return out


def extract_streams(ins, mode='stack', swizzle_target=None):
    """Read/Write through IStream, and calls that take the address of a member or run on one."""
    out = []
    tr = Tracker(mode)
    for n, i in enumerate(ins):
        if i.mn == 'call' and i.ops:
            t = call_target(i)
            if t is not None and t == swizzle_target:
                tr.step(i)
                continue
            m = mem(i.ops[0])
            args = tr.args
            if m and m[2] in (ISTREAM_READ_SLOT * 4, ISTREAM_WRITE_SLOT * 4) and len(args) >= 3:
                buf, cb = args[-2], args[-3]
                if buf[0] == 'addr' and cb[0] == 'imm':
                    out.append(Ev(buf[1], cb[1], 'stream', 'IStream::%s of %d bytes' %
                                  ('Read' if m[2] == 12 else 'Write', cb[1]), at=i.addr))
            elif t is not None:
                sizes = [a[1] for a in args if a[0] == 'imm' and 0 < a[1] <= 0x1000]
                for a in args:
                    if a[0] == 'addr':
                        out.append(Ev(a[1], sizes[0] if sizes else None, 'stream',
                                      'member address passed to 0x%X' % t, at=i.addr))
                if 'ecx' in tr.held and tr.held['ecx'] != 0:
                    out.append(Ev(tr.held['ecx'], None, 'stream', 'sub-object call 0x%X' % t, at=i.addr))
        tr.step(i)
    return out


def extract_crc(ins, sink_size, mode='ecx'):
    """The checksum feed.  sink_size(target) -> bytes a sink helper consumes, or None."""
    out = []
    tr = Tracker(mode)
    for i in ins:
        t = call_target(i)
        if t is not None:
            sz = sink_size(t)
            if sz:
                loads = [a for a in reversed(tr.args) if a[0] == 'load']
                addrs = [a for a in tr.args if a[0] == 'addr']
                if loads:
                    if sz == 8 and len(loads) == 2:
                        offs = sorted(a[1] for a in loads)
                        for o in offs:
                            out.append(Ev(o, 4, 'crc', 'dword of an 8-byte checksum feed', at=i.addr))
                    else:
                        a = loads[0]
                        out.append(Ev(a[1], min(sz, a[2]) if a[2] else sz, 'crc',
                                      '%d-byte checksum feed' % sz, at=i.addr))
                for a in addrs:
                    out.append(Ev(a[1], None, 'crc', 'member address fed to checksum helper 0x%X' % t, at=i.addr))
        tr.step(i)
    return out


_READER = re.compile(r'^\?(Read\w+)@')
READER_TYPES = {'ReadInteger': 'int', 'ReadBool': 'bool', 'ReadDouble': 'double', 'ReadString': 'char[]',
                'ReadFloat': 'float', 'ReadSoundID': 'int'}


def extract_ini(ins, strfn, readername, mode='ecx'):
    """Key strings paired with the member they feed.  strfn(va) -> text|None,
    readername(target) -> 'ReadXxx'|None."""
    out = []
    tr = Tracker(mode)
    pending = None
    for n, i in enumerate(ins):
        if pending is not None:
            if i.mn == 'call' or n - pending['n'] > 10:
                out.append(_finish_ini(pending))
                pending = None
            elif i.mn in ('mov', 'fstp') and len(i.ops) >= 1:
                dst = tr.recv_mem(i.ops[0])
                if dst is not None and (i.mn == 'fstp' or (len(i.ops) == 2 and binfn.norm_reg(i.ops[1]))):
                    pending['store'] = (dst[1], dst[0] or (8 if 'QWORD' in i.ops[0] else 4), i.mn, i.addr)
                    out.append(_finish_ini(pending))
                    pending = None
        t = call_target(i)
        if t is not None:
            strs = []
            for a in tr.args:
                if a[0] == 'imm':
                    s = strfn(a[1])
                    if s:
                        strs.append(s)
            rn = readername(t) or ('reader_0x%X' % t if strs and len(tr.args) >= 2 else None)
            if strs and rn:
                addr_args = [a for a in tr.args if a[0] == 'addr']
                loads = [a for a in tr.args if a[0] == 'load']
                pending = {'n': n, 'key': strs[0], 'reader': rn, 'at': i.addr, 'target': t,
                           'addr': addr_args[0][1] if addr_args else None,
                           'dflt': (loads[0][1], loads[0][2]) if loads else None, 'store': None}
        tr.step(i)
    if pending is not None:
        out.append(_finish_ini(pending))
    return [e for e in out if e is not None]


def _finish_ini(p):
    typ = READER_TYPES.get(p['reader'], p['reader'])
    if p['addr'] is not None:
        return Ev(p['addr'], None, 'ini', '%s("%s") into a member buffer' % (p['reader'], p['key']), at=p['at'],
                  key=p['key'], typ=typ)
    if p['store']:
        off, w, how, at = p['store']
        if how == 'fstp':
            typ = 'double' if w == 8 else 'float'
        return Ev(off, w, 'ini', '%s("%s") stored at 0x%X' % (p['reader'], p['key'], at), at=p['at'], key=p['key'],
                  typ=typ)
    if p['dflt']:
        return Ev(p['dflt'][0], p['dflt'][1], 'ini', '%s("%s") default read from the member' % (p['reader'], p['key']),
                  at=p['at'], key=p['key'], typ=typ)
    return None


# ---------------------------------------------------------------------------------------------
# Header parsing
# ---------------------------------------------------------------------------------------------

class Member(object):
    def __init__(self, name, ctype, count, off, line):
        self.name, self.ctype, self.count, self.off, self.line = name, ctype, count, off, line
        self.size = None
        self.span = None

    def is_placeholder(self):
        return bool(re.match(r'^(unknown|_pad|pad|unk|filler|gap|_unused|unused)', self.name, re.I))


_DECL = re.compile(r'^\s*((?:(?:unsigned|signed|const|struct|class)\s+)*[A-Za-z_][\w:<>,\* ]*?)\s*([\*&]*)\s*'
                   r'([A-Za-z_]\w*)\s*(?:\[\s*(\w+)\s*\])?\s*(?::\s*\d+)?\s*;\s*(//.*)?$')
_OFFCOMMENT = re.compile(r'//.*?\+0x([0-9A-Fa-f]+)')


def _read(p):
    with open(p, encoding='utf-8', errors='replace') as f:
        return f.read()


class HeaderIndex(object):
    def __init__(self, root=REPO):
        self.root = root
        lay = sorted(glob.glob(os.path.join(root, 'match', '_layout', '*.h')))
        rest = sorted(f for f in glob.glob(os.path.join(root, 'match', '**', '*.h'), recursive=True) if f not in lay)
        self.files = lay + rest
        self.text = {f: _read(f) for f in self.files}
        self.sizes = dict(PRIM)
        for t in self.text.values():
            for m in re.finditer(r'GG_STATIC_ASSERT\(\s*sizeof\(\s*([^)]+?)\s*\)\s*==\s*(0x[0-9A-Fa-f]+|\d+)\s*\)', t):
                self.sizes.setdefault(m.group(1).replace('struct ', '').replace('class ', ''), int(m.group(2), 0))

    def find(self, cls):
        pat = re.compile(r'^(?:class|struct)\s+%s\b[^;{]*\{' % re.escape(cls), re.M)
        for f in self.files:
            m = pat.search(self.text[f])
            if m:
                return f, m
        return None, None

    def body(self, cls):
        f, m = self.find(cls)
        if not f:
            return None, None, None
        t = self.text[f]
        depth, i = 1, m.end()
        while i < len(t) and depth:
            depth += {'{': 1, '}': -1}.get(t[i], 0)
            i += 1
        return f, t[m.end():i - 1], t

    def members(self, cls):
        f, body, full = self.body(cls)
        if f is None:
            return f, [], None
        asserts = {}
        for m in re.finditer(r'offsetof\(\s*%s\s*,\s*(\w+)\s*\)\s*==\s*(0x[0-9A-Fa-f]+|\d+)' % re.escape(cls), full):
            asserts[m.group(1)] = int(m.group(2), 0)
        out = []
        depth = 0
        for line in body.splitlines():
            code = line.split('//')[0]
            stripped = code.strip()
            if depth == 0 or True:
                if '(' not in code and not re.match(r'^\s*(virtual|typedef|friend|static|using|public|private|protected)', code):
                    m = _DECL.match(line)
                    if m and m.group(3) not in ('const',):
                        ctype = (m.group(1) + m.group(2)).strip()
                        name = m.group(3)
                        cnt = m.group(4)
                        c = None
                        if cnt is not None:
                            try:
                                c = int(cnt, 0)
                            except ValueError:
                                c = None
                        om = _OFFCOMMENT.search(line)
                        off = asserts.get(name)
                        if off is None and om:
                            off = int(om.group(1), 16)
                        if off is not None:
                            mb = Member(name, ctype, c if cnt is not None else 1, off, line.strip())
                            mb.array = cnt is not None
                            out.append(mb)
            depth += code.count('{') - code.count('}')
        seen, uniq = set(), []
        for mb in sorted(out, key=lambda x: x.off):
            if mb.off in seen:
                continue
            seen.add(mb.off)
            uniq.append(mb)
        return f, uniq, asserts

    def type_size(self, ctype):
        t = ctype.replace('const ', '').strip()
        if t.endswith('*'):
            return 4
        t = re.sub(r'^(struct|class)\s+', '', t)
        return self.sizes.get(t)


# ---------------------------------------------------------------------------------------------
# Data and per-class driver
# ---------------------------------------------------------------------------------------------

class Data(object):
    def __init__(self):
        d = os.path.join(REPO, 'scripts', 'data')
        self.ctors = json.load(open(os.path.join(d, 'ctor_field_offsets.json')))['constructors']
        self.sizes = {c['class']: c for c in json.load(open(os.path.join(d, 'class_sizes.json')))['classes']
                      if c.get('class')}
        self.rtti = {v['demangled_name']: v for v in json.load(open(os.path.join(d, 'rtti_classes.json')))['classes'].values()}
        b = json.load(open(os.path.join(d, 'symbol_bindings.json')))
        self.readers = {}
        for sym, addr in b.items():
            m = _READER.match(sym)
            if m:
                self.readers[int(addr, 16) if isinstance(addr, str) else addr] = m.group(1)


def ctor_evidence(data, cls):
    out = []
    for c in data.ctors:
        if c.get('class') != cls:
            continue
        for f in c['fields']:
            kinds = f['kinds']
            if 'vptr' in kinds:
                continue
            at = int(f['proofs'][0]['at'], 16) if f['proofs'] else None
            out.append(Ev(f['offset'], f['width'], 'ctor', '/'.join(kinds) + ' in ctor ' + c['constructor'], at=at,
                          typ='sub-object' if 'lea' in kinds else None))
    return out


def sizeof_class(data, hidx, cls):
    c = data.sizes.get(cls)
    if c:
        return c['sizeof']
    return hidx.sizes.get(cls)


def vtable_slot(binary, data, cls, slot):
    r = data.rtti.get(cls)
    if not r:
        return None
    for lc in r['locators']:
        if lc['base_offset'] == 0 and lc['vtable_va']:
            return binary.dword(int(lc['vtable_va'], 16) + 4 * slot)
    return None


def class_evidence(binary, data, hidx, cls, own_start=0):
    evs, notes = [], []
    evs += ctor_evidence(data, cls)
    swz = binary.dword(SWIZZLE_VTABLE + 4 * SWIZZLE_SLOT)
    chain = (data.rtti.get(cls) or {}).get('base_chain', [])
    sink_cache = {}

    def sink_size(t):
        if t not in sink_cache:
            sink_cache[t] = _sink_size(binary, t)
        return sink_cache[t]

    def fn(slot, mode):
        a = vtable_slot(binary, data, cls, slot)
        if not a:
            return None, None
        return a, binary.func(a)

    a, ins = fn(SLOT_LOAD, 'stack')
    if ins:
        evs += extract_swizzle(ins, swz)
        evs += extract_streams(ins, 'stack', swz)
        notes.append('Load 0x%X' % a)
    a, ins = fn(SLOT_SAVE, 'stack')
    if ins:
        evs += extract_streams(ins, 'stack')
        notes.append('Save 0x%X' % a)
    a, ins = fn(SLOT_CRC, 'ecx')
    if ins:
        evs += extract_crc(ins, sink_size)
        notes.append('Crc 0x%X' % a)
    if 'AbstractTypeClass' in chain:
        a, ins = fn(SLOT_INI, 'ecx')
        if ins:
            evs += extract_ini(ins, binary.cstring, lambda t: data.readers.get(t))
            notes.append('ReadINI 0x%X' % a)
    return [e for e in evs if e.off is not None and e.off >= own_start], notes


def _sink_size(binary, t):
    try:
        ins = binary.func(t, 0x30)
    except Exception:
        return None
    last = None
    for i in ins[:12]:
        if i.mn == 'push' and i.ops:
            v = imm(i.ops[0])
            if v is not None and 1 <= v <= 16:
                last = v
        if i.mn == 'call':
            return last
        if i.mn == 'ret':
            break
    return None


def propose(cls, evs, members, size, own_start):
    """Merge evidence into per-offset proposals and diff against the header members."""
    members = list(members)
    for k, m in enumerate(members):
        nxt = members[k + 1].off if k + 1 < len(members) else size
        m.span = (nxt - m.off) if nxt is not None else None
    by_off = {}
    for e in evs:
        by_off.setdefault(e.off, []).append(e)
    offs = sorted(by_off)
    gaps = []
    for m in members:
        if m.span is None:
            continue
        if m.is_placeholder() or m.size_known and m.size < m.span:
            gaps.append((m.off, m.off + m.span, m.name, 'placeholder' if m.is_placeholder() else 'hole'))
    return by_off, offs, gaps


def field_proposals(by_off, offs, lo, hi):
    out = []
    inside = [o for o in offs if lo <= o < hi]
    for k, o in enumerate(inside):
        evs = by_off[o]
        nxt = inside[k + 1] if k + 1 < len(inside) else min(hi, o + 4)
        width = max([e.width for e in evs if e.width] or [0])
        span = nxt - o
        if width == 0 or width > span:
            width = span if span in (1, 2, 4, 8) else (min(span, 4) if span >= 4 else span)
        sources = sorted(set(e.source for e in evs))
        key = next((e.key for e in evs if e.key), None)
        typ = next((e.typ for e in evs if e.typ and e.source == 'ini'), None)
        ptr = any(e.pointer for e in evs)
        sub = any(e.typ == 'sub-object' for e in evs)
        if typ and typ.startswith('Read') and not ptr:
            ctype = typ
        elif ptr:
            ctype = 'void*'
        elif sub:
            ctype = 'sub-object (>= %d bytes)' % span
        elif typ and typ in ('int', 'bool', 'double', 'float'):
            ctype = typ
        else:
            ctype = {1: 'unsigned char', 2: 'short', 4: 'int', 8: 'double'}.get(width, 'unsigned char[%d]' % span)
        name = ident(key) if key else 'unknown_%X' % o
        out.append({'off': o, 'size': width if not sub else span, 'type': ctype, 'name': name,
                    'sources': sources,
                    'evidence': ['%s %s%s' % (e.source, e.detail, ' @0x%X' % e.at if e.at else '') for e in evs[:4]]})
    return out


def ident(s):
    s = re.sub(r'[^0-9A-Za-z_]', '_', s)
    return s if re.match(r'[A-Za-z_]', s) else '_' + s


def analyse(cls, binary, data, hidx):
    f, members, _ = hidx.members(cls)
    size = sizeof_class(data, hidx, cls)
    if members:
        own_start = members[0].off
    else:
        base = ((data.rtti.get(cls) or {}).get('base_chain') or [None, None])[1:2]
        own_start = sizeof_class(data, hidx, base[0]) or 0 if base else 0
    for m in members:
        sz = hidx.type_size(m.ctype)
        m.size_known = sz is not None
        if sz is not None:
            m.size = sz * (m.count if getattr(m, 'array', False) and m.count else 1)
            if getattr(m, 'array', False) and m.count is None:
                m.size_known = False
    evs, notes = class_evidence(binary, data, hidx, cls, own_start)
    by_off, offs, gaps = propose(cls, evs, members, size, own_start)
    rep = {'class': cls, 'header': os.path.relpath(f, REPO) if f else None, 'sizeof': size,
           'own_start': own_start, 'sources': notes, 'gaps': [], 'covered_offsets': len(offs)}
    gap_bytes = touched = 0
    fillable = 0
    for lo, hi, name, kind in gaps:
        props = field_proposals(by_off, offs, lo, hi)
        rep['gaps'].append({'name': name, 'kind': kind, 'lo': lo, 'hi': hi, 'proposals': props})
        gap_bytes += hi - lo
        touched += sum(p['size'] for p in props)
        fillable += 1 if props else 0
    rep['gap_count'] = len(gaps)
    rep['gap_bytes'] = gap_bytes
    rep['gap_bytes_with_evidence'] = min(touched, gap_bytes)
    rep['gaps_fillable'] = fillable
    # evidence offsets that no header member covers (not inside any member span)
    declared = [(m.off, m.off + (m.span or 0)) for m in members]
    unmapped = [o for o in offs if not any(a <= o < b for a, b in declared)]
    rep['unmapped_offsets'] = unmapped[:40]
    # named members whose header type disagrees with the evidence
    conflicts = []
    for m in members:
        if m.is_placeholder() or m.off not in by_off:
            continue
        es = by_off[m.off]
        keys = sorted(set(e.key for e in es if e.key))
        if keys and ident(keys[0]).lower() != m.name.lower():
            conflicts.append({'off': m.off, 'header_name': m.name, 'ini_key': keys[0]})
        if any(e.pointer for e in es) and '*' not in m.ctype and m.ctype in PRIM:
            conflicts.append({'off': m.off, 'header_name': m.name, 'header_type': m.ctype, 'note': 'swizzled pointer'})
    rep['conflicts'] = conflicts
    # how each evidence source lines up with the header it is proposing against
    starts = set(m.off for m in members)
    agree = {}
    for e in evs:
        a = agree.setdefault(e.source, {'exact': 0, 'interior': 0, 'outside': 0})
        if e.off in starts:
            a['exact'] += 1
        elif any(x <= e.off < y for x, y in declared):
            a['interior'] += 1
        else:
            a['outside'] += 1
    rep['agreement'] = agree
    rep['members_total'] = len(members)
    rep['members_named'] = sum(1 for m in members if not m.is_placeholder())
    return rep


def text_report(rep, show_all=False):
    L = ['%s  (%s, sizeof %s, own range from 0x%X; evidence: %s)' % (
        rep['class'], rep['header'], hex(rep['sizeof']) if rep['sizeof'] else '?', rep['own_start'],
        ', '.join(rep['sources']) or 'ctor only')]
    L.append('  members %d (%d named); gap spans %d covering 0x%X bytes; fillable %d; bytes with evidence 0x%X' % (
        rep['members_total'], rep['members_named'], rep['gap_count'], rep['gap_bytes'], rep['gaps_fillable'],
        rep['gap_bytes_with_evidence']))
    for g in rep['gaps']:
        if not g['proposals'] and not show_all:
            continue
        L.append('  gap %s [%s] 0x%X..0x%X' % (g['name'], g['kind'], g['lo'], g['hi']))
        for p in g['proposals']:
            L.append('    +0x%X  %-3d  %-24s %-28s [%s]' % (p['off'], p['size'], p['type'], p['name'], ','.join(p['sources'])))
            if show_all:
                for e in p['evidence']:
                    L.append('        ' + e)
    L.append('  evidence vs header members: ' + '; '.join('%s exact %d interior %d outside %d' % (
        k, v['exact'], v['interior'], v['outside']) for k, v in sorted(rep['agreement'].items())))
    for c in rep['conflicts'][:20]:
        L.append('  note: %s' % json.dumps(c))
    if rep['unmapped_offsets']:
        L.append('  evidence offsets outside any header member: ' + ' '.join('0x%X' % o for o in rep['unmapped_offsets']))
    return '\n'.join(L)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n\n')[0] if __doc__ else '')
    ap.add_argument('classes', nargs='+')
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--all', action='store_true', help='show evidence lines and empty gaps')
    ap.add_argument('--summary', action='store_true', help='one coverage line per class')
    ap.add_argument('--classcheck', metavar='DIR', help='directory holding the proposed classcheck.py; runs it per class '
                    'to validate the header (sizeof, offsets, ctor stores, vtable slots) beside the proposals')
    a = ap.parse_args(argv)
    if a.classcheck:
        import subprocess
        for c in a.classes:
            r = subprocess.run([sys.executable, os.path.join(a.classcheck, 'classcheck.py'), c],
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
            print('== classcheck %s (exit %d)\n%s' % (c, r.returncode, r.stdout[-1500:]))
    binary = binfn.Binary()
    data = Data()
    hidx = HeaderIndex()
    reps = [analyse(c, binary, data, hidx) for c in a.classes]
    if a.json:
        print(json.dumps(reps, indent=1))
    elif a.summary:
        for r in reps:
            print('%-16s gaps %3d  fillable %3d  gap bytes 0x%X  with evidence 0x%X  (%s)' % (
                r['class'], r['gap_count'], r['gaps_fillable'], r['gap_bytes'], r['gap_bytes_with_evidence'],
                ', '.join(r['sources'])))
    else:
        for r in reps:
            print(text_report(r, a.all))
    return 0


if __name__ == '__main__':
    sys.exit(main())
