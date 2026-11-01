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
  split      restore a named local that the base source already declares (the inverse
             of `inline`): `T name = init;` before the one statement that spells `init`
  earlyret   `if (c) { ...; return; } REST` -> `if (c) { ...; return; } else { REST }`
  unelse     the inverse of earlyret
  declorder  move a declaration inside a run of declarations (B6/B14 creation-order lever)
  marker     draw a resolution of a --markers template: PERM_GENERAL(a, b, c) picks one alternative,
             PERM_LINESWAP(lines) permutes commuting lines (decomp-permuter style, worker-written)

--temp 'TYPE NAME = EXPR' offers a named temporary (homm3 B14, "name a value to change its creation
order"); `split` then pulls EXPR into NAME before the one statement that spells it. It is the only way the
filter accepts a local the base does not declare. --only/--skip choose mutation names (for a row routed
as a commutative or cmp swap: --only commute,swap).

Readability / anti-steering filter (always on; there is no command-line switch to
disable it). Mutations are
built to preserve semantics: two statements are only reordered when a conservative
effects model (locals, memory, calls, jumps) proves they commute. Every candidate is
then linted against the base body and rejected when it adds a cast, `volatile`,
`register`, a pragma/preprocessor line, inline asm, a pointer alias or any local the
base did not declare, a dummy local or self-assignment, a brace block that only
scopes, a duplicated statement or helper, or an unreadably long statement.
The certified candidate's diff from the base is classified (stmt-reorder, decl-order,
named-local-split/merge, loop-form, if-else-arms, early-return-shape, operand-order)
and printed with the chain of mutations that produced it.

Every candidate is compiled as the full TU (a temporary sibling file, so relative
includes resolve) and scored against retail with diff_retail's own stream
reader. A zero-residual candidate is certified with diff_retail.py before it is
reported.

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
# Candidates are written beside the TU, so they must go into the worktree being worked,
# not the checkout this script happens to live in.
TREE = os.environ.get("GAG_WORKTREE") or ROOT
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


# ---------------------------------------------------------------- effects model
# The mutations may only reorder what provably commutes. This is a deliberately
# conservative text model, not a C++ parser: anything it cannot classify counts as
# touching memory, and a call or a jump blocks every move across it.
SCALAR_WORDS = {"const", "unsigned", "signed", "int", "char", "short", "long", "float",
                "double", "bool", "BYTE", "WORD", "DWORD", "BOOL", "UINT", "__int64"}
TYPE_WORDS = SCALAR_WORDS | {"struct", "class", "enum", "union", "new", "delete", "this",
                             "true", "false", "NULL", "sizeof", "void", "static", "extern",
                             "unsigned", "signed"}
IDENT = re.compile(r"[A-Za-z_]\w*")
CTRL_JUMP = re.compile(r"\b(?:return|break|continue|goto|case|default)\b")
ASSIGN_OP = re.compile(r"<<=|>>=|[+\-*/%&|^]=|=")
FOR_DECL = re.compile(r"\bfor\s*\(\s*(?:const\s+)?([A-Za-z_][\w:<>]*(?:\s*\*+|\s+)\s*)(\w+)\s*=")
ADDR_OF = re.compile(r"(?:^|[(,=!;{}?:]|&&|\|\||\breturn\b)\s*&\s*([A-Za-z_]\w*)")
LVALUE = re.compile(r"((?:\*+\s*)*[A-Za-z_]\w*(?:\s*(?:\.|->)\s*[A-Za-z_]\w*|\s*\[[^\[\]]*\])*)\s*$")


def mask_noise(s):
    """Comments and string/char literals replaced by spaces (length preserved)."""
    out, i = [], 0
    while i < len(s):
        k = skip_noise(s, i)
        if k != i:
            out.append(" " * (k - i))
            i = k
        else:
            out.append(s[i])
            i += 1
    return "".join(out)


def is_scalar_type(t):
    """Pointer or builtin arithmetic type: splitting its declaration cannot change a ctor call."""
    if "*" in t:
        return True
    words = re.findall(r"\w+", t)
    return bool(words) and all(w in SCALAR_WORDS for w in words)


class Info:
    """Locals/params of the function under mutation and which of them have their address taken."""

    def __init__(self, locals_=(), addr_taken=(), floats=(), params=()):
        self.params = set(params)
        self.addr_taken = set(addr_taken)
        self.locals = set(locals_) - self.addr_taken
        self.floats = set(floats)


def signature_params(src, b0):
    """Parameter names of the function whose body starts at src[b0] ('{')."""
    head = mask_noise(src[:b0]).rstrip()
    head = re.sub(r"\b(?:const|throw\s*\(\s*\))\s*$", "", head).rstrip()
    if not head.endswith(")"):
        return []
    depth, i = 0, len(head) - 1
    while i >= 0:
        if head[i] == ")":
            depth += 1
        elif head[i] == "(":
            depth -= 1
            if depth == 0:
                break
        i -= 1
    if i < 0:
        return []
    names, depth, cur = [], 0, ""
    for ch in head[i + 1:-1] + ",":
        if ch in "(<[":
            depth += 1
        elif ch in ")>]":
            depth -= 1
        if ch == "," and depth == 0:
            ids = [w for w in IDENT.findall(re.sub(r"\[[^\]]*\]|=.*", "", cur)) if w not in TYPE_WORDS]
            if ids and cur.strip() not in ("void", "..."):
                names.append(ids[-1])
            cur = ""
        else:
            cur += ch
    return names


def build_info(body, params=()):
    names, floats = set(params), set()
    masked = mask_noise(body)
    for o, c in blocks(body):
        for st in split_stmts(body[o + 1:c]):
            d = decl_of(st)
            if d:
                names.add(d.group(2))
                if re.search(r"\b(?:float|double)\b", d.group(1)):
                    floats.add(d.group(2))
    for m in FOR_DECL.finditer(masked):
        names.add(m.group(2))
        if re.search(r"\b(?:float|double)\b", m.group(1)):
            floats.add(m.group(2))
    return Info(names, ADDR_OF.findall(masked), floats, params)


class Eff:
    __slots__ = ("ids", "writes", "mem_r", "mem_w", "call", "barrier", "nwrites")

    def __init__(self):
        self.nwrites = 0
        self.ids, self.writes = set(), set()
        self.mem_r = self.mem_w = self.call = self.barrier = False


def effects(stmt, info):
    """Conservative read/write summary of one statement (compound statements are opaque)."""
    e = Eff()
    t = re.sub(r"\bsizeof\s*\([^()]*\)", "0", mask_noise(stmt)).strip()
    if CTRL_JUMP.search(t) or re.match(r"\w+\s*:(?!:)", t):
        e.barrier = True
    d = decl_of(stmt)
    skip = set()
    if d:
        skip = set(IDENT.findall(d.group(1)))
        e.writes.add(d.group(2))
        e.ids.add(d.group(2))
        if not is_scalar_type(d.group(1)):
            e.call = True  # a class-typed declaration runs a constructor
    for m in ASSIGN_OP.finditer(t):
        op = m.group(0)
        if op == "=" and m.start() > 0 and t[m.start() - 1] in "=!<>":
            continue
        if op == "=" and m.end() < len(t) and t[m.end()] == "=":
            continue
        e.nwrites += 1
        lv = LVALUE.search(t[:m.start()])
        if lv and re.fullmatch(IDENT.pattern, lv.group(1)) and lv.group(1) in info.locals:
            before = t[:lv.start()].rstrip()
            if before[-1:] in (".", ">"):
                e.mem_w = True
            else:
                e.writes.add(lv.group(1))
        else:
            e.mem_w = True
    for m in re.finditer(r"(\+\+|--)\s*([A-Za-z_]\w*)|([A-Za-z_]\w*)\s*(\+\+|--)", t):
        nm = m.group(2) or m.group(3)
        e.nwrites += 1
        member = t[:m.start(2) if m.group(2) else m.start(3)].rstrip().endswith((".", "->"))
        if m.group(2) and re.match(r"\s*(?:\.|->|\[)", t[m.end():]):
            member = True
        if nm in info.locals and not member:
            e.writes.add(nm)
        else:
            e.mem_w = True
    if "->" in t or "[" in t or re.search(r"(?:^|[(,=!;{}?:+\-*/%&|^<>])\s*\*", t):
        e.mem_r = True
    for m in IDENT.finditer(t):
        w = m.group(0)
        prev = t[:m.start()].rstrip()
        if prev.endswith(".") or prev.endswith("->"):
            e.mem_r = True
            continue
        if w in skip or w in KEYWORDS or w in TYPE_WORDS:
            if w in ("new", "delete"):
                e.call = True
            continue
        if t[m.end():].lstrip().startswith("("):
            e.call = True
        elif w in info.locals:
            e.ids.add(w)
        else:
            e.mem_r = True
    return e


def commutes(a, b):
    """True when statements with effects a and b may run in either order."""
    if a.barrier or b.barrier:
        return False
    if a.writes & b.ids or b.writes & a.ids:
        return False
    if (a.mem_w or a.call) and (b.mem_r or b.mem_w or b.call):
        return False
    if (b.mem_w or b.call) and (a.mem_r or a.mem_w or a.call):
        return False
    return True


# ---------------------------------------------------------------- mutation context
DUMMY_NAME = re.compile(r"(?:tmp|temp|dummy|unused|var|val|v|t|x|y|z|a|b|c)\d*|\w*(?:dummy|unused|junk)\w*", re.I)


class Ctx:
    info = Info()
    pool = []        # (type, name, init, hinted) scalar temporaries the search may name
    allowed_new = set()  # hinted names the base does not declare (the only new locals lint accepts)
    template = None  # PERM_ marker template of the function body, or None


CTX = Ctx()


def parse_temp(spec):
    """'TYPE NAME = EXPR' -> (type, name, expr); the type must be scalar and the name must say what it holds."""
    m = re.fullmatch(r"\s*(.+?[\s*])\s*([A-Za-z_]\w*)\s*=\s*(.+?)\s*;?\s*", spec, re.S)
    if not m:
        raise ValueError("--temp wants 'TYPE NAME = EXPR': " + spec)
    typ, name, expr = m.group(1).strip(), m.group(2), m.group(3)
    if not is_scalar_type(typ):
        raise ValueError("--temp type must be a pointer or builtin arithmetic type: " + typ)
    if DUMMY_NAME.fullmatch(name):
        raise ValueError("--temp name %r does not say what the value is; pick a descriptive name" % name)
    return typ, name, expr


def set_context(base_body, params=(), temps=(), template=None):
    """Bind the function being mutated: its locals, the base's named temporaries and any hinted ones."""
    CTX.info = build_info(base_body, params)
    CTX.pool, CTX.allowed_new = [], set()
    CTX.template = template
    declared = declared_names(base_body)
    for o, c in blocks(base_body):
        for st in split_stmts(base_body[o + 1:c]):
            d = decl_of(st)
            if d and d.group(3) and is_scalar_type(d.group(1)):
                CTX.pool.append((d.group(1).strip(), d.group(2), d.group(3)[1:].strip(), False))
    for spec in temps:
        typ, name, expr = parse_temp(spec)
        if name in declared or name in set(IDENT.findall(mask_noise(base_body))):
            raise ValueError("--temp name %r is already used in the function" % name)
        CTX.pool.append((typ, name, expr, True))
        CTX.allowed_new.add(name)


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


def block_parts(body, o, c):
    """Statements of the block body[o]..body[c], without the whitespace before the closing brace."""
    return [x for x in split_stmts(body[o + 1:c]) if x.strip()]


def rebuild(body, o, c, parts):
    inner = body[o + 1:c]
    tail = inner[len(inner.rstrip()):]
    return body[:o + 1] + "".join(parts) + tail + body[c:]


def mut_swap(body, rnd):
    info = CTX.info
    cands = []
    for o, c in blocks(body):
        parts = block_parts(body, o, c)
        for i in range(len(parts) - 1):
            a, b = parts[i], parts[i + 1]
            if is_jump_or_label(a) or is_jump_or_label(b):
                continue
            if not commutes(effects(a, info), effects(b, info)):
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
    info = CTX.info
    cands = []
    for o, c in blocks(body):
        parts = block_parts(body, o, c)
        for i, st in enumerate(parts):
            d = decl_of(st)
            if not d or not d.group(3):
                continue
            ei = effects(st, info)
            for j in range(len(parts)):
                if j == i:
                    continue
                crossed = parts[j:i] if j < i else parts[i + 1:j + 1]
                if all(commutes(ei, effects(x, info)) for x in crossed):
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
        parts = block_parts(body, o, c)
        for i, st in enumerate(parts):
            d = decl_of(st)
            if d and d.group(3) and is_scalar_type(d.group(1)):
                cands.append((o, c, parts, i, d))
    if not cands:
        return None
    o, c, parts, i, d = rnd.choice(cands)
    p = list(parts)
    ind = re.match(r"\s*", parts[i]).group(0)
    p[i] = f"{ind}{d.group(2)} {d.group(3)};"
    p.insert(0, f"\n    {d.group(1).strip()} {d.group(2)};")
    return rebuild(body, o, c, p)


def mut_sink(body, rnd):
    cands = []
    for o, c in blocks(body):
        parts = block_parts(body, o, c)
        for i, st in enumerate(parts):
            d = decl_of(st)
            if not d or d.group(3) or not is_scalar_type(d.group(1)):
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


PURE_INIT_BAD = re.compile(r"\+\+|--|[A-Za-z_]\w*\s*\(|(?<![=!<>])=(?!=)|<<=|>>=|[+\-*/%&|^]=")


def init_is_pure(init):
    """An initialiser that may be evaluated later/earlier: no call, no side effect."""
    return not PURE_INIT_BAD.search(mask_noise(init))


def head_of(st):
    """The part of a statement evaluated before any nested statement runs, or None if it is a loop/block/jump."""
    t = st.strip()
    w = word_at(t, 0)
    if w in ("if", "switch"):
        p = skip_ws(t, len(w))
        if p >= len(t) or t[p] != "(":
            return None
        return t[:match_close(t, p) + 1]
    if w in ("for", "while", "do") or t.startswith("{"):
        return None
    if CTRL_JUMP.search(mask_noise(t)) and w != "return":
        return None
    return t


def use_site_ok(st, name, init, info, for_split=False):
    """May `init` be evaluated at statement `st`'s use of `name` (inline) or just before `st` (split)?"""
    head = head_of(st)
    if head is None:
        return False
    t = st.strip()
    if word_at(t, 0) in ("if", "switch") and uses(t[len(head):], name):
        return False
    eh, ei = effects(head, info), effects("x = " + init + ";", info)
    ids_init = {x for x in IDENT.findall(mask_noise(init)) if x in info.locals}
    if eh.writes & ids_init:
        return False
    if ei.mem_r and (eh.call or (eh.mem_w and eh.nwrites > 1)):
        return False  # a store that precedes the use inside the statement could change what init reads
    if for_split and ei.mem_r and re.search(r"&&|\|\||\?", mask_noise(head)):
        return False  # would turn a guarded load into an unconditional one
    return True


def mut_inline(body, rnd):
    info = CTX.info
    cands = []
    for o, c in blocks(body):
        parts = block_parts(body, o, c)
        for i, st in enumerate(parts):
            d = decl_of(st)
            if not d or not d.group(3) or not is_scalar_type(d.group(1)):
                continue
            name = d.group(2)
            init = d.group(3)[1:].strip()
            if not init_is_pure(init) or name in info.addr_taken:
                continue
            rest = parts[i + 1:]
            if sum(len(re.findall(r"\b" + re.escape(name) + r"\b", x)) for x in rest) != 1:
                continue
            k = next(n for n, x in enumerate(rest) if uses(x, name)) + i + 1
            if not use_site_ok(parts[k], name, init, info):
                continue
            ei = effects(st, info)
            if all(commutes(ei, effects(x, info)) for x in parts[i + 1:k]):
                cands.append((o, c, parts, i, d, k))
    if not cands:
        return None
    o, c, parts, i, d, k = rnd.choice(cands)
    name, init = d.group(2), d.group(3)[1:].strip()
    p = list(parts)
    simple = re.fullmatch(r"[\w.>\-\[\]]+|\(.*\)", init, re.S) is not None
    rep = init if simple else "(" + init + ")"
    p[k] = re.sub(r"\b" + re.escape(name) + r"\b", lambda _m: rep, p[k], count=1)
    del p[i]
    return rebuild(body, o, c, p)


def declared_names(body):
    out = set()
    for o, c in blocks(body):
        for st in block_parts(body, o, c):
            d = decl_of(st)
            if d:
                out.add(d.group(2))
    out.update(m.group(2) for m in FOR_DECL.finditer(mask_noise(body)))
    return out


def first_use(masked, name):
    m = re.search(r"\b" + re.escape(name) + r"\b", masked)
    return m.start() if m else -1


def lone_call_site(head, init, rx, info):
    """A hinted temporary that calls: hoisting is order-safe only when nothing else in the statement
    reads memory, calls, or writes memory except the single store of an assignment."""
    rest = rx.sub("0", head, count=1)
    rest = re.sub(r"^\s*(?:[A-Za-z_][\w.>\-\[\]]*|\*+\s*[A-Za-z_]\w*)\s*=(?!=)", "", rest)  # the store comes last
    er = effects(rest, info)
    return not (er.call or er.mem_r or (er.mem_w and er.nwrites > 1)) and not (
        effects("x = " + init + ";", info).barrier)


def mut_split(body, rnd):
    """Name a temporary: re-introduce a local the base declares (the inverse of `inline`), or one the
    worker named with --temp (homm3 B14: naming a value changes pseudo-creation order)."""
    info = CTX.info
    have = declared_names(body)
    masked = mask_noise(body)
    present = set(IDENT.findall(masked))
    cands = []
    for typ, name, init, hinted in CTX.pool:
        if name in have or name in present or not init:
            continue
        if not init_is_pure(init) and not hinted:
            continue
        ids = {x for x in IDENT.findall(mask_noise(init)) if x in info.locals and x not in info.params}
        rx = re.compile(r"(?<![\w.>])" + re.escape(init) + r"(?![\w])")
        for o, c in blocks(body):
            parts = block_parts(body, o, c)
            for k, st in enumerate(parts):
                head = head_of(st)
                if head is None or not rx.search(head):
                    continue
                pos = o + 1 + sum(len(x) for x in parts[:k])
                # every local the initialiser reads must already be declared before this statement
                if any(not 0 <= first_use(masked, i) < pos for i in ids):
                    continue
                if init_is_pure(init):
                    if not use_site_ok(st, name, init, info, for_split=True):
                        continue
                elif not lone_call_site(head, init, rx, info):
                    continue
                cands.append((o, c, parts, k, typ, name, init, rx))
    if not cands:
        return None
    o, c, parts, k, typ, name, init, rx = rnd.choice(cands)
    p = list(parts)
    ind = re.match(r"\s*", parts[k]).group(0)
    new_st = rx.sub(lambda _m: name, parts[k].lstrip(), count=1)
    p[k] = f"{ind}{typ} {name} = {init};\n    " + new_st
    return rebuild(body, o, c, p)


def mut_declorder(body, rnd):
    """Move one declaration to another position inside a run of consecutive declarations
    (initialised or not); declaration order is a register/frame-slot lever (B6, B14)."""
    info = CTX.info
    cands = []
    for o, c in blocks(body):
        parts = block_parts(body, o, c)
        i = 0
        while i < len(parts):
            if not decl_of(parts[i]):
                i += 1
                continue
            j = i
            while j < len(parts) and decl_of(parts[j]):
                j += 1
            run = range(i, j)
            for a in run:
                ea = effects(parts[a], info)
                for b in run:
                    if a == b:
                        continue
                    crossed = parts[b:a] if b < a else parts[a + 1:b + 1]
                    if all(commutes(ea, effects(x, info)) for x in crossed):
                        cands.append((o, c, parts, a, b))
            i = j
    if not cands:
        return None
    o, c, parts, a, b = rnd.choice(cands)
    p = list(parts)
    st = p.pop(a)
    p.insert(b, st)
    return rebuild(body, o, c, p)


# ---- manual alternatives (decomp-permuter style PERM_GENERAL / PERM_LINESWAP)
PERM_MARK = re.compile(r"PERM_(GENERAL|LINESWAP)\s*\(")


def split_top_commas(s):
    out, depth, cur, i = [], 0, "", 0
    while i < len(s):
        k = skip_noise(s, i)
        if k != i:
            cur += s[i:k]
            i = k
            continue
        ch = s[i]
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
        i += 1
    out.append(cur)
    return out


def expand_markers(text, rnd=None):
    """Resolve PERM_GENERAL(a, b, ...) to one alternative and PERM_LINESWAP(lines) to a permutation of
    its lines that keeps every reordered pair commuting. rnd=None gives the first alternative/original order."""
    out, i = [], 0
    while True:
        m = PERM_MARK.search(text, i)
        if not m:
            out.append(text[i:])
            return "".join(out)
        out.append(text[i:m.start()])
        p = m.end() - 1
        q = match_close(text, p)
        inner = text[p + 1:q]
        if m.group(1) == "GENERAL":
            alts = split_top_commas(inner)
            pick = alts[0] if rnd is None else rnd.choice(alts)
            out.append(expand_markers(pick.strip(), rnd))
        else:
            lines = [ln for ln in inner.split("\n") if ln.strip()]
            order = list(range(len(lines)))
            if rnd is not None:
                effs = [effects(ln, CTX.info) for ln in lines]
                for _ in range(30):
                    perm = list(range(len(lines)))
                    rnd.shuffle(perm)
                    pos = {v: k for k, v in enumerate(perm)}
                    if all(commutes(effs[a], effs[b]) for a in range(len(lines)) for b in range(a + 1, len(lines))
                           if pos[a] > pos[b]):
                        order = perm
                        break
            out.append("\n".join(lines[k] for k in order))
        i = q + 1


def mut_marker(body, rnd):
    """Draw a fresh resolution of the worker's PERM_ template (a manual alternative list)."""
    if not CTX.template:
        return None
    return expand_markers(CTX.template, rnd)


def parse_if(st):
    """(cond_end, then_start, then_end, else_start, else_end) of an `if` statement, else None."""
    t0 = skip_ws(st, 0)
    if word_at(st, t0) != "if":
        return None
    p = skip_ws(st, t0 + 2)
    if p >= len(st) or st[p] != "(":
        return None
    pe = match_close(st, p)
    a0 = skip_ws(st, pe + 1)
    ae = stmt_end(st, a0)
    e0 = skip_ws(st, ae)
    if word_at(st, e0) == "else":
        b0 = skip_ws(st, e0 + 4)
        return pe, a0, ae, b0, stmt_end(st, b0)
    return pe, a0, ae, None, None


def arm_returns(arm):
    arm = arm.strip()
    if arm.startswith("{"):
        inner = [x for x in split_stmts(arm[1:-1]) if x.strip()]
        return bool(inner) and word_at(inner[-1].strip(), 0) == "return"
    return word_at(arm, 0) == "return"


def mut_earlyret(body, rnd):
    """`if (c) { ...return; } REST`  ->  `if (c) { ...return; } else { REST }` (tail of the block only)."""
    cands = []
    for o, c in blocks(body):
        parts = block_parts(body, o, c)
        for i, st in enumerate(parts[:-1]):
            pi = parse_if(st)
            if not pi or pi[3] is not None or not arm_returns(st[pi[1]:pi[2]]):
                continue
            rest = parts[i + 1:]
            if any(word_at(x.strip(), 0) in ("case", "default") or re.match(r"\s*\w+\s*:(?!:)", x)
                   for x in rest):
                continue
            cands.append((o, c, parts, i, pi))
    if not cands:
        return None
    o, c, parts, i, pi = rnd.choice(cands)
    rest = parts[i + 1:]
    if len(rest) == 1 and not decl_of(rest[0]) and not rest[0].strip().startswith("{"):
        text = " else " + rest[0].strip()
    else:
        text = " else {" + "".join(rest) + "\n    }"
    p = list(parts[:i]) + [parts[i].rstrip() + text]
    return rebuild(body, o, c, p)


def mut_unelse(body, rnd):
    """`if (c) { ...return; } else { REST }`  ->  `if (c) { ...return; } REST`."""
    cands = []
    for o, c in blocks(body):
        parts = block_parts(body, o, c)
        for i, st in enumerate(parts):
            pi = parse_if(st)
            if not pi or pi[3] is None or not arm_returns(st[pi[1]:pi[2]]):
                continue
            cands.append((o, c, parts, i, pi))
    if not cands:
        return None
    o, c, parts, i, pi = rnd.choice(cands)
    st = parts[i]
    arm = st[pi[3]:pi[4]]
    if arm.startswith("{"):
        inner = arm[1:-1]
    else:
        inner = "\n    " + arm
    then_part = st[:pi[2]]
    p = list(parts[:i]) + [then_part, inner] + list(parts[i + 1:])
    return rebuild(body, o, c, p)


INVERT = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}


def invert_cond(c, floats=()):
    c = c.strip()
    isfloat = bool(re.search(r"\d\.\d|\d[fF]\b", c)) or any(uses(c, f) for f in floats)
    m = re.fullmatch(r"([^<>=!&|?:()]+?)\s*(==|!=|<=|>=|<|>)\s*([^<>=!&|?:()]+)", c)
    if m and not (isfloat and m.group(2) in ("<", ">", "<=", ">=")):
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


def dangling_else_risk(arm):
    """An unbraced arm that ends in an if without else would capture the `else` that follows it."""
    a = arm.strip()
    if a.startswith("{"):
        return False
    return word_at(a, 0) in ("if", "for", "while")


def mut_ifelse(body, rnd):
    ifs = [x for x in find_ifs(body) if not dangling_else_risk(body[x[5]:x[6]])]
    if not ifs:
        return None
    i, p, pe, t0, te, a0, ae = rnd.choice(ifs)
    cond = invert_cond(body[p + 1:pe], CTX.info.floats)
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
        inner = [x for x in split_stmts(body[b0 + 1:be - 1]) if x.strip()]
        if not inner or re.search(r"\bcontinue\b", body[b0:be]):
            continue
        last = inner[-1].strip()
        if not re.fullmatch(r"(\+\+|--)?\w+(\+\+|--)?;|\w+\s*[+\-]=\s*[^;]+;", last):
            continue
        # preceding simple statement becomes the init clause
        before = body[:m.start()].rstrip()
        if not before.endswith(";"):
            continue
        core = before[:-1]
        ps = max(core.rfind(";"), core.rfind("{"), core.rfind("}")) + 1
        init = before[ps:].strip()
        if word_at(init, 0) in KEYWORDS or decl_of(init) and not decl_of(init).group(3):
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
BIN_RANK = [("*", 13), ("/", 13), ("%", 13), ("+", 12), ("-", 12), ("<<", 11), (">>", 11),
            ("<=", 10), (">=", 10), ("<", 10), (">", 10), ("==", 9), ("!=", 9), ("&&", 3),
            ("||", 2), ("&", 7), ("^", 6), ("|", 5), ("?", 1)]
NEXT_OP = re.compile(r"(<<|>>|<=|>=|==|!=|&&|\|\||[*/%+\-<>&^|?])")


def rank_of(op):
    return dict(BIN_RANK).get(op, 0)


def mut_commute(body, rnd):
    cands = []
    masked = mask_noise(body)
    for m in COMM.finditer(masked):
        s = m.start()
        # operator must not be part of && || ++ -- += etc.
        before = masked[max(0, m.start(2) - 1):m.start(2)]
        after = masked[m.end(2):m.end(2) + 1]
        if before in "&|+=!<>" and before != "" and m.group(2) in ("&", "|", "+"):
            continue
        if after in ("&", "|", "+", "="):
            continue
        # left context must be a boundary, not a unary or higher-precedence operator
        pre = masked[:s].rstrip()
        if pre and pre[-1] in "*/%+-&|^<>!~" and not pre.endswith(("&&", "||")):
            continue
        # a tighter-binding operator to the right owns the right operand
        nx = NEXT_OP.match(masked[m.end():].lstrip())
        if nx and rank_of(nx.group(1)) > rank_of(m.group(2)):
            continue
        # `Type *name` / `Type &name` at a statement start is a declaration, not arithmetic
        if m.group(2) in ("*", "&") and (not pre or pre[-1] in ";{}") and re.match(
                r"\s*[=;,)]", masked[m.end():]):
            continue
        if m.group(1) in TYPE_WORDS or m.group(3) in TYPE_WORDS:
            continue
        cands.append(m)
    if not cands:
        return None
    m = rnd.choice(cands)
    return body[:m.start()] + f"{m.group(3)} {m.group(2)} {m.group(1)}" + body[m.end():]


MUTATIONS = [("swap", mut_swap, 6), ("move", mut_move, 4), ("hoist", mut_hoist, 2),
             ("sink", mut_sink, 3), ("inline", mut_inline, 3), ("split", mut_split, 3),
             ("ifelse", mut_ifelse, 4), ("earlyret", mut_earlyret, 2), ("unelse", mut_unelse, 2),
             ("forwhile", mut_forwhile, 3), ("commute", mut_commute, 3), ("declorder", mut_declorder, 3),
             ("marker", mut_marker, 4)]

FORBIDDEN = [re.compile(p) for p in (r"\bvolatile\b", r"\b__asm\b", r"\b_asm\b",
                                      r"\(\s*(?:unsigned\s+|signed\s+)?(?:int|char|short|long|void|float|double|bool)\s*\**\s*\)",
                                      r"\b(?:reinterpret|static|const|dynamic)_cast\b",
                                      r"\bif\s*\(\s*1\s*\)", r"\bif\s*\(\s*0\s*\)")]


def steering_count(text):
    return sum(len(p.findall(text)) for p in FORBIDDEN)


# ---------------------------------------------------------------- readability / anti-steering filter
CAST_BODY = re.compile(
    r"\(\s*(?:const\s+)?(?:(?:unsigned|signed|struct|class|enum)\s+)?"
    r"(?:(?:int|char|short|long|float|double|bool|void|BYTE|WORD|DWORD|BOOL|UINT|__int64|size_t)(?:\s*\*+)?"
    r"|[A-Za-z_][\w:]*\s*\*+|[A-Za-z_][\w:]*(?:Class|Type|_t))\s*\)\s*(?=[A-Za-z_0-9(&*\-~!\"'])")


def count_casts(t):
    """Parenthesised-type casts. `f(int) x`, `if (T) x` and `sizeof(T) * n` are not casts."""
    n = 0
    for m in CAST_BODY.finditer(t):
        prev = t[:m.start()].rstrip()
        mw = re.search(r"(\w+)$", prev)
        if (mw and mw.group(1) not in ("return", "case")) or prev.endswith((")", "]")):
            continue
        n += 1
    return n


def _rx_count(rx):
    return lambda t: len(rx.findall(t))


_RULES = (
    ("volatile", re.compile(r"\bvolatile\b")),
    ("register", re.compile(r"\bregister\b")),
    ("asm", re.compile(r"\b_?_asm\b")),
    ("perm-marker", re.compile(r"\bPERM_\w+")),
    ("preprocessor", re.compile(r"(?m)^\s*#")),
    ("c++-cast", re.compile(r"\b(?:reinterpret|static|const|dynamic)_cast\b")),
    ("c-cast", count_casts),
    ("const-condition", re.compile(r"\bif\s*\(\s*(?:1|0|true|false)\s*\)")),
    ("self-assignment", re.compile(r"\b(\w+)\s*=\s*\1\s*;")),
    ("helper-definition", re.compile(r"\b(?:static|inline|__forceinline|template|struct|class|namespace)\b")),
    ("function-shaped-block", re.compile(
        r"\b(?!(?:if|for|while|switch|catch|else|return)\b)\w+\s*\([^;{}()]*\)\s*(?:const\s*)?\{")),
)


LOCAL_RULES = tuple((n, r if callable(r) else _rx_count(r)) for n, r in _RULES)


def _stmt_norm(s):
    return re.sub(r"\s+", "", mask_noise(s))


def _simple_statements(body):
    out = []
    for o, c in blocks(body):
        for st in split_stmts(body[o + 1:c]):
            t = st.strip()
            if t.endswith(";") and word_at(t, 0) not in ("if", "for", "while", "switch", "do", "else"):
                n = _stmt_norm(t)
                if len(n) >= 6:
                    out.append(n)
    return out


def _bare_blocks(body):
    n = 0
    for o, c in blocks(body):
        for st in split_stmts(body[o + 1:c]):
            if st.lstrip().startswith("{"):
                n += 1
    return n


def _name_uses(body):
    masked = mask_noise(body)
    cnt = {}
    for w in IDENT.findall(masked):
        cnt[w] = cnt.get(w, 0) + 1
    return cnt


def lint_candidate(base, cand, max_stmt=140, max_depth=6):
    """Reasons a mutated body is not an ordinary-code rewrite of the base body (empty list = fine)."""
    why = []
    mb, mc = mask_noise(base), mask_noise(cand)
    for name, count in LOCAL_RULES:
        if count(mc) > count(mb):
            why.append(f"adds {name}")
    new_names = declared_names(cand) - declared_names(base) - CTX.allowed_new
    if new_names:
        why.append("adds local(s) the base does not declare: " + ", ".join(sorted(new_names)))
    ub, uc = _name_uses(base), _name_uses(cand)
    for n in declared_names(cand):
        if uc.get(n, 0) <= 1 and ub.get(n, 0) > 1:
            why.append(f"local {n} becomes unused")
    if _bare_blocks(cand) > _bare_blocks(base):
        why.append("adds a bare block (scope only)")
    from collections import Counter
    cb, cc = Counter(_simple_statements(base)), Counter(_simple_statements(cand))
    dup = [k for k, v in cc.items() if v > cb.get(k, 0) and cb.get(k, 0) >= 1]
    if dup:
        why.append("duplicates a statement: " + dup[0][:40])
    base_stmts = set(cb)
    for st in cc:
        if st not in base_stmts and len(st) > max_stmt:
            why.append("statement longer than %d characters" % max_stmt)
            break
    depth = mx = 0
    for ch in mc:
        if ch == "(":
            depth += 1
            mx = max(mx, depth)
        elif ch == ")":
            depth -= 1
    depth = mxb = 0
    for ch in mb:
        if ch == "(":
            depth += 1
            mxb = max(mxb, depth)
        elif ch == ")":
            depth -= 1
    if mx > max(max_depth, mxb):
        why.append("parenthesis nesting deeper than %d" % max_depth)
    return why


def _decls_with_init(body):
    out = {}
    for o, c in blocks(body):
        for st in split_stmts(body[o + 1:c]):
            d = decl_of(st)
            if d:
                out[d.group(2)] = bool((d.group(3) or "").strip())
    return out


def _all_statements(body):
    out = []
    for o, c in blocks(body):
        for st in split_stmts(body[o + 1:c]):
            t = st.strip()
            if t:
                out.append(_stmt_norm(t))
    return out


def classify_diff(base, cand):
    """Mutation classes visible in the diff between two bodies (heuristic, ordered, may be several)."""
    if base == cand:
        return ["identical"]
    mb, mc = mask_noise(base), mask_noise(cand)
    classes = []
    cnt = lambda rx, t: len(re.findall(rx, t))  # noqa: E731
    if (cnt(r"\bfor\b", mb), cnt(r"\bwhile\b", mb)) != (cnt(r"\bfor\b", mc), cnt(r"\bwhile\b", mc)):
        classes.append("loop-form")
    if cnt(r"\belse\b", mb) != cnt(r"\belse\b", mc):
        classes.append("early-return-shape")
    else:
        conds = lambda t: sorted(re.sub(r"\s+", "", x) for x in re.findall(r"\bif\s*\((.*?)\)\s*[\{a-z]", t))  # noqa: E731
        if conds(mb) != conds(mc) and cnt(r"\belse\b", mb):
            classes.append("if-else-arms")
    db, dc = _decls_with_init(base), _decls_with_init(cand)
    lost, gained = set(db) - set(dc), set(dc) - set(db)
    if gained or any(db[n] and not dc[n] for n in db if n in dc):
        classes.append("named-local-split")
    if lost or any(dc[n] and not db[n] for n in db if n in dc):
        classes.append("named-local-merge")
    sb, sc = _all_statements(base), _all_statements(cand)
    if sb != sc and sorted(sb) == sorted(sc):
        sm = difflib.SequenceMatcher(None, sb, sc, autojunk=False)
        moved = set()
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag != "equal":
                moved.update(sb[i1:i2])
        only_decl = all(re.match(r"^(?:const)?[A-Za-z_][\w:<>]*\**\w+(=[^;]*)?;$", x) and
                        not x.startswith(("return", "delete")) for x in moved)
        classes.append("decl-order" if only_decl else "stmt-reorder")
    elif sb != sc:
        key = lambda x: "".join(sorted(re.findall(r"[A-Za-z_]\w*|\d+|[^\sA-Za-z_\d]", x)))  # noqa: E731
        if sorted(map(key, sb)) == sorted(map(key, sc)):
            classes.append("operand-order")
    return sorted(set(classes), key=classes.index) or ["other"]


def diff_text(base, cand):
    return "".join(difflib.unified_diff(base.splitlines(True), cand.splitlines(True),
                                        "base", "candidate", n=2))


# ---------------------------------------------------------------- scoring
class Scorer:
    def __init__(self, tu, addr, sym, length):
        self.tu, self.addr, self.sym, self.length = tu, addr, sym, length
        raw = dr.ghidra_bytes(addr, length)
        self.retail = dr.raw_x86_insns(raw, addr, allow_data=True)
        self.R = [rc.dissect(m, o, set(), True) for _, _, m, o in self.retail]
        self.Rk = [self._key(x) for x in self.R]
        self.dir = os.path.dirname(os.path.join(TREE, tu))

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
    path = os.path.join(TREE, os.path.dirname(tu), f"zz_cert_{tag}.cpp")
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


def run(tu, addr, sym, length, minutes, seed, out, filt=True, only=(), skip=(), temps=(), markers=None):
    src = open(os.path.join(TREE, tu)).read()
    b0, b1 = find_function(src, addr)
    base_body = src[b0:b1]
    template = None
    if markers:
        template = open(markers).read().strip()
        if re.sub(r"\s+", "", expand_markers(template)) != re.sub(r"\s+", "", base_body):
            print("WARNING: the first alternative of the --markers template differs from the source body", flush=True)
    set_context(base_body, signature_params(src, b0), temps, template)
    scorer = Scorer(tu, addr, sym, length)
    rnd = random.Random(seed)
    tag = f"{os.getpid()}"
    steer0 = steering_count(base_body)
    cur, cur_score = base_body, scorer.score(src, tag)
    if cur_score is None:
        raise SystemExit("source_perm: base does not compile/score")
    best, best_score = cur, cur_score
    cur_hist, best_hist = [], []
    print(f"base score {cur_score}", flush=True)
    if not filt:
        print("WARNING: readability filter OFF; results are diagnostics, not landable", flush=True)
    seen = {hashlib.md5(cur.encode()).hexdigest()}
    avail = [m for m in MUTATIONS if (not only or m[0] in only) and m[0] not in skip
             and (m[0] != "marker" or template)]
    if not avail:
        raise SystemExit("source_perm: no mutation left after --only/--skip (known: %s)" % ", ".join(m[0] for m in MUTATIONS))
    names, funcs, weights = zip(*avail)
    deadline = time.time() + minutes * 60
    n = 0
    stale = idle = 0
    rejected = {}
    while time.time() < deadline and best_score > 0:
        cand, hist = cur, []
        for _ in range(rnd.choice((1, 1, 1, 2, 3))):
            k = rnd.choices(range(len(funcs)), weights)[0]
            try:
                r = funcs[k](cand, rnd)
            except (ValueError, IndexError):
                r = None
            if r:
                cand = r
                hist.append(names[k])
        h = hashlib.md5(cand.encode()).hexdigest()
        if cand == cur or h in seen or steering_count(cand) > steer0:
            idle += 1
            if idle > 3000:  # search space exhausted
                break
            continue
        if filt:
            why = lint_candidate(base_body, cand)
            if why:
                seen.add(h)
                for w in why:
                    rejected[w.split(":")[0]] = rejected.get(w.split(":")[0], 0) + 1
                continue
        idle = 0
        seen.add(h)
        n += 1
        sc = scorer.score(src[:b0] + cand + src[b1:], tag)
        if sc is None:
            continue
        if sc < cur_score or (sc == cur_score and rnd.random() < 0.5):
            cur, cur_score, cur_hist = cand, sc, cur_hist + hist
        if sc < best_score:
            best, best_score, stale = cand, sc, 0
            best_hist = cur_hist
            print(f"[{n}] score {sc}", flush=True)
        else:
            stale += 1
        if stale > 400:  # restart from the best found
            cur, cur_score, stale, cur_hist = best, best_score, 0, best_hist
    os.makedirs(out, exist_ok=True)
    full = src[:b0] + best + src[b1:]
    ok = False
    if best_score == 0:
        # last gate: the certified text must still be an ordinary-code rewrite of the base
        if filt and lint_candidate(base_body, best):
            print("source_perm: certified candidate fails the readability filter: "
                  + "; ".join(lint_candidate(base_body, best)), flush=True)
        else:
            ok = certify(full, tu, addr, sym, length, tag)
    open(os.path.join(out, "best.cpp"), "w").write(full)
    classes = classify_diff(base_body, best)
    open(os.path.join(out, "best.txt"), "w").write(
        f"score {best_score} certified {ok} candidates {n} filter {'on' if filt else 'OFF'}\n"
        f"classes {','.join(classes)}\nmutations {','.join(best_hist) or '-'}\n")
    open(os.path.join(out, "best.diff"), "w").write(diff_text(base_body, best))
    print(f"done: candidates {n} best {best_score} certified {ok}", flush=True)
    if rejected:
        print("filter rejected: " + ", ".join(f"{k} x{v}" for k, v in sorted(rejected.items())), flush=True)
    if best is not base_body:
        label = "certified candidate" if ok else "best candidate (not certified)"
        print(f"{label}: classes [{', '.join(classes)}]; mutation chain [{', '.join(best_hist) or '-'}]", flush=True)
        print(diff_text(base_body, best), flush=True)
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
    ap.add_argument("--only", default="", help="comma list of mutation names to use (e.g. commute,swap)")
    ap.add_argument("--skip", default="", help="comma list of mutation names to leave out")
    ap.add_argument("--temp", action="append", default=[], metavar="'TYPE NAME = EXPR'",
                    help="a named temporary the search may introduce (the only new locals the filter accepts); "
                         "the name must say what the value is")
    ap.add_argument("--markers", metavar="FILE",
                    help="function body with PERM_GENERAL(a, b, ...) / PERM_LINESWAP(lines) alternatives; "
                         "its first alternatives must equal the current body; landed text never contains markers")
    a = ap.parse_args()
    sys.exit(run(a.tu, int(a.addr, 16), a.sym, int(a.len, 16), a.minutes, a.seed,
                 os.path.abspath(a.out), filt=True,
                 only=[x for x in a.only.split(",") if x], skip=[x for x in a.skip.split(",") if x],
                 temps=a.temp, markers=a.markers))


if __name__ == "__main__":
    main()
