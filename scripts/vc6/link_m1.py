#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Address-faithful partial link (milestone M1), diagnostic only.

Links every project object, the M1 stubs (stubgen.py: 0xCC code COMDATs and
zero-filled data, no retail bytes), the toolchain LIBCMT/COMSUPP/LIBCPMT and
import libraries and a binkw32.lib written by implib.py, with an /ORDER file
that lays out the engine .text in retail order. No /FORCE: the link must
resolve every external. Then mapcheck.py compares each matched function's
linked address and size with the manifest.

The image is a layout probe. It does not run (stubs are int3) and it is never
evidence of identity with the retail executable.

Usage:
  scripts/vc6/build_project.py --out OBJDIR
  scripts/vc6/link_m1.py --objdir OBJDIR [--out DIR]
"""

import argparse
import json
from pathlib import Path
import subprocess
import sys

import implib
import link_diag
import mapcheck
import pindata
import stubgen
import taillink

ROOT = Path(__file__).resolve().parents[2]
TOOL_LIBS = link_diag.TOOL_LIBS + ["OLDNAMES.LIB", "UUID.LIB"]
IMPORT_LIBS = link_diag.IMPORT_LIBS
# Library order on the command line. Retail has two import-thunk blocks:
# WSOCK32, DDRAW, DSOUND, VERSION, IMM32 thunks before LIBCMT (0x7C8962) and
# KERNEL32, OLEAUT32 thunks after COMSUPP (0x7DCE62) (inventory section 1), so
# those import libraries are listed around the CRT in that order. Hypothesis
# under test; mapcheck reports where the CRT lands.
EARLY_IMPORT_LIBS = ["WSOCK32.LIB", "DDRAW.LIB", "DSOUND.LIB", "VERSION.LIB", "IMM32.LIB"]
LATE_IMPORT_LIBS = ["KERNEL32.LIB", "OLEAUT32.LIB"]


def library_order(bink):
    rest = [l for l in IMPORT_LIBS if l not in EARLY_IMPORT_LIBS + LATE_IMPORT_LIBS]
    return EARLY_IMPORT_LIBS + TOOL_LIBS + LATE_IMPORT_LIBS + rest + [bink]
# /OPT:REF as retail (only 89 import thunks survive in retail, which needs
# unreferenced thunk code discarded); stubs.obj carries an anchor table that
# references every ordered entry so the layout survives /OPT:REF. /OPT:NOICF:
# retail keeps identical bodies at separate addresses (one destructor body
# sits at three), and folding would merge the equal-sized 0xCC stubs.
LINK_FLAGS = ["/NOLOGO", "/SUBSYSTEM:WINDOWS", "/FIXED", "/BASE:0x400000", "/INCREMENTAL:NO",
              "/OPT:REF", "/OPT:NOICF", "/MACHINE:IX86"]
MAX_ROUNDS = 4


def library_symbols(extra=()):
    vc6, _ = link_diag.toolenv()
    names = set()
    for lib in TOOL_LIBS + IMPORT_LIBS:
        path = vc6 / "VC98/Lib" / lib
        if path.is_file():
            names |= link_diag.archive_symbols(path)
    for path in extra:
        names |= link_diag.archive_symbols(path)
    return names


def link(objects, libs, out):
    vc6, env = link_diag.toolenv()
    wp = link_diag.wine_path
    rsp = out / "link.rsp"
    lines = LINK_FLAGS + ["/ORDER:@" + wp(out / "stubs/order.txt"), "/OUT:" + wp(out / "m1.exe"),
                          "/MAP:" + wp(out / "m1.map")]
    lines += [f'"{wp(o)}"' for o in objects] + [f'"{wp(l)}"' if "/" in str(l) else l for l in libs]
    rsp.write_text("\r\n".join(lines) + "\r\n", encoding="latin-1")
    proc = subprocess.run(["wine", str(vc6 / "VC98/Bin/LINK.EXE"), "@" + wp(rsp)], env=env,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    log = proc.stdout.decode("latin-1")
    (out / "link.log").write_text(log, encoding="latin-1")
    return proc.returncode, log


def run(objdir, out, pin_data=False, order_tail=False):
    out.mkdir(parents=True, exist_ok=True)
    bink = out / "binkw32.lib"
    implib.build_from_def(ROOT / "scripts/vc6/binkw32.def", bink)
    library_names = library_symbols([bink])
    extra, rounds = set(), []
    pin_plan = None
    if pin_data:   # derived once from the retail image; stubgen.plan adds call pins to it
        index = json.loads((objdir / "objects.json").read_text())
        manifest = json.loads((ROOT / "scripts/data/match_manifest.json").read_text())
        pe, _, pe_sections = pindata.load_retail()
        pin_plan = pindata.derive(objdir, index, manifest, pe, pe_sections)
    for _ in range(MAX_ROUNDS):
        vc6, _ = link_diag.toolenv()
        result = stubgen.plan(objdir, library_names, out / "stubs", extra, pin_data=pin_data, pin_plan=pin_plan,
                              order_tail=order_tail, libdir=vc6 / "VC98/Lib")
        code, log = link(result["objects"], library_order(bink), out)
        unresolved, duplicates = link_diag.parse_link_log(log)
        rounds.append({"exit": code, "unresolved": len(unresolved), "duplicates": len(duplicates)})
        new = set(unresolved) - extra
        if not new:
            break
        extra |= new
    summary = {k: v for k, v in result.items() if k not in ("placed", "objects")}
    summary.update({"rounds": rounds, "link_exit_code": code, "unresolved_after_stubs": len(unresolved),
                    "unresolved_symbols": sorted(unresolved), "duplicates": sorted(duplicates),
                    "warnings": sorted({l.strip() for l in log.splitlines() if "warning LNK" in l})[:200]})
    return summary


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--objdir", type=Path, default=ROOT / "build-vc6/project")
    ap.add_argument("--out", type=Path, default=ROOT / "build-vc6/link_m1")
    ap.add_argument("--distribution-patches", action="store_true",
                    help="after a successful link, apply the post-link distribution patches "
                         "(apply_distribution_patches.py) to m1.exe")
    ap.add_argument("--pin-data", action="store_true",
                    help="M2: bind every bound global to its retail address (absolute symbols) "
                         "instead of placing zero-filled or project storage")
    ap.add_argument("--order-tail", action="store_true",
                    help="M2: place the library tail (import thunks, CRT, COMSUPP, LIBCPMT) at retail "
                         "addresses from scripts/data/crt_tail_layout.json")
    args = ap.parse_args(argv)
    out = args.out.resolve()
    summary = run(args.objdir.resolve(), out, pin_data=args.pin_data, order_tail=args.order_tail)
    (out / "link_report.json").write_text(json.dumps(summary, indent=1) + "\n")
    print(f"LINK exit {summary['link_exit_code']}; unresolved after stubs: {summary['unresolved_after_stubs']}; "
          f"duplicates: {len(summary['duplicates'])}; rounds: {summary['rounds']}")
    print(f"ordered entries {summary['ordered_entries']} (matched {summary['matched_placed']}, "
          f"stubs {summary['stubs_placed']}); extra stubs {summary['extra_stubs']}")
    if not (out / "m1.map").is_file():
        return 1
    if args.distribution_patches and summary["link_exit_code"] == 0:
        import apply_distribution_patches
        if apply_distribution_patches.main(["--image", str(out / "m1.exe")]):
            return 1
    check = mapcheck.check(out / "m1.map", out / "stubs/plan.json")
    (out / "mapcheck.json").write_text(json.dumps(check, indent=1) + "\n")
    mapcheck.print_summary(check)
    if args.order_tail:
        publics, _ = mapcheck.parse_map((out / "m1.map").read_text(encoding="latin-1"))
        tail = taillink.check_map(publics, taillink.load_layout())
        (out / "tailcheck.json").write_text(json.dumps(tail, indent=1) + "\n")
        print(f"library tail: {tail['at_retail_address']} of {tail['symbols']} symbols at retail addresses "
              f"({tail['displaced']} displaced, {tail['not_in_map']} not in map)")
    return 0 if summary["link_exit_code"] == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
