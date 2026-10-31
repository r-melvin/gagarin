#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Fold static-initialiser fragment files (header_init_*, mathtbl_init_*) into the file that carries their object's name.

  init_interleave.py fold  --wt WT --dest REL --src REL... [--run DIR] [--msg-dir DIR] [--no-commit]
  init_interleave.py merge --dest FILE --src FILE...            (text step only, no manifest/git/gates)

A fragment holds the dynamic initialisers (`// SYNTHETIC: GAMEMD 0xADDR` + the definition) of one run of retail
`__xc` entries. The destination holds the other initialisers of the same object, so the fragment's chunks go in at
their retail address position among the destination's own SYNTHETIC / FUNCTION anchors (the compiler emits _$E in
source order, so source order must equal retail address order). Per fold the tool:

  1. interleaves the chunks (address order), hoists the fragment's constants/declarations in front of its first chunk,
     drops those the destination already declares, adds the includes at the top, merges `defined globals` blocks;
  2. retargets the manifest rows (`tu`) and moves the fragment's file-scoped central bindings (`SRC::key`) to DEST;
  3. builds (inc_gates), then renumbers the destination's `_$E<n>` manifest rows from the new object: the n-th
     retail-address initialiser row is the n-th `_$E` symbol in object section order (count must agree), and the
     file-scoped `_$S<n>` binding keys follow by rank; every re-keyed binding is written to binding_rekeys.json;
  4. checks that the multiset of initialiser section digests (bytes + relocation target names) of the new object
     contains that of the old destination, that every mapped row is byte-exact, that no partial
     in an affected TU scores lower, and commits only when all of that holds (otherwise `git reset --hard` in WT).

Only tracked files change, so WT must be a worktree this packet owns.
"""

import argparse
import json
import os
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

FN_RE = re.compile(r"^// FUNCTION: GAMEMD 0x([0-9A-Fa-f]+)")
SY_RE = re.compile(r"^// SYNTHETIC: GAMEMD 0x([0-9A-Fa-f]+)")
GL_BEGIN = "// BEGIN defined globals"
GL_END = "// END defined globals"


# ---------------------------------------------------------------- text step (pure, unit-tested)

def anchor(line):
    """Retail address of a function definition / synthetic anchor line, else None (decl-only FUNCTION lines excluded)."""
    m = FN_RE.match(line)
    if m and "decl" not in line:
        return int(m.group(1), 16)
    m = SY_RE.match(line)
    return int(m.group(1), 16) if m else None


def trim(lines):
    lines = list(lines)
    while lines and not lines[-1].strip():
        lines.pop()
    while lines and not lines[0].strip():
        lines.pop(0)
    return lines


def parse_fragment(text):
    """-> dict(includes, prelude, chunks[(addr, lines)], globals)."""
    L = text.split("\n")
    i = 0
    while i < len(L) and (L[i].startswith("//") and not (SY_RE.match(L[i]) or FN_RE.match(L[i]) or L[i].startswith(
            "// GLOBAL")) or not L[i].strip()):
        i += 1
    incs, body = [], []
    for l in L[i:]:
        (incs if l.startswith("#include") else body).append(l)
    glob = []
    a = next((k for k, l in enumerate(body) if l.startswith(GL_BEGIN)), None)
    if a is not None:
        b = next((k for k, l in enumerate(body) if l.startswith(GL_END)), len(body))
        glob = body[a + 1:b]
        body = body[:a] + body[b + 1:]
    sy = [k for k, l in enumerate(body) if SY_RE.match(l)]
    prelude = trim(body[:sy[0]] if sy else body)
    chunks = []
    for n, k in enumerate(sy):
        end = sy[n + 1] if n + 1 < len(sy) else len(body)
        seg = body[k:end]
        # a chunk is the SYNTHETIC line, its comment lines and the statement; text after a blank line is a tail
        cut = next((j for j, l in enumerate(seg) if not l.strip()), len(seg))
        if cut < len(seg):
            glob = glob + [""] + [x for x in seg[cut:]]
        chunks.append((int(SY_RE.match(body[k]).group(1), 16), trim(seg[:cut])))
    return {"includes": incs, "prelude": prelude, "chunks": chunks, "globals": trim(glob)}


def insert_pos(D, addr):
    """Line index before the first anchor above ADDR that follows an anchor at or below it (the files are not globally
    sorted); else before the first anchor above ADDR; else the 'defined globals' block or the end. Leading plain
    comment lines of that anchor stay with it."""
    prev, first = None, None
    for i, l in enumerate(D):
        a = anchor(l)
        if a is None:
            continue
        if a > addr and first is None:
            first = i
        if a > addr and prev is not None and prev <= addr:
            first = i
            break
        prev = a
    if first is None:
        return next((i for i, l in enumerate(D) if l.startswith(GL_BEGIN)), len(D))
    i = first
    while i > 0 and D[i - 1].startswith("//") and anchor(D[i - 1]) is None:
        i -= 1
    return i


def top_include_end(D):
    """Index of the last line of the first contiguous run of #include lines (the include block at the top)."""
    first = next((i for i, l in enumerate(D) if l.startswith("#include")), None)
    if first is None:
        return None
    last = first
    while last + 1 < len(D) and D[last + 1].startswith("#include"):
        last += 1
    return last


DECL_NAME = re.compile(r"\b((?:DAT|FUN|Map|unknown)_[0-9A-Fa-f]+)\b")


def declared_names(D):
    return set(m for l in D if not l.startswith("//") for m in DECL_NAME.findall(l.split("=")[0].split("(")[0]))


def prelude_items(prelude):
    """Split into items: leading comment lines + statement lines up to the next blank / next comment run."""
    items, cur = [], []
    for l in prelude:
        if not l.strip():
            if cur:
                items.append(cur)
            cur = []
            continue
        if cur and not l.startswith("//") and all(not x.startswith("//") for x in cur[-1:]) and cur[-1].rstrip().endswith(
                (";", "}")):
            items.append(cur)
            cur = []
        if cur and l.startswith("//") and not cur[-1].startswith("//"):
            items.append(cur)
            cur = []
        cur.append(l)
    if cur:
        items.append(cur)
    return items


def item_names(item):
    return [m for l in item if not l.startswith("//") for m in DECL_NAME.findall(l.split("=")[0].split("(")[0])]


CHUNK_DEF = re.compile(r"^(?P<type>[A-Za-z_][\w:<>* ]*?)\s+(?P<name>(?:DAT|unknown)_[0-9A-Fa-f]+)\s*(?:\(|=|;)")


def first_use(D, name):
    rx = re.compile(r"\b%s\b" % name)
    return next((i for i, l in enumerate(D) if not l.lstrip("\x00").startswith("//") and rx.search(l)), None)


def retype(D, defs):
    """DEFS {name: type} of the objects the fragment defines. In the destination's own lines (not marked \\x00):
    `extern T NAME;` with another T takes the defining type; a placeholder definition of NAME is removed (the chunk defines
    it). Returns the list of (name, old_type) changes."""
    done = []
    for name, ty in defs.items():
        i = 0
        while i < len(D):
            l = D[i]
            if l.startswith("\x00") or l.startswith("//"):
                i += 1
                continue
            m = re.match(r"^extern\s+(?P<t>.+?)\s+%s(?P<arr>\[[^\]]*\])?\s*;" % name, l)
            plain = m and re.fullmatch(r"(unsigned )?(int|short|char|long|float|double|bool)", m.group("t"))
            if m and "const" not in m.group("t") and (m.group("t") != ty or not plain):
                defn = next((k for k, x in enumerate(D) if x.startswith("\x00") and re.match(r"^\x00[\w:<>* ]+\s+%s\s*[(=;]" % name, x)), None)
                if m.group("arr"):
                    done.append((name, "ARRAY-CONFLICT"))
                elif defn is not None and defn < i:
                    del D[i]     # VC6 reads a redeclaration after the definition as a second definition
                    if i > 0 and D[i - 1].startswith("// GLOBAL"):
                        del D[i - 1]
                        i -= 1
                    done.append((name, m.group("t") + " (extern dropped)"))
                    continue
                elif m.group("t") != ty:
                    D[i] = "extern %s %s%s;" % (ty, name, m.group("arr") or "")
                    done.append((name, m.group("t")))
            elif re.match(r"^(?!extern)[A-Za-z_][\w:<>* ]*?\s+%s\s*(=[^;]*)?;" % name, l):
                del D[i]
                if i > 0 and D[i - 1].startswith("// GLOBAL"):
                    del D[i - 1]
                    i -= 1
                done.append((name, "defined"))
                continue
            i += 1
    return done


def merge_into(dest_text, frag_text, rel_prefix=None):
    """Interleave one fragment into the destination text. Returns (new_text, report)."""
    D = dest_text.split("\n")
    F = parse_fragment(frag_text)
    report = {"chunks": len(F["chunks"]), "dropped": [], "includes": [], "retyped": []}
    for inc in F["includes"]:
        if rel_prefix and inc.startswith('#include "') and not inc.startswith('#include "/'):
            inc = '#include "%s"' % os.path.normpath(os.path.join(rel_prefix, re.search(r'"(.*)"', inc).group(1)))
        end = top_include_end(D)
        if end is None:
            D[0:0] = [inc, ""]
        elif inc.strip() not in [x.strip() for x in D[:end + 1]]:
            D.insert(end + 1, inc)
            report["includes"].append(inc)
    chunks = sorted(F["chunks"], key=lambda c: c[0])
    p0 = insert_pos(D, chunks[0][0]) if chunks else insert_pos(D, 1 << 31)
    keep = []
    for item in prelude_items(F["prelude"]):
        names = item_names(item)
        if names and all((first_use(D, n) is not None and first_use(D, n) < p0) for n in names):
            report["dropped"].append(names)
            continue
        keep.append(item)
    for item in list(keep):
        for n in item_names(item):
            body = [l for l in item if not l.startswith("//")]
            if not body or "=" not in body[0]:
                continue
            later = next((k for k, l in enumerate(D) if re.match(r"^(extern\s+)?const\s+\w+\s+%s\s*=" % n, l)), None)
            if later is None:
                continue
            if D[later].startswith("extern"):
                keep[keep.index(item)] = [l if l.startswith("//") else re.sub(r"^const (\w+) (\w+) = [^;]*;", r"extern const \1 \2;", l)
                                          for l in item]
            else:
                del D[later]
                if later > 0 and D[later - 1].startswith("// GLOBAL"):
                    del D[later - 1]
    for k, item in enumerate(keep):    # a function the destination declares later with C linkage keeps that linkage
        keep[k] = [('extern "C" ' + l) if (not l.startswith("//") and ('extern "C" ' + l) in D) else l for l in item]
    pre = []
    for item in keep:
        pre += item
    first = True
    marked = []
    for addr, lines in chunks:
        p = insert_pos(D, addr)
        block = (pre + [""] if first and pre else []) + lines + [""]
        first = False
        D[p:p] = ["\x00" + x for x in block]
    if not chunks and pre:
        p = insert_pos(D, 1 << 31)
        D[p:p] = ["\x00" + x for x in pre + [""]]
    defs = {}
    for addr, lines in chunks:
        for l in lines:
            m = CHUNK_DEF.match(l)
            if m:
                defs[m.group("name")] = m.group("type").strip()
    report["retyped"] = retype(D, defs)
    D = [l.lstrip("\x00") for l in D]
    if F["globals"]:
        gs = next((i for i, l in enumerate(D) if l.startswith(GL_BEGIN)), None)
        if gs is None:
            D += ["", GL_BEGIN + " (define_globals.py)", GL_END]
            gs = len(D) - 2
        ge = next(i for i in range(gs, len(D)) if D[i].startswith(GL_END))
        whole = "\n".join(l for l in D if not l.startswith("//"))
        add, cur = [], []
        for l in F["globals"]:
            cur.append(l)
            if l.startswith("//") or not l.strip():
                continue
            names = DECL_NAME.findall(l.split("=")[0])
            defined = lambda n: re.search(r"\b%s\b\s*(=|\[)" % n, whole)
            if not (names and all(defined(n) for n in names)):
                add += cur
            cur = []
        D[ge:ge] = add
    return "\n".join(D), report


# ---------------------------------------------------------------- manifest / bindings (pure, unit-tested)

def retarget_text(manifest_text, srcs, dest):
    n = 0
    for s in srcs:
        a, b = '"tu": "%s"' % s, '"tu": "%s"' % dest
        n += manifest_text.count(a)
        manifest_text = manifest_text.replace(a, b)
    return manifest_text, n


def rekey_bindings_text(text, srcs, dest):
    """Move `SRC::key` central bindings to `DEST::key`, in place (file order kept). A key DEST already holds with the
    same value is dropped (the constant was deduplicated). Returns (text, [{old,new,addr}])."""
    data = json.loads(text)
    moved = []
    for k, v in data.items():
        src = next((s for s in srcs if k.startswith(s + "::")), None)
        if src is not None:
            moved.append({"old": k, "new": dest + "::" + k[len(src) + 2:], "addr": v})
    return apply_rekeys_text(text, moved), moved


def apply_rekeys_text(text, rekeys):
    """Rebuild the bindings object with each {old,new,addr} replaced in place; collisions with a different value fail."""
    data = json.loads(text)
    rk = {r["old"]: r for r in rekeys}
    out = {}
    for k, v in data.items():
        r = rk.get(k)
        nk = r["new"] if r else k
        if nk in out and out[nk] != v:
            raise SystemExit("binding collision %s: %s vs %s" % (nk, out[nk], v))
        out[nk] = v
    return json.dumps(out, indent=1) + "\n"


def initialiser_rekeys(bindings, dest, mapping):
    """File-scoped `DEST::_$E<n>` keys name an initialiser by its retail address; follow the renumbered row."""
    by = {int(a, 16): s for a, s in mapping.items()}
    out = []
    for k, v in bindings.items():
        m = re.fullmatch(re.escape(dest) + r"::_\$E\d+", k)
        if m and int(v, 16) in by:
            nk = dest + "::" + by[int(v, 16)]
            if nk != k:
                out.append({"old": k, "new": nk, "addr": v})
    return out


def pair_by_order(rows, syms):
    """rows: [(addr, name)] ; syms: [(section, offset, name)]. The n-th row by address is the n-th symbol by section
    order. Returns {addr: new_name} or raises ValueError when the counts differ."""
    rs = sorted(rows)
    ss = sorted(syms)
    if len(rs) != len(ss):
        raise ValueError("%d initialiser rows but %d _$E symbols" % (len(rs), len(ss)))
    return {a: s[2] for (a, _), s in zip(rs, ss)}


def renumber_rows_text(manifest_text, mapping):
    """Textual edit of the sym of the row at each addr (keeps the file's formatting)."""
    changes = []
    for addr, new in mapping.items():
        i = manifest_text.index('"addr": "%s"' % addr)
        j = manifest_text.index('"sym": "', i)
        k = manifest_text.index('"', j + 8)
        old = manifest_text[j + 8:k]
        if old != new:
            manifest_text = manifest_text[:j + 8] + new + manifest_text[k:]
            changes.append((addr, old, new))
    return manifest_text, changes


def rank_remap(old_keys, old_syms, new_syms):
    """Binding keys `_$S<n>` follow by rank: old_syms/new_syms are [(section, offset, name)] of the old/new object.
    Returns {old_name: new_name}; counts must agree."""
    o, n = sorted(old_syms), sorted(new_syms)
    if len(o) != len(n):
        raise ValueError("%d old vs %d new _$S symbols" % (len(o), len(n)))
    rank = {s[2]: i for i, s in enumerate(o)}
    return {k: n[rank[k]][2] for k in old_keys if k in rank}


def digest_multiset(syms):
    return Counter(s["digest"] for s in syms if s["name"].startswith("_$E"))


# ---------------------------------------------------------------- driver

def sh(cmd, cwd, check=False, env=None):
    p = subprocess.run(cmd, shell=isinstance(cmd, str), cwd=cwd, capture_output=True, text=True, env=env)
    if check and p.returncode:
        raise SystemExit("command failed: %s\n%s" % (cmd, p.stdout[-600:] + p.stderr[-600:]))
    return p


def read_manifest(wt):
    return json.loads((Path(wt) / "scripts/data/match_manifest.json").read_text())


def obj_path(run, side, tu):
    return Path(run) / side / (tu[:-4] + ".obj")


def init_symbols(path):
    """[{name, digest}] of the `_$E` initialisers: digest = hash of the section bytes only (relocation target names move
    with the retyped globals; the gate rows prove the targets)."""
    import hashlib
    import wwlib
    if not Path(path).exists():
        return []
    data = Path(path).read_bytes()
    secs = wwlib.sections(data)
    return [{"name": n, "digest": hashlib.sha256(wwlib.section_bytes(data, secs, s)).hexdigest()[:12]}
            for n, s, v, scl in wwlib.defined_symbols(data) if re.match(r"^_\$E\d+$", n)]


def sym_order(path, prefix):
    import wwlib
    data = Path(path).read_bytes()
    return [(s, v, n) for n, s, v, scl in wwlib.defined_symbols(data) if re.match(r"^_\$%s\d+$" % prefix, n)]


def raw_ok(wt, obj, sym, addr, length):
    p = sh(["python3", "scripts/vc6/raw_match.py", "--obj", str(obj), "--sym", sym, "--addr", "0x%X" % addr, "--len", str(length)], wt)
    return p.returncode == 0


def pct_of(wt, obj, sym, addr, length):
    p = sh(["python3", "scripts/vc6/diff_retail.py", "--obj", str(obj), "--sym", sym, "--addr", "0x%X" % addr, "--len", str(length)], wt)
    m = re.search(r"match: ([\d.]+)%", p.stdout)
    return float(m.group(1)) if m else -1.0


def place_partials(wt, obj, gap, free, ss, info, mapping):
    """Partial rows between two byte-exact neighbours take, from the free symbols of the gap, the best-scoring one each."""
    free = list(free)
    for g in gap:
        best = max(free, key=lambda k: pct_of(wt, obj, ss[k][2], g, info[g][0]))
        mapping[g] = ss[best][2]
        free.remove(best)


def run_gates(wt, run):
    p = sh("%s/scripts/agent_tools/land/inc_gates.sh --tree %s --base HEAD --jobs 4 --run %s" % (wt, wt, run), wt)
    log = p.stdout + p.stderr
    return ("RESULT PASS" in log), log


def partials_not_lower(wt, run, base_rows, new_rows):
    import concurrent.futures as cf
    sec = json.loads((Path(run) / "sections.json").read_text())
    tus = set(sec.get("changed", [])) | set(sec.get("only_base", [])) | set(sec.get("only_new", []))
    new = {r["addr"].lower(): r for r in new_rows}
    jobs = [(b, new.get(b["addr"].lower())) for b in base_rows if b["status"] == "partial"
            and (b["tu"] in tus or (new.get(b["addr"].lower()) or {}).get("tu") in tus)]

    def pct(side, r):
        p = sh(["python3", "scripts/vc6/diff_retail.py", "--obj", str(obj_path(run, side, r["tu"])), "--sym", r["sym"],
                "--addr", r["addr"], "--len", r["len"]], wt)
        m = re.search(r"match: ([\d.]+)%", p.stdout)
        return float(m.group(1)) if m else None

    def one(j):
        b, h = j
        x = pct("base", b)
        x = float(b["pct"]) if x is None else x
        return b["addr"], x, pct("new", h) if h else None

    with cf.ThreadPoolExecutor(4) as ex:
        res = list(ex.map(one, jobs))
    return [(a, x, y) for a, x, y in res if y is None or y < x], len(res)


def fold(args):
    wt = os.path.abspath(args.wt)
    dest, srcs = args.dest, args.src
    run = args.run or os.path.join(os.path.dirname(wt), "g_" + Path(dest).stem)
    mpath = Path(wt) / "scripts/data/match_manifest.json"
    bpath = Path(wt) / "scripts/data/symbol_bindings.json"
    base_rows = read_manifest(wt)
    rows_moved = [r for r in base_rows if r["tu"] in srcs]
    dtext = (Path(wt) / dest).read_text()
    rel_prefix = None
    for s in srcs:
        ftext = (Path(wt) / s).read_text()
        rp = os.path.relpath(os.path.dirname(Path(wt) / s), os.path.dirname(Path(wt) / dest))
        dtext, rep = merge_into(dtext, ftext, rp if rp != "." else None)
        print("  %s: %d chunks, dropped %s, +includes %s, retyped %s" % (os.path.basename(s), rep["chunks"], rep["dropped"], rep["includes"], rep["retyped"]))
    (Path(wt) / dest).write_text(dtext)
    mt, n = retarget_text(mpath.read_text(), srcs, dest)
    mpath.write_text(mt)
    bt, moved = rekey_bindings_text(bpath.read_text(), srcs, dest)
    bpath.write_text(bt)
    sh(["git", "rm", "-q"] + srcs, wt, check=True)
    sh(["git", "add", "-u"], wt)

    def undo(why):
        if not args.keep:
            sh(["git", "reset", "-q", "--hard", "HEAD"], wt)
        print("UNDONE:", why)
        return 1

    ok, log = run_gates(wt, run)
    Path(run + ".log").write_text(log)
    errs = sorted(set(re.findall(r"(?:error C\d+|fatal)[^\n]*", log)))
    if errs:
        return undo("compile: " + "; ".join(e[:160] for e in errs[:6]))
    new_obj = obj_path(run, "new", dest)
    if not new_obj.exists():
        return undo("no new object for " + dest)
    mrows = read_manifest(wt)
    erows = [(int(r["addr"], 16), r["sym"]) for r in mrows if r["tu"] == dest and re.fullmatch(r"_\$E\d+", r["sym"])]
    esyms = sym_order(new_obj, "E")
    try:
        mapping = pair_by_order(erows, esyms)
    except ValueError:
        # the object also holds initialisers with no row (unmatched ones): align rows to symbols in order, each pick
        # byte-exact against retail (raw_match), skipping symbols that are not the row's
        info = {int(r["addr"], 16): (r["len"], r["status"]) for r in mrows if r["tu"] == dest}
        ss = sorted(esyms)
        mapping, pos, gap = {}, 0, []
        for a, _ in sorted(erows):
            ln, status = info[a]
            if status != "matched":
                gap.append(a)       # a partial row sits between its matched neighbours
                continue
            hit = next((k for k in range(pos, len(ss)) if raw_ok(wt, new_obj, ss[k][2], a, ln)), None)
            if hit is None:
                return undo("no byte-exact _$E for row 0x%X (aligned %d of %d)" % (a, len(mapping), len(erows)))
            if gap:
                free = list(range(pos, hit))
                if len(free) < len(gap):
                    return undo("partial rows before 0x%X have no free _$E in the gap" % a)
                place_partials(wt, new_obj, gap, free, ss, info, mapping)
                gap = []
            mapping[a] = ss[hit][2]
            pos = hit + 1
        if gap:
            free = list(range(pos, len(ss)))
            if len(free) < len(gap):
                return undo("trailing partial rows have no free _$E")
            place_partials(wt, new_obj, gap, free, ss, info, mapping)
    by_addr = {int(r["addr"], 16): r["addr"] for r in mrows if r["tu"] == dest}
    mapping = {by_addr[a]: v for a, v in mapping.items()}
    mt, changes = renumber_rows_text(mpath.read_text(), mapping)
    mpath.write_text(mt)
    # file-scoped binding keys of the destination follow the renumbering: `_$E<n>` by address, `_$S<n>` by rank
    bdata = json.loads(bpath.read_text())
    rekeys = list(moved) + initialiser_rekeys(bdata, dest, mapping)
    skeys = [k.split("::", 1)[1] for k in bdata if k.startswith(dest + "::_$S")]
    if skeys:
        try:
            rm = rank_remap(skeys, sym_order(obj_path(run, "base", dest), "S"), sym_order(new_obj, "S"))
        except ValueError as e:
            return undo("_$S: " + str(e))
        rekeys += [{"old": dest + "::" + k, "new": dest + "::" + nk, "addr": bdata[dest + "::" + k]}
                   for k, nk in rm.items() if k != nk]
    bpath.write_text(apply_rekeys_text(bpath.read_text(), [r for r in rekeys if r not in moved]))
    sh(["git", "add", "-u"], wt)
    ok, log = run_gates(wt, run)
    if not ok:
        bad = sorted(set(re.findall(r"(?:REGRESSED|FAIL 0x|GATE \w+\s+FAIL)[^\n]*", log)))[:3]
        return undo("gates: %s" % [b[:200] for b in bad])
    # digests: the destination's own initialisers are unchanged in the new object (the fragments' ones are proved
    # byte-exact against retail by the gate rows), and the object holds exactly one _$E per initialiser row
    old = digest_multiset(init_symbols(obj_path(run, "base", dest)))
    new = digest_multiset(init_symbols(new_obj))
    if old - new:
        return undo("initialiser digests of the destination changed: %d missing" % sum((old - new).values()))
    expect = sum(old.values()) + len(rows_moved)
    if sum(new.values()) != expect:
        return undo("%d _$E in the object but %d expected (destination %d + %d moved rows)" % (
            sum(new.values()), expect, sum(old.values()), len(rows_moved)))
    low, npart = partials_not_lower(wt, run, base_rows, read_manifest(wt))
    if low:
        return undo("partials lower: %s" % low[:4])
    if args.no_commit:
        print("PASS (not committed): %d rows moved, %d renumbered, %d partials checked, digests equal (%d initialisers)" % (
            n, len(changes), npart, sum(new.values())))
        return 0
    hdr = re.search(r"code range \((0x[0-9a-f]+)-(0x[0-9a-f]+)\)", (Path(wt) / dest).read_text()[:3000])
    names = ", ".join(Path(s).stem for s in srcs)
    title = "Phase 4: fold %s into %s" % (names, Path(dest).name)
    body = ("%s (%s) move into %s%s, interleaved at their retail address positions among the file's own initialisers. "
            "The compiler renumbers the file's initialisers (%d rows renumbered by script in retail address order, each re-proved "
            "byte-exact; the file's own initialiser digests unchanged) and the file-scoped bindings follow the file (%d re-keyed). "
            "Bodies unchanged; %d manifest rows change their tu; no partial changes." % (
                names, " ".join(sorted(r["addr"] for r in rows_moved)), Path(dest).name,
                (", inside the object's code range %s-%s" % (hdr.group(1), hdr.group(2))) if hdr else "",
                len(changes), len(rekeys), n))
    msgf = Path(args.msg_dir or os.path.dirname(wt)) / "msg_last.txt"
    msgf.write_text("%s\n\n%s\n\nCo-Authored-By: Claude Sonnet 5.5 <noreply@anthropic.com>\n" % (title, body))
    if rekeys:
        rk = Path(os.path.dirname(wt)) / "READY" / "binding_rekeys.json"
        cur = json.loads(rk.read_text()) if rk.exists() else []
        rk.parent.mkdir(exist_ok=True)
        rk.write_text(json.dumps(cur + rekeys, indent=1))
    p = sh(["git", "commit", "-q", "-F", str(msgf)], wt)
    print("PASS", sh(["git", "log", "--oneline", "-1"], wt).stdout.strip())
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    f = sub.add_parser("fold")
    f.add_argument("--wt", required=True)
    f.add_argument("--dest", required=True)
    f.add_argument("--src", nargs="+", required=True)
    f.add_argument("--run")
    f.add_argument("--msg-dir")
    f.add_argument("--no-commit", action="store_true")
    f.add_argument("--keep", action="store_true", help="leave the failed state in WT for inspection")
    m = sub.add_parser("merge")
    m.add_argument("--dest", required=True)
    m.add_argument("--src", nargs="+", required=True)
    a = ap.parse_args(argv)
    if a.cmd == "merge":
        t = Path(a.dest).read_text()
        for s in a.src:
            t, rep = merge_into(t, Path(s).read_text())
            print(s, rep)
        Path(a.dest).write_text(t)
        return 0
    return fold(a)


if __name__ == "__main__":
    sys.exit(main())
