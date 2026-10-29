#!/usr/bin/env python3
"""prove_rebase.py: compare what pktrebase produces with what the landers committed.

    prove_rebase.py [--cases NAME=PACKET_DIR=LANDED_SHA ...]

For each case the packet is rebased onto LANDED_SHA^ (the tree the lander had) with --keep,
the result's index is written as a tree and compared with the landed commit:
  files    tracked match/ files identical / differing / only on one side (STATUS.md, progress.svg ignored)
  rows     manifest rows the packet adds or changes: same address set, and per row the same
           tu/len/status; symbols that differ are listed (lander re-keys)
  order    for merged TU files: the sequence of body claims in the tool's file vs the landed file
  bytes    (clean cases) every packet row raw_match's in the tool's tree (pktrebase proved it)
Prints one line per case and a JSON report.
"""
import argparse
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402

B = D.BACKUPS
DEFAULT = [
    "fablefix=%s/land-b6/fablefix/READY=0487575" % B,
    "nearmiss=%s/w5-nearmiss/READY=db75843" % B,
    "tu288=%s/w6-tu288/READY=a4d5e26" % B,
    "tu171=%s/w6-tu171/READY=636fc6b" % B,
    "tu099=%s/w6-tu099/READY=ffbc8eb" % B,
    "tu180=%s/w6-tu180/READY=5dca46c" % B,
]


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--cases", nargs="*", default=DEFAULT)
    ap.add_argument("--repo", default=D.MAIN_REPO)
    a = ap.parse_args(argv)
    out = {}
    for case in a.cases:
        name, pdir, sha = case.split("=")
        landed = L.rev_parse(a.repo, sha)
        parent = L.rev_parse(a.repo, sha + "^")
        od = os.path.join(D.SCRATCH, "prove_rebase", name)
        r = subprocess.run([sys.executable, os.path.join(os.path.dirname(HERE), "pktrebase.py"), pdir, "--repo", a.repo, "--rev", parent,
                            "--out", od, "--gates", "none", "--keep"], capture_output=True, text=True)
        rep = json.load(open(os.path.join(od, "report.json")))
        wt = re.search(r"kept worktree (\S+)", r.stdout).group(1)
        try:
            tree = L.git(wt, "write-tree").strip()
            # files
            diff = L.git(a.repo, "diff", "--name-status", "--no-renames", tree, landed).splitlines()
            fd = {}
            for ln in diff:
                st, path = ln.split("\t", 1)
                if path in ("STATUS.md", ".github/assets/progress.svg", D.MANIFEST):
                    continue
                fd.setdefault(st, []).append(path)
            touched = {d.path for d in D.split_patch(open(os.path.join(od, "patch.diff")).read())}
            ident = sorted(p for p in touched if p not in {x for v in fd.values() for x in v})
            # rows
            lm = {D.hx(r_["addr"]): r_ for r_ in json.loads(L.git(a.repo, "show", "%s:%s" % (landed, D.MANIFEST)))}
            pm = {D.hx(r_["addr"]): r_ for r_ in json.loads(L.git(a.repo, "show", "%s:%s" % (parent, D.MANIFEST)))}
            landed_rows = {k: v for k, v in lm.items() if k not in pm or pm[k] != v}
            tool_rows = {D.hx(r_["addr"]): r_ for r_ in json.load(open(os.path.join(od, "manifest_delta.json")))}
            same_set = set(landed_rows) == set(tool_rows)
            per_row = dict(tu_len_status_equal=0, sym_differs=[], other_differs=[])
            for k in sorted(set(landed_rows) & set(tool_rows)):
                lr, tr = landed_rows[k], tool_rows[k]
                if (lr["tu"], D.hx(lr["len"]), lr["status"]) == (tr["tu"], D.hx(tr["len"]), tr["status"]):
                    per_row["tu_len_status_equal"] += 1
                else:
                    per_row["other_differs"].append(dict(addr=lr["addr"], landed=(lr["tu"], lr["len"], lr["status"]), tool=(tr["tu"], tr["len"], tr["status"])))
                if lr["sym"] != tr["sym"]:
                    per_row["sym_differs"].append(dict(addr=lr["addr"], landed=lr["sym"], tool=tr["sym"]))
            # order in merged TUs
            order = {}
            for m in rep.get("merged", []):
                lt = L.git(a.repo, "show", "%s:%s" % (landed, m["dest"]))
                tt = open(os.path.join(wt, m["dest"])).read()
                lo, to = D.rows_in_order(lt), D.rows_in_order(tt)
                order[m["dest"]] = dict(landed_claims=len(lo), tool_claims=len(to), same_sequence=lo == to,
                                        same_set=set(lo) == set(to), only_landed=["0x%X" % x for x in sorted(set(lo) - set(to))][:8],
                                        only_tool=["0x%X" % x for x in sorted(set(to) - set(lo))][:8],
                                        tool_ascending=to == sorted(to), landed_ascending=lo == sorted(lo))
            out[name] = dict(ok=rep["ok"], conflicts=len(rep["conflicts"]), proved_rows=rep.get("proved_rows"), secs=rep["secs"].get("total"),
                             files_identical=len(ident), files_differ=fd, rows_same_set=same_set,
                             rows_only_landed=["0x%X" % k for k in sorted(set(landed_rows) - set(tool_rows))][:10],
                             rows_only_tool=["0x%X" % k for k in sorted(set(tool_rows) - set(landed_rows))][:10],
                             per_row=per_row, merged_order=order, unify_notes=[n for n in rep["notes"] if n.startswith("unify")][:20])
            print("%-9s ok=%s conflicts=%d proved=%s files: %d identical, %s; rows same set=%s (%d equal tu/len/status, %d sym differ, %d other); order=%s" % (
                name, rep["ok"], len(rep["conflicts"]), rep.get("proved_rows"), len(ident),
                {k: len(v) for k, v in fd.items()}, same_set, per_row["tu_len_status_equal"], len(per_row["sym_differs"]), len(per_row["other_differs"]),
                {os.path.basename(k): (v["same_sequence"], v["same_set"], v["tool_ascending"]) for k, v in order.items()}))
        finally:
            D.remove_worktree(a.repo, wt)   # pktrebase --keep registered it
    json.dump(out, open(os.path.join(D.SCRATCH, "prove_rebase", "report.json"), "w"), indent=1)
    print("report", os.path.join(D.SCRATCH, "prove_rebase", "report.json"))


if __name__ == "__main__":
    sys.exit(main())
