#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; COFF/PE relocation arithmetic, no retail bytes embedded.
"""Check the actual targets hidden by relocation-normalized byte matching.

Checks every DIR32/REL32 field in one supplied span. Addresses come from exact
manifest rows or an explicit symbol -> VA JSON map (also for declarations,
libraries and globals); a mapping is a binding, not a recovered function body.
Unknown or ambiguous targets fail. Same-span local labels use their offset.
VC6 _$E<number> callbacks are scoped to the uniquely identified source TU;
otherwise they require an explicit object-local binding.
This complements raw_match.py; it proves neither non-relocation bytes nor
final-link symbol selection. SEARCH_LIBRARY weak defaults remain opt-in and
are reported as conditional.
"""
import argparse
import json
import struct
import sys
from pathlib import Path

from verify_vtable import (DEFAULT_MANIFEST, DEFAULT_TOTALS, VerifyError,
                          IMAGE_SYM_CLASS_WEAK_EXTERNAL, defined_symbol,
                          load_pe, manifest_symbol_addrs, parse_coff,
                          resolve_symbol)

DIR32 = 0x0006
REL32 = 0x0014
U32 = 0xFFFFFFFF


def _address(value):
    if isinstance(value, bool) or not isinstance(value, (str, int)):
        raise VerifyError("binding addresses must be integers or address strings")
    address = int(value, 0) if isinstance(value, str) else value
    if not 0 <= address <= U32:
        raise VerifyError("binding address is outside the 32-bit VA range")
    return address


def bindings(manifest, explicit=None, source_tu=None):
    known = manifest_symbol_addrs(manifest, source_tu)
    for name, addresses in known.items():
        for address in addresses:
            _address(address)
    if explicit is not None and not isinstance(explicit, dict):
        raise VerifyError("--symbol-map must contain a JSON object")
    for name, value in (explicit or {}).items():
        if not isinstance(name, str) or not name:
            raise VerifyError("binding names must be nonempty strings")
        address = _address(value)
        if name in known and address not in known[name]:
            raise VerifyError(f"explicit binding for {name} conflicts with matched manifest rows")
        known[name] = {address}
    return known


def _span(data, sections, address, length):
    found = []
    for _, start, virtual_size, raw_pointer, raw_size in sections:
        if start <= address and address + length <= start + min(virtual_size, raw_size):
            offset = raw_pointer + address - start
            found.append(data[offset:offset + length])
    if len(found) != 1:
        raise VerifyError("retail span must fit in one file-backed PE section")
    return found[0]


def verify(obj, symbol, address, length, binary, manifest_path=DEFAULT_MANIFEST,
           symbol_map_path=None, totals_path=DEFAULT_TOTALS,
           allow_library_defaults=False):
    if length <= 0 or not 0 <= address <= U32 or address + length > U32 + 1:
        raise VerifyError("span must be positive and inside the 32-bit VA range")
    manifest = json.loads(Path(manifest_path).read_text())
    explicit = json.loads(Path(symbol_map_path).read_text()) if symbol_map_path else None
    source_tus = {row["tu"] for row in manifest
                  if row.get("tu") and row.get("sym") == symbol
                  and int(row["addr"], 16) == address}
    source_tu = next(iter(source_tus)) if len(source_tus) == 1 else None
    known = bindings(manifest, explicit, source_tu)
    totals = json.loads(Path(totals_path).read_text())
    expected_sha = totals.get("_meta", {}).get("sha256")
    if not expected_sha:
        raise VerifyError("pinned SHA-256 missing from progress_totals.json")
    pe, _, pe_sections = load_pe(binary, expected_sha)
    retail = _span(pe, pe_sections, address, length)
    data, sections, symbols, auxiliary = parse_coff(obj)
    function = defined_symbol(sections, symbols, symbol)
    section = sections[function["section"]]
    start = function["value"]
    end = start + length
    if section["uninitialized"] or start < 0 or end > section["raw_size"]:
        raise VerifyError("requested span exceeds initialized COFF symbol section")
    strong = {}
    for item in symbols.values():
        if item["section"] in sections and item["storage_class"] != IMAGE_SYM_CLASS_WEAK_EXTERNAL:
            strong.setdefault(item["name"], {})[(item["section"], item["value"])] = item
    results = []
    occupied = set()
    for offset, index, kind in section["relocs"]:
        if offset >= end or offset + 4 <= start:
            continue
        if offset < start or offset + 4 > end:
            raise VerifyError("relocation crosses the requested span boundary")
        if kind not in (DIR32, REL32):
            raise VerifyError(f"unsupported relocation type {kind:#x}")
        field = set(range(offset, offset + 4))
        if occupied & field:
            raise VerifyError("overlapping relocation fields")
        occupied |= field
        target, defaults = resolve_symbol(
            symbols, auxiliary, index, strong_defined=strong,
            mapped_names=set(known), allow_library_defaults=allow_library_defaults)
        name = target["name"]
        if name in known:
            candidates = known[name]
            if len(candidates) != 1:
                raise VerifyError(f"ambiguous binding for {name}; supply an explicit selection")
            target_address = next(iter(candidates))
        elif (target["section"] == function["section"]
              and start <= target["value"] < end):
            target_address = address + target["value"] - start
        else:
            raise VerifyError(f"target {name} has no unique matched or explicit binding")
        relative = offset - start
        fmt = "<i" if kind == REL32 else "<I"
        addend = struct.unpack_from(fmt, data, section["raw_ptr"] + offset)[0]
        observed = struct.unpack_from(fmt, retail, relative)[0]
        if kind == REL32:
            observed += address + relative + 4
        observed &= U32
        expected = (target_address + addend) & U32
        if observed != expected:
            raise VerifyError(f"+{relative:#x}: {name} resolves to {expected:#010x}, retail target is {observed:#010x}")
        results.append({"offset": relative, "kind": "REL32" if kind == REL32 else "DIR32",
                        "symbol": name, "target": observed, "weak_defaults": defaults})
    return sorted(results, key=lambda row: row["offset"])


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--obj", required=True)
    ap.add_argument("--sym", required=True)
    ap.add_argument("--addr", required=True, type=lambda s: int(s, 0))
    ap.add_argument("--len", required=True, type=lambda s: int(s, 0))
    ap.add_argument("--binary", required=True)
    ap.add_argument("--manifest", default=str(DEFAULT_MANIFEST))
    ap.add_argument("--symbol-map", help="JSON symbol -> VA bindings; not function-match claims")
    ap.add_argument("--weak-defaults", action="store_true")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--totals", default=str(DEFAULT_TOTALS), help=argparse.SUPPRESS)
    args = ap.parse_args()
    try:
        result = verify(args.obj, args.sym, args.addr, args.len, args.binary,
                        args.manifest, args.symbol_map, args.totals, args.weak_defaults)
    except (OSError, ValueError, struct.error, VerifyError) as exc:
        print(f"verify_relocations: FAIL: {exc}", file=sys.stderr)
        return 1
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        for row in result:
            suffix = " [conditional weak default]" if row["weak_defaults"] else ""
            print(f"+{row['offset']:#06x} {row['kind']}: {row['target']:#010x} <- {row['symbol']}{suffix}")
        conditional = any(row["weak_defaults"] for row in result)
        print(f"{len(result)} relocation fields {'conditionally verified' if conditional else 'verified'}; not a byte-match or final-link proof")
    return 0


if __name__ == "__main__":
    sys.exit(main())
