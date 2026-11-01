#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; synthetic ledger rows and notes only.
"""Tests for regmine: python3 -m unittest test_regmine"""
import os
import re
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import regmine as R  # noqa: E402


def row(addr, raw, variant, delta=None, status="recorded"):
    return dict(addr=addr, raw=raw, variant=variant, delta=delta, status=status, date="2026-11-01")


class Classify(unittest.TestCase):
    def test_edit_classes(self):
        self.assertIn("operand-order", R.classify("commuted the add operands", R.EDIT_RX))
        self.assertIn("statement-order", R.classify("swap the two stores", R.EDIT_RX))
        self.assertIn("named-temporary", R.classify("cache it in a local temp", R.EDIT_RX))
        self.assertEqual(R.classify("zzz", R.EDIT_RX), ["unclassified"])

    def test_pattern_classes(self):
        self.assertIn("operand-swap", R.classify("add eax,ecx vs add ecx,eax", R.PATTERN_RX))
        self.assertIn("imm-vs-reg", R.classify("test al,0xff vs test al,al", R.PATTERN_RX))
        self.assertIn("scheduling", R.classify("multiset identical, scheduling only", R.PATTERN_RX))
        self.assertIn("register-allocation", R.classify("ecx vs eax in memmove arg", R.PATTERN_RX))
        self.assertIn("stack-frame", R.classify("frame 0x5c vs 0x4c", R.PATTERN_RX))

    def test_outcome(self):
        self.assertEqual(R.outcome(90, 100), "fixed")
        self.assertEqual(R.outcome(90, 92), "improved")
        self.assertEqual(R.outcome(90, 90.0), "no-change")
        self.assertEqual(R.outcome(90, 80), "regressed")
        self.assertEqual(R.outcome(None, 80), "unknown")


class Mining(unittest.TestCase):
    def test_ledger_pairs_use_previous_delta_and_current_edit(self):
        rows = [row("0x401000", 90.0, "baseline", "add eax,ecx vs add ecx,eax"),
                row("0x401000", 100.0, "commute the add operands"),
                row("0x402000", 50.0, "base"), row("0x402000", 49.0, "swap statements", "scheduling")]
        obs = R.ledger_pairs(rows)
        self.assertEqual(len(obs), 2)
        a = obs[0]
        self.assertEqual((a["outcome"], a["edit"], a["pattern"]), ("fixed", ["operand-order"], ["operand-swap"]))
        self.assertEqual(obs[1]["outcome"], "regressed")

    def test_imported_and_deferred_rows_are_not_pairs(self):
        rows = [row("0x401000", 90.0, "a", status="imported, unverified"), row("0x401000", 91.0, "b"),
                row("0x401000", None, "deferred", status="deferred")]
        self.assertEqual(R.ledger_pairs(rows), [])

    def test_readme_pairs(self):
        text = ("# p\n\n## Change\nDynamicVectorClass::AddItem takes the temp form: int cap = Capacity;\n\n"
                "## Held\n- 0x466380 BulletClass::BulletClass: 49.3 -> 54.8 (multiset identical, scheduling)\n"
                "- 0x556A20 LineTrail: matched 100 -> partial 92.7 (multiset identical)\n- no address 1 -> 2\n")
        obs = R.readme_pairs(text, "addgrow")
        self.assertEqual(len(obs), 1)             # the matched-100 demotion is not an edit effect
        self.assertEqual(R.readme_pairs("0x738890 to 98.2 (x)", "p"), [])
        self.assertEqual(obs[0]["addr"], "0x466380")
        self.assertEqual(obs[0]["outcome"], "improved")
        self.assertIn("named-temporary", obs[0]["edit"])
        self.assertEqual(obs[0]["source"], "packet:addgrow")


class Output(unittest.TestCase):
    def test_rulebook_counts_and_scrubbing(self):
        rows = [row("0x401000", 90.0, "baseline", "add eax,ecx vs add ecx,eax"),
                row("0x401000", 100.0, "commute the add operands see ../x/notes.md and /home/u/secret.txt"),
                row("0x403000", 80.0, "baseline", "add eax,ecx vs add ecx,eax"),
                row("0x403000", 80.0, "commute operands")]
        obs = R.mine(rows, [])
        md = R.rulebook(obs, [re.compile("secret", re.I)])
        self.assertIn("| operand-swap | operand-order | 2 | 1 | 0 | 1 | 0 |", md)
        self.assertNotIn("/home/", md)
        self.assertNotIn("notes.md", md)
        self.assertIn("## Top entries", md)

    def test_forbidden_line_is_redacted(self):
        self.assertEqual(R.scrub("mentions Zork here", [re.compile("zork", re.I)]), "[redacted]")

    def test_main_writes_rulebook(self):
        with tempfile.TemporaryDirectory() as d:
            led = Path(d) / "a.jsonl"
            import json
            led.write_text("\n".join(json.dumps(r) for r in [row("0x401000", 90.0, "a", "scheduling"),
                                                             row("0x401000", 91.0, "swap statements")]) + "\n")
            out = Path(d) / "sub" / "r.md"
            rc = R.main(["--ledger", str(led), "--ready-glob", str(Path(d) / "none" / "*"), "--out", str(out)])
            self.assertEqual(rc, 0)
            self.assertIn("statement-order", out.read_text())


if __name__ == "__main__":
    unittest.main()
