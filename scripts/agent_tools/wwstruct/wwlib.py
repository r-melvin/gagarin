#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Shared helpers for the structure-migration tools: COFF symbol/section reading and the object index."""

import hashlib
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "scripts/vc6"))
import coffgen  # noqa: E402

DATA = ROOT / "scripts/data"


def load_index(objdir):
    """objects.json of a build_project.py output directory."""
    return json.loads((Path(objdir) / "objects.json").read_text())


def object_paths(objdir):
    """{source: Path(obj)} for every successful object."""
    index = load_index(objdir)
    return {o["source"]: Path(objdir) / o["object"] for o in index["objects"] if o.get("success")}


def sections(data):
    """[(name, size, rawptr, characteristics)] indexed by section number - 1."""
    nsec = struct.unpack_from("<H", data, 2)[0]
    out = []
    for i in range(nsec):
        off = 20 + 40 * i
        name = data[off:off + 8].rstrip(b"\0").decode("latin-1")
        size, ptr = struct.unpack_from("<II", data, off + 16)
        chars = struct.unpack_from("<I", data, off + 36)[0]
        out.append((name, size, ptr, chars))
    return out


def section_bytes(data, secs, number):
    _, size, ptr, chars = secs[number - 1]
    if chars & 0x80:   # uninitialised data
        return b"\0" * size
    return data[ptr:ptr + size]


def defined_symbols(data):
    """[(name, section, value, storage_class)] for symbols defined in a section of this object."""
    nsec = struct.unpack_from("<H", data, 2)[0]
    return [(n, s, v, scl) for _, n, v, s, scl, _ in coffgen.read_symbols(data) if 0 < s <= nsec and scl in (2, 3)]


def retail_chd_attributes():
    """{symbol suffix '<Name>@@8' as in ??_R3<Name>@@8: (demangled, attributes)} from rtti_classes.json."""
    classes = json.loads((DATA / "rtti_classes.json").read_text())["classes"]
    out = {}
    for mangled, c in classes.items():
        if mangled.startswith((".?AV", ".?AU")):
            out[mangled[4:] + "8"] = (c["demangled_name"], c["attributes"])
    return out


def section_relocs(data, number):
    """[(offset, type, target symbol index)] of one section."""
    off = 20 + 40 * (number - 1)
    relptr = struct.unpack_from("<I", data, off + 24)[0]
    nrel = struct.unpack_from("<H", data, off + 32)[0]
    return [struct.unpack_from("<IIH", data, relptr + 10 * r) for r in range(nrel)]


def comdat_definitions(path):
    """{symbol: signature} for every external symbol an object defines in a COMDAT section.

    The signature is (section name, raw bytes, relocations by target NAME), so two copies compare equal exactly
    when the linker could substitute one for the other without changing the image."""
    data = Path(path).read_bytes()
    secs = sections(data)
    names = {i: n for i, n, *_ in coffgen.read_symbols(data)}
    out = {}
    for name, sec, value, scl in defined_symbols(data):
        if scl != 2 or not secs[sec - 1][3] & 0x1000:
            continue
        raw = section_bytes(data, secs, sec)
        rel = tuple(sorted((o, t, names.get(s, "?")) for o, s, t in section_relocs(data, sec)))
        out[name] = (secs[sec - 1][0], raw, rel)
    return out


def static_init_symbols(path):
    """The compiler-generated dynamic-initialiser (_$E<n>) and guard/static (_$S<n>) symbols an object defines,
    with the digest of the section that holds them (bytes + relocation target names)."""
    data = Path(path).read_bytes()
    secs = sections(data)
    names = {i: n for i, n, *_ in coffgen.read_symbols(data)}
    out = []
    for name, sec, value, scl in defined_symbols(data):
        if not re.match(r"^_\$[ES]\d+$", name):
            continue
        raw = section_bytes(data, secs, sec)
        rel = sorted((o, t, names.get(s, "?")) for o, s, t in section_relocs(data, sec))
        digest = hashlib.sha256(raw + repr(rel).encode()).hexdigest()[:12]
        out.append({"name": name, "section": secs[sec - 1][0], "offset": value, "size": len(raw), "digest": digest})
    return out
