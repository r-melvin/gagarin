#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the pinned PE ($GAMEMD_BINARY) at build time only, embeds nothing.
"""Source data swap-in (milestone M3): project data definitions at their retail addresses.

The M2 hybrid image takes all of .rdata and .data from the pinned image. Here every data symbol
that a compiled project object defines, whose retail address is known and whose compiled contents
equal retail's bytes at that address, is placed from the object instead. VC6 LINK cannot /ORDER
data, so the placement is explicit: each accepted definition becomes a section of the hybrid data
object (hybrid.data_object) that sits between sections filled from the pinned image, in address
order, with its relocations kept. Anything else stays retail fill and is reported.

A definition's retail address comes from, in order: the pin derived from matched code
(pindata.py), the symbol bindings. Its compiled contents must equal the bytes at that address
outside relocation sites, and every relocation must name a symbol whose own address is known
and equals `retail dword - compiled addend` (a pin, a placed function, a stub, a library symbol).

Kinds: string (??_C@), float (__real@), vtable (??_7), rtti (??_R), initialiser (.CRT$XCU
entries), global (everything else). Uninitialised definitions (.bss) are zero by construction:
their extents are validated (inside retail's bss, not overlapping) and accounted, nothing is
emitted for them.
"""

import re
import struct

import coffgen
import pindata

SCN_COMDAT = coffgen.SCN_LNK_COMDAT
SCN_UNINIT = 0x00000080
DIR32 = coffgen.REL_DIR32
PIN = re.compile(r"@pin([0-9A-F]{8})$")
SKIP_SECTIONS = (".text", ".debug", ".drectve", ".pdata", ".xdata", ".CRT$XCU")
CRT_INIT = ".CRT$XCU"


def kind_of(name, section):
    if section == ".bss":
        return "bss"
    if name.startswith("??_C@"):
        return "string"
    if name.startswith("__real@"):
        return "float"
    if name.startswith("??_7"):
        return "vtable"
    if name.startswith("??_R"):
        return "rtti"
    if name.startswith(("_$S", "$S")):
        return "guard"
    return "global"


def pin_address(name):
    m = PIN.search(name)
    return int(m.group(1), 16) if m else None


def section_relocs(data, secno):
    """[(offset, symbol index, type)] of the 1-based section of a COFF object."""
    off = 20 + 40 * (secno - 1)
    relptr, = struct.unpack_from("<I", data, off + 24)
    nrel, = struct.unpack_from("<H", data, off + 32)
    flags, = struct.unpack_from("<I", data, off + 36)
    first = 0
    if flags & coffgen.SCN_LNK_NRELOC_OVFL:
        nrel, first = struct.unpack_from("<I", data, relptr)[0], 1
    out = []
    for r in range(first, nrel):
        out.append(struct.unpack_from("<IIH", data, relptr + 10 * r))
    return out


class Resolver:
    """Where each name will be in the linked image: pin names carry it, the rest comes from the plan."""

    def __init__(self, *tables):
        self.tables = tables

    def address(self, name):
        va = pin_address(name)
        if va is not None:
            return va
        for table in self.tables:
            if name in table:
                return table[name]
        return None


def candidates(path, parsed, final, address_of, resolver, retail, regions):
    """Placement candidates of one project object.

    parsed: verify_vtable.parse_coff of the object as compiled; final: the link copy's bytes (relocations
    retargeted to pins, symbols renamed) before sections are made droppable; address_of(idx, symbol)
    gives a symbol's retail address or None. Returns (accepted, rejected) lists of dicts."""
    data, sections, symbols, _ = parsed
    names = {idx: (name, section, scl) for idx, name, _, section, scl, _ in coffgen.read_symbols(final)}
    symptr, = struct.unpack_from("<I", final, 8)
    # A weak external (VC6 writes ??_E, the vector deleting destructor, as one defaulting to ??_G) is
    # referenced through its default, as the object's own code would resolve it.
    for first in list(names):
        idx, seen = first, {first}
        while names[idx][2] == coffgen.CLASS_WEAK_EXTERNAL:
            tag, = struct.unpack_from("<I", final, symptr + 18 * (idx + 1))
            if tag in seen or tag not in names:
                break
            seen.add(tag)
            idx = tag
        names[first] = names[idx]
    by_section = {}
    for idx, s in symbols.items():
        if s["section"] > 0 and s["storage_class"] in (coffgen.CLASS_EXTERNAL, coffgen.CLASS_STATIC) \
                and not s["name"].startswith((".", "$L")):
            by_section.setdefault(s["section"], []).append((s["value"], idx, s))
    accepted, rejected = [], []

    def reject(name, kind, section, why, size=0, va=None):
        rejected.append({"name": name, "kind": kind, "section": section, "why": why, "size": size,
                         "va": va, "object": path.name})

    for secno, lst in sorted(by_section.items()):
        sec = sections[secno]
        if sec["name"].startswith(SKIP_SECTIONS):
            continue
        flags, = struct.unpack_from("<I", data, 20 + 40 * (secno - 1) + 36)
        lst.sort(key=lambda t: t[0])
        if flags & SCN_COMDAT:
            groups = [(0, sec["raw_size"], lst)]
        else:
            groups = []
            for n, (value, idx, s) in enumerate(lst):
                if n and lst[n - 1][0] == value:
                    continue   # an alias of the previous symbol: same extent
                end = next((v for v, _, _ in lst[n + 1:] if v > value), sec["raw_size"])
                groups.append((value, end, [t for t in lst if t[0] == value]))
        for start, end, members in groups:
            size = end - start
            name = members[0][2]["name"]
            kind = kind_of(name, sec["name"])
            if size <= 0:
                continue
            vas = set()
            for value, idx, s in members:
                va = address_of(idx, s)
                if va is not None:
                    vas.add(va - (value - start))
            if not vas:
                reject(name, kind, sec["name"], "no retail address", size)
                continue
            if len(vas) > 1:
                reject(name, kind, sec["name"], "symbols of one section disagree about its address", size)
                continue
            (va,) = vas
            where = regions.locate(va, size)
            if where is None:
                reject(name, kind, sec["name"], "outside retail's data sections", size, va)
                continue
            if sec["uninitialized"]:
                if where == "bss":
                    accepted.append({"names": [m[2]["name"] for m in members], "kind": "bss", "va": va, "size": size,
                                     "data": None, "relocs": [], "object": path.name, "region": where})
                    continue
                body = bytes(size)
            else:
                body = bytes(data[sec["raw_ptr"] + start:sec["raw_ptr"] + end])
            if where == "bss":
                reject(name, kind, sec["name"], "initialised data at an address retail leaves uninitialised", size, va)
                continue
            want = bytearray(retail.fill(va, size))
            ours = bytearray(body)
            relocs, bad = [], None
            for off, symidx, rtype in section_relocs(final, secno):
                if not start <= off < end:
                    continue
                if rtype != DIR32 or off + 4 > end:
                    bad = "relocation other than a 32-bit address"
                    break
                tname, tsec, tscl = names[symidx]
                lo = off - start
                addend, = struct.unpack_from("<I", body, lo)
                got, = struct.unpack_from("<I", want, lo)
                known = resolver.address(tname)
                if known is None:
                    bad = f"relocation target {tname} has no known address"
                    break
                if (known + addend) & 0xFFFFFFFF != got:
                    bad = f"relocation target {tname} is at 0x{known:X}, retail's field says 0x{(got - addend) & 0xFFFFFFFF:X}"
                    break
                ours[lo:lo + 4] = want[lo:lo + 4] = bytes(4)
                if pin_address(tname) is None and regions.locate(known, 1) is not None:
                    # data the object does not define (library or unrecovered data) or another definition:
                    # bound to its retail address like the references of matched code (pindata.py)
                    tname = pindata.pin_name(tname, known)
                relocs.append((lo, tname, rtype))
            if bad:
                reject(name, kind, sec["name"], bad, size, va)
                continue
            if ours != want:
                first = next(i for i in range(size) if ours[i] != want[i])
                reject(name, kind, sec["name"], f"contents differ from retail (first at +0x{first:X})", size, va)
                continue
            accepted.append({"names": [m[2]["name"] for m in members], "kind": kind, "va": va, "size": size,
                             "data": body, "relocs": relocs, "object": path.name, "region": where})
    return accepted, rejected


class Regions:
    """Retail's data ranges: file-backed .rdata and .data, and the .data bss tail."""

    def __init__(self, retail):
        r_start, r_vsize, _, _ = retail.by_name[".rdata"]
        d_start, d_vsize, _, d_raw = retail.by_name[".data"]
        self.ranges = [("file", r_start, r_start + r_vsize), ("file", d_start, d_start + d_raw),
                       ("bss", d_start + d_raw, d_start + d_vsize)]

    def locate(self, va, size):
        for name, lo, hi in self.ranges:
            if lo <= va and va + size <= hi:
                return name
        return None


def assign(accepted, rejected):
    """Drop duplicates and overlaps: returns (pieces sorted by address, rejected).

    Several symbols may carry one definition (a COMDAT every object that uses it defines, an alias):
    a candidate inside an accepted piece whose relocations agree merges into it. Uninitialised
    definitions are trimmed at the next one (the compiler's alignment padding is not retail's)."""
    pieces, bss = [], []
    for cand in sorted(accepted, key=lambda c: (c["va"], -c["size"], c["names"][0], c["object"])):
        group = bss if cand["kind"] == "bss" else pieces
        prev = group[-1] if group else None
        if prev and cand["va"] < prev["va"] + prev["size"]:
            inside = cand["va"] + cand["size"] <= prev["va"] + prev["size"]
            lo = cand["va"] - prev["va"]
            if cand["kind"] == "bss":
                if cand["va"] == prev["va"]:
                    prev["names"] = sorted(set(prev["names"]) | set(cand["names"]))
                    prev["objects"].append(cand["object"])
                    continue
                prev["size"] = cand["va"] - prev["va"]   # the earlier one ends where the next begins
                prev["trimmed"] = True
            elif inside and cand["data"] == prev["data"][lo:lo + cand["size"]] and \
                    sorted(r[0] for r in prev["relocs"] if lo <= r[0] < lo + cand["size"]) == \
                    sorted(r[0] + lo for r in cand["relocs"]):
                prev["names"] = sorted(set(prev["names"]) | set(cand["names"]))
                prev["objects"].append(cand["object"])
                continue
            else:
                rejected.append({"name": cand["names"][0], "kind": cand["kind"], "section": "", "size": cand["size"],
                                 "va": cand["va"], "object": cand["object"],
                                 "why": f"overlaps {prev['names'][0]} at 0x{prev['va']:X}"})
                continue
        cand["objects"] = [cand["object"]]
        group.append(cand)
    return sorted(pieces + bss, key=lambda c: c["va"]), rejected


def summarise(pieces, rejected, top=8):
    """Counts and bytes by kind of placed pieces and rejected candidates, with the largest rejections."""
    placed, refused = {}, {}
    seen = set()
    unique = []
    for r in rejected:   # one definition is rejected once per object that carries it
        if (r["kind"], r["name"]) not in seen:
            seen.add((r["kind"], r["name"]))
            unique.append(r)
    rejected = unique
    for p in pieces:
        e = placed.setdefault(p["kind"], {"symbols": 0, "pieces": 0, "bytes": 0})
        e["symbols"] += len(p["names"])
        e["pieces"] += 1
        e["bytes"] += p["size"]
    reasons = {}
    for r in rejected:
        e = refused.setdefault(r["kind"], {"symbols": 0, "bytes": 0})
        e["symbols"] += 1
        e["bytes"] += r["size"]
        why = re.sub(r"0x[0-9A-F]+|\S*@pin\S*|\S+(?= has no known)", "N", r["why"])
        why = re.sub(r"relocation target .* (has no known address|is at)", r"relocation target \1", why)
        reasons[why] = reasons.get(why, 0) + 1
    biggest = sorted(rejected, key=lambda r: -r["size"])[:top]
    return {"placed": placed, "rejected": refused, "reasons": dict(sorted(reasons.items(), key=lambda kv: -kv[1])),
            "largest_rejected": [{k: (f"0x{v:X}" if k == "va" and v is not None else v) for k, v in r.items()}
                                 for r in biggest]}


def verify_image(image, pieces, retail):
    """{(VA, size): [(offset, linked dword, retail dword)]} for the source-placed pieces whose bytes in
    the linked image differ from retail's (the first 16 differing dwords of each)."""
    import compare_image
    sections = compare_image.image_sections(image)
    bad = {}
    for p in pieces:
        if p["data"] is None:
            continue
        for _, va, vsize, data in sections:
            if va <= p["va"] < va + len(data):
                got = data[p["va"] - va:p["va"] - va + p["size"]]
                want = retail.fill(p["va"], p["size"])
                if got != want:
                    diffs = []
                    for off in range(0, p["size"] - 3, 4):
                        if got[off:off + 4] != want[off:off + 4]:
                            diffs.append((off, struct.unpack_from("<I", got, off)[0], struct.unpack_from("<I", want, off)[0]))
                    bad[(p["va"], p["size"])] = diffs[:16]
                break
        else:
            bad[(p["va"], p["size"])] = []
    return bad
