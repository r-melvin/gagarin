#!/usr/bin/env python3
"""global_decls.py: every declaration site of every retail global, and the addresses declared inconsistently.

A global is a namespace-scope data object bound to a retail address. This tool scans match/ (.cpp, .c, .h) for
namespace-scope variable declarations (`extern T X;`, `T X = v;`, `const T X[] = {...};`) and binds each to an
address by, in order: a Ghidra-style name (DAT_/STR_/PTR_ or a trailing `_xxxxxxxx`), scripts/data/symbol_bindings.json
(by identifier; a `tu::` scoped key for that TU), then the nearest preceding `// GLOBAL|STRING: GAMEMD 0xADDR`
annotation (one address, or the i-th of a run of declarations under a multi-address annotation).

Per address it prints the definition(s) and each declaration site (file:line, name, type). An address is flagged when
the tree uses more than one distinct (name, type) for it (--flagged), or when extern declarations of it sit in more than
one file (--multi-file; the "redeclare it at the top of every TU" pattern: one header should declare it once and the TUs
include it). The last line counts addresses, addresses with more than one (name, type), and addresses with extern
declarations in more than one file. Static data, class-static members and local objects are not globals here;
`T Class::member` declarations are reported with qualified=true (global_unify.py skips them).

    global_decls.py [--tree T] [--addr 0xA ...] [--flagged] [--multi-file] [--json] [--canon FILE] [--summary]

--canon FILE (a JSON {addr: name|null}) additionally flags sites whose name differs from the canonical name
(`non-canonical`). Read-only; decides no binary fact. global_unify.py edits the tree from the same scan.
"""
import argparse
import json
import os
import re
import sys

BINDINGS = "scripts/data/symbol_bindings.json"
ANNOT = re.compile(r"^\s*(?://|;)\s*(?:Declaration:\s*)?(GLOBAL|STRING)(?:\s+GAMEMD|:\s*GAMEMD)\s+(0x[0-9A-Fa-f]+(?:\s*/\s*0x[0-9A-Fa-f]+)*)")
ANNOT2 = re.compile(r"^\s*//\s*Declaration:\s*GAMEMD\s+(0x[0-9A-Fa-f]+)")
ADDR_IN = re.compile(r"0x[0-9A-Fa-f]+")
NAME_ADDR = re.compile(r"(?:^|_)([0-9A-Fa-f]{8})[a-z]?$")
SKIP_HEAD = re.compile(r"^(typedef|class|struct|union|enum|template|using|namespace|friend|static)\b")
IDENT = re.compile(r"[A-Za-z_]\w*")
LO, HI = 0x400000, 0xC00000


def ident_of_mangled(m):
    s = m.lstrip("?") if m.startswith("?") else m.lstrip("_")
    return s.split("@", 1)[0]


def strip_code(text):
    """(code, comment_lines): comments blanked (newlines kept), strings kept as "" placeholders, preprocessor lines blanked.
    comment_lines: {lineno: comment text} for annotation pairing."""
    out = []
    comments = {}
    i, n, line = 0, len(text), 1
    bol = True
    while i < n:
        c = text[i]
        if c == "\n":
            out.append(c); line += 1; i += 1; bol = True; continue
        if bol and c in " \t#":
            j = i
            while j < n and text[j] in " \t":
                j += 1
            if text.startswith("#", j):
                while j < n and text[j] != "\n":
                    if text[j] == "\\" and j + 1 < n and text[j + 1] == "\n":
                        out.append("\n"); line += 1; j += 2; continue
                    j += 1
                i = j
                continue
        bol = False
        if c == "/" and text.startswith("//", i):
            j = text.find("\n", i)
            j = n if j < 0 else j
            comments[line] = text[i:j]
            i = j
            continue
        if c == "/" and text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            seg = text[i:j]
            comments[line] = seg.split("\n")[0]
            line += seg.count("\n")
            out.append("\n" * seg.count("\n"))
            i = j
            continue
        if c == '"' or c == "'":
            j = i + 1
            while j < n and text[j] != c and text[j] != "\n":
                j += 2 if text[j] == "\\" else 1
            out.append('""' if c == '"' else "0")
            i = j + 1
            continue
        out.append(c)
        i += 1
    return "".join(out), comments


def statements(code):
    """[(start_line, end_line, text)] namespace-scope statements. Function/class bodies are skipped; `extern "C" {` and
    `namespace N {` are entered transparently."""
    res = []
    i, n, line = 0, len(code), 1
    buf, bline = [], None
    stack = []          # True = transparent brace
    while i < n:
        c = code[i]
        if c == "\n":
            line += 1
            if buf:
                buf.append(" ")
            i += 1
            continue
        if c.isspace():
            if buf:
                buf.append(" ")
            i += 1
            continue
        if bline is None:
            bline = line
        if c == "{":
            head = "".join(buf).strip()
            if re.match(r'^(extern\s*""|namespace\b)', head) and "=" not in head:
                buf, bline = [], None
                stack.append(True)
                i += 1
                continue
            # initialiser braces belong to the statement; any other body is skipped
            init = "=" in head and not re.search(r"\)\s*$", head)
            depth, j, ln = 0, i, line
            while j < n:
                if code[j] == "{":
                    depth += 1
                elif code[j] == "}":
                    depth -= 1
                    if depth == 0:
                        break
                elif code[j] == "\n":
                    ln += 1
                j += 1
            if init:
                buf.append("{}")
                line = ln
                i = j + 1
                continue
            line = ln
            i = j + 1
            # type body (`struct S {...} s;`) continues to `;`, a function body ends the statement
            if re.match(r"^(typedef|class|struct|union|enum)\b", head) or re.search(r"\b(class|struct|union|enum)\b", head):
                buf.append("{}")
                continue
            buf, bline = [], None
            continue
        if c == "}":
            if stack:
                stack.pop()
            buf, bline = [], None
            i += 1
            continue
        if c == ";":
            res.append((bline, line, "".join(buf).strip()))
            buf, bline = [], None
            i += 1
            continue
        buf.append(c)
        i += 1
    return res


def declared_name(d):
    m = re.search(r"\(\s*[*&]\s*(?:const\s+)?([A-Za-z_]\w*)\s*\)\s*\(", d)
    if m:
        return m.group(1), m.start(1), m.end(1)
    d2 = re.sub(r"\[[^\]]*\]", lambda mm: " " * len(mm.group(0)), d)
    ms = list(IDENT.finditer(d2))
    if not ms:
        return None, 0, 0
    mm = ms[-1]
    return mm.group(0), mm.start(), mm.end()


def norm_type(t):
    t = re.sub(r"\s+", " ", t).strip()
    t = re.sub(r"\s*\*\s*", "* ", t).strip()
    t = re.sub(r"\*\s+(?=[*)\]])", "*", t)
    return re.sub(r"\s+", " ", t).strip()


def parse_decl(text):
    """dict(name, type, extern, init) for a variable declaration statement, else None."""
    t = text.strip()
    if not t or SKIP_HEAD.match(t):
        return None
    ext = False
    m = re.match(r'^extern\s*(""\s*)?', t)
    if m:
        if m.group(1) is not None:
            t = t[m.end():].strip()
            if t.startswith("extern"):
                t = t[6:].strip()
        else:
            t = t[m.end():].strip()
        ext = True
    if re.match(r"^(typedef|class|struct|union|enum|template|using|namespace|friend|static|return|goto|delete)\b", t) and "{}" not in t:
        if not re.match(r"^(class|struct|union|enum)\s+\w+\s+[\*\w]", t):
            return None
    init = False
    if "=" in t:
        t = t.partition("=")[0].strip()
        init = True
    if "(" in t and not re.search(r"\(\s*[*&]", t):
        return None
    if "{}" in t:
        return None
    name, s, e = declared_name(t)
    qualified = bool(name) and bool(re.search(r"::\s*$", t[:s]))
    if not name or name in ("const", "unsigned", "signed", "int", "char", "short", "long", "float", "double", "void"):
        return None
    ty = norm_type(t[:s] + " " + re.sub(r"\s+", "", t[e:]))
    return {"name": name, "type": ty, "extern": ext and not init, "init": init, "decl": norm_type(t), "qualified": qualified}


class Binder:
    def __init__(self, tree):
        try:
            b = json.load(open(os.path.join(tree, BINDINGS)))
        except (OSError, ValueError):
            b = {}
        self.byid = {}
        self.scoped = {}
        for k, v in b.items():
            a = int(v, 16) if isinstance(v, str) else v
            if not (LO <= a < HI):
                continue
            tu, sep, m = k.partition("::")
            if sep:
                self.scoped.setdefault((tu, ident_of_mangled(m)), a)
            elif k.startswith("?") and "@@3" in k:        # data symbol
                self.byid.setdefault(ident_of_mangled(k), set()).add(a)
            elif not k.startswith("?") and "@" not in k:
                self.byid.setdefault(k.lstrip("_"), set()).add(a)

    def addr(self, tu, name):
        a = self.scoped.get((tu, name))
        if a:
            return a
        m = NAME_ADDR.search(name)
        if m:
            v = int(m.group(1), 16)
            if LO <= v < HI:
                return v
        s = self.byid.get(name)
        if s and len(s) == 1:
            return next(iter(s))
        return None


def scan_file(tree, rel, binder, keep_all=False):
    """Declarations of a file. Each carries file, line, end, ann (line of its `// GLOBAL|STRING: GAMEMD` annotation or None),
    ann_pos (index within the annotation's run), addr (None when unresolved; only kept with keep_all)."""
    try:
        text = open(os.path.join(tree, rel), errors="replace").read()
    except OSError:
        return []
    code, comments = strip_code(text)
    out = []
    lines = code.split("\n")

    def blank(k):
        return k - 1 < len(lines) and lines[k - 1].strip() == ""
    ctx = None          # (annotation line, [addrs], next index)
    prev_end = 0
    for ln, end, st in statements(code):
        gap = list(range(prev_end + 1, ln))
        prev_end = end
        found = None
        for k in reversed([k for k in gap if comments.get(k)]):
            mm = ANNOT.match(comments[k]) or ANNOT2.match(comments[k])
            if mm:
                # the annotation belongs to this declaration only when nothing but comments lies between them
                if all(comments.get(j) for j in range(k + 1, ln)):
                    found = (k, [int(x, 16) for x in ADDR_IN.findall(mm.group(mm.lastindex))], 0)
                break
        if found:
            ctx = found
        elif any(comments.get(k) or blank(k) for k in gap):
            ctx = None
        d = parse_decl(st)
        if not d:
            ctx = None
            continue
        d["file"], d["line"], d["end"] = rel, ln, end
        a = binder.addr(rel, d["name"])
        src = "name/bindings"
        d["ann"], d["ann_pos"], d["ann_text"] = None, None, None
        if ctx:
            d["ann"], d["ann_pos"], d["ann_text"] = ctx[0], ctx[2], comments.get(ctx[0])
            if a is None:
                addrs, idx = ctx[1], ctx[2]
                if len(addrs) == 1:
                    a = addrs[0]
                elif idx < len(addrs):
                    a = addrs[idx]
                src = "annotation"
            ctx = (ctx[0], ctx[1], ctx[2] + 1)
        if a is None or not (LO <= a < HI):
            if keep_all:
                d["addr"], d["via"] = None, None
                out.append(d)
            continue
        d["addr"], d["via"] = a, src
        out.append(d)
    return out


def scan_tree(tree, binder=None):
    binder = binder or Binder(tree)
    res = {}
    for root, _, names in os.walk(os.path.join(tree, "match")):
        for n in sorted(names):
            if n.lower().endswith((".cpp", ".c", ".h")):
                rel = os.path.relpath(os.path.join(root, n), tree)
                for d in scan_file(tree, rel, binder):
                    res.setdefault(d["addr"], []).append(d)
    return res


def analyse(res, canon=None):
    rows = {}
    for a, ds in sorted(res.items()):
        sigs = {(d["name"], d["type"]) for d in ds}
        files = {d["file"] for d in ds}
        declfiles = {d["file"] for d in ds if d["extern"]}
        defs = [d for d in ds if not d["extern"]]
        flags = []
        if len(sigs) > 1:
            flags.append("signatures")
        if len({d["name"] for d in ds}) > 1:
            flags.append("names")
        if len({d["type"] for d in ds}) > 1:
            flags.append("types")
        if len(files) > 1:
            flags.append("multi-file")
        if len(declfiles) > 1:
            flags.append("multi-decl")
        if len(defs) > 1:
            flags.append("multi-def")
        if canon and a in canon and canon[a] and any(d["name"] != canon[a] for d in ds):
            flags.append("non-canonical")
        rows[a] = {"sites": ds, "sigs": len(sigs), "files": len(files), "declfiles": len(declfiles), "flags": flags}
    return rows


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
    ap.add_argument("--addr", nargs="*", default=[])
    ap.add_argument("--flagged", action="store_true", help="only addresses with more than one distinct (name, type)")
    ap.add_argument("--multi-file", action="store_true", help="only addresses with extern declarations in more than one file")
    ap.add_argument("--canon", default=None)
    ap.add_argument("--summary", action="store_true")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args(argv)
    tree = os.path.abspath(a.tree)
    canon = None
    if a.canon:
        canon = {int(k, 16): v for k, v in json.load(open(a.canon)).items()}
    rows = analyse(scan_tree(tree), canon)
    want = {int(x, 16) for x in a.addr}
    sel = {k: v for k, v in rows.items()
           if (not want or k in want)
           and (not a.flagged or v["sigs"] > 1)
           and (not a.multi_file or v["declfiles"] > 1)}
    nsig = sum(1 for v in rows.values() if v["sigs"] > 1)
    nfile = sum(1 for v in rows.values() if v["declfiles"] > 1)
    if a.json:
        json.dump({"0x%08X" % k: {"flags": v["flags"], "sites": v["sites"]} for k, v in sel.items()}, sys.stdout, indent=1)
        print()
    elif not a.summary:
        for k, v in sel.items():
            print("0x%08X  sigs=%d files=%d extern-files=%d  %s" % (k, v["sigs"], v["files"], v["declfiles"], ",".join(v["flags"])))
            for d in v["sites"]:
                print("    %s:%d  %s  %s  [%s]" % (d["file"], d["line"], "extern" if d["extern"] else "DEF   ", d["decl"], d["via"]))
    print("%d addresses; %d with more than one (name,type); %d with extern declarations in more than one file" % (len(rows), nsig, nfile),
          file=sys.stderr if a.json else sys.stdout)
    return 0


if __name__ == "__main__":
    sys.exit(main())
