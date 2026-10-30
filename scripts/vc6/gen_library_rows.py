#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads only tracked project data (crt_tail_layout.json,
# function_extents.json, match/ markers) and the toolchain's import libraries. No retail bytes.
"""Write match/_rt/library_tail.h: `// LIBRARY: GAMEMD 0xADDR` markers for the linked library tail.

The tail of retail's .text (import thunks, LIBCMT, LIBCPMT, COMSUPP) is linked from the toolchain
libraries, never recovered as source. scripts/data/crt_tail_layout.json (tail_layout.py) records where
each archive section and import thunk sits; this turns that layout into the project's LIBRARY marker
rows, so ctx.py, the worklist filters (dlib.library_claims, dispatch.py) and the census tools see the
addresses as claimed-as-library instead of unrecovered. Markers already present elsewhere under match/
(match/_rt/library_functions.h and others) are not repeated. Entry points that the extent census lists
inside a placed section or thunk run (interior entries) get a `<name>+0xN` marker.

Marking changes classification only: link_m1.py takes the tail from the layout JSON, not from markers,
so the linked image is unchanged.

Usage:  scripts/vc6/gen_library_rows.py            # rewrite match/_rt/library_tail.h
        scripts/vc6/gen_library_rows.py --check    # exit 1 if the header is stale
        scripts/vc6/gen_library_rows.py --report   # counts and the unattributed census entries
"""
import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tail_layout  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / "match/_rt/library_tail.h"
LAYOUT = ROOT / "scripts/data/crt_tail_layout.json"
EXTENTS = ROOT / "scripts/data/function_extents.json"
EXTRA = ROOT / "scripts/data/library_tail_extra.json"
LIBDIR = ROOT / "toolchain/MSVC600/VC98/Lib"
MARK = re.compile(r"(?m)^// LIBRARY: GAMEMD (0x[0-9A-Fa-f]+)")
THUNK_LEN = 6


def existing_marks(exclude):
    out = set()
    for p in (ROOT / "match").rglob("*"):
        if p.suffix.lower() in (".h", ".cpp", ".c") and p != exclude:
            out.update(int(a, 16) for a in MARK.findall(p.read_text(errors="replace")))
    return out


def dll_of_symbol(libdir):
    """{decorated import symbol: dll stem} from the toolchain import libraries."""
    rev = {}
    for (dll, _), dec in tail_layout.decorated_names(libdir).items():
        rev.setdefault(dec, dll)
    return rev


def thunk_label(name, dlls):
    dll = dlls.get(name)
    plain = re.sub(r"@\d+$", "", name[1:] if name.startswith("_") else name)
    if dll is None:
        return plain if not name.startswith("_Bink") else "binkw32!" + name
    return "%s!%s" % (dll.upper(), plain)


def section_label(s):
    sym = s["symbols"][0][0] if s["symbols"] else "%s#%d" % (Path(s["member"].replace("\\", "/")).name, s["section"])
    return sym


def build(layout, extents, extra, skip, dlls):
    """([(addr, label, note)] new markers, stats, [unattributed census entries])."""
    rows = {}
    spans = []   # (lo, hi, label) of everything the layout places
    for t in layout["thunks"]:
        a = int(t["addr"], 16)
        spans.append((a, a + THUNK_LEN, thunk_label(t["name"], dlls)))
    for s in layout["sections"]:
        a = int(s["addr"], 16)
        spans.append((a, a + s["len"], section_label(s)))
        note = s["library"].split(".")[0] + " " + Path(s["member"].replace("\\", "/")).name
        if s["inferred_by_order"]:
            note += ", placed by archive order"
        rows[a] = (section_label(s), note)
    for t in layout["thunks"]:
        a = int(t["addr"], 16)
        rows[a] = (thunk_label(t["name"], dlls), "import thunk")
    for e in extra["ambiguous_library"]:
        a = int(e["addr"], 16)
        spans.append((a, a + e["len"], e["label"]))
        rows[a] = (e["label"], "LIBCMT/LIBCPMT section, member ambiguous")
    spans.sort()
    foreign = [(int(r["lo"], 16), int(r["hi"], 16)) for r in extra["not_library"]]
    interior, unattributed = {}, []
    for addr, ln, _gap, _gk, kind, _fl in extents["entries"]:
        a = int(addr, 16)
        if kind == "engine" or a < 0x7C8362:
            continue
        hit = next((sp for sp in spans if sp[0] <= a < sp[1]), None)
        if hit is None and any(lo <= a < hi for lo, hi in foreign):
            continue
        if hit is None:
            unattributed.append((a, int(ln, 16), kind))
        elif a not in rows:
            interior[a] = ("%s+0x%X" % (hit[2], a - hit[0]), "entry inside a placed section")
    rows.update(interior)
    new = sorted((a, l, n) for a, (l, n) in rows.items() if a not in skip)
    stats = {"markers_total": len(rows), "markers_new": len(new), "already_marked": len(rows) - len(new),
             "interior_entries": len(interior), "not_library_entries": sum(1 for e in extents["entries"] if e[4] != "engine" and any(int(r["lo"], 16) <= int(e[0], 16) < int(r["hi"], 16) for r in extra["not_library"])),
             "unattributed_entries": len(unattributed),
             "unattributed_bytes": sum(u[1] for u in unattributed)}
    return new, stats, unattributed


HEAD = """// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   GENERATED by scripts/vc6/gen_library_rows.py from scripts/data/crt_tail_layout.json (crt_ident
//   placement of the VC6 LIBCMT/LIBCPMT/COMSUPP members and the retail import-thunk runs). Do not
//   edit: rerun the script. The bodies are linked from the toolchain libraries; there is no source to
//   recover. Each marker is followed by the library symbol (mangled for C++ members) or by
//   DLL!function for a `JMP dword ptr [IAT]` linker import thunk. A `+0xN` suffix marks an entry
//   point that the extent census lists inside a larger section. Addresses that match/_rt/
//   library_functions.h or another header already marks are not repeated here.
#ifndef GG_MATCH_RT_LIBRARY_TAIL_H
#define GG_MATCH_RT_LIBRARY_TAIL_H
"""


def render(new):
    out = [HEAD]
    for a, label, note in new:
        out.append("// %s\n// LIBRARY: GAMEMD 0x%x\n// %s\n" % (note, a, label))
    out.append("#endif  // GG_MATCH_RT_LIBRARY_TAIL_H\n")
    return "\n".join(out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--out", type=Path, default=OUT)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--report", action="store_true")
    args = ap.parse_args(argv)
    layout = json.loads(LAYOUT.read_text())
    extents = json.loads(EXTENTS.read_text())
    extra = json.loads(EXTRA.read_text())
    new, stats, unattributed = build(layout, extents, extra, existing_marks(args.out.resolve()), dll_of_symbol(LIBDIR))
    text = render(new)
    print(json.dumps(stats))
    if args.report:
        for a, ln, kind in unattributed:
            print("unattributed 0x%X len %d (%s)" % (a, ln, kind))
        return 0
    if args.check:
        return 0 if args.out.exists() and args.out.read_text() == text else 1
    args.out.write_text(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
