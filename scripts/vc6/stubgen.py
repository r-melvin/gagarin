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
                   Explicit same-address aliases of matched providers are
                   coalesced only after all COMDAT definitions have identical
                   code and resolved relocation targets.
  order.txt        /ORDER file: the engine .text entries in retail order.
  plan.json        what was placed where, for mapcheck.py and the report.

Data addresses are NOT faithful in M1: data stubs are COMMON symbols and land
wherever the linker puts .bss. Only the engine .text layout is ordered.

M2 (both optional, both read only names, addresses and sizes at link time):
  pin_data    pindata.py derives retail addresses of referenced data and code pointers
              from the matched functions' relocation sites (needs the retail image) and
              retargets those relocations to absolute "<name>@pin<VA>" symbols.
  order_tail  taillink.py orders the import thunks and library code behind the engine
              block from scripts/data/crt_tail_layout.json and writes copies of the
              library members involved to OUT/tail.
"""

import argparse
import bisect
import json
import re
import struct
import sys
from pathlib import Path

import coffgen
import datasource
import hybrid as hybrid_module
import pindata
import rttimap
import taillink
from verify_vtable import VerifyError, parse_coff
from coff_equivalence import plan_folds

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


def link_order(index, manifest):
    """The objects.json entries in the order the link sees them: by the lowest retail address any manifest
    row of the TU claims; objects without rows keep their index order after them."""
    lowest = {}
    for row in manifest:
        a = int(row["addr"], 16)
        if row["tu"] not in lowest or a < lowest[row["tu"]]:
            lowest[row["tu"]] = a
    ordered = sorted(enumerate(index["objects"]),
                     key=lambda t: (lowest.get(t[1].get("source"), 1 << 40), t[0]))
    return [o for _, o in ordered]


def plan(objdir, library_names, out, extra_unresolved=(), manifest=None, extents=None, symbol_bindings=None,
         pin_data=False, pin_plan=None, order_tail=False, libdir=None, tail_layout=None, retail=None,
         source_data=False, data_reject=(), data_search=(), library_imports=False):
    hybrid = retail is not None   # hybrid.Retail: stubs carry retail bytes, leftovers leave the image

    def code_fill(va, size):
        return retail.fill(va, size) if hybrid else 0xCC

    index = json.loads((objdir / "objects.json").read_text())
    if manifest is None:
        manifest = json.loads((DATA / "match_manifest.json").read_text())
    # Link order decides which copy of a COMDAT (an inline function or a compiler-generated destructor
    # emitted by several TUs) the linker keeps: the first object seen wins. Order objects by the lowest
    # retail address their manifest rows claim, as the original link saw its objects in address order;
    # objects without rows keep their index order after them.
    objects = [objdir / o["object"] for o in link_order(index, manifest)]
    if extents is None:
        extents = json.loads((DATA / "function_extents.json").read_text())["entries"]
    bindings, conflicts = load_bindings(manifest, symbol_bindings)
    if pin_data and pin_plan is None:
        pe, _, pe_sections = pindata.load_retail()
        pin_plan = pindata.derive(objdir, index, manifest, pe, pe_sections)
    retail_pins = {}   # pin symbol -> retail VA, defined absolute in stubs.obj
    call_names = pin_plan.get("calls", {}) if pin_plan else {}

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
    parsed_cache = {}

    def parsed_of(path):
        if path not in parsed_cache:
            try:
                parsed_cache[path] = parse_coff(path)
            except VerifyError:
                parsed_cache[path] = None
        return parsed_cache[path]

    by_addr = {}
    for r in manifest:
        by_addr.setdefault(hx(r["addr"]), []).append(r)
    provider = {}
    provider_rows = {}
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
            # hybrid: a name several TUs define (implicit members such as a scalar deleting destructor, COMDAT
            # ANY) may have different bodies; LINK keeps the first, so the row's own body takes a unique name.
            shared = hybrid and obj is not None and obj in defined_in.get(sym, ()) and len(defined_in[sym]) > 1 \
                and any(hybrid_module.function_matches(parsed_of(other), sym, va, hx(r["len"]), retail) is False
                        for other in defined_in[sym] if other != obj)
            if sym in defined_in and sym not in used and not shared:
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
            provider_rows[va] = r
            break

    demoted, trims, trimmed = [], {}, {}
    if hybrid:
        # A compiled body that is not byte-identical to retail's (outside relocation sites) must not
        # take the slot: the image runs it in retail's place. Those slots get retail's bytes.
        for va in sorted(provider):
            row = provider_rows[va]
            obj = tu_object.get(row["tu"])
            if obj is None or parsed_of(obj) is None:
                continue
            if hybrid_module.function_matches(parsed_of(obj), row["sym"], va, hx(row["len"]), retail) is False:
                demoted.append({"addr": f"0x{va:X}", "symbol": row["sym"]})
                del provider[va]
                del provider_rows[va]
        for va, name in provider.items():
            row = provider_rows[va]
            obj = tu_object.get(row["tu"])
            if obj is None or len(defined_in.get(row["sym"], [obj])) > 1 and name == row["sym"]:
                continue
            cut = hybrid_module.pad_trim(parsed_of(obj), row["sym"], va, hx(row["len"]), retail)
            if cut:
                trims.setdefault(obj, []).append(cut)
                trimmed[va] = cut[1]

    # Model explicit same-address COMDAT sharing only after full code and
    # relocation equivalence to an existing matched provider is established.
    fold_providers, fold_definitions = {}, {}
    for va, name in provider.items():
        row = provider_rows[va]
        obj = tu_object.get(row['tu'])
        if name == row['sym']:
            fold_providers[va] = (name, hx(row['len']))
        elif own_rename.get(obj, {}).get(row['sym']) == name:
            fold_providers[va] = (name, hx(row['len']))
            fold_definitions[va] = (row['sym'], [obj])
    fold_rename, folded, fold_rejected = plan_folds(
        fold_providers, defined_in, bindings, fold_definitions)
    folded_names = {row['symbol'] for row in folded}

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
    layout = stub_layout(ordered)
    tail_plan = None
    text_pieces = []   # [va, size, origin, name]: the bytes of .text that come from compiled project objects
    if order_tail:
        # The census gives the last engine function a slot that runs over the import-thunk
        # run behind it; the tail ordering places those thunks, so the slot ends where they begin.
        tail_layout = tail_layout or taillink.load_layout()
        first = taillink.first_address(tail_layout)
        layout = [(va, min(slot, first - va) if va < first else slot, align) for va, slot, align in layout]
    for (va, slot, align), e in zip(layout, ordered):
        if va in provider:
            sym = provider[va]
            order.append(sym)
            size = trimmed.get(va, comdat_size.get(sym, 0))
            text_pieces.append([va, min(size, slot), "project", sym])
            placed.append({"addr": f"0x{va:X}", "symbol": sym, "kind": "matched", "len": e[1],
                           "object_size": f"0x{size:X}"})
            if size > slot:
                # Seen where retail returns early from a binary-patched function
                # and the census lists the dead remainder as its own entry: the
                # next stub gives the bytes back so later entries stay put.
                oversize.append({"addr": f"0x{va:X}", "symbol": sym, "object_size": f"0x{size:X}",
                                 "retail_slot": f"0x{slot:X}"})
                debt += size - slot
            elif size < slot and (va + slot) % 16 or slot - size >= 16 or e[3] == "mixed" or va in trimmed:
                # Retail keeps bytes after this function that the compiled COMDAT
                # (padded to 16) does not cover: hold their place with a filler.
                filler = f"?gap_{va:08X}@@YAXXZ"
                writer.add_code_comdat([filler], slot - size, 1, fill=code_fill(va + size, slot - size))
                order.append(filler)
                placed.append({"addr": f"0x{va + size:X}", "symbol": filler, "kind": "filler",
                               "len": f"0x{slot - size:X}"})
            continue
        names = sorted(n for n in names_at.get(va, ()) if n not in library_names and n not in provided_names
                       and n not in stub_names)
        # A library routine that retail keeps inside the engine block (__ftol): matched code
        # calls it by library name, so the stub at its retail address carries that name too.
        names += sorted(n for n, cva in call_names.items() if cva == va and n in library_names
                        and n not in provided_names and n not in stub_names and n not in names)
        key = f"?stub_{va:08X}@@YAXXZ"
        names = [key] + names
        if debt:
            paid = min(debt, slot - 1)
            slot, align, debt = slot - paid, 1, debt - paid
        writer.add_code_comdat(names, slot, align, fill=code_fill(va, slot))
        stub_names.update(names)
        order.append(key)
        placed.append({"addr": f"0x{va:X}", "symbol": key, "kind": "stub", "len": f"0x{slot:X}",
                       "names": len(names) - 1})

    if order_tail:
        engine_end = max(va + slot for va, slot, _ in layout)
        tail_plan = taillink.plan_tail(tail_layout, libdir or (ROOT / "toolchain/MSVC600/VC98/Lib"),
                                  engine_end, out / "tail")
        for name, size in tail_plan["fillers"]:
            writer.add_code_comdat([name], size, 1, fill=code_fill(int(name[9:17], 16), size) if hybrid else 0xCC)
        order.extend(tail_plan["order"])
        text_pieces.extend([va, size, "library", name] for va, size, name in tail_plan["library_sections"])
        stub_names.update(n for n, _ in tail_plan["fillers"])
        if hybrid and retail.text_end() > tail_plan["end"]:
            # Retail's .text continues past the last identified library section (code the toolchain
            # libraries do not explain); the image keeps its bytes so .rdata begins where retail's does.
            rest = retail.text_end() - tail_plan["end"]
            writer.add_code_comdat(["?hybrid_text_end@@YAXXZ"], rest, 1, fill=code_fill(tail_plan["end"], rest))
            order.append("?hybrid_text_end@@YAXXZ")
            stub_names.add("?hybrid_text_end@@YAXXZ")
        # Matched code can call a library name whose retail target is a different, identical body
        # (memmove calls land on memcpy's code), or a name the ordering does not place (an OLDNAMES alias such as
        # remove): pin such names to what the call sites say.
        placed_at = {name: va for va, name in tail_plan["names_at"].items()}
        if hybrid:
            # Import thunks come from the image, not from the import libraries (whose members would
            # bring their own import tables): same name, same 6 bytes, and the __imp_ slot as an absolute.
            # With library_imports the members are pulled and supply thunks and tables alike.
            for name, addr in ([] if library_imports else tail_plan["thunks"]):
                body = retail.fill(addr, 6)
                writer.add_code_comdat([name], 6, 1, fill=body)
                writer.add_absolute("__imp_" + name, struct.unpack_from("<I", body, 2)[0])
                stub_names.add(name)
            tail_copies = {}
            for sec in tail_layout["sections"]:
                path = out / "tail" / f"{sec['library'].split('.')[0].lower()}_{sec['member_index']:04d}.obj"
                if path in tail_plan["objects"]:
                    tail_copies.setdefault(path, []).append((sec["section"], hx(sec["addr"]), sec["len"]))
            tail_pins, tail_calls, tail_conflicts, tail_sites = pindata.derive_tail(list(tail_copies.items()), retail.pe,
                                                                         retail.sections)
            for name, va in tail_calls.items():
                call_names.setdefault(name, va)
        if pin_plan:
            lo, hi = taillink.first_address(tail_layout), (retail.text_end() if hybrid else tail_plan["end"])
            if hybrid:   # retail is the reference: every called name that derives to one address is bound to it
                lo = TEXT[0]
                moved = {n: va for n, va in call_names.items() if lo <= va < hi and n not in pin_plan["global"]}
            else:
                moved = {n: va for n, va in call_names.items() if lo <= va < hi and placed_at.get(n) != va
                         and n in library_names and n not in pin_plan["global"]}
            pin_plan["global"].update(moved)
            pin_plan["report"]["call_pins_for_library_names"] = {n: f"0x{va:X}" for n, va in sorted(moved.items())}

    # Unordered code stubs: bound names in .text outside the ordered block
    # (CRT placeholders, thunks) and still-unresolved function names.
    ext_len = {hx(e[0]): hx(e[1]) for e in extents}
    data_addrs = sorted({va for name, (va, _) in bindings.items() if section_of(va) in (".rdata", ".data")}
                        | {s[2] for s in DATA_SECTIONS})
    counts = {"aliases": 0, "code_bound_unordered": 0, "code_unbound": 0, "data_bound": 0, "data_unbound": 0}
    unbound = {"function": [], "data": []}
    renamed_away = {n for m in rename.values() for n in m}
    still_defined = set(defined_in) - renamed_away - folded_names
    # A second name for an address that something already defines (a matched
    # function under another view's name, a global the project defines under
    # its own name) becomes a weak alias of that definition.
    defined_at = {va: provider_name for va, provider_name in provider.items()}
    if tail_plan:
        for va, name in tail_plan["names_at"].items():
            defined_at.setdefault(va, name)
    for name in sorted(still_defined):
        if name in bindings:
            defined_at.setdefault(bindings[name][0], name)
    remaining = sorted((referenced | renamed_away | folded_names) - still_defined - library_names - stub_names)
    for sym in remaining:
        va = bindings.get(sym, (None,))[0]
        sec = section_of(va) if va is not None else None
        if va in defined_at and defined_at[va] != sym:
            writer.add_alias(sym, defined_at[va])
            counts["aliases"] += 1
        elif sec == ".text":
            writer.add_code_comdat([sym], max(ext_len.get(va, UNKNOWN_CODE_SIZE), 1), 16 if va % 16 == 0 else 1,
                                   section=".text" if hybrid else TAIL)
            counts["code_bound_unordered"] += 1
        elif sec is not None and pin_data:
            writer.add_absolute(sym, va)
            counts["data_bound"] += 1
        elif sec is not None:
            nxt = data_addrs[bisect.bisect_right(data_addrs, va)]
            writer.add_common(sym, nxt - va)
            counts["data_bound"] += 1
        elif looks_like_function(sym, called):
            writer.add_code_comdat([sym], UNKNOWN_CODE_SIZE, section=".text" if hybrid else TAIL)
            counts["code_unbound"] += 1
            unbound["function"].append(sym)
        else:
            writer.add_common(sym, UNKNOWN_DATA_SIZE)
            counts["data_unbound"] += 1
            unbound["data"].append(sym)

    if not hybrid:   # hybrid: link_m1 passes /INCLUDE instead, so no table lands in the image
        writer.set_anchor(order)
    out.mkdir(parents=True, exist_ok=True)
    link_objects = []
    renamed_total = 0
    order_set = set(order)
    tail_sections = 0
    removed_sections = 0
    pinned_definitions = 0
    pinned_symbols = 0
    data_candidates, data_rejected = [], []
    if source_data:
        if not (hybrid and pin_plan):
            raise ValueError("source_data needs the hybrid image and the pin plan")
        regions = datasource.Regions(retail)
        vtable_vas = {n: va for n, (va, _) in bindings.items() if n.startswith("??_7")}
        for table in (pin_plan["comdat"], pin_plan["global"]):
            vtable_vas.update({n: va for n, va in table.items() if n.startswith("??_7")})
        rtti_json = json.loads((ROOT / "scripts/data/rtti_classes.json").read_text())
        rtti = rttimap.RttiNames(retail, rtti_json["classes"], vtable_vas, rtti_json["type_descriptors_without_locator"])
        init_slots = datasource.initialiser_slots(retail)
        init_sections = [0, 0, 0]   # sections with a placed entry, and of those the ones in consecutive slots
        resolver = datasource.Resolver(
            {name: va for va, name in provider.items()},
            pin_plan["global"], call_names,
            {name: va for va, name in (tail_plan["names_at"].items() if tail_plan else ())},
            {name: va for name, va in (tail_plan["thunks"] if tail_plan else ())},
            {name: va for name, (va, _) in bindings.items()}, rtti,
            aliases={(r["symbol"], int(r["addr"], 16)): provider[int(r["addr"], 16)] for r in reused
                     if int(r["addr"], 16) in provider})
    # M2 data pinning: project definitions of bound globals become absolute symbols at
    # their retail addresses, so code references the retail storage directly.
    pin_map = {name: va for name, (va, _) in bindings.items() if section_of(va) in (".rdata", ".data")} \
        if pin_data else {}
    for path in objects:
        data, changed = path.read_bytes(), False
        if pin_plan:
            data, k, pins = pindata.retarget_object(path, data, pin_plan)
            if k:
                retail_pins.update(pins)
                pinned_symbols += k
                changed = True
        if path in fold_rename:
            data, _ = coffgen.rename_symbols(data, fold_rename[path], retarget_weak_defaults=True)
            changed = True
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
        if pin_map:
            data, k = coffgen.absolutise_symbols(data, pin_map)
            if k:
                pinned_definitions += k
                changed = True
        if source_data:
            def address_of(idx, symbol, path=path):
                pin = pin_plan["object"].get(path, {}).get(idx)
                if pin:
                    return pin[1]
                if symbol["storage_class"] == coffgen.CLASS_EXTERNAL:
                    for table in (pin_plan["global"], pin_plan["comdat"]):
                        if symbol["name"] in table:
                            return table[symbol["name"]]
                    va = bindings.get(symbol["name"], (None,))[0]
                    if va is not None and section_of(va) in (".rdata", ".data"):
                        return va
                    return rtti.address(symbol["name"])
                return None
            parsed = parsed_of(path)
            if parsed is not None:
                acc, rej = datasource.candidates(path, parsed, data, address_of, resolver, retail, regions, data_search)
                data_candidates += acc
                data_rejected += rej
                acc, rej, nsec, consecutive, thunks = datasource.initialisers(path, parsed, data, resolver, init_slots)
                init_sections[2] += thunks
                data_candidates += acc
                data_rejected += rej
                init_sections[0] += nsec
                init_sections[1] += consecutive
        tail = {}
        for idx, names in coffgen.section_symbols(data).items():
            off = 20 + 40 * (idx - 1)
            if data[off:off + 8].rstrip(b"\0") == b".text" and not order_set.intersection(names):
                tail[idx] = TAIL
        for secidx, size in trims.get(path, ()):
            data = coffgen.truncate_section(data, secidx, size)
            changed = True
        if hybrid:
            data, gone = hybrid_module.harden(data, order_set, re.sub(r'\W', '_', path.stem))
            if gone:
                removed_sections += len(gone)
                changed = True
        elif tail:
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
    if hybrid:
        tail_plan_pins = {"object": tail_pins, "site": tail_sites, "global": pin_plan["global"], "comdat": {},
                          "rejected": pin_plan["rejected"]} if tail_plan else None
        for path in tail_plan["objects"] if tail_plan else ():
            data, k, pins = pindata.retarget_object(path, path.read_bytes(), tail_plan_pins)
            retail_pins.update(pins)
            pinned_symbols += k
            data, gone = hybrid_module.harden(data, order_set, re.sub(r'\W', '_', path.stem))
            removed_sections += len(gone)
            path.write_bytes(data)
    for name, va in sorted(retail_pins.items()):
        writer.add_absolute(name, va)
    leftover = []
    if hybrid:
        # Archive members are pulled for every undefined name, however dead the referencing section
        # is, and a pulled member's own sections are roots. Give each library name that is still
        # undefined a placeholder of our own (a droppable COMDAT at the very end of .text: /OPT:REF
        # discards it unless retained code still references it, and then it shows in the map).
        defined_final, undefined_final = set(), set()
        for path in link_objects + (tail_plan["objects"] if tail_plan else []):
            d, u, _, _ = object_symbols(path)
            defined_final |= d
            undefined_final |= u
            defined_final |= {n for _, n, _, sec, scl, _ in coffgen.read_symbols(path.read_bytes())
                              if scl == 2 and sec == -1}
        have = {n for sec in writer.sections for n in sec[3]} | {n for n, _ in writer.commons} \
            | {n for n, _ in writer.absolutes} | {n for n, _ in writer.aliases}
        leftover = sorted((undefined_final - defined_final - have) & library_names)
        if library_imports:   # the import libraries define these: their members are pulled
            imported = {n for n, _ in tail_plan["thunks"]} if tail_plan else set()
            leftover = [n for n in leftover if n not in imported and not n.startswith("__imp_")]
        for name in leftover:
            writer.add_code_comdat([name], UNKNOWN_CODE_SIZE, 1, section=".text" if hybrid else TAIL)
    data_pieces, data_report = [], None
    if source_data:
        data_pieces, data_rejected = datasource.assign(data_candidates, data_rejected)
        for piece in data_pieces:   # data targets of a piece are absolute, like the references of matched code
            for _, tname, _ in piece["relocs"]:
                va = datasource.pin_address(tname)
                if va is not None and tname not in retail_pins:
                    retail_pins[tname] = va
                    writer.add_absolute(tname, va)
        dropped = [p for p in data_pieces if (p["va"], p["size"]) in data_reject]
        data_pieces = [p for p in data_pieces if (p["va"], p["size"]) not in data_reject]
        data_rejected += [{"name": p["names"][0], "kind": p["kind"], "section": "", "size": p["size"], "va": p["va"],
                           "object": p["object"], "why": "differs from retail in the linked image"} for p in dropped]
        data_report = datasource.summarise(data_pieces, data_rejected)
        data_report["initialiser_table"] = {"retail_entries": sum(len(v) for v in init_slots.values()),
                                            "sections_with_placed_entries": init_sections[0],
                                            "sections_in_consecutive_slots": init_sections[1],
                                            "entries_named_through_a_jump_thunk": init_sections[2]}
        out.mkdir(parents=True, exist_ok=True)
        (out / "data_rejected.json").write_text(json.dumps(data_rejected, indent=1) + "\n")
        (out / "data_placed.json").write_text(json.dumps(
            [{k: v for k, v in p.items() if k != "data"} for p in data_pieces], indent=1) + "\n")
    (out / "stubs.obj").write_bytes(writer.build())
    if tail_plan:
        link_objects.extend(tail_plan["objects"])
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
        "sections_made_droppable": removed_sections,
        "hybrid_rows_demoted_to_retail_bytes": demoted,
        "hybrid_padding_trimmed": [f"0x{va:X}" for va in sorted(trimmed)],
        "library_names_stubbed": leftover,
        "order_symbols": order,
        "binding_conflicts": conflicts,
        "collocated_comdats": folded,
        "collocated_comdats_rejected": fold_rejected,
        "matched_rows_without_definition": missing_matched,
        "matched_symbol_at_several_addresses": reused,
        "static_functions_promoted": len(promoted),
        "order_names_not_expressible": [n for n in order if not n.startswith(("?", "@", "_"))],
        "extra_stubs": counts,
        "tail": tail_plan["report"] if tail_plan else None,
        "pinned_definitions": pinned_definitions,
        "pinned_relocations": pinned_symbols,
        "pin_symbols_defined": len(retail_pins),
        "pin_report": pin_plan["report"] if pin_plan else None,
        "tail_pin_conflicts": tail_conflicts if tail_plan and hybrid else None,
        "unbound": unbound,
        "text_pieces": text_pieces,
        "thunk_names": tail_plan["thunks"] if tail_plan else [],
        "data_report": data_report,
        "placed": placed,
        "objects": [str(p) for p in link_objects],
    }
    (out / "plan.json").write_text(json.dumps(result, indent=1) + "\n")
    result["_data_pieces"] = data_pieces
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
