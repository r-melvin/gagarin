#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; reads only the project's own sources and the pinned PE.
"""Non-steering source permuter that works on the real translation unit.

decomp-permuter needs a hand-made C restatement and shim for every target and its
randomizers include casts, aliases and dead code. This tool instead mutates the
body of one function in its real .cpp using only ordinary-code edits:

  swap       swap two adjacent statements in a block
  move       move a declaration-with-initialiser earlier or later in its block
  hoist      split `T x = e;` into a block-start `T x;` and `x = e;` in place
  sink       merge `T x;` ... `x = e;` back into `T x = e;` at the assignment
  inline     remove a value temporary that is used exactly once
  ifelse     swap the arms of if/else and invert the condition
  forwhile   for (a; b; c) body  <->  a; while (b) { body c; }
  commute    swap the operands of a commutative operator (+ * & | ^ == !=)

Every candidate is compiled as the full TU (a temporary sibling file, so relative
includes resolve) and scored against retail with diff_retail's own stream
reader. Candidates that add `volatile`, `__asm` or a cast are rejected. A
zero-residual candidate is certified with diff_retail.py before it is reported.

Usage:
  source_perm.py --tu match/x.cpp --addr 0x4155F0 --sym '<mangled>' --len 0x1cd \
                 [--minutes 10] [--seed N] [--out DIR]
Writes the best body to DIR/best.cpp (whole TU) and DIR/best.txt (score).
"""
import argparse
import difflib
import hashlib
import os
import random
import re
import subprocess
import sys
import tempfile
import time

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "scripts/vc6"))
import diff_retail as dr  # noqa: E402
import residual_classify as rc  # noqa: E402

KEYWORDS = {"if", "for", "while", "switch", "do", "else", "return", "break",
            "continue", "goto", "case", "default"}


# ---------------------------------------------------------------- lexical helpers
def skip_noise(s, i):
    """If s[i:] starts a comment/string/char literal return its end, else i."""
    if s.startswith("//", i):
        j = s.find("\n", i)
        return len(s) if j < 0 else j
    if s.startswith("/*", i):
        j = s.find("*/", i + 2)
        return len(s) if j < 0 else j + 2
    if s[i] in "\"'":
        q = s[i]
        j = i + 1
        while j < len(s) and s[j] != q:
            j += 2 if s[j] == "\\" else 1
        return j + 1
    return i


def match_close(s, i):
    """s[i] is an opener; return the index of its matching closer."""
    pairs = {"(": ")", "{": "}", "[": "]"}
    stack = [pairs[s[i]]]
    j = i + 1
    while j < len(s):
        k = skip_noise(s, j)
        if k != j:
            j = k
            continue
        c = s[j]
        if c in pairs:
            stack.append(pairs[c])
        elif c == stack[-1]:
            stack.pop()
            if not stack:
                return j
        j += 1
    raise ValueError("unbalanced")


def skip_ws(s, i):
    while i < len(s):
        if s[i].isspace():
            i += 1
        elif s.startswith("//", i) or s.startswith("/*", i):
            i = skip_noise(s, i)
        else:
            break
    return i


def word_at(s, i):
    m = re.compile(r"[A-Za-z_]\w*").match(s, i)
    return m.group(0) if m else ""


def stmt_end(s, i):
    """Index just past the statement starting at s[i] (i at its first char)."""
    w = word_at(s, i)
    if s[i] == "{":
        return match_close(s, i) + 1
    if w in ("if", "for", "while", "switch"):
        j = skip_ws(s, i + len(w))
        j = match_close(s, j) + 1
        j = stmt_end(s, skip_ws(s, j))
        if w == "if":
            k = skip_ws(s, j)
            if word_at(s, k) == "else":
                j = stmt_end(s, skip_ws(s, k + 4))
        return j
    if w == "do":
        j = stmt_end(s, skip_ws(s, i + 2))
        j = skip_ws(s, j)
        j = skip_ws(s, j + 5)
        j = match_close(s, j) + 1
        return s.index(";", j) + 1
    if w in ("case", "default") or re.match(r"[A-Za-z_]\w*\s*:(?!:)", s[i:i + 80] or ""):
        if w not in KEYWORDS or w in ("case", "default"):
            return s.index(":", i) + 1
    j = i
    while j < len(s):
        k = skip_noise(s, j)
        if k != j:
            j = k
            continue
        if s[j] in "({[":
            j = match_close(s, j) + 1
            continue
        if s[j] == ";":
            return j + 1
        j += 1
    return len(s)


def split_stmts(s):
    """Split a block interior into statement strings (leading whitespace kept)."""
    out, i = [], 0
    while True:
        j = skip_ws(s, i)
        if j >= len(s):
            if s[i:]:
                out.append(s[i:])
            break
        e = stmt_end(s, j)
        out.append(s[i:e])
        i = e
    return out


def blocks(body):
    """All (open, close) brace index pairs inside body (body = '{...}')."""
    res, stack, i = [], [], 0
    while i < len(body):
        k = skip_noise(body, i)
        if k != i:
            i = k
            continue
        if body[i] == "{":
            stack.append(i)
        elif body[i] == "}":
            res.append((stack.pop(), i))
        i += 1
    return res


# ---------------------------------------------------------------- function lookup
def find_function(src, addr):
    pat = re.compile(r"//\s*(?:FUNCTION|SYNTHETIC)\s*:\s*GAMEMD\s+0x([0-9a-fA-F]+)")
    for m in pat.finditer(src):
        if int(m.group(1), 16) != addr:
            continue
        i = m.end()
        depth = 0
        while i < len(src):
            k = skip_noise(src, i)
            if k != i:
                i = k
                continue
            c = src[i]
            if c == "(":
                depth += 1
            elif c == ")":
                depth -= 1
            elif c == "{" and depth == 0:
                return i, match_close(src, i) + 1
            elif c == ";" and depth == 0:
                break
            i += 1
    raise SystemExit(f"source_perm: no function body found for {addr:#x}")


# ---------------------------------------------------------------- mutations
DECL_RE = re.compile(
    r"^\s*(?:const\s+)?(?!return\b|delete\b|goto\b|else\b)"
    r"([A-Za-z_][\w:<>]*(?:\s*\*+|\s+)\s*)(\w+)\s*(=[^;]*)?;\s*$", re.S)


def decl_of(stmt):
    m = DECL_RE.match(stmt)
    if not m or m.group(1).strip() in KEYWORDS:
        return None
    return m


def uses(stmt, name):
    return re.search(r"\b" + re.escape(name) + r"\b", stmt) is not None


def is_jump_or_label(st):
    t = st.strip()
    w = word_at(t, 0)
    return w in ("return", "break", "continue", "goto", "case", "default") or bool(
        re.match(r"\w+\s*:(?!:)", t))


def rebuild(body, o, c, parts):
    return body[:o + 1] + "".join(parts) + body[c:]


def mut_swap(body, rnd):
    cands = []
    for o, c in blocks(body):
        parts = split_stmts(body[o + 1:c])
        for i in range(len(parts) - 1):
            a, b = parts[i], parts[i + 1]
            if is_jump_or_label(a) or is_jump_or_label(b):
                continue
            da, db = decl_of(a), decl_of(b)
            if da and uses(b, da.group(2)) or db and uses(a, db.group(2)):
                continue
            # keep the leading whitespace of each slot in place
            wa, wb = re.match(r"\s*", a).group(0), re.match(r"\s*", b).group(0)
            cands.append((o, c, parts, i, wa, wb))
    if not cands:
        return None
    o, c, parts, i, wa, wb = rnd.choice(cands)
    a, b = parts[i], parts[i + 1]
    p = list(parts)
    p[i], p[i + 1] = wa + b.lstrip(), wb + a.lstrip()
    return rebuild(body, o, c, p)


def mut_move(body, rnd):
    cands = []
    for o, c in blocks(body):
        parts = split_stmts(body[o + 1:c])
        for i, st in enumerate(parts):
            d = decl_of(st)
            if not d or not d.group(3):
                continue
            name = d.group(2)
            for j in range(len(parts)):
                if j == i:
                    continue
                lo, hi = (j, i) if j < i else (i + 1, j + 1)
                between = parts[lo:hi] if j < i else parts[i + 1:j + 1]
                if is_jump_or_label(parts[j]) and j > i:
                    continue
                if j < i:
                    # moving earlier: initialiser must not read anything declared between
                    ok = all(not (decl_of(x) and uses(d.group(3), decl_of(x).group(2)))
                             for x in parts[j:i]) and not any(
                        is_jump_or_label(x) for x in parts[j:i])
                else:
                    ok = not any(uses(x, name) for x in parts[i + 1:j + 1][:0]) and not any(
                        is_jump_or_label(x) for x in parts[i + 1:j + 1])
                    # moving later: nothing crossed may use it
                    ok = ok and not any(uses(x, name) for x in parts[i + 1:j + 1])
                if ok:
                    cands.append((o, c, parts, i, j))
    if not cands:
        return None
    o, c, parts, i, j = rnd.choice(cands)
    p = list(parts)
    st = p.pop(i)
    p.insert(j, "\n    " + st.strip())
    return rebuild(body, o, c, p)


def mut_hoist(body, rnd):
    cands = []
    for o, c in blocks(body):
        parts = split_stmts(body[o + 1:c])
        for i, st in enumerate(parts):
            d = decl_of(st)
            if d and d.group(3):
                cands.append((o, c, parts, i, d))
    if not cands:
        return None
    o, c, parts, i, d = rnd.choice(cands)
    p = list(parts)
    ind = re.match(r"\s*", parts[i]).group(0)
    p[i] = f"{ind}{d.group(2)} {d.group(3)};"
    p.insert(0, f"\n    {d.group(1).strip()} {d.group(2)};")
    p[0], p[1] = p[0], p[1]
    return rebuild(body, o, c, p)


def mut_sink(body, rnd):
    cands = []
    for o, c in blocks(body):
        parts = split_stmts(body[o + 1:c])
        for i, st in enumerate(parts):
            d = decl_of(st)
            if not d or d.group(3):
                continue
            name = d.group(2)
            for j in range(i + 1, len(parts)):
                m = re.match(r"^(\s*)" + re.escape(name) + r"\s*=([^;=][^;]*);\s*$",
                             parts[j], re.S)
                if m and not any(uses(x, name) for x in parts[i + 1:j]):
                    cands.append((o, c, parts, i, j, d, m))
                    break
    if not cands:
        return None
    o, c, parts, i, j, d, m = rnd.choice(cands)
    p = list(parts)
    p[j] = f"{m.group(1)}{d.group(1).strip()} {d.group(2)} ={m.group(2)};"
    del p[i]
    return rebuild(body, o, c, p)


def mut_inline(body, rnd):
    cands = []
    for o, c in blocks(body):
        parts = split_stmts(body[o + 1:c])
        for i, st in enumerate(parts):
            d = decl_of(st)
            if not d or not d.group(3):
                continue
            name = d.group(2)
            rest = parts[i + 1:]
            n = sum(len(re.findall(r"\b" + re.escape(name) + r"\b", x)) for x in rest)
            if n == 1:
                cands.append((o, c, parts, i, d))
    if not cands:
        return None
    o, c, parts, i, d = rnd.choice(cands)
    name, init = d.group(2), d.group(3)[1:].strip()
    p = list(parts)
    del p[i]
    done = False
    for k in range(i, len(p)):
        if uses(p[k], name) and not done:
            simple = re.fullmatch(r"[\w.>\-\[\]]+|\(.*\)", init, re.S) is not None
            rep = init if simple else "(" + init + ")"
            p[k] = re.sub(r"\b" + re.escape(name) + r"\b", lambda _m: rep, p[k], count=1)
            done = True
    return rebuild(body, o, c, p)


INVERT = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}


def invert_cond(c):
    c = c.strip()
    m = re.fullmatch(r"([^<>=!&|?:()]+?)\s*(==|!=|<=|>=|<|>)\s*([^<>=!&|?:()]+)", c)
    if m:
        return f"{m.group(1).strip()} {INVERT[m.group(2)]} {m.group(3).strip()}"
    if re.fullmatch(r"![\w.>\-\[\]]+", c):
        return c[1:]
    if re.fullmatch(r"[\w.>\-\[\]]+", c):
        return "!" + c
    return f"!({c})"


def find_ifs(body):
    out = []
    i = 0
    while i < len(body):
        k = skip_noise(body, i)
        if k != i:
            i = k
            continue
        if body.startswith("if", i) and word_at(body, i) == "if" and (i == 0 or not (
                body[i - 1].isalnum() or body[i - 1] == "_")):
            p = skip_ws(body, i + 2)
            if body[p] == "(":
                pe = match_close(body, p)
                t0 = skip_ws(body, pe + 1)
                te = stmt_end(body, t0)
                e0 = skip_ws(body, te)
                if word_at(body, e0) == "else":
                    a0 = skip_ws(body, e0 + 4)
                    ae = stmt_end(body, a0)
                    out.append((i, p, pe, t0, te, a0, ae))
        i += 1
    return out


def mut_ifelse(body, rnd):
    ifs = find_ifs(body)
    if not ifs:
        return None
    i, p, pe, t0, te, a0, ae = rnd.choice(ifs)
    cond = invert_cond(body[p + 1:pe])
    then_t, else_t = body[t0:te], body[a0:ae]
    return body[:p + 1] + cond + ")" + body[pe + 1:t0] + else_t + body[te:a0] + \
        then_t + body[ae:]


def mut_forwhile(body, rnd):
    cands = []
    for m in re.finditer(r"\bfor\s*\(", body):
        p = m.end() - 1
        pe = match_close(body, p)
        hdr = body[p + 1:pe]
        parts = hdr.split(";")
        if len(parts) != 3:
            continue
        b0 = skip_ws(body, pe + 1)
        be = stmt_end(body, b0)
        if re.search(r"\bcontinue\b", body[b0:be]):
            continue
        cands.append((m.start(), p, pe, b0, be, parts))
    for m in re.finditer(r"\bwhile\s*\(", body):
        p = m.end() - 1
        if re.match(r"\s*;", body[match_close(body, p) + 1:]):
            continue  # do-while tail
        pe = match_close(body, p)
        b0 = skip_ws(body, pe + 1)
        if body[b0] != "{":
            continue
        be = stmt_end(body, b0)
        inner = split_stmts(body[b0 + 1:be - 1])
        if not inner or re.search(r"\bcontinue\b", body[b0:be]):
            continue
        last = inner[-1].strip()
        if not re.fullmatch(r"(\+\+|--)?\w+(\+\+|--)?;|\w+\s*[+\-]=\s*[^;]+;", last):
            continue
        # preceding simple statement becomes the init clause
        before = body[:m.start()].rstrip()
        ps = max(before.rfind(";"), before.rfind("{"), before.rfind("}")) + 1
        init = before[ps:].strip()
        if not init.endswith(";") or "(" in init and init.split("(")[0].strip() in KEYWORDS:
            continue
        cands.append((ps, m.start(), p, pe, b0, be, init, last, inner, "w2f"))
    if not cands:
        return None
    c = rnd.choice(cands)
    if len(c) == 10:
        ps, ws, p, pe, b0, be, init, last, inner, _ = c
        cond = body[p + 1:pe]
        new_body = "{" + "".join(inner[:-1]) + "\n    }"
        text = f"\n    for ({init.rstrip(';')}; {cond}; {last.rstrip(';')}) {new_body}"
        return body[:ps] + text + body[be:]
    fs, p, pe, b0, be, parts = c
    init, cond, inc = (x.strip() for x in parts)
    bodyt = body[b0:be]
    if bodyt.startswith("{"):
        bodyt = bodyt[:-1].rstrip() + f"\n        {inc};\n    }}"
    else:
        bodyt = "{ " + bodyt + f" {inc}; }}"
    pre = f"{init};\n    " if init else ""
    return body[:fs] + f"{pre}while ({cond or '1'}) " + bodyt + body[be:]


COMM = re.compile(r"(?<![\w.>\)\]])([A-Za-z_][\w.\-\>]*|\d+|0x[0-9a-fA-F]+)\s*"
                  r"(==|!=|\+|\*|&|\||\^)\s*([A-Za-z_][\w.\-\>]*|\d+|0x[0-9a-fA-F]+)"
                  r"(?![\w.\(\[\-]|->)")


def mut_commute(body, rnd):
    cands = []
    i = 0
    for m in COMM.finditer(body):
        s = m.start()
        # skip inside comments/strings
        j = 0
        bad = False
        while j < s:
            k = skip_noise(body, j)
            if k != j:
                if k > s:
                    bad = True
                    break
                j = k
            else:
                j += 1
        if bad:
            continue
        # operator must not be part of && || ++ -- += etc.
        before = body[max(0, m.start(2) - 1):m.start(2)]
        after = body[m.end(2):m.end(2) + 1]
        if before in "&|+=!<>" and before != "" and m.group(2) in ("&", "|", "+") :
            continue
        if after in ("&", "|", "+", "="):
            continue
        # left context must be a boundary, not a higher-precedence operator
        pre = body[:s].rstrip()
        if pre and pre[-1] in "*/%+-&|^<>" and not pre.endswith(("&&", "||")):
            continue
        cands.append(m)
    if not cands:
        return None
    m = rnd.choice(cands)
    return body[:m.start()] + f"{m.group(3)} {m.group(2)} {m.group(1)}" + body[m.end():]


MUTATIONS = [("swap", mut_swap, 6), ("move", mut_move, 4), ("hoist", mut_hoist, 2),
             ("sink", mut_sink, 3), ("inline", mut_inline, 3), ("ifelse", mut_ifelse, 4),
             ("forwhile", mut_forwhile, 3), ("commute", mut_commute, 3)]

FORBIDDEN = [re.compile(p) for p in (r"\bvolatile\b", r"\b__asm\b", r"\b_asm\b",
                                      r"\(\s*(?:unsigned\s+|signed\s+)?(?:int|char|short|long|void|float|double|bool)\s*\**\s*\)",
                                      r"\b(?:reinterpret|static|const|dynamic)_cast\b",
                                      r"\bif\s*\(\s*1\s*\)", r"\bif\s*\(\s*0\s*\)")]


def steering_count(text):
    return sum(len(p.findall(text)) for p in FORBIDDEN)


# ---------------------------------------------------------------- scoring
class Scorer:
    def __init__(self, tu, addr, sym, length):
        self.tu, self.addr, self.sym, self.length = tu, addr, sym, length
        raw = dr.ghidra_bytes(addr, length)
        self.retail = dr.raw_x86_insns(raw, addr, allow_data=True)
        self.R = [rc.dissect(m, o, set(), True) for _, _, m, o in self.retail]
        self.Rk = [self._key(x) for x in self.R]
        self.dir = os.path.dirname(os.path.join(ROOT, tu))

    @staticmethod
    def _key(d):
        return (d[0], d[1], d[2], d[3])

    def score(self, text, tag):
        name = f"zz_perm_{tag}"
        path = os.path.join(self.dir, name + ".cpp")
        obj = os.path.join(tempfile.gettempdir(), name + ".obj")
        with open(path, "w") as f:
            f.write(text)
        try:
            if os.path.exists(obj):
                os.unlink(obj)
            subprocess.run(["bash", os.path.join(ROOT, "scripts/vc6/vc6cl.sh"),
                            "/Fo" + obj, name + ".cpp"], cwd=self.dir,
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            if not os.path.exists(obj):
                return None
            try:
                comp, relocs = dr.objdump_insns(obj, self.sym)
            except SystemExit:
                return None
            dr.trim_padding(comp)
            inside = [c for c in comp if c[0] < self.length]
            if len(inside) < len(comp) and inside and inside[-1][2] in ("ret", "jmp"):
                comp = inside
            cv = rc.reloc_values(comp, relocs)
            C = [rc.dissect(m, o, cv[i], False) for i, (_, _, m, o) in enumerate(comp)]
            sm = difflib.SequenceMatcher(None, self.Rk, [self._key(x) for x in C],
                                         autojunk=False)
            matched = sum(b.size for b in sm.get_matching_blocks())
            tgt = rc.branch_targets(self.retail, self.addr)
            tgc = rc.branch_targets(comp, 0)
            bt = 0 if len(self.R) != len(C) else sum(1 for k in tgt if tgt[k] != tgc.get(k))
            return max(len(self.Rk), len(C)) - matched + bt
        finally:
            for p in (path, obj):
                if os.path.exists(p):
                    os.unlink(p)


def certify(tu_text, tu, addr, sym, length, tag):
    path = os.path.join(ROOT, os.path.dirname(tu), f"zz_cert_{tag}.cpp")
    obj = os.path.join(tempfile.gettempdir(), f"zz_cert_{tag}.obj")
    open(path, "w").write(tu_text)
    try:
        subprocess.run(["bash", os.path.join(ROOT, "scripts/vc6/vc6cl.sh"), "/Fo" + obj,
                        os.path.basename(path)], cwd=os.path.dirname(path),
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        p = subprocess.run([sys.executable, os.path.join(ROOT, "scripts/vc6/diff_retail.py"),
                            "--obj", obj, "--sym", sym, "--addr", hex(addr),
                            "--len", hex(length)], capture_output=True, text=True)
        return p.returncode == 0
    finally:
        for q in (path, obj):
            if os.path.exists(q):
                os.unlink(q)


def run(tu, addr, sym, length, minutes, seed, out):
    src = open(os.path.join(ROOT, tu)).read()
    b0, b1 = find_function(src, addr)
    base_body = src[b0:b1]
    scorer = Scorer(tu, addr, sym, length)
    rnd = random.Random(seed)
    tag = f"{os.getpid()}"
    steer0 = steering_count(base_body)
    cur, cur_score = base_body, scorer.score(src, tag)
    if cur_score is None:
        raise SystemExit("source_perm: base does not compile/score")
    best, best_score = cur, cur_score
    print(f"base score {cur_score}", flush=True)
    seen = {hashlib.md5(cur.encode()).hexdigest()}
    names, funcs, weights = zip(*MUTATIONS)
    deadline = time.time() + minutes * 60
    n = 0
    stale = idle = 0
    while time.time() < deadline and best_score > 0:
        cand = cur
        for _ in range(rnd.choice((1, 1, 1, 2, 3))):
            k = rnd.choices(range(len(funcs)), weights)[0]
            try:
                r = funcs[k](cand, rnd)
            except (ValueError, IndexError):
                r = None
            if r:
                cand = r
        h = hashlib.md5(cand.encode()).hexdigest()
        if cand == cur or h in seen or steering_count(cand) > steer0:
            idle += 1
            if idle > 3000:  # search space exhausted
                break
            continue
        idle = 0
        seen.add(h)
        n += 1
        sc = scorer.score(src[:b0] + cand + src[b1:], tag)
        if sc is None:
            continue
        if sc < cur_score or (sc == cur_score and rnd.random() < 0.5):
            cur, cur_score = cand, sc
        if sc < best_score:
            best, best_score, stale = cand, sc, 0
            print(f"[{n}] score {sc}", flush=True)
        else:
            stale += 1
        if stale > 400:  # restart from the best found
            cur, cur_score, stale = best, best_score, 0
    os.makedirs(out, exist_ok=True)
    full = src[:b0] + best + src[b1:]
    ok = False
    if best_score == 0:
        ok = certify(full, tu, addr, sym, length, tag)
    open(os.path.join(out, "best.cpp"), "w").write(full)
    open(os.path.join(out, "best.txt"), "w").write(
        f"score {best_score} certified {ok} candidates {n}\n")
    print(f"done: candidates {n} best {best_score} certified {ok}", flush=True)
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tu", required=True)
    ap.add_argument("--addr", required=True)
    ap.add_argument("--sym", required=True)
    ap.add_argument("--len", required=True)
    ap.add_argument("--minutes", type=float, default=10)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    sys.exit(run(a.tu, int(a.addr, 16), a.sym, int(a.len, 16), a.minutes, a.seed, a.out))


if __name__ == "__main__":
    main()
