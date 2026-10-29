#!/usr/bin/env python3
"""Per-function byte identity across a TU move.

  identity.py BASE_OBJS NEW_OBJS BASE_MANIFEST NEW_MANIFEST [--all-touched]

For every manifest row whose `tu` changed (and, with --all-touched, every row of
a TU that changed or was rewritten), the row's code section in the base object
(old TU) must equal the one in the new object (new TU): same bytes and same
relocation list (offset, type, target), with compiler-numbered local labels
($SGnnn, $Lnnn, ...) normalised. Rows new in NEW_MANIFEST are listed, not
compared. Exit 1 on any difference or missing section.
"""
import json, os, re, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'land'))
import sectioncmp

LOCAL = re.compile(r'^\$[A-Za-z]+\d+$')
_cache = {}


def sections(objdir, tu):
    p = os.path.join(objdir, tu[:-4] + '.obj')
    if p not in _cache:
        if not os.path.exists(p):
            _cache[p] = None
        else:
            out = {}
            for k, (h, rel) in sectioncmp.coff(p).items():
                sn, _, sym = k.partition('|')
                sym = sym.split('#')[0]
                if sn.startswith('.text') and sym:
                    rel = tuple((o, '$L' if LOCAL.match(n) else n, t) for o, n, t in rel)
                    out.setdefault(sym, (h, rel))
            _cache[p] = out
    return _cache[p]


def main():
    bo, no, bm, nm = sys.argv[1:5]
    only = None
    if os.environ.get('TUMIG_ONLY'):
        only = {int(x, 16) for x in open(os.environ['TUMIG_ONLY']).read().split()}
    touched_files = set(sys.argv[6:]) if len(sys.argv) > 6 else set()
    base = {int(r['addr'], 16): r for r in json.load(open(bm))}
    new = {int(r['addr'], 16): r for r in json.load(open(nm))}
    bad, ok, added = [], 0, []
    for a, r in sorted(new.items()):
        b = base.get(a)
        if b is None:
            added.append(hex(a))
            continue
        if only is not None and a not in only:
            continue
        if b['tu'] == r['tu'] and b['tu'] not in touched_files:
            continue
        if b['sym'] != r['sym']:
            bad.append((hex(a), 'symbol changed', b['sym'], r['sym']))
            continue
        x = sections(bo, b['tu'])
        y = sections(no, r['tu'])
        if x is None or y is None:
            bad.append((hex(a), 'object missing', b['tu'], r['tu']))
            continue
        sx, sy = x.get(r['sym']), y.get(r['sym'])
        if sx is None and sy is None:
            print("  ABSENT-BOTH", hex(a), r["sym"]); ok += 1
            continue
        if sx != sy:
            bad.append((hex(a), 'differs' if sx and sy else 'section missing', b['tu'], r['tu'], r['sym']))
        else:
            ok += 1
    print('identity: %d identical, %d differ, %d new rows' % (ok, len(bad), len(added)))
    for x in bad:
        print('  DIFF', *x)
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
