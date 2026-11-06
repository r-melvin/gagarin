#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; compiles project sources with the VC6 wrapper and scores rows through
# scripts/vc6/raw_match.py / diff_retail.py against the pinned PE.
"""flag_sweep.py: score every manifest row of a TU under several inline-flag variants.

    flag_sweep.py --tu match/X.cpp [--tu ...] [--variants base,ob2,ob1,ob0] [--json OUT] [-j 4]

Variants take the TU's own `// VC6FLAGS:` line (or the wrapper default) and replace its /Ob* switch:
base = unchanged, obN = /ObN. Each variant compiles once and every row (matched or partial) of the TU is
scored; the tool prints a per-row table and flags rows that regress or gain against base. Rows that
prefer different variants are listed as opposite-side evidence. Needs GAMEMD_BINARY.
"""
import argparse, concurrent.futures as cf, json, os, re, shutil, subprocess, tempfile
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DEFAULT = "/nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2"


def tu_flags(path):
    for l in open(os.path.join(ROOT, path), errors="replace"):
        m = re.match(r"\s*//\s*VC6FLAGS:(.*)", l)
        if m:
            return m.group(1).strip()
    return DEFAULT


def variant_flags(path, v):
    base = tu_flags(path)
    if v == "base":
        return base
    return (re.sub(r"/Ob\d", "", base) + " /Ob" + v[2:]).strip()


def pct(obj, e):
    last = None
    for tool in ("raw_match.py", "diff_retail.py"):
        r = subprocess.run(["python3", f"{ROOT}/scripts/vc6/{tool}", "--obj", obj, "--sym", e["sym"],
                            "--addr", e["addr"], "--len", e["len"]], capture_output=True, text=True)
        if r.returncode == 0 and "100.0%" in r.stdout:
            return 100.0
        for l in r.stdout.splitlines():
            if l.startswith("match:"):
                try:
                    last = float(l.split()[-1].rstrip("%"))
                except ValueError:
                    pass
    return last


def run(tu, v, rows, tmp):
    d = os.path.join(ROOT, os.path.dirname(tu))
    obj = os.path.join(tmp, re.sub(r"\W", "_", tu) + "_" + v + ".obj")
    env = dict(os.environ, VC6_FLAGS=variant_flags(tu, v))
    r = subprocess.run(["bash", f"{ROOT}/scripts/vc6/vc6cl.sh", f"/Fo{obj}", os.path.basename(tu)], cwd=d,
                       env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    if r.returncode or not os.path.exists(obj):
        return {e["addr"]: None for e in rows}
    return {e["addr"]: pct(obj, e) for e in rows}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tu", action="append", required=True)
    ap.add_argument("--variants", default="base,ob2")
    ap.add_argument("--json")
    ap.add_argument("-j", type=int, default=4)
    a = ap.parse_args()
    man = json.load(open(f"{ROOT}/scripts/data/match_manifest.json"))
    vs = a.variants.split(",")
    out = {}
    os.makedirs(f"{ROOT}/build-vc6", exist_ok=True)
    tmp = tempfile.mkdtemp(prefix="flag_sweep_", dir=f"{ROOT}/build-vc6")
    with cf.ThreadPoolExecutor(a.j) as pool:
        jobs = {}
        for tu in a.tu:
            rows = [e for e in man if e["tu"] == tu]
            for v in vs:
                jobs[(tu, v)] = (pool.submit(run, tu, v, rows, tmp), rows)
        for (tu, v), (f, rows) in jobs.items():
            out.setdefault(tu, {})[v] = f.result()
    shutil.rmtree(tmp)
    for tu in a.tu:
        rows = [e for e in man if e["tu"] == tu]
        print(f"== {tu}  base flags: {tu_flags(tu)}")
        for e in sorted(rows, key=lambda e: int(e["addr"], 16)):
            cells = [out[tu][v][e["addr"]] for v in vs]
            b = cells[0]
            mark = ""
            for v, c in zip(vs[1:], cells[1:]):
                if b is not None and c is not None and c != b:
                    mark += f" {v}:{'GAIN' if c > b else 'LOSS'}"
                elif (b is None) != (c is None):
                    mark += f" {v}:COMPILE"
            print(f"  {e['addr']} {e['status']:<8} " + " ".join(f"{v}={c}" for v, c in zip(vs, cells)) + f"  {e['name'][:50]}{mark}")
    if a.json:
        json.dump(out, open(a.json, "w"), indent=1)


if __name__ == "__main__":
    main()
