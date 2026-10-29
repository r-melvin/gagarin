#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling (measurement only).
"""Run the M3 hybrid link with datasource.candidates patched to report EVERY bad relocation of a rejected
definition (field "slots": [[offset, target, why, known, wanted]]), not only the first. Output goes to --out
(under build-vc6/); the image it links is the ordinary M3 image.

Usage: GAMEMD_BINARY=... data_census_link.py --objdir build-vc6/gate --out build-vc6/census-link
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import datasource  # noqa: E402

src = Path(datasource.__file__).read_text()
a = '''                if known is None:
                    bad = f"relocation target {tname} has no known address"
                    break
                if (known + addend) & 0xFFFFFFFF != got:
                    bad = f"relocation target {tname} is at 0x{known:X}, retail's field says 0x{(got - addend) & 0xFFFFFFFF:X}"
                    break
'''
b = '''                if known is None:
                    slot_bad.append([lo, tname, "unknown", None, (got - addend) & 0xFFFFFFFF])
                    bad = bad or f"relocation target {tname} has no known address"
                    continue
                if (known + addend) & 0xFFFFFFFF != got:
                    slot_bad.append([lo, tname, "moved", known, (got - addend) & 0xFFFFFFFF])
                    bad = bad or f"relocation target {tname} is at 0x{known:X}, retail's field says 0x{(got - addend) & 0xFFFFFFFF:X}"
                    continue
'''
assert src.count(a) == 1
src = src.replace(a, b)
a2 = "            relocs, bad = [], None\n"
assert src.count(a2) == 1
src = src.replace(a2, "            relocs, bad, slot_bad = [], None, []\n")
a3 = '''            if bad:
                reject(name, kind, sec["name"], bad, size, va)
                continue
            if ours != want:'''
b3 = '''            if bad:
                reject(name, kind, sec["name"], bad, size, va)
                rejected[-1]["slots"] = slot_bad
                continue
            if ours != want:'''
assert src.count(a3) == 1
src = src.replace(a3, b3)
a4 = '''            if not vas:
                reject(name, kind, sec["name"], "no retail address", size)
                continue
'''
b4 = '''            if not vas:
                reject(name, kind, sec["name"], "no retail address", size)
                if kind == "vtable":
                    rejected[-1]["slotinfo"] = [[off - start, names[symidx][0], resolver.address(names[symidx][0])]
                                                for off, symidx, rtype in section_relocs(final, secno) if start <= off < end]
                continue
'''
assert src.count(a4) == 1
src = src.replace(a4, b4)
exec(compile(src, "datasource_patched", "exec"), datasource.__dict__)

import link_m1  # noqa: E402

if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--objdir", type=Path, required=True)
    ap.add_argument("--out", type=Path, required=True)
    args = ap.parse_args()
    s = link_m1.run(args.objdir.resolve(), args.out.resolve(), hybrid=True, source_data=True, search=("string", "float"))
    print("exit", s["link_exit_code"], s["rounds"])
