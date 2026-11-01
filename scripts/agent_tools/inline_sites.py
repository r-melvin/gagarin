#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads only the user's retail gamemd.exe (GAMEMD_BINARY) and
#   scripts/data/{function_extents,match_manifest}.json.
"""Find repeated inline expansions across the retail .text.

Every engine function (function_extents.json) is disassembled once and each instruction is
normalised: registers abstracted (by width), displacements and immediates kept, call targets kept,
stack-frame displacements and out-of-body branch targets abstracted. Windows of N normalised
instructions that repeat are seeded into clusters, each cluster is grown left and right while its
sites agree, and the surviving bodies are ranked.

For every cluster the report gives the site count, the distinct containing functions, the
out-of-line copy of the same body when one exists (a function that is just the body plus
prologue/epilogue noise: the strongest evidence of the real source form), and how many containing
functions are still unmatched (partial or absent from the manifest).

    inline_sites.py [--top 20] [--min-sites 4] [--min-insns 6] [--window 5]
                    [--json OUT] [--show N] [--body] [--rebuild]

Report only; nothing is edited. The disassembly/normalisation is cached in
scripts/agent_tools/cache/inline_sites.pickle (key: image hash, options).
"""
import argparse, bisect, collections, hashlib, json, os, pickle, re, subprocess, sys, tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

REG32 = "eax ebx ecx edx esi edi ebp esp".split()
REG16 = "ax bx cx dx si di bp sp".split()
REG8 = "al bl cl dl ah bh ch dh".split()
REG_RE = re.compile(r"\b(" + "|".join(REG32 + REG16 + REG8) + r")\b")
MEM_RE = re.compile(r"\[([^\]]*)\]")
HEX_RE = re.compile(r"-?0x[0-9a-f]+")
OBJ_LINE = re.compile(r"^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s*(.*)$")
JCC = re.compile(r"^j[a-z]+$")
STACK_BASES = ("esp", "ebp")


def _regclass(m):
    r = m.group(1)
    return "R32" if r in REG32 else ("R16" if r in REG16 else "R8")


def normalise(mn, ops, addr, size, lo, hi, keep_stack=False):
    """One normalised string for an instruction at addr (len size) of a function spanning [lo, hi)."""
    if mn in ("nop", "int3", "xchg") and (not ops or ops in ("ax,ax", "eax,eax")):
        return None
    if mn == "call":
        if ops.startswith("0x"):
            return "call " + ops
        return "call " + norm_operand(ops, keep_stack)
    if mn == "jmp" or JCC.match(mn):
        if ops.startswith("0x"):
            try:
                t = int(ops, 16)
            except ValueError:
                return mn + " far"
            d = t - (addr + size)
            if lo <= t < hi and -0x60 <= d <= 0x60:
                return f"{mn} {d:+d}"
            return mn + " far"
        return mn + " " + norm_operand(ops, keep_stack)
    return mn + " " + norm_operand(ops, keep_stack)


def norm_operand(ops, keep_stack):
    def mem(m):
        inner = m.group(1)
        if not keep_stack and any(re.search(r"\b" + b + r"\b", inner) for b in STACK_BASES):
            inner = REG_RE.sub(_regclass, inner)
            inner = HEX_RE.sub("S", inner)
            return "[" + inner + "]"
        return "[" + REG_RE.sub(_regclass, inner) + "]"
    # size prefixes (dword ptr ...) stay: they are part of the shape
    ops = MEM_RE.sub(mem, ops)
    ops = REG_RE.sub(_regclass, ops)
    return ops


def disasm_blobs(pe, funcs):
    """funcs: [(addr, length)]. One objdump run over .text with everything outside the function
    extents masked to int3, so addresses are real and jump tables/data cannot desynchronise a body.
    Returns {addr: [(iaddr, size, mnemonic, operands)]}."""
    base, text = pe.sect_bytes(".text")
    img = bytearray(b"\xcc" * len(text))
    for a, n in funcs:
        img[a - base: a - base + n] = text[a - base: a - base + n]
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as f:
        f.write(img)
        path = f.name
    try:
        out = subprocess.run(["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel",
                              f"--adjust-vma={base:#x}", path], capture_output=True, text=True, check=True).stdout
    finally:
        os.unlink(path)
    starts = [a for a, _ in funcs]
    res = {a: [] for a in starts}
    for line in out.splitlines():
        m = OBJ_LINE.match(line)
        if not m:
            continue
        txt = m.group(3).strip()
        if not txt:
            continue  # continuation bytes of a long instruction
        off = int(m.group(1), 16)
        i = bisect.bisect_right(starts, off) - 1
        if i < 0 or off >= funcs[i][0] + funcs[i][1]:
            continue
        txt = re.sub(r"\s+", " ", txt)
        parts = txt.split(" ", 1)
        mn = parts[0]
        if mn in ("rep", "repz", "repnz", "lock") and len(parts) > 1:
            p2 = parts[1].split(" ", 1)
            mn = mn + " " + p2[0]
            parts = [mn, p2[1] if len(p2) > 1 else ""]
        ops = parts[1] if len(parts) > 1 else ""
        res[starts[i]].append((off, 0, mn, ops))
    return res


def fix_sizes(insns, end):
    """Sizes from consecutive addresses (the last runs to the function end)."""
    out = []
    for i, (ia, sz, mn, ops) in enumerate(insns):
        nxt = insns[i + 1][0] if i + 1 < len(insns) else end
        out.append((ia, nxt - ia, mn, ops))
    return out


def load_data(opts):
    import common
    pe = common.pe()
    ext = common.load_json("function_extents.json")
    funcs = []
    kinds = {}
    for a, n, gap, gk, kind, fl in ext["entries"]:
        a, n = int(a, 16), int(n, 16)
        kinds[a] = kind
        if kind in opts.kinds:
            funcs.append((a, n))
    funcs.sort()
    key = hashlib.sha256((common.SHA256 + repr((opts.kinds, opts.keep_stack, ext["counts"]))).encode()).hexdigest()[:16]
    cache = common.CACHE / "inline_sites.pickle"
    if cache.exists() and not opts.rebuild:
        try:
            d = pickle.loads(cache.read_bytes())
            if d["key"] == key:
                return d
        except Exception:
            pass
    raw = disasm_blobs(pe, funcs)
    vocab, table = {}, []
    fdata = []
    for a, n in funcs:
        ins = fix_sizes(raw.get(a, []), a + n)
        lo, hi = a, a + n
        toks, addrs, sizes = [], [], []
        for ia, sz, mn, ops in ins:
            s = normalise(mn, ops, ia, sz, lo, hi, opts.keep_stack)
            if s is None:
                continue
            t = vocab.get(s)
            if t is None:
                t = vocab[s] = len(table)
                table.append(s)
            toks.append(t)
            addrs.append(ia)
            sizes.append(sz)
        fdata.append((a, n, toks, addrs, sizes))
    d = {"key": key, "table": table, "funcs": fdata, "kinds": kinds}
    try:
        common.CACHE.mkdir(exist_ok=True)
        cache.write_bytes(pickle.dumps(d))
    except OSError:
        pass
    return d


def content_score(table, toks):
    """Number of instructions that carry information (memory operand, call, compare, constant)."""
    n = 0
    for t in toks:
        s = table[t]
        mn = s.split(" ", 1)[0]
        if mn in ("ret", "retn", "leave", "pop", "push") and "[" not in s and "0x" not in s:
            continue
        if mn.startswith("mov") and re.fullmatch(r"mov R\d+,R\d+", s):
            continue
        if mn.startswith("j") and "[" not in s:
            continue
        n += 1
    return n


def find_clusters(d, opts):
    funcs = d["funcs"]
    table = d["table"]
    W = opts.window
    cnt = collections.Counter()
    for fi, (a, n, toks, _, _) in enumerate(funcs):
        for i in range(len(toks) - W + 1):
            cnt[hash(tuple(toks[i:i + W]))] += 1
    rep = {h for h, c in cnt.items() if c >= opts.min_sites}
    seeds = collections.defaultdict(list)
    for fi, (a, n, toks, _, _) in enumerate(funcs):
        for i in range(len(toks) - W + 1):
            w = tuple(toks[i:i + W])
            h = hash(w)
            if h in rep:
                seeds[w].append((fi, i))
    bodies = {}
    for w, sites in seeds.items():
        if len(sites) < opts.min_sites:
            continue
        lo, hi = 0, W            # body = toks[i-lo : i+hi]
        sites = list(sites)
        while True:
            nxt = collections.Counter()
            for fi, i in sites:
                t = funcs[fi][2]
                j = i + hi
                nxt[t[j] if j < len(t) else None] += 1
            tok, c = nxt.most_common(1)[0]
            if tok is None or c < opts.min_sites or c < 0.6 * len(sites):
                break
            sites = [(fi, i) for fi, i in sites if i + hi < len(funcs[fi][2]) and funcs[fi][2][i + hi] == tok]
            hi += 1
        while True:
            prv = collections.Counter()
            for fi, i in sites:
                t = funcs[fi][2]
                j = i - lo - 1
                prv[t[j] if j >= 0 else None] += 1
            tok, c = prv.most_common(1)[0]
            if tok is None or c < opts.min_sites or c < 0.6 * len(sites):
                break
            sites = [(fi, i) for fi, i in sites if i - lo - 1 >= 0 and funcs[fi][2][i - lo - 1] == tok]
            lo += 1
        fi0, i0 = sites[0]
        body = tuple(funcs[fi0][2][i0 - lo: i0 + hi])
        if body in bodies:
            continue
        # sites as body starts; drop self-overlapping sites within one function
        starts, last = [], {}
        for fi, i in sorted(sites):
            s = i - lo
            if fi in last and s < last[fi] + len(body):
                continue
            last[fi] = s
            starts.append((fi, s))
        if len(starts) >= opts.min_sites:
            bodies[body] = starts
    # filter weak bodies
    out = []
    for body, starts in bodies.items():
        if len(body) < opts.min_insns or content_score(table, body) < opts.min_content:
            continue
        out.append([body, starts])
    # suppress sub-bodies that have no more sites than the larger body containing them
    out.sort(key=lambda x: -len(x[0]))
    kept = []
    for body, starts in out:
        sup = False
        for kb, ks in kept:
            if len(kb) > len(body) and len(starts) <= 1.25 * len(ks) and is_sub(body, kb):
                sup = True
                break
        if not sup:
            kept.append((body, starts))
    return kept


def is_sub(a, b):
    n = len(a)
    for i in range(len(b) - n + 1):
        if b[i:i + n] == a:
            return True
    return False


STROPS = re.compile(r"^(rep|repn?z?) |^(scas|movs|stos|cmps|lods)")
GLOBAL_RE = re.compile(r"0x(?:[4-9a-f][0-9a-f]{5})\b")


def classify(strs):
    """Idiom label for a body: generic compiler output that is not a source-level helper."""
    n = len(strs)
    sops = sum(1 for s in strs if STROPS.match(s))
    if sops >= 2:
        return "string-op"
    anchored = any(s.startswith("call 0x") or GLOBAL_RE.search(s) for s in strs)
    only_movs = sum(1 for s in strs if s.startswith("mov ") or s.startswith("lea ")) >= 0.85 * n
    if only_movs and not anchored:
        return "copy-chain"
    return "anchored" if anchored else "plain"


def find_out_of_line(d, body, extra):
    """Functions that are the body plus at most `extra` other instructions."""
    n = len(body)
    res = []
    for fi, (a, ln, toks, _, _) in enumerate(d["funcs"]):
        if n <= len(toks) <= n + extra:
            for i in range(len(toks) - n + 1):
                if tuple(toks[i:i + n]) == body:
                    res.append(a)
                    break
    return res


def status_map():
    import common
    st = {}
    for r in common.manifest():
        a = common.h(r["addr"])
        old = st.get(a)
        if old != "matched":
            st[a] = r["status"]
    return st, {common.h(r["addr"]): r for r in common.manifest()}


def build_report(d, clusters, opts, st=None, rows=None):
    table = d["table"]
    funcs = d["funcs"]
    if st is None:
        st, rows = status_map()
    reps = []
    for body, starts in clusters:
        fn = collections.Counter(funcs[fi][0] for fi, _ in starts)
        blocked = sorted(a for a in fn if st.get(a) != "matched")
        partial = sorted(a for a in fn if st.get(a) == "partial")
        sites = []
        for fi, s in starts:
            a, n, toks, addrs, sizes = funcs[fi]
            sites.append({"func": a, "addr": addrs[s], "end": addrs[s + len(body) - 1] + sizes[s + len(body) - 1]})
        ool = find_out_of_line(d, body, opts.ool_extra)
        reps.append({
            "insns": len(body), "sites": len(starts), "functions": len(fn),
            "blocked_functions": len(blocked), "partial_functions": len(partial),
            "score": len(body) * len(starts),
            "out_of_line": [{"addr": a, "status": st.get(a, "unclaimed"),
                             "pct": (rows.get(a) or {}).get("pct"),
                             "name": (rows.get(a) or {}).get("name")} for a in ool],
            "first_site": sites[0],
            "sites_list": sites,
            "blocked": blocked,
            "body": [table[t] for t in body],
            "label": classify([table[t] for t in body]),
        })
    return reps


def rank_key(r, how):
    if how == "blocked":
        return (-r["blocked_functions"], -r["score"])
    if how == "sites":
        return (-r["sites"], -r["insns"])
    return (-r["score"], -r["sites"])


def fmt(r, i, opts):
    lines = [f"#{i} [{r['label']}] insns={r['insns']} sites={r['sites']} functions={r['functions']} "
             f"blocked={r['blocked_functions']} (partial {r['partial_functions']}) "
             f"first={r['first_site']['addr']:#x} in {r['first_site']['func']:#x}"]
    if r["out_of_line"]:
        lines.append("   out-of-line: " + ", ".join(
            f"{o['addr']:#x} [{o['status']}{'' if o['pct'] is None else ' %s%%' % o['pct']}] {o['name'] or ''}".rstrip()
            for o in r["out_of_line"][:6]))
    bl = r["blocked"]
    lines.append("   blocked fns: " + " ".join(f"{a:#x}" for a in bl[:opts.show]) + (" ..." if len(bl) > opts.show else ""))
    if opts.body:
        lines += ["      " + s for s in r["body"]]
    return "\n".join(lines)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--top", type=int, default=20)
    ap.add_argument("--min-sites", type=int, default=4)
    ap.add_argument("--min-insns", type=int, default=6)
    ap.add_argument("--min-content", type=int, default=4)
    ap.add_argument("--window", type=int, default=5)
    ap.add_argument("--ool-extra", type=int, default=6, help="max extra instructions in an out-of-line copy")
    ap.add_argument("--kinds", default="engine")
    ap.add_argument("--keep-stack", action="store_true")
    ap.add_argument("--rank", choices=["blocked", "score", "sites"], default="blocked")
    ap.add_argument("--show", type=int, default=12)
    ap.add_argument("--body", action="store_true")
    ap.add_argument("--label", default="anchored,plain",
                    help="comma list of labels to report (anchored, plain, string-op, copy-chain, all)")
    ap.add_argument("--touch", action="append", default=[],
                    help="only clusters whose body contains this text (e.g. 0xac1b48, 'call 0x578290'); repeatable")
    ap.add_argument("--func", action="append", default=[], help="only clusters with a site in this function (hex)")
    ap.add_argument("--json")
    ap.add_argument("--rebuild", action="store_true")
    opts = ap.parse_args(argv)
    opts.kinds = tuple(opts.kinds.split(","))
    d = load_data(opts)
    clusters = find_clusters(d, opts)
    reps = build_report(d, clusters, opts)
    labels = set(opts.label.split(","))
    if "all" not in labels:
        reps = [r for r in reps if r["label"] in labels]
    for t in opts.touch:
        reps = [r for r in reps if any(t.lower() in b.lower() for b in r["body"])]
    for f in opts.func:
        fa = int(f, 16)
        reps = [r for r in reps if any(s["func"] == fa for s in r["sites_list"])]
    reps.sort(key=lambda r: rank_key(r, opts.rank))
    print(f"{len(d['funcs'])} functions, {len(clusters)} clusters, {len(reps)} shown-eligible (window {opts.window}, min sites {opts.min_sites}, "
          f"min insns {opts.min_insns}); ranked by {opts.rank}")
    for i, r in enumerate(reps[:opts.top], 1):
        print(fmt(r, i, opts))
    if opts.json:
        with open(opts.json, "w") as f:
            json.dump(reps[:max(opts.top, 200)], f, indent=1)


if __name__ == "__main__":
    main()
