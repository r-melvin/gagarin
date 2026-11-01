#!/usr/bin/env python3
"""c2probe - DIAGNOSTIC-ONLY decision-forcing driver for the pinned C2.DLL.

Concept and hook map after sushi-shi/homm3-decomp (CC0 1.0): the vc6 shim and
decision-forcing.md.  A copy of the toolchain with a pass-through `c2.dll` shim is
built under toolchain/c2probe (ignored, never committed).  Nothing here is used by
match.sh, compile_all, verify_all, m3_gate or any land gate, and the shim refuses
to run unless this driver sets C2PROBE_DRIVER=1.  Output is a report only.

Commands:
  build                      build/refresh the overlay toolchain and the shim DLL
  gate [--n 200] [--hooked]  inertness proof (see gate())
  probe ADDR [ADDR..]        force one decision at a time and report (see probe())
"""
import argparse, hashlib, json, os, shutil, subprocess, sys, time
from pathlib import Path

REPO = Path(__file__).resolve().parents[3]
TC = (REPO / "toolchain").resolve()
REAL_ROOT = TC / "MSVC600"
PROBE_TOP = TC / "c2probe"
PROBE_ROOT = PROBE_TOP / "MSVC600"
WORK = REPO / "build" / "c2probe"
SHIM_DIR = Path(__file__).resolve().parent / "shim"
PINNED_C2 = "a0cc45f83fd0ed009aa4f43df5598105a1049ad9675de0b1089be7cce7d3c153"
MARKER = "C2PROBE DIAGNOSTIC-ONLY"


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def wpath(p):
    return "Z:" + str(Path(p).resolve()).replace("/", "\\")


def wine_env(root):
    env = dict(os.environ)
    vc98, msdev = root / "VC98", root / "Common/MSDev98"
    env["WINEPREFIX"] = str(TC / "wineprefix")
    env["WINEDEBUG"] = "-all"
    env["MESA_LOADER_DRIVER_OVERRIDE"] = "swrast"
    env["LIBGL_ALWAYS_SOFTWARE"] = "1"
    env["WINEPATH"] = f"{vc98}/Bin;{msdev}/Bin"
    env["INCLUDE"] = f"{vc98}/Include;{vc98}/ATL/Include"
    env["LIB"] = f"{vc98}/Lib"
    return env


def build():
    if sha(REAL_ROOT / "VC98/Bin/c2.dll") != PINNED_C2:
        sys.exit("c2probe: real c2.dll is not the pinned 12.00.8447 image; refusing")
    bin_dst = PROBE_ROOT / "VC98/Bin"
    if PROBE_ROOT.exists():
        shutil.rmtree(PROBE_ROOT)
    bin_dst.mkdir(parents=True)
    for e in (REAL_ROOT / "VC98").iterdir():
        if e.name != "Bin":
            (PROBE_ROOT / "VC98" / e.name).symlink_to(e)
    (PROBE_ROOT / "Common").symlink_to(REAL_ROOT / "Common")
    for f in (REAL_ROOT / "VC98/Bin").iterdir():
        if f.is_file():
            shutil.copy2(f, bin_dst / f.name)
    shutil.move(bin_dst / "c2.dll", bin_dst / "C2_real.dll")
    if sha(bin_dst / "C2_real.dll") != PINNED_C2:
        sys.exit("c2probe: copy of c2.dll differs from the pinned image")
    # compile + link the shim with the period compiler itself (C89, no CRT)
    obj_dir = PROBE_TOP / "shimbuild"
    obj_dir.mkdir(exist_ok=True)
    env = wine_env(REAL_ROOT)
    cl = REAL_ROOT / "VC98/Bin/CL.EXE"
    link = REAL_ROOT / "VC98/Bin/LINK.EXE"
    r = subprocess.run(["wine", str(cl), "/nologo", "/c", "/W3", "/O1", "/Gy", f"/I{wpath(SHIM_DIR)}",
                        f"/Fo{wpath(obj_dir / 'passthru.obj')}", wpath(SHIM_DIR / "passthru.c")],
                       env=env, capture_output=True, text=True, cwd=obj_dir)
    sys.stdout.write(r.stdout)
    if r.returncode or not (obj_dir / "passthru.obj").exists():
        sys.exit("shim compile failed")
    r = subprocess.run(["wine", str(link), "/nologo", "/DLL", "/NOENTRY", "/NODEFAULTLIB",
                        f"/DEF:{wpath(SHIM_DIR / 'passthru.def')}", "/OUT:" + wpath(bin_dst / "c2.dll"),
                        wpath(obj_dir / "passthru.obj"), "kernel32.lib"],
                       env=env, capture_output=True, text=True, cwd=obj_dir)
    sys.stdout.write(r.stdout)
    if r.returncode or not (bin_dst / "c2.dll").exists():
        sys.exit("shim link failed")
    print("built", bin_dst / "c2.dll", (bin_dst / "c2.dll").stat().st_size, "bytes")


# --------------------------------------------------------------------------- compile helpers
LEDGER = PROBE_TOP / "ledger.tsv"      # sha256 of every object the shim produced (guard.py reads it)
QUEUE = Path("/home/richard/Projects/gagarin-scratch/permq2/queue.tsv")
VC6CL = REPO / "scripts/vc6/vc6cl.sh"
ENV_KEYS = ("C2PROBE_DRIVER", "C2PROBE_LOG", "C2PROBE_FILTER", "C2PROBE_INLINE_FORCE",
            "C2PROBE_REG_FORCE", "C2PROBE_MERGE_VETO", "C2PROBE_SCRATCH_FORCE", "VC6_ROOT", "VC6_EXTRA_FLAGS", "VC6_FLAGS")


def clean_env():
    return {k: v for k, v in os.environ.items() if k not in ENV_KEYS}


def ledger_add(obj, mode):
    PROBE_TOP.mkdir(parents=True, exist_ok=True)
    with open(LEDGER, "a") as f:
        f.write(f"{sha(obj)}\t{obj}\t{mode}\t{int(time.time())}\n")


def run_cl(src, out, *, probe=False, log=None, extra="", hook=None, tag="plain"):
    """Compile *src* through vc6cl.sh into *out*; probe=True routes through the shim overlay.
    hook = dict(filter=..., inline=<file>, reg=..., merge=...) installs the decision hooks."""
    env = clean_env()
    if extra:
        env["VC6_EXTRA_FLAGS"] = extra
    if probe:
        env["VC6_ROOT"] = str(PROBE_ROOT)
        env["C2PROBE_DRIVER"] = "1"
        env["C2PROBE_LOG"] = wpath(log or (WORK / "scratch.log"))
        if hook:
            env["C2PROBE_FILTER"] = hook["filter"]
            if hook.get("inline"):
                env["C2PROBE_INLINE_FORCE"] = wpath(hook["inline"])
            if hook.get("reg"):
                env["C2PROBE_REG_FORCE"] = hook["reg"]
            if hook.get("merge"):
                env["C2PROBE_MERGE_VETO"] = hook["merge"]
            if hook.get("scratch"):
                env["C2PROBE_SCRATCH_FORCE"] = hook["scratch"]
    out = Path(out)
    out.parent.mkdir(parents=True, exist_ok=True)
    if out.exists():
        out.unlink()
    src = Path(src).resolve()
    # Output goes to a file, not a pipe: the first wine run after the wineserver exited starts a new
    # server that inherits the pipe, and communicate() would then wait for it forever.
    cap = out.with_suffix(".cl.txt")
    with open(cap, "w") as fh:
        subprocess.run(["bash", str(VC6CL), f"/Fo{out}", src.name], env=env, cwd=src.parent,
                       stdout=fh, stderr=subprocess.STDOUT, stdin=subprocess.DEVNULL)
    text = cap.read_text(errors="replace")
    cap.unlink()
    ok = out.exists() and "error" not in text.lower().replace("0 error", "")
    if ok and probe:
        ledger_add(out, tag)
    return ok, text


def masked_diff(a, b):
    """Byte offsets where two COFF objects differ, ignoring the 4 TimeDateStamp bytes."""
    da, db = Path(a).read_bytes(), Path(b).read_bytes()
    if len(da) != len(db):
        return [-1]
    return [i for i in range(len(da)) if da[i] != db[i] and not 4 <= i < 8]


def capture(src, capdir):
    """One /d1il front-end run: the four IL streams every replay reuses."""
    capdir = Path(capdir)
    if capdir.exists():
        shutil.rmtree(capdir)
    capdir.mkdir(parents=True)
    run_cl(src, capdir / "unused.obj", extra="/d1il" + wpath(capdir / "il"))
    missing = [s for s in ("in", "gl", "sy", "ex") if not (capdir / ("il" + s)).is_file()]
    if missing:
        raise RuntimeError(f"IL capture of {src} lacks {missing}")


def replay(src, capdir, out, **kw):
    feed = Path(out).parent / ("feed-" + Path(out).stem)
    if feed.exists():
        shutil.rmtree(feed)
    feed.mkdir(parents=True)
    for f in Path(capdir).glob("il*"):
        shutil.copy2(f, feed / f.name)
    try:
        return run_cl(src, out, extra="/d2il" + wpath(feed / "il"), **kw)
    finally:
        shutil.rmtree(feed, ignore_errors=True)


# --------------------------------------------------------------------------- inertness gate
def _gate_one(src):
    d = WORK / "gate" / hashlib.md5(str(src).encode()).hexdigest()[:10]
    if d.exists():
        shutil.rmtree(d)
    d.mkdir(parents=True)
    res = {"tu": str(src.relative_to(REPO)), "status": None}
    ok1, _ = run_cl(src, d / "real1.obj")
    if not ok1:
        res["status"] = "skip-real-compile-fails"
        return res
    ok2, _ = run_cl(src, d / "real2.obj")
    if not ok2 or masked_diff(d / "real1.obj", d / "real2.obj"):
        res["status"] = "skip-baseline-nondeterministic"
        return res
    okp, tp = run_cl(src, d / "pass.obj", probe=True, log=d / "pass.log", tag="gate-pass")
    okh, th = run_cl(src, d / "hook.obj", probe=True, log=d / "hook.log", tag="gate-hooked",
                     hook=dict(filter="*"))
    res["pass_ok"], res["hook_ok"] = okp, okh
    res["pass_diff"] = masked_diff(d / "real1.obj", d / "pass.obj") if okp else ["compile-failed"]
    res["hook_diff"] = masked_diff(d / "real1.obj", d / "hook.obj") if okh else ["compile-failed"]
    res["bytes"] = (d / "real1.obj").stat().st_size
    ev = {"main": 0, "site": 0, "color": 0, "merge": 0, "scratch": 0}
    if (d / "hook.log").exists():
        for line in (d / "hook.log").read_text(errors="replace").splitlines():
            w = line.split(" ", 1)[0]
            if w in ev:
                ev[w] += 1
    res["events"] = ev
    res["status"] = "ok" if not res["pass_diff"] and not res["hook_diff"] else "FAIL"
    if res["status"] == "ok":
        shutil.rmtree(d, ignore_errors=True)
    return res


def negative(n=40, jobs=4, seed=20261101):
    """Negative control: a gate that cannot go red proves nothing.  Force registers with the hooks
    live and require that the comparison DOES report differing objects."""
    import random
    from concurrent.futures import ThreadPoolExecutor
    tus = sorted(p for p in (REPO / "match").rglob("*.cpp") if "_layout" not in p.parts)
    random.Random(seed).shuffle(tus)

    def one(src):
        d = WORK / "negative" / hashlib.md5(str(src).encode()).hexdigest()[:10]
        d.mkdir(parents=True, exist_ok=True)
        ok1, _ = run_cl(src, d / "real.obj")
        okh, _ = run_cl(src, d / "forced.obj", probe=True, log=d / "f.log", tag="gate-negative",
                        hook=dict(filter="*", reg=",".join(f"{k}:{r}" for k in range(1, 9) for r in (6,)),
                                  scratch=",".join(f"{k}:3" for k in range(1, 40))))
        diff = ok1 and okh and masked_diff(d / "real.obj", d / "forced.obj")
        shutil.rmtree(d, ignore_errors=True)
        return bool(diff)

    with ThreadPoolExecutor(jobs) as ex:
        hits = list(ex.map(one, tus[:n]))
    print(f"negative control: {sum(hits)}/{n} TUs differ when registers are forced (must be > 0)")
    return 0 if any(hits) else 1


def gate(n, jobs, seed=20261101):
    import random
    from concurrent.futures import ThreadPoolExecutor
    WORK.mkdir(parents=True, exist_ok=True)
    tus = sorted(p for p in (REPO / "match").rglob("*") if p.suffix.lower() in (".cpp", ".c")
                 and "_layout" not in p.parts)
    random.Random(seed).shuffle(tus)
    results, valid, i = [], 0, 0
    t0 = time.time()
    with ThreadPoolExecutor(jobs) as ex:
        while valid < n and i < len(tus):
            chunk = tus[i:i + max(jobs * 8, n - valid)]
            i += len(chunk)
            for r in ex.map(_gate_one, chunk):
                results.append(r)
                if r["status"] in ("ok", "FAIL"):
                    valid += 1
                print(f"[{len(results):4d}] {r['status']:34s} {r['tu']}", flush=True)
    bad = [r for r in results if r["status"] == "FAIL"]
    ok = [r for r in results if r["status"] == "ok"]
    ev = {k: sum(r["events"][k] for r in ok) for k in ("main", "site", "color", "merge", "scratch")}
    summary = {"marker": MARKER, "tus_valid": valid, "ok": len(ok), "fail": len(bad),
               "skipped": {s: sum(1 for r in results if r["status"] == s)
                           for s in sorted({r["status"] for r in results}) if s not in ("ok", "FAIL")},
               "seed": seed, "bytes_compared_each_of_pass_and_hooked": sum(r["bytes"] for r in ok),
               "hook_events_exercised_with_empty_rules": ev, "secs": round(time.time() - t0),
               "c2_real_sha256": PINNED_C2, "shim_sha256": sha(PROBE_ROOT / "VC98/Bin/c2.dll"),
               "failures": bad}
    (WORK / "gate_summary.json").write_text(json.dumps(summary, indent=1))
    print(json.dumps(summary, indent=1))
    return 1 if bad or valid < n else 0


# --------------------------------------------------------------------------- probe
def load_row(addr):
    import csv
    want = int(addr, 16)
    for r in csv.DictReader(open(QUEUE), delimiter="\t"):
        if int(r["addr"], 16) == want:
            return r
    sys.exit(f"{addr}: not in {QUEUE}")


def score(obj, row, streams=None):
    """(pct, ndiff, exact) from diff_retail.py; streams optionally dumped."""
    cmd = [sys.executable, str(REPO / "scripts/vc6/diff_retail.py"), "--obj", str(obj), "--sym", row["sym"],
           "--addr", row["addr"], "--len", row["len"]]
    if streams:
        cmd += ["--dump-streams", str(streams)]
    r = subprocess.run(cmd, capture_output=True, text=True, env=clean_env() | {"GAMEMD_BINARY": os.environ["GAMEMD_BINARY"]})
    out = r.stdout
    import re
    m = re.search(r"match: ([0-9.]+)%", out)
    d = re.search(r"\((\d+) exact, (\d+) reloc-normalised, (\d+) diff\)", out)
    if not m or not d:
        return None
    diffs = [ln for ln in out.splitlines() if ln.rstrip().endswith("**DIFF**")]
    return float(m.group(1)), int(d.group(3)), r.returncode == 0 and "100.0%" in m.group(0), diffs


def parse_log(path, root):
    sites, colors, merges, scratch = [], [], [], []
    inroot = False
    for line in Path(path).read_text(errors="replace").splitlines():
        if line.startswith("main "):
            inroot = line.split()[1] == root
            continue
        if not inroot:
            continue
        kv = dict(p.split("=", 1) for p in line.split()[1:] if "=" in p)
        if line.startswith("site "):
            sites.append(kv)
        elif line.startswith("color "):
            colors.append(kv)
        elif line.startswith("merge "):
            merges.append(kv)
        elif line.startswith("scratch "):
            scratch.append(kv)
    return sites, colors, merges, scratch


REGS = {1: "eax", 2: "ecx", 3: "edx", 4: "ebx", 6: "ebp", 7: "esi", 8: "edi"}


class Probe:
    def __init__(self, addr, max_trials, work, depth2=5):
        self.depth2 = depth2
        self.row = load_row(addr)
        self.addr = addr
        self.src = REPO / self.row["tu"]
        self.root = self.row["sym"]
        self.dir = work / addr.lower()
        self.max_trials = max_trials
        self.trials = 0
        self.n = 0
        self.report = {"marker": MARKER, "addr": addr, "tu": self.row["tu"], "sym": self.root,
                       "queue_pct": float(self.row["pct"]), "steps": []}

    def run(self, rules=(), reg=(), veto=(), scratch=(), tag=None, record=True):
        """One shim replay with the given decisions forced; returns (score, log path, obj)."""
        self.n += 1
        tag = tag or f"t{self.n}"
        obj = self.dir / f"{tag}.obj"
        log = self.dir / f"{tag}.log"
        if log.exists():
            log.unlink()
        hook = dict(filter=self.root)
        if rules:
            rf = self.dir / f"{tag}.rules"
            rf.write_text("".join(f"{o}\t{c}\t{n}\t{a}\n" for o, c, n, a in rules))
            hook["inline"] = rf
        if reg:
            hook["reg"] = ",".join(f"{k}:{r}" for k, r in reg)
        if veto:
            hook["merge"] = ",".join(str(k) for k in veto)
        if scratch:
            hook["scratch"] = ",".join(f"{k}:{r}" for k, r in scratch)
        ok, text = replay(self.src, self.dir / "cap", obj, probe=True, log=log, hook=hook, tag="probe-" + tag)
        if not ok:
            return None, log, obj
        return score(obj, self.row), log, obj

    def go(self):
        self.dir.mkdir(parents=True, exist_ok=True)
        capture(self.src, self.dir / "cap")
        real = self.dir / "real.obj"
        ok, _ = replay(self.src, self.dir / "cap", real)
        if not ok:
            raise RuntimeError("real replay failed")
        self.base_real = score(real, self.row)
        sc, log, obj = self.run(tag="base")
        self.report["inert"] = bool(sc) and not masked_diff(real, obj)
        self.report["baseline"] = {"pct": sc[0] if sc else None, "ndiff": sc[1] if sc else None,
                                   "real_replay_pct": self.base_real[0] if self.base_real else None}
        if not self.report["inert"]:
            self.report["verdict"] = "ABORT: shim replay differs from real replay outside the timestamp"
            return
        self.report["first_diffs"] = sc[3][:12]
        cur = dict(rules=[], reg=[], veto=[], scratch=[])
        best = (sc[0], sc[1])
        sites, colors, merges, scr = parse_log(log, self.root)
        self.report["hookable"] = {"inline_sites": len(sites), "colour_decisions": len(colors),
                                   "merge_decisions": len(merges), "scratch_requests": len(scr)}
        self.base_ndiff = best[1]
        sideways = []
        for rnd in range(4):
            if best[0] >= 100.0 or self.trials >= self.max_trials:
                break
            cands = self.candidates(cur, sites, colors, merges, scr)
            round_best = None
            for desc, new in cands:
                if self.trials >= self.max_trials:
                    break
                self.trials += 1
                s, _, _ = self.run(rules=new["rules"], reg=new["reg"], veto=new["veto"], scratch=new["scratch"])
                if s and rnd == 0 and s[1] <= self.base_ndiff and s[0] >= best[0] - 0.5:
                    sideways.append((s, desc, new))
                if s and (s[0], -s[1]) > (best[0], -best[1]) and (round_best is None or (s[0], -s[1]) > (round_best[0][0], -round_best[0][1])):
                    round_best = (s, desc, new)
            self.report["steps"].append({"round": rnd + 1, "candidates": len(cands),
                                         "best": None if not round_best else
                                         {"decision": round_best[1], "pct": round_best[0][0], "ndiff": round_best[0][1]}})
            if not round_best:
                break
            best = (round_best[0][0], round_best[0][1])
            cur = round_best[2]
            self.report.setdefault("applied", []).append(round_best[1])
            _, log2, _ = self.run(rules=cur["rules"], reg=cur["reg"], veto=cur["veto"], scratch=cur["scratch"], tag=f"after{rnd+1}")
            sites, colors, merges, scr = parse_log(log2, self.root)
        if best[0] < 100.0 and not self.report.get("applied") and sideways and self.depth2 > 0:
            # No single decision improves the score: look for a coupled pair (first step is
            # no worse than baseline; second step is scratch or colour).
            sideways.sort(key=lambda t: (-t[0][0], t[0][1]))
            pair_best = None
            for s1, d1, n1 in sideways[:self.depth2]:
                if self.trials >= self.max_trials * 3:
                    break
                _, log2, _ = self.run(rules=n1["rules"], reg=n1["reg"], veto=n1["veto"], scratch=n1["scratch"], tag="pair-base")
                st2, co2, me2, sc2 = parse_log(log2, self.root)
                for d2, n2 in self.candidates(n1, st2, co2, me2, sc2):
                    if not d2.startswith(("scratch", "register")) or self.trials >= self.max_trials * 3:
                        continue
                    self.trials += 1
                    s2, _, _ = self.run(rules=n2["rules"], reg=n2["reg"], veto=n2["veto"], scratch=n2["scratch"])
                    if s2 and (s2[0], -s2[1]) > (best[0], -best[1]) and (pair_best is None or (s2[0], -s2[1]) > (pair_best[0][0], -pair_best[0][1])):
                        pair_best = (s2, [d1, d2])
                        if s2[0] >= 100.0:
                            break
                if pair_best and pair_best[0][0] >= 100.0:
                    break
            self.report["steps"].append({"round": "pair", "best": None if not pair_best else
                                         {"decisions": pair_best[1], "pct": pair_best[0][0], "ndiff": pair_best[0][1]}})
            if pair_best:
                best = (pair_best[0][0], pair_best[0][1])
                self.report["applied"] = pair_best[1]
        self.report["trials"] = self.trials
        self.report["best_pct"] = best[0]
        self.report["reproduces_retail"] = best[0] >= 100.0
        if best[0] >= 100.0 and not self.report.get("applied"):
            self.report["verdict"] = "already exact in the current tree (queue row stale)"
        elif best[0] >= 100.0:
            self.report["verdict"] = "forcing reproduces retail: " + "; ".join(self.report["applied"])
        elif self.report.get("applied"):
            self.report["verdict"] = f"partial: best forced {best[0]} ({best[1]} diff) with " + "; ".join(self.report["applied"])
        else:
            self.report["verdict"] = "no single hooked decision (inline/colour/merge/scratch), and no coupled scratch/colour pair from the top first steps, reproduces retail"

    def candidates(self, cur, sites, colors, merges, scr):
        out = []
        fixed_s = {k for k, _ in cur["scratch"]}
        for q in scr:
            k = int(q["k"])
            if k in fixed_s:
                continue
            now = int(q["cursor"]) + 1 if q.get("forced") is None else int(q["forced"])
            for r in (1, 2, 3):
                if r != now:
                    out.append((f"scratch k={k} pseudo={q['pseudo']} start {REGS[now] if now in REGS else now}->{REGS[r]}", dict(cur, scratch=cur["scratch"] + [(k, r)])))
        seen = {}
        occ = []
        for s in sites:
            key = (s["owner"], s["callee"])
            seen[key] = seen.get(key, 0) + 1
            occ.append((key, seen[key], s))
        have = {(o, c, n) for o, c, n, a in cur["rules"]}
        for (o, c), n, s in occ:
            if (o, c, n) in have:
                continue
            for act in ("E", "K"):
                if s.get("force") == act:
                    continue
                d = f"inline {act} owner={o} callee={c} occurrence={n} (cb={s['cb']} budget={s['budget']} depth={s['depth']})"
                out.append((d, dict(cur, rules=cur["rules"] + [(o, c, n, act)])))
        fixed = {k for k, _ in cur["reg"]}
        for c in colors:
            k = int(c["k"])
            if k in fixed:
                continue
            elig = int(c["eligible"], 16)
            for r in range(1, 9):
                if r != 5 and elig >> r & 1 and r != int(c.get("forced") or c["chosen"]):
                    d = (f"register k={k} priority={c['priority']} {REGS.get(int(c['chosen']), '?')}->{REGS[r]} "
                         f"(eligible {','.join(REGS[x] for x in range(1, 9) if x != 5 and elig >> x & 1)})")
                    out.append((d, dict(cur, reg=cur["reg"] + [(k, r)])))
        for m in merges:
            k = int(m["k"])
            if k not in cur["veto"]:
                out.append((f"merge-veto k={k} kind={m['kind']} count={m['count']}", dict(cur, veto=cur["veto"] + [k])))
        return out


def probe(addrs, jobs, max_trials, depth2=5):
    from concurrent.futures import ThreadPoolExecutor
    work = WORK / "probe"
    work.mkdir(parents=True, exist_ok=True)

    def one(a):
        p = Probe(a, max_trials, work, depth2)
        try:
            p.go()
        except Exception as e:
            p.report["verdict"] = f"ERROR {e!r}"
        (work / f"{a.lower()}.json").write_text(json.dumps(p.report, indent=1))
        return p.report

    with ThreadPoolExecutor(jobs) as ex:
        reps = list(ex.map(one, addrs))
    lines = [f"# {MARKER} - decision-forcing report (never a source or manifest change)", ""]
    for r in reps:
        lines.append(f"## {r['addr']} {r['tu']} (queue {r['queue_pct']}%)")
        lines.append(f"- verdict: {r.get('verdict')}")
        lines.append(f"- inert replay: {r.get('inert')}; baseline: {r.get('baseline')}; hookable: {r.get('hookable')}")
        for d in r.get("first_diffs", []):
            lines.append(f"  - diff `{d}`")
        for a in r.get("applied", []):
            lines.append(f"  - applied: {a}")
        lines.append("")
    (WORK / "report.md").write_text("\n".join(lines))
    print("\n".join(lines))


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("build")
    g = sub.add_parser("gate")
    g.add_argument("--n", type=int, default=200)
    g.add_argument("--jobs", type=int, default=4)
    g.add_argument("--negative", action="store_true")
    p = sub.add_parser("probe")
    p.add_argument("addrs", nargs="+")
    p.add_argument("--jobs", type=int, default=2)
    p.add_argument("--max-trials", type=int, default=150)
    p.add_argument("--depth2", type=int, default=5, help="first-step candidates to extend into pairs (0 = off)")
    a = ap.parse_args()
    if a.cmd == "build":
        build()
    elif a.cmd == "gate":
        sys.exit(negative(jobs=a.jobs) if a.negative else gate(a.n, a.jobs))
    else:
        if "GAMEMD_BINARY" not in os.environ:
            sys.exit("set GAMEMD_BINARY")
        probe(a.addrs, a.jobs, a.max_trials, a.depth2)


if __name__ == "__main__":
    main()
