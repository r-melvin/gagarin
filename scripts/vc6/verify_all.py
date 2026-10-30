#!/usr/bin/env python3
# verify_all.py — P5 match-% dashboard + regression gate.
#
# Reads the authoritative match manifest (scripts/data/match_manifest.json: the verified
# {tu, addr, sym, len, status} per function), compiles each referenced TU with the
# period VC6 toolchain, and re-runs the per-function oracle (raw_match.py, then
# diff_retail.py for remaining cases) against the user's retail
# gamemd.exe. Emits a per-TU and overall match-% table, and FAILS if any function
# marked `matched` no longer reaches 100% (a true regression gate). The manifest
# carries the ground-truth len/sym so the check is exact (auto-deriving lengths
# from Ghidra misfires on overloads / undefined-function entries).
#
# This is the authoritative whole-repo check: run it before committing or in CI to
# confirm no matched function has regressed. It needs the user's binary (Ghidra
# CLI) + the fetched toolchain — both developer-supplied, never committed.
#
# Usage:   scripts/vc6/verify_all.py [--md docs/match_dashboard.md] [--jobs N] [--changed [REF]] [--tu TU] [--shard I/N]
# Exit 0 iff all referenced TUs compile and every 100% row still matches.
import argparse, atexit, concurrent.futures, json, os, shutil, subprocess, sys, tempfile

# NOTE: `matched` entries are re-proved on every run, but a `partial` entry's
# recorded pct is only a note - nothing re-measures it. After any change to the
# scoring rules in diff_retail.py those numbers are stale, and stale in both
# directions: the register-rename false positive inflated them, and a wrong
# --len deflated them. Refresh with scripts/vc6/refresh_partials.py.

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))  # loaded by path from other tools
import changed_tus  # noqa: E402

GHIDRA = os.path.expanduser("~/.cargo/bin/ghidra")




def pct_of(stdout):
    for l in stdout.splitlines():
        if l.startswith("match:"):
            return l.split()[-1]
    return None


def verify(obj, sym, addr, length):
    """100% per raw_match, then instruction comparison for remaining cases.

    Exact bytes with actual COFF relocations are the cheapest strong proof.
    Trying them first avoids expensive disassembly for already-exact functions.
    """
    last = ""
    for tool in ("raw_match.py", "diff_retail.py"):
        r = subprocess.run(["python3", f"{ROOT}/scripts/vc6/{tool}", "--obj", obj,
                            "--sym", sym, "--addr", addr, "--len", length],
                           capture_output=True, text=True)
        if tool == "raw_match.py" and r.returncode == 3:
            return False, "hard float-literal relocation failure"
        if tool == "raw_match.py" and r.returncode == 4:
            return False, "address-labelled DAT relocation target mismatch"
        if r.returncode == 0 and "100.0%" in r.stdout:
            return True, "100.0%"
        last = r.stdout
    return False, pct_of(last) or "?"


def default_jobs():
    return max(1, min(8, os.cpu_count() or 1))


def check_tu(n, tu, rows, objdir):
    """Compile one TU and score its matched rows. Returns (compiled, results).

    results is [(row, ok, pct)] for the `matched` rows only, in manifest order.
    Pure of printing so TUs can run concurrently and be reported in order.
    """
    d = os.path.join(ROOT, os.path.dirname(tu))
    f = os.path.basename(tu)
    obj = os.path.join(objdir, f"{n}_{os.path.splitext(f)[0]}.obj")
    if os.path.exists(obj):
        os.remove(obj)
    # Compiler output is unused. A Wine descendant can inherit a capture
    # pipe and prevent communicate() from reaching EOF after CL exits.
    compiled = subprocess.run(
        ["bash", f"{ROOT}/scripts/vc6/{'vc6asm.sh' if f.lower().endswith('.asm') else 'vc6cl.sh'}", f"/Fo{obj}", f],
        cwd=d, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    if compiled.returncode != 0 or not os.path.exists(obj):
        return False, []
    results = []
    for e in rows:
        # Manifest status is authoritative. A partial row may have a
        # 100% diagnostic score while still lacking structural proof
        # (for example, a vtable slot closure); never promote it here.
        if e.get("status") == "matched":
            ok, pc = verify(obj, e["sym"], e["addr"], e["len"])
            results.append((e, ok, pc))
    return True, results


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--manifest", default=f"{ROOT}/scripts/data/match_manifest.json")
    ap.add_argument("--md", help="write a markdown dashboard to this path")
    ap.add_argument("--jobs", type=int, default=default_jobs(),
                    help="TUs compiled and scored concurrently (default: nproc, max 8)")
    ap.add_argument("--changed", nargs="?", const="HEAD", metavar="REF",
                    help="only TUs whose source or transitively included header "
                         "differs from git REF (default HEAD); totals then cover "
                         "that subset only")
    ap.add_argument("--tu", action="append", default=[],
                    help="only this TU (repeatable)")
    ap.add_argument("--shard", metavar="I/N",
                    help="only every Nth sorted TU starting at I (for splitting a run)")
    args = ap.parse_args()
    if args.jobs < 1:
        ap.error("--jobs must be positive")
    if args.md and (args.changed or args.tu or args.shard):
        ap.error("--md needs a full run; it cannot be combined with --changed/--tu/--shard")

    with open(args.manifest) as manifest:
        man = json.load(manifest)
    by_tu = {}
    for e in man:
        by_tu.setdefault(e["tu"], []).append(e)
    tus = sorted(by_tu)
    if args.tu:
        tus = [tu for tu in tus if tu in set(args.tu)]
    if args.shard:
        i, n = map(int, args.shard.split("/"))
        tus = [tu for k, tu in enumerate(tus) if k % n == i % n]
    if args.changed:
        keep = changed_tus.select_changed(ROOT, tus, args.changed)
        tus = [tu for tu in tus if tu in keep]
        print(f"--changed {args.changed}: {len(tus)} of {len(by_tu)} TUs affected")

    # Private per-run object directory. Fixed /tmp/va_<name>.obj paths let two
    # overlapping runs (or two TUs with the same basename in different
    # directories) overwrite each other's objects and verify the wrong bytes.
    objdir = tempfile.mkdtemp(prefix="verify_all_")
    atexit.register(shutil.rmtree, objdir, True)
    tot_m = tot_p = regr = 0
    md = ["# Match-% Dashboard", "",
          "Auto-generated by `scripts/vc6/verify_all.py` from `scripts/data/match_manifest.json`.",
          "", "| TU | matched | partial | status |", "|----|--------:|--------:|--------|"]
    fail = False
    # Results are consumed in sorted-TU order whatever order they finish in, so
    # the report is byte-identical to a serial run.
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = [pool.submit(check_tu, n, tu, by_tu[tu], objdir)
                   for n, tu in enumerate(tus)]
        for tu, future in zip(tus, futures):
            compiled, results = future.result()
            if not compiled:
                print(f"COMPILE FAIL  {tu}"); fail = True
                md.append(f"| `{tu}` | — | — | **COMPILE FAIL** |"); continue
            m = 0; bad = []
            for e, ok, pc in results:
                if ok:
                    m += 1
                else:
                    regr += 1; bad.append(f"{e['name']} -> {pc}")
                    print(f"  REGRESSED {tu}::{e['name']} -> {pc}")
            p = len(by_tu[tu]) - len(results)  # Compile checked; partial pct is not re-measured.
            tot_m += m; tot_p += p
            st = "OK" if not bad else "**REGRESSED: " + "; ".join(bad) + "**"
            print(f"  {tu:<46} matched {m}  partial {p}  {st if bad else ''}")
            md.append(f"| `{tu}` | {m} | {p} | {st} |")
    md.insert(5, f"| **TOTAL** | **{tot_m}** | **{tot_p}** | "
                 f"{'**' + str(regr) + ' REGRESSED**' if regr else 'all green'} |")
    print(f"\n=== {tot_m} matched (100%), {tot_p} documented partials, "
          f"{regr} regressed, across {len(tus)} TUs ===")
    if args.md:
        open(args.md, "w").write("\n".join(md) + "\n")
        print(f"dashboard -> {args.md}")
    sys.exit(1 if (fail or regr) else 0)


if __name__ == "__main__":
    main()
