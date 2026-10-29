#!/usr/bin/env python3
"""flagsweep.py: compiler-flag sweep over every TU that holds partial rows, as a proposal packet.

    flagsweep.py [--tree WT] [--tu PATH ...] [--limit N] [--out DIR] [--jobs 4]

Drives ../cheap-near/flagprobe.py (variants: /Ob none|1|2, /Op toggled) on each TU with at least
one partial row. A variant is PROPOSED for a TU only if no row's score drops (matched rows must
stay 100) and at least one partial rises. Output in --out:
  sweep.jsonl        flagprobe's raw per-TU results
  report.md          per TU: current flags, best variant, rows up (old -> new), rows down
  proposals.json     [{tu, flags, up: {addr: [old, new]}}] (the lander's decision list)
  patch.diff         the VC6FLAGS marker edits for the proposed TUs (one line each, with the
                     reason comment AGENTS.md asks for), and manifest_delta.json with the new pct
                     values (status unchanged: a row that reaches 100 is listed for promotion but
                     promoted only after raw+strict in a packet; `pkt.py bind` does that).
Deterministic, no model; the oracle is diff_retail/raw_match as everywhere else.
"""
import argparse
import concurrent.futures as cf
import json
import os
import re
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402

PROBE = os.path.join(D.TOOLS, "cheap-near", "flagprobe.py")
DEFAULT = "/nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2"   # scripts/vc6/vc6cl.sh


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=D.MAIN_REPO)
    ap.add_argument("--tu", action="append", default=[])
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--out")
    ap.add_argument("--jobs", type=int, default=D.MAX_JOBS)
    a = ap.parse_args(argv)
    out = a.out or D.scratch_dir("flagsweep_")
    os.makedirs(out, exist_ok=True)
    man = json.load(open(os.path.join(a.tree, D.MANIFEST)))
    by_tu = {}
    for r in man:
        by_tu.setdefault(r["tu"], []).append(r)
    tus = a.tu or sorted(t for t, rows in by_tu.items() if any(r["status"] != "matched" for r in rows))
    if a.limit:
        tus = tus[:a.limit]
    t0 = time.time()
    env = dict(L.toolenv(), TMPDIR=out)          # flagprobe's mkdtemp lands on disk, not /tmp
    results = []

    def one(tu):
        jl = os.path.join(out, "sweep-%s.jsonl" % tu.replace("/", "__"))
        if os.path.exists(jl):
            os.unlink(jl)
        subprocess.run([sys.executable, PROBE, "--tree", a.tree, "--tu", tu, "--out", jl], env=env, capture_output=True, text=True)
        return [json.loads(l) for l in open(jl)] if os.path.isfile(jl) else [{"tu": tu, "error": "probe failed"}]

    with cf.ThreadPoolExecutor(max(1, min(a.jobs, 4) // 2)) as ex:   # each probe compiles up to 4 variants
        for res in ex.map(one, tus):
            results += res
    with open(os.path.join(out, "sweep.jsonl"), "w") as f:
        for r in results:
            f.write(json.dumps(r) + "\n")
    proposals, lines = [], ["# flag sweep on %s (%d TUs with partials, %.0fs)" % (a.tree, len(tus), time.time() - t0), ""]
    for r in results:
        if "error" in r:
            lines.append("- %s: %s" % (r["tu"], r["error"]))
            continue
        best = None
        for vn, v in r["variants"].items():
            if "error" in v or not v["up"] or v["down"]:
                continue
            gain = sum(nv - (ov or 0) for ov, nv in v["up"].values())
            if best is None or gain > best[0]:
                best = (gain, vn, v)
        if best:
            gain, vn, v = best
            proposals.append(dict(tu=r["tu"], cur=r["cur"], flags=v["flags"], up=v["up"], gain=round(gain, 1)))
            lines.append("- **%s**: %s -> `%s` (%s): %d rows up, gain %.1f: %s" % (
                r["tu"], r["cur"], v["flags"], vn, len(v["up"]), gain,
                ", ".join("%s %s->%s" % (k, ov, nv) for k, (ov, nv) in sorted(v["up"].items()))))
        else:
            tried = ", ".join("%s(%s)" % (vn, "err" if "error" in v else "%d up/%d down" % (len(v["up"]), len(v["down"]))) for vn, v in r["variants"].items())
            lines.append("- %s: no variant helps without a drop (%s)" % (r["tu"], tried))
    open(os.path.join(out, "report.md"), "w").write("\n".join(lines) + "\n")
    json.dump(proposals, open(os.path.join(out, "proposals.json"), "w"), indent=1)
    # VC6FLAGS edits + pct delta
    patch, delta = [], []
    for p in proposals:
        path = os.path.join(a.tree, p["tu"])
        src = open(path, errors="replace").read()
        new_flags = " ".join(x for x in DEFAULT.split()) + "".join(" " + x for x in p["flags"].split() if x not in DEFAULT.split())
        marker = "// VC6FLAGS: %s  -- flag sweep: %d partial rows rise with no row dropping (flagsweep.py)" % (new_flags, len(p["up"]))
        if re.search(r"(?m)^\s*//\s*VC6FLAGS:.*$", src):
            new = re.sub(r"(?m)^\s*//\s*VC6FLAGS:.*$", marker, src, count=1)
        else:
            lines_ = src.split("\n")
            i = 0
            while i < len(lines_) and lines_[i].startswith("//"):
                i += 1
            new = "\n".join(lines_[:i] + [marker] + lines_[i:])
        tmpdir = os.path.join(out, "edit")
        os.makedirs(os.path.join(tmpdir, os.path.dirname(p["tu"])), exist_ok=True)
        open(os.path.join(tmpdir, p["tu"]), "w").write(new)
        d = subprocess.run(["git", "diff", "--no-index", "--", path, os.path.join(tmpdir, p["tu"])], capture_output=True, text=True).stdout
        d = d.replace("a" + path, "a/" + p["tu"]).replace("b" + os.path.join(tmpdir, p["tu"]), "b/" + p["tu"])
        d = re.sub(r"(?m)^(--- |\+\+\+ )(.*)$", lambda m: m.group(1) + ("a/" if m.group(1).startswith("---") else "b/") + p["tu"], d)
        patch.append(d)
        for addr, (ov, nv) in p["up"].items():
            row = dict(next(r for r in by_tu[p["tu"]] if r["addr"].lower() == addr.lower()))
            row["pct"] = nv
            row["op"] = "change"
            delta.append(row)
    open(os.path.join(out, "patch.diff"), "w").write("".join(patch))
    delta.sort(key=lambda r: D.hx(r["addr"]))
    json.dump(delta, open(os.path.join(out, "manifest_delta.json"), "w"), indent=1)
    print("\n".join(lines[:40]))
    print("%d proposals; %s" % (len(proposals), out))
    return 0


if __name__ == "__main__":
    sys.exit(main())
