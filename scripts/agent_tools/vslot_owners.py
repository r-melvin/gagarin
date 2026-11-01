#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads only the user's retail gamemd.exe (GAMEMD_BINARY),
#   scripts/data/rtti_classes.json and scripts/data/match_manifest.json.
"""Which class each virtual function belongs to, by the RTTI vtables that hold it, vs the manifest.

Every function in a slot of class X's vtable is a virtual of X or of one of X's bases. Across all
vtables holding a function, the declaring class is the most-derived class common to every holder's
base chain (where the slot was introduced or last overridden), and the slot index is its position in
the holder vtables. A manifest row whose symbol is owned by a stand-in (`*View`, `Obj_XXXXXXXX`...),
by a class outside that chain, or by no class at all, is mis-homed: the binary says where it goes.

    vslot_owners.py [--json OUT] [--tsv OUT] [--class NAME]

The TSV is the rehoming worklist (addr, status, current owner, target class, slots, symbol), ranked by
target class so one class family can be restructured at a time. Report only; nothing is edited.
"""
import argparse, collections, json, os, re, struct, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
STANDIN = re.compile(r"(?:Obj|Packed|Quad|Rec|Dlg|Inline)_[0-9A-Fa-f]{6,8}$|View(?:_[0-9A-Fa-f]+)?$|_[0-9A-Fa-f]{8}$")


def load_image(exe):
    data = open(exe, "rb").read()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec, optsz = struct.unpack_from("<H", data, pe + 6)[0], struct.unpack_from("<H", data, pe + 20)[0]
    base = struct.unpack_from("<I", data, pe + 52)[0]
    secs = []
    for i in range(nsec):
        o = pe + 24 + optsz + 40 * i
        vsz, va, rsz, roff = struct.unpack_from("<IIII", data, o + 8)
        secs.append((base + va, vsz, roff, rsz, struct.unpack_from("<I", data, o + 36)[0]))
    return data, secs


def owner_of(sym):
    """Class owning a mangled symbol, or None for a free function (or an unmangled name)."""
    if not sym.startswith("?"):
        return None
    special = re.match(r"\?\?(?:_[0-9A-Z]|[0-9A-Z])(\?\$)?(\w+)@", sym)   # ctor/dtor/??_G..., maybe a template
    if special:
        return special.group(2)
    if re.match(r"\?[^@?]+@@Y", sym):
        return None
    tmpl = re.match(r"\?[^@?]+@\?\$(\w+)@", sym)
    if tmpl:
        return tmpl.group(1)
    plain = re.match(r"\?[^@?]+@(\w+)@", sym)
    return plain.group(1) if plain else None


def short(name):
    return name.split("<")[0].split("::")[-1]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json")
    ap.add_argument("--tsv")
    ap.add_argument("--class", dest="cls", help="only rows whose target class is NAME")
    a = ap.parse_args(argv)
    exe = os.environ.get("GAMEMD_BINARY") or sys.exit("set GAMEMD_BINARY")
    data, secs = load_image(exe)

    def dword(v):
        for s, vsz, roff, rsz, ch in secs:
            if s <= v < s + min(vsz, rsz) - 3:
                return struct.unpack_from("<I", data, roff + v - s)[0]
        return None

    def is_code(x):
        return any(s <= x < s + vsz for s, vsz, _, _, ch in secs if ch & 0x20)

    rtti = json.load(open(os.path.join(ROOT, "scripts/data/rtti_classes.json")))["classes"]
    vt_starts = {int(l["vtable_va"], 16) for c in rtti.values() for l in c.get("locators", []) if l.get("vtable_va")}
    chain, holders = {}, collections.defaultdict(dict)   # fn -> {class: slot}
    for c in rtti.values():
        name = c.get("demangled_name")
        if not name:
            continue
        chain[name] = c.get("base_chain") or [name]
        for loc in c.get("locators", []):
            if not loc.get("vtable_va") or loc.get("base_offset", 0):
                continue                       # primary vtable only; secondary ones hold thunks/bases
            v = int(loc["vtable_va"], 16)
            for k in range(1024):
                w = dword(v + 4 * k)
                if w is None or not is_code(w) or (k and v + 4 * k in vt_starts):
                    break
                holders[w].setdefault(name, k)

    def declaring(hs):
        common = None
        for h in hs:
            ch = [short(x) for x in chain.get(h, [h])]          # most-derived first
            common = ch if common is None else [x for x in common if x in ch]
        return common[0] if common else None

    rows, counts = [], collections.Counter()
    for e in json.load(open(os.path.join(ROOT, "scripts/data/match_manifest.json"))):
        f = int(e["addr"], 16)
        hs = holders.get(f)
        if not hs:
            continue
        target = declaring(hs)
        allowed = {short(x) for h in hs for x in chain.get(h, [h])}
        cur = owner_of(e["sym"])
        if cur is None:
            kind = "free function"
        elif short(cur) == target:
            kind = "ok"
        elif short(cur) in allowed:
            kind = "base of target"          # legal C++ (inherited, not overridden) only if the slot is the base's
        elif STANDIN.search(cur):
            kind = "stand-in owner"
        else:
            kind = "outside chain"
        counts[kind] += 1
        if kind != "ok":
            rows.append({"addr": e["addr"], "status": e["status"], "kind": kind, "owner": cur, "target": target,
                         "slots": {short(h): k for h, k in sorted(hs.items())}, "sym": e["sym"], "tu": e["tu"]})
    if a.cls:
        rows = [r for r in rows if r["target"] == a.cls]
    rows.sort(key=lambda r: (str(r["target"]), r["addr"]))
    print("virtual functions in the manifest by owner:", ", ".join(f"{k} {n}" for k, n in counts.most_common()))
    per = collections.Counter(r["target"] for r in rows)
    print("mis-homed by target class (top 15):", ", ".join(f"{k} {n}" for k, n in per.most_common(15)))
    if a.json:
        json.dump(rows, open(a.json, "w"), indent=1)
    if a.tsv:
        with open(a.tsv, "w") as f:
            f.write("addr\tstatus\tkind\towner\ttarget\tslots\tsym\ttu\n")
            for r in rows:
                f.write("\t".join([r["addr"], r["status"], r["kind"], str(r["owner"]), str(r["target"]),
                                   ",".join(f"{k}:{v}" for k, v in r["slots"].items()), r["sym"], r["tu"]]) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
