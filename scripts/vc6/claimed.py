#!/usr/bin/env python3
"""claimed.py 0xADDR [0xADDR ...] — is this retail address already taken?

Run this before drafting anything. A bare grep is not enough: annotations in
this tree are written both zero-padded and not (0x004F42D0 and 0x4F42D0), in
upper and lower case, so a grep for one spelling silently misses the other.
That exact miss produced a duplicate body for 0x4F42D0, drafted as a
"SessionInputCursor" setter in one translation unit while MapClass already
owned it in another.

Checks all four sources an address can be claimed by:
  * scripts/data/match_manifest.json          -- the matched/annotated record
  * match/**/*.cpp and *.c            -- a real body (parts of the engine are C)
  * match/**/*.h                      -- a declaration or stand-in
  * the Ghidra function list, if exported, for the retail name

Exit status is 1 if any address is claimed, so it can gate a script.
"""
import glob
import json
import os
import re
import sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
ROOT = os.path.normpath(ROOT)


def spellings(addr):
    """Every way this tree writes one address."""
    out = set()
    for width in (0, 6, 8):
        body = ('%0*x' % (width, addr)) if width else ('%x' % addr)
        out.add('0x' + body.lower())
        out.add('0x' + body.upper())
    return out


def main(argv):
    if not argv:
        print(__doc__.strip(), file=sys.stderr)
        return 2

    sources = []
    for ext in ('*.cpp', '*.c', '*.h'):
        sources += glob.glob(os.path.join(ROOT, 'match', '**', ext), recursive=True)
    texts = {p: open(p, errors='ignore').read() for p in sources}

    manifest = {}
    man_path = os.path.join(ROOT, 'scripts', 'data', 'match_manifest.json')
    if os.path.exists(man_path):
        for e in json.load(open(man_path)):
            manifest[int(e['addr'], 16)] = e

    any_claimed = False
    for raw in argv:
        addr = int(raw, 16)
        forms = spellings(addr)
        print('%#010x' % addr)

        e = manifest.get(addr)
        if e:
            any_claimed = True
            print('  manifest  %s  %s  %s%%' % (e['tu'], e.get('name', ''), e.get('pct')))

        for path, text in sorted(texts.items()):
            hits = [n + 1 for n, line in enumerate(text.splitlines())
                    if any(f in line for f in forms)]
            if not hits:
                continue
            rel = os.path.relpath(path, ROOT)
            # A callee stand-in is marked "(decl; reloc)" and is not a claim on
            # the address -- only a definition is.
            kind = 'declares' if rel.endswith('.h') else 'BODY'
            for n in hits:
                line = text.splitlines()[n - 1].strip()
                if 'decl;' in line:
                    kind = 'decl-only'
                print('  %-9s %s:%d  %s' % (kind, rel, n, line[:90]))
            if kind == 'BODY':
                any_claimed = True

        if not e and not any(any(f in t for f in forms) for t in texts.values()):
            print('  unclaimed')

    return 1 if any_claimed else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
