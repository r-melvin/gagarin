#!/usr/bin/env python3
"""dispatch.py: refilter the worklist against the tip and write one cluster brief per TU.

    dispatch.py [--worklist CSV] [--tree WT] [--out DIR] [--min N] [--top K]

Drops rows already in the tip manifest or claimed by a body in the tree, groups the rest by
original TU (tu_id), and writes for each cluster a brief with: the migrated TU file to write
into (one TU = one file) when it exists, the canonical headers of the owning classes, the
addresses with CFG spans (not the padded worklist size), RA2-twin and family hints, and the
rules checklist. Also writes worklist_refiltered.csv and clusters.tsv (ranked by expected yield).
Deterministic; the orchestrator picks clusters and hands the brief files to workers.
"""
import argparse
import csv
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402

WORKLISTS = [os.environ.get("GAG_WORKLIST", ""), os.path.join(D.L.SCRATCH_ROOT, "worklist/worklist_live.csv"), os.path.join(D.L.SCRATCH_ROOT, "worklist/worklist.csv"),
             os.path.join(D.BACKUPS, "worklist/worklist.csv")]
RULES = """## Rules (pktlint enforces them)
- include the canonical headers listed above; never a new per-TU view of a class that has one
- write into the TU file named above when there is one (ascending address order); otherwise a new file in the module dir
- CFG-closed spans (given); no steering, no asm, no volatile on accesses; placeholder names unless the binary attests
- REA MCP primary (cite ev_ ids), ghidra CLI fallback stated; `pkt.py init/score/bind/finish`; -j4; no watch loops
"""


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--worklist")
    ap.add_argument("--tree", default=D.MAIN_REPO)
    ap.add_argument("--out")
    ap.add_argument("--min", type=int, default=5, help="minimum rows per cluster")
    ap.add_argument("--top", type=int, default=30, help="write briefs for the top K clusters")
    a = ap.parse_args(argv)
    wl = a.worklist or D.first_existing(WORKLISTS)
    if not wl:
        raise SystemExit("no worklist found (GAG_WORKLIST)")
    out = a.out or D.scratch_dir("dispatch_")
    os.makedirs(os.path.join(out, "briefs"), exist_ok=True)
    tree = D.Tree(a.tree, "HEAD")
    claims = tree.claims()
    rows = list(csv.DictReader(open(wl)))
    keep, dropped = [], {"in_manifest": 0, "claimed": 0}
    for r in rows:
        va = D.hx(r["addr"])
        if va in tree.by_addr:
            dropped["in_manifest"] += 1
        elif va in claims:
            dropped["claimed"] += 1
        else:
            keep.append(r)
    with open(os.path.join(out, "worklist_refiltered.csv"), "w") as f:
        w = csv.DictWriter(f, fieldnames=rows[0].keys())
        w.writeheader()
        w.writerows(keep)
    windows = tree.tu_windows()
    canon = tree.canonical_classes()
    clusters = {}
    for r in keep:
        clusters.setdefault(r.get("tu_id") or "?", []).append(r)
    ranked = []
    for tu, rs in clusters.items():
        if len(rs) < a.min or tu in ("?", ""):      # rows without an original TU are CRT/library thunks: LIBRARY batch, not matching
            continue
        yield_ = sum(float(r.get("p_match") or 0) for r in rs)
        ranked.append((yield_, tu, rs))
    ranked.sort(reverse=True)
    with open(os.path.join(out, "clusters.tsv"), "w") as f:
        f.write("tu_id\toriginal_tu\trows\texpected_matches\ttu_file\towning_classes\n")
        for y, tu, rs in ranked:
            dest = tree.tu_for_addr(D.hx(rs[0]["addr"]))
            f.write("%s\t%s\t%d\t%.1f\t%s\t%s\n" % (tu, rs[0].get("original_tu", ""), len(rs), y, dest or "-",
                                                   ",".join(sorted({r.get("owning_class", "") for r in rs if r.get("owning_class")}))))
    for y, tu, rs in ranked[: a.top]:
        rs.sort(key=lambda r: D.hx(r["addr"]))
        dest = tree.tu_for_addr(D.hx(rs[0]["addr"]))
        classes = sorted({r.get("owning_class", "") for r in rs if r.get("owning_class") and r["owning_class"] != "unknown"})
        hdrs = sorted({h for c in classes for h in canon.get(c, [])})
        lines = ["# Cluster %s (%s): %d functions, expected matches %.1f" % (tu, rs[0].get("original_tu", "?"), len(rs), y), ""]
        lines.append("TU file: %s" % (("**%s** (migrated; add the bodies there in address order)" % dest) if dest else "none yet (new file in the module dir of the owning class)"))
        lines.append("Owning classes: %s" % (", ".join(classes) or "unknown"))
        lines.append("Canonical headers to include: %s" % (", ".join(hdrs) or "none (placeholder views allowed; propose header members)"))
        lines.append("")
        lines.append("| addr | cfg span | worklist size | class | RA2 twin | family | hint | name hint |")
        lines.append("|---|---|---|---|---|---|---|---|")
        for r in rs:
            va = D.hx(r["addr"])
            try:
                span, _ = D.cfg_span(va)
            except (Exception, SystemExit):
                span = 0
            lines.append("| 0x%X | 0x%x | %s | %s | %s | %s | %s | %s |" % (
                va, span, r.get("size", ""), r.get("owning_class", ""), r.get("ra2_twin", ""), r.get("family_size", ""),
                r.get("difficulty_hint", ""), r.get("attested_name") or r.get("unattested_hint") or ""))
        lines += ["", RULES]
        open(os.path.join(out, "briefs", "cluster_%s.md" % tu), "w").write("\n".join(lines) + "\n")
    print("worklist %s: %d rows, dropped %s, kept %d; %d clusters >= %d rows; briefs for top %d in %s" % (
        wl, len(rows), dropped, len(keep), len(ranked), a.min, min(a.top, len(ranked)), os.path.join(out, "briefs")))
    for y, tu, rs in ranked[:12]:
        print("  %-6s %4d rows  expected %.1f  %s" % (tu, len(rs), y, tree.tu_for_addr(D.hx(rs[0]["addr"])) or "-"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
