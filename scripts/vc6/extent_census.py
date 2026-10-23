#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the developer-supplied pinned PE only.
"""Function-extent census of the retail .text section (link milestone M1).

For every known function entry point in .text this computes the CFG-closed
extent from the entry: the instructions reachable through fall-through and
in-function branches, the jump tables those branches index (read from the
pinned PE) and the byte index tables that select into them. It never uses the
padded or merged lengths of earlier worklists. The output is a fact table of
addresses and lengths, no bytes:

  scripts/data/function_extents.json
    entries: [addr, len, gap, gap_kind, kind, flags]
      addr      entry point (hex string)
      len       CFG-closed extent in bytes (hex string)
      gap       bytes from addr+len to the next entry (hex string)
      gap_kind  "none" | "cc" | "nop" | "zero" | "mixed" (padding class of the gap)
      kind      "engine" | "lzo" | "thunk" | "crt" | "comsupp"
      flags     list: "audit" (span taken from function_extent_audit.json),
                "truncated" (the walk wanted to run past the next entry),
                "table" (jump/byte tables extend the span)

Entry points are the union of ret_imm_census.json, the manifest,
unlisted_entry_points.json and restored_function_entries.txt. The table is
generated once from the developer's own exe (needs GAMEMD_BINARY and objdump)
and is tracked; the exe is not.

Usage:
  GAMEMD_BINARY=/path/gamemd.exe scripts/vc6/extent_census.py [--out FILE] [--jobs N]
"""

import argparse
import bisect
import json
from multiprocessing import Pool
import os
from pathlib import Path
import re
import struct
import subprocess
import sys
import tempfile

from verify_vtable import load_pe

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / "scripts/data"
SHA256 = "1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c"
# Retail .text regions that are not engine code (inventory: LZO, linker
# import thunks, the LIBCMT block and COMSUPP).
REGIONS = [(0x55BB90, 0x55C2B0, "lzo"), (0x7C8962, 0x7C8A3A, "thunk"), (0x7DC720, 0x7DCE62, "comsupp"),
           (0x7DCE62, 0x7DCFC3, "thunk"), (0x7C8A3A, 0x7E1000, "crt")]
MAX_WINDOW = 0x8000

LINE = re.compile(r"^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s*(.*)$")
BRANCH = re.compile(r"^(j\w+|loop\w*|jecxz)\s+(?:0x)?([0-9a-f]+)\s*$")
JTABLE = re.compile(r"^jmp\s+DWORD PTR \[\w+\*4\+0x([0-9a-f]+)\]$")
BTABLE = re.compile(r"^(?:movzx|mov)\s+\w+,\s*BYTE PTR \[\w+\+0x([0-9a-f]+)\]$")


def kind_of(addr):
    for lo, hi, kind in REGIONS:
        if lo <= addr < hi:
            return kind
    return "engine"


def entry_points():
    """(trusted, leads): sorted entry points (ints) from the tracked lists.

    Trusted: the census's Ghidra function-list entries, every manifest row,
    unlisted_entry_points.json and restored_function_entries.txt. Leads: the
    census's sweep entries (data references, aligned-after-padding, call
    targets); a lead that lies inside a trusted function's walked extent is an
    interior label (a jump-table case, usually) and is dropped.
    """
    trusted, leads = set(), set()
    census = json.loads((DATA / "ret_imm_census.json").read_text())
    for f in census["functions"]:
        (leads if f.get("entry_point_is_lead") else trusted).add(int(f["addr"], 16))
    trusted.update(int(r["addr"], 16) for r in json.loads((DATA / "match_manifest.json").read_text()))
    trusted.update(int(a, 16) for a in json.loads((DATA / "unlisted_entry_points.json").read_text()))
    for line in (DATA / "restored_function_entries.txt").read_text().split():
        trusted.add(int(line, 16))
    return sorted(trusted), sorted(leads - trusted)


def objdump(blob, va):
    with tempfile.NamedTemporaryFile(suffix=".bin") as tmp:
        tmp.write(blob)
        tmp.flush()
        text = subprocess.run(["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel",
                               f"--adjust-vma={va:#x}", tmp.name],
                              capture_output=True, text=True, check=True).stdout
    insns = {}
    last = None
    for line in text.splitlines():
        m = LINE.match(line)
        if not m:
            continue
        a, size, txt = int(m.group(1), 16), len(m.group(2).split()), re.sub(r"\s+", " ", m.group(3).strip())
        if not txt and last is not None:   # continuation of a long instruction
            insns[last] = (insns[last][0] + size, insns[last][1])
            continue
        insns[a] = (size, txt)
        last = a
    return insns


class Image:
    def __init__(self, path):
        self.data, _, sections = load_pe(path, SHA256)
        self.text = next(s for s in sections if s[0] == ".text")

    def read(self, va, n):
        _, start, vsize, rawptr, rawsize = self.text
        end = start + min(vsize, rawsize)
        n = max(0, min(n, end - va))
        return self.data[rawptr + va - start: rawptr + va - start + n]


def walk(img, va, nxt, entries=frozenset()):
    """CFG-closed extent of the function at va, bounded by the next entry nxt.

    A jmp/jcc to another known entry point is a tail call and is not
    followed; jump-table targets always are (their cases are interior)."""
    limit = min(nxt, va + MAX_WINDOW)
    blob = img.read(va, limit - va)
    limit = va + len(blob)
    insns = {}

    def decode_from(a):
        insns.update(objdump(blob[a - va:], a))

    decode_from(va)
    seen, work, flags = set(), [va], set()
    tables = []   # (start, end) of jump and byte tables inside the window
    while work:
        a = work.pop()
        while va <= a < limit and a not in seen:
            if a not in insns:
                decode_from(a)
                if a not in insns:
                    break
            seen.add(a)
            size, txt = insns[a]
            mn = txt.split(" ")[0]
            m = BRANCH.match(txt)
            if m:
                tgt = int(m.group(2), 16)
                if va <= tgt < limit and (tgt == va or tgt not in entries):
                    work.append(tgt)
                elif tgt >= nxt and tgt < va + MAX_WINDOW:
                    flags.add("truncated")
            m = JTABLE.match(txt)
            if m:
                t = int(m.group(1), 16)
                n = 0
                while va <= t + 4 * n and t + 4 * n + 4 <= limit:
                    tgt = struct.unpack_from("<I", blob, t + 4 * n - va)[0]
                    if not (va <= tgt < limit):
                        break
                    work.append(tgt)
                    n += 1
                if n:
                    tables.append((t, t + 4 * n))
            m = BTABLE.match(txt)
            if m and va <= int(m.group(1), 16) < limit:
                tables.append((int(m.group(1), 16), None))
            if mn.startswith("ret") or mn == "jmp" or txt.startswith("(bad)") or mn == "int3":
                break
            a += size
    if not seen:
        return 0, flags
    end = max(a + insns[a][0] for a in seen)
    if tables:
        flags.add("table")
        for start, stop in tables:
            if stop is None:
                # A byte index table runs to the end of the window less its
                # trailing padding; its element count is not encoded anywhere.
                stop = limit
                while stop > start and blob[stop - 1 - va] in (0xCC, 0x90):
                    stop -= 1
            end = max(end, stop)
    return end - va, flags


def gap_kind(raw):
    if not raw:
        return "none"
    for byte, name in ((0xCC, "cc"), (0x90, "nop"), (0x00, "zero")):
        if raw == bytes([byte]) * len(raw):
            return name
    return "mixed"


_IMG = None
DROPPED_LEADS = []


_ENTRIES = frozenset()


def _init(path, entries):
    global _IMG, _ENTRIES
    _IMG = Image(path)
    _ENTRIES = frozenset(entries)


def _one(item):
    va, nxt = item
    length, flags = walk(_IMG, va, nxt, _ENTRIES)
    return va, length, sorted(flags)


def _bounded(entries, end_text):
    return [(a, entries[i + 1] if i + 1 < len(entries) else end_text) for i, a in enumerate(entries)]


def census(binary, jobs=4):
    img = Image(binary)
    _, start, vsize, _, _ = img.text
    end_text = start + vsize
    trusted, leads = entry_points()
    trusted = [a for a in trusted if start <= a < end_text]
    with Pool(jobs, initializer=_init, initargs=(binary, set(trusted) | set(leads))) as pool:
        first = pool.map(_one, _bounded(trusted, end_text), chunksize=64)
        spans = sorted((va, va + length) for va, length, _ in first)
        starts = [s for s, _ in spans]
        interior = set()
        for a in leads:
            i = bisect.bisect_right(starts, a) - 1
            if i >= 0 and a < spans[i][1]:
                interior.add(a)
        entries = sorted(set(trusted) | {a for a in leads if start <= a < end_text and a not in interior})
        items = _bounded(entries, end_text)
        walked = pool.map(_one, items, chunksize=64)
    global DROPPED_LEADS
    DROPPED_LEADS = sorted(interior)
    audit = {int(f["address"], 16): f["corrected_size"]
             for f in json.loads((DATA / "function_extent_audit.json").read_text())["functions"]}
    nexts = dict(items)
    rows = []
    for va, length, flags in walked:
        nxt = nexts[va]
        if va in audit and audit[va] != length:
            length = audit[va]
            flags = sorted(set(flags) | {"audit"})
        length = min(length, nxt - va)
        gap = nxt - va - length
        rows.append([f"0x{va:X}", f"0x{length:X}", f"0x{gap:X}", gap_kind(img.read(va + length, gap)),
                     kind_of(va), flags])
    return rows


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary", default=os.environ.get("GAMEMD_BINARY"))
    ap.add_argument("--out", type=Path, default=DATA / "function_extents.json")
    ap.add_argument("--jobs", type=int, default=4)
    args = ap.parse_args(argv)
    if not args.binary:
        print("extent_census: set GAMEMD_BINARY or --binary", file=sys.stderr)
        return 2
    rows = census(args.binary, args.jobs)
    counts = {}
    for r in rows:
        counts[r[4]] = counts.get(r[4], 0) + 1
    doc = {
        "schema": "gagarin/function_extents/1",
        "binary_sha256": SHA256,
        "provenance": "own-binary: entry points from the tracked census lists; extents by an entry-origin "
                      "CFG walk over the pinned PE (objdump), jump tables read from the PE",
        "generated_by": "scripts/vc6/extent_census.py",
        "fields": ["addr", "len", "gap", "gap_kind", "kind", "flags"],
        "counts": dict(sorted(counts.items())),
        # Sweep leads that the walk of a trusted entry reaches (interior labels).
        "interior_leads_dropped": [f"0x{a:X}" for a in DROPPED_LEADS],
        "entries": rows,
    }
    text = json.dumps(doc, indent=None, separators=(",", ":"))
    # One entry per line keeps diffs reviewable.
    text = text.replace('"entries":[[', '"entries":[\n[').replace("],[", "],\n[")
    args.out.write_text(text + "\n", encoding="utf-8")
    print(f"{len(rows)} entries -> {args.out}  {doc['counts']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
