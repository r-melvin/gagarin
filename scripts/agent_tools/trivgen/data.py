#!/usr/bin/env python3
# Provenance: original. Candidate selection for trivgen: worklist, exclusions, TU map, vtable slots.
import csv
import glob
import json
import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
import common  # noqa: E402

SR = os.environ.get("GAG_SCRATCH_ROOT") or str(common.MAIN.parent / "gagarin-scratch")   # disk scratch next to the main checkout
WORKLIST = os.environ.get("TRIVGEN_WORKLIST", SR + "/worklist/worklist.csv")
TUMAP = os.environ.get("TRIVGEN_TUMAP", SR + "/tumap2/tu_map_v2.csv")
FUNC_TO_TU = os.environ.get("TRIVGEN_FUNC_TO_TU", SR + "/tumap/func_to_tu.csv")
WT = Path(os.environ.get("TRIVGEN_WT", SR + "/trivgen/wt"))  # isolated worktree at main HEAD
MAIN = common.MAIN

CLAIM = re.compile(r"^(?://\s*)?(?:FUNCTION|SYNTHETIC|TEMPLATE|LIBRARY|STUB):\s*GAMEMD\s+(0x[0-9A-Fa-f]+)(.*)$", re.M)
DIFFCLAIM = re.compile(r"^\+// (?:FUNCTION|SYNTHETIC|TEMPLATE|LIBRARY|STUB): GAMEMD (0x[0-9A-Fa-f]+)(.*)$", re.M)


def _grep_claims(root):
    """Column-zero body claims in .cpp/.c/.h under root (decl-only markers are not claims)."""
    out = set()
    r = subprocess.run(["grep", "-rhE", r"^// (FUNCTION|SYNTHETIC|TEMPLATE|LIBRARY|STUB): GAMEMD 0x[0-9A-Fa-f]+",
                        str(root), "--include=*.[cC][pP][pP]", "--include=*.[cC]", "--include=*.[hH]", "--include=*.[iI][nN][lL]",
                        "--exclude=trivial_tu*_methods.*"],
                       capture_output=True, text=True)
    for line in r.stdout.splitlines():
        m = re.match(r"^// (?:FUNCTION|SYNTHETIC|TEMPLATE|LIBRARY|STUB): GAMEMD (0x[0-9A-Fa-f]+)(.*)$", line)
        if m and "decl;" not in m.group(2) and "declaration" not in m.group(2):
            out.add(int(m.group(1), 16))
    return out


def inflight_claims():
    """Addresses claimed by READY packets and the mgm tree: (addr -> source)."""
    out = {}
    pats = [SR + "/" + p for p in ("w*/READY", "w5-mgm", "prep-*/READY", "cx-*/READY", "fu-*/READY", "tumig*/READY")]
    dirs = [d for p in pats for d in glob.glob(p)]
    for d in dirs:
        for f in glob.glob(d + "/**/manifest_delta.json", recursive=True) + glob.glob(d + "/delta*.json"):
            try:
                data = json.load(open(f))
            except Exception:
                continue
            rows = data if isinstance(data, list) else data.get("rows", data.get("add", []))
            for r in rows if isinstance(rows, list) else []:
                if isinstance(r, dict) and "addr" in r:
                    try:
                        out.setdefault(common.h(r["addr"]), f)
                    except Exception:
                        pass
        for f in glob.glob(d + "/**/*.diff", recursive=True) + glob.glob(d + "/**/*.patch", recursive=True):
            try:
                text = open(f, errors="replace").read()
            except Exception:
                continue
            for m in DIFFCLAIM.finditer(text):
                if "decl;" not in m.group(2):
                    out.setdefault(int(m.group(1), 16), f)
        for f in glob.glob(d + "/**/results.tsv", recursive=True) + glob.glob(d + "/*.tsv"):
            try:
                for line in open(f, errors="replace"):
                    m = re.match(r"^(0x[0-9A-Fa-f]+)\t", line)
                    if m:
                        out.setdefault(int(m.group(1), 16), f)
            except Exception:
                pass
    return out


def worktree_claims(manifest_path):
    man = {common.h(r["addr"]) for r in json.load(open(manifest_path))}
    return man


def tu_info():
    """tu_id -> dict(name, lo, hi); and current dir votes from func_to_tu."""
    tus = {}
    for r in csv.DictReader(open(TUMAP)):
        tus[r["tu_id"]] = dict(name=r["name_or_bound"], lo=int(r["text_lo"], 16), hi=int(r["text_hi"], 16),
                               conf=r["confidence"])
    votes = {}
    if os.path.exists(FUNC_TO_TU):
        for r in csv.DictReader(open(FUNC_TO_TU)):
            cur = r.get("current_tu") or ""
            if "/" in cur:
                d = cur.split("/")[1]
                votes.setdefault(r["tu_id"], {}).setdefault(d, 0)
                votes[r["tu_id"]][d] += 1
    return tus, votes


def vtable_index():
    """addr -> list of (class, slot, base_offset, vtable_va)."""
    vt = json.load(open(common.CACHE / "vtable_slots.json"))
    idx = {}
    for v in vt["vtables"]:
        for i, s in enumerate(v["slots"]):
            idx.setdefault(int(s, 16), []).append((v["class"], i, v["base_offset"], v["vtable_va"]))
    return idx


def candidates(max_size=int(os.environ.get("TRIVGEN_MAXSIZE", "32"))):
    rows = [r for r in csv.DictReader(open(WORKLIST)) if int(r["size"]) <= max_size]
    man = worktree_claims(WT / "scripts/data/match_manifest.json")
    body = _grep_claims(MAIN / "match") | _grep_claims(WT / "match")
    infl = inflight_claims()
    keep, drop = [], []
    for r in rows:
        a = int(r["addr"], 16)
        why = ("manifest" if a in man else "main-annotation" if a in body else
               "inflight:" + infl[a] if a in infl else None)
        (drop if why else keep).append((r, why))
    return keep, drop
