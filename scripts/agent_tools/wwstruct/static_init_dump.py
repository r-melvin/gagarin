#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Dump the static-initialiser symbols (_$E<n> initialisers, _$S<n> statics) of every object, and diff two builds.

  static_init_dump.py OBJDIR [--tu SUBSTR ...] [--json OUT]
  static_init_dump.py OBJDIR --against OTHER_OBJDIR [--tu SUBSTR ...]

The compiler numbers these per translation unit from its internal symbol counter, so including a different
header set, or merging TUs, renumbers them (the numbers are not part of the image, but their order and the
bytes behind them are the dynamic-initialisation order). The diff reports, per TU, symbols that were
renamed (same ordinal, different number), added, removed, or whose section bytes changed.
"""

import argparse
import json
import sys

import wwlib


def dump(objdir):
    out = {}
    for source, path in wwlib.object_paths(objdir).items():
        syms = wwlib.static_init_symbols(path)
        if syms:
            out[source] = sorted(syms, key=lambda s: (s["section"], s["offset"], s["name"]))
    return out


def diff(old, new):
    result = []
    for tu in sorted(set(old) | set(new)):
        a, b = old.get(tu, []), new.get(tu, [])
        if [(s["name"], s["digest"]) for s in a] == [(s["name"], s["digest"]) for s in b]:
            continue
        kinds = []
        if [s["name"] for s in a] != [s["name"] for s in b]:
            kinds.append("renumbered" if len(a) == len(b) else "count")
        if [s["digest"] for s in a] != [s["digest"] for s in b]:
            kinds.append("bytes")
        result.append({"tu": tu, "change": "+".join(kinds) or "order", "before": [s["name"] for s in a],
                       "after": [s["name"] for s in b]})
    return result


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("objdir")
    ap.add_argument("--against")
    ap.add_argument("--tu", action="append", default=[])
    ap.add_argument("--json")
    args = ap.parse_args(argv)
    keep = lambda d: {k: v for k, v in d.items() if not args.tu or any(t in k for t in args.tu)}
    new = keep(dump(args.objdir))
    if args.against:
        changes = diff(keep(dump(args.against)), new)
        for c in changes:
            print(f"{c['change']:20} {c['tu']}  {c['before']} -> {c['after']}")
        print(f"-- tus_changed={len(changes)}")
        payload = {"changes": changes}
    else:
        for tu, syms in sorted(new.items()):
            print(f"{tu}: " + " ".join(f"{s['name']}[{s['digest']}]" for s in syms))
        print(f"-- tus={len(new)} symbols={sum(len(v) for v in new.values())}")
        payload = {"tus": new}
    if args.json:
        with open(args.json, "w") as f:
            json.dump(payload, f, indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
