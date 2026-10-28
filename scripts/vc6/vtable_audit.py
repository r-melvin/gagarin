#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; works on the outputs of link_m1.py --hybrid --source-data (under build-vc6/).
"""Audit the vtables placed from source (milestone M3, step 3).

For every vtable the link placed from a project object, each slot is a relocation against a function name.
The linked slot value is looked up in the placement plan (stubs/plan.json): it should be the first byte of
the function the slot names, as a matched body. Classes:

  own body     the linked address is a matched function's entry and the slot's name is that function's
               name (or is bound to that address)
  alias        a matched function's entry under another name (an identical body kept at one address)
  stub         an unmatched function: the slot points at the retail-filled stub of its address
  library      a toolchain library member or thunk of the tail
  data         an RTTI locator or other object (the slot before the first function)
  elsewhere    not the entry of any placed function: another translation unit's COMDAT copy, a leftover
               placeholder or the middle of something

Vtables whose linked bytes differed from retail were given back to retail fill; link_m1 recorded their
differing slots (data_linked_diff.json) and they are listed with the address the linker used.

Usage:  vtable_audit.py LINK_DIR     (LINK_DIR holds m1.exe, stubs/plan.json, stubs/data_placed.json)
"""

import bisect
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import compare_image  # noqa: E402
import datasource  # noqa: E402
import stubgen  # noqa: E402
import taillink  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]


def classify(name, target, entries, starts, bound, library, data_start=None):
    """(class, detail) of a slot named `name` whose linked value is `target`."""
    if data_start is not None and target >= data_start:
        return "data", None   # an RTTI locator or other object, not a function
    at = bisect.bisect_right(starts, target) - 1
    if at < 0 or entries[at]["end"] <= target:
        return ("library", None) if any(lo <= target < hi for lo, hi in library) else ("elsewhere", None)
    entry = entries[at]
    if entry["addr"] != target:
        return "elsewhere", f"inside {entry['symbol']}"
    if entry["kind"] == "matched":
        pinned = datasource.pin_address(name)   # the reference was bound to this address by the matched code
        if entry["symbol"] == name or bound.get(name) == target or pinned == target:
            return "own body", None
        return "alias", entry["symbol"]
    if entry["kind"] == "stub":
        return "stub", None
    return "elsewhere", entry["kind"]


def audit(link_dir):
    link_dir = Path(link_dir)
    plan = json.loads((link_dir / "stubs/plan.json").read_text())
    placed = json.loads((link_dir / "stubs/data_placed.json").read_text())
    image = (link_dir / "m1.exe").read_bytes()
    sections = compare_image.image_sections(image)
    entries = []
    for p in plan["placed"]:
        addr = int(p["addr"], 16)
        size = int(p.get("object_size", p["len"]), 16) if p["kind"] == "matched" else int(p["len"], 16)
        entries.append({"addr": addr, "end": addr + size, "symbol": p["symbol"], "kind": p["kind"]})
    entries.sort(key=lambda e: e["addr"])
    starts = [e["addr"] for e in entries]
    manifest = json.loads((ROOT / "scripts/data/match_manifest.json").read_text())
    bound = {n: va for n, (va, _) in stubgen.load_bindings(manifest)[0].items()}
    text = next(sec for sec in sections if sec[0] == ".text")
    library = [(taillink.first_address(taillink.load_layout()), text[1] + text[2])]   # thunks, CRT and friends

    def read(va):
        for _, start, _, data in sections:
            if start <= va < start + len(data):
                return struct.unpack_from("<I", data, va - start)[0]
        raise ValueError(f"0x{va:X} not in the image")

    counts, bad, vtables = {}, [], 0
    for piece in placed:
        if piece["kind"] != "vtable":
            continue
        vtables += 1
        for off, name, _ in piece["relocs"]:
            target = read(piece["va"] + off)
            cls, detail = classify(name, target, entries, starts, bound, library, text[1] + text[2])
            counts[cls] = counts.get(cls, 0) + 1
            if cls in ("elsewhere", "alias"):
                bad.append({"vtable": piece["names"][0], "va": f"0x{piece['va']:X}", "slot": off // 4, "name": name,
                            "target": f"0x{target:X}", "class": cls, "detail": detail})
    given_back = []
    diff_path = link_dir / "data_linked_diff.json"
    if diff_path.is_file():
        for key, diffs in json.loads(diff_path.read_text()).items():
            va = int(key.split("+")[0], 16)
            rejected = [r for r in json.loads((link_dir / "stubs/data_rejected.json").read_text())
                        if r["va"] == va and r["kind"] == "vtable"]
            if rejected:
                given_back.append({"vtable": rejected[0]["name"], "va": f"0x{va:X}",
                                   "slots": [{"slot": off // 4, "linked": f"0x{got:X}", "retail": f"0x{want:X}"}
                                             for off, got, want in diffs]})
    wrong = [{"vtable": r["name"], "va": f"0x{r['va']:X}", "why": r["why"]}
             for r in json.loads((link_dir / "stubs/data_rejected.json").read_text())
             if r["kind"] == "vtable" and r["va"] and "is at" in r["why"]]
    return {"vtables_placed": vtables, "slots": sum(counts.values()), "by_class": counts,
            "not_own_body": bad, "given_back_to_retail": given_back,
            "slot_names_a_different_address_than_retail": wrong}


def main(argv=None):
    if len(sys.argv if argv is None else argv) < 2 and argv is None:
        raise SystemExit(__doc__)
    link_dir = (argv or sys.argv[1:])[0]
    result = audit(link_dir)
    (Path(link_dir) / "vtable_audit.json").write_text(json.dumps(result, indent=1) + "\n")
    print(f"{result['vtables_placed']} vtables placed from source, {result['slots']} slots: {result['by_class']}")
    for row in result["given_back_to_retail"]:
        print(f"  given back {row['vtable']} {row['va']}: {row['slots']}")
    print(f"{len(result['slot_names_a_different_address_than_retail'])} vtables not placed: a slot names a function "
          f"bound to another address than retail's slot holds")
    for row in result["not_own_body"][:20]:
        print(f"  {row['class']}: {row['vtable']} slot {row['slot']} {row['name']} -> {row['target']} {row['detail'] or ''}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
