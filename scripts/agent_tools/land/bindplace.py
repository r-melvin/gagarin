#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""bindplace.py: fail when a bound project body is linked away from its binding's address.

    bindplace.py M1.map BINDINGS.json

Strict verify resolves a relocation through the binding, so a symbol can be bound to a retail address
while the link places that symbol's own body somewhere else. The map is read, not placement.json: a stray
body sits outside the ordered pieces. Library objects are skipped (retail aliases). Exit 1 lists each.
"""
import json
import re
import sys

PUBLIC = re.compile(r"^ [0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(?:. )*(\S+)$")


def misplaced(map_text, bindings):
    """[(sym, linked_va, bound_va, obj)] of project symbols linked away from their binding."""
    out = []
    for line in map_text.splitlines():
        m = PUBLIC.match(line)
        if not m or m.group(1) not in bindings or m.group(3).startswith("libcmt_"):
            continue
        va, bound = int(m.group(2), 16), int(bindings[m.group(1)], 16)
        if va != bound:
            out.append((m.group(1), va, bound, m.group(3)))
    return out


def main(argv=None):
    mapfile, bindings = argv if argv is not None else sys.argv[1:]
    bad = misplaced(open(mapfile, encoding="latin-1").read(), json.load(open(bindings)))
    for sym, va, bound, obj in bad:
        print("%s (%s) linked at 0x%X, bound to 0x%X" % (sym, obj, va, bound))
    print("%d bound project symbols away from their binding" % len(bad))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
