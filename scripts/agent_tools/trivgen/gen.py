#!/usr/bin/env python3
# Provenance: original. Bin building and file text for trivgen.
"""A Bin is one generated translation unit (.h + .cpp pair).  Functions are added
in address order; a function whose declarations conflict with what the bin
already holds is refused (the caller then tries the next bin of the same TU)."""
import os
import re
from dataclasses import dataclass, field

import data
import emit
from emit import Field, Glob, View, hx
from lift import Unsupported

PROVENANCE = "// Provenance: own-binary-via-Ghidra"


def merge_view(dst, src):
    for off, f in src.fields.items():
        g = dst.fields.get(off)
        if g is None:
            dst.fields[off] = Field(f.off, f.size, f.kind, f.ptr, f.sg, f.uns)
        else:
            if g.size != f.size or g.kind != f.kind or (g.kind == "ptr" and g.ptr != f.ptr):
                raise Unsupported("bin-field-conflict")
            if f.sg == "s":
                g.sg = "s"
            g.uns = g.uns or f.uns
    for a, d in src.methods.items():
        dst.methods.setdefault(a, d)
    for s, d in src.vslots.items():
        dst.vslots.setdefault(s, d)
    if src.global_obj is not None:
        dst.global_obj = src.global_obj


def overlaps(view):
    end = 4 if view.vslots else 0
    for off in sorted(view.fields):
        f = view.fields[off]
        if off < end:
            return True
        end = off + f.size
    return False


@dataclass
class Bin:
    name: str                      # file stem
    module: str                    # directory under match/
    items: list = field(default_factory=list)        # Out, in address order
    views: dict = field(default_factory=dict)
    globals: dict = field(default_factory=dict)
    protos: dict = field(default_factory=dict)
    includes: set = field(default_factory=set)

    def can_add(self, out):
        """Raise Unsupported if `out` conflicts with the bin."""
        for name, v in out.views.items():
            cur = self.views.get(name)
            if cur is not None:
                probe = View(name)
                merge_view(probe, cur)
                merge_view(probe, v)
                if overlaps(probe):
                    raise Unsupported("bin-field-overlap")
            elif overlaps(v):
                raise Unsupported("field-overlap")
        for a, g in out.globals.items():
            cur = self.globals.get(a)
            if cur is not None and (cur.ctype != g.ctype or cur.array != g.array):
                raise Unsupported("bin-global-conflict")
        for a, pr in out.protos.items():
            cur = self.protos.get(a)
            if cur is not None and cur[0] != pr[0]:
                raise Unsupported("bin-proto-conflict")

    def add(self, out):
        self.can_add(out)
        for name, v in out.views.items():
            merge_view(self.views.setdefault(name, View(name)), v)
        for a, g in out.globals.items():
            self.globals.setdefault(a, g)
        for a, p in out.protos.items():
            self.protos.setdefault(a, p)
        if out.canon:
            self.includes.add(out.canon["header"])
        self.items.append(out)

    # -------------------------------------------------------------- text
    def guard(self):
        return "GG_MATCH_" + self.module.upper().replace("/", "_") + "_" + self.name.upper() + "_H"

    def header_text(self, describe):
        L = [
            "// SPDX-License-Identifier: GPL-3.0-or-later",
            PROVENANCE,
            "//   Each entry point disassembled individually from the user's retail",
            "//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder",
            "//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.",
            f"#ifndef {self.guard()}",
            f"#define {self.guard()}",
            "",
            "#include <stddef.h>",
            '#include "../_rt/gg_static_assert.h"',
        ]
        for inc in sorted(self.includes):
            rel = os.path.relpath(inc, str(data.WT / "match" / self.module))
            L.append(f'#include "{rel}"')
        L.append("")
        names = sorted(self.views)
        for n in names:
            L.append(f"struct {n};")
        if names:
            L.append("")
        for a in sorted(self.globals):
            g = self.globals[a]
            L.append(f"// GLOBAL: GAMEMD 0x{a:X}")
            if g.array:
                L.append(f"extern char DAT_{hx(a)}[];")
            else:
                L.append(f"extern {'const ' if g.const else ''}{g.ctype} DAT_{hx(a)};")
        if self.globals:
            L.append("")
        for T, pr in sorted(self.protos.items()):
            key, decl, addr = pr[0], pr[1], pr[2]
            if addr is None:
                L.append(f"// {pr[3]}")
            else:
                L.append(f"// FUNCTION: GAMEMD 0x{T:X} (declaration)")
            L.append(decl)
        if self.protos:
            L.append("")
        # views ordered by first use
        owner_order = {}
        for o in self.items:
            owner_order.setdefault(o.member_of, o)
        for n in names:
            L += self.view_text(self.views[n])
        L.append("")
        for o in self.items:
            if o.decl:
                L.append(f"// FUNCTION: GAMEMD 0x{o.spec.addr:X}")
                L.append(o.decl)
        L += ["", f"#endif  // {self.guard()}", ""]
        return "\n".join(L)

    def view_text(self, v):
        packed = any(off % (f.size if f.size in (1, 2, 4, 8) else 4) for off, f in v.fields.items()
                     if f.kind != "fp" or True)
        L = (["#pragma pack(push, 1)"] if packed else []) + [f"struct {v.name}", "{"]
        pos = 0
        asserts = []
        if v.vslots:
            for sl in range(max(v.vslots) + 1):
                L.append(v.vslots.get(sl, f"    virtual void vf_{sl}();"))
            pos = 4
        v1 = "unsigned char"
        for off in sorted(v.fields):
            f = v.fields[off]
            if off > pos:
                L.append(f"    char unknown_{pos:02X}[0x{off - pos:X}];")
            ct = f.ctype(self.v1_for(v, off))
            L.append(f"    {ct} unknown_{off:02X};   // +0x{off:04X}")
            asserts.append(f"GG_STATIC_ASSERT(offsetof({v.name}, unknown_{off:02X}) == 0x{off:X});")
            pos = off + f.size
        for a, d in sorted(v.methods.items()):
            L.append(f"    // FUNCTION: GAMEMD 0x{a:X}")
            L.append(f"    {d}" if isinstance(d, str) else f"    {d[0]}")
        L.append("};")
        if packed:
            L.append("#pragma pack(pop)")
        L += asserts
        L.append("")
        return L

    def v1_for(self, v, off):
        for o in self.items:
            if v.name in o.views:
                return o.var.get("v1", "unsigned char")
        return "unsigned char"

    def cpp_text(self, describe):
        L = [
            "// SPDX-License-Identifier: GPL-3.0-or-later",
            PROVENANCE,
            "//   Bytes matched against retail gamemd.exe v1.001 at each address below.",
            "//",
            "//   Ordered ascending by retail address.",
            "",
            f'#include "{self.name}.h"',
            "",
        ]
        for o in sorted(self.items, key=lambda x: x.spec.addr):
            L.append(f"// FUNCTION: GAMEMD 0x{o.spec.addr:X}")
            if o.pattern:
                L.append(f"// {o.pattern}")
            L.append(o.body)
        return "\n".join(L)

    def line_map(self, text):
        """function addr -> (first line, last line) in the cpp text."""
        out = {}
        for i, line in enumerate(text.split("\n"), 1):
            m = re.match(r"^// FUNCTION: GAMEMD 0x([0-9A-F]+)$", line)
            if m:
                out.setdefault(int(m.group(1), 16), [i, i])
        order = sorted(out.items(), key=lambda kv: kv[1][0])
        total = len(text.split("\n"))
        for k, (a, rng) in enumerate(order):
            rng[1] = (order[k + 1][1][0] - 1) if k + 1 < len(order) else total
        return {a: tuple(r) for a, r in out.items()}
