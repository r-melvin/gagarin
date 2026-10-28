#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the retail image at run time, embeds no retail bytes.
"""Derive retail addresses of the data that matched code references (milestone M2).

A matched function's compiled bytes equal retail except at relocation sites, so
for every DIR32/REL32 site in a matched span the retail dword minus the addend
stored in our object is the retail address of the referenced symbol:

    target = retail dword - addend            (REL32: retail field + site + 4 - addend)

Targets that fall in .rdata/.data become pins. A pin retargets every relocation
against that symbol (in the link copy of the object) to a new absolute symbol
"<name>@pin<VA>", so the object's own COMDAT or static storage is left intact
and simply becomes unreferenced.

Calls: REL32 sites to code give "calls" {name: retail VA} for the names that derive to a single
address (link_m1 uses them to hang library names on the engine-range stub they call, and
tail_layout.py to resolve library sections that match in several places).

Keys. A symbol that is defined in this object as a COMDAT (float and string
literals, vtables, inline data) or is file-local (statics, section symbols such
as .rdata) is pinned per object: retail pools literals per module, so one name
may legitimately sit at several addresses. Any other symbol (an undefined
external, or a global with one non-COMDAT definition) has one address for the
whole link; a name that derives to two addresses is rejected and left unpinned.
A key whose own sites disagree is rejected too.
"""

import json
import os
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import coffgen  # noqa: E402
from verify_relocations import LITERAL, _literal_address  # noqa: E402
from verify_vtable import DEFAULT_TOTALS, VerifyError, load_pe, parse_coff, pe_dword  # noqa: E402

DIR32, REL32 = 0x06, 0x14
U32 = 0xFFFFFFFF
SCN_COMDAT = 0x1000
DATA_RANGES = [(0x7E1000, 0x7E1000 + 0x30074), (0x812000, 0x812000 + 0x367BE4)]
WEAK_EXTERNAL = 105


def in_data(va):
    return any(lo <= va < hi for lo, hi in DATA_RANGES)


IMAGE_BASE = 0x400000
IMAGE_LO, IMAGE_HI = 0x401000, 0xC04000


def pin_name(name, va):
    return f"{name}@pin{va:08X}"


def rel_pin_name(name, va):
    """Companion for REL32 sites: defined as va - image base (LINK 6 quirk, see coffgen.retarget_relocations)."""
    return f"{name}@pinrel{va:08X}"


def retail_path(binary=None):
    binary = binary or os.environ.get("GAMEMD_BINARY")
    if not binary:
        raise SystemExit("pindata: GAMEMD_BINARY is not set (the retail image is read at run time)")
    return binary


def load_retail(binary=None):
    binary = retail_path(binary)
    sha = json.loads(Path(DEFAULT_TOTALS).read_text())["_meta"]["sha256"]
    return load_pe(binary, sha)


def _comdat(data, section):
    return bool(struct.unpack_from("<I", data, 20 + 40 * (section - 1) + 36)[0] & SCN_COMDAT)


def classify(data, symbol):
    """'object' if the symbol is pinned per object, 'global' if per link, None to skip."""
    scl, sec = symbol["storage_class"], symbol["section"]
    if scl == WEAK_EXTERNAL:
        return None
    if scl == coffgen.CLASS_STATIC:
        return "object" if sec > 0 else None
    if scl != coffgen.CLASS_EXTERNAL:
        return None
    if sec > 0 and _comdat(data, sec):
        return "object"
    return "global"


def site_targets(data, sections, symbols, row_sym, address, length, pe, pe_sections):
    """Yield (symbol index, base VA, kind) for each relocation site in the row's span."""
    function = [s for s in symbols.values() if s["name"] == row_sym and s["section"] in sections]
    if len(function) != 1:
        return
    function = function[0]
    yield from span_targets(data, sections, symbols, function["section"], function["value"], length, address,
                            pe, pe_sections)


def span_targets(data, sections, symbols, secidx, start, length, address, pe, pe_sections, with_offset=False):
    """Yield (symbol index, base VA, kind) for each relocation site in bytes [start, start+length) of a
    section whose byte `start` sits at retail VA `address` ((.., offset) too with with_offset)."""
    section = sections[secidx]
    end = start + length
    if section["uninitialized"] or end > section["raw_size"]:
        return
    for offset, index, kind in section["relocs"]:
        if offset < start or offset + 4 > end or kind not in (DIR32, REL32):
            continue
        sym = symbols.get(index)
        if sym is None or sym["section"] == secidx:
            continue
        rel = offset - start
        fmt = "<i" if kind == REL32 else "<I"
        addend = struct.unpack_from(fmt, data, section["raw_ptr"] + offset)[0]
        try:
            retail = struct.unpack_from(fmt, struct.pack("<I", pe_dword(pe, pe_sections, address + rel)), 0)[0]
        except VerifyError:
            continue
        observed = retail + (address + rel + 4 if kind == REL32 else 0)
        if with_offset:
            yield index, (observed - addend) & U32, kind, offset
        else:
            yield index, (observed - addend) & U32, kind


def derive_tail(copies, pe, pe_sections):
    """Pins for the library tail: copies is [(object path, [(section index, retail VA, length)])].

    Every cross-section target inside the image becomes a per-object pin {path: {symbol index: (name, VA)}}, a symbol
    that derives to two addresses within one object is pinned site by site. The second result is {name: VA} for
    code the tail calls that is defined in no copy (library code retail keeps outside the identified
    sections), so it can be bound to its retail address."""
    pins, calls, conflicts, site_pins = {}, {}, [], {}
    for path, spans in copies:
        try:
            data, sections, symbols, _ = parse_coff(path)
        except VerifyError:
            continue
        seen, where = {}, {}
        for secidx, va, length in spans:
            if secidx not in sections:
                continue
            for idx, base, kind, offset in span_targets(data, sections, symbols, secidx, 0, length, va, pe,
                                                        pe_sections, with_offset=True):
                sym = symbols[idx]
                if IMAGE_LO <= base < IMAGE_HI:   # code and data alike: where the layout is right the pin equals
                    seen.setdefault(idx, set()).add(base)   # the placed address, where it is not retail's wins
                    where.setdefault(idx, []).append((secidx, offset, base))
                if kind == REL32 and sym["section"] == 0 and sym["storage_class"] == coffgen.CLASS_EXTERNAL:
                    calls.setdefault(sym["name"], set()).add(base)
        for idx, bases in seen.items():
            if len(bases) > 1:
                conflicts.append({"symbol": symbols[idx]["name"], "object": path.name,
                                  "addresses": sorted(f"0x{b:X}" for b in bases)})
                for secidx, offset, base in where[idx]:
                    site_pins.setdefault(path, {})[(secidx, offset)] = (symbols[idx]["name"], base)
                continue
            pins.setdefault(path, {})[idx] = (symbols[idx]["name"], next(iter(bases)))
    return pins, {n: next(iter(v)) for n, v in calls.items() if len(v) == 1}, conflicts, site_pins


def derive(objdir, index, manifest, pe, pe_sections):
    """Pin plan: {"global": {name: va}, "object": {obj path: {symidx: (name, va)}}, "report": {...}}."""
    tu_object = {o["source"]: Path(objdir) / o["object"] for o in index["objects"]}
    cache = {}
    obs_object = {}   # (path, symidx) -> {base: sites}
    obs_global = {}   # name -> {base: [(path, symidx, sites)]}
    obs_calls = {}    # name -> {call target VA: sites} (REL32 to code)
    skipped = {"text_or_other": 0, "rows": 0, "sites": 0}
    for row in manifest:
        if row["status"] != "matched":
            continue
        path = tu_object.get(row["tu"])
        if path is None:
            skipped["rows"] += 1
            continue
        if path not in cache:
            try:
                cache[path] = parse_coff(path)
            except VerifyError:
                cache[path] = None
        parsed = cache[path]
        if parsed is None:
            skipped["rows"] += 1
            continue
        data, sections, symbols, _ = parsed
        for idx, base, kind in site_targets(data, sections, symbols, row["sym"], int(row["addr"], 16),
                                            int(row["len"], 16), pe, pe_sections):
            skipped["sites"] += 1
            how = classify(data, symbols[idx])
            # DIR32 sites are pinned wherever they point: function pointers (an atexit callback _$E<n>
            # whose retail callee is another TU's body, project names no matched row provides) and
            # constants that matched code takes as the "address" of an extern.
            code_pointer = kind == DIR32 and not symbols[idx]["name"].startswith((".", "$"))
            if not in_data(base) and not code_pointer:
                skipped["text_or_other"] += 1
                if kind == REL32 and how == "global":
                    obs_calls.setdefault(symbols[idx]["name"], {}).setdefault(base, 0)
                    obs_calls[symbols[idx]["name"]][base] += 1
                continue
            if how == "object":
                obs_object.setdefault((path, idx), {}).setdefault(base, 0)
                obs_object[(path, idx)][base] += 1
            elif how == "global":
                obs_global.setdefault(symbols[idx]["name"], {}).setdefault(base, []).append((path, idx))
    rejected = []
    object_pins, global_pins = {}, {}
    for (path, idx), bases in sorted(obs_object.items(), key=lambda kv: (str(kv[0][0]), kv[0][1])):
        name = cache[path][2][idx]["name"]
        if len(bases) > 1:
            rejected.append({"symbol": name, "object": path.name, "scope": "object",
                             "addresses": sorted(f"0x{b:X}" for b in bases)})
            continue
        (base,) = bases
        object_pins.setdefault(path, {})[idx] = (name, base)
    for name, bases in sorted(obs_global.items()):
        if len(bases) > 1:
            rejected.append({"symbol": name, "scope": "global", "addresses": sorted(f"0x{b:X}" for b in bases)})
            continue
        (base,) = bases
        global_pins[name] = base
    # Literal contents: a pooled literal's retail bytes should equal ours. Informational.
    literal_mismatch = []
    for path, pins in object_pins.items():
        data, sections, symbols, _ = cache[path]
        for idx, (name, base) in pins.items():
            sym = symbols[idx]
            if LITERAL.fullmatch(name) and sym["section"] in sections and sym["storage_class"] == coffgen.CLASS_EXTERNAL:
                try:
                    _literal_address(data, sections[sym["section"]], sym, symbols, base, pe, pe_sections, name)
                except VerifyError as exc:
                    literal_mismatch.append({"symbol": name, "object": path.name, "address": f"0x{base:X}",
                                             "why": str(exc)})
    varying = sorted(name for name in {n for p in object_pins.values() for n, _ in p.values()}
                     if len({b for p in object_pins.values() for n, b in p.values() if n == name}) > 1)
    report = {
        "sites_examined": skipped["sites"], "sites_not_data": skipped["text_or_other"],
        "rows_without_object": skipped["rows"],
        "object_pins": sum(len(p) for p in object_pins.values()),
        "global_pins": len(global_pins),
        "distinct_pin_symbols": len({pin_name(n, b) for p in object_pins.values() for n, b in p.values()}
                                    | {pin_name(n, b) for n, b in global_pins.items()}),
        "rejected_inconsistent": rejected,
        "per_object_names_with_several_addresses": len(varying),
        "literal_content_differs": literal_mismatch,
    }
    # A COMDAT is defined in every object that uses it and LINK keeps one copy (the matched
    # function's own object need not be the one it keeps), so every copy's references to a
    # COMDAT name that derives to one address everywhere are pinned alike.
    by_name = {}
    for path, pins in object_pins.items():
        for idx, (name, base) in pins.items():
            if cache[path][2][idx]["storage_class"] == coffgen.CLASS_EXTERNAL:
                by_name.setdefault(name, set()).add(base)
    comdat_pins = {name: next(iter(vas)) for name, vas in by_name.items() if len(vas) == 1}
    calls = {name: next(iter(vas)) for name, vas in obs_calls.items() if len(vas) == 1}
    report["call_names_with_several_targets"] = sorted(n for n, v in obs_calls.items() if len(v) > 1)
    report["comdat_pins"] = len(comdat_pins)
    return {"global": global_pins, "object": object_pins, "comdat": comdat_pins,
            "rejected": {r["symbol"] for r in rejected if r["scope"] == "global"}, "calls": calls, "report": report}


def retarget_object(path, data, plan):
    """(object bytes, retargeted relocations, {pin symbol: absolute value}) for one link copy of an object."""
    mapping, rel_mapping, pins, sites = {}, {}, {}, {}

    def put(idx, name, va):
        mapping[idx] = pin_name(name, va)
        rel_mapping[idx] = rel_pin_name(name, va)
        pins[mapping[idx]] = va
        pins[rel_mapping[idx]] = va - IMAGE_BASE

    for idx, (name, va) in plan["object"].get(path, {}).items():
        put(idx, name, va)
    if plan["global"] or plan.get("comdat"):
        for idx, name, _, section, scl, _ in coffgen.read_symbols(data):
            if scl != coffgen.CLASS_EXTERNAL or idx in mapping:
                continue
            if section > 0 and _comdat(data, section):
                va = plan.get("comdat", {}).get(name)
            elif name in plan["global"]:
                va = plan["global"][name]
            elif name not in plan.get("rejected", ()):
                va = plan.get("comdat", {}).get(name)   # undefined here, a COMDAT elsewhere
            else:
                va = None
            if va is not None:
                put(idx, name, va)
    for key, (name, va) in plan.get("site", {}).get(path, {}).items():
        sites[key] = (pin_name(name, va), rel_pin_name(name, va))
        pins[sites[key][0]] = va
        pins[sites[key][1]] = va - IMAGE_BASE
    data, count, used = coffgen.retarget_relocations(data, mapping, rel_mapping, sites)
    return data, count, {name: va for name, va in pins.items() if name in used}
