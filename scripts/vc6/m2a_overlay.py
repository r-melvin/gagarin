#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads both images at run time, embeds no retail bytes.
"""M2a: compare every matched function in the M1 link image with retail, in place.

For each exact manifest row the linked bytes at the row's address are compared with
the retail bytes at the same address (relocations already applied by the linker, so
this is stricter than relocation-normalised matching). Differing dwords whose retail
and linked values both look like image addresses are classed as "displaced address"
(the referenced global or function sits elsewhere in the link); anything else is
"other". Displaced targets are aggregated by retail address: that list is the data
placement work for a runnable hybrid (M2).

Optionally writes an overlay image: a copy of the retail file with every identical
matched body written back from the link (a build output; never commit it).

Usage:
  scripts/vc6/m2a_overlay.py --link DIR [--binary gamemd.exe] [--json OUT] [--overlay OUT.exe]
"""
import argparse
import collections
import json
import os
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from verify_vtable import ROOT, load_pe  # noqa: E402

RETAIL_SHA = "1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c"


def file_offset(sections, va, size):
    for _, start, vsize, rawptr, rawsize in sections:
        if start <= va and va + size <= start + min(vsize, rawsize):
            return rawptr + va - start
    return None


def looks_like_va(value, lo, hi):
    return lo <= value < hi


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("--link", required=True, help="link_m1.py output directory (contains m1.exe)")
    ap.add_argument("--binary", default=os.environ.get("GAMEMD_BINARY"))
    ap.add_argument("--manifest", default=str(ROOT / "scripts/data/match_manifest.json"))
    ap.add_argument("--json", help="write the full report here")
    ap.add_argument("--overlay", help="write the retail-plus-identical-bodies overlay image here")
    args = ap.parse_args(argv)

    retail, base, rsec = load_pe(args.binary, RETAIL_SHA)
    linked_path = Path(args.link) / "m1.exe"
    import hashlib
    linked, lbase, lsec = load_pe(linked_path, hashlib.sha256(linked_path.read_bytes()).hexdigest())
    if base != lbase:
        raise SystemExit(f"image base differs: retail {base:#x}, linked {lbase:#x}")
    hi = max(s[1] + s[2] for s in rsec)

    rows = {}
    for r in json.load(open(args.manifest)):
        if r["status"] == "matched":
            rows.setdefault(int(r["addr"], 16), r)

    identical, differ, missing = [], [], []
    displaced = collections.Counter()
    displaced_calls = collections.Counter()
    other_bytes = 0
    for addr in sorted(rows):
        r = rows[addr]
        n = int(r["len"], 16)
        ro, lo = file_offset(rsec, addr, n), file_offset(lsec, addr, n)
        if ro is None or lo is None:
            missing.append(r["addr"])
            continue
        a, b = retail[ro:ro + n], linked[lo:lo + n]
        if a == b:
            identical.append(addr)
            continue
        kinds = collections.Counter()
        i = 0
        while i < n:
            if a[i] == b[i]:
                i += 1
                continue
            # Align on the dword containing the first differing byte, scanning back up to 3.
            j = max(0, i - 3)
            hit = False
            for k in range(j, i + 1):
                if k + 4 <= n:
                    rv, lv = struct.unpack_from("<I", a, k)[0], struct.unpack_from("<I", b, k)[0]
                    if rv != lv and looks_like_va(rv, base, hi) and looks_like_va(lv, base, hi):
                        displaced[rv] += 1
                        kinds["displaced"] += 1
                        i = k + 4
                        hit = True
                        break
            if not hit:
                # A REL32 operand: both values decode to in-image targets from the same site.
                for k in range(j, i + 1):
                    if k + 4 <= n:
                        rv, lv = struct.unpack_from("<i", a, k)[0], struct.unpack_from("<i", b, k)[0]
                        rt, lt = addr + k + 4 + rv, addr + k + 4 + lv
                        if rv != lv and looks_like_va(rt, base, hi) and looks_like_va(lt, base, hi):
                            displaced_calls[rt] += 1
                            kinds["displaced_call"] += 1
                            i = k + 4
                            hit = True
                            break
            if not hit:
                kinds["other"] += 1
                other_bytes += 1
                i += 1
        differ.append({"addr": r["addr"], "name": r["name"], "tu": r["tu"], **kinds})

    only_displaced = sum(1 for d in differ if not d.get("other"))
    report = {
        "matched_rows": len(rows), "identical": len(identical), "differ": len(differ),
        "differ_only_displaced_addresses": only_displaced,
        "differ_with_other_bytes": len(differ) - only_displaced, "missing": missing,
        "displaced_targets": len(displaced),
        "top_displaced": [[f"{va:#x}", c] for va, c in displaced.most_common(40)],
        "displaced_call_targets": len(displaced_calls),
        "top_displaced_calls": [[f"{va:#x}", c] for va, c in displaced_calls.most_common(40)],
        "differing_functions": differ,
    }
    print(f"matched rows {len(rows)}: identical in place {len(identical)}, differ {len(differ)} "
          f"({only_displaced} only through displaced addresses, {len(differ) - only_displaced} with other bytes), "
          f"missing {len(missing)}")
    print(f"distinct displaced call targets {len(displaced_calls)}; top: "
          + ", ".join(f"{va:#x}x{c}" for va, c in displaced_calls.most_common(10)))
    print(f"distinct displaced targets {len(displaced)}; top: "
          + ", ".join(f"{va:#x}x{c}" for va, c in displaced.most_common(10)))
    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=1))
    if args.overlay:
        out = bytearray(retail)
        for addr in identical:
            n = int(rows[addr]["len"], 16)
            ro, lo = file_offset(rsec, addr, n), file_offset(lsec, addr, n)
            out[ro:ro + n] = linked[lo:lo + n]
        Path(args.overlay).write_bytes(bytes(out))
        print(f"overlay written: {args.overlay} ({'equal to' if bytes(out) == retail else 'differs from'} retail)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
