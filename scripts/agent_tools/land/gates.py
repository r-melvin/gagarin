#!/usr/bin/env python3
"""gates.py: the landing gates for one gagarin tree, in `full` or `inc` mode.

    gates.py --tree WT --base REV [--mode inc|full] [--jobs N] [--run DIR]
             [--symmap FILE]... [--waive 0xADDR]... [--only g1,g2] [--skip g1,g2]
             [--msg FILE] [--allow-path REGEX]... [--fail-fast]

WT is a git worktree holding the change (staged or committed; untracked files
are ignored, as build_project ignores them). REV is the base the change is
measured against (a rev in WT's repository).

Modes
  full  Everything, from scratch: build_project --jobs N + --check into a per-run
        dir (replaces compile_all.sh, verify_all's own compiles and the separate
        project build: one compile pass), every matched manifest row verified,
        unit tests, check_duplicates, dupdefs over all objects, check_naked,
        section comparison of every object against independently built base
        objects (cache-assisted, see README), lint, words, strict relocation
        checks on the changed rows. The compile cache is NOT used for the new side.
  inc   Whole-tree compile check through the content-addressed object cache
        (hit = skip, miss = compile), but verify_all-equivalent row checks,
        section comparison and tests only on the AFFECTED TUs: changed .cpp files,
        TUs whose include closure holds a changed header (in the base or the new
        tree), TUs of changed manifest rows, plus layout headers likewise.
        Changing scripts/vc6/vc6cl.sh or any non-test script under scripts/vc6
        escalates to all TUs.

Every gate prints one line `GATE <name> <PASS|FAIL|SKIP|INFO> <secs>s <detail>`;
logs and summary.json land in the run dir. Exit status is non-zero if a gate failed.
"""
import argparse
import concurrent.futures as cf
import importlib.util
import json
import os
import re
import shutil
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import landlib as L  # noqa: E402
import sectioncmp as S  # noqa: E402

FORBID_RE = L.FORBID_RE
ALLOWED_DEFAULT = L.ALLOWED_PATHS
GATES = []


def gate(fn):
    GATES.append(fn)
    return fn


class Ctx:
    def __init__(self, a):
        self.a = a
        self.tree = os.path.abspath(a.tree)
        self.mode = a.mode
        self.jobs = a.jobs
        self.run = os.path.abspath(a.run)
        os.makedirs(self.run, exist_ok=True)
        self.base = L.rev_parse(self.tree, a.base)
        self.env = L.toolenv()
        self.t0 = time.time()
        self.results = []
        # file sets and include indexes
        roots = list(L.INCLUDE_ROOTS) + [r.strip("/") for r in getattr(a, "include_root", [])]
        for _ in range(3):
            self.new_files = L.TreeFiles(self.tree, roots)
            self.idx_new = L.IncludeIndex(self.new_files)
            more = self.discover_roots(roots)
            if not more:
                break
            roots += more
        self.roots = roots
        self.base_files = L.RevFiles(self.tree, self.base, roots)
        self.idx_base = L.IncludeIndex(self.base_files)
        self.salt = L.toolchain_salt(self.tree)
        self.tus = self.idx_new.tus()
        # change set
        out = L.git(self.tree, "diff", "--name-status", "--no-renames", "-z", self.base, "--", text=False)
        parts = [p.decode() for p in out.split(b"\0") if p]
        self.changed = {}
        for i in range(0, len(parts) - 1, 2):
            self.changed[parts[i + 1]] = parts[i][0]
        # manifest delta
        bm = self.base_files_manifest()
        nm, _ = L.load_manifest(os.path.join(self.tree, L.MANIFEST))
        self.man = nm
        self.added, self.changed_rows, self.removed = L.manifest_diff(bm, nm)
        self.compute_affected()
        self.objs_new = os.path.join(self.run, "new")      # new-side object tree
        self.objs_base = os.path.join(self.run, "base")
        self.new_obj_state = {}                             # tu -> 'compiled'|'cache'|'FAIL'
        self.new_keys = {}
        self.promote = False

    def discover_roots(self, roots):
        """Tracked top-level directories (not yet roots) that an unresolved quoted include points into,
        e.g. "../../../third_party/..." from match/<dir>/<dir>/x.c."""
        tops = {p.split("/", 1)[0] for p in L.git(self.tree, "ls-files", "-z", text=False).decode(errors="replace").split("\0") if "/" in p}
        found = set()
        for tu, lst in self.idx_new.all_unresolved().items():
            for f, inc in lst:
                cand = L._norm(os.path.join(os.path.dirname(f), inc))
                top = cand.split("/", 1)[0]
                if top in tops and top not in roots and not cand.startswith(".."):
                    found.add(top)
        return sorted(found)

    def base_files_manifest(self):
        data = L.git(self.tree, "show", "%s:%s" % (self.base, L.MANIFEST), text=False)
        return json.loads(data)

    # ------------------------------------------------------------- affected set
    def compute_affected(self):
        ch = self.changed
        notes = []
        self.escalate = None
        for p in ch:
            if p == "scripts/vc6/vc6cl.sh" or (p.startswith("scripts/vc6/") and not os.path.basename(p).startswith("test_")
                                                and p.endswith((".py", ".sh"))):
                self.escalate = p
        dep_new = self.idx_new.dependents()
        dep_base = self.idx_base.dependents()
        tus = set()
        for p in ch:
            if not (p.startswith("match/") or p in self.idx_new.known or p in self.idx_base.known):
                continue
            if p.endswith(L.SRC_EXT) and p in self.idx_new.known and p.startswith("match/"):
                tus.add(p)
            tus |= dep_new.get(p, set())
            tus |= {t for t in dep_base.get(p, set()) if t in self.idx_new.known}
        self.by_include = set(tus)
        # manifest rows that moved: verify their TUs too
        row_tus = {r["tu"] for r in self.added + self.changed_rows + self.removed}
        base_rows = {L.A(r): r for r in self.base_files_manifest()}
        for r in self.changed_rows + self.removed:
            if L.A(r) in base_rows:
                row_tus.add(base_rows[L.A(r)]["tu"])
        self.row_tus = {t for t in row_tus if t in self.idx_new.known}
        tus |= self.row_tus
        if self.escalate:
            notes.append("escalated to all TUs: %s changed" % self.escalate)
            tus = set(self.tus)
        self.affected = sorted(tus)
        self.scope = sorted(self.tus) if self.mode == "full" else self.affected
        self.notes = notes
        # layout headers
        affected_files = set(ch)
        self.layout_scope = []
        for h in L.layout_headers(self.new_files):
            if self.mode == "full" or self.escalate or set(self.idx_new.closure(h)) & affected_files \
                    or any(c in affected_files for c in self.idx_base.closure(h) if h in self.idx_base.known):
                self.layout_scope.append(h)


def objpath(root, tu):
    return os.path.join(root, os.path.splitext(tu)[0] + ".obj")


# ---------------------------------------------------------------- object cache
def cache_path(key):
    return os.path.join(L.CACHE, "obj", key[:2], key + ".obj")


def cache_get(key, dst):
    p = cache_path(key)
    if os.path.isfile(p):
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copyfile(p, dst)
        try:
            os.utime(p)          # keep recently used entries out of cache_tool gc
        except OSError:
            pass
        return True
    return False


def cache_put(key, src):
    p = cache_path(key)
    if os.path.isfile(p):
        return
    os.makedirs(os.path.dirname(p), exist_ok=True)
    tmp = p + ".tmp%d" % os.getpid()
    shutil.copyfile(src, tmp)
    os.replace(tmp, p)


def compile_one(tree, tu, dst, env, extra=()):
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    if os.path.exists(dst):
        os.unlink(dst)
    rc, text = L.run(["bash", os.path.join(tree, "scripts/vc6/vc6cl.sh"), *extra, "/Fo" + dst, os.path.basename(tu)],
                     cwd=os.path.join(tree, os.path.dirname(tu)), env=env, log=dst[:-4] + ".log")
    ok = rc == 0 and os.path.isfile(dst)
    if not ok and os.path.exists(dst):
        os.unlink(dst)
    return ok


def compile_set(ctx, tree, files, index, tus, outroot, use_cache, store, label):
    """Compile (or fetch) every TU into outroot. Returns {tu: state}."""
    state = {}
    keys = {tu: index.key(tu, ctx.salt) for tu in tus}

    def one(tu):
        dst = objpath(outroot, tu)
        if use_cache and cache_get(keys[tu], dst):
            return tu, "cache"
        if not compile_one(tree, tu, dst, ctx.env):
            return tu, "FAIL"
        if store:
            cache_put(keys[tu], dst)
        return tu, "compiled"

    with cf.ThreadPoolExecutor(ctx.jobs) as ex:
        for tu, st in ex.map(one, tus):
            state[tu] = st
    return state, keys


# ---------------------------------------------------------------- gates
@gate
def static(ctx):
    """Whole-tree static checks: includes resolve, no tracked symlinks, manifest TUs tracked."""
    errs = []
    un = ctx.idx_new.all_unresolved()
    for tu, lst in sorted(un.items()):
        for f, inc in lst[:3]:
            errs.append("unresolved include %r in %s (reached from %s)" % (inc, f, tu))
    tracked = set(ctx.new_files.paths)
    for p in ctx.new_files.paths:
        if os.path.islink(os.path.join(ctx.tree, p)):
            errs.append("tracked symlink " + p)
    for r in ctx.man:
        if r["tu"] not in tracked:
            errs.append("manifest row %s names untracked TU %s" % (r["addr"], r["tu"]))
    known = {"tu", "addr", "sym", "len", "name", "status", "pct", "note", "qualification", "metric", "pct_metric"}
    for r in ctx.added + ctx.changed_rows:
        extra = sorted(set(r) - known)
        if extra:
            errs.append("manifest row %s has unexpected keys %s (packet bookkeeping left in the manifest?)" % (r["addr"], extra))
    sym = [p for p in ctx.changed if os.path.islink(os.path.join(ctx.tree, p))]
    errs += ["changed path is a symlink: " + p for p in sym]
    for e in sorted(set(errs))[:40]:
        print(e)
    return ("FAIL" if errs else "PASS"), "%d TUs indexed, %d unresolved/other problems" % (len(ctx.tus), len(set(errs)))


@gate
def compile(ctx):
    """Compile check. full: build_project --jobs N + --check (one pass). inc: whole tree via cache."""
    out = os.path.join(ctx.run, "new")
    if ctx.mode == "full":
        # base side first (cache lookup) so the new side can be stored afterwards without self-comparison
        shutil.rmtree(out, ignore_errors=True)
        rc, text = L.run([sys.executable, "scripts/vc6/build_project.py", "--jobs", str(ctx.jobs), "--out", out],
                         cwd=ctx.tree, env=ctx.env, log=os.path.join(ctx.run, "build_project.log"))
        rc2, text2 = L.run([sys.executable, "scripts/vc6/build_project.py", "--check", "--out", out],
                           cwd=ctx.tree, env=ctx.env, log=os.path.join(ctx.run, "build_check.log"))
        keys = {tu: ctx.idx_new.key(tu, ctx.salt) for tu in ctx.tus}
        ctx.new_keys = keys
        ctx.new_obj_state = {tu: ("compiled" if os.path.isfile(objpath(out, tu)) else "FAIL") for tu in ctx.tus}
        ctx.promote = True
        bad = [tu for tu, s in ctx.new_obj_state.items() if s == "FAIL"]
        for tu in bad[:20]:
            print("COMPILE FAIL", tu)
        tail = (text.strip().splitlines() or [""])[-1]
        return ("PASS" if rc == 0 and rc2 == 0 and not bad else "FAIL"), "build rc=%d check rc=%d; %s" % (rc, rc2, tail)
    state, keys = compile_set(ctx, ctx.tree, ctx.new_files, ctx.idx_new, ctx.tus, out, True, True, "new")
    ctx.new_obj_state, ctx.new_keys = state, keys
    bad = [tu for tu, s in state.items() if s == "FAIL"]
    for tu in bad[:20]:
        print("COMPILE FAIL", tu)
        print(open(objpath(out, tu)[:-4] + ".log", errors="replace").read()[-600:])
    hits = sum(1 for s in state.values() if s == "cache")
    return ("FAIL" if bad else "PASS"), "%d TUs: %d from cache, %d compiled, %d failed" % (
        len(state), hits, len(state) - hits - len(bad), len(bad))


@gate
def layout(ctx):
    """Layout headers compile standalone (their static asserts hold) through an includer outside the tree."""
    scope = ctx.layout_scope
    d = os.path.join(ctx.run, "layout")
    os.makedirs(d, exist_ok=True)
    bad = []

    def one(h):
        base = os.path.basename(h)[:-2]
        inc = os.path.join(d, "_ca_%s.cpp" % base)
        rel = os.path.relpath(os.path.join(ctx.tree, h), d)
        open(inc, "w").write('#include "%s"\nint _chk_%s(){return 0;}\n' % (rel, base))
        dst = os.path.join(d, base + ".obj")
        key = L.sha(ctx.salt + "|layout|" + base + "|" + "|".join(
            "%s:%s" % (f, L.sha(ctx.new_files.read(f) or b"")) for f in sorted(ctx.idx_new.closure(h))))
        if ctx.mode != "full" and cache_get(key, dst):
            return h, "cache"
        if os.path.exists(dst):
            os.unlink(dst)
        rc, text = L.run(["bash", os.path.join(ctx.tree, "scripts/vc6/vc6cl.sh"), "/Fo" + dst, os.path.basename(inc)],
                         cwd=d, env=ctx.env, log=dst[:-4] + ".log")
        if rc == 0 and os.path.isfile(dst):
            cache_put(key, dst)
            return h, "compiled"
        return h, "FAIL"

    with cf.ThreadPoolExecutor(ctx.jobs) as ex:
        res = dict(ex.map(one, scope))
    for h, s in res.items():
        if s == "FAIL":
            bad.append(h)
            print("LAYOUT FAIL", h)
    total = len(L.layout_headers(ctx.new_files))
    return ("FAIL" if bad else "PASS"), "%d/%d layout headers checked, %d failed" % (len(scope), total, len(bad))


def load_verify_all(tree):
    spec = importlib.util.spec_from_file_location("va_tree", os.path.join(tree, "scripts/vc6/verify_all.py"))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


@gate
def verify(ctx):
    """verify_all equivalent on the scoped TUs, from the already built objects (per-run temp dir, no /tmp/va_*)."""
    va = load_verify_all(ctx.tree)
    by_tu = {}
    for r in ctx.man:
        by_tu.setdefault(r["tu"], []).append(r)
    scope = [tu for tu in ctx.scope if tu in by_tu]
    work = []
    fail_tus = []
    partial = 0
    for tu in scope:
        o = objpath(ctx.objs_new, tu)
        if not os.path.isfile(o):
            fail_tus.append(tu)
            print("COMPILE FAIL ", tu)
            continue
        for r in by_tu[tu]:
            if r.get("status") == "matched":
                work.append((tu, o, r))
            else:
                partial += 1
    os.environ["GAMEMD_BINARY"] = L.BINARY

    def one(w):
        tu, o, r = w
        try:
            ok, pc = va.verify(o, r["sym"], r["addr"], r["len"])
        except Exception as ex:   # surface, never swallow
            ok, pc = False, "exception %r" % (ex,)
        return tu, r, ok, pc

    regressed = []
    with cf.ThreadPoolExecutor(ctx.jobs) as ex:
        for tu, r, ok, pc in ex.map(one, work):
            if not ok:
                regressed.append((tu, r))
                print("  REGRESSED %s::%s %s -> %s" % (tu, r.get("name"), r["addr"], pc))
    detail = "%d TUs, %d matched rows re-proved, %d partial rows compile-checked, %d regressed, %d compile fails" % (
        len(scope), len(work), partial, len(regressed), len(fail_tus))
    ctx.verify_summary = {"tus": len(scope), "rows": len(work), "regressed": sorted(r["addr"] for _, r in regressed)}
    return ("FAIL" if regressed or fail_tus else "PASS"), detail


@gate
def strict(ctx):
    """raw_match + strict verify_relocations on added/changed matched manifest rows."""
    rows = [r for r in ctx.added + ctx.changed_rows if r.get("status") == "matched"]
    if not rows:
        return "SKIP", "no added/changed matched rows"
    # Each map file is a {symbol: address} object. Entries that agree across files are
    # merged into one map; a row that fails with the merged map is retried with each file
    # alone (TU-local labels such as $L244 legitimately differ between clusters).
    files = [json.load(open(p)) for p in ctx.a.symmap]
    merged, clash = {}, set()
    for d in files:
        for k, v in d.items():
            if k in merged and int(str(merged[k]), 0) != int(str(v), 0):
                clash.add(k)
            merged.setdefault(k, v)
    for k in clash:
        merged.pop(k, None)
    mp = os.path.join(ctx.run, "symmap_merged.json")
    json.dump(merged, open(mp, "w"))
    singles = []
    for i, d in enumerate(files):
        sp = os.path.join(ctx.run, "symmap_%d.json" % i)
        json.dump(d, open(sp, "w"))
        singles.append(sp)
    waived = {int(w, 0) for w in ctx.a.waive}

    def one(r):
        o = objpath(ctx.objs_new, r["tu"])
        if not os.path.isfile(o):
            return r, 99, 99, "no object"
        c = ["--obj", o, "--sym", r["sym"], "--addr", r["addr"], "--len", r["len"]]
        p = subprocess.run([sys.executable, "scripts/vc6/raw_match.py", *c], capture_output=True, text=True,
                           env=ctx.env, cwd=ctx.tree)
        for cand in [mp] + (singles if clash else []):
            q = subprocess.run([sys.executable, "scripts/vc6/verify_relocations.py", *c, "--binary", L.BINARY, "--json",
                                "--symbol-map", cand], capture_output=True, text=True, env=ctx.env, cwd=ctx.tree)
            if q.returncode == 0:
                break
        return r, p.returncode, q.returncode, ((p.stdout + p.stderr)[-160:] + (q.stdout + q.stderr)[-240:]).replace("\n", " ")

    fails, waivedn = [], 0
    with cf.ThreadPoolExecutor(ctx.jobs) as ex:
        res = list(ex.map(one, rows))
    out = []
    for r, rc, sc, text in res:
        out.append({"addr": r["addr"], "tu": r["tu"], "raw": rc, "strict": sc})
        if rc or sc:
            if L.A(r) in waived:
                waivedn += 1
                continue
            fails.append(r["addr"])
            print("FAIL", r["addr"], r["tu"], "raw=%d strict=%d" % (rc, sc), text)
    json.dump(out, open(os.path.join(ctx.run, "strict.json"), "w"), indent=1)
    return ("FAIL" if fails else "PASS"), "%d rows, %d failed, %d waived" % (len(rows), len(fails), waivedn)


@gate
def tests(ctx):
    scripts_touched = any(p.startswith("scripts/") for p in ctx.changed)
    if ctx.mode == "inc" and not scripts_touched:
        return "SKIP", "no scripts/ change (inc mode); full mode always runs them"
    rc, text = L.run([sys.executable, "-m", "unittest", "discover", "-s", "scripts/vc6", "-p", "test_*.py"],
                     cwd=ctx.tree, env=ctx.env, log=os.path.join(ctx.run, "tests.log"))
    tail = text.strip().splitlines()[-3:]
    if rc:
        print("\n".join(tail))
    return ("PASS" if rc == 0 else "FAIL"), " ".join(tail[-1:]) if tail else ""


@gate
def dups(ctx):
    rc, text = L.run([sys.executable, "scripts/vc6/check_duplicates.py"], cwd=ctx.tree, env=ctx.env,
                     log=os.path.join(ctx.run, "check_duplicates.log"))
    if rc:
        print(text[-1500:])
    return ("PASS" if rc == 0 else "FAIL"), (text.strip().splitlines() or [""])[-1]


@gate
def naked(ctx):
    rc, text = L.run([sys.executable, "scripts/vc6/check_naked.py"], cwd=ctx.tree, env=ctx.env,
                     log=os.path.join(ctx.run, "check_naked.log"))
    if rc:
        print(text[-800:])
    return ("PASS" if rc == 0 else "FAIL"), (text.strip().splitlines() or [""])[-1]


def strong_defs(tree_vt, path):
    import struct
    d, ss, sy, aux = tree_vt.parse_coff(path)
    nsec = struct.unpack_from("<H", d, 2)[0]
    ch = {i: struct.unpack_from("<I", d, 20 + (i - 1) * 40 + 36)[0] for i in range(1, nsec + 1)}
    sel = {}
    for i, s in sy.items():
        if s["storage_class"] == 3 and s["aux_count"] and s["section"] in ss and s["name"] == ss[s["section"]]["name"] \
                and s["value"] == 0:
            a = aux.get(i + 1)
            if a:
                sel[s["section"]] = a[14]
    out = []
    for s in sy.values():
        if s["storage_class"] == 2 and s["section"] > 0:
            sec = s["section"]
            comdat = bool(ch[sec] & 0x1000)
            if not comdat or sel.get(sec) == 1:
                out.append(s["name"])
    return out


@gate
def dupdefs(ctx):
    """External symbols defined (non-COMDAT or NODUPLICATES) in more than one object, whole tree."""
    spec = importlib.util.spec_from_file_location("vt_tree", os.path.join(ctx.tree, "scripts/vc6/verify_vtable.py"))
    vt = importlib.util.module_from_spec(spec)
    sys.path.insert(0, os.path.join(ctx.tree, "scripts/vc6"))
    spec.loader.exec_module(vt)
    defs, missing = {}, []
    sd = os.path.join(L.CACHE, "symdefs")
    os.makedirs(sd, exist_ok=True)
    for tu in ctx.tus:
        key = ctx.new_keys.get(tu) or ctx.idx_new.key(tu, ctx.salt)
        sp = os.path.join(sd, key + ".json")
        if ctx.mode != "full" and os.path.isfile(sp):
            names = json.load(open(sp))
        else:
            o = objpath(ctx.objs_new, tu)
            if not os.path.isfile(o):
                missing.append(tu)
                continue
            names = strong_defs(vt, o)
            json.dump(names, open(sp, "w"))
        for n in names:
            defs.setdefault(n, []).append(tu)
    bad = {k: v for k, v in defs.items() if len(v) > 1}
    for k, v in sorted(bad.items())[:30]:
        print("DUPLICATE", k, v)
    if missing:
        print("no object for", missing[:10])
    return ("FAIL" if bad or missing else "PASS"), "%d symbols, %d strong duplicates, %d objects missing" % (
        len(defs), len(bad), len(missing))


def ensure_base_objects(ctx, tus):
    """Base-side objects for tus: cache by closure key, misses compiled from a scratch base worktree."""
    keys = {tu: ctx.idx_base.key(tu, ctx.salt) for tu in tus if tu in ctx.idx_base.known}
    miss = []
    for tu, k in keys.items():
        if not cache_get(k, objpath(ctx.objs_base, tu)):
            miss.append(tu)
    built = 0
    if miss:
        wt = os.path.join(ctx.run, "basewt")
        L.git(ctx.tree, "worktree", "add", "--detach", wt, ctx.base)
        try:
            os.symlink(L.TOOLCHAIN, os.path.join(wt, "toolchain"))
            with cf.ThreadPoolExecutor(ctx.jobs) as ex:
                futs = {tu: ex.submit(compile_one, wt, tu, objpath(ctx.objs_base, tu), ctx.env) for tu in miss}
                for tu, f in futs.items():
                    if f.result():
                        cache_put(keys[tu], objpath(ctx.objs_base, tu))
                        built += 1
        finally:
            L.git(ctx.tree, "worktree", "remove", "--force", wt, check=False)
    return keys, len(tus) - len(miss), built


def raw_pct(tree, env, obj, row):
    """(raw-matches retail, percent or None) of ROW's function in OBJ, relocations wildcarded (raw_match.py)."""
    p = subprocess.run([sys.executable, "scripts/vc6/raw_match.py", "--obj", obj, "--sym", row["sym"],
                        "--addr", row["addr"], "--len", row["len"]], cwd=tree, env=env, capture_output=True, text=True)
    m = re.findall(r"match: ([0-9.]+)%", p.stdout)
    pct = float(m[-1]) if m else None
    return p.returncode == 0 and pct == 100.0, pct


def unexplained_sections(rep, base_rows, touched, raw_fn, base_obj, new_obj):
    """Differing sections of matched functions the delta does not touch. Returns (unexplained, improved):
    a byte change is IMPROVED (not a failure) when the new bytes raw-match retail where the old bytes did
    not (e.g. a non-owner COMDAT copy moving to retail); a change away from retail, or between two
    states that both match, stays unexplained. improved = [(tu, section, before_pct, after_pct)]."""
    unexpl, improved = [], []
    for tu, r in rep["changed"].items():
        for d in r["differ"]:
            sym = d["section"].split("|", 1)[1].split("#")[0] if "|" in d["section"] else ""
            if sym in base_rows and sym not in touched and not d["bytes_same"]:
                row = base_rows[sym]
                old_ok, old_pct = raw_fn(base_obj(tu), row)
                new_ok, new_pct = raw_fn(new_obj(tu), row)
                if new_ok and not old_ok:
                    improved.append((tu, d["section"], old_pct, new_pct))
                else:
                    unexpl.append((tu, d["section"]))
    return unexpl, improved


@gate
def sections(ctx):
    """Section comparison, base objects vs new objects, over the scoped TUs."""
    tus = [tu for tu in ctx.scope if tu in ctx.idx_base.known and tu in ctx.idx_new.known]
    keys, hits, built = ensure_base_objects(ctx, tus)
    rep = S.compare_trees(ctx.objs_base, ctx.objs_new, tus)
    rep["only_new"] = sorted(t for t in ctx.scope if t not in ctx.idx_base.known)
    rep["only_base"] = sorted(t for t in ctx.idx_base.tus() if t not in ctx.idx_new.known)
    json.dump(rep, open(os.path.join(ctx.run, "sections.json"), "w"), indent=1)
    lines = S.summarize(rep)
    open(os.path.join(ctx.run, "sections.txt"), "w").write("\n".join(lines) + "\n")
    # unexplained: a differing section whose function row is matched in base and untouched by the delta
    touched = {r["sym"] for r in ctx.added + ctx.changed_rows + ctx.removed}
    touched |= {r["name"] for r in ctx.added + ctx.changed_rows + ctx.removed if r.get("name")}
    base_rows = {r["sym"]: r for r in ctx.base_files_manifest() if r.get("status") == "matched"}
    def raw_fn(obj, row):
        return raw_pct(ctx.tree, ctx.env, obj, row)
    unexpl, improved = unexplained_sections(rep, base_rows, touched, raw_fn,
                                            lambda tu: objpath(ctx.objs_base, tu), lambda tu: objpath(ctx.objs_new, tu))
    for tu, s_, b, a in improved:
        print("MATCHED FUNCTION IMPROVED", tu, s_, "%s%% -> %s%% vs retail (relocation-wildcarded)" % (b, a))
    for tu, s in unexpl[:20]:
        print("MATCHED FUNCTION BYTES CHANGED", tu, s)
    if rep["missing_base"] or rep["missing_new"]:
        print("missing objects: base", rep["missing_base"][:5], "new", rep["missing_new"][:5])
    ctx.sections_digest = sorted(map(list, S.digest(rep)))
    status = "FAIL" if (unexpl or rep["missing_base"] or rep["missing_new"]) else "PASS"
    return status, "%d TUs compared (%d base from cache, %d built), %d identical, %d changed, %d matched-function byte changes, %d matched-function improvements" % (
        len(tus), hits, built, rep["identical"], len(rep["changed"]), len(unexpl), len(improved))


@gate
def lint(ctx):
    """reccmp-decomplint on touched match files; fails on error types the base file did not have."""
    exe = shutil.which("reccmp-decomplint")
    if not exe:
        return "SKIP", "reccmp-decomplint not on PATH"
    files = [p for p, s in ctx.changed.items() if p.startswith("match/") and p.endswith((".cpp", ".h")) and s != "D"]
    rx = re.compile(r"(error|warning): [a-z_]+")

    def types(path):
        rc, t = L.run([exe, "--module", "GAMEMD", path], env=ctx.env)
        return {m.group(0) for m in rx.finditer(t)}

    def one(p):
        n = types(os.path.join(ctx.tree, p))
        if ctx.changed[p] == "A":
            return p, "NEW", sorted(x for x in n if x.startswith("error"))
        b = ctx.base_files.read(p)
        bp = os.path.join(ctx.run, "lintbase", p)
        os.makedirs(os.path.dirname(bp), exist_ok=True)
        open(bp, "wb").write(b or b"")
        new = sorted(x for x in n - types(bp) if x.startswith("error"))
        return p, "PRE", new

    with cf.ThreadPoolExecutor(ctx.jobs) as ex:
        res = list(ex.map(one, files))
    bad = [(p, k, n) for p, k, n in res if n]
    for p, k, n in bad[:30]:
        print("%s %s %s" % (k, p, n))
    return ("FAIL" if bad else "PASS"), "%d files linted, %d with new error types" % (len(files), len(bad))


@gate
def words(ctx):
    """Forbidden words in added lines and the commit message; paths outside the allowed set."""
    out = L.git(ctx.tree, "diff", "-U0", "--no-color", ctx.base, "--")
    ok = [re.compile(x) for x in ctx.a.allow_word]
    vend = [re.compile(x) for x in L.VENDORED_PATHS + list(getattr(ctx.a, "vendored", []))]
    hits, nvend = L.word_hits(out, ok, vend)
    msg_hits = 0
    if ctx.a.msg and os.path.isfile(ctx.a.msg):
        msg_hits = len(FORBID_RE.findall(open(ctx.a.msg).read()))
    allowed = [re.compile(x) for x in ALLOWED_DEFAULT + list(ctx.a.allow_path)]
    forb = sorted(p for p in ctx.changed if not any(a.search(p) for a in allowed))
    for h in hits[:15]:
        print("WORD", h[:160])
    for f in forb:
        print("PATH NOT ALLOWED", f)
    return ("FAIL" if hits or msg_hits or forb else "PASS"), "%d added-line hits, %d message hits, %d disallowed paths%s" % (
        len(hits), msg_hits, len(forb), ("; %d lines in vendored paths exempt" % nvend) if nvend else "")


# ---------------------------------------------------------------- driver
def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", required=True)
    ap.add_argument("--base", required=True)
    ap.add_argument("--mode", choices=["inc", "full"], default="inc")
    ap.add_argument("--jobs", type=int, default=min(16, (os.cpu_count() or 8) // 2))
    ap.add_argument("--run", default=None)
    ap.add_argument("--symmap", action="append", default=[])
    ap.add_argument("--waive", action="append", default=[])
    ap.add_argument("--only", default="")
    ap.add_argument("--skip", default="")
    ap.add_argument("--msg", default=None)
    ap.add_argument("--allow-path", action="append", default=[])
    ap.add_argument("--allow-word", action="append", default=[],
                    help="regex; added lines matching it are not word hits (e.g. a binary-attested RTTI name)")
    ap.add_argument("--include-root", action="append", default=[],
                    help="extra tracked top-level directory quoted includes may resolve into (third_party is built in; others are auto-discovered)")
    ap.add_argument("--vendored", action="append", default=[],
                    help="regex of a vendored path whose upstream text the words gate skips (built in: third_party/lzo/)")
    ap.add_argument("--fail-fast", action="store_true")
    ap.add_argument("--no-promote", action="store_true", help="do not add full-mode objects to the cache")
    a = ap.parse_args(argv)
    if a.run is None:
        os.makedirs(L.RUNS, exist_ok=True)
        a.run = os.path.join(L.RUNS, "run-%s-%d" % (time.strftime("%Y%m%d-%H%M%S"), os.getpid()))
    if not os.path.isfile(L.BINARY):
        print("retail binary not found: %s (set GAMEMD_BINARY)" % L.BINARY, file=sys.stderr)
        return 2
    ctx = Ctx(a)
    print("tree %s  base %s  mode %s  jobs %d  run %s" % (ctx.tree, ctx.base[:10], ctx.mode, ctx.jobs, ctx.run))
    print("changed paths %d; affected TUs %d of %d (by include/source %d, by manifest rows %d)%s" % (
        len(ctx.changed), len(ctx.affected), len(ctx.tus), len(ctx.by_include), len(ctx.row_tus),
        "; " + "; ".join(ctx.notes) if ctx.notes else ""))
    only = set(filter(None, a.only.split(",")))
    skip = set(filter(None, a.skip.split(",")))
    worst = 0
    for g in GATES:
        n = g.__name__
        if (only and n not in only) or n in skip:
            continue
        t = time.time()
        # ordering dependency: later gates need objects; compile always precedes them in GATES order
        try:
            status, detail = g(ctx)
        except Exception as ex:
            import traceback
            traceback.print_exc()
            status, detail = "FAIL", "exception %r" % (ex,)
        dt = time.time() - t
        ctx.results.append({"gate": n, "status": status, "secs": round(dt, 1), "detail": detail})
        print("GATE %-9s %-4s %6.1fs %s" % (n, status, dt, detail), flush=True)
        if status == "FAIL":
            worst = 1
            if a.fail_fast:
                break
    if ctx.mode == "full" and getattr(ctx, "promote", False) and not a.no_promote and worst == 0:
        for tu, st in ctx.new_obj_state.items():
            if st == "compiled":
                cache_put(ctx.new_keys[tu], objpath(ctx.objs_new, tu))
    summ = {"tree": ctx.tree, "base": ctx.base, "mode": ctx.mode, "jobs": ctx.jobs,
            "wall_secs": round(time.time() - ctx.t0, 1), "affected": ctx.affected, "tus_total": len(ctx.tus),
            "results": ctx.results, "escalate": ctx.escalate,
            "verify": getattr(ctx, "verify_summary", None), "sections": getattr(ctx, "sections_digest", None),
            "by_include": sorted(ctx.by_include), "row_tus": sorted(ctx.row_tus)}
    json.dump(summ, open(os.path.join(ctx.run, "summary.json"), "w"), indent=1)
    print("RESULT %s wall %.1fs run %s" % ("FAIL" if worst else "PASS", time.time() - ctx.t0, ctx.run))
    return worst


if __name__ == "__main__":
    sys.exit(main())
