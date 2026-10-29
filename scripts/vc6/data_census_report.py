#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling (measurement only).
"""Turn data_census.py's raw JSON into census.json, report numbers and the ranked worklist TSV.
Usage: data_census_report.py RAW.json LINKDIR OUT_DIR WORKLIST.tsv"""
import bisect
import collections
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
raw = json.loads(Path(sys.argv[1]).read_text())
link, outdir, tsv = Path(sys.argv[2]), Path(sys.argv[3]), Path(sys.argv[4])
plan = json.loads((link / "stubs/plan.json").read_text())
manifest = json.loads((ROOT / "scripts/data/match_manifest.json").read_text())
tu_of = {r["sym"]: r["tu"] for r in manifest}
m = sorted((int(p["addr"], 16), int(p["addr"], 16) + int(p["len"], 16), p["symbol"]) for p in plan["placed"] if p["kind"] == "matched")
ms = [x[0] for x in m]
msites = {int(k): v for k, v in raw["_msites"].items()}
def tu_for(va, size):
    c = collections.Counter()
    for k in range(va, va + size):
        for site in msites.get(k, ()):
            i = bisect.bisect_right(ms, site) - 1
            if i >= 0 and m[i][0] <= site < m[i][1]:
                c[tu_of.get(m[i][2], "?")] += 1
    return c.most_common(1)[0][0] if c else None
tus = collections.defaultdict(lambda: collections.Counter())
for r in raw["_lit_m"]:
    t = tu_for(r["va"], r["size"])
    tus[t]["lit_" + r["kind"] + "_n"] += 1
    tus[t]["lit_" + r["kind"] + "_bytes"] += r["size"]
for it in raw["_glob_m"]:
    t = tu_for(it["va"], it["size"])
    k = it["region"].strip(".") + ("_notadopted" if it["group"].startswith("defined") else "")
    tus[t]["glob_%s_n" % k] += 1
    tus[t]["glob_%s_bytes" % k] += min(it["size"], 1024)   # sizes are distances to the next referenced address: cap them
rows = []
def add(item, bytes_, fix, effort, kind, extra=None):
    rows.append({"item": item, "bytes": bytes_, "fix": fix, "effort": effort, "kind": kind, **(extra or {})})
V = raw["vtables"]
for r in V["rejected_rows"]:
    fx = collections.Counter(f["fix"] for f in r["fixes"])
    eff = 1 + (fx.get("override_matched", 0) > 0) + 2 * (fx.get("recover_function", 0) > 0) + (fx.get("find_address", 0) > 0) + (fx.get("bind_ambiguous", 0) > 0)
    why = "; ".join("%d x %s" % (n, k) for k, n in sorted(fx.items()))
    detail = ", ".join("slot%d %s -> %s%s" % (f.get("slot", -1), f.get("name", "")[:40], f.get("Y"), "(%s)" % f["Y_matched_as"][:30] if f.get("Y_matched_as") else "") for f in r["fixes"][:4])
    add("vtable " + r["name"][:80], r["bytes"], why + " | " + detail + " | " + r["reason"][:60], eff, "vtable_rejected",
        {"slots_to_fix": r["bad_slots"], "bytes_per_slot": round(r["bytes"] / max(1, r["bad_slots"]), 1)})
for r in V["no_candidate"]:
    eff = 2 if r["unmatched_slots"] == 0 else 3 if r["unmatched_slots"] <= 2 else 4
    add("vtable(no TU defines it) %s @%s" % (r["class"], r["va"]), r["bytes"],
        "no compiled definition; %d of %d slots point at unmatched functions (%d code bytes)" % (r["unmatched_slots"], r["slots"], r["unmatched_code_bytes"]), eff, "vtable_nodef",
        {"slots_to_fix": max(1, r["unmatched_slots"]), "bytes_per_slot": round(r["bytes"] / max(1, r["unmatched_slots"]), 1)})
for t, c in tus.items():
    lit = c["lit_string_bytes"] + c["lit_float_bytes"]
    gl = c["glob_data_bytes"] + c["glob_bss_bytes"] + c["glob_rdata_bytes"]
    n = sum(v for k, v in c.items() if k.endswith("_n"))
    if lit + gl:
        add("TU " + str(t), lit + gl, "define the %d literals/globals matched code here reaches by absolute address (strings %dB/%d, floats %dB/%d, data+bss+rdata %dB/%d)" % (
            n, c["lit_string_bytes"], c["lit_string_n"], c["lit_float_bytes"], c["lit_float_n"], gl,
            c["glob_data_n"] + c["glob_bss_n"] + c["glob_rdata_n"]), 1 + n // 25, "tu_define_data", {"slots_to_fix": n, "bytes_per_slot": round((lit + gl) / max(1, n), 1)})
L = raw["literals"]
S = raw["_sizes_by_label"]
census = {"regions": raw["regions"], "fill_by_label": S, "vtables": {k: v for k, v in V.items() if k not in ("rejected_rows", "no_candidate")},
          "vtable_rejected": V["rejected_rows"], "vtable_no_candidate": V["no_candidate"], "literals": L,
          "literals_rejected_by_reason": raw["literals_rejected_by_reason"], "globals": raw["globals"], "imports": raw["imports"],
          "tu_define_data": {str(t): dict(c) for t, c in tus.items()}, "top_globals_by_size": raw["_glob_items"][:60],
          "rejected_non_vtable": raw["_rejected_all"]}
outdir.mkdir(parents=True, exist_ok=True)
(outdir / "census.json").write_text(json.dumps(census, indent=1) + "\n")
rows.sort(key=lambda r: (-r["bytes"] / (r["effort"] * 1.0)))
tsv.parent.mkdir(parents=True, exist_ok=True)
with tsv.open("w") as f:
    f.write("rank\titem\tbytes\tfix_needed\teffort(1-5)\tkind\tbytes_per_effort\n")
    for i, r in enumerate(rows, 1):
        f.write("%d\t%s\t%d\t%s\t%d\t%s\t%.0f\n" % (i, r["item"].replace("\t", " "), r["bytes"], r["fix"].replace("\t", " "), r["effort"], r["kind"], r["bytes"] / r["effort"]))
print(len(rows), "rows")
for i, r in enumerate(rows[:25], 1):
    print(i, r["bytes"], r["effort"], r["kind"], r["item"][:70], "|", r["fix"][:110])
