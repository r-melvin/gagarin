#!/usr/bin/env python3
# SPDX-Provenance: own-binary-via-Ghidra
#
# vtable_slots.py — walk every RTTI-located vtable in the user's own retail
# gamemd.exe and list its slots, so functions reached only through a vtable
# (which Ghidra's call-following auto-analysis misses) become named targets.
#
#   vtable starts  -> scripts/data/rtti_classes.json (locator sweep)
#   slot contents  -> dwords read straight from the PE image
#
# A walk stops at the first dword that does not point into .text, or where the
# next vtable's locator pointer sits. A slot pointer shared with a base class's
# vtable is inherited: its owner is the most basic class that carries it.
#
# Usage: vtable_slots.py <gamemd.exe> <rtti_classes.json> <out.json>
#            [--ghidra procs.txt] [--manifest match_manifest.json] [--match DIR]

import argparse
import glob
import json
import os
import re
import struct
from collections import defaultdict

ANNOT = re.compile(r'// (?:FUNCTION|LIBRARY|STUB|TEMPLATE|SYNTHETIC): GAMEMD (0x[0-9A-Fa-f]+)')


def load_pe(path):
    b = open(path, 'rb').read()
    pe = struct.unpack_from('<I', b, 0x3C)[0]
    nsec = struct.unpack_from('<H', b, pe + 6)[0]
    optsz = struct.unpack_from('<H', b, pe + 20)[0]
    base = struct.unpack_from('<I', b, pe + 24 + 28)[0]
    secs = []
    for i in range(nsec):
        name, vsize, va, rsize, roff = struct.unpack_from('<8sIIII', b, pe + 24 + optsz + 40 * i)
        secs.append((name.rstrip(b'\0').decode(), base + va, vsize, roff, rsize))
    return b, secs


def reader(b, secs):
    def dword(va):
        for _, start, vsize, roff, rsize in secs:
            if start <= va < start + min(vsize, rsize) - 3:
                return struct.unpack_from('<I', b, roff + va - start)[0]
        return None

    def bytes_at(va, n):
        for _, start, vsize, roff, rsize in secs:
            if start <= va < start + rsize:
                o = roff + va - start
                return b[o:o + n]
        return b''
    return dword, bytes_at


def trivial(code):
    """Tag bodies that are shared defaults rather than real targets."""
    if code[:1] == b'\xC3':
        return 'ret'
    if code[:1] == b'\xC2':
        return 'ret_n'
    if code[:3] in (b'\x33\xC0\xC3', b'\x32\xC0\xC3'):
        return 'return_0'
    if code[:2] == b'\x33\xC0' and code[2:3] == b'\xC2':
        return 'return_0_n'
    if code[:1] == b'\xE9':
        return 'jmp_thunk'
    return None


def annotated(manifest, match_dir):
    known = set()
    if manifest:
        known |= {int(r['addr'], 16) for r in json.load(open(manifest))}
    if match_dir:
        for f in glob.glob(os.path.join(match_dir, '**', '*.c*'), recursive=True):
            for m in ANNOT.finditer(open(f, errors='ignore').read()):
                known.add(int(m.group(1), 16))
    return known


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('exe')
    ap.add_argument('rtti')
    ap.add_argument('out')
    ap.add_argument('--ghidra')
    ap.add_argument('--manifest')
    ap.add_argument('--match')
    a = ap.parse_args()

    b, secs = load_pe(a.exe)
    dword, bytes_at = reader(b, secs)
    text = next(s for s in secs if s[0] == '.text')
    in_text = lambda v: v is not None and text[1] <= v < text[1] + text[2]

    classes = json.load(open(a.rtti))['classes']
    tables = []  # (class, base_offset, vtable_va)
    for cls in classes.values():
        for loc in cls['locators']:
            if loc.get('vtable_va'):
                tables.append((cls, loc['base_offset'], int(loc['vtable_va'], 16)))
    # A vtable ends where another's locator pointer (vtable_va - 4) begins.
    stops = {va - 4 for _, _, va in tables}

    slot_users = defaultdict(list)  # target -> [(class, base_off, index)]
    vtables = []
    for cls, boff, va in sorted(tables, key=lambda t: t[2]):
        slots = []
        p = va
        while True:
            v = dword(p)
            if not in_text(v):
                break
            slots.append(v)
            slot_users[v].append((cls['demangled_name'], boff, len(slots) - 1))
            p += 4
            if p in stops:
                break
        vtables.append({'class': cls['demangled_name'], 'base_offset': boff,
                        'vtable_va': '0x%08X' % va, 'slots': ['0x%08X' % s for s in slots]})

    depth = {c['demangled_name']: c.get('num_base_classes', 1) for c in classes.values()}
    ghidra = set()
    if a.ghidra:
        ghidra = {int(l, 16) for l in open(a.ghidra) if l.strip()}
    known = annotated(a.manifest, a.match)

    targets = []
    for t, users in sorted(slot_users.items()):
        owner = min(users, key=lambda u: (depth.get(u[0], 99), u[0]))
        targets.append({
            'addr': '0x%08X' % t,
            'owner': owner[0], 'base_offset': owner[1], 'slot': owner[2],
            'users': len({u[0] for u in users}),
            'trivial': trivial(bytes_at(t, 4)),
            'in_ghidra': t in ghidra,
            'annotated': t in known,
        })

    new = [t for t in targets if not t['in_ghidra'] and not t['trivial']]
    open_ = [t for t in targets if not t['annotated'] and not t['trivial']]
    summary = {
        'vtables': len(vtables),
        'slots': sum(len(v['slots']) for v in vtables),
        'distinct_targets': len(targets),
        'trivial_targets': sum(1 for t in targets if t['trivial']),
        'not_in_ghidra': len(new),
        'unannotated': len(open_),
        'unannotated_not_in_ghidra': sum(1 for t in open_ if not t['in_ghidra']),
    }
    json.dump({'_meta': {'source': 'user-owned retail gamemd.exe', 'summary': summary},
               'vtables': vtables, 'targets': targets}, open(a.out, 'w'), indent=1)
    for k, v in summary.items():
        print('%-28s %d' % (k, v))


if __name__ == '__main__':
    main()
