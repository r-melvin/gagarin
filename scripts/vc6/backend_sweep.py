#!/usr/bin/env python3
"""backend_sweep.py: compile every TU with alternative c2.dll code generators and score every manifest row.

Retail's Rich header lists 513 C++ objects stamped build 8447 and 12 stamped build 8168 (RTM).
@comp.id is stamped by c2.dll, so the 12 were compiled with an RTM backend. This tool finds the TUs
whose rows behave like that: compile each TU with the pinned 8447 toolchain (the control) and with
each alternative backend, then compare per manifest row.

    backend_sweep.py setup                      # build the overlays (idempotent)
    backend_sweep.py stamps                     # compile a trivial object per backend, print @comp.id
    backend_sweep.py run [--backend 8168 ...] [--tu match/x.cpp ...] [--limit N] [--jobs 4] [--out DIR]
    backend_sweep.py report --out DIR [--backend 8168]   # ranked candidates from DIR/results.jsonl

Overlays live in <main>/toolchain/backends/<name>/MSVC600 (ignored, never committed): VC98/Bin is a
real copy of the pinned Bin's regular files with c2.dll replaced; every other directory is a symlink
to the pinned install. The pinned toolchain/MSVC600 is never modified; the overlay is reached only
through vc6cl.sh's VC6_ROOT, which this tool sets for the alternative compiles. Gates are unaffected.

Per row, the class under a backend is:
  same     the row's COMDAT section (bytes + relocations) is identical to the control build
  up/down  the section differs and the diff_retail/raw_match score rises/falls vs the control score
  flat     the section differs but the score is unchanged
A candidate RTM TU: no matched row falls, at least one partial rises, and the compile succeeded.
Rows are scored with the same oracle as cheap-near/flagprobe.py. Needs GAMEMD_BINARY for scoring.
"""
import argparse
import concurrent.futures as cf
import json
import os
import shutil
import struct
import subprocess
import sys
import tempfile
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, os.path.join(REPO, "scripts", "agent_tools", "land"))
from sectioncmp import coff  # noqa: E402

MAIN = os.environ.get("GAG_MAIN", "/home/richard/Projects/gagarin")
PINNED = os.path.join(MAIN, "toolchain", "MSVC600")
BACKENDS_DIR = os.path.join(MAIN, "toolchain", "backends")
MEDIA = "/home/richard/Projects/gagarin-scratch/tmp-archive-20261022/gagarin-vc6-media-review"
# name -> c2.dll source. 8447 is the control through the pinned toolchain; its overlay is only a check.
SOURCES = {
    "8168": os.path.join(MEDIA, "base/VC98/BIN/C2.DLL"),               # VC6 RTM base install
    "9044": os.path.join(PINNED, "VC98/Bin/c2.dll.sp3bak"),            # Processor Pack backend
    "8447": os.path.join(PINNED, "VC98/Bin/c2.dll"),
}
MANIFEST = os.path.join(REPO, "scripts/data/match_manifest.json")
MAX_JOBS = 4


def overlay_root(name):
    return os.path.join(BACKENDS_DIR, name, "MSVC600")


def setup(names):
    for n in names:
        src = SOURCES[n]
        if not os.path.isfile(src):
            print("setup: missing c2.dll for %s: %s" % (n, src), file=sys.stderr)
            continue
        root = overlay_root(n)
        os.makedirs(os.path.join(root, "VC98", "Bin"), exist_ok=True)
        for top in os.listdir(PINNED):
            if top == "VC98":
                continue
            dst = os.path.join(root, top)
            if not os.path.lexists(dst):
                os.symlink(os.path.join(PINNED, top), dst)
        for sub in os.listdir(os.path.join(PINNED, "VC98")):
            if sub == "Bin":
                continue
            dst = os.path.join(root, "VC98", sub)
            if not os.path.lexists(dst):
                os.symlink(os.path.join(PINNED, "VC98", sub), dst)
        pb = os.path.join(PINNED, "VC98", "Bin")
        ob = os.path.join(root, "VC98", "Bin")
        for f in os.listdir(pb):
            p = os.path.join(pb, f)
            if os.path.isfile(p) and not os.path.islink(p) and not f.lower().startswith("c2.dll"):
                if not os.path.exists(os.path.join(ob, f)):
                    shutil.copyfile(p, os.path.join(ob, f))
        shutil.copyfile(src, os.path.join(ob, "c2.dll"))
        print("overlay %s: %s" % (n, root))


def comp_ids(obj):
    """Every @comp.id value in the object's symbol table (usually one)."""
    d = open(obj, "rb").read()
    symoff, nsym = struct.unpack_from("<II", d, 8)
    strtab = symoff + nsym * 18
    out, i = [], 0
    while i < nsym:
        raw = d[symoff + i * 18: symoff + i * 18 + 18]
        if raw[:4] == b"\0\0\0\0":
            o = struct.unpack_from("<I", raw, 4)[0]
            n = d[strtab + o:d.index(b"\0", strtab + o)]
        else:
            n = raw[:8].rstrip(b"\0")
        aux = raw[17]
        if n == b"@comp.id":
            out.append(struct.unpack_from("<I", raw, 8)[0])
        i += 1 + aux
    return out


def fmt_id(v):
    return "0x%08x(prod %#x build %d)" % (v, v >> 16, v & 0xffff)


def compile_tu(tu, obj, root=None):
    env = dict(os.environ)
    if root:
        env["VC6_ROOT"] = root
    else:
        env.pop("VC6_ROOT", None)
    env.pop("VC6_FLAGS", None)
    if os.path.exists(obj):
        os.remove(obj)
    r = subprocess.run(["bash", os.path.join(REPO, "scripts/vc6/vc6cl.sh"), "/Fo" + obj, os.path.basename(tu)],
                       cwd=os.path.join(REPO, os.path.dirname(tu)), env=env,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return r.returncode == 0 and os.path.exists(obj)


def score(obj, e):
    last = ""
    for tool in ("raw_match.py", "diff_retail.py"):
        r = subprocess.run([sys.executable, os.path.join(REPO, "scripts/vc6", tool), "--obj", obj, "--sym", e["sym"],
                            "--addr", e["addr"], "--len", e["len"]], capture_output=True, text=True)
        if r.returncode == 0 and "100.0%" in r.stdout:
            return 100.0
        last = r.stdout
    for l in last.splitlines():
        if l.startswith("match:"):
            try:
                return float(l.split()[-1].rstrip("%"))
            except ValueError:
                pass
    return None


def secs(obj):
    d = {}
    for k, v in coff(obj).items():
        if "|" in k:
            d.setdefault(k.split("|", 1)[1].split("#")[0], []).append(v)
    return d


def stamps(names):
    tmp = tempfile.mkdtemp(prefix="bsweep_stamp_")
    src = os.path.join(tmp, "t.cpp")
    open(src, "w").write("int f(int a){return a*3+1;}\n")
    res = {}
    for n in ["pinned"] + names:
        obj = os.path.join(tmp, n + ".obj")
        env = dict(os.environ)
        env.pop("VC6_FLAGS", None)
        if n != "pinned":
            env["VC6_ROOT"] = overlay_root(n)
        else:
            env.pop("VC6_ROOT", None)
        # vc6cl treats an absolute argument as a flag, so pass the source by name from its own directory.
        subprocess.run(["bash", os.path.join(REPO, "scripts/vc6/vc6cl.sh"), "/Fo" + obj, "t.cpp"], cwd=tmp, env=env,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        res[n] = [fmt_id(v) for v in comp_ids(obj)] if os.path.exists(obj) else ["COMPILE FAIL"]
        print("%-8s %s" % (n, ", ".join(res[n])))
    shutil.rmtree(tmp, True)
    return res


def sweep_one(tu, rows, backends, tmpd):
    base = os.path.join(tmpd, "ctl.obj")
    rec = {"tu": tu, "nrows": len(rows), "backends": {}}
    if not compile_tu(tu, base):
        rec["error"] = "control compile failed"
        return rec
    rec["control_comp_id"] = [fmt_id(v) for v in comp_ids(base)]
    bs = secs(base)
    bscore = {}
    for n in backends:
        obj = os.path.join(tmpd, n + ".obj")
        if not compile_tu(tu, obj, overlay_root(n)):
            rec["backends"][n] = {"error": "compile failed"}
            continue
        vs = secs(obj)
        res = {"comp_id": [fmt_id(v) for v in comp_ids(obj)], "rows": {}}
        for e in rows:
            a = e["addr"]
            # Static initialisers (_$E..) are local symbols, so their sections are keyed "" : compare that bucket.
            key = e["sym"] if e["sym"] in bs else ""
            if bs.get(key) is None and vs.get(key) is None:
                res["rows"][a] = ["nosec", e["status"], None, None]   # nothing emitted by either build
                continue
            if bs.get(key) == vs.get(key):
                res["rows"][a] = ["same", e["status"], None, None]
                continue
            if a not in bscore:
                bscore[a] = score(base, e)
            ns = score(obj, e)
            o = bscore[a] or 0
            nv = ns or 0
            cls = "up" if nv > o else "down" if nv < o else "flat"
            res["rows"][a] = [cls, e["status"], bscore[a], ns]
        rec["backends"][n] = res
        os.remove(obj)
    os.remove(base)
    return rec


def run(a):
    man = json.load(open(MANIFEST))
    by_tu = {}
    for r in man:
        by_tu.setdefault(r["tu"], []).append(r)
    tus = a.tu or sorted(by_tu)
    if a.limit:
        tus = tus[:a.limit]
    out = a.out or os.path.join("/home/richard/Projects/gagarin-scratch", "backend_sweep_%d" % int(time.time()))
    os.makedirs(os.path.join(out, "tmp"), exist_ok=True)
    resf = os.path.join(out, "results.jsonl")
    done = set()
    if os.path.isfile(resf):
        for l in open(resf):
            try:
                if "error" not in json.loads(l):
                    done.add(json.loads(l)["tu"])
            except Exception:
                pass
    todo = [t for t in tus if t not in done]
    print("%d TUs, %d to do, backends %s, out %s" % (len(tus), len(todo), a.backend, out), flush=True)
    t0 = time.time()

    def one(tu):
        tmpd = tempfile.mkdtemp(prefix="w_", dir=os.path.join(out, "tmp"))
        try:
            return sweep_one(tu, by_tu[tu], a.backend, tmpd)
        except Exception as ex:  # keep the sweep alive; the TU is retried on the next run
            return {"tu": tu, "error": "exception: %r" % (ex,)}
        finally:
            shutil.rmtree(tmpd, True)

    with open(resf, "a") as f, cf.ThreadPoolExecutor(min(a.jobs, MAX_JOBS)) as ex:
        for i, rec in enumerate(ex.map(one, todo), 1):
            f.write(json.dumps(rec) + "\n")
            f.flush()
            if i % 25 == 0:
                print("%d/%d  %.0fs" % (i, len(todo), time.time() - t0), flush=True)
    print("done %.0fs" % (time.time() - t0))
    a.out = out
    report(a)


def summarize(rec, backend):
    b = rec.get("backends", {}).get(backend)
    if not b or "error" in b:
        return None
    s = dict(matched_same=0, matched_down=0, part_up=0, part_down=0, part_flat=0, part_same=0,
             net=0.0, ups=[], downs=[])
    for a, (cls, st, o, n) in b["rows"].items():
        m = st == "matched"
        if cls in ("same", "nosec"):
            s["matched_same" if m else "part_same"] += 1
            if cls == "nosec":
                s["nosec"] = s.get("nosec", 0) + 1
            continue
        d = (n or 0) - (o or 0)
        s["net"] += d
        if m:
            if (n or 0) >= 100:
                s["matched_same"] += 1       # bytes differ but the row still scores 100
            else:
                s["matched_down"] += 1
                s["downs"].append((a, o, n))
        elif cls == "up":
            s["part_up"] += 1
            s["ups"].append((a, o, n))
        elif cls == "down":
            s["part_down"] += 1
            s["downs"].append((a, o, n))
        else:
            s["part_flat"] += 1
    return s


def report(a):
    recs = [json.loads(l) for l in open(os.path.join(a.out, "results.jsonl"))]
    backend = a.backend[0] if isinstance(a.backend, list) else a.backend
    cands, lines = [], []
    fails = [r["tu"] for r in recs if "error" in r or "error" in r.get("backends", {}).get(backend, {})]
    for r in recs:
        s = summarize(r, backend)
        if s and s["matched_down"] == 0 and s["part_up"] > 0:
            cands.append((r["tu"], s))
    cands.sort(key=lambda c: (-c[1]["net"], c[0]))
    lines.append("# backend %s vs pinned 8447: %d TUs swept, %d compile/err, %d candidates" % (backend, len(recs), len(fails), len(cands)))
    lines.append("")
    for tu, s in cands:
        lines.append("- %s: net %+.1f, matched same %d, partials up %d / down %d / flat %d / same %d: up %s%s" % (
            tu, s["net"], s["matched_same"], s["part_up"], s["part_down"], s["part_flat"], s["part_same"],
            ", ".join("%s %s->%s" % x for x in s["ups"]),
            ("; down " + ", ".join("%s %s->%s" % x for x in s["downs"])) if s["downs"] else ""))
    lines.append("")
    lines.append("## failed or errored: %s" % ", ".join(fails))
    lines.append("")
    lines.append("## TUs with a matched row falling (not candidates)")
    for r in recs:
        s = summarize(r, backend)
        if s and s["matched_down"]:
            lines.append("- %s: matched down %d, partial up %d, net %+.1f" % (r["tu"], s["matched_down"], s["part_up"], s["net"]))
    lines.append("")
    lines.append("## @comp.id (first object seen)")
    for r in recs:
        if "control_comp_id" in r:
            lines.append("control %s" % r["control_comp_id"])
            for n, b in r["backends"].items():
                if "comp_id" in b:
                    lines.append("%s %s" % (n, b["comp_id"]))
            break
    open(os.path.join(a.out, "report.md"), "w").write("\n".join(lines) + "\n")
    print("\n".join(lines[:60]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["setup", "stamps", "run", "report"])
    ap.add_argument("--backend", action="append")
    ap.add_argument("--tu", action="append", default=[])
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=MAX_JOBS)
    ap.add_argument("--out")
    a = ap.parse_args(argv)
    a.backend = a.backend or ["8168"]
    if a.cmd == "setup":
        setup(list(SOURCES))
    elif a.cmd == "stamps":
        setup(list(SOURCES))
        stamps(list(SOURCES))
    elif a.cmd == "run":
        if not os.environ.get("GAMEMD_BINARY"):
            sys.exit("backend_sweep: set GAMEMD_BINARY")
        setup(a.backend)
        run(a)
    else:
        report(a)
    return 0


if __name__ == "__main__":
    sys.exit(main())
