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


def pin_name(name, va):
    return f"{name}@pin{va:08X}"


def load_retail(binary=None):
    binary = binary or os.environ.get("GAMEMD_BINARY")
    if not binary:
        raise SystemExit("pindata: GAMEMD_BINARY is not set (the retail image is read at run time)")
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
    section = sections[function["section"]]
    start, end = function["value"], function["value"] + length
    if section["uninitialized"] or end > section["raw_size"]:
        return
    for offset, index, kind in section["relocs"]:
        if offset < start or offset + 4 > end or kind not in (DIR32, REL32):
            continue
        sym = symbols.get(index)
        if sym is None or sym["section"] == function["section"]:
            continue
        rel = offset - start
        fmt = "<i" if kind == REL32 else "<I"
        addend = struct.unpack_from(fmt, data, section["raw_ptr"] + offset)[0]
        try:
            retail = struct.unpack_from(fmt, struct.pack("<I", pe_dword(pe, pe_sections, address + rel)), 0)[0]
        except VerifyError:
            continue
        observed = retail + (address + rel + 4 if kind == REL32 else 0)
        yield index, (observed - addend) & U32, kind


def derive(objdir, index, manifest, pe, pe_sections):
    """Pin plan: {"global": {name: va}, "object": {obj path: {symidx: (name, va)}}, "report": {...}}."""
    tu_object = {o["source"]: Path(objdir) / o["object"] for o in index["objects"]}
    cache = {}
    obs_object = {}   # (path, symidx) -> {base: sites}
    obs_global = {}   # name -> {base: [(path, symidx, sites)]}
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
            if not in_data(base):
                skipped["text_or_other"] += 1
                continue
            how = classify(data, symbols[idx])
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
    return {"global": global_pins, "object": object_pins, "report": report}


def retarget_object(path, data, plan):
    """(object bytes, retargeted symbols, {pin symbol: va}) for one link copy of an object."""
    mapping, pins = {}, {}
    for idx, (name, va) in plan["object"].get(path, {}).items():
        mapping[idx] = pin_name(name, va)
        pins[mapping[idx]] = va
    if plan["global"]:
        for idx, name, _, section, scl, _ in coffgen.read_symbols(data):
            if scl == coffgen.CLASS_EXTERNAL and name in plan["global"] and idx not in mapping \
                    and not (section > 0 and _comdat(data, section)):
                va = plan["global"][name]
                mapping[idx] = pin_name(name, va)
                pins[mapping[idx]] = va
    data, _ = coffgen.retarget_relocations(data, mapping)
    return data, len(mapping), pins
