# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Tests for init_interleave.py (text step, row/binding renumbering; no compiler, no retail binary)."""

import json
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import init_interleave as I  # noqa: E402

DEST = """// header
#include <stddef.h>
#include "x.h"

// GLOBAL: GAMEMD 0x7E51A0
extern const double DAT_007E51A0;

// SYNTHETIC: GAMEMD 0x48BCA0
// GLOBAL: GAMEMD 0x89E908
double DAT_0089E908 = DAT_0089E8B8 / DAT_007E51A0;

// SYNTHETIC: GAMEMD 0x48BE40
// GLOBAL: GAMEMD 0x89E8F8
MathTblCoord DAT_0089E8F8;

// FUNCTION: GAMEMD 0x48BE60
int Foo() { return 1; }

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E51A0
extern const double DAT_007E51A0 = 60.0;
// END defined globals
"""

FRAG = """// SPDX
// Provenance: x
// text
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E51A0
const double DAT_007E51A0 = 60.0;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x48BC70
// GLOBAL: GAMEMD 0x89E8B8
double DAT_0089E8B8 = FUN_004CAC40(DAT_007E1708);
// SYNTHETIC: GAMEMD 0x48BCE0
// GLOBAL: GAMEMD 0x89E8E8
double DAT_0089E8E8 = DAT_0089E8B8 * 45.0;
// SYNTHETIC: GAMEMD 0x48BE20
// GLOBAL: GAMEMD 0x89E8D0
HeaderCoordInit DAT_0089E8D0(0, 0, 0);
"""


class TextStep(unittest.TestCase):
    def test_parse(self):
        f = I.parse_fragment(FRAG)
        self.assertEqual([a for a, _ in f["chunks"]], [0x48BC70, 0x48BCE0, 0x48BE20])
        self.assertEqual(len(f["includes"]), 2)
        self.assertTrue(any("DAT_007E1708" in l for l in f["prelude"]))

    def test_interleave_in_address_order(self):
        out, rep = I.merge_into(DEST, FRAG)
        addrs = [I.anchor(l) for l in out.split("\n") if I.anchor(l) is not None]
        self.assertEqual(addrs, sorted(addrs))
        self.assertEqual(rep["chunks"], 3)
        # the constant the destination already defines is not repeated, the new one is kept
        self.assertEqual(out.count("DAT_007E51A0 = 60.0"), 1)
        self.assertIn("const double DAT_007E1708 = 2.0;", out)
        # includes join the top include block
        lines = out.split("\n")
        self.assertLess(lines.index("#include <math.h>"), lines.index(""))

    def test_hoisted_prelude_precedes_first_chunk(self):
        out, _ = I.merge_into(DEST, FRAG)
        self.assertLess(out.index("const double DAT_007E1708"), out.index("SYNTHETIC: GAMEMD 0x48BC70"))

    def test_declaration_only_does_not_drop_the_definition(self):
        dest = DEST.replace("extern const double DAT_007E51A0;",
                            "extern const double DAT_007E51A0;\nextern const double DAT_007E1708;")
        out, rep = I.merge_into(dest, FRAG)
        self.assertIn("const double DAT_007E1708 = 2.0;", out)
        self.assertNotIn(["DAT_007E1708"], rep["dropped"])

    def test_retype_extern_and_placeholder_definition(self):
        dest = DEST.replace("extern const double DAT_007E51A0;",
                            "extern const double DAT_007E51A0;\nextern int DAT_0089E8D0;")
        out, rep = I.merge_into(dest, FRAG)
        self.assertIn(("DAT_0089E8D0", "int"), rep["retyped"])
        self.assertIn("extern HeaderCoordInit DAT_0089E8D0;", out)


class Renumber(unittest.TestCase):
    def test_pair_by_order(self):
        rows = [(0x20, "_$E5"), (0x10, "_$E2")]
        syms = [(9, 0, "_$E8"), (3, 0, "_$E5")]
        self.assertEqual(I.pair_by_order(rows, syms), {0x10: "_$E5", 0x20: "_$E8"})
        with self.assertRaises(ValueError):
            I.pair_by_order(rows, syms[:1])

    def test_renumber_rows_text_keeps_format(self):
        t = '[\n {\n  "addr": "0x10",\n  "sym": "_$E2",\n  "len": "0x4"\n },\n {\n  "addr": "0x20",\n  "sym": "_$E5"\n }\n]'
        out, ch = I.renumber_rows_text(t, {"0x10": "_$E5", "0x20": "_$E8"})
        self.assertEqual(ch, [("0x10", "_$E2", "_$E5"), ("0x20", "_$E5", "_$E8")])
        self.assertEqual(json.loads(out)[1]["sym"], "_$E8")

    def test_retarget(self):
        t = '{"tu": "a.cpp"}\n{"tu": "a.cpp"}\n{"tu": "b.cpp"}'
        out, n = I.retarget_text(t, ["a.cpp"], "d.cpp")
        self.assertEqual(n, 2)
        self.assertEqual(out.count('"d.cpp"'), 2)

    def test_binding_rekeys_in_place(self):
        t = json.dumps({"a::k": "1", "src::_DAT_1": "0x1", "d::_$E2": "0x10", "d::_$E5": "0x20", "z::k": "9"})
        out, moved = I.rekey_bindings_text(t, ["src"], "d")
        self.assertEqual(moved, [{"old": "src::_DAT_1", "new": "d::_DAT_1", "addr": "0x1"}])
        self.assertEqual(list(json.loads(out)), ["a::k", "d::_DAT_1", "d::_$E2", "d::_$E5", "z::k"])
        # initialiser keys follow the renumbered rows by address, without colliding mid-way
        rk = I.initialiser_rekeys(json.loads(out), "d", {"0x10": "_$E5", "0x20": "_$E8"})
        out2 = I.apply_rekeys_text(out, rk)
        d = json.loads(out2)
        self.assertEqual((d["d::_$E5"], d["d::_$E8"]), ("0x10", "0x20"))
        self.assertNotIn("d::_$E2", d)

    def test_collision_is_an_error(self):
        t = json.dumps({"d::k": "1", "s::k": "2"})
        with self.assertRaises(SystemExit):
            I.rekey_bindings_text(t, ["s"], "d")[0]
            I.apply_rekeys_text(t, [{"old": "s::k", "new": "d::k", "addr": "2"}])

    def test_rank_remap(self):
        old = [(1, 0, "_$S3"), (1, 4, "_$S6")]
        new = [(1, 0, "_$S9"), (1, 4, "_$S12")]
        self.assertEqual(I.rank_remap(["_$S3", "_$S6"], old, new), {"_$S3": "_$S9", "_$S6": "_$S12"})
        with self.assertRaises(ValueError):
            I.rank_remap(["_$S3", "_$S6"], old, new[:1])
        # a fragment that adds file-scoped data: the destination's symbols keep their rank from the end
        grown = [(1, 0, "_$S2"), (1, 4, "_$S4"), (1, 8, "_$S9"), (2, 0, "_$S12")]
        self.assertEqual(I.rank_remap(["_$S3", "_$S6"], old, grown), {"_$S3": "_$S9", "_$S6": "_$S12"})

    def test_digest_multiset_ignores_statics(self):
        d = I.digest_multiset([{"name": "_$E2", "digest": "a"}, {"name": "_$S3", "digest": "b"}])
        self.assertEqual(dict(d), {"a": 1})


if __name__ == "__main__":
    unittest.main()
