#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the pinned PE ($GAMEMD_BINARY) at build time only, embeds nothing.
"""Retail addresses of the compiled RTTI symbols (milestone M3).

With /GR every polymorphic class carries MSVC RTTI. The compiler names each piece:

    ??_R0?AVX@@@8           type descriptor
    ??_R1<pmd,attrs>X@@8    base class descriptor (one per base subobject: A@ ?0 A@ A@ = mdisp 0, pdisp -1, vdisp 0, attrs 0)
    ??_R2X@@8               base class array
    ??_R3X@@8               class hierarchy descriptor
    ??_R4X@@6B@             complete object locator (6BY@@@ for the vtable of the subobject Y)

None of those has a symbol binding, but retail's copies are a linked graph that the class sweep
(scripts/data/rtti_classes.json: type descriptor, locators, hierarchy descriptors) anchors: this
module walks it in the pinned image and names every piece the way the compiler would. A locator
is named after its vtable (??_R4<suffix> goes with ??_7<suffix>), so it is found through the slot
before that vtable. Addresses are only the lookup; datasource.py still adopts a piece only when its
bytes and relocation targets equal retail's.
"""

import struct

PREFIXES = ("??_R0", "??_R1", "??_R2", "??_R3", "??_R4")


def encode_number(n):
    """MSVC name mangling of an integer: 0 -> A@, 1..10 -> 0..9, larger -> hex nibbles A..P then @, negative -> ?"""
    if n < 0:
        return "?" + encode_number(-n)
    if n == 0:
        return "A@"
    if n <= 10:
        return str(n - 1)
    digits = ""
    while n:
        digits = chr(ord("A") + (n & 15)) + digits
        n >>= 4
    return digits + "@"


def signed(v):
    return v - (1 << 32) if v & 0x80000000 else v


def core(mangled):
    """'.?AVX@@' -> 'X@@' (the class part both the type descriptor and the other pieces are named by)."""
    return mangled[4:]


def type_descriptor_name(mangled):
    return "??_R0" + mangled[1:] + "@8"


class RttiNames:
    """{compiled symbol name: retail VA} for the RTTI of the classes in rtti_classes.json.

    Names that two different retail pieces would claim are dropped and listed in `ambiguous`.
    `vtables` maps a ??_7 name to its retail address (symbol bindings); with it a ??_R4 name is
    resolved through the locator slot before that vtable, whatever the vtable's qualifier. bare: mangled names
    of classes that have a type descriptor and no locator."""

    def __init__(self, retail, classes, vtables=None, bare=()):
        self.retail = retail
        self.vtables = vtables if vtables is not None else {}
        self.names = {}
        self.ambiguous = set()
        self.locators = set()
        for mangled, info in classes.items():
            self._class(mangled, info)
        for mangled in bare:   # type descriptors no locator points to: found by their (unique) name string
            found = retail.search(mangled.encode() + b"\0")
            if len(found) == 1 and found[0] % 4 == 0:
                self._add(type_descriptor_name(mangled), found[0] - 8)

    def _dword(self, va):
        return struct.unpack("<I", self.retail.fill(va, 4))[0]

    def _string(self, va):
        out = b""
        while len(out) < 512:
            ch = self.retail.fill(va + len(out), 1)
            if ch in (b"", b"\0"):
                break
            out += ch
        return out.decode("latin-1")

    def _add(self, name, va):
        if name in self.ambiguous:
            return
        if self.names.get(name, va) != va:
            del self.names[name]
            self.ambiguous.add(name)
            return
        self.names[name] = va

    def _class(self, mangled, info):
        c = core(mangled)
        self._add(type_descriptor_name(mangled), int(info["type_descriptor_va"], 16))
        for loc in info["locators"]:
            col = int(loc["locator_va"], 16)
            self.locators.add(col)
            if loc["cd_offset"] == 0 and loc["base_offset"] == 0:
                self._add("??_R4" + c + "6B@", col)
            chd = int(loc["class_hierarchy_va"], 16)
            self._add("??_R3" + c + "8", chd)
            count, bca = struct.unpack("<II", self.retail.fill(chd + 8, 8))
            if not 0 < count < 256:
                continue
            self._add("??_R2" + c + "8", bca)
            for k in range(count):
                bcd = self._dword(bca + 4 * k)
                td, _, mdisp, pdisp, vdisp, attrs = struct.unpack("<IIIIII", self.retail.fill(bcd, 24))
                name = self._string(td + 8)
                if not name.startswith(".?A"):
                    continue
                self._add("??_R1" + "".join(encode_number(signed(v)) for v in (mdisp, pdisp, vdisp, attrs))
                          + core(name) + "8", bcd)

    def address(self, name):
        """Retail VA of an RTTI symbol, or None."""
        if not name.startswith(PREFIXES):
            return None
        if name.startswith("??_R4"):
            vt = self.vtables.get("??_7" + name[5:])
            if vt is not None:
                col = self._dword(vt - 4)
                return col if col in self.locators else None
        return self.names.get(name)

    def __contains__(self, name):
        return self.address(name) is not None

    def __getitem__(self, name):
        va = self.address(name)
        if va is None:
            raise KeyError(name)
        return va
