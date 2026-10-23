#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Plan and write the M1 placeholder objects and /ORDER file.

Inputs (all tracked or built from tracked files; the retail exe is not read):
  - the object index of build_project.py (OBJDIR/objects.json),
  - scripts/data/function_extents.json (retail entry points and CFG extents),
  - scripts/data/match_manifest.json and scripts/data/symbol_bindings.json,
  - the public symbols of the libraries the link uses.

Outputs, in OUT:
  stubs.obj        one /Gy COMDAT per engine function that no matched row
                   provides, sized from the extent table, filled with 0xCC and
                   carrying every name bound to that address; COMMON symbols
                   for unresolved data (zero-filled by the linker); a COMDAT
                   for every remaining unresolved function name.
  objects/...      copies of project objects in which definitions that belong
                   to a stubbed address (partial rows, bound non-row helpers)
                   are renamed out of the way (references keep the old name).
  order.txt        /ORDER file: the engine .text entries in retail order.
  plan.json        what was placed where, for mapcheck.py and the report.

Data addresses are NOT faithful in M1: data stubs are COMMON symbols and land
wherever the linker puts .bss. Only the engine .text layout is ordered.
"""

import argparse
import bisect
import json
import re
import struct
import sys
from pathlib import Path

import coffgen

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / "scripts/data"
# Retail section ranges (inventory: PE section table of the pinned exe).
TEXT = (0x401000, 0x401000 + 0x3DF38D)
DATA_SECTIONS = [(".rdata", 0x7E1000, 0x7E1000 + 0x30074), (".data", 0x812000, 0x812000 + 0x367BE4)]
IMAGE = (0x400000, 0xC04000)
# The engine block that /ORDER can place: everything before the first linker
# import-thunk block. Thunks, LIBCMT and COMSUPP come from the libraries.
ORDERED_KINDS = {"engine", "lzo"}
# Grouped section that LINK sorts after every plain .text contribution
# (the toolchain libraries included): code that /ORDER does not place.
TAIL = ".text$zz"
UNKNOWN_DATA_SIZE = 4
UNKNOWN_CODE_SIZE = 16
NAMED = re.compile(r"^(?:[A-Za-z_]\w*?)_([0-9A-Fa-f]{8})$")


def hx(s):
    return int(s, 16)


def name_address(sym):
    """Retail VA embedded in the leading name component (FUN_/DAT_/VT_/Name_<addr>)."""
    if sym.startswith("??"):
        return None
    comp = sym.lstrip("?_@").split("@", 1)[0]
    m = NAMED.match(comp)
    if not m:
        return None
    va = int(m.group(1), 16)
    return va if IMAGE[0] <= va < IMAGE[1] else None


def section_of(va):
    if TEXT[0] <= va < TEXT[1]:
        return ".text"
    for name, lo, hi in DATA_SECTIONS:
        if lo <= va < hi:
            return name
    return None


def object_symbols(path):
    """defined, undefined, called (REL32 targets) external names of one object,
    and {name: raw size of its section} for names defined at a section start."""
    data = path.read_bytes()
    defined, undefined = set(), set()
    names, sizes = {}, {}
    nsec = struct.unpack_from("<H", data, 2)[0]
    for idx, name, value, section, scl, _ in coffgen.read_symbols(data):
        names[idx] = name
        if scl in (2, 3) and 0 < section <= nsec and value == 0 and not name.startswith((".", "$")):
            sizes.setdefault(name, struct.unpack_from("<I", data, 20 + 40 * (section - 1) + 16)[0])
        if scl == 2:
            if section > 0 or (section == 0 and value > 0):
                defined.add(name)
            elif section == 0:
                undefined.add(name)
        elif scl == 105:   # weak external: has a default
            defined.add(name)
    called = set()
    for i in range(nsec):
        off = 20 + 40 * i
        relptr, nrel = struct.unpack_from("<I", data, off + 24)[0], struct.unpack_from("<H", data, off + 32)[0]
        for r in range(nrel):
            _, symidx, kind = struct.unpack_from("<IIH", data, relptr + 10 * r)
            if kind == 0x14 and symidx in names:
                called.add(names[symidx])
    return defined, undefined, called, sizes


def looks_like_function(sym, called):
    if sym in called:
        return True
    if sym.startswith("?"):
        return sym.endswith("Z") and not sym.startswith(("??_7", "??_8"))
    return sym.startswith("@") or bool(re.match(r"^_\w+@\d+$", sym))


def load_bindings(manifest, symbol_bindings=None):
    """name -> (va, source); conflicts -> list."""
    out, conflicts = {}, []

    def put(name, va, source):
        if name in out and out[name][0] != va:
            conflicts.append({"symbol": name, "kept": f"0x{out[name][0]:X}", "kept_source": out[name][1],
                              "dropped": f"0x{va:X}", "dropped_source": source})
            return
        out.setdefault(name, (va, source))

    for r in manifest:
        put(r["sym"], hx(r["addr"]), "manifest")
    if symbol_bindings is None:
        symbol_bindings = json.loads((DATA / "symbol_bindings.json").read_text())
    for key, va in symbol_bindings.items():
        put(key.rsplit("::", 1)[-1], hx(va), "symbol_bindings")
    return out, conflicts


def stub_layout(entries):
    """[(va, slot, align)] for each ordered extent entry: the slot runs to the
    next entry (CFG extent plus the gap after it). VC6 pads every function
    COMDAT to 16 bytes with NOPs itself, so the slot, not the bare extent, is
    what a placeholder must occupy."""
    out = []
    for e in entries:
        va = hx(e[0])
        out.append((va, max(hx(e[1]) + hx(e[2]), 1), min(16, va & -va)))
    return out


def order_name(sym):
    """Spelling of a linker symbol in a LINK 6 /ORDER file: LINK prepends "_" to
    every name that does not start with "?" or "@" (probe: link_m1 tests)."""
    return sym[1:] if sym.startswith("_") else sym


def plan(objdir, library_names, out, extra_unresolved=(), manifest=None, extents=None, symbol_bindings=None):
    index = json.loads((objdir / "objects.json").read_text())
    objects = [objdir / o["object"] for o in index["objects"]]
    if manifest is None:
        manifest = json.loads((DATA / "match_manifest.json").read_text())
    if extents is None:
        extents = json.loads((DATA / "function_extents.json").read_text())["entries"]
    bindings, conflicts = load_bindings(manifest, symbol_bindings)

    defined_in = {}
    referenced, called = set(), set()
    comdat_size, sizes_in = {}, {}
    for path in objects:
        d, u, c, z = object_symbols(path)
        sizes_in[path] = z
        for name, size in z.items():
            comdat_size.setdefault(name, size)
        for name in d:
            defined_in.setdefault(name, []).append(path)
        referenced |= u
        called |= c
    # Names that only library members reference (WinMain, for one) show up in
    # the link log, not in the project objects; link_m1.py feeds them back.
    referenced |= set(extra_unresolved)

    # Which address each matched row provides (first matched row wins).
    # Two cases need the row's own object adjusted (a copy, never the build
    # output): a static function (LINK cannot /ORDER file-local COMDATs) is
    # made external under a unique name, and a name that a second address
    # also uses (one template body per TU in retail, folded to one by our
    # COMDAT ANY) is renamed in the second row's object.
    tu_object = {o["source"]: objdir / o["object"] for o in index["objects"]}
    statics_in = {}
    for path in objects:
        statics_in[path] = {name for _, name, _, sec, scl, _ in coffgen.read_symbols(path.read_bytes())
                            if scl == 3 and sec > 0}
    by_addr = {}
    for r in manifest:
        by_addr.setdefault(hx(r["addr"]), []).append(r)
    provider = {}
    own_rename = {}   # object path -> {old: new} (with references)
    static_rename = {}
    missing_matched, reused, promoted = [], [], []
    used = set()
    for va in sorted(by_addr):
        for r in by_addr[va]:
            if r["status"] != "matched":
                continue
            obj = tu_object.get(r["tu"])
            sym = r["sym"]
            if sym in defined_in and sym not in used:
                provider[va] = sym
            elif obj is not None and sym in statics_in.get(obj, ()):
                provider[va] = f"?static_{va:08X}@@YAXXZ"
                static_rename.setdefault(obj, {})[sym] = provider[va]
                comdat_size[provider[va]] = sizes_in[obj].get(sym, 0)
                promoted.append(f"0x{va:X}")
            elif sym in defined_in and obj is not None and obj in defined_in[sym] \
                    and sym not in own_rename.get(obj, {}):
                provider[va] = f"?dup_{va:08X}@@YAXXZ"
                own_rename.setdefault(obj, {})[sym] = provider[va]
                comdat_size[provider[va]] = sizes_in[obj].get(sym, 0)
                reused.append({"addr": f"0x{va:X}", "symbol": sym})
            else:
                # e.g. one definition claimed by rows at three addresses: it can
                # sit at one of them; the others get a stub of retail size.
                missing_matched.append({"addr": f"0x{va:X}", "symbol": sym})
                continue
            used.add(sym)
            break

    # Every name bound to an address that no matched row provides belongs to
    # the stub at that address; project definitions of it are renamed away.
    names_at = {}
    for name, (va, _) in bindings.items():
        names_at.setdefault(va, set()).add(name)
    unresolved = referenced - set(defined_in) - library_names
    for name in unresolved:
        va = name_address(name)
        if va is not None and name not in bindings:
            bindings[name] = (va, "name")
            names_at.setdefault(va, set()).add(name)
    provided_names = set(provider.values())
    rename = {}   # object path -> {old: new}
    new_names = {}
    for va, names in sorted(names_at.items()):
        # Only code is ordered; data definitions stay where the project has them.
        if va in provider or section_of(va) != ".text":
            continue
        for name in sorted(names):
            if name in library_names or name in provided_names or name not in defined_in:
                continue
            new = new_names.setdefault(name, f"__displaced_{va:08X}_{len(new_names)}")
            for path in defined_in[name]:
                rename.setdefault(path, {})[name] = new

    writer = coffgen.ObjectWriter()
    order, placed = [], []
    stub_names = set()
    ordered = [e for e in extents if e[4] in ORDERED_KINDS]
    oversize = []
    debt = 0   # bytes a compiled function ran past its retail slot
    for (va, slot, align), e in zip(stub_layout(ordered), ordered):
        if va in provider:
            sym = provider[va]
            order.append(sym)
            size = comdat_size.get(sym, 0)
            placed.append({"addr": f"0x{va:X}", "symbol": sym, "kind": "matched", "len": e[1],
                           "object_size": f"0x{size:X}"})
            if size > slot:
                # Seen where retail returns early from a binary-patched function
                # and the census lists the dead remainder as its own entry: the
                # next stub gives the bytes back so later entries stay put.
                oversize.append({"addr": f"0x{va:X}", "symbol": sym, "object_size": f"0x{size:X}",
                                 "retail_slot": f"0x{slot:X}"})
                debt += size - slot
            elif size < slot and (va + slot) % 16 or slot - size >= 16 or e[3] == "mixed":
                # Retail keeps bytes after this function that the compiled COMDAT
                # (padded to 16) does not cover: hold their place with a filler.
                filler = f"?gap_{va:08X}@@YAXXZ"
                writer.add_code_comdat([filler], slot - size, 1)
                order.append(filler)
                placed.append({"addr": f"0x{va + size:X}", "symbol": filler, "kind": "filler",
                               "len": f"0x{slot - size:X}"})
            continue
        names = sorted(n for n in names_at.get(va, ()) if n not in library_names and n not in provided_names
                       and n not in stub_names)
        key = f"?stub_{va:08X}@@YAXXZ"
        names = [key] + names
        if debt:
            paid = min(debt, slot - 1)
            slot, align, debt = slot - paid, 1, debt - paid
        writer.add_code_comdat(names, slot, align)
        stub_names.update(names)
        order.append(key)
        placed.append({"addr": f"0x{va:X}", "symbol": key, "kind": "stub", "len": f"0x{slot:X}",
                       "names": len(names) - 1})

    # Unordered code stubs: bound names in .text outside the ordered block
    # (CRT placeholders, thunks) and still-unresolved function names.
    ext_len = {hx(e[0]): hx(e[1]) for e in extents}
    data_addrs = sorted({va for name, (va, _) in bindings.items() if section_of(va) in (".rdata", ".data")}
                        | {s[2] for s in DATA_SECTIONS})
    counts = {"aliases": 0, "code_bound_unordered": 0, "code_unbound": 0, "data_bound": 0, "data_unbound": 0}
    unbound = {"function": [], "data": []}
    renamed_away = {n for m in rename.values() for n in m}
    still_defined = set(defined_in) - renamed_away
    # A second name for an address that something already defines (a matched
    # function under another view's name, a global the project defines under
    # its own name) becomes a weak alias of that definition.
    defined_at = {va: provider_name for va, provider_name in provider.items()}
    for name in sorted(still_defined):
        if name in bindings:
            defined_at.setdefault(bindings[name][0], name)
    remaining = sorted((referenced | renamed_away) - still_defined - library_names - stub_names)
    for sym in remaining:
        va = bindings.get(sym, (None,))[0]
        sec = section_of(va) if va is not None else None
        if va in defined_at and defined_at[va] != sym:
            writer.add_alias(sym, defined_at[va])
            counts["aliases"] += 1
        elif sec == ".text":
            writer.add_code_comdat([sym], max(ext_len.get(va, UNKNOWN_CODE_SIZE), 1), 16 if va % 16 == 0 else 1,
                                   section=TAIL)
            counts["code_bound_unordered"] += 1
        elif sec is not None:
            nxt = data_addrs[bisect.bisect_right(data_addrs, va)]
            writer.add_common(sym, nxt - va)
            counts["data_bound"] += 1
        elif looks_like_function(sym, called):
            writer.add_code_comdat([sym], UNKNOWN_CODE_SIZE, section=TAIL)
            counts["code_unbound"] += 1
            unbound["function"].append(sym)
        else:
            writer.add_common(sym, UNKNOWN_DATA_SIZE)
            counts["data_unbound"] += 1
            unbound["data"].append(sym)

    writer.set_anchor(order)
    out.mkdir(parents=True, exist_ok=True)
    (out / "stubs.obj").write_bytes(writer.build())
    link_objects = []
    renamed_total = 0
    order_set = set(order)
    tail_sections = 0
    for path in objects:
        data, changed = path.read_bytes(), False
        if path in rename:
            data, k = coffgen.rename_symbols(data, rename[path])
            renamed_total += k
            changed = True
        if path in own_rename:
            data, _ = coffgen.rename_symbols(data, own_rename[path], retarget=False)
            changed = True
        if path in static_rename:
            data, _ = coffgen.rename_symbols(data, static_rename[path], retarget=False, statics=True)
            changed = True
        tail = {}
        for idx, names in coffgen.section_symbols(data).items():
            off = 20 + 40 * (idx - 1)
            if data[off:off + 8].rstrip(b"\0") == b".text" and not order_set.intersection(names):
                tail[idx] = TAIL
        if tail:
            data = coffgen.set_section_names(data, tail)
            tail_sections += len(tail)
            changed = True
        if changed:
            target = out / "objects" / path.relative_to(objdir)
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(data)
            link_objects.append(target)
        else:
            link_objects.append(path)
    link_objects.append(out / "stubs.obj")
    (out / "order.txt").write_text("\n".join(order_name(n) for n in order) + "\n", encoding="latin-1")
    result = {
        "ordered_entries": len(order),
        "matched_placed": sum(1 for p in placed if p["kind"] == "matched"),
        "fillers_placed": sum(1 for p in placed if p["kind"] == "filler"),
        "matched_object_larger_than_retail_slot": oversize,
        "stubs_placed": sum(1 for p in placed if p["kind"] == "stub"),
        "stub_names_bound": sum(p.get("names", 0) for p in placed),
        "unresolved_before_stubs": len(unresolved),
        "renamed_definitions": renamed_total,
        "renamed_objects": len(rename),
        "project_code_sections_moved_to_tail": tail_sections,
        "binding_conflicts": conflicts,
        "matched_rows_without_definition": missing_matched,
        "matched_symbol_at_several_addresses": reused,
        "static_functions_promoted": len(promoted),
        "order_names_not_expressible": [n for n in order if not n.startswith(("?", "@", "_"))],
        "extra_stubs": counts,
        "unbound": unbound,
        "placed": placed,
        "objects": [str(p) for p in link_objects],
    }
    (out / "plan.json").write_text(json.dumps(result, indent=1) + "\n")
    return result


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--objdir", type=Path, required=True)
    ap.add_argument("--out", type=Path, required=True)
    args = ap.parse_args(argv)
    import link_m1
    result = plan(args.objdir.resolve(), link_m1.library_symbols(), args.out.resolve())
    print(json.dumps({k: v for k, v in result.items() if k not in ("placed", "objects", "unbound")}, indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
