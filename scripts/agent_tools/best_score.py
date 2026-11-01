#!/usr/bin/env python3
# Provenance: original.
"""best_score.py - stamp best_pct / best_at on the manifest's partial rows.

A partial row keeps its current score (pct) and the highest score ever recorded (best_pct), with best_at
naming where it was measured: a commit sha, plus 'attempts:<date>:<agent>' when the attempts ledger is the
source. best only rises. Matched rows are 100 and carry neither.

  best_score.py backfill [--ledger FILE] [--at SHA] [--manifest M] [--dry-run]
      best_pct = max(pct, existing best_pct, best ledger score for the address (attempts.py best), only below 100,
      since a 100 on a still-partial row is a structural gap, not a score). best_at = SHA (default: HEAD, 8
      chars) unless the ledger supplies the best.
"""
import argparse
import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(HERE, "land"))
sys.path.insert(0, HERE)
import landlib as L  # noqa: E402
import attempts  # noqa: E402


def ledger_best(path):
    """addr (int) -> (raw, 'attempts:<date>:<agent>') for the highest sub-100 raw score in the ledger."""
    best = {}
    if not path or not os.path.exists(path):
        return best
    for line in open(path):
        if not line.strip():
            continue
        r = json.loads(line)
        raw = r.get("raw")
        if not isinstance(raw, (int, float)) or raw >= 100:
            continue
        a = int(r["addr"], 16)
        if a not in best or raw > best[a][0]:
            best[a] = (raw, "attempts:%s:%s" % (r.get("date", "?"), r.get("agent", "?")))
    return best


def backfill(man, ledger, at):
    """Stamp every partial row in place; returns (rows_stamped, rows_raised_by_ledger)."""
    stamped = raised = 0
    for i, r in enumerate(man):
        if r.get("status") != "partial" or not isinstance(r.get("pct"), (int, float)):
            continue
        prior = r.get("best_pct", r["pct"])
        best, where = max(prior, r["pct"]), r.get("best_at") or at
        led = ledger.get(int(r["addr"], 16))
        if led and led[0] > best:
            best, where = led[0], "%s %s" % (at, led[1])
            raised += 1
        r = dict(r, best_pct=best, best_at=where)
        man[i] = L.stamp_best(None, r)          # key order: best_* directly after pct
        stamped += 1
    return stamped, raised


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    b = sub.add_parser("backfill")
    b.add_argument("--manifest", default=os.path.join(ROOT, L.MANIFEST))
    b.add_argument("--ledger", default=str(attempts.LEDGER), help="default: the attempts.py ledger")
    b.add_argument("--at", default=None, help="sha best_at names (default: HEAD, 8 chars)")
    b.add_argument("--dry-run", action="store_true")
    a = ap.parse_args(argv)
    at = a.at or subprocess.run(["git", "-C", ROOT, "rev-parse", "--short=8", "HEAD"], capture_output=True, text=True).stdout.strip()
    man, _ = L.load_manifest(a.manifest)
    n, raised = backfill(man, ledger_best(a.ledger), at)
    print("%d partial rows stamped, %d raised above pct by the ledger (best_at %s)" % (n, raised, at))
    if not a.dry_run:
        open(a.manifest, "w").write(L.dump_manifest(man))
    return 0


if __name__ == "__main__":
    sys.exit(main())
