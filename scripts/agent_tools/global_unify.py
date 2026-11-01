#!/usr/bin/env python3
"""global_unify.py: declare a retail global once, in one shared header, and make every TU use it.

    global_unify.py plan  ADDRS.json|0xA.. --headers MAP.json [--canon FILE] --out PLAN.json
    global_unify.py apply PLAN.json [--only 0xA..] [--skip 0xA..]
    global_unify.py check PLAN.json --base OBJDIR --new OBJDIR [--ignore-bss] [--drop-file F]
    global_unify.py bisect PLAN.json --tu match/X.cpp --base OBJDIR --work DIR --reset SCRIPT [--ignore-bss]
    global_unify.py bindings PLAN.json --new OBJDIR [--base OBJDIR] [--apply]
    global_unify.py rekeys PLAN.json --new OBJDIR --pre REV --post REV --out PACKET_DIR

plan   per address: one canonical name (the canon map {addr: name|null}, else the name every site agrees on, else the
       single binary-attested name, else DAT_/STR_<ADDR>; two attested names is ambiguous), one canonical declaration
       (the definition's own type, else the most common site type), the shared header (MAP.json: [[lo, hi, header, why]])
       and what its type needs: class and struct names are forward declared with the keyword their definition uses, class
       templates come with their defining header (VC6 instantiates a template named by an extern variable, so a bare
       forward declaration breaks the later definition). Skipped, with the reason: two definitions, a class-static member,
       an ambiguous name, a type that only a .cpp defines, a typedef or enum, a Win32 type.
apply  rewrites the tree: the definition keeps its initialiser and type and takes the canonical name, every other
       declaration (cpp or header) and its `// GLOBAL: GAMEMD` annotation is removed, every file that still spells an
       old name follows the rename, the shared header gains the declaration, every touched file includes it. Writes
       PLAN.json.applied (addresses and the files each touched).
check  compares the objects of a build of the edited tree with the base objects, section by section, relocation targets
       resolved to addresses (a rename or a type change that re-mangles a symbol is not a difference; a byte, a size, a
       different address or a compile failure is) and names the plan addresses behind every failing TU. VC6 re-orders
       .bss by symbol-name hash, so renaming a definition can move variables inside an object; the M3 link pins data,
       and --ignore-bss accepts that.
bisect ddmin over the plan addresses behind one failing TU (a few TUs change their scheduling or RTTI attribute byte with
       the set of declarations in scope): the minimal address set that makes that one TU differ. Drop one element.
bindings  after a build: add the mangled data symbols the objects define or reference for plan addresses that
       scripts/data/symbol_bindings.json does not bind yet, and drop the entries the edit made stale (stale against --new,
       not against --base). --apply writes the file.
rekeys the packet files for the removed central keys: binding_rekeys.json and symbol_map.json.

Nothing here decides a binary fact; the gates (gates.py --mode full, m3_gate.sh --full) stay the oracle.
"""
import argparse
import collections
import json
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(HERE, "land"))
import global_decls as GD  # noqa: E402

PRIMS = {"int", "char", "short", "long", "float", "double", "void", "bool", "unsigned", "signed", "const", "wchar_t",
         "__int64", "volatile", "struct", "class", "union", "enum", "size_t"}
WIN = {"DWORD", "WORD", "BYTE", "HWND", "HINSTANCE", "HANDLE", "HDC", "HRESULT", "LPVOID", "CRITICAL_SECTION", "HMODULE",
       "BOOL", "UINT", "LONG", "ULONG", "RECT", "POINT", "IID", "GUID", "LPCSTR", "LPSTR", "HBITMAP", "HICON", "HCURSOR"}
PLACEHOLDER = re.compile(r"^(DAT|STR|PTR|FUN)_[0-9A-Fa-f]{8}\w*$")
HEXTAIL = re.compile(r"_[0-9A-Fa-f]{8}$|_[0-9A-Fa-f]{6}$")


def hx(a):
    return "0x%08X" % a


def read(tree, rel):
    return open(os.path.join(tree, rel), errors="replace").read()


def write(tree, rel, text):
    with open(os.path.join(tree, rel), "w") as f:
        f.write(text)


def type_index(tree):
    """{type name: [(file, kind, template header)]} from class/struct/union/enum bodies (kind = the keyword) and typedefs
    (kind `typedef`) at column zero."""
    idx = collections.defaultdict(list)
    rx_body = re.compile(r"^(template\s*<[^>]*>\s*)?(class|struct|union|enum)\s+(\w+)\s*(?::[^{;]*)?\{", re.M)
    rx_td = re.compile(r"^typedef\b[^;{]*?(\w+)\s*(?:\[[^\]]*\])?\s*;", re.M)
    rx_td2 = re.compile(r"^\}\s*(\w+)\s*;", re.M)
    rx_fwd = re.compile(r"^(template\s*<[^>]*>\s*)?(class|struct)\s+(\w+)\s*;", re.M)
    for root, _, names in os.walk(os.path.join(tree, "match")):
        for n in names:
            if n.lower().endswith((".h", ".cpp", ".c")):
                rel = os.path.relpath(os.path.join(root, n), tree)
                t = read(tree, rel)
                for m in rx_body.finditer(t):
                    idx[m.group(3)].append((rel, m.group(2), (m.group(1) or "").strip()))
                for rx in (rx_td, rx_td2):
                    for m in rx.finditer(t):
                        idx[m.group(1)].append((rel, "typedef", ""))
                for m in rx_fwd.finditer(t):
                    idx[m.group(3)].append((rel, "fwd-" + m.group(2), (m.group(1) or "").strip()))
    return idx


def includes_of(tree, rel, cache):
    if rel in cache:
        return cache[rel]
    cache[rel] = set()
    out = set()
    try:
        t = read(tree, rel)
    except OSError:
        return out
    base = os.path.dirname(rel)
    for m in re.finditer(r'^\s*#\s*include\s+"([^"]+)"', t, re.M):
        inc = m.group(1)
        for cand in (os.path.normpath(os.path.join(base, inc)), os.path.normpath(os.path.join("match", inc))):
            if os.path.isfile(os.path.join(tree, cand)):
                out.add(cand)
                out |= includes_of(tree, cand, cache)
                break
    cache[rel] = out
    return out


def type_tokens(decl, name):
    d = re.sub(r"\[[^\]]*\]", " ", re.sub(r"\b%s\b" % re.escape(name), " ", decl))
    return [t for t in re.findall(r"[A-Za-z_]\w*", d) if t not in PRIMS]


def with_name(decl, old, new):
    return re.sub(r"\b%s\b" % re.escape(old), new, decl, count=1)


def choose_name(a, sites, canon):
    k = hx(a)
    if k in canon:
        return canon[k]
    names = collections.Counter(d["name"] for d in sites)
    if len(names) == 1:
        return next(iter(names))
    attested = [(n, c) for n, c in names.most_common() if not PLACEHOLDER.match(n) and not HEXTAIL.search(n)]
    if len({n for n, _ in attested}) == 1:
        return attested[0][0]
    if len(attested) > 1:
        return None
    pre = "STR" if any("char" in d["type"] for d in sites) and any(d["name"].startswith("STR_") for d in sites) else "DAT"
    return "%s_%08X" % (pre, a)


def header_for(a, hmap):
    for lo, hi, name in hmap:
        if lo <= a < hi:
            return name
    return None


def cmd_plan(args):
    tree = os.path.abspath(args.tree)
    res = GD.scan_tree(tree)
    canon = json.load(open(args.canon)) if args.canon else {}
    hmap = [(int(lo, 16), int(hi, 16), n) for lo, hi, n, _ in json.load(open(args.headers))]
    hdesc = {n: d for _, _, n, d in json.load(open(args.headers))}
    addrs = []
    for x in args.addrs:
        if os.path.isfile(x):
            addrs += [int(v, 16) for v in json.load(open(x))]
        else:
            addrs.append(int(x, 16))
    tidx = type_index(tree)
    inc_cache = {}
    plan, skipped = {}, {}
    for a in sorted(set(addrs)):
        sites = res.get(a, [])
        if not sites:
            skipped[hx(a)] = "no declaration site found"
            continue
        defs = [d for d in sites if not d["extern"]]
        if len(defs) > 1:
            skipped[hx(a)] = "two definitions: " + ", ".join("%s:%d" % (d["file"], d["line"]) for d in defs)
            continue
        if any(d.get("qualified") for d in sites):
            skipped[hx(a)] = "class static member (qualified declarator)"
            continue
        name = choose_name(a, sites, canon)
        if not name:
            skipped[hx(a)] = "ambiguous name: " + ", ".join(sorted({d["name"] for d in sites}))
            continue
        hdr = header_for(a, hmap)
        if not hdr:
            skipped[hx(a)] = "no header mapped"
            continue
        if defs:
            rep = defs[0]
        else:
            ct = collections.Counter(d["type"] for d in sites)
            rep = next(d for d in sites if d["type"] == ct.most_common(1)[0][0])
        decl = with_name(rep["decl"], rep["name"], name)
        owner = defs[0]["file"] if defs else sites[0]["file"]
        need, fwd, bad = [], [], None
        for tok in sorted(set(type_tokens(rep["decl"], rep["name"]))):
            if tok in WIN:
                bad = "Win32 type %s needs <windows.h>, which clashes with TU-local API prototypes" % tok
                break
            defs_ = tidx.get(tok, [])
            kinds = collections.Counter(k for _, k, _ in defs_)
            if not defs_:
                bad = "type %s is defined nowhere" % tok
                break
            if kinds.get("typedef") or kinds.get("enum"):
                bad = "type %s is a %s (cannot be forward declared)" % (tok, "typedef" if kinds.get("typedef") else "enum")
                break
            hf = [d for d in defs_ if d[0].endswith(".h") and not d[1].startswith("fwd-")]
            if not hf:
                bad = "type %s is defined only in %s" % (tok, defs_[0][0])
                break
            kw = collections.Counter(k for _, k, _ in hf).most_common(1)[0][0]
            th = collections.Counter(t for _, _, t in hf if t).most_common(1)
            th = th[0][0] if th else ""
            if "=" in th:
                bad = "template %s has default arguments" % tok
                break
            if th:
                # VC6 instantiates a class template named by an extern variable when only a forward declaration is
                # visible, and the later definition then fails: templates come with their defining header.
                lay = [d[0] for d in hf if "/_layout/" in d[0]]
                pick = (lay or sorted({d[0] for d in hf}))[0]
                inc = '"%s"' % os.path.relpath(pick, "match")
                if inc not in need:
                    need.append(inc)
                continue
            line = "%s %s;" % (kw, tok)
            if line not in fwd:
                fwd.append(line)
        if bad:
            skipped[hx(a)] = bad
            continue
        plan[hx(a)] = {"name": name, "decl": decl, "header": hdr, "needs": need, "fwd": fwd, "owner": owner,
                       "old_names": sorted({d["name"] for d in sites} - {name}),
                       "sites": ["%s:%d%s" % (d["file"], d["line"], "" if d["extern"] else "=DEF") for d in sites]}
    out = {"tree": tree, "plan": plan, "skipped": skipped, "headers": {v["header"]: hdesc[v["header"]] for v in plan.values()}}
    json.dump(out, open(args.out, "w"), indent=1)
    print("%d planned, %d skipped -> %s" % (len(plan), len(skipped), args.out))
    for k, v in skipped.items():
        print("  skip", k, v)
    return 0


# ---------------------------------------------------------------- apply

def insert_pos(lines):
    """Index at which to insert an #include: after the last #include of the leading preprocessor/comment block."""
    last_inc = None
    guard = None
    in_block = False
    for i, ln in enumerate(lines):
        s = ln.strip()
        if in_block:
            if "*/" in s:
                in_block = False
            continue
        if s == "" or s.startswith("//"):
            continue
        if s.startswith("/*"):
            if "*/" not in s:
                in_block = True
            continue
        if s.startswith("#"):
            if re.match(r"#\s*include", s):
                last_inc = i
            elif re.match(r"#\s*define\s+\w+\s*$", s) and guard is None and i > 0 and re.match(r"#\s*ifndef", lines[i - 1].strip()):
                guard = i
            continue
        break
    if last_inc is not None:
        return last_inc + 1
    if guard is not None:
        return guard + 1
    for i, ln in enumerate(lines):
        s = ln.strip()
        if s and not s.startswith("//"):
            return i
    return len(lines)


def add_include(text, hdr):
    if re.search(r'^\s*#\s*include\s+"(?:[^"]*/)?%s"' % re.escape(hdr), text, re.M):
        return text
    lines = text.split("\n")
    p = insert_pos(lines)
    lines.insert(p, '#include "%s"' % hdr)
    return "\n".join(lines)


def header_preamble(hdr, desc):
    g = "GG_MATCH_" + re.sub(r"[^A-Za-z0-9]", "_", hdr.upper())
    return ("// SPDX-License-Identifier: GPL-3.0-or-later\n// Provenance: own-binary-via-Ghidra\n//   %s\n"
            "#ifndef %s\n#define %s\n\n" % (desc, g, g)), "\n#endif  // %s\n" % g


def annotation_for(a, decl):
    kind = "STRING" if re.search(r"\bchar\b|wchar_t", decl) and "[" in decl else "GLOBAL"
    return "// %s: GAMEMD 0x%X" % (kind, a)


def cmd_apply(args):
    P = json.load(open(args.plan))
    tree = P["tree"]
    plan = P["plan"]
    only = {hx(int(x, 16)) for x in args.only} if args.only else None
    skip = {hx(int(x, 16)) for x in args.skip}
    sel = {k: v for k, v in plan.items() if (only is None or k in only) and k not in skip}
    binder = GD.Binder(tree)
    # fresh scan with all declarations kept (annotation runs need their neighbours)
    allsites = collections.defaultdict(list)
    for root, _, names in os.walk(os.path.join(tree, "match")):
        for n in names:
            if n.lower().endswith((".cpp", ".c", ".h")):
                rel = os.path.relpath(os.path.join(root, n), tree)
                ds = GD.scan_file(tree, rel, binder, keep_all=True)
                if ds:
                    allsites[rel] = ds
    addr_sites = collections.defaultdict(list)
    for rel, ds in allsites.items():
        for d in ds:
            if d["addr"] is not None and hx(d["addr"]) in sel:
                addr_sites[hx(d["addr"])].append(d)
    anntext = {}
    for k in sel:
        cands = sorted(addr_sites.get(k, []), key=lambda d: (d["extern"], d["file"], d["line"]))
        for d in cands:
            t_ = d.get("ann_text") or ""
            m_ = GD.ANNOT.match(t_) if t_ else None
            if m_ and len(GD.ADDR_IN.findall(m_.group(2))) == 1 and not t_.lstrip("/ ").startswith("Declaration:"):
                anntext[k] = t_.strip()
                break
    texts = {}
    edits = collections.defaultdict(list)      # file -> [(first, last)] 1-based inclusive line ranges to delete
    renames = collections.defaultdict(set)     # file -> {(old, new)}
    inc_needed = collections.defaultdict(set)  # file -> {headers}
    for k, ent in sel.items():
        for d in addr_sites.get(k, []):
            rel = d["file"]
            inc_needed[rel].add(ent["header"])
            for old in {d["name"]} - {ent["name"]}:
                renames[rel].add((old, ent["name"]))
    for k, ent in sel.items():
        for d in addr_sites.get(k, []):
            rel = d["file"]
            if rel not in texts:
                texts[rel] = read(tree, rel)
    lines_of = {rel: t.split("\n") for rel, t in texts.items()}
    problems = []
    for k, ent in sel.items():
        for d in addr_sites.get(k, []):
            if not d["extern"]:
                continue
            rel = d["file"]
            L = lines_of[rel]
            seg = [L[i - 1] for i in range(d["line"], d["end"] + 1)]
            joined = " ".join(x.split("//")[0] for x in seg).strip()
            if joined.count(";") != 1 or not joined.endswith(";") or not joined.startswith("extern") or "/*" in joined:
                problems.append((k, rel, d["line"], "declaration shares its lines"))
                continue
            edits[rel].append((d["line"], d["end"], d))
    bad = {p[0] for p in problems}
    if bad:
        for p in problems:
            print("  cannot edit", *p)
    sel = {k: v for k, v in sel.items() if k not in bad}
    # annotation blocks: delete when every declaration of the run is deleted
    delete = collections.defaultdict(set)
    for rel, es in edits.items():
        for a, b, d in es:
            if hx(d["addr"]) not in sel:
                continue
            for i in range(a, b + 1):
                delete[rel].add(i)
    # annotation lines
    for rel, ds in allsites.items():
        runs = collections.defaultdict(list)
        for d in ds:
            if d["ann"] is not None:
                runs[d["ann"]].append(d)
        for ann, members in runs.items():
            if all(d["addr"] is not None and hx(d["addr"]) in sel and d["extern"] and d["line"] in delete[rel] for d in members):
                first = min(d["line"] for d in members)
                L = lines_of.get(rel) or read(tree, rel).split("\n")
                lines_of.setdefault(rel, L)
                texts.setdefault(rel, "\n".join(L))
                for i in range(ann, first):
                    if L[i - 1].strip().startswith("//"):
                        delete[rel].add(i)
                    elif L[i - 1].strip() != "":
                        break
    # every file that still names an old spelling follows the rename, whether or not it declared the global itself
    gmap = {}
    clash = set()
    for k, ent in sel.items():
        for old in ent.get("old_names", []):
            if old in gmap and gmap[old][0] != ent["name"]:
                clash.add(old)
            gmap[old] = (ent["name"], ent["header"], k)
    for old in clash:
        gmap.pop(old, None)
    newnames = {ent["name"] for ent in sel.values()}
    for old in [o for o in gmap if o in newnames]:
        gmap.pop(old)
    touched = collections.defaultdict(set)
    for k in sel:
        touched[k].add("match/" + sel[k]["header"])
        for d in addr_sites.get(k, []):
            touched[k].add(d["file"])
    if gmap:
        rx = re.compile(r"(?<![\w.>:])(%s)\b" % "|".join(re.escape(o) for o in sorted(gmap, key=len, reverse=True)))
        for root, _, names in os.walk(os.path.join(tree, "match")):
            for n in names:
                if n.lower().endswith((".cpp", ".c", ".h")):
                    rel = os.path.relpath(os.path.join(root, n), tree)
                    t = texts[rel] if rel in texts else read(tree, rel)
                    hits = {m.group(1) for m in rx.finditer(t)}
                    if hits:
                        for o in hits:
                            renames[rel].add((o, gmap[o][0]))
                            inc_needed[rel].add(gmap[o][1])
                            touched[gmap[o][2]].add(rel)
    for rel in sorted(set(delete) | set(renames) | set(inc_needed)):
        if rel not in texts:
            texts[rel] = read(tree, rel)
        L = texts[rel].split("\n")
        out = []
        gone = False
        for i, ln in enumerate(L, 1):
            if i in delete.get(rel, ()):
                gone = True
                continue
            if gone and ln.strip() == "" and out and out[-1].strip() == "":
                gone = False
                continue        # the deletion would leave two blank lines in a row
            gone = False
            out.append(ln)
        t = "\n".join(out)
        for old, new in sorted(renames.get(rel, ()), key=lambda x: -len(x[0])):
            t = re.sub(r"(?<![\w.>:])%s\b" % re.escape(old), new, t)
        for hdr in sorted(inc_needed.get(rel, ())):
            if os.path.basename(rel) != hdr and rel != hdr:
                t = add_include(t, hdr)
        write(tree, rel, t)
    # shared headers
    byhdr = collections.defaultdict(list)
    for k, ent in sel.items():
        byhdr[ent["header"]].append((int(k, 16), ent))
    for hdr, ents in byhdr.items():
        path = "match/" + hdr
        full = os.path.join(tree, path)
        if os.path.isfile(full):
            t = read(tree, path)
        else:
            pre, post = header_preamble(hdr, P.get("headers", {}).get(hdr, "Retail globals declared once for every translation unit that reads them."))
            t = pre + post
        for a, ent in sorted(ents):
            if re.search(r"\b%s\b\s*(\[[^\]]*\])?\s*;" % re.escape(ent["name"]), t):
                continue
            body = []
            for n in ent["needs"]:
                inc = "#include %s" % n
                if inc not in t and inc not in body:
                    body.append(inc)
            if body:
                t = add_inc_after_guard(t, body)
            fw = [f for f in ent["fwd"] if f not in t]
            if fw:
                t = add_fwd(t, fw)
            t = t.replace("\n#endif  // ", "%s\n%s;\n\n#endif  // " % (anntext.get(hx(a)) or annotation_for(a, ent["decl"]), "extern " + ent["decl"]), 1)
        write(tree, path, t)
    print("applied %d addresses (%d files)" % (len(sel), len(set(delete) | set(renames) | set(inc_needed))))
    json.dump({"addrs": sorted(sel), "files": {k: sorted(v) for k, v in touched.items() if k in sel}},
              open(args.plan + ".applied", "w"))
    return 0


def add_fwd(t, fw):
    """Forward declarations go after the leading #include/guard block, before the first annotation."""
    lines = t.split("\n")
    p = insert_pos(lines)
    ins = [""] + fw + [""]
    for f in reversed(ins):
        lines.insert(p, f)
    return "\n".join(lines)


def add_inc_after_guard(t, body):
    lines = t.split("\n")
    p = insert_pos(lines)
    for b in reversed(body):
        lines.insert(p, b)
    return "\n".join(lines)


# ---------------------------------------------------------------- check

def resolver(tree, plan, extra=None):
    """Symbol -> address. EXTRA: an older bindings file (the base's) whose entries the tree may have pruned."""
    bind = {}
    try:
        b = json.load(open(os.path.join(tree, GD.BINDINGS)))
    except OSError:
        b = {}
    if extra is None:
        extra = os.environ.get("GLOBAL_UNIFY_BASE_BINDINGS")
    if extra:
        old = json.load(open(extra))
        b = dict(old, **b)
    byident = {}
    for k, v in b.items():
        a = int(v, 16) if isinstance(v, str) else v
        bind[k] = a
        if k.startswith("?") and "@@3" in k:
            byident.setdefault(GD.ident_of_mangled(k), set()).add(a)
    names = {}
    for k, ent in plan.items():
        a = int(k, 16)
        names[ent["name"]] = a
        for o in ent.get("old_names", []):
            names[o] = a

    def res(sym):
        if sym in bind:
            return bind[sym]
        ident = GD.ident_of_mangled(sym) if sym.startswith("?") or sym.startswith("_") else sym
        if sym.startswith("?") and "@@3" in sym:
            if ident in names:
                return names[ident]
            m = GD.NAME_ADDR.search(ident)
            if m:
                return int(m.group(1), 16)
            s = byident.get(ident)
            if s and len(s) == 1:
                return next(iter(s))
        elif sym.startswith("_"):
            m = re.match(r"^_(?:DAT|FUN|PTR)_([0-9A-Fa-f]{8})", sym)
            if m:
                return int(m.group(1), 16)
        return None
    return res


def sections(path, res, skip_bss=False):
    import sectioncmp as S
    full = S.coff_full(path)
    out = []
    for key, (data, rel) in full.items():
        sec = key.split("|")[0]
        if skip_bss and sec.startswith(".bss"):
            continue
        slots = {o for o, _, t in rel if t in (6, 0x14)}
        d = bytearray(data)
        r2 = []
        for o, sym, t in rel:
            if sym.startswith("$"):
                r2.append((o, t, ("L",)))
                continue
            a = res(sym)
            imm = struct.unpack_from("<I", data, o)[0] if o + 4 <= len(data) else 0
            if t in (6, 0x14) and o + 4 <= len(d):
                d[o:o + 4] = b"\0\0\0\0"
                r2.append((o, t, ("A", (a + imm) & 0xFFFFFFFF) if a is not None else ("S", sym, imm)))
            else:
                r2.append((o, t, ("S", sym)))
        out.append((sec, bytes(d), tuple(sorted(r2, key=lambda x: (x[0], x[1], str(x[2]))))))
    return sorted(out, key=lambda x: (x[0], x[1], str(x[2])))


def layout(vt, path, res):
    """[(section, offset, address-or-name)] of the external symbols an object defines in data sections."""
    d, ss, sy, aux = vt.parse_coff(path)
    out = []
    for s_ in sy.values():
        if s_["storage_class"] == 2 and s_["section"] > 0 and s_["section"] in ss:
            sec = ss[s_["section"]]["name"]
            if sec.startswith(".text"):
                continue
            nm = s_["name"]
            a = res(nm)
            out.append((sec.split("$")[0], s_["value"], a if a is not None else nm))
    return sorted(out, key=lambda x: (x[0], x[1], str(x[2])))


def compare_obj(vt, res, b, nw, ignore_bss):
    """None when the new object equals the base object once relocation targets are resolved to addresses, else why."""
    if open(b, "rb").read() == open(nw, "rb").read():
        return None
    try:
        x, y = sections(b, res, ignore_bss), sections(nw, res, ignore_bss)
    except Exception as e:  # noqa: BLE001
        return "unreadable: %s" % e
    lx, ly = (layout(vt, b, res), layout(vt, nw, res)) if not ignore_bss else ([], [])
    if x == y and lx != ly:
        return "data symbol layout differs %s" % [(p, q) for p, q in zip(lx, ly) if p != q][:2]
    if x != y:
        why = []
        if len(x) != len(y):
            why.append("%d vs %d sections" % (len(x), len(y)))
        for (sa, da, ra), (sb, db, rb) in zip(x, y):
            if sa != sb or da != db:
                why.append("%s bytes differ" % sa)
                break
            if ra != rb:
                diff = [(p, q) for p, q in zip(ra, rb) if p != q][:2]
                why.append("%s relocs differ %s" % (sa, diff))
                break
        return "; ".join(why) or "sections differ"
    return None


def load_vt(tree):
    import importlib.util
    spec = importlib.util.spec_from_file_location("vt_tree", os.path.join(tree, "scripts/vc6/verify_vtable.py"))
    vt = importlib.util.module_from_spec(spec)
    sys.path.insert(0, os.path.join(tree, "scripts/vc6"))
    spec.loader.exec_module(vt)
    return vt


def closure_candidates(tree, tu_src, applied, touched):
    """Applied addresses whose edited files are in the include closure of TU_SRC (or are the TU itself)."""
    cache = {}
    clo = includes_of(tree, tu_src, cache) | {tu_src}
    return [k for k in applied if clo & set(touched.get(k, ()))]


def cmd_bisect(args):
    """ddmin over the addresses behind one failing TU: which minimal set of plan addresses makes TU differ from base?
    Each trial resets the tree (the scratch worktree), applies the plan without the addresses outside the subset, and
    compiles only that TU."""
    import subprocess
    P = json.load(open(args.plan))
    tree = P["tree"]
    plan = P["plan"]
    saved = open(args.plan + ".applied").read()
    ap_ = json.loads(saved)
    applied, touched = ap_["addrs"], ap_.get("files", {})
    tu = args.tu
    cands = closure_candidates(tree, tu, applied, touched)
    vt = load_vt(tree)
    scratch = os.path.abspath(args.work)
    os.makedirs(scratch, exist_ok=True)
    base_obj = os.path.join(args.base, os.path.splitext(tu)[0] + ".obj")

    def trial(subset):
        keep = set(subset)
        skip = [k for k in plan if k not in keep]
        subprocess.check_call(["bash", args.reset])
        subprocess.check_call([sys.executable, os.path.abspath(__file__), "--tree", tree, "apply", args.plan,
                               "--skip"] + skip, stdout=subprocess.DEVNULL)
        for h in subprocess.check_output(["git", "-C", tree, "ls-files", "--others", "--exclude-standard", "match"]).decode().split():
            if h.endswith("_globals.h"):
                subprocess.check_call(["git", "-C", tree, "add", h])
        obj = os.path.join(scratch, "t.obj")
        if os.path.exists(obj):
            os.unlink(obj)
        src = os.path.join(tree, tu)
        subprocess.run(["bash", os.path.join(tree, "scripts/vc6/vc6cl.sh"), "/Fo" + obj, os.path.basename(src)],
                       cwd=os.path.dirname(src), stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        if not os.path.isfile(obj):
            return "no object"
        res = resolver(tree, {k: plan[k] for k in keep})
        return compare_obj(vt, res, base_obj, obj, args.ignore_bss)

    # ddmin: find a minimal subset of cands whose application makes the TU differ
    n = 2
    cur = list(cands)
    if not trial(cur):
        print("closure candidates do not reproduce (%s); trying every applied address" % cands)
        cur = list(applied)
        if not trial(cur):
            open(args.plan + ".applied", "w").write(saved)
            print("the full applied set does not reproduce")
            return 1
    while len(cur) >= 2:
        chunk = max(1, len(cur) // n)
        subsets = [cur[i:i + chunk] for i in range(0, len(cur), chunk)]
        for sub in subsets:
            if trial(sub):
                cur, n = sub, 2
                break
        else:
            for sub in subsets:
                comp = [x for x in cur if x not in sub]
                if comp and trial(comp):
                    cur, n = comp, max(n - 1, 2)
                    break
            else:
                if n >= len(cur):
                    break
                n = min(len(cur), n * 2)
    open(args.plan + ".applied", "w").write(saved)
    print(json.dumps(cur))
    if args.out:
        json.dump(cur, open(args.out, "w"))
    return 0


def cmd_check(args):
    P = json.load(open(args.plan))
    tree = P["tree"]
    plan = P["plan"]
    ap_ = json.load(open(args.plan + ".applied")) if os.path.isfile(args.plan + ".applied") else {"addrs": list(plan), "files": {}}
    applied, touched = ap_["addrs"], ap_.get("files", {})
    res = resolver(tree, {k: plan[k] for k in applied})
    import importlib.util
    spec = importlib.util.spec_from_file_location("vt_tree", os.path.join(tree, "scripts/vc6/verify_vtable.py"))
    vt = importlib.util.module_from_spec(spec)
    sys.path.insert(0, os.path.join(tree, "scripts/vc6"))
    spec.loader.exec_module(vt)
    bad = {}
    for root, _, names in os.walk(args.base):
        for n in names:
            if not n.endswith(".obj"):
                continue
            b = os.path.join(root, n)
            rel = os.path.relpath(b, args.base)
            nw = os.path.join(args.new, rel)
            if not os.path.isfile(nw):
                bad[rel] = "no object (compile failed)"
                continue
            why = compare_obj(vt, res, b, nw, args.ignore_bss)
            if why:
                bad[rel] = why
    attributed = collections.defaultdict(list)
    freq = collections.Counter()
    toks = {}
    for k in applied:
        toks[k] = set(type_tokens(plan[k]["decl"], plan[k]["name"]))
        freq.update(toks[k])
    rare_tokens = {k: [t for t in v if freq[t] <= 4 and len(t) > 6] for k, v in toks.items()}
    for rel, why in sorted(bad.items()):
        src = os.path.splitext(rel)[0]
        log = os.path.join(args.new, src + ".log")
        text = ""
        if os.path.isfile(log):
            text = open(log, errors="replace").read()
        hit = set()
        # identifiers of the failing source lines plus the message text
        srctext = []
        for m in re.finditer(r"match[\\/]([^(\s]+)\((\d+)\)", text):
            f = os.path.join(tree, "match", m.group(1).replace("\\", "/"))
            try:
                srctext.append(open(f, errors="replace").read().split("\n")[int(m.group(2)) - 1])
            except (OSError, IndexError):
                pass
        blob = " ".join(l for l in text.splitlines() if "error" in l) + " " + " ".join(srctext) + " " + why
        for k in applied:
            ent = plan[k]
            for nm in [ent["name"]] + ent.get("old_names", []):
                if re.search(r"\b%s\b" % re.escape(nm), blob):
                    hit.add(k)
        if not hit:
            for k in applied:
                for tok in rare_tokens.get(k, ()):
                    if re.search(r"\b%s\b" % re.escape(tok), blob):
                        hit.add(k)
        if not hit:
            srcrel = os.path.splitext(rel)[0]
            hit = {k for k in applied if any(os.path.splitext(f[len("match/"):])[0] == srcrel[len("match/"):] for f in touched.get(k, ()))}
        for k in hit:
            attributed[k].append(rel)
        print("FAIL %s: %s%s" % (rel, why[:200], "  [%s]" % ",".join(sorted(hit)) if hit else "  [unattributed]"))
        if not hit and text:
            print("     ", " | ".join([l for l in text.splitlines() if "error" in l][:2]))
    print("%d failing objects; %d addresses implicated" % (len(bad), len(attributed)))
    if args.drop_file:
        json.dump(sorted(attributed), open(args.drop_file, "w"))
    return 1 if bad else 0


# ---------------------------------------------------------------- bindings

def cmd_bindings(args):
    """Bind the mangled data symbols of plan addresses that the objects define or reference."""
    P = json.load(open(args.plan))
    tree = P["tree"]
    plan = P["plan"]
    ap_ = json.load(open(args.plan + ".applied")) if os.path.isfile(args.plan + ".applied") else {"addrs": list(plan)}
    applied = ap_["addrs"]
    vt = load_vt(tree)
    sys.path.insert(0, os.path.join(tree, "scripts/agent_tools"))
    path = os.path.join(tree, GD.BINDINGS)
    raw = open(path).read()
    bind = json.loads(raw)
    byname = {plan[k]["name"]: int(k, 16) for k in applied}
    need = {}
    for root, _, names in os.walk(args.new):
        for n in names:
            if n.endswith(".obj"):
                d, ss, sy, aux = vt.parse_coff(os.path.join(root, n))
                for s_ in sy.values():
                    nm = s_.get("name") or ""
                    if nm.startswith("?") and "@@3" in nm:
                        ident = GD.ident_of_mangled(nm)
                        if ident in byname and nm not in bind:
                            need[nm] = "0x%08X" % byname[ident]
    for k, v in sorted(need.items()):
        print("BIND", k, v)
    # entries the edit made stale: stale against the new objects but not against the base objects
    drop = []
    if args.base:
        import bindings_prune as BP
        per_n, un_n = BP.scan(vt, args.new)
        per_b, un_b = BP.scan(vt, args.base)
        sn = set(BP.stale_keys(bind, per_n, un_n)) - {k for k in need}
        sb = set(BP.stale_keys(bind, per_b, un_b))
        drop = sorted(sn - sb)
        for k in drop:
            print("STALE", k, bind[k])
    if args.apply and (need or drop):
        bind.update(need)
        for k in drop:
            bind.pop(k, None)
        if list(json.loads(raw)) == sorted(json.loads(raw)):
            bind = dict(sorted(bind.items()))
        indent = 1 if raw.startswith("{\n ") and not raw.startswith("{\n  ") else 2
        with open(path, "w") as f:
            f.write(json.dumps(bind, indent=indent, ensure_ascii=False) + ("\n" if raw.endswith("\n") else ""))
    print("%d new bindings, %d newly stale%s" % (len(need), len(drop), " (written)" if args.apply else ""))
    return 0


def cmd_rekeys(args):
    """binding_rekeys.json and symbol_map.json for a packet: every central key the patch removes is re-keyed to the
    key of the same address that the build emits under the canonical name (or the only emitted key of that address)."""
    import subprocess
    P = json.load(open(args.plan))
    tree, plan = P["tree"], P["plan"]
    vt = load_vt(tree)

    def show(rev):
        return json.loads(subprocess.check_output(["git", "-C", tree, "show", "%s:%s" % (rev, GD.BINDINGS)]))
    pre, post = show(args.pre), show(args.post)
    canon = {int(k, 16): v["name"] for k, v in plan.items()}
    emitted = set()
    for r, _, ns in os.walk(args.new):
        for n in ns:
            if n.endswith(".obj"):
                emitted |= {s_["name"] for s_ in vt.parse_coff(os.path.join(r, n))[2].values() if s_.get("name")}
    byaddr = {}
    for k, v in post.items():
        if k in emitted:
            byaddr.setdefault(int(v, 16) if isinstance(v, str) else v, []).append(k)
    rek, miss = {}, []
    for k, v in pre.items():
        if k in post:
            continue
        a = int(v, 16) if isinstance(v, str) else v
        c = byaddr.get(a, [])
        pick = [x for x in c if GD.ident_of_mangled(x) == canon.get(a)] or (c if len(c) == 1 else [])
        if pick:
            rek[k] = (pick[0], a)
        else:
            miss.append((k, hx(a), c))
    os.makedirs(args.out, exist_ok=True)
    json.dump([{"old": k, "new": n, "addr": hx(a)} for k, (n, a) in sorted(rek.items())],
              open(os.path.join(args.out, "binding_rekeys.json"), "w"), indent=1)
    smap = {k: post[k] for k in post if k not in pre}
    smap.update({n: post[n] for n, _ in rek.values()})
    json.dump(smap, open(os.path.join(args.out, "symbol_map.json"), "w"), indent=1)
    print("%d rekeys, %d symbols in symbol_map.json, %d removed keys without a target" % (len(rek), len(smap), len(miss)))
    for m in miss:
        print("  MISSING", m)
    return 1 if miss else 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=os.path.join(HERE, "..", ".."))
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("plan")
    p.add_argument("addrs", nargs="+")
    p.add_argument("--headers", required=True)
    p.add_argument("--canon")
    p.add_argument("--out", required=True)
    p = sub.add_parser("apply")
    p.add_argument("plan")
    p.add_argument("--skip", nargs="*", default=[])
    p.add_argument("--only", nargs="*", default=[])
    p = sub.add_parser("check")
    p.add_argument("plan")
    p.add_argument("--base", required=True)
    p.add_argument("--new", required=True)
    p.add_argument("--drop-file")
    p.add_argument("--ignore-bss", action="store_true", help="skip .bss sections and the data-symbol layout comparison")
    p = sub.add_parser("bisect")
    p.add_argument("plan")
    p.add_argument("--tu", required=True, help="repo-relative source, e.g. match/Queue.cpp")
    p.add_argument("--base", required=True)
    p.add_argument("--work", required=True)
    p.add_argument("--reset", required=True, help="script that restores the worktree")
    p.add_argument("--ignore-bss", action="store_true")
    p.add_argument("--out")
    p = sub.add_parser("rekeys")
    p.add_argument("plan")
    p.add_argument("--new", required=True)
    p.add_argument("--pre", required=True)
    p.add_argument("--post", required=True)
    p.add_argument("--out", required=True)
    p = sub.add_parser("bindings")
    p.add_argument("plan")
    p.add_argument("--new", required=True)
    p.add_argument("--base", help="base object dir: only entries that became stale against --new (not against --base) are dropped")
    p.add_argument("--apply", action="store_true")
    a = ap.parse_args(argv)
    return {"plan": cmd_plan, "apply": cmd_apply, "check": cmd_check, "bindings": cmd_bindings, "bisect": cmd_bisect, "rekeys": cmd_rekeys}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())
