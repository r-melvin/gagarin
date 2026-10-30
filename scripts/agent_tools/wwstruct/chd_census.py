#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""RTTI class-hierarchy-descriptor census: the ??_R3 attributes word per class per object, against retail.

  chd_census.py OBJDIR [--base OBJDIR] [--tu SUBSTR ...] [--json OUT] [--all]

OBJDIR is a build_project.py output (objects.json). Retail attributes come from scripts/data/rtti_classes.json.
Rows: source, class, ours, retail, status (ok/DIFF/noretail). With --base, a before column and a transition
(e.g. 5->1) are added. The totals count each (object, class) once; --all also lists classes already equal.
A class emitted by several objects appears once per object (the emitter map tells which one the link keeps).
"""

import argparse
import json
import struct
import sys

import wwlib


def census(objdir, retail=None):
    """{(source, symbol): attributes} for every ??_R3 an object defines."""
    out = {}
    for source, path in wwlib.object_paths(objdir).items():
        data = path.read_bytes()
        secs = wwlib.sections(data)
        for name, sec, value, _ in wwlib.defined_symbols(data):
            if name.startswith("??_R3"):
                raw = wwlib.section_bytes(data, secs, sec)
                if len(raw) >= value + 8:
                    out[(source, name)] = struct.unpack_from("<I", raw, value + 4)[0]
    return out


def rows(after, before=None, retail=None):
    retail = retail if retail is not None else wwlib.retail_chd_attributes()
    result = []
    for (source, sym), ours in sorted(after.items()):
        demangled, want = retail.get(sym[5:], (sym[5:], None))
        row = {"source": source, "symbol": sym, "class": demangled, "ours": ours, "retail": want,
               "status": "noretail" if want is None else ("ok" if want == ours else "DIFF")}
        if before is not None:
            row["before"] = before.get((source, sym))
        result.append(row)
    return result


def summarise(table):
    ok = sum(1 for r in table if r["status"] == "ok")
    diff = sum(1 for r in table if r["status"] == "DIFF")
    out = {"objects": len(table), "ok": ok, "diff": diff}
    if table and "before" in table[0]:
        out["flipped"] = [(r["source"], r["class"], r["before"], r["ours"]) for r in table
                          if r["before"] is not None and r["before"] != r["ours"]]
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("objdir")
    ap.add_argument("--base")
    ap.add_argument("--tu", action="append", default=[], help="only sources containing this substring")
    ap.add_argument("--json")
    ap.add_argument("--all", action="store_true")
    args = ap.parse_args(argv)
    after = census(args.objdir)
    before = census(args.base) if args.base else None
    table = rows(after, before)
    if args.tu:
        table = [r for r in table if any(t in r["source"] for t in args.tu)]
    shown = [r for r in table if args.all or args.tu or r["status"] == "DIFF"
             or (r.get("before") is not None and r["before"] != r["ours"])]
    for r in shown:
        b = f" before={r['before']}" if "before" in r else ""
        print(f"{r['status']:8} {r['source']}  {r['class']}  ours={r['ours']} retail={r['retail']}{b}")
    s = summarise(table)
    print(f"-- objects={s['objects']} ok={s['ok']} diff={s['diff']}" +
          (f" flipped={len(s['flipped'])}" if "flipped" in s else ""))
    if args.json:
        with open(args.json, "w") as f:
            json.dump({"summary": s, "rows": table}, f, indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
