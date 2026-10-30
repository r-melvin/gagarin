#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic objects; no retail bytes.
"""tpl_audit: instance names, link-order winners, divergent COMDATs and the multi-address ??_G list."""

import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "vc6"))
import coffgen  # noqa: E402
import tpl_audit  # noqa: E402

SYM = "?SetCapacity@?$DynamicVectorClass@H@@UAE_NHPAX@Z"
GSYM = "??_G?$VectorClass@PAVObjectClass@@@@UAEPAXI@Z"


class InstanceTests(unittest.TestCase):
    def test_instance_of(self):
        self.assertEqual(tpl_audit.instance_of(SYM), "DynamicVectorClass<int>")
        self.assertEqual(tpl_audit.instance_of(GSYM), "VectorClass<ObjectClass*>")
        self.assertEqual(tpl_audit.instance_of("??_7?$VectorClass@H@@6B@"), "VectorClass<int>")
        self.assertIsNone(tpl_audit.instance_of("?f@@YAXXZ"))
        self.assertEqual(tpl_audit.instance_of("??_R0?AV?$VectorClass@PAVSpotLightClass@@@@@8"), "VectorClass<SpotLightClass*>")
        self.assertEqual(tpl_audit.instance_of("??_R3?$DynamicVectorClass@PAVPlanningNodeClass@@@@8"), "DynamicVectorClass<PlanningNodeClass*>")
        self.assertEqual(tpl_audit.instance_of("??_R4?$VectorClass@PAVBuildingClass@@@@6B@"), "VectorClass<BuildingClass*>")

    def test_multi_address_is_template_gdtor_only(self):
        manifest = [{"sym": GSYM, "addr": "0x40CF30"}, {"sym": GSYM, "addr": "0x488030"},
                    {"sym": SYM, "addr": "0x401000"}, {"sym": SYM, "addr": "0x401100"},
                    {"sym": "??_GFoo@@UAEPAXI@Z", "addr": "0x1"}, {"sym": "??_GFoo@@UAEPAXI@Z", "addr": "0x2"}]
        self.assertEqual(tpl_audit.multi_address(manifest), {GSYM: [0x40CF30, 0x488030]})


class AuditTests(unittest.TestCase):
    def test_winner_is_first_in_link_order_and_divergence_is_flagged(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            for name, fill in (("early.obj", 0xAA), ("late.obj", 0xBB)):
                w = coffgen.ObjectWriter()
                w.add_code_comdat([SYM], 0x10, fill=fill)
                (root / name).write_bytes(w.build())
            # index order is late, early; the manifest claims a lower address for early.cpp
            (root / "objects.json").write_text(json.dumps({"objects": [
                {"object": "late.obj", "source": "late.cpp"}, {"object": "early.obj", "source": "early.cpp"}]}))
            manifest = [{"tu": "early.cpp", "addr": "0x401000", "sym": SYM, "len": "0x10", "status": "matched"},
                        {"tu": "late.cpp", "addr": "0x402000", "sym": "?x@@YAXXZ", "len": "0x10", "status": "matched"}]
            rows = tpl_audit.audit(root, manifest, None)
            self.assertEqual(len(rows), 1)
            self.assertEqual(rows[0]["winner"], "early.obj")
            self.assertEqual([d["object"] for d in rows[0]["definers"]], ["early.obj", "late.obj"])
            self.assertTrue(rows[0]["divergent"])
            self.assertEqual(rows[0]["instance"], "DynamicVectorClass<int>")


if __name__ == "__main__":
    unittest.main()
