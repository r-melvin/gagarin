#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the developer-supplied pinned PE at build time only.
"""Runnable hybrid image (milestone M2): retail content for everything that is not matched source.

link_m1.py --hybrid reads the pinned retail image ($GAMEMD_BINARY, SHA-256 checked) while it
builds and writes its outputs under build-vc6/ only. Nothing derived from the image is tracked
or committed. The pieces:

  fill(va, n)       retail bytes for an unmatched function slot, a gap or the unidentified end of
                    .text (stubgen writes them into the stub COMDATs instead of 0xCC);
  data_object()     one COFF object whose sections reproduce retail's .rdata, .data (with its
                    .bss extent) and .rsrc at their retail addresses, split where LINK derives
                    PE data directories from section names:

                      .idata$5  import address table      (data directory 12)
                      .rdata    everything up to the import directory
                      .idata$2  import descriptors, .idata$3 their terminator (directory 1)
                      .idata$4  import lookup tables
                      .idata$6  hint/name strings and the rest of .rdata
                      .data     initialised data, .bss the rest of the section
                      .rsrc$01  the resource tree and data (directory 2)

                    LINK sorts $5 first and $2-$6 last in .rdata; the object is linked first so
                    its plain .rdata and .data sections come before any other contribution.
                    Project and library data sections are then removed from the image
                    (coffgen.remove_sections): everything matched code references is pinned to
                    these retail addresses (pindata.py).
"""

import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import coffgen  # noqa: E402
import taillink  # noqa: E402
from verify_vtable import DEFAULT_TOTALS, VerifyError, load_pe  # noqa: E402

IMAGE_BASE = 0x400000
COMDAT_ASSOCIATIVE = 5
DATA_FLAGS = coffgen.SCN_CNT_INITIALIZED_DATA | coffgen.SCN_MEM_READ
IDATA_FLAGS = DATA_FLAGS | coffgen.SCN_MEM_WRITE
BSS_FLAGS = 0x00000080 | coffgen.SCN_MEM_READ | coffgen.SCN_MEM_WRITE   # CNT_UNINITIALIZED_DATA


class Retail:
    """The pinned image, addressed by VA."""

    def __init__(self, binary):
        sha = json.loads(Path(DEFAULT_TOTALS).read_text())["_meta"]["sha256"]
        self.pe, _, self.sections = load_pe(binary, sha)
        self.by_name = {n.decode() if isinstance(n, bytes) else n: (start, vsize, rawptr, rawsize)
                        for n, start, vsize, rawptr, rawsize in self.sections}

    def fill(self, va, n):
        """The n file-backed bytes at VA `va` (zeros past a section's raw data)."""
        for _, start, vsize, rawptr, rawsize in self.sections:
            if start <= va < start + max(vsize, rawsize):
                have = max(0, min(n, start + rawsize - va))
                return self.pe[rawptr + va - start:rawptr + va - start + have] + bytes(n - have)
        raise VerifyError(f"{va:#x} is not in a section of the image")

    def search(self, body):
        """VAs of every occurrence of `body` in the file-backed parts of .rdata and .data."""
        found = []
        for name in (".rdata", ".data"):
            start, _, rawptr, rawsize = self.by_name[name]
            image = self.pe[rawptr:rawptr + rawsize]
            at = image.find(body)
            while at >= 0:
                found.append(start + at)
                at = image.find(body, at + 1)
        return found

    def text_end(self):
        start, vsize, _, _ = self.by_name[".text"]
        return start + vsize

    def directory(self, index):
        pe_off = struct.unpack_from("<I", self.pe, 0x3C)[0]
        rva, size = struct.unpack_from("<II", self.pe, pe_off + 0x78 + 8 * index)
        return IMAGE_BASE + rva, size

    def import_layout(self):
        """(IAT, import descriptors, terminator, ILT, names) as (va, size) pairs inside .rdata."""
        iat = self.directory(12)
        imp_va, imp_size = self.directory(1)
        descriptors = (imp_va, imp_size - 20)
        terminator = (imp_va + imp_size - 20, 20)
        ilt_lo, ilt_hi = None, 0
        at = imp_va
        while True:
            orig, _, _, name_rva, _ = struct.unpack("<IIIII", self.fill(at, 20))
            if not name_rva:
                break
            n = 0
            while struct.unpack("<I", self.fill(IMAGE_BASE + orig + 4 * n, 4))[0]:
                n += 1
            lo = IMAGE_BASE + orig
            ilt_lo = lo if ilt_lo is None else min(ilt_lo, lo)
            ilt_hi = max(ilt_hi, lo + 4 * (n + 1))
            at += 20
        return iat, descriptors, terminator, (ilt_lo, ilt_hi - ilt_lo), (ilt_hi, 0)


def write_object(sections):
    """COFF object from [(name, flags, data or None, size) or (.., relocs)]: relocations are
    [(offset, symbol name, type)] against undefined externals; no other symbols.

    data None gives an uninitialised section of `size` bytes."""
    strtab = bytearray(4)
    index = {}
    symbols = bytearray()
    sections = [tuple(sec) + (() ,) * (5 - len(sec)) for sec in sections]
    for sec in sections:
        for _, name, _ in sec[4]:
            if name not in index:
                raw = name.encode("latin-1")
                field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strtab))
                if len(raw) > 8:
                    strtab += raw + b"\0"
                index[name] = len(index)
                symbols += field + struct.pack("<IhHBB", 0, 0, 0, coffgen.CLASS_EXTERNAL, 0)
    struct.pack_into("<I", strtab, 0, len(strtab))
    offset = 20 + 40 * len(sections)
    headers, body = bytearray(), bytearray()
    for name, flags, data, size, relocs in sections:
        raw = name.encode("latin-1").ljust(8, b"\0")
        align = flags & 0x00F00000 or (coffgen.ALIGN[2] if name == ".idata$6" else coffgen.ALIGN[4])
        if len(relocs) > 0xFFFF:
            raise ValueError("too many relocations in one section")
        relptr = offset + len(data) if relocs else 0
        headers += raw + struct.pack("<IIIIIIHHI", 0, 0, size, offset if data is not None else 0, relptr, 0,
                                     len(relocs), 0, (flags & ~0x00F00000) | align)
        if data is not None:
            body += data
            offset += len(data)
        for off, symbol, kind in relocs:
            body += struct.pack("<IIH", off, index[symbol], kind)
            offset += 10
    return bytes(struct.pack("<HHIIIHH", coffgen.I386, len(sections), 0, offset, len(index), 0, 0) + headers + body
                 + symbols + strtab)


def region_sections(name, flags, va, size, retail, pieces):
    """Sections that tile [va, va+size) of a region: retail fill around the source `pieces`
    (dicts with va, size, data, relocs), all named `name`. The first carries the region's own
    alignment; the rest are byte-aligned so nothing is padded between them."""
    out, cursor = [], va

    def add(lo, data, length, relocs=()):
        first = not out
        out.append((name, flags if first else (flags & ~0x00F00000) | coffgen.ALIGN[1], data, length, list(relocs)))

    for p in pieces:
        if p["va"] > cursor:
            add(cursor, retail.fill(cursor, p["va"] - cursor), p["va"] - cursor)
        add(p["va"], p["data"], p["size"], p["relocs"])
        cursor = p["va"] + p["size"]
    if cursor < va + size or not out:
        add(cursor, retail.fill(cursor, va + size - cursor), va + size - cursor)
    return out


def data_object(retail, pieces=(), library_imports=False):
    """(object bytes, [(section name, VA, size)]) reproducing retail's .rdata, .data and .rsrc.

    pieces: source-placed definitions (datasource.assign) that replace retail fill; each lies inside one
    of the pieces below (initialised ones only: uninitialised definitions need no section).
    library_imports: leave out the import tables ($5, $2, $3, $4, $6): the import libraries supply them."""
    r_start, r_vsize, _, _ = retail.by_name[".rdata"]
    iat, descriptors, terminator, ilt, names = retail.import_layout()
    r_end = r_start + r_vsize
    # LINK starts the plain .rdata contributions on a 16-byte boundary after the IAT; retail's gap is zeros.
    lead_start = (iat[0] + iat[1] + 15) & ~15
    if any(retail.fill(iat[0] + iat[1], lead_start - iat[0] - iat[1])):
        raise VerifyError("the bytes between the import address table and the next .rdata are not zero")
    regions = [
        (".idata$5", iat[0], iat[1]),
        (".rdata", lead_start, descriptors[0] - lead_start),
        (".idata$2", descriptors[0], descriptors[1]),
        (".idata$3", terminator[0], terminator[1]),
        (".idata$4", ilt[0], ilt[1]),
        (".idata$6", names[0], r_end - names[0]),
    ]
    if iat[0] != r_start:
        raise VerifyError("the import address table is not at the start of .rdata")
    d_start, d_vsize, _, d_rawsize = retail.by_name[".data"]
    s_start, s_vsize, _, _ = retail.by_name[".rsrc"]
    regions.append((".data", d_start, d_rawsize))
    regions.append((".rsrc$01", s_start, s_vsize))
    pieces = sorted((p for p in pieces if p["data"] is not None), key=lambda p: p["va"])
    sections, layout = [], []
    for name, va, size in regions:
        if library_imports and name.startswith(".idata"):
            layout.append((name, va, size))
            continue
        inside = [p for p in pieces if va <= p["va"] and p["va"] + p["size"] <= va + size]
        # The attributes of an import library's sections: LINK 6 gives sections of one name with
        # different attributes (alignment included) separate output sections.
        if name.startswith(".idata"):
            flags = IDATA_FLAGS
        elif name == ".data":
            flags = DATA_FLAGS | coffgen.SCN_MEM_WRITE
        else:
            flags = DATA_FLAGS
        sections.extend(region_sections(name, flags, va, size, retail, inside))
        layout.append((name, va, size))
        if name == ".data" and d_vsize > d_rawsize:
            sections.append((".bss", BSS_FLAGS, None, d_vsize - d_rawsize))
            layout.append((".bss", d_start + d_rawsize, d_vsize - d_rawsize))
    stray = [p for p in pieces if not any(va <= p["va"] and p["va"] + p["size"] <= va + size for _, va, size in regions)]
    if stray:
        raise VerifyError(f"a source piece lies outside the data regions: 0x{stray[0]['va']:X}")
    return write_object(sections), layout


def harden(data, order_set, tag):
    """(object bytes, [section indices made droppable]): the hybrid image keeps what is ordered, and
    every other non-COMDAT section becomes an ANY COMDAT with its own key, so /OPT:REF discards it
    unless something retained still references it (LINK 6 ignores IMAGE_SCN_LNK_REMOVE, probe).

    tag: unique per object, it names the generated keys."""
    ordered = {idx for idx, names in coffgen.section_symbols(data).items() if order_set.intersection(names)}
    nsec = struct.unpack_from("<H", data, 2)[0]
    data = bytearray(data)
    # An associative COMDAT (unwind tables, scope tables) is kept whenever its parent is, but the
    # parent's references to it are pinned to retail's copy: make it an ordinary droppable one.
    symptr = struct.unpack_from("<I", data, 8)[0]
    for idx, name, value, section, scl, naux in coffgen.read_symbols(bytes(data)):
        if scl == coffgen.CLASS_STATIC and section > 0 and section not in ordered and naux and value == 0 \
                and name.startswith(".") and data[symptr + 18 * (idx + 1) + 14] == COMDAT_ASSOCIATIVE:
            data[symptr + 18 * (idx + 1) + 12:symptr + 18 * (idx + 1) + 15] = bytes(3)
            off = 20 + 40 * (section - 1)
            struct.pack_into("<I", data, off + 36, struct.unpack_from("<I", data, off + 36)[0] & ~coffgen.SCN_LNK_COMDAT)
    data = bytes(data)
    drop = []
    for idx in range(1, nsec + 1):
        off = 20 + 40 * (idx - 1)
        name = bytes(data[off:off + 8]).rstrip(b"\0").decode("latin-1")
        flags, = struct.unpack_from("<I", data, off + 36)
        if flags & (coffgen.SCN_LNK_COMDAT | coffgen.SCN_LNK_INFO) or name.startswith(".debug") or idx in ordered:
            continue
        drop.append((idx, f"{tag}_{idx}"))
    if not drop:
        return data, []
    # A label (storage class 6) ahead of the first real symbol would be taken as the COMDAT key: make
    # labels in the sections about to become COMDATs ordinary statics.
    dropped = {idx for idx, _ in drop}
    data = bytearray(data)
    symptr = struct.unpack_from("<I", data, 8)[0]
    for idx, name, value, section, scl, naux in coffgen.read_symbols(bytes(data)):
        if scl == 6 and section in dropped:
            data[symptr + 18 * idx + 16] = coffgen.CLASS_STATIC
    data, _ = taillink.prepare_member(bytes(data), drop)
    # An emptied group still pads .text up to its alignment (VirtualSize would no longer be retail's):
    # a droppable .text$x or .text$zz section is a plain .text one.
    renames = {idx: ".text" for idx in dropped
               if bytes(data[20 + 40 * (idx - 1):28 + 40 * (idx - 1)]).startswith(b".text$")}
    if renames:
        data = coffgen.set_section_names(data, renames)
    return data, [idx for idx, _ in drop]


def function_matches(parsed, symbol, address, length, retail):
    """True if the compiled function equals retail's bytes at `address` outside relocation sites,
    False if it differs (or does not cover `length`), None if the object does not define it once.

    parsed: verify_vtable.parse_coff of the object. The image can only hold one body per slot, so
    the hybrid image gives a slot whose function is not byte-identical to retail's bytes instead
    of the compiled body (a wrong body would run in its place)."""
    if parsed is None:
        return None
    data, sections, symbols, _ = parsed
    found = [s for s in symbols.values() if s["name"] == symbol and s["section"] in sections]
    if len(found) != 1:
        return None
    fn = found[0]
    sec = sections[fn["section"]]
    start, end = fn["value"], fn["value"] + length
    if sec["uninitialized"] or end > sec["raw_size"]:
        return False
    ours = bytearray(data[sec["raw_ptr"] + start:sec["raw_ptr"] + end])
    want = bytearray(retail.fill(address, length))
    for offset, _, _ in sec["relocs"]:
        if start <= offset < end:
            lo = offset - start
            ours[lo:lo + 4] = want[lo:lo + 4] = bytes(len(want[lo:lo + 4]))
    return ours == want


def pad_trim(parsed, symbol, address, length, retail):
    """(section index, length) when the bytes the compiler padded the function's section with
    (up to 16-byte alignment) are not what retail has after the function, else None.

    Retail's inter-function bytes are whatever its linker and earlier builds left; the hybrid image
    cuts the padding off the section and fills the gap with retail's bytes instead."""
    if parsed is None:
        return None
    data, sections, symbols, _ = parsed
    found = [s for s in symbols.values() if s["name"] == symbol and s["section"] in sections]
    if len(found) != 1 or found[0]["value"] != 0:
        return None
    sec = sections[found[0]["section"]]
    if sec["uninitialized"] or sec["raw_size"] <= length:
        return None
    pad = bytearray(data[sec["raw_ptr"] + length:sec["raw_ptr"] + sec["raw_size"]])
    want = bytearray(retail.fill(address + length, len(pad)))
    for offset, _, _ in sec["relocs"]:   # a jump table after the function holds relocated addresses
        if length - 3 <= offset < sec["raw_size"]:
            lo = max(0, offset - length)
            pad[lo:lo + 4] = want[lo:lo + 4] = bytes(len(want[lo:lo + 4]))
    if pad == want:
        return None
    return found[0]["section"], length
