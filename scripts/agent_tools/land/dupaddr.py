#!/usr/bin/env python3
"""dupaddr.py: two or more strong DEFINITIONS bound to the same retail address, whatever their mangling.

The dupdefs gate compares mangled names, so `void* DAT_00B0FB48` in one object and
`WholeFileBlock* DAT_00B0FB48` in another (different manglings, one address) passes it. This
module resolves every definition to an address and groups by address.

A definition is bound to an address by, in order:
  * a `// GLOBAL: GAMEMD 0xADDR` / `// FUNCTION: GAMEMD 0xADDR` annotation followed by a non-extern,
    non-static declaration in a .cpp/.c file (source scan);
  * scripts/data/symbol_bindings.json (`mangled` or a scoped `tu::mangled` key);
  * a Ghidra-style name (`DAT_xxxxxxxx`, `FUN_xxxxxxxx`, `PTR_xxxxxxxx`) in a strong external symbol of an object;
  * a match_manifest.json row (`sym` -> `addr`) for a strong external symbol of an object.
Declarations (`extern`) never count. Weak/COMDAT symbols never count (the caller passes strong names only).

    dupaddr.py --tree WT --objs DIR [--baseline FILE] [--write-baseline FILE] [--json]

DIR holds <tu without extension>.obj (the gates' run layout, e.g. <run>/new). The baseline is a
ratchet: addresses recorded there are legacy; only an address that is not in it, or a TU that joins a
legacy address, is a new violation.
"""
import argparse
import json
import os
import re
import sys

BINDINGS = "scripts/data/symbol_bindings.json"
MANIFEST = "scripts/data/match_manifest.json"
BASELINE = "scripts/data/dupaddr_baseline.json"

ANNOT = re.compile(r"^(?://|;) (GLOBAL|FUNCTION): GAMEMD (0x[0-9A-Fa-f]+)")
NAME_ADDR = re.compile(r"^\??_?(?:DAT|FUN|PTR)_([0-9A-Fa-f]{8})(?:@|$)")
ANY_ANNOT = re.compile(r"^(?://|;) [A-Z]+: GAMEMD 0x")
IDENT = re.compile(r"[A-Za-z_]\w*")
SRC_EXT = (".cpp", ".c")
FUNC_DEFS = os.environ.get("DUPADDR_FUNC_ANNOT") == "1"   # experimental: FUNCTION annotations as source-level claims


def hx(v):
    return "0x%08X" % (int(v, 16) if isinstance(v, str) else v)


def ident_of_mangled(m):
    """Unqualified base name of a decorated symbol: `?DAT_1@@3HA` -> DAT_1, `_FUN_2@8` -> FUN_2."""
    s = m.lstrip("?")
    s = s.lstrip("_") if not m.startswith("?") else s
    return s.split("@", 1)[0]


def declared_name(decl):
    """Identifier declared by DECL (text up to the terminating `;`/`{`), or None."""
    d = decl
    for stop in ("=", "{"):
        i = d.find(stop)
        if i >= 0:
            d = d[:i]
    d = d.strip().rstrip(";").strip()
    m = re.search(r"\(\s*[*&]\s*(?:const\s+)?([A-Za-z_]\w*)\s*\)\s*\(", d)     # function pointer
    if m:
        return m.group(1)
    if "(" in d:                                                                # function definition/prototype
        d = d[:d.index("(")]
    d = re.sub(r"\[[^\]]*\]", "", d)
    toks = IDENT.findall(d)
    return toks[-1] if toks else None


def internal_const(decl):
    """True for a non-extern declaration that is const itself (`const double X = 2.0;`, `const char* const t[]`):
    C++ gives it internal linkage, so it is not a strong external definition."""
    d = decl.split("=")[0].split("{")[0]
    tail = d[d.rfind("*") + 1:] if "*" in d else d
    return re.search(r"\bconst\b", tail) is not None


def source_defs(text):
    """[(addr, ident, kind)] for annotated non-extern, non-static declarations at column zero of a source file.
    FUNCTION annotations count only when the next code line looks like a definition head (it has `(`)."""
    out = []
    lines = text.split("\n")
    for i, ln in enumerate(lines):
        m = ANNOT.match(ln)
        if not m:
            continue
        kind, addr = m.group(1), int(m.group(2), 16)
        j = i + 1
        while j < len(lines) and (not lines[j].strip() or lines[j].lstrip().startswith(("//", ";", "#"))):
            if ANY_ANNOT.match(lines[j]):
                j = len(lines)          # another annotation first: this one marks no declaration of its own
                break
            j += 1
        if j >= len(lines):
            continue
        head = []
        k = j
        while k < len(lines) and k < j + 8:
            head.append(lines[k])
            if re.search(r"[;{]\s*(//.*)?$", lines[k]) or lines[k].rstrip().endswith("}"):
                break
            k += 1
        decl = " ".join(x.strip() for x in head)
        ext_init = bool(re.match(r"extern\s+(?!\")", decl)) and "=" in decl.split(";")[0]    # `extern const T X = v;` defines X
        if ext_init:
            decl = re.sub(r"^extern\s+", "", decl)
        if re.match(r"(extern|static|typedef|template|class|struct|enum|union|using)\b", decl) and not decl.startswith("extern \"C\" {"):
            continue
        if kind == "FUNCTION":
            if not FUNC_DEFS:
                continue
            toks = re.findall(r"[~A-Za-z_][\w:]*", decl.split("(")[0])
            name = toks[-1].split("::")[-1] if "(" in decl and not decl.rstrip().endswith(");") and toks else None
        else:
            if "(" in decl and not re.search(r"\(\s*[*&]", decl):
                continue                                                         # a function prototype, not data
            if not ext_init and internal_const(decl):
                continue
            name = declared_name(decl)
        if name:
            out.append((addr, name, kind))
    return out


def load_json(tree, rel):
    try:
        with open(os.path.join(tree, rel)) as f:
            return json.load(f)
    except (OSError, ValueError):
        return {}


class Resolver:
    def __init__(self, tree):
        b = load_json(tree, BINDINGS)
        self.bind = {}
        self.scoped = {}
        for k, v in b.items():
            t, sep, name = k.partition("::")
            a = int(v, 16) if isinstance(v, str) else v
            if sep:
                self.scoped[(t, name)] = a
            else:
                self.bind[k] = a
        self.rows = {}
        man = load_json(tree, MANIFEST)
        for r in man if isinstance(man, list) else []:
            if r.get("sym") and r.get("addr") is not None and r.get("status") in ("matched", "partial"):
                self.rows.setdefault(r["sym"], int(r["addr"], 16) if isinstance(r["addr"], str) else r["addr"])

    def addr(self, tu, sym):
        a = self.scoped.get((tu, sym))
        if a is None:
            a = self.bind.get(sym)
        if a is None:
            m = NAME_ADDR.match(sym)
            if m:
                a = int(m.group(1), 16)
        if a is None:
            a = self.rows.get(sym)
        return a


def collect(tree, tus, strong_names, read_source=None):
    """{addr: {(tu, ident): [via...]}} from source annotations and object symbols.
    strong_names(tu) -> iterable of strong external symbol names of that TU's object (or None)."""
    res = Resolver(tree)
    by_addr = {}
    for tu in tus:
        if tu.lower().endswith(SRC_EXT):
            if read_source:
                text = read_source(tu)
            else:
                try:
                    with open(os.path.join(tree, tu), errors="replace") as f:
                        text = f.read()
                except OSError:
                    text = ""
            strong = strong_names(tu)
            have = {ident_of_mangled(x) for x in strong} if strong is not None else None
            for addr, ident, kind in source_defs(text or ""):
                if have is not None and ident not in have:
                    continue        # static, internal-linkage const, #if'd out: the object has no such external symbol
                by_addr.setdefault(addr, {}).setdefault((tu, ident), []).append("annotation")
        for sym in strong_names(tu) or ():
            a = res.addr(tu, sym)
            if a is not None:
                by_addr.setdefault(a, {}).setdefault((tu, ident_of_mangled(sym)), []).append(sym)
    return by_addr


def violations(by_addr):
    """{addr: sorted [(tu, ident, [via])]} for addresses with two or more distinct (tu, ident) definitions."""
    out = {}
    for a, mem in by_addr.items():
        if len(mem) > 1:
            out[a] = sorted((tu, ident, sorted(set(via))) for (tu, ident), via in mem.items())
    return out


def to_baseline(viol, base_sha=""):
    return {"version": 1, "base": base_sha,
            "note": "legacy addresses with two or more strong definitions; the dupaddr gate fails only on addresses or TUs not listed here",
            "addresses": {hx(a): [{"tu": tu, "name": n} for tu, n, _ in mem] for a, mem in sorted(viol.items())}}


def new_violations(viol, baseline):
    """(new, fixed): violations not covered by the baseline, and baseline addresses no longer violating."""
    legacy = {}
    for a, mem in (baseline or {}).get("addresses", {}).items():
        legacy[int(a, 16)] = {m["tu"] for m in mem}
    new = {}
    for a, mem in viol.items():
        if a not in legacy:
            new[a] = mem
        elif any(tu not in legacy[a] for tu, _, _ in mem):
            new[a] = mem
    fixed = sorted(a for a in legacy if a not in viol)
    return new, fixed


def categorize(mem, res_tus=None):
    """A coarse category for reports: code (FUN_ bodies), same-tu (aliases in one TU), same-name (one global defined in
    several TUs under different types/qualifiers), different-name."""
    tus = {tu for tu, _, _ in mem}
    names = {n for _, n, _ in mem}
    if any(n.startswith("FUN_") for n in names):
        return "code"
    if len(tus) == 1:
        return "same-tu"
    if len(names) == 1:
        return "same-name"
    return "different-name"


def main(argv=None):
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "vc6"))
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=".")
    ap.add_argument("--objs", required=True, help="object dir: <tu without ext>.obj")
    ap.add_argument("--baseline", default=None)
    ap.add_argument("--write-baseline", default=None)
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args(argv)
    tree = os.path.abspath(a.tree)
    import importlib.util
    spec = importlib.util.spec_from_file_location("vt_tree", os.path.join(tree, "scripts/vc6/verify_vtable.py"))
    vt = importlib.util.module_from_spec(spec)
    sys.path.insert(0, os.path.join(tree, "scripts/vc6"))
    spec.loader.exec_module(vt)
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import gates as G
    tus = []
    for root, _, names in os.walk(os.path.join(tree, "match")):
        for n in names:
            if n.lower().endswith((".cpp", ".c")):
                tus.append(os.path.relpath(os.path.join(root, n), tree))
    tus.sort()

    def names(tu):
        o = G.objpath(a.objs, tu)
        return G.strong_defs(vt, o) if os.path.isfile(o) else None

    viol = violations(collect(tree, tus, names))
    if a.write_baseline:
        json.dump(to_baseline(viol), open(a.write_baseline, "w"), indent=1)
        open(a.write_baseline, "a").write("\n")
    cats = {}
    for addr, mem in viol.items():
        cats.setdefault(categorize(mem), []).append(addr)
    if a.json:
        print(json.dumps({hx(k): v for k, v in viol.items()}, indent=1), file=sys.stdout)
    else:
        for addr, mem in sorted(viol.items()):
            print(hx(addr), categorize(mem), "; ".join("%s:%s" % (tu, n) for tu, n, _ in mem))
    print("%d violating addresses: %s" % (len(viol), ", ".join("%s %d" % (k, len(v)) for k, v in sorted(cats.items()))),
          file=sys.stderr if a.json else sys.stdout)
    if a.baseline:
        base = json.load(open(a.baseline))
        new, fixed = new_violations(viol, base)
        print("%d new vs baseline, %d baseline entries fixed" % (len(new), len(fixed)))
        return 1 if new else 0
    return 0


if __name__ == "__main__":
    sys.exit(main())
