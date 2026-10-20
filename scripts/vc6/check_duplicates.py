#!/usr/bin/env python3
# check_duplicates.py — pre-commit invariant check over the annotation map.
#
# Two defects this catches, both of which break the reccmp gate rather than
# merely looking untidy:
#
#   * one retail address with a body in more than one translation unit (two
#     functions claiming the same address), which happened four times across
#     parallel sessions before this check existed;
#   * a manifest entry whose translation unit no longer carries the annotation,
#     left behind when a body is moved or deleted.
#
# Headers legitimately repeat their own TU's annotations, so only bodies in
# .cpp and .c files both count as a claim.
#
# Usage:  scripts/vc6/check_duplicates.py
# Exit 0 iff the annotation map is consistent.
import collections, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
# A claim is an annotation at column zero. Trailing prose after the address is
# common and harmless. Lines marked as a declaration annotate a callee defined
# elsewhere, so they are not claims; neither is an indented mention inside a
# provenance header.
ANNOT = re.compile(r'(?m)^// (?:FUNCTION|SYNTHETIC): GAMEMD (0x[0-9A-Fa-f]+)(.*)$')


def claims(text):
    for m in ANNOT.finditer(text):
        # The tree marks a callee declaration as "(decl; reloc)". Match that
        # exactly: a bare "decl" substring also occurs in "(__cdecl)".
        if 'decl;' in m.group(2):
            continue
        yield int(m.group(1), 16)


def main():
    owner = collections.defaultdict(set)
    # Both extensions: parts of the retail engine were compiled as C, not C++,
    # so a .c translation unit is a first-class claim on an address and must be
    # visible to this gate. Globbing only *.cpp would let a C TU silently
    # duplicate an address already owned by a C++ one.
    sources = []
    for ext in ('*.cpp', '*.c'):
        sources += glob.glob(os.path.join(ROOT, 'match', '**', ext), recursive=True)
    for path in sorted(sources):
        rel = os.path.relpath(path, ROOT)
        with open(path, errors='ignore') as source:
            text = source.read()
        for addr in claims(text):
            owner[addr].add(rel)

    bad = 0
    for addr, tus in sorted(owner.items()):
        if len(tus) > 1:
            bad += 1
            print("DUPLICATE  %#08x claimed by: %s" % (addr, ', '.join(sorted(tus))))

    man_path = os.path.join(ROOT, 'scripts', 'data', 'match_manifest.json')
    if os.path.exists(man_path):
        with open(man_path) as manifest:
            entries = json.load(manifest)
        for e in entries:
            addr = int(e['addr'], 16)
            if e['tu'] not in owner.get(addr, ()):
                bad += 1
                print("ORPHAN     %s %#08x is in the manifest but not annotated there"
                      % (e['tu'], addr))

    print("%d addresses with bodies, %d problems" % (len(owner), bad))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
