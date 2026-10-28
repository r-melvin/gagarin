#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Minimal i386 COFF object writer and symbol renamer (link milestone M1).

Pure Python, no assembler or compiler. Used by stubgen.py to write placeholder
objects. Nothing written here contains retail bytes: code stubs are filled
with 0xCC and data stubs are COMMON symbols (zero-initialised by the linker).
"""

import struct

I386 = 0x14C
SCN_CNT_CODE = 0x00000020
SCN_LNK_COMDAT = 0x00001000
SCN_MEM_EXECUTE = 0x20000000
SCN_MEM_READ = 0x40000000
SCN_CNT_INITIALIZED_DATA = 0x00000040
SCN_MEM_WRITE = 0x80000000
SCN_LNK_NRELOC_OVFL = 0x01000000
REL_DIR32 = 6
REL_REL32 = 0x14
ALIGN = {1: 0x00100000, 2: 0x00200000, 4: 0x00300000, 8: 0x00400000, 16: 0x00500000}
CLASS_EXTERNAL = 2
CLASS_STATIC = 3
CLASS_WEAK_EXTERNAL = 105
WEAK_EXTERN_SEARCH_ALIAS = 3
DT_FUNCTION = 0x20
COMDAT_ANY = 2


class ObjectWriter:
    """Collects code COMDATs, COMMON data symbols and an optional anchor table,
    then writes one object."""

    def __init__(self):
        self.sections = []   # (name, characteristics, data, [external names], comdat)
        self.commons = []    # (name, size)
        self.anchor = []     # names the anchor table points at
        self.aliases = []    # (name, target) weak externals
        self.absolutes = []  # (name, va) absolute symbols (pinned retail addresses)

    def add_code_comdat(self, names, size, align=16, fill=0xCC, section=".text"):
        """One .text COMDAT of `size` fill bytes (`fill`: a byte value, or a bytes object of
        exactly `size` bytes for retail-content stubs); names[0] is the COMDAT key,
        the rest are extra external labels at offset 0 of the same section."""
        if not names or size <= 0:
            raise ValueError("a code stub needs at least one name and a positive size")
        flags = SCN_CNT_CODE | SCN_LNK_COMDAT | SCN_MEM_EXECUTE | SCN_MEM_READ | ALIGN[align]
        content = bytes(fill) if isinstance(fill, (bytes, bytearray)) else bytes([fill]) * size
        if len(content) != size:
            raise ValueError("code stub fill must be exactly `size` bytes")
        self.sections.append((section, flags, content, list(names), True))

    def add_common(self, name, size):
        self.commons.append((name, max(1, size)))

    def add_absolute(self, name, va):
        """An absolute external: references resolve to the fixed address `va`."""
        self.absolutes.append((name, va))

    def add_alias(self, name, target):
        """Weak external: `name` resolves to `target` (defined anywhere in the
        link) unless something else defines `name`."""
        self.aliases.append((name, target))

    def set_anchor(self, names):
        """A .data$zz table of DIR32 pointers to these names, so that /OPT:REF
        keeps every ordered function even when nothing else calls it."""
        self.anchor = list(names)

    def build(self):
        strtab = bytearray(b"\0\0\0\0")
        strings = {}

        def name_field(name):
            raw = name.encode("latin-1")
            if len(raw) <= 8:
                return raw.ljust(8, b"\0")
            if raw not in strings:
                strings[raw] = len(strtab)
                strtab.extend(raw + b"\0")
            return struct.pack("<II", 0, strings[raw])

        sections = list(self.sections)
        if self.anchor:
            sections.append((".data$zz", SCN_CNT_INITIALIZED_DATA | SCN_MEM_READ | SCN_MEM_WRITE | ALIGN[4],
                             bytes(4 * len(self.anchor)), [], False))
        nsec = len(sections)
        if nsec > 0x7FFF:
            raise ValueError("too many sections for one COFF object")
        symbols = bytearray()
        index = {}
        count = 0
        for i, (name, flags, data, externals, comdat) in enumerate(sections, 1):
            symbols += name_field(name) + struct.pack("<IhHBB", 0, i, 0, CLASS_STATIC, 1)
            symbols += struct.pack("<IHHIHB3x", len(data), len(self.anchor) if name == ".data$zz" else 0,
                                   0, 0, 0, COMDAT_ANY if comdat else 0)
            count += 2
            for ext in externals:
                index[ext] = count
                symbols += name_field(ext) + struct.pack("<IhHBB", 0, i, DT_FUNCTION, CLASS_EXTERNAL, 0)
                count += 1
        for name, size in self.commons:
            index[name] = count
            symbols += name_field(name) + struct.pack("<IhHBB", size, 0, 0, CLASS_EXTERNAL, 0)
            count += 1
        for name, va in self.absolutes:
            index[name] = count
            symbols += name_field(name) + struct.pack("<IhHBB", va, -1, 0, CLASS_EXTERNAL, 0)
            count += 1
        def undefined(name):
            nonlocal count, symbols
            if name not in index:   # defined elsewhere: an undefined external here
                index[name] = count
                symbols += name_field(name) + struct.pack("<IhHBB", 0, 0, DT_FUNCTION, CLASS_EXTERNAL, 0)
                count += 1
            return index[name]

        for name, target in self.aliases:
            tag = undefined(target)
            symbols += name_field(name) + struct.pack("<IhHBB", 0, 0, DT_FUNCTION, CLASS_WEAK_EXTERNAL, 1)
            symbols += struct.pack("<II10x", tag, WEAK_EXTERN_SEARCH_ALIAS)
            count += 2
        relocs = bytearray()
        for k, name in enumerate(self.anchor):
            relocs += struct.pack("<IIH", 4 * k, undefined(name), REL_DIR32)
        struct.pack_into("<I", strtab, 0, len(strtab))
        offset = 20 + 40 * nsec
        headers, body = bytearray(), bytearray()
        for name, flags, data, _, _ in sections:
            nrel = len(self.anchor) if name == ".data$zz" else 0
            if nrel > 0xFFFF:
                flags |= SCN_LNK_NRELOC_OVFL
            rel_ptr = offset + len(data) if nrel else 0
            headers += name.encode("latin-1").ljust(8, b"\0")
            headers += struct.pack("<IIIIIIHHI", 0, 0, len(data), offset if data else 0, rel_ptr, 0,
                                   min(nrel, 0xFFFF), 0, flags)
            body += data
            offset += len(data)
            if nrel:
                if nrel > 0xFFFF:   # first relocation carries the real count
                    body += struct.pack("<IIH", nrel + 1, 0, 0)
                    offset += 10
                body += relocs
                offset += len(relocs)
        out = bytearray(struct.pack("<HHIIIHH", I386, nsec, 0, offset, count, 0, 0))
        out += headers + body + symbols + strtab
        return bytes(out)


def read_symbols(data):
    """[(index, name, value, section, storage_class, naux)] of a COFF object."""
    nsec, symptr, nsyms = struct.unpack_from("<H", data, 2)[0], *struct.unpack_from("<II", data, 8)
    strtab = symptr + nsyms * 18
    out, i = [], 0
    while i < nsyms:
        off = symptr + 18 * i
        if data[off:off + 4] == b"\0\0\0\0":
            so = struct.unpack_from("<I", data, off + 4)[0]
            name = data[strtab + so:data.index(b"\0", strtab + so)].decode("latin-1")
        else:
            name = data[off:off + 8].rstrip(b"\0").decode("latin-1")
        value, section, _, scl, naux = struct.unpack_from("<IhHBB", data, off + 8)
        out.append((i, name, value, section, scl, naux))
        i += 1 + naux
    return out


def rename_symbols(data, mapping, retarget=True, statics=False, retarget_weak_defaults=False):
    """Return (object bytes, count) with symbol definitions renamed per
    mapping {old: new}.

    retarget=True moves only the definition: a new undefined external with
    the old name is appended and every relocation that pointed at the renamed
    symbol is retargeted to it, so the object's own references still resolve
    to whatever else defines the old name (a stub at the retail address).
    retarget=False renames the symbol and its references together.
    retarget_weak_defaults=True also redirects weak-external fallback indices
    to the replacement undefined external when retarget=True.
    statics=True renames static (file-local) definitions too and makes them
    external, so LINK can place them through /ORDER (it ignores statics).
    """
    data = bytearray(data)
    nsec = struct.unpack_from("<H", data, 2)[0]
    symptr, nsyms = struct.unpack_from("<II", data, 8)
    strtab_at = symptr + nsyms * 18
    strsize = struct.unpack_from("<I", data, strtab_at)[0]
    if strtab_at + strsize != len(data):
        raise ValueError("string table is not at the end of the object")
    strtab = bytearray(data[strtab_at:])

    def field(raw):
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        off = len(strtab)
        strtab.extend(raw + b"\0")
        return struct.pack("<II", 0, off)

    retargets = {}
    added = bytearray()
    renamed = 0
    symbol_rows = read_symbols(bytes(data))
    for idx, name, _, section, scl, _ in symbol_rows:
        if name not in mapping or section <= 0:
            continue
        if not (scl == CLASS_EXTERNAL or (statics and scl == CLASS_STATIC)):
            continue
        off = symptr + 18 * idx
        data[off:off + 8] = field(mapping[name].encode("latin-1"))
        if statics and scl == CLASS_STATIC:
            data[off + 16] = CLASS_EXTERNAL
        renamed += 1
        if retarget and scl == CLASS_EXTERNAL:
            retargets[idx] = nsyms + len(retargets)
            sym_type = struct.unpack_from("<H", data, off + 14)[0]
            added += field(name.encode("latin-1")) + struct.pack("<IhHBB", 0, 0, sym_type, CLASS_EXTERNAL, 0)
    if retarget_weak_defaults:
        for idx, _, _, _, scl, naux in symbol_rows:
            if scl == CLASS_WEAK_EXTERNAL and naux:
                off = symptr + 18 * (idx + 1)
                target = struct.unpack_from("<I", data, off)[0]
                if target in retargets:
                    struct.pack_into("<I", data, off, retargets[target])
    for i in range(nsec):
        off = 20 + 40 * i
        relptr = struct.unpack_from("<I", data, off + 24)[0]
        nrel = struct.unpack_from("<H", data, off + 32)[0]
        for r in range(nrel):
            roff = relptr + 10 * r
            symidx = struct.unpack_from("<I", data, roff + 4)[0]
            if symidx in retargets:
                struct.pack_into("<I", data, roff + 4, retargets[symidx])
    struct.pack_into("<I", strtab, 0, len(strtab))
    struct.pack_into("<I", data, 12, nsyms + len(retargets))
    return bytes(data[:strtab_at]) + bytes(added) + bytes(strtab), renamed


def section_symbols(data):
    """{section index: [names of class 2/3 symbols defined at offset 0]}"""
    out = {}
    for _, name, value, section, scl, _ in read_symbols(data):
        if section > 0 and scl in (CLASS_EXTERNAL, CLASS_STATIC) and value == 0 and not name.startswith((".", "$")):
            out.setdefault(section, []).append(name)
    return out


def truncate_section(data, section, size):
    """Copy of the object whose 1-based `section` keeps only its first `size` bytes (the section
    header and the section symbol's aux record both say so)."""
    data = bytearray(data)
    off = 20 + 40 * (section - 1)
    if size > struct.unpack_from("<I", data, off + 16)[0]:
        raise ValueError("cannot grow a section")
    struct.pack_into("<I", data, off + 16, size)
    symptr = struct.unpack_from("<I", data, 8)[0]
    for idx, name, value, sec, scl, naux in read_symbols(bytes(data)):
        if sec == section and scl == CLASS_STATIC and value == 0 and naux and name.startswith("."):
            struct.pack_into("<I", data, symptr + 18 * (idx + 1), size)
            break
    return bytes(data)


SCN_LNK_REMOVE = 0x00000800
SCN_LNK_INFO = 0x00000200


def remove_sections(data, keep):
    """Copy of the object in which every non-COMDAT section for which keep(name, flags, index)
    is false carries IMAGE_SCN_LNK_REMOVE, so LINK leaves its contents out of the image.

    Returns (object bytes, [names of the sections removed])."""
    data = bytearray(data)
    nsec = struct.unpack_from("<H", data, 2)[0]
    removed = []
    for idx in range(1, nsec + 1):
        off = 20 + 40 * (idx - 1)
        name = bytes(data[off:off + 8]).rstrip(b"\0").decode("latin-1")
        flags = struct.unpack_from("<I", data, off + 36)[0]
        if flags & (SCN_LNK_COMDAT | SCN_LNK_INFO | SCN_LNK_REMOVE) or keep(name, flags, idx):
            continue
        struct.pack_into("<I", data, off + 36, flags | SCN_LNK_REMOVE)
        removed.append(name)
    return bytes(data), removed


def set_section_names(data, names):
    """Copy of the object with section headers renamed per {index: name} (<= 8 chars).

    Used to move code that is not in the /ORDER file into a grouped section
    (.text$zz) that LINK sorts after every plain .text contribution."""
    data = bytearray(data)
    for idx, name in names.items():
        raw = name.encode("latin-1")
        if len(raw) > 8:
            raise ValueError("section name longer than 8 bytes")
        off = 20 + 40 * (idx - 1)
        data[off:off + 8] = raw.ljust(8, b"\0")
    return bytes(data)


def absolutise_symbols(data, mapping):
    """Return (object bytes, count) with external definitions named in mapping
    {name: va} turned into absolute symbols at va. Only definitions in
    non-COMDAT, non-code sections are changed; their storage stays in the object
    unused, and every relocation against the symbol now resolves to va."""
    nsec, symptr, nsyms = struct.unpack_from("<H", data, 2)[0], *struct.unpack_from("<II", data, 8)
    out, count = bytearray(data), 0
    for idx, name, value, section, scl, _ in read_symbols(data):
        if section <= 0 or scl != CLASS_EXTERNAL or name not in mapping:
            continue
        flags = struct.unpack_from("<I", data, 20 + 40 * (section - 1) + 36)[0]
        if flags & (SCN_CNT_CODE | SCN_LNK_COMDAT):
            continue
        struct.pack_into("<Ih", out, symptr + 18 * idx + 8, mapping[name], -1)
        count += 1
    return bytes(out), count


def retarget_relocations(data, mapping, rel32_mapping=None, sites_mapping=None):
    """Return (object bytes, count, used names) with relocations against symbol index i
    redirected to a new undefined external named mapping[i]; REL32 relocations
    use rel32_mapping[i] instead when it has one (LINK 6 computes a REL32 to an
    absolute symbol against the unrelocated site, so it needs a symbol that is
    the address minus the image base). Only names actually used are appended.

    sites_mapping {(section index, relocation offset): (dir32 name, rel32 name)} redirects single
    relocations, for a symbol whose sites disagree (it wins over the per-symbol mappings).

    One undefined external is appended per distinct new name (indices of the
    existing symbols do not change), so the new names must be defined elsewhere
    in the link, e.g. as absolute symbols. Addends stored in the section data
    are untouched: the linker adds them to the new symbol's value."""
    rel32_mapping = rel32_mapping or {}
    sites_mapping = sites_mapping or {}
    if not mapping and not rel32_mapping and not sites_mapping:
        return bytes(data), 0, set()
    data = bytearray(data)
    nsec = struct.unpack_from("<H", data, 2)[0]
    symptr, nsyms = struct.unpack_from("<II", data, 8)
    strtab_at = symptr + nsyms * 18
    sites = []   # (offset of the symbol field, new name)
    for i in range(nsec):
        off = 20 + 40 * i
        relptr = struct.unpack_from("<I", data, off + 24)[0]
        nrel = struct.unpack_from("<H", data, off + 32)[0]
        first = 0
        if struct.unpack_from("<I", data, off + 36)[0] & SCN_LNK_NRELOC_OVFL:
            nrel, first = struct.unpack_from("<I", data, relptr)[0], 1   # first record holds the real count
        for r in range(first, nrel):
            roff = relptr + 10 * r
            symidx, kind = struct.unpack_from("<IH", data, roff + 4)
            new = (rel32_mapping.get(symidx) if kind == REL_REL32 else None) or mapping.get(symidx)
            if (i + 1, struct.unpack_from("<I", data, roff)[0]) in sites_mapping:
                pair = sites_mapping[(i + 1, struct.unpack_from("<I", data, roff)[0])]
                new = pair[1] if kind == REL_REL32 else pair[0]
            if new:
                sites.append((roff + 4, new))
    used = {name for _, name in sites}
    strtab = bytearray(data[strtab_at:])
    added, new_index = bytearray(), {}
    for name in sorted(used):
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            field = raw.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strtab))
            strtab.extend(raw + b"\0")
        new_index[name] = nsyms + len(new_index)
        added += field + struct.pack("<IhHBB", 0, 0, 0, CLASS_EXTERNAL, 0)
    for at, name in sites:
        struct.pack_into("<I", data, at, new_index[name])
    struct.pack_into("<I", strtab, 0, len(strtab))
    struct.pack_into("<I", data, 12, nsyms + len(new_index))
    return bytes(data[:strtab_at]) + bytes(added) + bytes(strtab), len(sites), used
