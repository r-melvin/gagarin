#!/usr/bin/env python3
# Provenance: original. trivgen: generate and verify C++ for trivial retail functions.
"""trivgen.py  scan | patterns | run | packet   (see README.md)

All state lives in WORK (default <scratch>/trivgen/work); generated sources are
written into the isolated worktree WT (default <scratch>/trivgen/wt, a detached
worktree at main HEAD), never into main.
"""
import argparse
import collections
import concurrent.futures as cf
import csv
import hashlib
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent))

import canon  # noqa: E402
import common  # noqa: E402
import data  # noqa: E402
import emit  # noqa: E402
import gen  # noqa: E402
import lift  # noqa: E402
import patterns  # noqa: E402
import verify  # noqa: E402
import x86  # noqa: E402
from lift import Unsupported  # noqa: E402

WORK = Path(os.environ.get("TRIVGEN_WORK", data.SR + "/trivgen/work"))
READY = Path(os.environ.get("TRIVGEN_READY", data.SR + "/trivgen/READY"))
WT = data.WT
JOBS = int(os.environ.get("TRIVGEN_JOBS", "4"))
MAX_EXT = 48
# Static-initialiser shapes (the __xc table entries). Kept in their own files so they can land with,
# or after, the header-initialiser milestone independently of the ordinary functions.
INIT_PATTERNS = {"static-init-fp", "static-init-stores"}

def log(*a):
    print(time.strftime("%H:%M:%S"), *a, file=sys.stderr, flush=True)


# ---------------------------------------------------------------- scan / lift
def scan():
    WORK.mkdir(parents=True, exist_ok=True)
    keep, drop = data.candidates()
    tus, votes = data.tu_info()
    vi = data.vtable_index()
    items = []
    for r, _ in keep:
        a = int(r["addr"], 16)
        size, insns = x86.extent(a)
        items.append(dict(addr=a, ext=size, wl_size=int(r["size"]), tu_id=r["tu_id"], tu_name=r["original_tu"],
                          owning_class=r["owning_class"], vtable=[list(e) for e in vi.get(a, [])]))
    dropped = collections.Counter(w.split(":")[0] for _, w in drop)
    (WORK / "candidates.json").write_text(json.dumps(dict(items=items, dropped=dict(dropped),
                                                          total=len(keep) + len(drop)), indent=1))
    log(f"candidates {len(items)} (worklist <=32 bytes: {len(keep) + len(drop)}; dropped {dict(dropped)})")
    return items


def load_items():
    p = WORK / "candidates.json"
    if not p.exists():
        scan()
    return json.loads(p.read_text())


def library_range():
    """Address span of the statically linked CRT, from libmatch's byte matches (library_map.json)."""
    lm = common.library_map()
    if not lm:
        return None
    rows = json.loads((common.STATE / "library_map.json").read_text())["found"]
    lo = min(common.h(r["addr"]) for r in rows)
    hi = max(common.h(r["addr"]) + common.h(r["len"]) for r in rows)
    return lo, hi


def do_lift(items):
    lib = library_range()
    for it in items:
        a = it["addr"]
        if lib and lib[0] <= a < lib[1]:
            it["pattern"] = "library-region"
            it["fail"] = "statically linked CRT (libmatch span %#x-%#x): mark LIBRARY, not generated" % lib
            continue
        if it["ext"] == 0 or it["ext"] > MAX_EXT:
            it["pattern"] = "unsupported:extent"
            it["fail"] = f"extent {it['ext']}"
            continue
        try:
            sp = lift.lift(a)
            if it.get("vtable"):
                sp.flags["member"] = True
                c = canon.find(a, it["vtable"])
                if c:
                    sp.flags["canon"] = c
            it["spec"] = sp
            it["pattern"] = patterns.pattern_of(sp)
        except Unsupported as e:
            it["pattern"] = "unsupported:" + str(e).split(":")[0]
            it["fail"] = "lift:" + str(e)
        except Exception as e:  # lifter defect: keep going, record it
            it["pattern"] = "unsupported:lifter-exception"
            it["fail"] = "lift-exception:" + repr(e)[:80]
    return items


def cmd_patterns(args):
    d = load_items()
    items = do_lift(d["items"])
    c = collections.Counter(i["pattern"] for i in items)
    out = ["pattern\tcount"] + [f"{k}\t{v}" for k, v in c.most_common()]
    (WORK / "pattern_counts.tsv").write_text("\n".join(out) + "\n")
    print("\n".join(out))
    print("total", len(items))


# ---------------------------------------------------------------- planning
def module_for_tu(tu_id, votes):
    v = votes.get(tu_id)
    if v:
        return max(v.items(), key=lambda kv: kv[1])[0]
    return "core"


def existing_basenames():
    names = set()
    for root in (WT / "match",):
        for p in root.rglob("*"):
            if p.suffix.lower() in (".cpp", ".h", ".c"):
                names.add(p.name)
    return names


def emit_item(it, var):
    return emit.emit(it["spec"], var)


TAKEN = set()   # basenames already in the tree (set by callers that must not collide)


def plan_bins(items, varsel, votes, taken):
    """Build bins from items (address order) using each item's chosen variant."""
    by_tu = collections.defaultdict(list)
    for it in items:
        by_tu[(it["tu_id"], it["pattern"] in INIT_PATTERNS)].append(it)
    bins = []
    for tu, is_init in sorted(by_tu):
        mod = module_for_tu(tu, votes)
        tub = []
        for it in sorted(by_tu[(tu, is_init)], key=lambda x: x["addr"]):
            if it.get("fail"):
                continue
            var = varsel[it["addr"]]
            try:
                out = emit_item(it, var)
            except Unsupported as e:
                it["fail"] = "emit:" + str(e)
                continue
            out.pattern = patterns.describe(it["pattern"]) + describe_owner(it)
            placed = False
            for b in tub:
                try:
                    b.add(out)
                    placed = True
                    break
                except Unsupported:
                    continue
            if not placed:
                idx = len(tub)
                while True:
                    stem = (f"trivial_{tu.lower()}" + ("_init" if is_init else "") +
                            (f"_{chr(ord('a') + idx)}" if idx else "") + "_methods")
                    if stem + ".h" not in TAKEN and stem + ".cpp" not in TAKEN:
                        break
                    idx += 1
                b = gen.Bin(stem, mod)
                try:
                    b.add(out)
                except Unsupported as e:
                    it["fail"] = "emit:" + str(e)
                    continue
                tub.append(b)
            it["bin"] = None
        bins += tub
    return bins


def describe_owner(it):
    vt = it.get("vtable")
    if not vt:
        return ""
    cls, slot, n = canon.owner_of(vt)
    more = f" and {n - 1} derived vtable(s)" if n > 1 else ""
    return f" Vtable slot {slot} of {cls} (RTTI){more}."


# ---------------------------------------------------------------- writing / compiling
def write_bins(bins):
    for b in bins:
        d = WT / "match" / b.module
        d.mkdir(parents=True, exist_ok=True)
        (d / (b.name + ".h")).write_text(b.header_text(None))
        (d / (b.name + ".cpp")).write_text(b.cpp_text(None))


def clean_generated():
    for p in (WT / "match").rglob("trivial_tu*_methods.*"):
        p.unlink()


def compile_all(bins):
    results = {}

    def one(b):
        rel = f"match/{b.module}/{b.name}.cpp"
        return b.name, verify.compile_bin(rel)

    with cf.ThreadPoolExecutor(JOBS) as ex:
        for name, res in ex.map(one, bins):
            results[name] = res
    return results


def attribute_errors(b, errors):
    """Map compile errors to function addresses; returns (addrs, unattributed_count)."""
    cpp = b.cpp_text(None)
    lm = b.line_map(cpp)
    hdr = b.header_text(None).split("\n")
    bad, un = set(), 0
    for fn, line, code, msg in errors:
        if fn.endswith(".cpp"):
            hit = [a for a, (lo, hi) in lm.items() if lo <= line <= hi]
            if hit:
                bad.update(hit)
                continue
        elif fn.endswith(".h") and 1 <= line <= len(hdr):
            text = hdr[line - 1]
            m = re.search(r"(?:FUN|DAT)_([0-9A-F]{8})", text)
            hits = set()
            if m:
                hits.add(int(m.group(1), 16))
            # a view / member line: attribute to the owning function through its names
            names = re.findall(r"(Obj|Arg\d+|Sub|Gbl|Gptr)_([0-9A-F]{8})", text)
            for _, h in names:
                hits.add(int(h, 16))
            if hits:
                bad.update(hits)
                continue
        un += 1
    return bad, un


# ---------------------------------------------------------------- run
def build_variant_lists(live):
    """Per function: ordered list of variant dicts with duplicate bodies removed.
    A variant the emitter refuses is skipped; the function fails only if every variant is refused."""
    for it in live:
        seen, lst, first_err = set(), [], None
        try:
            vars_ = emit.variants(it["spec"])
        except Exception as e:
            it["fail"] = "emit-exception:" + repr(e)[:100]
            it["vlist"] = []
            continue
        for var in vars_:
            try:
                body = emit_item(it, var).body
            except Unsupported as e:
                first_err = first_err or ("emit:" + str(e))
                continue
            except Exception as e:
                first_err = first_err or ("emit-exception:" + repr(e)[:100])
                continue
            if body not in seen:
                seen.add(body)
                lst.append(var)
        if not lst:
            it["fail"] = first_err or "emit:no-variant"
        it["vlist"] = lst


def compile_probe(todo, sel, votes):
    """Plan, write and compile bins for `todo`; drop functions with compile errors and retry.
    Returns (bins, results, compile_fail{addr: reason})."""
    probe = list(todo)
    compile_fail = {}
    bins, res = [], {}
    for attempt in range(8):
        for it in probe:
            it["fail"] = None
        bins = plan_bins(probe, sel, votes, None)
        clean_generated()
        write_bins(bins)
        res = compile_all(bins)
        newbad = set()
        for b in bins:
            obj, errs, text = res[b.name]
            if obj is not None:
                continue
            bad, un = attribute_errors(b, errs)
            if not bad:
                bad = {o.spec.addr for o in b.items}
            reason = (errs[0][2] + " " + errs[0][3]) if errs else "compile"
            for a in bad:
                compile_fail.setdefault(a, reason)
            newbad |= bad
        if not newbad:
            break
        probe = [i for i in probe if i["addr"] not in newbad]
    return bins, res, compile_fail


def verify_bins(bins, res):
    """-> {addr: check result dict}"""
    jobs = []
    for b in bins:
        obj, errs, _ = res[b.name]
        if obj is None:
            continue
        sp = WORK / f"smap_{b.name}.json"
        sp.write_text(json.dumps(verify.symbol_map(obj)))
        for o in b.items:
            jobs.append((b, obj, o, sp))

    def chk(j):
        b, obj, o, sp = j
        return o, b, verify.check_function(obj, o.spec.addr, o.spec.size, sp, hint=o.sym_hint)

    out = {}
    with cf.ThreadPoolExecutor(8) as ex:
        for o, b, r in ex.map(chk, jobs):
            r["bin"] = b.name
            r["module"] = b.module
            out[o.spec.addr] = r
    return out


def cmd_run(args):
    d = load_items()
    items = do_lift(d["items"])
    tus, votes = data.tu_info()
    live = [i for i in items if "spec" in i]
    if args.only:
        live = [i for i in live if re.search(args.only, i["pattern"])]
    if args.limit:
        live = live[:args.limit]
    log(f"liftable {len(live)} / {len(items)}")
    build_variant_lists(live)
    attempts = collections.defaultdict(list)       # addr -> [(variant, outcome)]
    exact = {}
    live = [i for i in live if i["vlist"]]
    maxr = max((len(i["vlist"]) for i in live), default=0)
    for rnd in range(maxr):
        todo = [i for i in live if i["addr"] not in exact and len(i["vlist"]) > rnd]
        if not todo:
            break
        sel = {i["addr"]: i["vlist"][rnd] for i in todo}
        bins, res, cfail = compile_probe(todo, {a: v for a, v in sel.items()}, votes)
        for a, why in cfail.items():
            attempts[a].append((sel[a], "compile: " + why))
        checks = verify_bins(bins, res)
        n_ok = 0
        for a, r in checks.items():
            attempts[a].append((sel[a], "exact" if r["ok"] else r["why"]))
            if r["ok"]:
                exact[a] = dict(var=sel[a], sym=r["sym"], relocs=r.get("relocs", ""), tu=r["bin"], module=r["module"])
                n_ok += 1
        log(f"round {rnd}: tried {len(todo)}, exact +{n_ok} -> {len(exact)}")
    # final emission: only exact functions
    final = [i for i in live if i["addr"] in exact]
    clean_generated()
    bins = plan_bins(final, {i["addr"]: exact[i["addr"]]["var"] for i in final}, votes, None)
    write_bins(bins)
    summary = []
    for i in items:
        a = i["addr"]
        if args.only or args.limit:
            if a not in {x["addr"] for x in live} and "spec" in i:
                continue
        if a in exact:
            st, why = "exact", ""
        else:
            st = "fail"
            tried = attempts.get(a, [])
            why = i.get("fail") or ("; ".join(f"{json.dumps(v, sort_keys=True)}:{o}" for v, o in tried[:2]))
        summary.append(dict(addr=hex(a), pattern=i["pattern"], tu=i["tu_id"], size=i["ext"], status=st,
                            why=why, attempts=len(attempts.get(a, []))))
    (WORK / "run_state.json").write_text(json.dumps(dict(
        exact={hex(k): v for k, v in exact.items()}, summary=summary,
        attempts={hex(k): v for k, v in attempts.items()}), indent=1))
    c = collections.Counter(s["status"] for s in summary)
    log("final:", dict(c))
    byp = collections.defaultdict(lambda: [0, 0])
    for s in summary:
        byp[s["pattern"]][0] += 1
        byp[s["pattern"]][1] += s["status"] == "exact"
    for k, (n, e) in sorted(byp.items(), key=lambda kv: -kv[1][0]):
        print(f"{k:40s} {n:5d} {e:5d}")


def cmd_diag(args):
    """Emit one function into a scratch TU, compile, and show the aligned diff."""
    d = load_items()
    items = do_lift(d["items"])
    a = int(args.addr, 0)
    it = next(i for i in items if i["addr"] == a)
    if "spec" not in it:
        print("not liftable:", it.get("fail"))
        print("\n".join(f"{i.addr:#x} {i.text}" for i in x86.extent(a)[1]))
        return
    out = emit_item(it, emit.variants(it["spec"])[args.var])
    b = gen.Bin("trivial_tu999_diag_methods", "core")
    b.add(out)
    write_bins([b])
    print((WT / "match/core/trivial_tu999_diag_methods.cpp").read_text().split("#include")[1].split("\n", 2)[2])
    if not args.brief:
        print((WT / "match/core/trivial_tu999_diag_methods.h").read_text().split("#include \"../_rt/gg_static_assert.h\"")[1])
    obj, errs, text = verify.compile_bin("match/core/trivial_tu999_diag_methods.cpp")
    if obj is None:
        print(text)
        return
    sym = verify.find_symbol(obj, a)
    r = subprocess.run([sys.executable, str(WT / "scripts/vc6/diff_retail.py"), "--obj", str(obj), "--sym", sym,
                        "--addr", hex(a), "--len", hex(it["ext"])], capture_output=True, text=True,
                       env=dict(os.environ, GAMEMD_BINARY=verify.BIN))
    print(r.stdout)
    for f in (WT / "match/core").glob("trivial_tu999_diag_methods.*"):
        f.unlink()


def cmd_setup():
    if WT.exists():
        print("worktree exists:", WT)
        return
    WT.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(["git", "-C", str(data.MAIN), "worktree", "add", str(WT), "main", "--detach"], check=True)
    link = WT / "toolchain"
    if not link.exists():
        link.symlink_to(data.MAIN / "toolchain")
    print("worktree ready at", WT, subprocess.run(["git", "-C", str(WT), "rev-parse", "HEAD"], capture_output=True,
                                                  text=True).stdout.strip())


def cmd_teardown():
    link = WT / "toolchain"
    if link.is_symlink():
        link.unlink()
    subprocess.run(["git", "-C", str(data.MAIN), "worktree", "remove", "--force", str(WT)], check=True)
    print("worktree removed:", WT)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("cmd", choices=["setup", "scan", "patterns", "run", "packet", "all", "diag", "teardown"])
    ap.add_argument("addr", nargs="?")
    ap.add_argument("--var", type=int, default=0)
    ap.add_argument("--brief", action="store_true")
    ap.add_argument("--only", help="regex on pattern name (run only)")
    ap.add_argument("--limit", type=int, help="max functions (run only)")
    args = ap.parse_args()
    if args.cmd == "setup":
        cmd_setup()
    elif args.cmd == "teardown":
        cmd_teardown()
    elif args.cmd == "all":
        scan()
        cmd_run(args)
        import packet
        packet.main()
    elif args.cmd == "scan":
        scan()
    elif args.cmd == "patterns":
        cmd_patterns(args)
    elif args.cmd == "run":
        cmd_run(args)
    elif args.cmd == "diag":
        cmd_diag(args)
    elif args.cmd == "packet":
        import packet
        packet.main()


if __name__ == "__main__":
    main()
