#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original. Source scanner for the pktlint rule `unclaimed-callee` (no compiler).
"""unclaimed.py: an unannotated function definition that a matched function references.

An out-of-line function definition with no FUNCTION/SYNTHETIC/TEMPLATE/LIBRARY/STUB annotation is not
placed at a retail address. When a matched (exact) function calls it, or takes its address, the matched
function's relocation points at the linked copy, which sits past the end of retail .text: the M3 image
differs in the caller's bytes. The unannotated name must be a declaration only, so the caller binds to the
retail function.

    unclaimed.py [--repo PATH] [--rev REV]      scan a tree (default: the main checkout's HEAD)

What counts as a reference to a definition `Cls::name` (or a free `name`) in a matched body:
  * `Cls::name` written out (a direct, non-virtual call or address-of);
  * a plain `name` in a body of the same class, or anywhere when no other class defines `name`
    (a placeholder like FUN_006FDB80 is unique) -- for non-virtual `name` only;
  * a free function: `name` in a body of the same file.
A virtual slot (`vf_<n>`, or a name declared `virtual` in a header) called as `obj->name()` is a vtable
dispatch and relocates nothing, so only the `Cls::name(` form counts for it. A by-value object calling a
virtual slot (devirtualised) is the one shape this source scan cannot see; the M3 gate catches it.
"""
import argparse
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import cppscan  # noqa: E402

ANNOT = re.compile(r"^(?://|;)\s?(FUNCTION|STUB|TEMPLATE|SYNTHETIC|LIBRARY):\s*GAMEMD\s+(0x[0-9A-Fa-f]+)")
VIRT_DECL = re.compile(r"\bvirtual\b[^;{}()]*?\b(\w+)\s*\(")
KEYWORDS = {"if", "while", "for", "switch", "catch", "return", "sizeof", "else", "do", "main", "DllMain", "WinMain"}
SKIP_HEAD = re.compile(r"\b(inline|template|__forceinline|__declspec)\b")


def parse_def(header, first_line):
    """(qualifier or None, name, signature first line) of a function header, or None when it is not a plain
    named function (operator, constructor, destructor, template, inline, static initialiser)."""
    lines = header.split("\n")
    keep = [(i, l) for i, l in enumerate(lines) if not l.lstrip().startswith("#")]
    keep = [(i, l) for i, l in keep if l.strip()]
    if not keep:
        return None
    start_idx = keep[0][0]
    sig = " ".join(l for _, l in keep)
    p = sig.find("(")
    if p < 0:
        return None
    before = sig[:p].strip()
    if not before or SKIP_HEAD.search(before) or "operator" in before or before.endswith(("=", ",")):
        return None
    tok = re.split(r"\s+", before)[-1].lstrip("*&")
    if not re.fullmatch(r"(?:[A-Za-z_]\w*::)*[A-Za-z_]\w*", tok):
        return None
    parts = tok.split("::")
    fn, cls = parts[-1], (parts[-2] if len(parts) > 1 else None)
    if cls and fn == cls:
        return None
    if fn in KEYWORDS or fn.startswith("_$"):
        return None
    return cls, fn, first_line - (len(lines) - 1 - start_idx)     # FIRST_LINE: the line the header ends on


def annotation_above(lines, sig_line):
    """The (kind, addr) annotation in the comment/blank block directly above 1-based SIG_LINE, or None."""
    i = sig_line - 2
    while i >= 0:
        s = lines[i]
        if s.strip() == "" or s.lstrip().startswith("//") or s.startswith(";"):
            m = ANNOT.match(s)
            if m:
                return m.group(1), int(m.group(2), 16)
            i -= 1
            continue
        break
    return None


def parse_file(text):
    """[dict(cls, name, line, ann, body)] for each out-of-line function body of a source text."""
    lines = text.split("\n")
    code = cppscan.strip_code(text).split("\n")
    out = []
    for header, body, first, last, in_class in cppscan.function_defs(text):
        if in_class:
            continue        # an in-class definition is implicitly inline: no out-of-line copy is linked
        end = first          # cppscan gives the line of `{` and a stripped header: find the header's last line
        while end > 1 and code[end - 1].split("{")[0].strip() == "":
            end -= 1
        d = parse_def(header, end)
        if not d:
            continue
        cls, fn, line = d
        out.append(dict(cls=cls, name=fn, line=line, ann=annotation_above(lines, line), body=body))
    return out


def find(cpps, matched):
    """Source candidates [dict(file, line, sym, callers=[(file, line, addr)])]: an out-of-line definition with no
    annotation and a matched (annotated, address in MATCHED) function of the SAME file whose body names it (a plain
    or `Cls::` qualified token). Inlined helpers and virtual dispatch also look like this; `confirm` decides from
    the compiled object whether a relocation really points at the copy. CPPS is {path: text}."""
    out = []
    for path, text in cpps.items():
        fns = parse_file(text)
        callers = [c for c in fns if c["ann"] and c["ann"][1] in matched and c["ann"][0] in ("FUNCTION", "SYNTHETIC", "TEMPLATE", "STUB")]
        if not callers:
            continue
        for f in fns:
            if f["ann"]:
                continue
            cls, fn = f["cls"], f["name"]
            tok = re.compile(r"\b%s\b" % re.escape(fn))
            hits = [(path, c["line"], c["ann"][1]) for c in callers if c is not f and tok.search(c["body"])]
            if hits:
                out.append(dict(file=path, line=f["line"], sym="%s::%s" % (cls, fn) if cls else fn, name=fn, callers=hits))
    return out


# ---------------------------------------------------------------- compiled object
def coff_relocs(path):
    """({section no: (characteristics, [(offset, target symbol name)])}, [(name, section no, value, storage class)])
    of an i386 COFF object."""
    with open(path, "rb") as fh:
        d = fh.read()
    nsec = struct.unpack_from("<H", d, 2)[0]
    sptr, nsym = struct.unpack_from("<II", d, 8)
    strtab = sptr + nsym * 18
    names, syms, i = {}, [], 0
    while i < nsym:
        o = sptr + i * 18
        if d[o:o + 4] == b"\0\0\0\0":
            so = struct.unpack_from("<I", d, o + 4)[0]
            nm = d[strtab + so:d.index(b"\0", strtab + so)].decode("latin1")
        else:
            nm = d[o:o + 8].rstrip(b"\0").decode("latin1")
        val, sec = struct.unpack_from("<Ih", d, o + 8)
        scl = d[o + 16]
        names[i] = nm
        syms.append((nm, sec, val, scl))
        i += 1 + d[o + 17]
    secs = {}
    for k in range(nsec):
        o = 20 + k * 40
        chars = struct.unpack_from("<I", d, o + 36)[0]
        rptr = struct.unpack_from("<I", d, o + 24)[0]
        rcount = struct.unpack_from("<H", d, o + 32)[0]
        rel = []
        for j in range(rcount):
            ro = rptr + j * 10
            va, idx = struct.unpack_from("<II", d, ro)
            rel.append((va, names.get(idx, "?")))
        secs[k + 1] = (chars, rel)
    return secs, syms


def obj_violations(path, matched_syms, claimed_syms):
    """[(caller symbol, target symbol)]: a function of MATCHED_SYMS in the object whose code has a relocation to a
    code symbol the object itself defines and CLAIMED_SYMS (every manifest row's symbol) does not name."""
    secs, syms = coff_relocs(path)
    code = {n for n, sec, v, scl in syms if sec > 0 and secs.get(sec, (0,))[0] & 0x20 and scl in (2, 3)}
    out = []
    for n, sec, v, scl in syms:
        if n in matched_syms and sec > 0 and scl == 2 and secs.get(sec, (0,))[0] & 0x20:
            for va, tgt in secs[sec][1]:
                if tgt in code and tgt not in claimed_syms and tgt != n:
                    out.append((n, tgt))
    return sorted(set(out))


def confirm(tree_dir, cands, manifest, work, jobs=4):
    """Compile each candidate file in TREE_DIR (a worktree with the toolchain) and keep the candidates whose symbol the
    object really references from a matched function. Returns (confirmed findings, [(file, compile error)])."""
    import concurrent.futures as cf
    import dlib as D
    files = sorted({c["file"] for c in cands})
    claimed = {r["sym"] for r in manifest if r.get("sym")}
    matched_by_tu = {}
    for r in manifest:
        if r.get("status") == "matched" and r.get("sym"):
            matched_by_tu.setdefault(r.get("tu"), set()).add(r["sym"])

    def one(f):
        obj = os.path.join(work, os.path.splitext(f)[0] + ".obj")
        ok, text = D.compile_tu(tree_dir, f, obj)
        return f, ok, text, obj

    with cf.ThreadPoolExecutor(jobs) as ex:
        res = list(ex.map(one, files))
    out, bad = [], []
    for f, ok, text, obj in res:
        if not ok:
            bad.append((f, " | ".join([l for l in text.splitlines() if re.search(r"error|fatal", l, re.I)][:2])))
            continue
        hits = obj_violations(obj, matched_by_tu.get(f, set()), claimed)
        for c in cands:
            if c["file"] != f:
                continue
            ref = [(caller, tgt) for caller, tgt in hits if c["name"] in tgt]
            if ref:
                out.append(dict(c, symbols=ref))
    return out, bad


def tree_inputs(tree):
    """(cpps, matched) of a dlib.Tree."""
    cpps = {p: tree.text(p) or "" for p in tree.cpps() if p.startswith("match/")}
    matched = {a for a, r in tree.by_addr.items() if r.get("status") == "matched"}
    return cpps, matched


def describe(f):
    callers = ", ".join("%s -> %s" % c for c in f["symbols"])
    return ("%s is defined without a FUNCTION/SYNTHETIC/TEMPLATE/LIBRARY annotation and a matched function's relocation "
            "points at it (%s); linked past retail .text it breaks the image: make it a declaration only so the caller "
            "binds to the retail function" % (f["sym"], callers))


def main(argv=None):
    import tempfile
    import dlib as D
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--repo", default=D.MAIN_REPO)
    ap.add_argument("--rev", default="HEAD")
    ap.add_argument("--tree", help="worktree (with toolchain link) used to compile the candidate files; default: a scratch worktree at --rev")
    ap.add_argument("--jobs", type=int, default=4)
    a = ap.parse_args(argv)
    t = D.Tree(a.repo, a.rev)
    cands = find(*tree_inputs(t))
    print("%d source candidate(s) in %d file(s)" % (len(cands), len({c["file"] for c in cands})))
    work = D.scratch_dir("unclaimed_")
    wt = None
    try:
        tree_dir = a.tree
        if not tree_dir and cands:
            wt = tree_dir = D.add_worktree(a.repo, os.path.join(work, "wt"), t.rev)
        found, bad = confirm(tree_dir, cands, t.manifest, os.path.join(work, "obj"), a.jobs) if cands else ([], [])
    finally:
        if wt:
            D.remove_worktree(a.repo, wt)
        D.remove_dir(work)
    for f, why in bad:
        print("warning: %s does not compile: %s" % (f, why))
    for f in found:
        print("%s:%d: %s" % (f["file"], f["line"], describe(f)))
    print("unclaimed-callee: %d violation(s) in %s" % (len(found), (t.rev or t.repo)[:10]))
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main())
