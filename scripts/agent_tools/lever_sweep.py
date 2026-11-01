#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; reads only the project's own sources/objects and the pinned PE
# (through scripts/vc6/diff_retail.py).
"""lever_sweep.py: try a source rewrite ("lever") on every function and keep it only when it helps.

    lever_sweep.py --tree WT [--rules vec-count,...] [--matched] [--only ADDR ...] [--exclude-file F ...]
                   [--exclude-tu match/X.cpp ...] [--tsv OUT] [--ledger L] [--dry-run] [-j 4]

For each partial row (and, with --matched, each matched row as a safety check that the rewrite is a
no-op there) the tool finds the function body in its TU (by its `// FUNCTION: GAMEMD 0xADDR` marker),
asks every enabled rewrite rule for its sites in that body, applies the rewrite to the TU, recompiles,
and rescores with diff_retail. The rewrite is KEPT only when

    * the target row's percentage rose, and
    * every other row of the TU is no worse: each matched row is still 100 (byte-identical under
      diff_retail's relocation normalisation) and no partial row dropped.

Otherwise the file is restored. Kept rewrites accumulate (the next row starts from the kept text).
With a multi-site body the all-sites variant is tried first; if it is not a keeper, or it is a keeper
below 100, each single site is tried too and the best keeper wins.

Rules (RULES below) are data: a name, a regex finder over the body, the replacement, and the real
member the replacement needs. A rule whose accessor does not exist in the canonical vector header is
disabled (no new helpers are ever introduced). Add a lever by adding a Rule; the keep-if-better-and-
no-regression check is shared.

The TU is edited in place (so includes resolve exactly) and restored in a `finally`; --tree must
therefore be a linked git worktree you own (the main checkout is refused).

Output: a TSV (addr, before, after, kept, plus tu, rule, variant, sites, reason) on stdout / --tsv, and
one attempts-ledger row per variant (kept: status `recorded`; rejected: status `swept`, which the
ledger's cap/patience rules do not count). Needs GAMEMD_BINARY. Tests: python3 -m unittest test_lever_sweep.
"""
import argparse
import concurrent.futures as cf
import datetime
import hashlib
import json
import os
import re
import subprocess
import sys
import threading

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import attempts  # noqa: E402
import partial_triage as pt  # noqa: E402

MAX_JOBS = 4
MARKER = re.compile(r"//\s*(FUNCTION|SYNTHETIC|TEMPLATE|STUB):\s*GAMEMD\s+(0x[0-9A-Fa-f]+)")
VECTOR_HEADERS = ("match/vector_class.h", "match/_layout/vector_class.h")


# ---------------------------------------------------------------- rewrite rules
class Rule:
    """A named rewrite: `pattern` finds candidate sites in a body, `repl` is the replacement text for
    group 0 (a callable of the match), `accessor` is the real member that must exist in a vector header."""

    def __init__(self, name, pattern, repl, accessor, doc=""):
        self.name, self.pattern, self.repl, self.accessor, self.doc = name, re.compile(pattern), repl, accessor, doc

    def sites(self, body):
        """[(start, end, new_text)] in `body` (offsets within body), skipping non-reads."""
        out = []
        for m in self.pattern.finditer(body):
            if is_write_context(body, m.start(), m.end()):
                continue
            out.append((m.start(), m.end(), self.repl(m)))
        return out


def is_write_context(body, s, e):
    """True when body[s:e] is stored to, modified or address-taken (so an accessor cannot replace it)."""
    after = body[e:e + 4].lstrip()
    if re.match(r"(=(?!=)|\+\+|--|[-+*/%|&^]=|<<=|>>=|\()", after):
        return True
    ls = body.rfind("\n", 0, s) + 1
    if re.search(r"(\+\+|--|(?<!&)&(?!&))\s*[\w.>\[\]-]*$", body[ls:s]):
        return True
    return False


RULES = {
    "vec-count": Rule(
        "vec-count", r"(\.|->)Count\b", lambda m: m.group(1) + "GetCount()", "GetCount",
        "raw .Count read -> the vector's inline GetCount() (keeps source order against the vptr store)"),
    "vec-activecount": Rule(
        "vec-activecount", r"(\.|->)ActiveCount\b", lambda m: m.group(1) + "GetActiveCount()", "GetActiveCount",
        "raw .ActiveCount read -> GetActiveCount() (disabled until such a canonical accessor exists)"),
    "vec-capacity": Rule(
        "vec-capacity", r"(\.|->)Capacity\b", lambda m: m.group(1) + "GetCapacity()", "GetCapacity",
        "raw .Capacity read -> GetCapacity() (disabled until such a canonical accessor exists)"),
}


def accessor_exists(tree, accessor):
    """True when a canonical vector header declares `accessor` (a real member, never invented here)."""
    for h in VECTOR_HEADERS:
        try:
            with open(os.path.join(tree, h), encoding="latin-1") as f:
                if re.search(r"\b%s\s*\(" % re.escape(accessor), f.read()):
                    return True
        except OSError:
            pass
    return False


def enabled_rules(tree, names):
    out, skipped = [], []
    for n in names:
        if accessor_exists(tree, RULES[n].accessor):
            out.append(RULES[n])
        else:
            skipped.append(n)
    return out, skipped


# ---------------------------------------------------------------- source scanning
def skip_lexeme(src, i):
    """If src[i:] starts a comment/string/char literal return the index after it, else None."""
    c = src[i]
    if src.startswith("//", i):
        j = src.find("\n", i)
        return len(src) if j < 0 else j
    if src.startswith("/*", i):
        j = src.find("*/", i + 2)
        return len(src) if j < 0 else j + 2
    if c in "\"'":
        j = i + 1
        while j < len(src) and src[j] != c:
            j += 2 if src[j] == "\\" else 1
        return j + 1
    return None


def function_body(src, addr):
    """(start, end) of the `{ ... }` body (braces included) for the marker at `addr`, or None.

    None when there is no marker, the marker is followed by another marker or a `;` before any `{`
    (a body-less SYNTHETIC claim), or the braces never balance."""
    want = int(addr, 16)
    mk = None
    for m in MARKER.finditer(src):
        if int(m.group(2), 16) == want:
            mk = m
            break
    if mk is None:
        return None
    nxt = MARKER.search(src, mk.end())
    limit = nxt.start() if nxt else len(src)
    i = mk.end()
    # skip the rest of the marker's own line and any comment lines up to the declaration
    i = src.find("\n", i) if src.find("\n", i) >= 0 else len(src)
    paren = 0
    while i < limit:
        sk = skip_lexeme(src, i)
        if sk is not None:
            i = sk
            continue
        c = src[i]
        if c == "(":
            paren += 1
        elif c == ")":
            paren -= 1
        elif c == ";" and paren == 0:
            return None
        elif c == "{" and paren == 0:
            break
        i += 1
    else:
        return None
    start, depth = i, 0
    while i < len(src):
        sk = skip_lexeme(src, i)
        if sk is not None:
            i = sk
            continue
        if src[i] == "{":
            depth += 1
        elif src[i] == "}":
            depth -= 1
            if depth == 0:
                return start, i + 1
        i += 1
    return None


def apply_sites(src, body_span, sites):
    """Rewrite `sites` (offsets relative to the body start) in src."""
    b0, _ = body_span
    out, last = [], 0
    body = src[b0:body_span[1]]
    for s, e, new in sorted(sites):
        out.append(body[last:s])
        out.append(new)
        last = e
    out.append(body[last:])
    return src[:b0] + "".join(out) + src[body_span[1]:]


def variants(rule, body):
    """[(label, [sites])]: all sites, then each single site when there are several."""
    sites = rule.sites(body)
    if not sites:
        return []
    out = [("all", sites)]
    if len(sites) > 1:
        out += [("site%d" % (k + 1), [s]) for k, s in enumerate(sites)]
    return out


# ---------------------------------------------------------------- compile and score
def score_pct(tree, obj, row):
    """diff_retail percentage for one row against `obj`, or None when it cannot be scored."""
    p = subprocess.run([sys.executable, os.path.join(tree, "scripts", "vc6", "diff_retail.py"), "--obj", obj,
                        "--sym", row["sym"], "--addr", row["addr"], "--len", row["len"]],
                       capture_output=True, text=True, cwd=tree)
    m = re.findall(r"match: ([0-9.]+)%", p.stdout)
    return float(m[-1]) if m else None


def score_all(tree, obj, rows, score_fn):
    return {r["addr"]: score_fn(tree, obj, r) for r in rows}


def regression(base, new, target):
    """Why `new` (addr -> pct) is not an acceptable successor of `base`, or None."""
    for a, b in base.items():
        if a == target:
            continue
        n = new.get(a)
        if b is not None and (n is None or n < b - 1e-9):
            return "regressed %s %s -> %s" % (a, b, n)
    return None


def read_text(path):
    with open(path, encoding="latin-1", newline="") as f:
        return f.read()


def write_text(path, text):
    with open(path, "w", encoding="latin-1", newline="") as f:
        f.write(text)


def sweep_tu(tree, tu, rows, rules, targets, compile_fn=pt.compile_tu, score_fn=score_pct, objdir=None):
    """Sweep one TU. rows: every manifest row of the TU; targets: the addrs to try. Returns records.

    Each record: addr, tu, rule, variant, sites, before, after, kept, reason, source_sha."""
    path = os.path.join(tree, tu)
    orig = read_text(path)
    obj = pt.obj_path(objdir, tu)
    recs = []
    cur = orig

    def has_sites(addr):
        span = function_body(orig, addr)
        return span is not None and any(variants(r, orig[span[0]:span[1]]) for r in rules)

    targets = {a for a in targets if has_sites(a)}
    if not targets:
        return [], orig  # nothing to rewrite: no compile
    try:
        ok, why = compile_fn(tree, tu, obj)
        if not ok:
            return [dict(addr=a, tu=tu, rule="", variant="", sites=0, before=None, after=None, kept=False,
                         reason="baseline compile failed: " + why[:80], source_sha=None) for a in sorted(targets)], orig
        base = score_all(tree, obj, rows, score_fn)
        for row in rows:
            addr = row["addr"]
            if addr not in targets:
                continue
            for rule in rules:
                span = function_body(cur, addr)
                if span is None:
                    break
                vs = variants(rule, cur[span[0]:span[1]])
                if not vs:
                    continue
                best = None  # (after, label, text, sites, new_scores)
                tried = []
                for label, sites in vs:
                    if label != "all" and best is not None and best[0] >= 100.0 - 1e-9:
                        break
                    text = apply_sites(cur, span, sites)
                    sha = hashlib.sha256(text.encode("latin-1")).hexdigest()
                    write_text(path, text)
                    ok, why = compile_fn(tree, tu, obj)
                    rec = dict(addr=addr, tu=tu, rule=rule.name, variant=label, sites=len(sites),
                               before=base.get(addr), after=None, kept=False, reason="", source_sha=sha)
                    if not ok:
                        rec["reason"] = "compile failed: " + why[:80]
                    else:
                        new = score_all(tree, obj, rows, score_fn)
                        rec["after"] = new.get(addr)
                        reg = regression(base, new, addr)
                        b, a = base.get(addr), new.get(addr)
                        if reg:
                            rec["reason"] = reg
                        elif a is None:
                            rec["reason"] = "target not scorable"
                        elif b is not None and a <= b + 1e-9:
                            rec["reason"] = "no improvement" if a == b else "worse"
                        else:
                            rec["kept"] = True  # provisional; the best candidate is chosen below
                            if best is None or a > best[0]:
                                best = (a, label, text, sites, new)
                    tried.append(rec)
                    # all-sites already exact: no point trying singles
                    if label == "all" and rec["kept"] and rec["after"] >= 100.0 - 1e-9:
                        break
                chosen = best[1] if best else None
                for rec in tried:
                    if rec["kept"] and rec["variant"] != chosen:
                        rec["kept"], rec["reason"] = False, "a better variant (%s) won" % chosen
                if best:
                    cur = best[2]
                    base = best[4]
                write_text(path, cur)
                recs.extend(tried)
    finally:
        write_text(path, orig)
    return recs, cur


# ---------------------------------------------------------------- driver
def is_linked_worktree(tree):
    def g(arg):
        return subprocess.run(["git", "-C", tree, "rev-parse", arg], capture_output=True, text=True).stdout.strip()

    gd, cd = g("--absolute-git-dir"), g("--git-common-dir")
    cd = os.path.abspath(os.path.join(tree, cd)) if cd and not os.path.isabs(cd) else cd
    return bool(gd) and os.path.realpath(gd) != os.path.realpath(cd)


def load_exclusions(files, tus):
    out = set(tus)
    for f in files:
        with open(f) as fh:
            for line in fh:
                line = line.strip()
                if line and not line.startswith("#"):
                    out.add(line)
    return out


def ledger_row(rec, tree, agent):
    note = "lever-sweep %s/%s (%d site%s): %s" % (rec["rule"], rec["variant"], rec["sites"],
                                                   "" if rec["sites"] == 1 else "s",
                                                   "KEPT" if rec["kept"] else "rejected: " + rec["reason"])
    raw = rec["after"]
    if not rec["kept"] and rec["reason"].startswith("regressed"):
        raw = None  # an improvement that broke a neighbour must not raise the address's best
    return dict(addr=attempts.norm(rec["addr"]), tu=rec["tu"], flags=attempts.tu_flags(os.path.join(tree, rec["tu"])),
                source_sha=rec["source_sha"], variant=note, raw=raw, positional=raw, multiset=None,
                delta="before %s after %s" % (rec["before"], rec["after"]), agent=agent,
                date=datetime.date.today().isoformat(), status="recorded" if rec["kept"] else "swept")


def tsv_line(r):
    f = lambda v: "" if v is None else (("%g" % v) if isinstance(v, float) else str(v))
    return "\t".join([r["addr"], f(r["before"]), f(r["after"]), "yes" if r["kept"] else "no", r["tu"], r["rule"],
                      r["variant"], str(r["sites"]), r["reason"]])


TSV_HEAD = "addr\tbefore\tafter\tkept\ttu\trule\tvariant\tsites\treason"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=os.environ.get("GAG_WORKTREE") or REPO)
    ap.add_argument("--rules", default="vec-count", help="comma list of: " + ",".join(RULES))
    ap.add_argument("--matched", action="store_true", help="also try matched rows (safety check: must stay 100)")
    ap.add_argument("--only", nargs="*", default=[], help="restrict to these addresses")
    ap.add_argument("--exclude-file", nargs="*", default=[], help="files listing repo paths (match/X.cpp) to skip")
    ap.add_argument("--exclude-tu", nargs="*", default=[])
    ap.add_argument("--skip-addr", nargs="*", default=[], help="addresses to leave alone (e.g. a packet in flight)")
    ap.add_argument("--tsv", help="write the TSV here as well")
    ap.add_argument("--ledger", type=lambda p: p, default=str(attempts.LEDGER))
    ap.add_argument("--dry-run", action="store_true", help="restore every file, even kept rewrites; no ledger")
    ap.add_argument("--agent", default="lever-sweep")
    ap.add_argument("--out", help="scratch dir for objects (default: <scratch>/lever_sweep)")
    ap.add_argument("--limit-tus", type=int, default=0)
    ap.add_argument("-j", type=int, default=MAX_JOBS)
    ap.add_argument("--allow-main", action="store_true", help="edit the main checkout in place (do not)")
    a = ap.parse_args(argv)
    tree = os.path.abspath(a.tree)
    if not a.allow_main and not is_linked_worktree(tree):
        raise SystemExit("lever_sweep: %s is not a linked git worktree; the sweep edits TUs in place" % tree)
    scratch = os.environ.get("GAG_SCRATCH_ROOT") or os.path.join(os.path.dirname(tree), "gagarin-scratch")
    out = pt.abs_out(a.out or os.path.join(scratch, "lever_sweep"))
    names = [n for n in a.rules.split(",") if n]
    for n in names:
        if n not in RULES:
            raise SystemExit("lever_sweep: unknown rule %s (have %s)" % (n, ",".join(RULES)))
    rules, skipped = enabled_rules(tree, names)
    if skipped:
        print("disabled (no canonical accessor in the vector headers): " + ", ".join(skipped), file=sys.stderr)
    if not rules:
        raise SystemExit("lever_sweep: no enabled rule")
    with open(os.path.join(tree, "scripts", "data", "match_manifest.json")) as f:
        man = json.load(f)
    excl = load_exclusions(a.exclude_file, a.exclude_tu)
    only = {x.lower() for x in a.only}
    skip = {x.lower() for x in a.skip_addr}
    by_tu = {}
    for r in man:
        if r["tu"] in excl or r["tu"].endswith(".asm") or r["status"] not in ("partial", "matched"):
            continue
        by_tu.setdefault(r["tu"], []).append(r)
    wanted = ("partial", "matched") if a.matched else ("partial",)
    work = {}
    for tu, rows in by_tu.items():
        tg = {r["addr"] for r in rows if r["status"] in wanted and (not only or r["addr"].lower() in only)
              and r["addr"].lower() not in skip}
        if tg:
            work[tu] = (rows, tg)
    tus = sorted(work)
    if a.limit_tus:
        tus = tus[:a.limit_tus]
    print("%d TUs, %d target rows, rules %s" % (len(tus), sum(len(work[t][1]) for t in tus),
                                                 ",".join(r.name for r in rules)), file=sys.stderr)
    lock = threading.Lock()
    ledger = attempts.Path(a.ledger)
    allrecs = []
    sys.stdout.write(TSV_HEAD + "\n")

    def one(tu):
        rows, tg = work[tu]
        try:
            res = sweep_tu(tree, tu, rows, rules, tg, objdir=out)
        except Exception as exc:  # a broken TU must not stop the sweep
            return tu, [dict(addr=next(iter(tg)), tu=tu, rule="", variant="", sites=0, before=None, after=None,
                             kept=False, reason="error: %s" % exc, source_sha=None)], None
        return (tu,) + res

    with cf.ThreadPoolExecutor(max(1, min(a.j, MAX_JOBS))) as ex:
        for tu, recs, final in ex.map(one, tus):
            kept = [r for r in recs if r["kept"]]
            if kept and not a.dry_run:
                write_text(os.path.join(tree, tu), final)
            with lock:
                for r in recs:
                    sys.stdout.write(tsv_line(r) + "\n")
                sys.stdout.flush()
                if recs and not a.dry_run:
                    attempts.append(ledger, [ledger_row(r, tree, a.agent) for r in recs])
            allrecs += recs
    if a.tsv:
        with open(a.tsv, "w") as f:
            f.write(TSV_HEAD + "\n" + "".join(tsv_line(r) + "\n" for r in allrecs))
    k = [r for r in allrecs if r["kept"]]
    print("tried %d variants over %d rows; kept %d (%d reach 100)" % (
        len(allrecs), len({r["addr"] for r in allrecs}), len(k),
        sum(1 for r in k if r["after"] is not None and r["after"] >= 100.0 - 1e-9)), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
