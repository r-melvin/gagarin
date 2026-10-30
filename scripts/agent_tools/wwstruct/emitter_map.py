#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Which object the link keeps for every shared COMDAT (vtables, RTTI, template and inline members).

  emitter_map.py OBJDIR [--json OUT] [--all] [--prefix ??_R3 ...]
  emitter_map.py OBJDIR --against OTHER_OBJDIR [--json OUT]

The link keeps the first definition it meets (COMDAT ANY). Objects are ordered as stubgen.link_order does:
by the lowest retail address any manifest row of the TU claims, objects without rows after, in index order.
For each symbol defined by two or more objects (or every COMDAT with --all) the map gives the kept source,
all definers, and whether the copies are interchangeable (same section bytes and same relocation targets).
For ??_R3 the kept copy's attributes word is compared with retail (scripts/data/rtti_classes.json).

--against compares two builds: symbols whose kept object changed, whose kept bytes changed, or that
appeared/disappeared. That is the "emitter map diff" gate for a header or TU change.
"""

import argparse
import json
import struct
import sys

import wwlib

sys.path.insert(0, str(wwlib.ROOT / "scripts/vc6"))


def ordered_sources(objdir, manifest=None):
    import stubgen
    index = wwlib.load_index(objdir)
    if manifest is None:
        manifest = json.loads((wwlib.DATA / "match_manifest.json").read_text())
    return [o["source"] for o in stubgen.link_order(index, manifest) if o.get("success")]


def build_map(objdir, manifest=None):
    paths = wwlib.object_paths(objdir)
    definers = {}
    for source in ordered_sources(objdir, manifest):
        for sym, sig in wwlib.comdat_definitions(paths[source]).items():
            definers.setdefault(sym, []).append((source, sig))
    retail = wwlib.retail_chd_attributes()
    out = {}
    for sym, defs in definers.items():
        kept_source, kept_sig = defs[0]
        entry = {"kept": kept_source, "definers": [s for s, _ in defs],
                 "identical": all(sig == kept_sig for _, sig in defs),
                 "digest": hash_sig(kept_sig)}
        if sym.startswith("??_R3") and len(kept_sig[1]) >= 8:
            ours = struct.unpack_from("<I", kept_sig[1], 4)[0]
            want = retail.get(sym[5:], (None, None))[1]
            entry["chd"] = {"ours": ours, "retail": want}
            entry["equals_retail"] = want == ours
        out[sym] = entry
    return out


def hash_sig(sig):
    import hashlib
    h = hashlib.sha256()
    h.update(sig[0].encode())
    h.update(sig[1])
    for rel in sig[2]:
        h.update(repr(rel).encode())
    return h.hexdigest()[:16]


def diff_maps(old, new):
    changes = []
    for sym in sorted(set(old) | set(new)):
        a, b = old.get(sym), new.get(sym)
        if a is None or b is None:
            changes.append({"symbol": sym, "change": "added" if a is None else "removed",
                            "kept": (b or a)["kept"]})
        elif a["kept"] != b["kept"]:
            changes.append({"symbol": sym, "change": "emitter", "from": a["kept"], "to": b["kept"]})
        elif a["digest"] != b["digest"]:
            changes.append({"symbol": sym, "change": "bytes", "kept": b["kept"]})
    return changes


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("objdir")
    ap.add_argument("--against")
    ap.add_argument("--json")
    ap.add_argument("--all", action="store_true", help="include COMDATs defined by one object only")
    ap.add_argument("--prefix", action="append", default=[], help="only symbols starting with this")
    args = ap.parse_args(argv)
    new = build_map(args.objdir)
    sel = lambda m: {k: v for k, v in m.items() if (not args.prefix or k.startswith(tuple(args.prefix)))}
    if args.against:
        old = build_map(args.against)
        changes = diff_maps(sel(old), sel(new))
        for c in changes:
            print(json.dumps(c))
        print(f"-- changes={len(changes)}")
        payload = {"changes": changes}
    else:
        shown = {k: v for k, v in sel(new).items() if args.all or len(v["definers"]) > 1}
        for sym, e in sorted(shown.items()):
            flag = "" if e["identical"] else " DIVERGENT"
            eq = "" if "equals_retail" not in e else (" retail=ok" if e["equals_retail"] else " retail=DIFF")
            print(f"{sym}  kept={e['kept']}  definers={len(e['definers'])}{flag}{eq}")
        print(f"-- symbols={len(new)} shared={sum(1 for v in new.values() if len(v['definers']) > 1)}"
              f" divergent={sum(1 for v in new.values() if not v['identical'])}")
        payload = {"symbols": sel(new)}
    if args.json:
        with open(args.json, "w") as f:
            json.dump(payload, f, indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
