#!/usr/bin/env python3
# Provenance: original; reads our VC6 objects, our manifest and our pinned PE.
"""refaudit.py — implied-base consistency of unverified DIR32 references.

Usage: refaudit.py [--objdirs DIR ...] [--json OUT] [--show N]
  default objdirs: $GAG_WORKTREE/build-vc6 then $GAG_MAIN/build-vc6
  (only <tu-stem>.obj for manifest TUs is read, never rebuilt; the first
   directory wins on a name clash)

For every matched manifest row whose symbol is defined in an object, the
function's bytes are compared with retail outside relocation fields (rows that
differ are skipped as stale). Each DIR32 field that refers to an EXTERNAL symbol
with no manifest address (what verify_relocations.py cannot bind) yields

    implied base = retail dword at the field - addend stored in our object

i.e. the address our symbol would need for that reference to be right. For a
real single object every reference agrees. A symbol with more than one implied
base means a wrong member offset/addend in some TU, or several objects sharing
one name (a per-TU constant, an overload, a mis-declared global).

Prints conflicts (and how many references back each base) and a count of
consistent symbols. --json writes everything, including the consistent
symbol -> implied address bindings (leads for GLOBAL annotations).
"""
import argparse
import json
import struct
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common  # noqa: E402
from verify_vtable import manifest_symbol_addrs  # noqa: E402

DIR32 = 0x0006
REL32 = 0x0014


def objects(dirs):
    """The object each manifest TU compiles to (verify_tus.py naming: basename.obj);
    other objects in build-vc6 are experiments and are ignored."""
    want = {Path(r["tu"]).stem + ".obj" for r in common.manifest()}
    seen = {}
    for d in dirs:
        for name in sorted(want):
            p = Path(d) / name
            if p.exists():
                seen.setdefault(name, p)
    return list(seen.values())


def audit(dirs):
    rows = [r for r in common.manifest() if r["status"] == "matched"]
    by_sym = defaultdict(list)
    for r in rows:
        by_sym[r["sym"]].append(r)
    known = manifest_symbol_addrs(common.manifest())
    img = common.pe()
    refs = defaultdict(lambda: defaultdict(list))  # sym -> base -> [(addr, obj)]
    stats = dict(objects=0, functions=0, stale=0, fields=0, known_fields=0)
    for obj in objects(dirs):
        try:
            data, sections, symbols, _ = common.parse_coff(obj)
        except Exception:
            continue
        stats["objects"] += 1
        for s in symbols.values():
            if s["name"] not in by_sym or s["section"] not in sections:
                continue
            sec = sections[s["section"]]
            for row in by_sym[s["name"]]:
                if Path(row["tu"]).stem != obj.stem:
                    continue
                va, n = common.h(row["addr"]), common.h(row["len"])
                ours = data[sec["raw_ptr"] + s["value"]: sec["raw_ptr"] + s["value"] + n]
                retail = img.read(va, n)
                if retail is None or len(ours) != n:
                    continue
                fields = [(rva - s["value"], symbols.get(idx), kind) for rva, idx, kind in sec["relocs"]
                          if s["value"] <= rva < s["value"] + n - 3]
                mask = bytearray(ours)
                rmask = bytearray(retail)
                for off, _, _ in fields:
                    mask[off:off + 4] = rmask[off:off + 4] = b"\0\0\0\0"
                if mask != rmask:
                    stats["stale"] += 1
                    continue
                stats["functions"] += 1
                for off, sym, kind in fields:
                    if kind != DIR32 or sym is None or sym["storage_class"] != 2:
                        continue  # statics ($SG strings, jump tables) are per-object
                    stats["fields"] += 1
                    if sym["name"] in known:
                        stats["known_fields"] += 1
                        continue
                    addend = struct.unpack_from("<I", ours, off)[0]
                    target = struct.unpack_from("<I", retail, off)[0]
                    base = (target - addend) & 0xFFFFFFFF
                    refs[sym["name"]][base].append((f"0x{va + off:X}", obj.name, addend))
    conflicts, consistent = {}, {}
    for name, bases in refs.items():
        entry = {f"0x{b:X}": [dict(field=a, obj=o, addend=hex(ad)) for a, o, ad in v] for b, v in bases.items()}
        (conflicts if len(bases) > 1 else consistent)[name] = entry
    return stats, conflicts, consistent


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--objdirs", nargs="+", default=[str(common.WORKTREE / "build-vc6"), str(common.MAIN / "build-vc6")])
    ap.add_argument("--json", type=Path)
    ap.add_argument("--show", type=int, default=40)
    a = ap.parse_args(argv)
    stats, conflicts, consistent = audit(a.objdirs)
    print(f"objects {stats['objects']}  functions checked {stats['functions']}  stale skipped {stats['stale']}")
    print(f"external DIR32 fields {stats['fields']} (bound by manifest {stats['known_fields']})")
    print(f"unbound symbols: {len(consistent)} consistent, {len(conflicts)} with >1 implied base")
    ranked = sorted(conflicts.items(), key=lambda kv: -sum(len(v) for v in kv[1].values()))
    for name, bases in ranked[:a.show]:
        print(f"  {name}")
        for b, uses in sorted(bases.items(), key=lambda kv: -len(kv[1])):
            sec = common.pe().section_of(int(b, 16)) or "?"
            ex = uses[0]
            print(f"     base {b:<10} {sec:<6} x{len(uses):<3} e.g. field {ex['field']} addend {ex['addend']} in {ex['obj']}")
    if a.json:
        a.json.write_text(json.dumps(dict(stats=stats, conflicts=conflicts, consistent=consistent), indent=1))
        print(f"wrote {a.json}")


if __name__ == "__main__":
    main()
