#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Mapping generator for the structure migration: current source file -> target <Name>.CPP (report only, no moves).

  tu_mapping.py [--json OUT] [--tsv OUT] [--file SUBSTR ...] [--split]

Inputs: scripts/data/original_tu_map.json (link_order windows and per-function evidence) and
scripts/data/match_manifest.json (which current file holds each function). Rules, applied per function:
  1. witnessed, or address inside the [lo,hi] window of an attested TU        -> that TU, exact retail spelling
  2. inferred-class / inferred-contiguity naming an attested TU                -> that TU
     inferred-class / inferred-contiguity (class:<Name>)                       -> <Family>.CPP
     where Family is the class name without the trailing "Class" (TriggerTypeClass -> TriggerType)
  3. comdat                                                                    -> no TU (header or instantiation TU)
  4. unknown                                                                   -> stays (no target)
A current file gets a target when every attributed (rules 1-2) function in it maps to the same one; it is
"split" when two or more targets occur, "unplaced" when none does. Files that would merge are listed per
target. Addresses never appear in a target name. Nothing is moved.
"""

import argparse
import bisect
import collections
import json
import re
import sys

import wwlib


def family_name(cls):
    """Class name -> RA-style family file stem: drop template args/namespaces, then a trailing 'Class'."""
    name = re.sub(r"<.*", "", cls).split("::")[-1]
    name = re.sub(r"Class$", "", name) or name
    return re.sub(r"[^A-Za-z0-9_]", "", name)


def class_of(tu):
    m = re.match(r"^class:([^@]+)", tu or "")
    return m.group(1) if m else None


def classify(entry, windows, starts):
    """-> (kind, target or None) for one original_tu_map function entry."""
    kind = entry["tu_kind"]
    addr = int(entry["addr"], 16)
    if kind == "witnessed":
        return "attested", entry["tu"]
    i = bisect.bisect_right(starts, addr) - 1
    if i >= 0 and windows[i][0] <= addr <= windows[i][1] and kind != "comdat":
        return "attested-window", windows[i][2]
    if kind in ("inferred-class", "inferred-contiguity"):
        tu = entry.get("tu")
        cls = class_of(tu)
        if cls:
            return "class", family_name(cls) + ".CPP"
        return ("attested-inferred", tu) if tu and not tu.startswith("class:") else ("class", None)
    return kind, None


def build(tu_map=None, manifest=None):
    tu_map = tu_map or json.loads((wwlib.DATA / "original_tu_map.json").read_text())
    manifest = manifest or json.loads((wwlib.DATA / "match_manifest.json").read_text())
    windows = sorted((int(w["lo"], 16), int(w["hi"], 16), w["tu"]) for w in tu_map["link_order"])
    starts = [w[0] for w in windows]
    per_addr = {e["addr"].upper().replace("0X", "0x"): classify(e, windows, starts) for e in tu_map["functions"]}
    files = collections.defaultdict(lambda: collections.Counter())
    for row in manifest:
        key = row["addr"].upper().replace("0X", "0x")
        kind, target = per_addr.get(key, ("unknown", None))
        files[row["tu"]][(kind, target)] += 1
    out = {}
    for f, c in sorted(files.items()):
        targets = collections.Counter()
        other = collections.Counter()
        for (kind, target), n in c.items():
            if target:
                targets[target] += n
            else:
                other[kind] += n
        if len(targets) == 1:
            status, target = "single", next(iter(targets))
        elif targets:
            status, target = "split", None
        else:
            status, target = "unplaced", None
        out[f] = {"status": status, "target": target, "targets": dict(targets), "unattributed": dict(other)}
    return out


def merges(mapping):
    by_target = collections.defaultdict(list)
    for f, e in mapping.items():
        if e["target"]:
            by_target[e["target"]].append(f)
    return by_target


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json")
    ap.add_argument("--tsv")
    ap.add_argument("--file", action="append", default=[], help="only current files containing this substring")
    ap.add_argument("--split", action="store_true", help="list split files with their target histogram")
    args = ap.parse_args(argv)
    mapping = build()
    sel = {f: e for f, e in mapping.items() if not args.file or any(s in f for s in args.file)}
    count = collections.Counter(e["status"] for e in sel.values())
    for f, e in sel.items():
        if args.file or (args.split and e["status"] == "split"):
            print(f"{e['status']:9} {f} -> {e['target'] or e['targets']} unattributed={e['unattributed']}")
    by = merges(sel)
    print(f"-- files={len(sel)} single={count['single']} split={count['split']} unplaced={count['unplaced']}"
          f" targets={len(by)} merging_targets={sum(1 for v in by.values() if len(v) > 1)}")
    if args.tsv:
        with open(args.tsv, "w") as f:
            for name, e in sel.items():
                f.write(f"{name}\t{e['status']}\t{e['target'] or ''}\n")
    if args.json:
        with open(args.json, "w") as f:
            json.dump({"files": sel, "merges": {k: v for k, v in by.items() if len(v) > 1}}, f, indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
