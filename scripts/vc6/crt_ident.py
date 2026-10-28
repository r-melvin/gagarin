#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Locate statically linked CRT/COMSUPP/LIBCPMT code in retail's library tail.

Every code section of every archive member is compared with the retail bytes
(read at run time from $GAMEMD_BINARY, which must be the pinned image) with the
section's relocated fields wildcarded. Sections with one possible position are
placed; sections that match in several places are resolved by contiguity with
already placed sections and by preferring members that already have a placement.
Writes a JSON list of placed sections (not tracked) and, with --symbols, a
names-and-addresses census file (no bytes).
"""
import argparse
import json
import os
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
import coffgen  # noqa: E402
from verify_vtable import DEFAULT_TOTALS, load_pe  # noqa: E402

LIBS = ["LIBCMT.LIB", "COMSUPP.LIB", "LIBCPMT.LIB"]
TAIL_START = 0x7C43A0
SCN_CODE = 0x20
SCN_COMDAT = 0x1000
RELOC_SIZES = {0x06: 4, 0x07: 4, 0x14: 4, 0x0A: 2, 0x0B: 4, 0x09: 2}  # DIR32 DIR32NB REL32 SECTION SECREL ...


def archive_members(path):
    """[(member name, object bytes)] of a COFF archive, in archive order."""
    data = Path(path).read_bytes()
    if not data.startswith(b"!<arch>\n"):
        raise ValueError(f"{path} is not a COFF archive")
    pos, longnames, out = 8, b"", []
    while pos + 60 <= len(data):
        name = data[pos:pos + 16].decode("latin-1").rstrip()
        size = int(data[pos + 48:pos + 58])
        body = data[pos + 60:pos + 60 + size]
        pos += 60 + size + (size & 1)
        if name == "//":
            longnames = body
        elif name in ("/", ""):
            continue
        else:
            if name.startswith("/") and name[1:].isdigit():
                at = int(name[1:])
                name = longnames[at:longnames.index(b"\0", at)].decode("latin-1")
            out.append((name.rstrip("/"), body))
    return out


def code_sections(obj):
    """[{index, size, align, data, mask, symbols}] of an object's code sections.

    mask[i] is True where byte i is a relocated field (wildcard).
    """
    if len(obj) < 20 or struct.unpack_from("<H", obj, 0)[0] != 0x14C:
        return []
    nsec = struct.unpack_from("<H", obj, 2)[0]
    optsize = struct.unpack_from("<H", obj, 16)[0]
    syms = {}
    for _, name, value, sec, scl, _ in coffgen.read_symbols(obj):
        if sec > 0 and scl in (2, 3) and not name.startswith("."):
            syms.setdefault(sec, []).append((name, value, scl == 2))
    out = []
    for i in range(nsec):
        off = 20 + optsize + 40 * i
        _, _, _, rawsize, rawptr, relptr, _, nreloc, _, flags = struct.unpack_from("<8sIIIIIIHHI", obj, off)
        if not flags & SCN_CODE or rawsize == 0 or rawptr == 0:
            continue
        data = obj[rawptr:rawptr + rawsize]
        mask = bytearray(rawsize)
        for r in range(nreloc):
            roff, _, rtype = struct.unpack_from("<IIH", obj, relptr + 10 * r)
            for k in range(RELOC_SIZES.get(rtype, 0)):
                if roff + k < rawsize:
                    mask[roff + k] = 1
        align = 1 << (((flags >> 20) & 0xF) - 1) if (flags >> 20) & 0xF else 16
        out.append({"index": i + 1, "size": rawsize, "align": align, "data": data, "mask": bytes(mask),
                    "comdat": bool(flags & SCN_COMDAT), "symbols": syms.get(i + 1, [])})
    return out


def runs(sec):
    """Unmasked (offset, bytes) runs of a section."""
    data, mask, out, i = sec["data"], sec["mask"], [], 0
    while i < len(data):
        if mask[i]:
            i += 1
            continue
        j = i
        while j < len(data) and not mask[j]:
            j += 1
        out.append((i, data[i:j]))
        i = j
    return out


def matches_at(sec, tail, pos):
    if pos < 0 or pos + sec["size"] > len(tail):
        return False
    return all(tail[pos + o:pos + o + len(b)] == b for o, b in sec["runs"])


def candidates(sec, tail):
    if not sec["runs"]:
        return []
    off, run = max(sec["runs"], key=lambda r: len(r[1]))
    probe = run[:16]
    found, at = [], tail.find(probe)
    while at >= 0:
        pos = at - off
        if matches_at(sec, tail, pos):
            found.append(pos)
        at = tail.find(probe, at + 1)
    return found


def align_up(value, align):
    return (value + align - 1) // align * align


def identify(sections, tail):
    """Place sections; returns {section id: tail offset}. Sections are dicts with
    'id', 'member_key', 'cands' (offsets), 'size', 'align'."""
    placed, taken = {}, []   # taken: sorted list of (start, end)
    alive = {s["id"]: set(s["cands"]) for s in sections if s["cands"]}
    by_id = {s["id"]: s for s in sections}
    member_placed = set()
    inferred = set()

    def overlaps(a, b):
        return any(a < e and s < b for s, e in taken)

    def place(sid, pos):
        s = by_id[sid]
        placed[sid] = pos
        taken.append((pos, pos + s["size"]))
        taken.sort()
        member_placed.add(s["member_key"])
        del alive[sid]
        for other, cs in list(alive.items()):
            o = by_id[other]
            cs.difference_update([c for c in cs if c < pos + s["size"] and pos < c + o["size"]])
            if not cs:
                del alive[other]

    progress = True
    while progress:
        progress = False
        claims = {}
        for sid, cs in alive.items():
            for c in cs:
                claims.setdefault((c, by_id[sid]["size"]), []).append(sid)
        for sid in sorted(alive, key=lambda i: len(alive[i])):
            if sid not in alive or len(alive[sid]) != 1:
                continue
            (c,) = alive[sid]
            rivals = [r for r in claims.get((c, by_id[sid]["size"]), []) if r != sid and r in alive]
            if not rivals:
                place(sid, c)
                progress = True
        if progress:
            continue
        ends = {}    # end offset -> member keys of sections ending there
        starts = {}  # start offset -> member keys of sections starting there
        for pid, ppos in placed.items():
            ends.setdefault(ppos + by_id[pid]["size"], set()).add(by_id[pid]["member_key"])
            starts.setdefault(ppos, set()).add(by_id[pid]["member_key"])

        def adjacent(sid, c):
            """Member keys of placed sections touching candidate c (after, or before within padding)."""
            s = by_id[sid]
            keys = set()
            for e, ks in ends.items():
                if align_up(e, s["align"]) == c:
                    keys |= ks
            for st, ks in starts.items():
                if c + s["size"] <= st <= align_up(c + s["size"], 16):
                    keys |= ks
            return keys

        for sid in sorted(alive):
            if sid not in alive:
                continue
            s = by_id[sid]
            adj = {c: adjacent(sid, c) for c in alive[sid]}
            same = [c for c, ks in adj.items() if s["member_key"] in ks]
            near = same if len(same) == 1 else [c for c, ks in adj.items() if ks] if not same else []
            if len(near) == 1:
                rivals = [r for r in claims.get((near[0], s["size"]), []) if r != sid and r in alive
                          and by_id[r]["member_key"] in member_placed]
                if s["member_key"] in member_placed or not rivals:
                    place(sid, near[0])
                    progress = True
        if progress:
            continue
        # identical sections competing for the same spot: prefer a member that already has a placement
        for (c, size), sids in sorted(claims.items()):
            live = [x for x in sids if x in alive and c in alive[x]]
            known = [x for x in live if by_id[x]["member_key"] in member_placed]
            if len(live) > 1 and len(known) == 1 and not overlaps(c, c + size):
                place(known[0], c)
                progress = True
                break
        if progress:
            continue
        # last resort: sibling sections of one member with identical size and candidate set
        # are laid out in object order, so assign them in section order (only for members
        # that already have a placement, to avoid inventing objects)
        groups = {}
        for sid, cs in alive.items():
            groups.setdefault((by_id[sid]["member_key"], by_id[sid]["size"], tuple(sorted(cs))), []).append(sid)
        for (_, _, cs), sids in sorted(groups.items()):
            if len(sids) == len(cs) > 1 and by_id[sids[0]]["member_key"] in member_placed:
                for sid, c in zip(sorted(sids, key=lambda i: by_id[i]["order"]), cs):
                    if sid in alive and c in alive[sid]:
                        place(sid, c)
                        inferred.add(sid)
                progress = True
                break
    return placed, alive, inferred


def split_gap(tail, a, b):
    """Split [a, b) into (kind, start, end): padding (0xCC), import_thunks (jmp [imm32]) or unmatched."""
    out, i = [], a
    while i < b:
        j = i
        if tail[i] == 0xCC:
            while j < b and tail[j] == 0xCC:
                j += 1
            kind = "padding"
        else:
            m = re.compile(rb"(?:\xff\x25[\x00-\xff]{4}){2,}").match(tail, i, b)
            if m:
                j, kind = m.end(), "import_thunks"
            else:
                j = i + 1
                while j < b and tail[j] != 0xCC and not re.compile(rb"\xff\x25[\x00-\xff]{4}\xff\x25").match(tail, j, b):
                    j += 1
                kind = "unmatched"
        if out and out[-1][0] == kind and out[-1][2] == i:
            out[-1] = (kind, out[-1][1], j)
        else:
            out.append((kind, i, j))
        i = j
    return out


def load_retail(start):
    binary = os.environ.get("GAMEMD_BINARY")
    if not binary:
        sys.exit("GAMEMD_BINARY is not set")
    expected = json.loads(Path(DEFAULT_TOTALS).read_text())["_meta"]["sha256"]
    data, _, secs = load_pe(binary, expected)
    for name, va, vsize, rawptr, rawsize in secs:
        if name == ".text":
            end = va + min(vsize, rawsize)
            if start is None:
                start = crt_start(va, data[rawptr:rawptr + end - va])
            return start, data[rawptr + start - va:rawptr + end - va]
    sys.exit("no .text section")


def crt_start(base, tail):
    """First address after the first long import-thunk block (retail's CRT follows it)."""
    for m in re.finditer(rb"(?:\xff\x25[\x00-\xff]{4}){100,}", tail):
        return base + m.end()
    return TAIL_START


def gather(libdir):
    sections = []
    for lib in LIBS:
        for mi, (member, obj) in enumerate(archive_members(libdir / lib)):
            for sec in code_sections(obj):
                sec["runs"] = runs(sec)
                sec["library"], sec["member"] = lib, member
                sec["member_key"] = (lib, mi)
                sec["id"] = len(sections)
                sec["order"] = (LIBS.index(lib), mi, sec["index"])
                sections.append(sec)
    return sections


def run(libdir, start, hints=None):
    base, tail = load_retail(start)
    sections = gather(libdir)
    for s in sections:
        s["cands"] = candidates(s, tail)
    placed, alive, inferred = identify(sections, tail)
    # hints {symbol: retail VA} (e.g. REL32 targets of matched code) settle sections that the
    # first pass could not place; the first archive section defining the name is the one LINK
    # would pull. Placed sections are never moved (matched code may call a body under another
    # library name: memmove calls land on memcpy's identical body).
    if hints:
        seen = set()
        for s in sections:
            for name, value, external in s["symbols"]:
                if external and name in hints and name not in seen:
                    seen.add(name)
                    if s["id"] not in placed and hints[name] - base - value in s["cands"]:
                        s["cands"] = [hints[name] - base - value]
        placed, alive, inferred = identify(sections, tail)
    records, covered = [], []
    for sid, pos in placed.items():
        s = sections[sid]
        ext = [(n, v) for n, v, e in s["symbols"] if e]
        records.append({"addr": f"0x{base + pos:08X}", "len": s["size"], "library": s["library"],
                        "member": s["member"], "member_index": s["member_key"][1], "section": s["index"],
                        "align": s["align"], "symbol": (ext or [(f"{s['member']}#{s['index']}", 0)])[0][0],
                        "symbols": [{"name": n, "addr": f"0x{base + pos + v:08X}"} for n, v in ext],
                        "comdat": s["comdat"], "inferred_by_order": sid in inferred})
        covered.append((pos, pos + s["size"]))
    records.sort(key=lambda r: int(r["addr"], 16))
    covered.sort()
    gaps, cursor = [], 0
    for a, b in covered:
        if a > cursor:
            gaps.append((cursor, a))
        cursor = max(cursor, b)
    if cursor < len(tail):
        gaps.append((cursor, len(tail)))
    gap_records = []
    for a, b in gaps:
        for kind, x, y in split_gap(tail, a, b):
            if gap_records and gap_records[-1]["kind"] == kind and gap_records[-1]["_end"] == x:
                gap_records[-1]["len"] += y - x
                gap_records[-1]["_end"] = y
            else:
                gap_records.append({"addr": f"0x{base + x:08X}", "len": y - x, "kind": kind, "_end": y})
    for g in gap_records:
        del g["_end"]
    groups = {}
    for sid, cs in alive.items():
        s = sections[sid]
        groups.setdefault((tuple(sorted(cs)), s["size"]), []).append(f"{s['library']}:{s['member']}:{s['symbols'][0][0] if s['symbols'] else s['index']}")
    ambiguous = [{"addrs": [f"0x{base + c:08X}" for c in cs], "len": n, "sections": sorted(m)}
                 for (cs, n), m in sorted(groups.items())]
    unplaced = [s for s in sections if s["id"] not in placed]
    stats = {
        "tail_start": f"0x{base:08X}", "tail_len": len(tail),
        "sections_total": len(sections), "sections_placed": len(placed), "sections_inferred_by_order": len(inferred),
        "sections_ambiguous": sum(len(m) for m in groups.values()),
        "bytes_covered": sum(b - a for a, b in covered),
        "gap_bytes_padding": sum(g["len"] for g in gap_records if g["kind"] == "padding"),
        "gap_bytes_import_thunks": sum(g["len"] for g in gap_records if g["kind"] == "import_thunks"),
        "gap_bytes_unmatched": sum(g["len"] for g in gap_records if g["kind"] == "unmatched"),
    }
    order = []
    for r in records:
        if not order or order[-1] != (r["library"], r["member"]):
            order.append((r["library"], r["member"]))
    return {"stats": stats, "sections": records, "gaps": gap_records, "ambiguous": ambiguous,
            "member_order": [{"library": l, "member": m} for l, m in order]}


def census(result):
    """{symbol: address} for symbols that resolve to one address."""
    seen, bad = {}, set()
    for r in result["sections"]:
        if r["inferred_by_order"]:
            continue
        for s in r["symbols"]:
            if s["name"] in seen and seen[s["name"]] != s["addr"]:
                bad.add(s["name"])
            seen[s["name"]] = s["addr"]
    return {k: v for k, v in sorted(seen.items(), key=lambda kv: kv[1]) if k not in bad}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--libdir", type=Path, default=ROOT / "toolchain/MSVC600/VC98/Lib")
    ap.add_argument("--start", type=lambda x: int(x, 0), default=None, help="tail start (default: end of the first import-thunk block)")
    ap.add_argument("--out", type=Path, default=ROOT / "build-vc6/crt_ident.json")
    ap.add_argument("--symbols", type=Path, help="write the symbol-to-address census here")
    args = ap.parse_args(argv)
    result = run(args.libdir, args.start)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(result, indent=1) + "\n")
    if args.symbols:
        args.symbols.write_text(json.dumps(census(result), indent=1) + "\n")
    print(json.dumps(result["stats"], indent=1))


if __name__ == "__main__":
    main()
