#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling (measurement only).
"""List the globals/literals that matched code of one TU reaches but nothing defines (from data_census raw JSON).
Usage: data_census_tu.py RAW.json match/ai/team_type_class_body.cpp"""
import bisect
import collections
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
raw = json.loads(Path(sys.argv[1]).read_text())
want = sys.argv[2]
plan_path = Path(sys.argv[3]) if len(sys.argv) > 3 else ROOT / "build-vc6/base-m3/stubs/plan.json"
plan = json.loads(plan_path.read_text())
manifest = json.loads((ROOT / "scripts/data/match_manifest.json").read_text())
tu_of = {r["sym"]: r["tu"] for r in manifest}
m = sorted((int(p["addr"], 16), int(p["addr"], 16) + int(p["len"], 16), p["symbol"]) for p in plan["placed"] if p["kind"] == "matched")
ms = [x[0] for x in m]
msites = {int(k): v for k, v in raw["_msites"].items()}
def tus_for(va, size):
    c = collections.Counter()
    for k in range(va, va + size):
        for site in msites.get(k, ()):
            i = bisect.bisect_right(ms, site) - 1
            if i >= 0 and m[i][0] <= site < m[i][1]:
                c[tu_of.get(m[i][2], "?")] += 1
    return c
for it in raw["_glob_m"] + [dict(x, region="lit") for x in raw["_lit_m"]]:
    c = tus_for(it["va"], min(it["size"], 1024))
    if c and c.most_common(1)[0][0] == want:
        print("0x%X" % it["va"], it["size"], it["region"], it.get("kind", it.get("label")), it.get("ops", ""), dict(c))
