#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Compare reccmp's function matching with scripts/data/match_manifest.json.

Run with reccmp's own interpreter (reccmp_image.py finds it from the reccmp-reccmp script).

reccmp compares the original image with the rebuilt one function by function. This script runs that comparison
in-process and classifies every manifest row (matched and partial) by what reccmp made of its address:

  exact          reccmp matched it to a rebuilt function and the two instruction streams are equal
  diff_names     matched; the streams differ only in the names reccmp prints for call/jump/data operands
                 (an operand's entity is unknown to reccmp, so the two sides name it differently)
  diff_other     matched; the bytes at both addresses are equal but reccmp's instruction streams differ beyond
                 names (it decodes a different extent, or names a tail-jump target)
  diff_bytes     matched; the bytes at the two addresses differ
  unmatched      reccmp knows the function (a marker or a CSV row) but found no rebuilt function for it
  no_entity      reccmp knows nothing at that address: no marker survived its parser (reasons below)

and lists the addresses reccmp reports exact that the manifest does not call matched. no_entity rows carry a reason:
no_marker (no GAMEMD marker line names the address), other_marker (only LIBRARY/SYNTHETIC/TEMPLATE/... markers),
function_marker_lost (a FUNCTION marker names it but reccmp's parser dropped or attached it elsewhere).

Usage:  reccmp_audit.py ORIG EXE PDB SOURCE_DIR MANIFEST MATCH_DIR OUT.json [--csv FILE]
"""

import argparse
import bisect
import collections
import json
from pathlib import Path
import re
import sys

MARKER = re.compile(r"^\s*//\s*(?P<type>\w+):\s*GAMEMD\s+(?P<addr>0x[0-9a-f]+)", re.I)


def marker_index(match_dir):
    """{address: [(type, marker line, next line)]} over the unsanitised sources."""
    index = collections.defaultdict(list)
    for path in Path(match_dir).rglob("*"):
        if path.suffix.lower() not in (".cpp", ".c", ".h", ".asm", ".inc") or not path.is_file():
            continue
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        for i, line in enumerate(lines):
            m = MARKER.match(line)
            if m:
                index[int(m["addr"], 16)].append((m["type"].upper(), line, lines[i + 1] if i + 1 < len(lines) else ""))
    return index


def unmatched_reason(markers):
    """Why a FUNCTION marker that reccmp read found no rebuilt function: its form in the source."""
    functions = [m for m in markers if m[0] == "FUNCTION"]
    if not functions:
        return "no_function_marker"
    if all("(decl" in m[1] or "(declaration" in m[1] for m in functions):
        return "declaration_marker"
    if all(m[2].lstrip().startswith("//") for m in functions):
        return "name_comment_after_marker"
    return "signature_not_resolved"


def stream(pairs):
    return [text for _, text in pairs]


TAGGED = re.compile(r"[^,\[\]+*]*?\((?:FUNCTION|GLOBAL|STRING|VTABLE|LIBRARY|SYNTHETIC|TEMPLATE|STUB|WIDECHAR|FLOAT|DATA|[A-Z]+)\)")
LINE_NOTE = re.compile(r"\s*\t\([^()]*:\d+\)\s*$")
OFFSET = re.compile(r"<OFFSET\d+>")
BIG_HEX = re.compile(r"0x[0-9a-f]{4,}")


def names_only(orig, recomp):
    """True when the two instruction lists differ only in how reccmp names an operand: a tagged entity name
    (`FUN_004071A0 (FUNCTION)`, `DAT_00B0F670 (DATA)`) on one side against another name, an <OFFSETn> placeholder
    or a bare address on the other, and the `(file:line)` note it appends to rebuilt lines."""
    if len(orig) != len(recomp):
        return False

    def scrub(text):
        head, _, tail = LINE_NOTE.sub("", text).partition(" ")
        return head + re.sub(r"\s+", "", BIG_HEX.sub("N", OFFSET.sub("N", TAGGED.sub("N", tail))))

    return all(scrub(a) == scrub(b) for a, b in zip(orig, recomp))


def provenance(placement):
    """addr -> 'project' / 'library' / 'retail' (retail fill: no project or library piece covers it)."""
    pieces = sorted((p[1], p[1] + p[2], p[3]) for p in json.loads(placement.read_text())["pieces"] if p[0] == ".text")
    starts = [p[0] for p in pieces]

    def of(addr):
        i = bisect.bisect_right(starts, addr) - 1
        return pieces[i][2] if i >= 0 and addr < pieces[i][1] else "retail"
    return of


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    for name in ("orig", "exe", "pdb", "source", "manifest", "match_dir", "out"):
        ap.add_argument(name, type=Path)
    ap.add_argument("--csv", type=Path)
    ap.add_argument("--placement", type=Path, help="link placement.json: says which .text bytes the project compiled")
    ap.add_argument("--pair-by-address", action="store_true",
                    help="pair each manifest function with the rebuilt function at the same address (the link is "
                         "address-faithful, mapcheck verifies it) instead of relying on markers or symbols")
    args = ap.parse_args(argv)
    from reccmp.compare import Compare
    from reccmp.project.detect import GhidraConfig, RecCmpTarget, ReportConfig
    from reccmp.types import EntityType, ImageId
    target = RecCmpTarget(target_id="GAMEMD", filename=args.orig.name, sha256="", original_path=args.orig,
                          recompiled_path=args.exe, recompiled_pdb=args.pdb, encoding="utf-8",
                          source_paths=(args.source,), ghidra_config=GhidraConfig(), report_config=ReportConfig(),
                          data_sources=[args.csv] if args.csv else [])
    compare = Compare.from_target(target)
    db = compare._db
    manifest = json.loads(args.manifest.read_text())
    paired = 0
    if args.pair_by_address:
        with db.batch() as batch:
            for row in manifest:
                addr = int(row["addr"], 16)
                recomp = db.get(ImageId.RECOMP, addr)
                orig = db.get(ImageId.ORIG, addr)
                if recomp is None or recomp.matched or (orig is not None and orig.matched):
                    continue
                batch.set(ImageId.ORIG, addr, type=EntityType.FUNCTION, name=row["name"],
                          size=int(row["len"], 16))
                batch.match(addr, addr)
                paired += 1
    reports = {r.orig_addr: r for r in compare.compare_functions()}
    markers = marker_index(args.match_dir)
    origin = provenance(args.placement) if args.placement else (lambda addr: "unknown")
    out = {"rows": {}, "counts": {}}
    counts = collections.Counter()
    for row in manifest:
        addr = int(row["addr"], 16)
        status = row["status"]
        entity = db.get(ImageId.ORIG, addr)
        detail = {}
        if entity is None:
            kinds = {m[0] for m in markers.get(addr, ())}
            reason = "no_marker" if not kinds else ("function_marker_lost" if "FUNCTION" in kinds else "other_marker")
            klass = "no_entity"
            detail["reason"] = reason
            detail["marker_types"] = sorted(kinds)
        elif not entity.matched:
            klass = "unmatched"
            detail["reason"] = unmatched_reason(markers.get(addr, []))
        else:
            rep = reports.get(addr)
            if rep is None:
                klass = "unmatched"
                detail["reason"] = "matched entity not compared"
            elif rep.effective_ratio >= 1.0:
                klass = "exact"
            else:
                diff = rep.result.diff
                klass = "diff_names" if names_only(stream(diff.orig_inst), stream(diff.recomp_inst)) else "diff_other"
                detail["ratio"] = round(rep.ratio, 4)
                size = int(row["len"], 16)
                try:
                    detail["bytes_equal"] = compare.orig_bin.read(addr, size) == compare.recomp_bin.read(rep.recomp_addr, size)
                except Exception:   # reading past a section end
                    detail["bytes_equal"] = None
                if detail["bytes_equal"] is False:
                    klass = "diff_bytes"
        detail["origin"] = origin(addr)
        counts[(status, klass + "/" + detail["origin"])] += 1
        out["rows"].setdefault(row["addr"], []).append({"status": status, "class": klass, "tu": row["tu"],
                                                          "name": row["name"], **detail})
    in_manifest = {int(r["addr"], 16): r["status"] for r in manifest}
    extra = [{"addr": f"0x{a:X}", "name": r.name, "manifest": in_manifest.get(a, "absent")}
             for a, r in sorted(reports.items()) if r.effective_ratio >= 1.0 and in_manifest.get(a) != "matched"
             and not r.is_stub]
    for e in extra:
        e["origin"] = origin(int(e["addr"], 16))
    out["reccmp_exact_not_manifest_matched"] = extra
    out["counts"] = {f"{s}/{k}": n for (s, k), n in sorted(counts.items())}
    out["reccmp_functions_compared"] = len(reports)
    out["paired_by_address"] = paired
    args.out.write_text(json.dumps(out, indent=1) + "\n")
    for k, n in out["counts"].items():
        print(f"{n:7d}  {k}")
    print(f"{len(extra):7d}  reccmp exact, manifest not matched")
    return 0


if __name__ == "__main__":
    sys.exit(main())
