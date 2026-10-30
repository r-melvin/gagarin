#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original. Read-only audit of template-instance COMDATs over a build objdir.
"""tpl_audit: who defines each template COMDAT, which definer the link keeps, and does it equal retail?

Read-only: it reads an objdir (objects.json + .obj files), the manifest and (optionally) the pinned image.
It writes nothing except the optional --json file.

  tpl_audit.py OBJDIR [--instance SUBSTR] [--all] [--divergent] [--multi-g] [--json OUT]

Reports (no flag = owner table and divergent report):
  owners     one row per COMDAT symbol that two or more objects define: the definers in link order (the order
             stubgen gives the link: lowest retail address any manifest row of the TU claims), which one wins
             (LINK keeps the first definition, IMAGE_COMDAT_SELECT_ANY), whether the winner's bytes equal
             retail at the symbol's manifest address, and the instance (template class) it belongs to.
             Template symbols only unless --all.
  instances  the same grouped per instance: definers, winners, rows files.
  divergent  symbols whose definers differ in size or in reloc-normalised bytes, with the definers in link
             order; ">" marks the winner. Redundant identical copies are benign and not listed.
  multi-g    template ??_G (any symbol with --all-symbols) that the manifest places at 2+ retail addresses:
             `ghidra x-ref to` each address, counting CALL and DATA references, to check whether the extra
             copies are per-TU code reached by direct calls. Needs the ghidra CLI and GAMEMD_BINARY.

Equality against retail needs GAMEMD_BINARY; without it the column is "-".
"""
import argparse
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent.parent
sys.path.insert(0, str(ROOT / "scripts" / "vc6"))

import hybrid  # noqa: E402
import idiom_lift  # noqa: E402
import stubgen  # noqa: E402
from verify_vtable import parse_coff, VerifyError  # noqa: E402

GHIDRA = os.path.expanduser("~/.cargo/bin/ghidra")


def instance_of(sym):
    """Template class of a mangled symbol ("DynamicVectorClass<int>"), or None for a non-template symbol."""
    if "?$" not in sym:
        return None
    if sym.startswith("??_C"):   # string literal
        return None
    probe = sym
    if sym.startswith(("??_7", "??_R")):
        # vtable / RTTI record: cut the tail so the template id is followed by a member-shaped suffix
        g = sym[sym.index("?$"):]
        g = g[:-3] if sym.startswith(("??_7", "??_R4")) else g[:-2] if sym.startswith("??_R0") else g[:-1]
        probe = "?x@" + g + "QAEXXZ"
    try:
        d = idiom_lift.demangle(probe)
    except Exception:
        d = None
    if d and d.get("cls"):
        return d["cls"]
    m = re.search(r"\?\$\w+@[^@]*", sym)   # fallback: leading part of the template id
    return m.group(0) if m else None


def comdat_bytes(parsed, sym):
    """(size, sha1 of the section bytes with 4-byte relocation fields zeroed) for a symbol at a section start,
    or None. Section-level, so padding the compiler added is part of the comparison."""
    if parsed is None:
        return None
    data, sections, symbols, _ = parsed
    found = [s for s in symbols.values() if s["name"] == sym and s["section"] in sections]
    if len(found) != 1 or found[0]["value"] != 0:
        return None
    sec = sections[found[0]["section"]]
    if sec["uninitialized"]:
        return (sec["raw_size"], "bss")
    raw = bytearray(data[sec["raw_ptr"]:sec["raw_ptr"] + sec["raw_size"]])
    for offset, _, _ in sec["relocs"]:
        raw[offset:offset + 4] = bytes(len(raw[offset:offset + 4]))
    return (sec["raw_size"], hashlib.sha1(bytes(raw)).hexdigest()[:12])


def load_retail():
    if not os.environ.get("GAMEMD_BINARY"):
        return None
    try:
        return hybrid.Retail(os.environ["GAMEMD_BINARY"])
    except Exception as e:   # no image: equality column becomes "-"
        print(f"warning: retail image unavailable ({e})", file=sys.stderr)
        return None


def audit(objdir, manifest=None, retail=None, include_all=False):
    index = json.loads((objdir / "objects.json").read_text())
    if manifest is None:
        manifest = json.loads((stubgen.DATA / "match_manifest.json").read_text())
    order = stubgen.link_order(index, manifest)
    rows_at = defaultdict(list)   # symbol -> [row]
    for r in manifest:
        rows_at[r["sym"]].append(r)
    definers = defaultdict(list)  # symbol -> [(object name, source, size, norm)]
    parsed = {}
    for rank, o in enumerate(order):
        path = objdir / o["object"]
        try:
            parsed[o["object"]] = parse_coff(path)
        except VerifyError:
            parsed[o["object"]] = None
        _, _, _, sizes = stubgen.object_symbols(path)
        for sym in sizes:
            if sym.startswith(("?", "_")) and not sym.startswith("??_C") and (include_all or "?$" in sym):
                norm = comdat_bytes(parsed[o["object"]], sym)
                if norm:
                    definers[sym].append({"object": o["object"], "source": o.get("source"), "rank": rank,
                                          "size": norm[0], "norm": norm[1]})
    out = []
    for sym, defs in sorted(definers.items()):
        if len(defs) < 2:
            continue
        addrs = sorted({stubgen.hx(r["addr"]) for r in rows_at.get(sym, [])})
        winner = defs[0]
        eq = {}
        for d in defs:
            e = "-"
            if retail is not None and addrs:
                rows = sorted(rows_at[sym], key=lambda r: stubgen.hx(r["addr"]))
                got = hybrid.function_matches(parsed[d["object"]], sym, stubgen.hx(rows[0]["addr"]),
                                              stubgen.hx(rows[0]["len"]), retail)
                e = {True: "Y", False: "N", None: "?"}[got]
            eq[d["object"]] = e
            d["eq_retail"] = e
        out.append({"symbol": sym, "instance": instance_of(sym), "addresses": [f"0x{a:X}" for a in addrs],
                    "rows": [{"addr": r["addr"], "tu": r["tu"], "status": r["status"]} for r in rows_at.get(sym, [])],
                    "definers": defs, "winner": winner["object"], "winner_eq_retail": winner["eq_retail"],
                    "divergent": len({(d["size"], d["norm"]) for d in defs}) > 1})
    return out


def multi_address(manifest, include_all=False):
    """symbol -> sorted addresses, for template ??_G (or every symbol with include_all) placed at 2+ addresses."""
    at = defaultdict(set)
    for r in manifest:
        sym = r["sym"]
        if include_all or (sym.startswith("??_G") and "?$" in sym):
            at[sym].add(stubgen.hx(r["addr"]))
    return {s: sorted(a) for s, a in at.items() if len(a) > 1}


def xref_summary(addr):
    try:
        r = subprocess.run([GHIDRA, "x-ref", "to", f"0x{addr:X}", "--json"], capture_output=True, text=True,
                           timeout=120)
        refs = json.loads(r.stdout)
    except (OSError, ValueError, subprocess.TimeoutExpired):
        return None
    calls = [x for x in refs if "CALL" in x.get("ref_type", "")]
    data = [x for x in refs if x.get("ref_type") == "DATA"]
    other = len(refs) - len(calls) - len(data)
    return {"calls": len(calls), "data": len(data), "other": other,
            "callers": sorted({x.get("from_function") or x["from"] for x in calls})[:6],
            "data_from": sorted(x["from"] for x in data)[:6]}


def print_owners(rows, instance):
    print(f"{'symbol':70} {'win':3} definers in link order (eq-retail, size)")
    for r in rows:
        if instance and instance not in (r["instance"] or "") and instance not in r["symbol"]:
            continue
        defs = "  ".join(f"{'>' if d['object'] == r['winner'] else ' '}{Path(d['object']).stem}"
                         f"[{d['eq_retail']},{d['size']:#x}]" for d in r["definers"])
        print(f"{r['symbol'][:70]:70} {r['winner_eq_retail']:3} {defs}"
              f"{'  DIVERGENT' if r['divergent'] else ''}  @{','.join(r['addresses']) or '-'}")


def print_instances(rows, instance):
    by = defaultdict(list)
    for r in rows:
        if instance and instance not in (r["instance"] or "") and instance not in r["symbol"]:
            continue
        by[r["instance"] or "(non-template)"].append(r)
    print(f"{'instance':50} {'syms':>4} {'div':>3} {'win!=ret':>8} winners")
    for inst, rs in sorted(by.items()):
        wins = defaultdict(int)
        for r in rs:
            wins[Path(r["winner"]).stem] += 1
        bad = sum(1 for r in rs if r["winner_eq_retail"] == "N")
        print(f"{inst[:50]:50} {len(rs):>4} {sum(r['divergent'] for r in rs):>3} {bad:>8} "
              + ", ".join(f"{k}:{v}" for k, v in sorted(wins.items())))


def print_divergent(rows, instance):
    div = [r for r in rows if r["divergent"] and (not instance or instance in (r["instance"] or "") or instance in r["symbol"])]
    print(f"{len(div)} divergent COMDAT symbols (definers differ in size or normalised bytes)")
    for r in div:
        print(r["symbol"])
        for d in r["definers"]:
            print(f"   {'>' if d['object'] == r['winner'] else ' '} #{d['rank']:<4} {d['object']:50} size={d['size']:#x} "
                  f"norm={d['norm']} eq_retail={d['eq_retail']}")
        print(f"     retail @ {','.join(r['addresses']) or '-'}")


def print_multi(manifest, include_all, skip_ghidra):
    multi = multi_address(manifest, include_all)
    print(f"{len(multi)} symbols placed at 2+ retail addresses")
    tally = {"copies": 0, "with_calls": 0, "data_only": 0, "no_refs": 0, "unknown": 0}
    for sym, addrs in sorted(multi.items()):
        print(sym)
        for a in addrs:
            x = None if skip_ghidra else xref_summary(a)
            tally["copies"] += 1
            if x is None:
                tally["unknown"] += 1
                print(f"   0x{a:X}  (no x-ref data)")
            else:
                tally["with_calls" if x["calls"] else "data_only" if x["data"] else "no_refs"] += 1
                print(f"   0x{a:X}  calls={x['calls']} data={x['data']} other={x['other']}  "
                      f"callers={','.join(x['callers']) or '-'}  data_from={','.join(x['data_from']) or '-'}")
    if not skip_ghidra:
        print("summary: " + ", ".join(f"{k}={v}" for k, v in tally.items())
              + "  (data_only = referenced only from a vtable slot, no direct call)")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("objdir", type=Path)
    ap.add_argument("--instance", help="substring of the template class or symbol to show")
    ap.add_argument("--all", action="store_true", help="include non-template COMDATs")
    ap.add_argument("--instances", action="store_true", help="per-instance summary instead of per symbol")
    ap.add_argument("--divergent", action="store_true", help="only the divergent-COMDAT report")
    ap.add_argument("--multi-g", action="store_true", help="only the multi-address ??_G check")
    ap.add_argument("--no-ghidra", action="store_true", help="multi-g: list addresses without x-refs")
    ap.add_argument("--json", type=Path, help="write the owner rows here")
    a = ap.parse_args()
    manifest = json.loads((stubgen.DATA / "match_manifest.json").read_text())
    if a.multi_g:
        print_multi(manifest, a.all, a.no_ghidra)
        return 0
    rows = audit(a.objdir, manifest, load_retail(), a.all)
    if a.json:
        a.json.write_text(json.dumps(rows, indent=1))
    if a.divergent:
        print_divergent(rows, a.instance)
    elif a.instances:
        print_instances(rows, a.instance)
    else:
        print_owners(rows, a.instance)
        print()
        print_divergent(rows, a.instance)
    return 0


if __name__ == "__main__":
    sys.exit(main())
