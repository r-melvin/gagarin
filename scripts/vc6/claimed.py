#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""claimed.py 0xADDR [0xADDR ...] — is this retail address already taken?

Run this before drafting anything. A bare grep is not enough: annotations in
this tree are written both zero-padded and not (0x004F42D0 and 0x4F42D0), in
upper and lower case, so a grep for one spelling silently misses the other.
That exact miss produced a duplicate body for 0x4F42D0, drafted as a
"SessionInputCursor" setter in one translation unit while MapClass already
owned it in another.

Claims come from the manifest or the same source FUNCTION annotations used by
check_duplicates.py. Header declarations, callee declarations and prose references
are displayed for context but do not claim a body.

Exit status is 1 if any address is claimed, so it can gate a script.
"""
import glob
import json
import os
import re
import sys

from check_duplicates import ANNOT, source_files

ADDRESS = re.compile(r"\b0x[0-9a-f]+\b", re.I)

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
ROOT = os.path.normpath(ROOT)


def line_kind(path, line, addr):
    """Classify an exact numeric address mention using the annotation gate."""
    if not any(int(m.group(), 16) == addr for m in ADDRESS.finditer(line)):
        return None
    marker = ANNOT.match(line.lstrip() if path.lower().endswith('.h') else line)
    if marker and int(marker.group(1), 16) == addr:
        if 'decl;' in marker.group(2):
            return 'decl-only'
        return 'declares' if path.lower().endswith('.h') else 'BODY'
    return 'reference'


def main(argv):
    if not argv:
        print(__doc__.strip(), file=sys.stderr)
        return 2

    sources = []
    sources = source_files(('.cpp', '.c', '.asm', '.h'), ROOT)
    texts = {}
    for path in sources:
        with open(path, errors='ignore') as stream:
            texts[path] = stream.read().splitlines()

    manifest = {}
    man_path = os.path.join(ROOT, 'scripts', 'data', 'match_manifest.json')
    if os.path.exists(man_path):
        with open(man_path) as stream:
            for e in json.load(stream):
                manifest[int(e['addr'], 16)] = e

    any_claimed = False
    for raw in argv:
        addr = int(raw, 16)
        address_claimed = False
        print('%#010x' % addr)

        e = manifest.get(addr)
        if e:
            address_claimed = True
            print('  manifest  %s  %s  %s%%' % (e['tu'], e.get('name', ''), e.get('pct')))

        for path, lines in sorted(texts.items()):
            rel = os.path.relpath(path, ROOT)
            for n, line in enumerate(lines, 1):
                kind = line_kind(rel, line, addr)
                if kind is None:
                    continue
                print('  %-9s %s:%d  %s' % (kind, rel, n, line.strip()[:90]))
                if kind == 'BODY':
                    address_claimed = True
        if not address_claimed:
            print('  unclaimed')
        any_claimed |= address_claimed

    return 1 if any_claimed else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
