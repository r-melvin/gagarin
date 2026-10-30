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

--hybrid (M2) builds a runnable image instead. It reads the pinned retail image
($GAMEMD_BINARY) while it builds and writes only under build-vc6/ (the output is
ignored by git and must never be committed): unmatched code, gaps and the unidentified
end of .text take retail's bytes, matched bodies that differ from retail give their slot
back, and a data object (hybrid.py) supplies .rdata, .data (with the .bss extent), the
import tables and .rsrc at their retail addresses. Everything matched code references is
pinned to those addresses. scripts/vc6/compare_image.py compares the result with retail.

M3 flags on top of --hybrid (each leaves the default hybrid image unchanged):
  --source-data       data symbols, initialiser table entries and bss extents that project objects define
                      come from the objects when their bytes and relocation targets equal retail's
                      (datasource.py); the rest stays retail fill. vtable_audit.py checks the vtables.
  --search-literals   also place string/float literals with no known address where retail holds them
  --rsrc-from-project .rsrc comes from the project build (match/rsrc/gamemd.rc by RC.EXE, placeholder icon and
                      cursor images, scripts/vc6/rsrc_pack.py) instead of the retail image; a stub link (no --hybrid)
                      always links it
  --rsrc-art-from-retail  byte comparison only: icon and cursor image data read from $GAMEMD_BINARY at link time
  --library-imports   experimental, does not reach section identity (imports.py explains why)

Usage:
  scripts/vc6/build_project.py --out OBJDIR
  scripts/vc6/link_m1.py --objdir OBJDIR [--out DIR]
"""

import argparse
import json
import os
from pathlib import Path
import subprocess
import sys

import datasource
import hybrid as hybrid_module
import implib
import imports
import link_diag
import mapcheck
import pindata
import rsrc_decompile
import rsrc_pack
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


# Retail's import descriptors follow this library order (the DLLs in descriptor order); the thunks
# and the CRT are /ORDERed, so with imports linked from the libraries the library order is free.
RETAIL_IMPORT_ORDER = ["KERNEL32.LIB", "USER32.LIB", "GDI32.LIB", "ADVAPI32.LIB", "SHELL32.LIB", "OLE32.LIB",
                       "OLEAUT32.LIB", "WINMM.LIB", "WSOCK32.LIB", "DDRAW.LIB", "DSOUND.LIB", "VERSION.LIB",
                       "COMCTL32.LIB", "IMM32.LIB"]


def library_order(bink, library_imports=False):
    if library_imports:
        return RETAIL_IMPORT_ORDER + [bink] + TOOL_LIBS
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


def link(objects, libs, out, includes=()):
    vc6, env = link_diag.toolenv()
    wp = link_diag.wine_path
    rsp = out / "link.rsp"
    lines = LINK_FLAGS + ["/ORDER:@" + wp(out / "stubs/order.txt"), "/OUT:" + wp(out / "m1.exe"),
                          "/MAP:" + wp(out / "m1.map")]
    lines += [f"/INCLUDE:{n}" for n in includes]
    lines += [f'"{wp(o)}"' for o in objects] + [f'"{wp(l)}"' if "/" in str(l) else l for l in libs]
    rsp.write_text("\r\n".join(lines) + "\r\n", encoding="latin-1")
    proc = subprocess.run(["wine", str(vc6 / "VC98/Bin/LINK.EXE"), "@" + wp(rsp)], env=env,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    log = proc.stdout.decode("latin-1")
    (out / "link.log").write_text(log, encoding="latin-1")
    return proc.returncode, log


def rsrc_object(objdir, out, art_from_retail=False):
    """COFF object (rsrc_pack.rsrc_object) for the project's resources (build_project.py wrote objdir/rsrc/gamemd.res), or None when
    the object directory has none. art_from_retail swaps the icon and cursor image data for the ones in
    $GAMEMD_BINARY (rsrc_pack.pack); that .res lives under `out`, which the caller keeps under build-vc6/."""
    res = objdir / "rsrc/gamemd.res"
    if not res.is_file():
        return None
    (out / "rsrc").mkdir(parents=True, exist_ok=True)
    if art_from_retail:
        res = rsrc_pack.pack(objdir / "rsrc/gamemd_rc.res", out / "rsrc/gamemd_art.res", True)
    return rsrc_pack.rsrc_object(rsrc_pack.read_res(res.read_bytes()), out / "rsrc/gamemd_rsrc.obj")


def rsrc_pieces(image, retail):
    """Placement pieces for the project's .rsrc: the whole section less the icon and cursor image data
    (placeholder or retail art, neither of which is recovered source) and the padding after it."""
    locations = []
    rsrc_decompile.read_resources(None, locations, image.read_bytes())
    start, vsize, _, _ = retail.by_name[".rsrc"]
    art = sorted((rva + 0x400000, size + (-size % 4)) for t, _, rva, size in locations if t in (1, 3))
    pieces, cursor = [], start
    for va, size in art:
        if va > cursor:
            pieces.append([".rsrc", cursor, va - cursor, "project", "rsrc"])
        cursor = va + size
    if cursor < start + vsize:
        pieces.append([".rsrc", cursor, start + vsize - cursor, "project", "rsrc"])
    return pieces


def run(objdir, out, pin_data=False, order_tail=False, hybrid=False, source_data=False, search=(), library_imports=False,
        rsrc=False, art_from_retail=False):
    out.mkdir(parents=True, exist_ok=True)
    rsrc_obj = rsrc_object(objdir, out, art_from_retail) if rsrc else None
    if rsrc and rsrc_obj is None:
        raise SystemExit("link_m1: no resources in the object directory (build_project.py builds objdir/rsrc/gamemd.res)")
    retail = None
    linked_diff = {}
    reject = set()   # (VA, size) of source-placed data that did not come out equal to retail's bytes
    if hybrid:
        pin_data = order_tail = True
        retail = hybrid_module.Retail(pindata.retail_path())
        data_obj, data_layout = hybrid_module.data_object(retail, library_imports=library_imports, rsrc=rsrc_obj is None)
        (out / "hybrid_data.obj").write_bytes(data_obj)
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
    for _ in range(MAX_ROUNDS + 4):
        vc6, _ = link_diag.toolenv()
        result = stubgen.plan(objdir, library_names, out / "stubs", extra, pin_data=pin_data, pin_plan=pin_plan,
                              order_tail=order_tail, libdir=vc6 / "VC98/Lib", retail=retail,
                              source_data=source_data, data_reject=reject, data_search=search, library_imports=library_imports)
        objects = result["objects"]
        if source_data:
            data_obj, data_layout = hybrid_module.data_object(retail, result["_data_pieces"], library_imports,
                                                              rsrc=rsrc_obj is None)
            (out / "hybrid_data.obj").write_bytes(data_obj)
        includes = ()
        if hybrid:
            objects = [out / "hybrid_data.obj"] + objects
            includes = result["order_symbols"]
            if library_imports:   # pull the import library members in retail's slot order
                includes = imports.import_symbols(retail, vc6 / "VC98/Lib", [bink],
                                                  {n for n, _ in result["thunk_names"]})[0] + includes
        if rsrc_obj:
            objects = objects + [rsrc_obj]
        code, log = link(objects, library_order(bink, library_imports), out, includes)
        unresolved, duplicates = link_diag.parse_link_log(log)
        rounds.append({"exit": code, "unresolved": len(unresolved), "duplicates": len(duplicates)})
        new = set(unresolved) - extra
        if source_data and code == 0 and not new:
            # a source-placed piece the linker put somewhere else, or filled differently, gives its place back
            bad = datasource.verify_image((out / "m1.exe").read_bytes(), result["_data_pieces"], retail)
            rounds[-1]["data_pieces_differing"] = len(bad)
            if bad:
                reject |= set(bad)
                linked_diff.update({f"0x{va:X}+{size}": [list(d) for d in diffs] for (va, size), diffs in bad.items()})
                continue
        if not new:
            break
        extra |= new
    if hybrid:
        placement = [[".text", va, size, origin, name] for va, size, origin, name in result["text_pieces"]]
        for p in result.get("_data_pieces", ()):
            section = ".data" if p["va"] >= retail.by_name[".data"][0] else ".rdata"
            placement.append([section, p["va"], p["size"], "project", p["names"][0]])
        if rsrc_obj and code == 0:
            placement += rsrc_pieces(out / "m1.exe", retail)
        (out / "placement.json").write_text(json.dumps({"pieces": placement}) + "\n")
    if linked_diff:
        (out / "data_linked_diff.json").write_text(json.dumps(linked_diff, indent=1) + "\n")
    summary = {k: v for k, v in result.items()
               if k not in ("placed", "objects", "order_symbols", "text_pieces") and not k.startswith("_")}
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
    ap.add_argument("--hybrid", action="store_true",
                    help="M2: runnable image (implies --pin-data --order-tail): unmatched code and all data, "
                         "the resources and the import tables take their bytes from $GAMEMD_BINARY at build time")
    ap.add_argument("--source-data", action="store_true",
                    help="M3 (with --hybrid): data symbols that project objects define at a known retail address "
                         "and whose compiled contents equal retail's are placed from the objects, not from the image")
    ap.add_argument("--search-literals", action="store_true",
                    help="with --source-data: a string or float literal with no known address is placed where retail "
                         "holds exactly its bytes, when that is the only such place")
    ap.add_argument("--library-imports", action="store_true",
                    help="M3 (with --hybrid): the import address table, lookup tables, hint/name strings, descriptors "
                         "and the import thunks come from the import libraries, pulled in retail's slot order")
    ap.add_argument("--rsrc-from-project", action="store_true",
                    help="with --hybrid: .rsrc comes from the project build (objdir/rsrc/gamemd.res, RC.EXE and CVTRES) "
                         "instead of the retail image; without --hybrid the project resources are always linked "
                         "when the object directory has them")
    ap.add_argument("--rsrc-art-from-retail", action="store_true",
                    help="byte comparison only: the icon and cursor image data of the project .rsrc is read from "
                         "$GAMEMD_BINARY at link time (the layout and group directories stay the project's); "
                         "implies --rsrc-from-project; --out must be under build-vc6/")
    args = ap.parse_args(argv)
    out = args.out.resolve()
    if args.library_imports and not args.hybrid:
        ap.error("--library-imports needs --hybrid")
    if args.search_literals and not args.source_data:
        ap.error("--search-literals needs --source-data")
    if args.source_data and not args.hybrid:
        ap.error("--source-data needs --hybrid")
    if args.rsrc_art_from_retail and ROOT / "build-vc6" not in out.parents:
        ap.error("--rsrc-art-from-retail embeds retail artwork: --out must be under build-vc6/")
    if args.rsrc_art_from_retail and not os.environ.get("GAMEMD_BINARY"):
        ap.error("--rsrc-art-from-retail needs GAMEMD_BINARY")
    if (args.rsrc_from_project or args.rsrc_art_from_retail) and not args.hybrid:
        ap.error("--rsrc-from-project and --rsrc-art-from-retail need --hybrid (a stub link always links the project resources)")
    if args.hybrid and ROOT / "build-vc6" not in out.parents and out != ROOT / "build-vc6":
        ap.error("--hybrid embeds bytes of the retail image in its outputs: --out must be under build-vc6/")
    summary = run(args.objdir.resolve(), out, pin_data=args.pin_data, order_tail=args.order_tail, hybrid=args.hybrid,
                  source_data=args.source_data, search=("string", "float") if args.search_literals else (),
                  library_imports=args.library_imports,
                  rsrc=args.rsrc_from_project or args.rsrc_art_from_retail or not args.hybrid and (args.objdir / "rsrc/gamemd.res").is_file(),
                  art_from_retail=args.rsrc_art_from_retail)
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
