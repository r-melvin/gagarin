#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""placement_diff.py: diff two placement.json files (link_m1.py --hybrid) and classify each changed piece.

    placement_diff.py OLD/placement.json NEW/placement.json [--json OUT] [--limit N]

Pieces are keyed by (section, VA). Classes:
  project->fill   piece in OLD only (the project object no longer owns those bytes)
  fill->project   piece in NEW only (newly project-placed)
  rename          same address and size, different symbol name
  size            same address, different size (name may or may not change)
  origin          same address, size and name, project <-> library
Each class is counted by pieces and bytes; ??_R3 pieces (RTTI class hierarchy descriptors, which
move in bulk with class edits) are tagged and reported separately, and "project bytes" is given
with and without them. Exit 0 always; this is a report.
"""
import argparse
import json
import sys


def load(path):
    pieces = json.load(open(path))["pieces"]
    return {(p[0], p[1]): (p[2], p[3], p[4]) for p in pieces}


def is_r3(name):
    return name.startswith("??_R3")


def project_bytes(pl):
    """(all project bytes, project bytes excluding ??_R3)"""
    tot = sum(s for s, o, n in pl.values() if o == "project")
    r3 = sum(s for s, o, n in pl.values() if o == "project" and is_r3(n))
    return tot, tot - r3


def classify(old, new):
    """[{class, section, va, old, new, r3}] for every piece that differs; old/new = (size, origin, name) or None."""
    out = []
    for key in sorted(set(old) | set(new), key=lambda k: (k[0], k[1])):
        o, n = old.get(key), new.get(key)
        if o == n:
            continue
        if o is None:
            cls = "fill->project" if n[1] == "project" else "fill->library"
        elif n is None:
            cls = "project->fill" if o[1] == "project" else "library->fill"
        elif o[0] != n[0]:
            cls = "size"
        elif o[2] != n[2]:
            cls = "rename"
        else:
            cls = "origin"
        out.append(dict(cls=cls, section=key[0], va=key[1], old=o, new=n,
                        r3=any(x and is_r3(x[2]) for x in (o, n))))
    return out


def summarize(old, new):
    ch = classify(old, new)
    classes = {}
    for c in ch:
        s = classes.setdefault(c["cls"], dict(pieces=0, bytes=0, r3_pieces=0, r3_bytes=0))
        b = abs((c["new"] or (0,))[0] - (c["old"] or (0,))[0]) if c["cls"] == "size" else max((c["old"] or (0,))[0], (c["new"] or (0,))[0])
        s["pieces"] += 1
        s["bytes"] += b
        if c["r3"]:
            s["r3_pieces"] += 1
            s["r3_bytes"] += b
    po, pon = project_bytes(old), project_bytes(new)
    return dict(changes=ch, classes=classes,
                project_bytes=dict(old=po[0], new=pon[0], delta=pon[0] - po[0]),
                project_bytes_excl_r3=dict(old=po[1], new=pon[1], delta=pon[1] - po[1]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("old")
    ap.add_argument("new")
    ap.add_argument("--json")
    ap.add_argument("--limit", type=int, default=10, help="example pieces to list per class (default 10)")
    a = ap.parse_args(argv)
    r = summarize(load(a.old), load(a.new))
    for cls, s in sorted(r["classes"].items()):
        print("%-14s %6d pieces %9d bytes  (??_R3: %d pieces %d bytes)" % (cls, s["pieces"], s["bytes"], s["r3_pieces"], s["r3_bytes"]))
        shown = 0
        for c in r["changes"]:
            if c["cls"] == cls and shown < a.limit:
                shown += 1
                print("    %s 0x%X  %s -> %s" % (c["section"], c["va"], c["old"], c["new"]))
    for k in ("project_bytes", "project_bytes_excl_r3"):
        v = r[k]
        print("%-22s old %d new %d delta %+d" % (k, v["old"], v["new"], v["delta"]))
    if a.json:
        json.dump(r, open(a.json, "w"), indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
