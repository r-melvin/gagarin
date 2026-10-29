#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; reads the developer-supplied pinned PE (GAMEMD_BINARY)
# and tracked census data. Output holds addresses, lengths and hashes only; no
# retail bytes or instruction text are written.
"""Cluster engine functions by normalised instruction shape and report reuse.

Every kind=='engine' function in function_extents.json is disassembled
(objdump, as extent_census does) and reduced to a shape: mnemonics, operand
forms and register names are kept (register allocation is part of a match);
absolute addresses inside the image, and call/jump targets, are masked.
Two levels are hashed:
  exact   other immediates and displacements are kept
  coarse  every numeric immediate/displacement is masked too (ret N kept)
Families with >=2 members and >=1 unmatched member are written to JSON, sorted
by recoverable bytes (unmatched bytes in families holding a matched member).

Usage:
  GAMEMD_BINARY=/path/gamemd.exe scripts/vc6/shape_families.py \
      [--out scripts/data/shape_families.json] [--report FILE.md] [--jobs N]
"""

import argparse
from collections import defaultdict
import hashlib
import json
from multiprocessing import Pool
import os
from pathlib import Path
import re
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / "scripts/data"
LEVELS = ("exact", "coarse")
RANK = {"matched": 2, "partial": 1, "unmatched": 0}

NUM = re.compile(r"(?<![\w.])(-?)0x([0-9a-f]+)\b")
BARE = re.compile(r"^(?:0x)?[0-9a-f]+$")
BRANCH = re.compile(r"^(?:j\w+|call|loop\w*|jecxz)$")


def normalise(text, lo, hi, coarse):
    """One objdump-intel instruction text -> shape string."""
    parts = text.split(None, 1)
    mnem = parts[0]
    # rep/lock prefixes: keep them and treat the next word as the mnemonic
    while mnem in ("rep", "repe", "repz", "repne", "repnz", "lock") and len(parts) > 1:
        parts = parts[1].split(None, 1)
        mnem = mnem + " " + parts[0]
    last = mnem.split()[-1]
    ops = parts[1].strip() if len(parts) > 1 else ""
    if BRANCH.match(last) and BARE.match(ops):
        return mnem + " T"

    def sub(m):
        neg, digits = m.group(1), m.group(2)
        if not neg and lo <= int(digits, 16) < hi:
            return "A"
        if coarse and last != "ret":
            return "N"
        return m.group(0)
    return (mnem + " " + NUM.sub(sub, ops)).strip()


def shape_hashes(insn_texts, lo, hi):
    out = []
    for coarse in (False, True):
        body = "\n".join(normalise(t, lo, hi, coarse) for t in insn_texts)
        out.append(hashlib.sha1(body.encode()).hexdigest()[:16])
    return out


def cluster(funcs):
    """funcs: dicts with addr, len, status, hashes=[exact, coarse], n_insns.

    Returns {level: [family]} for families with >=2 members and >=1 unmatched.
    """
    result = {}
    for li, level in enumerate(LEVELS):
        groups = defaultdict(list)
        for f in funcs:
            groups[f["hashes"][li]].append(f)
        fams = []
        for h, mem in groups.items():
            if len(mem) < 2:
                continue
            un = [m for m in mem if m["status"] == "unmatched"]
            if not un:
                continue
            matched = [m for m in mem if m["status"] == "matched"]
            partial = [m for m in mem if m["status"] == "partial"]
            ubytes = sum(m["len"] for m in un)
            ex = max(matched, key=lambda m: (m.get("pct", 100), -m["len"], -m["addr"])) if matched else None
            fams.append({
                "hash": h, "n_insns": mem[0]["n_insns"], "func_len": mem[0]["len"],
                "members": len(mem), "matched": len(matched), "partial": len(partial),
                "unmatched": len(un), "unmatched_bytes": ubytes,
                "recoverable_bytes": ubytes if matched else 0,
                "exemplar": ex, "unmatched_members": sorted(un, key=lambda m: m["addr"]),
            })
        fams.sort(key=lambda f: (-f["recoverable_bytes"], -f["unmatched_bytes"], f["hash"]))
        result[level] = fams
    return result


def totals(fams_by_level):
    out = {}
    for level, fams in fams_by_level.items():
        rec = [f for f in fams if f["matched"]]
        out[level] = {
            "families": len(fams), "families_with_matched_exemplar": len(rec),
            "unmatched_functions_in_families": sum(f["unmatched"] for f in fams),
            "unmatched_bytes_in_families": sum(f["unmatched_bytes"] for f in fams),
            "recoverable_functions": sum(f["unmatched"] for f in rec),
            "recoverable_bytes": sum(f["unmatched_bytes"] for f in rec),
        }
    return out


# ---- binary-dependent part -------------------------------------------------

def _disasm(job):
    addr, blob = job
    from extent_census import objdump
    insns = objdump(blob, addr)
    return addr, [t for _, (_, t) in sorted(insns.items())]


def load_inputs():
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from verify_vtable import load_pe
    ext = json.loads((DATA / "function_extents.json").read_text())
    binary = os.environ.get("GAMEMD_BINARY")
    if not binary:
        sys.exit("GAMEMD_BINARY is not set")
    data, _, sections = load_pe(binary, ext["binary_sha256"])
    return ext, data, sections


def va_reader(data, sections):
    def read(va, n):
        for _, start, vsize, rawptr, rawsize in sections:
            if start <= va and va + n <= start + min(vsize, rawsize):
                return data[rawptr + va - start: rawptr + va - start + n]
        return None
    return read


def rtti_owners(read, text_lo, text_hi):
    """function address -> ['Class' (slot n), ...] from RTTI vtables."""
    owners = defaultdict(list)
    classes = json.loads((DATA / "rtti_classes.json").read_text())["classes"]
    for c in classes.values():
        for loc in c["locators"]:
            vt = loc.get("vtable_va")
            if not vt:
                continue
            vt = int(vt, 16)
            for slot in range(512):
                raw = read(vt + 4 * slot, 4)
                if raw is None:
                    break
                tgt = struct.unpack("<I", raw)[0]
                if not text_lo <= tgt < text_hi:
                    break
                tag = f"{c['demangled_name']}[{slot}]"
                if tag not in owners[tgt]:
                    owners[tgt].append(tag)
    return owners


def manifest_index():
    idx = {}
    for r in json.loads((DATA / "match_manifest.json").read_text()):
        a = int(r["addr"], 16)
        if a not in idx or RANK[r["status"]] > RANK[idx[a]["status"]]:
            idx[a] = r
    return idx


def build(jobs):
    ext, data, sections = load_inputs()
    read = va_reader(data, sections)
    lo = min(s[1] for s in sections)
    hi = max(s[1] + s[2] for s in sections)
    text = next(s for s in sections if s[0] == ".text")
    man = manifest_index()
    spans = [(int(a, 16), int(n, 16)) for a, n, _, _, k, _ in ext["entries"] if k == "engine"]
    work = [(a, read(a, n)) for a, n in spans]
    with Pool(jobs) as pool:
        dis = dict(pool.imap_unordered(_disasm, work, chunksize=64))
    owners = rtti_owners(read, text[1], text[1] + text[2])
    funcs = []
    for a, n in spans:
        texts = dis.get(a) or []
        if not texts:
            continue
        m = man.get(a)
        f = {"addr": a, "len": n, "n_insns": len(texts),
             "hashes": shape_hashes(texts, lo, hi),
             "status": m["status"] if m else "unmatched", "pct": m.get("pct") if m else None}
        if m:
            f.update(tu=m["tu"], sym=m["sym"], name=m.get("name"))
        if a in owners:
            f["rtti"] = owners[a][:3]
        funcs.append(f)
    return funcs


def _fmt(m):
    d = dict(m)
    d.pop("hashes", None)
    d["addr"] = f"0x{m['addr']:X}"
    return {k: v for k, v in d.items() if v is not None}


def to_json(funcs, fams, tot):
    return {
        "schema": "gagarin/shape_families/1",
        "generated_by": "scripts/vc6/shape_families.py",
        "note": "families of engine functions sharing a normalised instruction shape; "
                "addresses/lengths/hashes only. exact keeps non-address immediates, coarse masks them.",
        "functions_hashed": len(funcs), "totals": tot,
        "families": {
            level: [dict(f, exemplar=_fmt(f["exemplar"]) if f["exemplar"] else None,
                         unmatched_members=[_fmt(m) for m in f["unmatched_members"]])
                    for f in fl]
            for level, fl in fams.items()},
    }


def report(fams, tot, nfuncs, top=60, coarse_top=30):
    L = ["# Shape families", "", f"Engine functions hashed: {nfuncs}", "",
         "| level | families | with matched exemplar | unmatched fns in families | unmatched bytes | recoverable fns | recoverable bytes |",
         "|---|---|---|---|---|---|---|"]
    for lv in LEVELS:
        t = tot[lv]
        L.append(f"| {lv} | {t['families']} | {t['families_with_matched_exemplar']} | "
                 f"{t['unmatched_functions_in_families']} | {t['unmatched_bytes_in_families']} | "
                 f"{t['recoverable_functions']} | {t['recoverable_bytes']} |")
    for lv, n in (("exact", top), ("coarse", coarse_top)):
        L += ["", f"## Top {n} {lv} families by recoverable bytes", ""]
        for i, f in enumerate([x for x in fams[lv] if x["matched"]][:n], 1):
            ex = f["exemplar"]
            L.append(f"### {i}. {lv} `{f['hash']}`: {f['recoverable_bytes']} recoverable bytes")
            L.append(f"members {f['members']} (matched {f['matched']}, partial {f['partial']}, "
                     f"unmatched {f['unmatched']}); {f['n_insns']} insns, {f['func_len']} bytes")
            L.append(f"- exemplar: 0x{ex['addr']:X} `{ex.get('name') or ''}` tu `{ex['tu']}` sym `{ex['sym']}`")
            L.append("- unmatched:")
            um = f["unmatched_members"]
            for m in um[:12]:
                r = ", ".join(m["rtti"]) if m.get("rtti") else "-"
                L.append(f"  - 0x{m['addr']:X} len {m['len']} rtti {r}")
            if len(um) > 12:
                L.append(f"  - ... {len(um) - 12} more")
            L.append("")
    return "\n".join(L) + "\n"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--out", default=str(DATA / "shape_families.json"))
    ap.add_argument("--report")
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    args = ap.parse_args(argv)
    funcs = build(args.jobs)
    fams = cluster(funcs)
    tot = totals(fams)
    Path(args.out).write_text(json.dumps(to_json(funcs, fams, tot), indent=1) + "\n")
    if args.report:
        Path(args.report).parent.mkdir(parents=True, exist_ok=True)
        Path(args.report).write_text(report(fams, tot, len(funcs)))
    print(json.dumps(tot, indent=1))


if __name__ == "__main__":
    main()
