#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads only link outputs under build-vc6/.
"""RTTI bytes adopted from the project objects versus left as retail fill, with the rejection reasons.

Usage: scripts/vc6/rtti_report.py LINKDIR      (a link_m1.py --hybrid --source-data output directory)
"""
import collections
import json
import re
import sys
from pathlib import Path


def piece_type(name):
    m = re.match(r"\?\?_R(\d)", name)
    return "R" + m.group(1) if m else None


def report(linkdir):
    stubs = Path(linkdir) / "stubs"
    placed = json.loads((stubs / "data_placed.json").read_text())
    rejected = json.loads((stubs / "data_rejected.json").read_text())
    adopted = collections.defaultdict(lambda: [0, 0])
    for p in placed:
        t = piece_type(p["names"][0])
        if p["kind"] == "rtti" and t:
            adopted[t][0] += 1
            adopted[t][1] += p["size"]
    refused = collections.defaultdict(lambda: [0, 0])
    why, why_bytes, example = collections.Counter(), collections.Counter(), {}
    seen = set()
    for r in rejected:
        t = piece_type(r["name"])
        if r["kind"] != "rtti" or not t or r["name"] in seen:
            continue
        seen.add(r["name"])
        refused[t][0] += 1
        refused[t][1] += r["size"]
        w = re.sub(r"0x[0-9A-F]+|\S*@pin\S*", "N", r["why"])
        w = re.sub(r"relocation target \S+", "relocation target X", w)
        why[w] += 1
        why_bytes[w] += r["size"]
        example.setdefault(w, r["name"])
    return {"adopted": dict(adopted), "rejected": dict(refused),
            "reasons": [(w, n, why_bytes[w], example[w]) for w, n in why.most_common()]}


if __name__ == "__main__":
    rep = report(sys.argv[1])
    for key in ("adopted", "rejected"):
        total = sum(v[1] for v in rep[key].values())
        print(f"{key}: {sum(v[0] for v in rep[key].values())} symbols, {total} bytes  "
              + "  ".join(f"{t}:{v[0]}/{v[1]}" for t, v in sorted(rep[key].items())))
    for w, n, b, ex in rep["reasons"][:10]:
        print(f"  {n:5d} symbols {b:7d} bytes  {w}  (e.g. {ex})")
