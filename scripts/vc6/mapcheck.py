#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""M1 exit check: compare linked .text addresses with retail.

Reads a VC6 LINK /MAP file and the stubgen.py plan (the ordered engine
entries with their retail addresses) and reports, for every matched function,
its linked address against the manifest address. Where the offset between
linked and retail address changes from one ordered entry to the next, the
entry before the change is the drift source: its linked slot (distance to the
next linked entry) differs from the retail slot. Sources are grouped by kind
(matched function vs stub) and listed largest first.

Usage:
  scripts/vc6/mapcheck.py MAP PLAN [--json FILE] [--exe M1.EXE --retail GAMEMD.EXE]

With --exe and --retail it also counts the matched functions whose bytes in
the linked image already equal retail without masking (diagnostic only).
"""

import argparse
from collections import Counter
import json
from pathlib import Path
import re
import sys

from verify_vtable import load_pe

# Retail landmarks after the engine block (PE header entry point; the two
# import-thunk blocks and the CRT start from the inventory scan of the pinned
# exe). They show how far the library tail floats; M1 does not order it.
LANDMARKS = {"entry point (WinMainCRTStartup)": 0x7CD80F, "first import thunk block": 0x7C8962,
             "second import thunk block (KERNEL32)": 0x7DCE62}
THUNK = re.compile(r"^\s*0001:[0-9A-Fa-f]{8}\s+(\S+)\s+([0-9A-Fa-f]{8}) f\s+(\w+):\S+\.dll\s*$", re.I)
ENTRY = re.compile(r"entry point at\s+0001:([0-9A-Fa-f]{8})")
PUBLIC = re.compile(r"^\s*([0-9A-Fa-f]{4}):([0-9A-Fa-f]{8})\s+(\S+)\s+([0-9A-Fa-f]{8})\s")
SECTION = re.compile(r"^\s*([0-9A-Fa-f]{4}):([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})H\s+(\S+)\s+(\w+)")


def parse_map(text):
    """-> ({symbol: VA}, [(section index, start offset, length, name, class)])."""
    publics, sections = {}, []
    in_publics = False
    for line in text.splitlines():
        if "Publics by Value" in line:
            in_publics = True
            continue
        if not in_publics:
            m = SECTION.match(line)
            if m:
                sections.append((int(m.group(1), 16), int(m.group(2), 16), int(m.group(3), 16), m.group(4),
                                 m.group(5)))
            continue
        m = PUBLIC.match(line)
        if m:
            publics.setdefault(m.group(3), int(m.group(4), 16))
    return publics, sections


def landmarks(text, publics):
    out = {}
    m = ENTRY.search(text)
    entry = publics.get("_WinMainCRTStartup")
    thunks = []
    for line in text.splitlines():
        t = THUNK.match(line)
        if t:
            thunks.append((int(t.group(2), 16), t.group(3).upper()))
    first = min((a for a, _ in thunks), default=None)
    kernel = min((a for a, d in thunks if d == "KERNEL32"), default=None)
    for label, linked in (("entry point (WinMainCRTStartup)", entry), ("first import thunk block", first),
                          ("second import thunk block (KERNEL32)", kernel)):
        retail = LANDMARKS[label]
        out[label] = {"retail": f"0x{retail:X}", "linked": None if linked is None else f"0x{linked:X}",
                      "delta": None if linked is None else linked - retail}
    out["import thunks linked"] = len(thunks)
    return out


def check(map_path, plan_path):
    text = Path(map_path).read_text(encoding="latin-1")
    publics, _ = parse_map(text)
    plan = json.loads(Path(plan_path).read_text())
    placed = plan["placed"]
    rows = []
    for p in placed:
        va = publics.get(p["symbol"])
        rows.append({"addr": int(p["addr"], 16), "symbol": p["symbol"], "kind": p["kind"], "linked": va})
    matched = [r for r in rows if r["kind"] == "matched"]
    at_retail = [r for r in matched if r["linked"] == r["addr"]]
    missing = [r for r in rows if r["linked"] is None]
    events = []
    prev = None
    for i, r in enumerate(rows):
        if r["linked"] is None:
            continue
        delta = r["linked"] - r["addr"]
        if prev is not None and delta != prev[1]:
            src = rows[prev[0]]
            events.append({"at": f"0x{r['addr']:X}", "change": delta - prev[1], "delta_after": delta,
                           "source_addr": f"0x{src['addr']:X}", "source_kind": src["kind"],
                           "source_symbol": src["symbol"],
                           "linked_slot": r["linked"] - src["linked"], "retail_slot": r["addr"] - src["addr"]})
        prev = (i, delta)
    first_off = next((r for r in rows if r["linked"] is not None and r["linked"] != r["addr"]), None)
    by_kind = Counter(e["source_kind"] for e in events)
    bytes_by_kind = Counter()
    for e in events:
        bytes_by_kind[e["source_kind"]] += abs(e["change"])
    deltas = Counter((r["linked"] - r["addr"]) for r in matched if r["linked"] is not None)
    return {
        "ordered_entries": len(rows),
        "matched_functions": len(matched),
        "matched_at_retail_address": len(at_retail),
        "matched_off_address": len(matched) - len(at_retail) - sum(1 for r in matched if r["linked"] is None),
        "entries_missing_from_map": len(missing),
        "missing_examples": [f"0x{r['addr']:X} {r['symbol']}" for r in missing[:20]],
        "first_divergence": None if first_off is None else {
            "addr": f"0x{first_off['addr']:X}", "symbol": first_off["symbol"], "linked": f"0x{first_off['linked']:X}"},
        "drift_events": len(events),
        "drift_events_by_source_kind": dict(by_kind),
        "drift_bytes_by_source_kind": dict(bytes_by_kind),
        "largest_drift_events": sorted(events, key=lambda e: -abs(e["change"]))[:40],
        "events": events,
        "matched_delta_histogram_top": [[f"{d:+#x}", n] for d, n in deltas.most_common(15)],
        "landmarks": landmarks(text, publics),
    }


def _reader(path, expected_sha=None):
    data, _, sections = load_pe(path, expected_sha) if expected_sha else _load_any(path)

    def read(va, n):
        for _, start, vsize, rawptr, rawsize in sections:
            if start <= va and va + n <= start + min(vsize, rawsize):
                return data[rawptr + va - start:rawptr + va - start + n]
        return None
    return read


def _load_any(path):
    import hashlib
    return load_pe(path, hashlib.sha256(Path(path).read_bytes()).hexdigest())


def byte_check(exe, retail, plan_path, retail_sha):
    """Diagnostic only: how many placed matched functions already have the
    retail bytes in the linked image with no masking. The rest differ in
    relocated fields (M1 data addresses are not faithful). Never identity."""
    linked, original = _reader(exe), _reader(retail, retail_sha)
    same = differ = 0
    for p in json.loads(Path(plan_path).read_text())["placed"]:
        if p["kind"] != "matched":
            continue
        va, n = int(p["addr"], 16), int(p["len"], 16)
        if linked(va, n) is not None and linked(va, n) == original(va, n):
            same += 1
        else:
            differ += 1
    return {"matched_bytes_equal_unmasked": same, "matched_bytes_differ": differ}


def print_summary(c):
    print(f"matched functions at retail address: {c['matched_at_retail_address']} / {c['matched_functions']}"
          f" (off address {c['matched_off_address']}, missing from map {c['entries_missing_from_map']})")
    print(f"first divergence: {c['first_divergence']}")
    print(f"drift events: {c['drift_events']} by source {c['drift_events_by_source_kind']} "
          f"bytes {c['drift_bytes_by_source_kind']}")
    for label, v in c["landmarks"].items():
        print(f"  {label}: {v}")
    for e in c["largest_drift_events"][:10]:
        print(f"  {e['source_kind']:<7} {e['source_addr']} {e['source_symbol'][:60]:<60} "
              f"linked slot {e['linked_slot']:#x} retail {e['retail_slot']:#x} change {e['change']:+#x}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("map", type=Path)
    ap.add_argument("plan", type=Path)
    ap.add_argument("--json", type=Path)
    ap.add_argument("--exe", type=Path, help="linked image, for the optional byte check")
    ap.add_argument("--retail", type=Path, help="the pinned retail exe (read, never copied)")
    args = ap.parse_args(argv)
    c = check(args.map, args.plan)
    if args.exe and args.retail:
        import extent_census
        c["byte_check"] = byte_check(args.exe, args.retail, args.plan, extent_census.SHA256)
        print(f"byte check (diagnostic): {c['byte_check']}")
    if args.json:
        args.json.write_text(json.dumps(c, indent=1) + "\n")
    print_summary(c)
    return 0


if __name__ == "__main__":
    sys.exit(main())
