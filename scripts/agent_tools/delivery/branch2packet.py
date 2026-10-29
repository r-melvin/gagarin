#!/usr/bin/env python3
# Provenance: original. Packet assembly for branch-style workers.
"""branch2packet.py: turn a worker branch plus a rows JSON into a READY packet.

    branch2packet.py BRANCH --rows rows.json [--removed removed.json] [--out DIR] [--onto REV]
                     [--repo REPO] [--message-file F] [--evidence TEXT_OR_FILE] [--lint]

Workers that commit on a branch instead of using pkt.py still have to hand the lander a READY
directory. This builds it with git plumbing only (no checkout, no worktree, nothing in REPO changes):

  patch.diff           git diff --binary MERGE_BASE BRANCH over the allowed paths; the manifest, STATUS.md and
                       progress.svg are left out (the delta is authoritative, the lander regenerates the others).
                       Hunks on scripts/data/symbol_bindings.json stay in: the lander reads them as binding additions.
  manifest_delta.json  rows.json sorted by address, each with an op decided against the manifest at MERGE_BASE:
                       absent -> add, present and different -> change (old symbol recorded), identical -> dropped
                       with a note. removed.json (rows or bare addresses) -> remove ops carrying the base row.
  base_sha, README.md  the merge base; the commit message (the branch tip's, or --message-file) in a
                       'Proposed commit message' block; --evidence text (REA Evidence IDs, or the tool used).

rows.json is a list of manifest rows (addr, tu, sym, len, name, status, pct; addr and len may be ints),
or {"rows": [...]}. MERGE_BASE is the merge base of BRANCH and --onto (default HEAD of REPO).
--lint runs pktlint on the result against MERGE_BASE. Exit 1 on inconsistent input.
"""
import argparse
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402

EXCLUDE = (D.MANIFEST, "STATUS.md", ".github/assets/progress.svg")


def hexrow(r):
    r = dict(r)
    if isinstance(r.get("addr"), int):
        r["addr"] = "0x%X" % r["addr"]
    if isinstance(r.get("len"), int):
        r["len"] = "0x%x" % r["len"]
    return r


def addr_of(x):
    if isinstance(x, dict):
        x = x["addr"]
    return x if isinstance(x, int) else int(x, 16)


def load_rows(path):
    d = json.load(open(path))
    if isinstance(d, dict):
        d = d.get("rows", d.get("add", []))
    return d


def build_delta(base_manifest, rows, removed):
    """-> (delta list sorted by address, notes, errors)."""
    base = {addr_of(r): r for r in base_manifest}
    notes, errs, out = [], [], []
    seen = set()
    for r in rows:
        r = hexrow(r)
        for need in ("addr", "tu", "sym", "len", "status"):
            if need not in r:
                errs.append("row %r lacks %s" % (r.get("addr"), need))
        if errs and errs[-1].startswith("row %r" % r.get("addr")):
            continue
        a = addr_of(r)
        if a in seen:
            errs.append("address 0x%X twice in rows" % a)
            continue
        seen.add(a)
        if r["status"] == "matched" and float(r.get("pct", 100)) != 100:
            errs.append("row 0x%X is matched with pct %s" % (a, r.get("pct")))
        row = {k: v for k, v in r.items() if k not in ("op", "old") and not k.startswith("_")}
        if a not in base:
            out.append(dict(row, op="add"))
        elif {k: v for k, v in base[a].items()} == row:
            notes.append("0x%X identical to the base manifest row: dropped" % a)
        else:
            out.append(dict(row, op="change", old={"sym": base[a]["sym"]}))
    for x in removed:
        a = addr_of(x)
        if a not in base:
            errs.append("removed address 0x%X is not in the base manifest" % a)
        elif a in seen:
            errs.append("address 0x%X is both in rows and removed" % a)
        else:
            out.append(dict(base[a], op="remove"))
    out.sort(key=addr_of)
    return out, notes, errs


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("branch")
    ap.add_argument("--rows", required=True)
    ap.add_argument("--removed")
    ap.add_argument("--out", help="packet directory (READY is appended unless the name is READY); default <scratch>/<branch>/READY")
    ap.add_argument("--onto", default="HEAD", help="revision of --repo the merge base is taken against (default HEAD)")
    ap.add_argument("--repo", default=D.MAIN_REPO)
    ap.add_argument("--message-file")
    ap.add_argument("--evidence", help="text, or a file whose text goes into the README (REA Evidence IDs / tool statement)")
    ap.add_argument("--lint", action="store_true")
    a = ap.parse_args(argv)

    repo = a.repo
    tip = L.rev_parse(repo, a.branch)
    onto = L.rev_parse(repo, a.onto)
    base = L.git(repo, "merge-base", tip, onto).strip()
    out = a.out or os.path.join(D.SCRATCH, "b2p-" + re.sub(r"[^\w.-]+", "_", a.branch))
    if os.path.basename(os.path.normpath(out)) != "READY":
        out = os.path.join(out, "READY")
    os.makedirs(out, exist_ok=True)

    try:
        base_manifest = json.loads(L.git(repo, "show", "%s:%s" % (base, D.MANIFEST)))
    except Exception as ex:
        print("cannot read the manifest at %s: %s" % (base[:10], ex), file=sys.stderr)
        return 1
    rows = load_rows(a.rows)
    removed = load_rows(a.removed) if a.removed else []
    delta, notes, errs = build_delta(base_manifest, rows, removed)

    changed = set(L.git(repo, "diff", "--name-only", base, tip).split("\n")) - {""}
    patch = L.git(repo, "diff", "--binary", base, tip, "--", ".", *[":(exclude)%s" % x for x in EXCLUDE])
    in_patch = {m.group(1) for m in re.finditer(r"^diff --git a/\S+ b/(\S+)", patch, re.M)}
    for r in delta:
        if r["op"] != "remove" and r["tu"] not in in_patch and not os.path.basename(r["tu"]).startswith("_"):
            notes.append("row %s names %s, which the branch does not change relative to %s (pktlint will flag it)" % (r["addr"], r["tu"], base[:10]))
    for x in sorted(changed & set(EXCLUDE)):
        notes.append("%s changed on the branch: left out of patch.diff" % x)
    if errs:
        for e in errs:
            print("ERROR", e, file=sys.stderr)
        return 1

    open(os.path.join(out, "patch.diff"), "w").write(patch)
    json.dump(delta, open(os.path.join(out, "manifest_delta.json"), "w"), indent=1)
    open(os.path.join(out, "base_sha"), "w").write(base + "\n")
    msg = open(a.message_file).read().strip() if a.message_file else L.git(repo, "log", "-1", "--format=%B", tip).strip()
    evidence = a.evidence or "(none recorded: add the RE tool's evidence IDs, or state the tool used)"
    if os.path.isfile(evidence):
        evidence = open(evidence).read().strip()
    nadd = sum(r["op"] == "add" for r in delta)
    nchg = sum(r["op"] == "change" for r in delta)
    nrem = sum(r["op"] == "remove" for r in delta)
    nex = sum(r.get("status") == "matched" and r["op"] != "remove" for r in delta)
    open(os.path.join(out, "README.md"), "w").write("""# %s READY packet (from branch %s)

Base: %s. Branch tip %s. Delta: %d add, %d change, %d remove (%d matched). Built by branch2packet.py.

## Evidence
%s

## Notes
%s

## Proposed commit message
```
%s
```
""" % (re.sub(r"[^\w.-]+", "_", a.branch), a.branch, base, tip[:10], nadd, nchg, nrem, nex, evidence,
       "\n".join("- " + n for n in notes) or "- none", msg))
    with open(os.path.join(out, "results.tsv"), "w") as f:
        f.write("addr\tsymbol\t%\tstatus\ttu\n")
        for r in delta:
            if r["op"] != "remove":
                f.write("%s\t%s\t%s\t%s\t%s\n" % (r["addr"], r["sym"], r.get("pct", ""), "exact" if r["status"] == "matched" else "partial", r["tu"]))
    print("packet %s: base %s, %d files in patch, delta %d add / %d change / %d remove" % (out, base[:10], len(in_patch), nadd, nchg, nrem))
    for n in notes:
        print("note:", n)
    if a.lint:
        return subprocess.run([sys.executable, os.path.join(os.path.dirname(os.path.abspath(__file__)), "pktlint.py"), out,
                               "--repo", repo, "--rev", base]).returncode
    return 0


if __name__ == "__main__":
    sys.exit(main())
