#!/usr/bin/env python3
"""Find the __FILE__ string and its referencing push sites for each assert-named TU."""
import csv, json, struct, sys, os
BIN = os.environ.get('GAMEMD_BINARY', '')
d = open(BIN, 'rb').read()
pe = struct.unpack_from('<I', d, 0x3c)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]; opt = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
secs = []
for i in range(nsec):
    h = pe + 24 + opt + i * 40
    va, rsz, rptr = struct.unpack_from('<I4xII', d, h + 8)[0], *struct.unpack_from('<II', d, h + 16)
    vsz, va = struct.unpack_from('<II', d, h + 8)
    secs.append((va, vsz, rptr, rsz))
def off2va(o):
    for va, vsz, rp, rs in secs:
        if rp <= o < rp + rs: return base + va + o - rp
def va2off(v):
    for va, vsz, rp, rs in secs:
        if base + va <= v < base + va + rs: return v - base - va + rp
out = {}
for t in csv.DictReader(open(os.environ.get('GAG_TUMAP') or os.path.join(os.environ.get('GAG_SCRATCH_ROOT') or os.path.join(os.path.dirname(os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..'))), 'gagarin-scratch'), 'tumap2/tu_map_v2.csv'))):
    if t['name_confidence'] != 'assert': continue
    name = t['name_or_bound']
    lo, hi = int(t['text_lo'], 16), int(t['text_hi'], 16)
    hits = []; i = -1
    while True:
        i = d.find(b'\\' + name.encode() + b'\0', i + 1)
        if i < 0: break
        st = d.rfind(b'\0', 0, i) + 1
        hits.append(off2va(st))
    sites = []
    for s in hits:
        pat = b'\x68' + struct.pack('<I', s); j = va2off(lo)
        end = va2off(hi)
        while True:
            j = d.find(pat, j, end + 1)
            if j < 0: break
            sites.append(off2va(j)); j += 1
    out[t['tu_id']] = dict(name=name, strings=[hex(h) for h in hits], push_sites=[hex(s) for s in sites])
    print(t['tu_id'], name, [hex(h) for h in hits], len(sites), [hex(s) for s in sites[:3]])
json.dump(out, open(sys.argv[1], 'w'), indent=1)
