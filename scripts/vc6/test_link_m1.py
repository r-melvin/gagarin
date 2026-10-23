#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic objects; the LINK probe runs only where the toolchain is installed.
"""link_m1: library order, and (with Wine + toolchain) the LINK 6 behaviour the M1 layout relies on."""

import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

import coffgen
import link_diag
import link_m1
import mapcheck
import stubgen


class LibraryOrderTests(unittest.TestCase):
    def test_thunk_block_libraries_bracket_the_crt(self):
        libs = link_m1.library_order("bink.lib")
        self.assertLess(libs.index("WSOCK32.LIB"), libs.index("LIBCMT.LIB"))
        self.assertLess(libs.index("IMM32.LIB"), libs.index("LIBCMT.LIB"))
        self.assertLess(libs.index("COMSUPP.LIB"), libs.index("KERNEL32.LIB"))
        self.assertEqual(libs[-1], "bink.lib")
        self.assertEqual(len(libs), len(set(libs)))
        self.assertEqual(set(link_m1.IMPORT_LIBS) - set(libs), set())


def toolchain_ready():
    vc6, _ = link_diag.toolenv()
    return shutil.which("wine") and (vc6 / "VC98/Bin/LINK.EXE").is_file()


@unittest.skipUnless(toolchain_ready(), "Wine or the VC6 toolchain is not installed")
class LinkProbeTests(unittest.TestCase):
    """/ORDER spelling, per-COMDAT alignment, weak aliases and /OPT:REF,NOICF with
    the anchor table: the four LINK 6 behaviours stubgen depends on."""

    def test_order_alignment_alias_and_anchor(self):
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["_entry"], 3, 16)
        w.add_code_comdat(["?stub_b@@YAXXZ"], 5, 1)
        w.add_code_comdat(["@fast@8"], 4, 4)
        w.add_code_comdat(["_c_name"], 16, 16)          # same size and bytes as below: NOICF keeps both
        w.add_code_comdat(["_c_twin"], 16, 16)
        w.add_code_comdat(["_dropped"], 16, 16)          # neither ordered nor referenced: /OPT:REF drops it
        w.add_alias("?alias@@YAXXZ", "_c_name")
        order = ["_entry", "?stub_b@@YAXXZ", "@fast@8", "_c_twin", "_c_name"]
        w.set_anchor(order + ["?alias@@YAXXZ"])
        vc6, env = link_diag.toolenv()
        with tempfile.TemporaryDirectory(dir=os.environ.get("GAG_SCRATCH")) as tmp:
            root = Path(tmp)
            (root / "s.obj").write_bytes(w.build())
            (root / "order.txt").write_text("\n".join(stubgen.order_name(n) for n in order) + "\n")
            wp = link_diag.wine_path
            subprocess.run(["wine", str(vc6 / "VC98/Bin/LINK.EXE"), "/NOLOGO", "/NODEFAULTLIB", "/ENTRY:entry",
                            "/SUBSYSTEM:CONSOLE", "/OPT:REF", "/OPT:NOICF", "/ORDER:@" + wp(root / "order.txt"),
                            "/MAP:" + wp(root / "t.map"), "/OUT:" + wp(root / "t.exe"), wp(root / "s.obj")],
                           env=env, check=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            publics, _ = mapcheck.parse_map((root / "t.map").read_text(encoding="latin-1"))
        self.assertEqual(publics["_entry"], 0x401000)
        self.assertEqual(publics["?stub_b@@YAXXZ"], 0x401003)   # align 1: right after a 3-byte COMDAT
        self.assertEqual(publics["@fast@8"], 0x401008)          # align 4
        self.assertEqual(publics["_c_twin"], 0x401010)          # ordered before _c_name
        self.assertEqual(publics["_c_name"], 0x401020)          # not folded into its twin
        self.assertEqual(publics["?alias@@YAXXZ"], 0x401020)    # weak alias resolves to its target
        self.assertNotIn("_dropped", publics)


if __name__ == "__main__":
    unittest.main()
