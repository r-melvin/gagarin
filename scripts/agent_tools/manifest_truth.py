#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; measures compiled objects against the retail span, embeds no retail bytes.
"""manifest_truth.py: check match_manifest.json against a built tree.

    manifest_truth.py [--tree PATH] [--out DIR] [--jobs 4] [--tu match/x.cpp ...] [--tol 0.5]
                      [--no-strict] [--reuse-objs]

For every TU of TREE: compile it with the project wrapper, then
  * every `partial` row is scored with partial_score.score (the same rule refresh_partials uses);
  * every `matched` row is run through raw_match and strict verify_relocations (central bindings only).
Reports (TSV + summary.txt in --out):
  pct_off        partial rows whose stored pct differs from the measured one by more than --tol
  raw100_partial partial rows that measure 100.0 but stay partial, with raw_match and strict results
  strict_fail    matched rows failing raw_match or strict verify_relocations
  noscore        partial rows with no score; compile_fail: TUs that did not build
Read-only on the tree except for object files in --out. Exit 0 always (it reports; it does not gate).
"""
import argparse, concurrent.futures as cf, json, os, subprocess, sys, tempfile


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=os.getcwd())
    ap.add_argument("--out", required=True)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--tu", action="append", default=[])
    ap.add_argument("--tol", type=float, default=0.5)
    ap.add_argument("--no-strict", action="store_true")
    ap.add_argument("--reuse-objs", action="store_true")
    a = ap.parse_args()
    tree = os.path.abspath(a.tree)
    sys.path.insert(0, os.path.join(tree, "scripts/vc6"))
    import partial_score
    a.out = os.path.abspath(a.out)
    os.makedirs(a.out, exist_ok=True)
    objdir = os.path.join(a.out, "obj")
    os.makedirs(objdir, exist_ok=True)
    man = json.load(open(os.path.join(tree, "scripts/data/match_manifest.json")))
    by_tu = {}
    for r in man:
        by_tu.setdefault(r["tu"], []).append(r)
    tus = sorted(by_tu)
    if a.tu:
        tus = [t for t in tus if t in set(a.tu)]
    skips = partial_score.patch_skips(tree)
    env = dict(os.environ)

    def run(cmd):
        return subprocess.run(cmd, cwd=tree, env=env, capture_output=True, text=True)

    def one_tu(n, tu):
        res = {"tu": tu, "compiled": True, "pct_off": [], "raw100": [], "strict": [], "noscore": []}
        d, f = os.path.split(os.path.join(tree, tu))
        obj = os.path.join(objdir, "%d_%s.obj" % (n, os.path.splitext(f)[0]))
        if not (a.reuse_objs and os.path.exists(obj)):
            if os.path.exists(obj):
                os.remove(obj)
            drv = "vc6asm.sh" if f.lower().endswith(".asm") else "vc6cl.sh"
            subprocess.run(["bash", os.path.join(tree, "scripts/vc6", drv), "/Fo" + obj, f], cwd=d, env=env,
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        if not os.path.exists(obj):
            res["compiled"] = False
            return res
        for r in by_tu[tu]:
            c = ["--obj", obj, "--sym", r["sym"], "--addr", r["addr"], "--len", r["len"]]
            if r["status"] == "matched":
                if a.no_strict:
                    continue
                p = run([sys.executable, "scripts/vc6/raw_match.py", *c])
                q = run([sys.executable, "scripts/vc6/verify_relocations.py", *c, "--binary", os.environ["GAMEMD_BINARY"], "--json"]) if p.returncode == 0 else None
                if p.returncode != 0 or q.returncode != 0:
                    why = ("raw rc=%d " % p.returncode + (p.stdout + p.stderr)[-120:]) if p.returncode else \
                          "strict " + (q.stdout + q.stderr)[-200:]
                    res["strict"].append((r, why.replace("\n", " ").replace("\t", " ")))
            else:
                pct = partial_score.score(tree, obj, r, skips, env)
                if pct is None:
                    p = run([sys.executable, "scripts/vc6/raw_match.py", *c])
                    pct = 100.0 if p.returncode == 0 else None
                if pct is None:
                    res["noscore"].append(r)
                    continue
                if abs(pct - r.get("pct", 0)) > a.tol:
                    res["pct_off"].append((r, pct))
                if pct >= 99.95:
                    p = run([sys.executable, "scripts/vc6/raw_match.py", *c])
                    q = run([sys.executable, "scripts/vc6/verify_relocations.py", *c, "--binary",
                             os.environ["GAMEMD_BINARY"], "--json"]) if p.returncode == 0 else None
                    r = dict(r, _raw=p.returncode, _strict=(q.returncode if q else None),
                             _why=((q.stdout + q.stderr)[-160:] if q and q.returncode else "").replace("\n", " "))
                    res["raw100"].append((r, pct))
        return res

    with cf.ThreadPoolExecutor(a.jobs) as ex:
        results = list(ex.map(lambda x: one_tu(*x), enumerate(tus)))
    def w(name, rows):
        with open(os.path.join(a.out, name), "w") as fh:
            for row in rows:
                fh.write("\t".join(str(x) for x in row) + "\n")
    w("pct_off.tsv", [(r["addr"], r.get("pct"), "%.1f" % m, r["tu"], r["name"]) for x in results for r, m in x["pct_off"]])
    w("raw100_partial.tsv", [(r["addr"], r.get("pct"), "%.1f" % m, "raw=%s" % r["_raw"], "strict=%s" % r["_strict"], r["tu"], r["name"], r["_why"]) for x in results for r, m in x["raw100"]])
    w("strict_fail.tsv", [(r["addr"], r["tu"], r["name"], why) for x in results for r, why in x["strict"]])
    w("noscore.tsv", [(r["addr"], r["tu"], r["name"]) for x in results for r in x["noscore"]])
    w("compile_fail.tsv", [(x["tu"],) for x in results if not x["compiled"]])
    s = "TUs %d; pct_off %d; raw100_partial %d; strict_fail %d; noscore %d; compile_fail %d\n" % (
        len(results), sum(len(x["pct_off"]) for x in results), sum(len(x["raw100"]) for x in results),
        sum(len(x["strict"]) for x in results), sum(len(x["noscore"]) for x in results),
        sum(not x["compiled"] for x in results))
    open(os.path.join(a.out, "summary.txt"), "w").write(s)
    print(s, end="")


if __name__ == "__main__":
    main()
