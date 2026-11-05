#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; reads only partial_triage.py output.
"""residual_signatures.py: group partial rows by the shape of what differs from retail.

    residual_signatures.py TRIAGE_DIR [--top N] [--max-hunk M] [--tsv OUT]

Aligns the mnemonic streams in TRIAGE_DIR/streams/*.json and reduces each differing hunk to
`retail mnemonics => compiled mnemonics`. Signatures shared by many rows are candidates for one
codegen rule instead of per-function work. Report only: decides no binary fact.
"""
import argparse, collections, csv, difflib, glob, json, os


def mnem(i):
    return i[2]     # stream rows are [offset, hex bytes, mnemonic, operands]


def signatures(retail, comp, max_hunk=6):
    a, b = [mnem(x) for x in retail], [mnem(x) for x in comp]
    out = set()
    for tag, i0, i1, j0, j1 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if tag != "equal" and i1 - i0 <= max_hunk and j1 - j0 <= max_hunk:
            out.add("%s => %s" % (" ".join(a[i0:i1]) or "-", " ".join(b[j0:j1]) or "-"))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("triage_dir")
    ap.add_argument("--top", type=int, default=30)
    ap.add_argument("--max-hunk", type=int, default=6)
    ap.add_argument("--tsv")
    a = ap.parse_args(argv)
    rows = collections.defaultdict(list)
    n = 0
    for f in glob.glob(os.path.join(a.triage_dir, "streams", "*.json")):
        d = json.load(open(f))
        n += 1
        for s in signatures(d["retail"], d["comp"], a.max_hunk):
            rows[s].append(os.path.basename(f)[:-5])
    ranked = sorted(rows.items(), key=lambda kv: -len(kv[1]))
    print("%d rows, %d signatures" % (n, len(ranked)))
    for s, r in ranked[: a.top]:
        print("%4d  %s   e.g. %s" % (len(r), s, " ".join(sorted(r)[:3])))
    if a.tsv:
        with open(a.tsv, "w", newline="") as f:
            w = csv.writer(f, delimiter="\t")
            w.writerow(["rows", "signature", "addrs"])
            for s, r in ranked:
                w.writerow([len(r), s, " ".join(sorted(r))])


if __name__ == "__main__":
    main()
