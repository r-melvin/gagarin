#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; compares COFF vtable relocations with the pinned retail PE.
"""Verify that a compiled COFF vtable resolves slot-for-slot to retail.

This proves only the requested vtable slots. It does not prove whole-image identity.
The optional --weak-defaults mode assumes an unresolved SEARCH_LIBRARY weak
external uses its recorded COFF default. A later final link may find a strong
definition in a library that is not present in this object or manifest, so such
a result is conditional and is not final-link proof.
"""
import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_MANIFEST = ROOT / "scripts/data/match_manifest.json"
DEFAULT_TOTALS = ROOT / "scripts/data/progress_totals.json"
IMAGE_REL_I386_DIR32 = 0x0006
IMAGE_SYM_CLASS_WEAK_EXTERNAL = 105
IMAGE_WEAK_EXTERN_SEARCH_LIBRARY = 2
IMAGE_WEAK_EXTERN_SEARCH_ALIAS = 3


class VerifyError(Exception):
    pass


def _cstring(data, offset, limit=None):
    end = data.find(b"\0", offset, limit)
    if end < 0:
        raise VerifyError("unterminated COFF string")
    return data[offset:end].decode("ascii", errors="strict")


def parse_coff(path):
    """Return sections, primary symbols by index, and section relocations."""
    data = Path(path).read_bytes()
    if len(data) < 20:
        raise VerifyError("truncated COFF header")
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optsize != 0:
        raise VerifyError("input is not an i386 COFF object")
    section_table = 20 + optsize
    if section_table + nsec * 40 > len(data):
        raise VerifyError("truncated COFF section table")
    section_table_end = section_table + nsec * 40
    sym_end = symptr + nsyms * 18
    if nsyms and symptr < section_table_end:
        raise VerifyError("COFF symbol table overlaps file/section headers")
    if symptr and sym_end + 4 > len(data):
        raise VerifyError("truncated COFF symbol table")
    strsize = struct.unpack_from("<I", data, sym_end)[0] if symptr else 0
    if symptr and (strsize < 4 or sym_end + strsize > len(data)):
        raise VerifyError("invalid COFF string table")

    sections = {}
    for secno in range(1, nsec + 1):
        off = section_table + (secno - 1) * 40
        name_raw = data[off:off + 8]
        if name_raw.startswith(b"/") and name_raw[1:2].isdigit():
            if not symptr:
                raise VerifyError("long COFF section name requires a string table")
            try:
                stroff = int(name_raw[1:].split(b"\0", 1)[0])
            except ValueError as exc:
                raise VerifyError("invalid long COFF section name") from exc
            if stroff < 4 or stroff >= strsize:
                raise VerifyError("invalid long COFF section name offset")
            name = _cstring(data, sym_end + stroff, sym_end + strsize)
        else:
            name = name_raw.rstrip(b"\0").decode("ascii", errors="replace")
        raw_size, raw_ptr, reloc_ptr = struct.unpack_from("<III", data, off + 16)
        reloc_count = struct.unpack_from("<H", data, off + 32)[0]
        if raw_ptr + raw_size > len(data) or reloc_ptr + reloc_count * 10 > len(data):
            raise VerifyError(f"truncated data/relocations in COFF section {name}")
        if raw_size and raw_ptr < section_table_end:
            raise VerifyError(f"COFF section {name} raw data overlaps file/section headers")
        if reloc_count and reloc_ptr < section_table_end:
            raise VerifyError(f"COFF section {name} relocations overlap file/section headers")
        relocs = []
        for i in range(reloc_count):
            roff = reloc_ptr + i * 10
            rva, symidx, kind = struct.unpack_from("<IIH", data, roff)
            relocs.append((rva, symidx, kind))
        sections[secno] = {"name": name, "raw_ptr": raw_ptr,
                           "raw_size": raw_size, "relocs": relocs}

    # COFF relocation symbol indices count auxiliary records. Retain those
    # indices when walking, but never treat an auxiliary record as a symbol.
    symbols = {}
    auxiliary = {}
    index = 0
    while index < nsyms:
        off = symptr + index * 18
        if off + 18 > sym_end:
            raise VerifyError("truncated COFF symbol record")
        name_raw = data[off:off + 8]
        if name_raw[:4] == b"\0\0\0\0":
            stroff = struct.unpack_from("<I", name_raw, 4)[0]
            if stroff < 4 or stroff >= strsize:
                raise VerifyError("invalid COFF long symbol name offset")
            name = _cstring(data, sym_end + stroff, sym_end + strsize)
        else:
            name = name_raw.rstrip(b"\0").decode("ascii", errors="replace")
        value, secno = struct.unpack_from("<Ih", data, off + 8)
        storage_class = data[off + 16]
        aux_count = data[off + 17]
        symbols[index] = {"name": name, "value": value, "section": secno,
                          "storage_class": storage_class, "aux_count": aux_count}
        if index + aux_count >= nsyms:
            raise VerifyError("COFF auxiliary symbol count exceeds table")
        for auxno in range(1, aux_count + 1):
            auxidx = index + auxno
            aux_off = symptr + auxidx * 18
            auxiliary[auxidx] = data[aux_off:aux_off + 18]
        index += 1 + aux_count
    return data, sections, symbols, auxiliary


def resolve_symbol(symbols, auxiliary, symbol_index, trail=(), *,
                   strong_defined=None, mapped_names=None,
                   allow_library_defaults=False):
    """Resolve COFF weak-external aliases without guessing decorated names."""
    if symbol_index in trail:
        chain = " -> ".join(map(str, (*trail, symbol_index)))
        raise VerifyError(f"cycle in COFF weak-external alias chain: {chain}")
    symbol = symbols.get(symbol_index)
    if symbol is None:
        if symbol_index in auxiliary:
            raise VerifyError(f"COFF weak-external alias points to auxiliary symbol index {symbol_index}")
        raise VerifyError(f"COFF relocation refers to missing symbol index {symbol_index}")
    if symbol["storage_class"] != IMAGE_SYM_CLASS_WEAK_EXTERNAL:
        return symbol, []
    # A normal definition with the same name wins over a weak external. Also,
    # when the final symbol is already accounted for by a verified manifest row
    # or explicit library map, preserve that name rather than taking its default.
    strong_candidates = (strong_defined or {}).get(symbol["name"], {})
    if strong_candidates:
        if len(strong_candidates) > 1:
            raise VerifyError(f"ambiguous same-name strong COFF definitions for {symbol['name']}")
        return next(iter(strong_candidates.values())), []
    if symbol["name"] in (mapped_names or set()):
        return symbol, []
    if symbol["aux_count"] < 1:
        raise VerifyError(f"weak external {symbol['name']} has no auxiliary alias record")
    aux = auxiliary.get(symbol_index + 1)
    if aux is None:
        raise VerifyError(f"weak external {symbol['name']} has a missing auxiliary record")
    tag_index, characteristics = struct.unpack_from("<II", aux)
    if characteristics == IMAGE_WEAK_EXTERN_SEARCH_LIBRARY:
        if not allow_library_defaults:
            raise VerifyError(f"weak external {symbol['name']} uses SEARCH_LIBRARY; pass --weak-defaults to accept its recorded default")
        target, prior_defaults = resolve_symbol(
            symbols, auxiliary, tag_index, (*trail, symbol_index),
            strong_defined=strong_defined, mapped_names=mapped_names,
            allow_library_defaults=allow_library_defaults)
        return target, [symbol["name"], *prior_defaults]
    if characteristics != IMAGE_WEAK_EXTERN_SEARCH_ALIAS:
        raise VerifyError(f"weak external {symbol['name']} uses unsupported search kind {characteristics}")
    return resolve_symbol(
        symbols, auxiliary, tag_index, (*trail, symbol_index),
        strong_defined=strong_defined, mapped_names=mapped_names,
        allow_library_defaults=allow_library_defaults)


def defined_symbol(sections, symbols, name):
    found = [s for s in symbols.values()
             if s["name"] == name and s["section"] in sections]
    if not found:
        raise VerifyError(f"defined COFF symbol not found: {name}")
    locations = {(s["section"], s["value"]) for s in found}
    if len(locations) != 1:
        raise VerifyError(f"ambiguous COFF definitions for {name}")
    return found[0]


def load_pe(path, expected_sha):
    data = Path(path).read_bytes()
    actual_sha = hashlib.sha256(data).hexdigest()
    if actual_sha.lower() != expected_sha.lower():
        raise VerifyError(f"binary SHA-256 mismatch: expected {expected_sha}, got {actual_sha}")
    if data[:2] != b"MZ":
        raise VerifyError("retail input has no DOS MZ header")
    peoff = struct.unpack_from("<I", data, 0x3C)[0]
    if peoff + 24 > len(data) or data[peoff:peoff + 4] != b"PE\0\0":
        raise VerifyError("retail input has no valid PE signature")
    nsec = struct.unpack_from("<H", data, peoff + 6)[0]
    optsize = struct.unpack_from("<H", data, peoff + 20)[0]
    opt = peoff + 24
    if opt + optsize > len(data) or optsize < 32:
        raise VerifyError("truncated PE optional header")
    magic = struct.unpack_from("<H", data, opt)[0]
    if magic != 0x10B:
        raise VerifyError("retail PE is not PE32")
    image_base = struct.unpack_from("<I", data, opt + 28)[0]
    sec_table = opt + optsize
    if sec_table + nsec * 40 > len(data):
        raise VerifyError("truncated PE section table")
    section_table_end = sec_table + nsec * 40
    sections = []
    for i in range(nsec):
        off = sec_table + i * 40
        name, vsize, rva, rawsize, rawptr = struct.unpack_from("<8sIIII", data, off)
        label = name.rstrip(b"\0").decode("ascii", errors="replace")
        if rawsize and rawptr < section_table_end:
            raise VerifyError(f"PE section {label} raw data overlaps headers")
        if rawptr + rawsize > len(data):
            raise VerifyError(f"PE section {label} raw data exceeds file bounds")
        sections.append((name.rstrip(b"\0").decode("ascii", errors="replace"),
                         image_base + rva, vsize, rawptr, rawsize))
    return data, image_base, sections


def pe_dword(pe_data, sections, va):
    found = []
    for _, start, vsize, rawptr, rawsize in sections:
        if start <= va and va + 4 <= start + min(vsize, rawsize):
            off = rawptr + va - start
            if off + 4 <= len(pe_data):
                found.append(struct.unpack_from("<I", pe_data, off)[0])
    if len(found) > 1:
        raise VerifyError(f"retail VA {va:#x} is ambiguously covered by overlapping PE sections")
    if found:
        return found[0]
    raise VerifyError(f"retail VA {va:#x} is not backed by four file bytes")


def manifest_symbol_addrs(manifest):
    by_symbol = {}
    for row in manifest:
        if row.get("status") != "matched" or row.get("pct") != 100:
            continue
        by_symbol.setdefault(row["sym"], set()).add(int(row["addr"], 16))
    return by_symbol


def verify(obj, vtable_symbol, address, slots, binary, manifest_path,
           symbol_map_path=None, totals_path=DEFAULT_TOTALS,
           allow_library_defaults=False):
    if slots <= 0:
        raise VerifyError("slot count must be positive")
    totals = json.loads(Path(totals_path).read_text())
    expected_sha = totals.get("_meta", {}).get("sha256")
    if not expected_sha:
        raise VerifyError("pinned SHA-256 missing from progress_totals.json")
    manifest = json.loads(Path(manifest_path).read_text())
    known = manifest_symbol_addrs(manifest)
    library = {}
    if symbol_map_path:
        raw_map = json.loads(Path(symbol_map_path).read_text())
        if not isinstance(raw_map, dict):
            raise VerifyError("--symbol-map must contain a JSON object")
        for name, value in raw_map.items():
            library[name] = int(value, 0) if isinstance(value, str) else int(value)

    coff_data, sections, symbols, auxiliary = parse_coff(obj)
    strong_defined = {}
    for symbol in symbols.values():
        if (symbol["section"] in sections
                and symbol["storage_class"] != IMAGE_SYM_CLASS_WEAK_EXTERNAL):
            strong_defined.setdefault(symbol["name"], {})[(symbol["section"], symbol["value"])] = symbol
    vtable = defined_symbol(sections, symbols, vtable_symbol)
    sec = sections[vtable["section"]]
    start = vtable["value"]
    end = start + slots * 4
    if start < 0 or end > sec["raw_size"]:
        raise VerifyError(f"vtable {vtable_symbol} does not contain {slots} complete slots")
    wanted_by_offset = {}
    for rva, symidx, kind in sec["relocs"]:
        if start <= rva < end:
            if kind != IMAGE_REL_I386_DIR32:
                raise VerifyError(f"slot relocation at +{rva-start:#x} has unsupported type {kind:#x}")
            if rva + 4 > end or (rva - start) % 4:
                raise VerifyError(f"misaligned or crossing relocation at +{rva-start:#x}")
            if rva in wanted_by_offset:
                raise VerifyError(f"duplicate relocation at vtable offset +{rva-start:#x}")
            target, defaults = resolve_symbol(
                symbols, auxiliary, symidx, strong_defined=strong_defined,
                mapped_names=set(known) | set(library),
                allow_library_defaults=allow_library_defaults)
            wanted_by_offset[rva] = (target["name"], target["section"],
                                     target["value"], defaults)

    pe, _, pe_sections = load_pe(binary, expected_sha)
    results = []
    for slot in range(slots):
        off = start + slot * 4
        if off not in wanted_by_offset:
            raise VerifyError(f"slot {slot} (+{slot*4:#x}) has no COFF relocation")
        name, target_section, target_value, defaults = wanted_by_offset[off]
        rawptr = sec["raw_ptr"] + off
        addend = struct.unpack_from("<I", coff_data, rawptr)[0]
        if name in known:
            candidates = {addr + addend for addr in known[name]}
        elif name in library:
            candidates = {library[name] + addend}
        else:
            raise VerifyError(f"slot {slot} target {name} has no 100%-matched manifest row or library mapping")
        retail = pe_dword(pe, pe_sections, address + slot * 4)
        if retail not in candidates:
            vals = ", ".join(f"{x:#x}" for x in sorted(candidates))
            raise VerifyError(f"slot {slot}: retail {retail:#x}, {name} resolves to {{{vals}}}")
        results.append((slot, name, retail, defaults))
    return results


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--obj", required=True)
    ap.add_argument("--sym", required=True, help="defined COFF vtable symbol")
    ap.add_argument("--addr", required=True, help="retail vtable VA, first slot")
    ap.add_argument("--slots", required=True, type=int)
    ap.add_argument("--binary", required=True, help="user-supplied pinned retail PE")
    ap.add_argument("--manifest", default=str(DEFAULT_MANIFEST))
    ap.add_argument("--symbol-map", help="JSON object for LIBRARY symbols: symbol -> VA")
    ap.add_argument("--weak-defaults", action="store_true",
                    help="conditionally follow unresolved COFF SEARCH_LIBRARY defaults; this does not prove final-link resolution")
    ap.add_argument("--totals", default=str(DEFAULT_TOTALS), help=argparse.SUPPRESS)
    args = ap.parse_args()
    if args.slots <= 0:
        ap.error("--slots must be positive")
    try:
        results = verify(args.obj, args.sym, int(args.addr, 0), args.slots,
                         args.binary, args.manifest, args.symbol_map, args.totals,
                         args.weak_defaults)
    except (OSError, ValueError, struct.error, VerifyError) as exc:
        print(f"verify_vtable: FAIL: {exc}", file=sys.stderr)
        return 1
    used_defaults = set()
    for slot, name, target, defaults in results:
        suffix = f" [conditional weak default: {', '.join(defaults)}]" if defaults else ""
        used_defaults.update(defaults)
        print(f"slot {slot:2}: {target:#010x} <- {name}{suffix}")
    if used_defaults:
        print("WARNING: this slot result assumes unresolved SEARCH_LIBRARY symbols use their recorded COFF defaults; a final link may select strong library definitions.")
    summary = "conditionally verified" if used_defaults else "verified"
    print(f"vtable slots {summary}: {len(results)}/{args.slots} (scoped slot check; not a whole-image claim)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
