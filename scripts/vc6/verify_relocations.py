#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; COFF/PE relocation arithmetic, no retail bytes embedded.
"""Check the actual targets hidden by relocation-normalized byte matching.

Checks every DIR32/REL32 field in one supplied span. Addresses come from exact
manifest rows, the tracked binding file scripts/data/symbol_bindings.json, or an
explicit symbol -> VA JSON map that overrides it (also for declarations,
libraries and globals); a mapping is a binding, not a recovered function body.
Unknown or ambiguous targets fail. Same-span local labels use their offset;
so do $L switch labels (jump tables) outside the span in the same section.
String and float literals (??_C@, __real@) bind where the retail bytes equal
their contents, since retail pools them per module.
VC6 _$E<number> callbacks are scoped to the uniquely identified source TU;
otherwise they require an explicit object-local binding.
This complements raw_match.py; it proves neither non-relocation bytes nor
final-link symbol selection. SEARCH_LIBRARY weak defaults remain opt-in and
are reported as conditional.
"""
import argparse
import json
import re
import struct
import sys
from pathlib import Path

from verify_vtable import (ROOT, DEFAULT_MANIFEST, DEFAULT_TOTALS, VerifyError,
                          IMAGE_SYM_CLASS_WEAK_EXTERNAL, defined_symbol,
                          load_pe, manifest_symbol_addrs, parse_coff,
                          resolve_symbol)

DIR32 = 0x0006
REL32 = 0x0014
U32 = 0xFFFFFFFF
IMAGE_SYM_CLASS_STATIC = 3
IMAGE_SYM_CLASS_LABEL = 6
LOCAL_LABEL = re.compile(r"\$L[0-9]+")
LITERAL = re.compile(r"\?\?_C@.+|__real@.+")
DEFAULT_BINDINGS = ROOT / "scripts/data/symbol_bindings.json"


def _address(value):
    if isinstance(value, bool) or not isinstance(value, (str, int)):
        raise VerifyError("binding addresses must be integers or address strings")
    address = int(value, 0) if isinstance(value, str) else value
    if not 0 <= address <= U32:
        raise VerifyError("binding address is outside the 32-bit VA range")
    return address


def _scoped(central, source_tu):
    """Bindings file keys "<tu>::<symbol>" bind a TU-local (static) symbol for that TU only."""
    if not isinstance(central, dict):
        return central
    scoped = {}
    for key, value in central.items():
        tu, sep, name = key.partition("::") if isinstance(key, str) else ("", "", key)
        if not sep:
            scoped[key] = value
        elif tu == source_tu:
            scoped[name] = value
    return scoped


def bindings(manifest, explicit=None, source_tu=None, central=None):
    known = manifest_symbol_addrs(manifest, source_tu)
    for name, addresses in known.items():
        for address in addresses:
            _address(address)
    matched = {name: set(addresses) for name, addresses in known.items()}
    for label, mapping in (("bindings file", _scoped(central, source_tu)), ("--symbol-map", explicit)):
        if mapping is not None and not isinstance(mapping, dict):
            raise VerifyError(f"{label} must contain a JSON object")
        for name, value in (mapping or {}).items():
            if not isinstance(name, str) or not name:
                raise VerifyError("binding names must be nonempty strings")
            address = _address(value)
            if name in matched and address not in matched[name]:
                raise VerifyError(f"{label} binding for {name} conflicts with matched manifest rows")
            known[name] = {address}
    return known


def _literal_size(name):
    """Byte size encoded in a VC6 literal name, or None."""
    real = re.fullmatch(r"__real@([48])@[0-9a-f]+", name)
    if real:
        return int(real.group(1))
    text = re.match(r"\?\?_C@_[01]([0-9]|[A-P]+@)", name)
    if not text:
        return None
    number = text.group(1)
    if number.isdigit():
        return int(number) + 1
    return int("".join("%X" % (ord(c) - ord("A")) for c in number[:-1]), 16)


def _retail_bytes(pe, pe_sections, address, length):
    """Retail image bytes; the zero-filled tail beyond a section's raw data reads as zeros."""
    for _, start, virtual_size, raw_pointer, raw_size in pe_sections:
        if start <= address and address + length <= start + max(virtual_size, raw_size):
            out = bytearray(length)
            filed = max(0, min(address + length, start + min(virtual_size, raw_size)) - address)
            out[:filed] = pe[raw_pointer + address - start:raw_pointer + address - start + filed]
            return bytes(out)
    raise VerifyError(f"retail address {address:#010x} is outside the image sections")


def _literal_address(data, section, target, symbols, address, pe, pe_sections, name):
    extent = min([item["value"] for item in symbols.values()
                  if item["section"] == target["section"] and item["value"] > target["value"]]
                 + [section["raw_size"]])
    size = _literal_size(name)
    if size is not None:
        extent = min(extent, target["value"] + size)
    if any(target["value"] - 4 < offset < extent for offset, _, _ in section["relocs"]):
        raise VerifyError(f"literal {name} contains a relocation")
    if section["uninitialized"]:
        # VC6 emits the all-zero literal "" as a BSS COMDAT.
        content = bytes(extent - target["value"])
    else:
        content = data[section["raw_ptr"] + target["value"]:section["raw_ptr"] + extent]
    if not content or _retail_bytes(pe, pe_sections, address, len(content)) != content:
        raise VerifyError(f"literal {name}: retail bytes at {address:#010x} differ from its contents")
    return address


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
           allow_library_defaults=False, default_bindings_path=DEFAULT_BINDINGS):
    if length <= 0 or not 0 <= address <= U32 or address + length > U32 + 1:
        raise VerifyError("span must be positive and inside the 32-bit VA range")
    manifest = json.loads(Path(manifest_path).read_text())
    explicit = json.loads(Path(symbol_map_path).read_text()) if symbol_map_path else None
    source_tus = {row["tu"] for row in manifest
                  if row.get("tu") and row.get("sym") == symbol
                  and int(row["addr"], 16) == address}
    source_tu = next(iter(source_tus)) if len(source_tus) == 1 else None
    central = None
    if default_bindings_path is not None and (
            Path(default_bindings_path).is_file()
            or Path(default_bindings_path) != DEFAULT_BINDINGS):
        central = json.loads(Path(default_bindings_path).read_text())
    known = bindings(manifest, explicit, source_tu, central)
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
        relative = offset - start
        fmt = "<i" if kind == REL32 else "<I"
        addend = struct.unpack_from(fmt, data, section["raw_ptr"] + offset)[0]
        observed = struct.unpack_from(fmt, retail, relative)[0]
        if kind == REL32:
            observed += address + relative + 4
        observed &= U32
        if name in known:
            candidates = known[name]
            if len(candidates) != 1:
                raise VerifyError(f"ambiguous binding for {name}; supply an explicit selection")
            target_address = next(iter(candidates))
        elif (target["section"] == function["section"]
              and start <= target["value"] < end):
            target_address = address + target["value"] - start
        elif (target["section"] == function["section"]
              and target["storage_class"] in (IMAGE_SYM_CLASS_STATIC, IMAGE_SYM_CLASS_LABEL)
              and LOCAL_LABEL.fullmatch(name)):
            # Switch jump tables and case labels sit at a fixed offset from the
            # function in both images; they are TU-position dependent by name.
            target_address = address + target["value"] - start
        elif LITERAL.fullmatch(name) and target["section"] in sections:
            # Retail pools literals per module, so a literal has no single
            # address; it binds where the retail bytes equal its contents.
            target_address = _literal_address(data, sections[target["section"]], target, symbols,
                                              (observed - addend) & U32, pe, pe_sections, name)
        else:
            raise VerifyError(f"target {name} has no unique matched or explicit binding")
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
    ap.add_argument("--symbol-map", help="JSON symbol -> VA bindings overriding the bindings file; not function-match claims")
    ap.add_argument("--bindings", default=str(DEFAULT_BINDINGS),
                    help="tracked symbol -> VA bindings file (default: %(default)s)")
    ap.add_argument("--no-bindings", action="store_true", help="ignore the bindings file")
    ap.add_argument("--weak-defaults", action="store_true")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--totals", default=str(DEFAULT_TOTALS), help=argparse.SUPPRESS)
    args = ap.parse_args()
    try:
        result = verify(args.obj, args.sym, args.addr, args.len, args.binary,
                        args.manifest, args.symbol_map, args.totals, args.weak_defaults,
                        None if args.no_bindings else args.bindings)
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
