#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Place the statically linked library tail at its retail addresses (milestone M2).

Input is scripts/data/crt_tail_layout.json (tail_layout.py: names, addresses, sizes
and archive coordinates; no retail bytes) and the toolchain's libraries. LINK 6 can
/ORDER only COMDAT sections that it can name, and it lays out the rest by object
order, so each library member that retail's tail uses is copied out of its archive
into a link object in which

  * every identified code section is a COMDAT (a plain .text section gets the
    COMDAT flag and an ANY selection),
  * every such section has an external key symbol (a static one is renamed,
    a nameless one gets a fresh symbol),

and the order list interleaves those keys with the import thunks, in retail order,
with 0xCC fillers (stubs.obj) wherever retail has bytes that are not identified
(or where LINK's alignment padding would not reproduce the gap).
Copies are written to the link directory only; the toolchain archives are not changed.
"""
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import coffgen  # noqa: E402
import crt_ident  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
LAYOUT = ROOT / "scripts/data/crt_tail_layout.json"
THUNK_SIZE = 6


def hx(s):
    return int(s, 16)


def make_comdat_with_key(obj, section, key, offset_zero_names):
    """(object bytes, key symbol name) with `section` (1-based) a COMDAT whose key symbol is external.

    key: preferred external name defined at offset 0 of the section, or None."""
    data = bytearray(obj)
    sec_off = 20 + 40 * (section - 1)
    flags = struct.unpack_from("<I", data, sec_off + 36)[0]
    symptr, nsyms = struct.unpack_from("<II", data, 8)
    rows = coffgen.read_symbols(bytes(data))
    if not flags & coffgen.SCN_LNK_COMDAT:
        struct.pack_into("<I", data, sec_off + 36, flags | coffgen.SCN_LNK_COMDAT)
        for idx, name, value, sec, scl, naux in rows:
            if sec == section and scl == coffgen.CLASS_STATIC and value == 0 and naux and name.startswith("."):
                data[symptr + 18 * (idx + 1) + 14] = coffgen.COMDAT_ANY
                break
    if key:
        return bytes(data), key
    return bytes(data), None


def external_at_zero(obj, section):
    """The first named symbol of the section in symbol-table order: LINK takes that one as the
    section's COMDAT key, whatever its offset (probe: tail_layout of memcpy.obj, pow.obj)."""
    for idx, name, value, sec, scl, naux in coffgen.read_symbols(obj):
        if sec == section and scl in (coffgen.CLASS_EXTERNAL, coffgen.CLASS_STATIC) and not name.startswith("."):
            return idx, name, scl
    return None


def add_symbol(obj, name, section):
    """Append an external symbol `name` defined at offset 0 of `section`."""
    symptr, nsyms = struct.unpack_from("<II", obj, 8)
    strtab_at = symptr + nsyms * 18
    strtab = bytearray(obj[strtab_at:])
    raw = name.encode("latin-1")
    field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strtab))
    if len(raw) > 8:
        strtab.extend(raw + b"\0")
    struct.pack_into("<I", strtab, 0, len(strtab))
    out = bytearray(obj[:strtab_at]) + field + struct.pack("<IhHBB", 0, section, coffgen.DT_FUNCTION, coffgen.CLASS_EXTERNAL, 0)
    struct.pack_into("<I", out, 12, nsyms + 1)
    return bytes(out) + bytes(strtab)


def prepare_member(obj, sections):
    """(object bytes, {section: key}) with every listed section an orderable COMDAT.

    sections: [(section index, unique tag for generated names)]"""
    keys = {}
    for section, tag in sections:
        found = external_at_zero(obj, section)
        flags = struct.unpack_from("<I", obj, 20 + 40 * (section - 1) + 36)[0]
        obj, _ = make_comdat_with_key(obj, section, None, ())
        if found is None:
            key = f"?tail_{tag}@@YAXXZ"
            obj = add_symbol(obj, key, section)
        elif found[2] == coffgen.CLASS_STATIC:
            key = f"?tail_{tag}@@YAXXZ"
            obj, _ = coffgen.rename_symbols(obj, {found[1]: key}, retarget=False, statics=True)
        else:
            key = found[1]
        keys[section] = key
    return obj, keys


def align_up(value, align):
    return (value + align - 1) // align * align


def order_entries(entries, start):
    """Order list for entries [{addr, len, align, name, names}] laid out from `start`.

    Returns (order names, [(filler name, size)], {address: name}, skipped, end address). A filler (an
    align-1 0xCC COMDAT in stubs.obj) is inserted wherever LINK's own alignment padding would not
    reproduce the retail gap; an entry that starts before the previous one ends is skipped."""
    order, fillers, names_at, skipped = [], [], {}, []
    cursor = start
    for e in sorted(entries, key=lambda e: e["addr"]):
        if e["addr"] < cursor:
            skipped.append({"addr": f"0x{e['addr']:X}", "name": e["name"], "why": f"overlaps previous end 0x{cursor:X}"})
            continue
        if align_up(cursor, e["align"]) != e["addr"]:
            fillers.append((f"?tailgap_{cursor:08X}@@YAXXZ", e["addr"] - cursor))
            order.append(fillers[-1][0])
            names_at.setdefault(cursor, fillers[-1][0])
        order.append(e["name"])
        for n, off in e["names"]:
            names_at.setdefault(e["addr"] + off, n)
        cursor = e["addr"] + e["len"]
    return order, fillers, names_at, skipped, cursor


def plan_tail(layout, libdir, start, out):
    """Write the library member copies to `out` and return the ordering plan.

    start: first address after the ordered engine block."""
    out.mkdir(parents=True, exist_ok=True)
    members = {}
    for sec in layout["sections"]:
        members.setdefault((sec["library"], sec["member_index"]), []).append(sec)
    archives = {}
    objects, keys = [], {}
    problems = []
    for (lib, mi), secs in sorted(members.items()):
        if lib not in archives:
            archives[lib] = crt_ident.archive_members(libdir / lib)
        name, obj = archives[lib][mi]
        if name != secs[0]["member"]:
            problems.append({"member": secs[0]["member"], "why": f"archive member {mi} of {lib} is {name}"})
            continue
        obj, k = prepare_member(obj, [(s["section"], s["addr"][2:].upper()) for s in secs])
        keys.update({(lib, mi, section): key for section, key in k.items()})
        path = out / f"{lib.split('.')[0].lower()}_{mi:04d}.obj"
        path.write_bytes(obj)
        objects.append(path)
    entries = []
    for t in layout["thunks"]:
        if t["name"]:
            entries.append({"addr": hx(t["addr"]), "len": THUNK_SIZE, "align": 1, "name": t["name"], "kind": "thunk",
                            "names": [(t["name"], 0)]})
    for s in layout["sections"]:
        key = keys.get((s["library"], s["member_index"], s["section"]))
        if key:
            entries.append({"addr": hx(s["addr"]), "len": s["len"], "align": s["align"], "name": key,
                            "kind": "section", "names": [(n, o) for n, o in s["symbols"]] or [(key, 0)]})
    order, fillers, names_at, skipped, end = order_entries(entries, start)
    thunks = [(e["name"], e["addr"]) for e in entries if e["kind"] == "thunk"]
    return {"objects": objects, "order": order, "thunks": thunks, "fillers": fillers, "names_at": names_at, "end": end,
            "report": {"members_copied": len(objects), "ordered": len(order) - len(fillers), "fillers": len(fillers),
                       "filler_bytes": sum(n for _, n in fillers), "skipped": skipped, "problems": problems}}


def check_map(publics, layout):
    """Compare the linked address of every named layout symbol with retail's.

    publics: {symbol: VA} of the link map. Returns counts and the first mismatches."""
    want = {t["name"]: hx(t["addr"]) for t in layout["thunks"] if t["name"]}
    for s in layout["sections"]:
        for name, off in s["symbols"]:
            want.setdefault(name, hx(s["addr"]) + off)
    ok, off_address, missing = 0, [], 0
    for name, va in want.items():
        got = publics.get(name)
        if got is None:
            missing += 1
        elif got == va:
            ok += 1
        else:
            off_address.append({"symbol": name, "retail": f"0x{va:X}", "linked": f"0x{got:X}"})
    return {"symbols": len(want), "at_retail_address": ok, "displaced": len(off_address), "not_in_map": missing,
            "first_displaced": off_address[:10]}


def first_address(layout):
    """Lowest retail address the layout orders (thunks and identified sections)."""
    return min([hx(t["addr"]) for t in layout["thunks"] if t["name"]] + [hx(s["addr"]) for s in layout["sections"]])


def load_layout(path=LAYOUT):
    return json.loads(Path(path).read_text())
