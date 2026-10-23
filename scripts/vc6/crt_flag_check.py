#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Compare two object builds that differ only in one compiler flag.

Used for the /ML vs /MT question: build the tree twice with build_project.py,
once as is and once with VC6_EXTRA_FLAGS=/MT, then run

  scripts/vc6/crt_flag_check.py --base OBJDIR --other OBJDIR [--json FILE]

Every section of every object is compared (name, flags, bytes, and each
relocation's offset, type and target symbol name). The .drectve section is
reported separately because it carries the /DEFAULTLIB request the flag is
meant to change. A manifest row is affected when the section that defines
its symbol differs. Exit 0 when no section other than .drectve differs.
"""

import argparse
import json
from pathlib import Path
import sys

from verify_vtable import parse_coff

ROOT = Path(__file__).resolve().parents[2]


def reloc_target(symbols, idx):
    """External targets by name; local ones ($L labels, statics) by position,
    because the compiler numbers its $L labels per compilation and the
    numbering moves when an unrelated header changes."""
    sym = symbols.get(idx)
    if sym is None:
        return idx
    if sym["storage_class"] == 2:
        return sym["name"]
    if sym["name"].startswith("$") or sym["storage_class"] == 6:
        return ("local", sym["section"], sym["value"])
    return sym["name"]


def sections_by_name(path):
    data, sections, symbols, _ = parse_coff(path)
    out = []
    for secno in sorted(sections):
        s = sections[secno]
        raw = b"" if s["uninitialized"] else data[s["raw_ptr"]:s["raw_ptr"] + s["raw_size"]]
        relocs = tuple((off, reloc_target(symbols, idx), kind) for off, idx, kind in s["relocs"])
        defined = sorted(sym["name"] for sym in symbols.values()
                         if sym["section"] == secno and sym["storage_class"] == 2)
        out.append({"name": s["name"], "raw": raw, "size": s["raw_size"], "relocs": relocs, "defines": defined})
    return out


def compare_objects(a, b):
    """-> (drectve_differs, [differing section descriptions], structural problem or None)."""
    sa, sb = sections_by_name(a), sections_by_name(b)
    if len(sa) != len(sb):
        return False, [], f"section count {len(sa)} vs {len(sb)}"
    drectve, diffs = False, []
    for x, y in zip(sa, sb):
        if x["name"] != y["name"]:
            return drectve, diffs, f"section order differs ({x['name']} vs {y['name']})"
        same = x["raw"] == y["raw"] and x["size"] == y["size"] and x["relocs"] == y["relocs"]
        if same:
            continue
        if x["name"] == ".drectve":
            drectve = True
            continue
        diffs.append({"section": x["name"], "defines": x["defines"] or y["defines"]})
    return drectve, diffs, None


def drectve_text(path):
    data, sections, _, _ = parse_coff(path)
    for s in sections.values():
        if s["name"] == ".drectve":
            return data[s["raw_ptr"]:s["raw_ptr"] + s["raw_size"]].decode("latin-1").strip("\0 ")
    return ""


def run(base, other, manifest):
    index = json.loads((base / "objects.json").read_text())
    rows_by_sym = {}
    for r in manifest:
        rows_by_sym.setdefault(r["sym"], []).append(r)
    report = {"objects": 0, "identical_except_drectve": 0, "drectve_changed": 0, "differing_objects": [],
              "affected_rows": [], "structural": [], "drectve_example": None}
    for item in index["objects"]:
        a, b = base / item["object"], other / item["object"]
        report["objects"] += 1
        drectve, diffs, problem = compare_objects(a, b)
        if problem:
            report["structural"].append({"object": item["object"], "problem": problem})
            continue
        if drectve:
            report["drectve_changed"] += 1
            if report["drectve_example"] is None:
                report["drectve_example"] = {"object": item["object"], "base": drectve_text(a),
                                             "other": drectve_text(b)}
        if diffs:
            report["differing_objects"].append({"object": item["object"], "sections": diffs})
            for d in diffs:
                for sym in d["defines"]:
                    for r in rows_by_sym.get(sym, []):
                        report["affected_rows"].append({"addr": r["addr"], "sym": sym, "status": r["status"],
                                                        "object": item["object"]})
        else:
            report["identical_except_drectve"] += 1
    status = {}
    for r in manifest:
        status[r["status"]] = status.get(r["status"], 0) + 1
    report["manifest_rows"] = status
    report["affected_by_status"] = {}
    for r in report["affected_rows"]:
        report["affected_by_status"][r["status"]] = report["affected_by_status"].get(r["status"], 0) + 1
    return report


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--base", type=Path, required=True)
    ap.add_argument("--other", type=Path, required=True)
    ap.add_argument("--manifest", type=Path, default=ROOT / "scripts/data/match_manifest.json")
    ap.add_argument("--json", type=Path)
    args = ap.parse_args(argv)
    report = run(args.base, args.other, json.loads(args.manifest.read_text()))
    if args.json:
        args.json.write_text(json.dumps(report, indent=1) + "\n")
    print(f"objects compared: {report['objects']}; identical apart from .drectve: "
          f"{report['identical_except_drectve']}; .drectve changed: {report['drectve_changed']}")
    print(f"objects with other differing sections: {len(report['differing_objects'])}; "
          f"structural mismatches: {len(report['structural'])}")
    print(f"manifest rows affected: {len(report['affected_rows'])} {report['affected_by_status']} "
          f"of {report['manifest_rows']}")
    if report["drectve_example"]:
        ex = report["drectve_example"]
        print(f".drectve example ({ex['object']}):\n  base:  {ex['base']}\n  other: {ex['other']}")
    clean = not report["differing_objects"] and not report["structural"]
    return 0 if clean else 1


if __name__ == "__main__":
    sys.exit(main())
