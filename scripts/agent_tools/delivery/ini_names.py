#!/usr/bin/env python3
# Provenance: original. Reads match/ sources and the manifest; report only, edits nothing.
"""ini_names.py: field names established by matched INI readers, and where the same offsets are still unknown.

    ini_names.py [--tree PATH] [--class NAME]... [--include-partial] [--possible] [--json OUT] [--limit N]

A retail INI reader stores `Field = ini->ReadX(ID, "Key", Field)`; when that function is a matched row, the
member name (the INI key spells it) and its class are binary-attested at the member's offset. This collects
every such statement in match/**, resolves the offset from the class's `GG_STATIC_ASSERT(offsetof(Class, Field)
== N)` (else the `// +0xNNN` comment on the member declaration), then lists where the same offset in the same
class is still an unknown_XX member:

  declaration   a class/struct definition of that class name (any file) with an unknown member at the offset
  use           `unknown_XX` accessed in a method of that class (definite), or in a file that mentions the class (possible)

Nothing is renamed. Use the report to rename members and uses in one commit per class, then rescore the
touched TUs.
"""
import argparse
import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cppscan  # noqa: E402
import dlib as D  # noqa: E402

READ = re.compile(r"\bRead\w+\s*\(")
ANN = re.compile(r"^\s*//\s*FUNCTION:\s*GAMEMD\s+(0x[0-9A-Fa-f]+)(.*)$")
ASSERT = re.compile(r"GG_STATIC_ASSERT\s*\(\s*offsetof\s*\(\s*(\w+)\s*,\s*(\w+)\s*\)\s*==\s*(0x[0-9A-Fa-f]+|\d+)\s*\)")
CLASS_OPEN = re.compile(r"^\s*(?:class|struct)\s+(\w+)\b[^;{]*\{", re.M)
MEMBER_OFF = re.compile(r"//\s*\+0x([0-9A-Fa-f]+)")
UNKNOWN = re.compile(r"\bunknown_(?:[A-Za-z]+_)?([0-9A-Fa-f]+)\b")


def split_args(s, i):
    """args of the call whose '(' is at s[i-1]; -> (list of arg strings, index after ')')"""
    depth, args, cur, j, instr = 1, [], [], i, False
    while j < len(s):
        c = s[j]
        if instr:
            cur.append(c)
            if c == "\\":
                cur.append(s[j + 1]); j += 1
            elif c == '"':
                instr = False
        elif c == '"':
            instr = True; cur.append(c)
        elif c in "([{":
            depth += 1; cur.append(c)
        elif c in ")]}":
            depth -= 1
            if depth == 0:
                args.append("".join(cur).strip())
                return args, j + 1
            cur.append(c)
        elif c == "," and depth == 1:
            args.append("".join(cur).strip()); cur = []
        else:
            cur.append(c)
        j += 1
    return args, j


def readers(path, text, manifest):
    """[(class, func, addr, row, field, key, kind, line)] of `Field = X->ReadY(id, "Key", ...Field...)` statements."""
    out = []
    lines = text.split("\n")
    for header, body, l0, l1 in cppscan.function_bodies(text):
        m = re.findall(r"(\w+)\s*::\s*(~?\w+)\s*$", header.split("(")[0].strip())
        if not m:
            continue
        cls, fn = m[-1]
        addr = None
        for k in range(l0 - 2, max(l0 - 40, 0) - 1, -1):
            a = ANN.match(lines[k])
            if a and "decl;" not in a.group(2):
                addr = int(a.group(1), 16)
                break
            if lines[k].startswith("}"):
                break
        raw = "\n".join(lines[l0 - 1:l1])
        raw = re.sub(r"(?m)//[^\"\n]*$", "", raw)
        for rm in READ.finditer(raw):
            pre = raw[:rm.start()].rstrip()
            kind = rm.group(0).rstrip("( ")
            # strip a receiver (ini->, ini., DAT_x.) and an optional cast to find the '='
            pre = re.sub(r"\w+(?:\[[^\]]*\])?\s*(?:->|\.)\s*$", "", pre)
            pre = re.sub(r"\(\s*[\w\s\*]+\)\s*$", "", pre).rstrip()
            if not pre.endswith("=") or pre.endswith(("==", "!=", "<=", ">=")):
                continue
            lhs = re.search(r"([A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*)*)\s*=$", pre.rstrip())
            if not lhs:
                continue
            field = re.split(r"\s*(?:->|\.)\s*", lhs.group(1))[-1]
            if field.startswith("unknown") or field in ("this",):
                continue
            args, _ = split_args(raw, rm.end())
            if len(args) < 3:
                continue
            km = re.fullmatch(r'"([^"]+)"', args[1])
            if not km or not re.search(r"\b%s\b" % re.escape(field), args[2]):
                continue
            ln = l0 + raw[:rm.start()].count("\n")
            out.append(dict(cls=cls, func=fn, addr=("0x%X" % addr) if addr else None, field=field, key=km.group(1), kind=kind,
                            file=path, line=ln, row=manifest.get(addr)))
    return out


def class_bodies(text):
    """[(name, first_line, last_line, body_lines)] for class/struct definitions (brace matched on stripped text)."""
    s = cppscan.strip_code(text)
    res = []
    for m in CLASS_OPEN.finditer(s):
        depth, i = 1, m.end()
        while i < len(s) and depth:
            depth += (s[i] == "{") - (s[i] == "}")
            i += 1
        l0 = s.count("\n", 0, m.start()) + 1
        l1 = s.count("\n", 0, i) + 1
        res.append((m.group(1), l0, l1))
    return res


def analyse(tree, only=(), include_partial=False):
    man = {int(r["addr"], 16): r for r in __import__("json").load(open(os.path.join(tree, D.MANIFEST)))}
    files = []
    for dp, _, fs in os.walk(os.path.join(tree, "match")):
        for f in fs:
            if f.endswith((".cpp", ".h", ".inl", ".c")):
                p = os.path.join(dp, f)
                files.append((os.path.relpath(p, tree), open(p, errors="replace").read()))
    asserts = {}
    for rel, text in files:
        for m in ASSERT.finditer(text):
            asserts.setdefault((m.group(1), m.group(2)), int(m.group(3), 0))
    found = []
    for rel, text in files:
        if rel.endswith(".cpp") and "Read" in text:
            found += readers(rel, text, man)
    keep = []
    for r in found:
        row = r.pop("row")
        r["status"] = row["status"] if row else None
        r["pct"] = row.get("pct") if row else None
        if only and r["cls"] not in only:
            continue
        if not (row and (row["status"] == "matched" or (include_partial and row["status"] == "partial"))):
            continue
        keep.append(r)
    # offsets: asserts first, then the +0xNNN comment on the member's declaration inside a definition of the class
    defs = collections.defaultdict(list)      # class -> [(rel, l0, l1, lines)]
    for rel, text in files:
        lines = text.split("\n")
        for name, l0, l1 in class_bodies(text):
            defs[name].append((rel, l0, l1, lines))
    for r in keep:
        off = asserts.get((r["cls"], r["field"]))
        r["offset_from"] = "assert" if off is not None else None
        if off is None:
            for rel, l0, l1, lines in defs.get(r["cls"], []):
                for k in range(l0, min(l1, len(lines))):
                    if re.search(r"\b%s\b\s*(\[[^\]]*\])?\s*;" % re.escape(r["field"]), lines[k]):
                        mo = MEMBER_OFF.search(lines[k])
                        if mo:
                            off, r["offset_from"] = int(mo.group(1), 16), "comment %s:%d" % (rel, k + 1)
                            break
                if off is not None:
                    break
        r["offset"] = ("0x%X" % off) if off is not None else None
    # unknown sites, per (class, offset)
    wanted = collections.defaultdict(list)
    for r in keep:
        if r["offset"]:
            wanted[(r["cls"], int(r["offset"], 16))].append(r)
    sites = {}
    bodies_cache = {}
    for (cls, off), rs in wanted.items():
        decl, use = [], []
        for rel, l0, l1, lines in defs.get(cls, []):
            for k in range(l0 - 1, min(l1, len(lines))):
                ln = lines[k]
                if "unknown" not in ln or not re.search(r";", ln):
                    continue
                mo = MEMBER_OFF.search(ln)
                um = UNKNOWN.search(ln)
                if not um:
                    continue
                if (int(mo.group(1), 16) if mo else int(um.group(1), 16)) == off:
                    decl.append(dict(file=rel, line=k + 1, text=ln.strip()[:110]))
        pat = re.compile(r"\bunknown_(?:[A-Za-z]+_)?0*%X\b" % off, re.I)
        for rel, text in files:
            if not re.search(r"\b%s\b" % re.escape(cls), text):
                continue
            lines = text.split("\n")
            if rel not in bodies_cache:
                bodies_cache[rel] = [(l0, l1, h) for h, _, l0, l1 in cppscan.function_bodies(text)] if rel.endswith(".cpp") else []
            meth = bodies_cache[rel]
            for k, ln in enumerate(lines, 1):
                if not pat.search(ln) or ln.lstrip().startswith("//"):
                    continue
                if any(d["file"] == rel and d["line"] == k for d in decl):
                    continue
                if not re.search(r"(->|\.)\s*unknown_|^\s*unknown_|[^\w]unknown_", ln):
                    continue
                inm = next((h for l0, l1, h in meth if l0 <= k <= l1), None)
                definite = bool(inm and re.search(r"\b%s\s*::" % re.escape(cls), inm.split("(")[0]))
                use.append(dict(file=rel, line=k, how="method of %s" % cls if definite else "possible (file mentions %s)" % cls, text=ln.strip()[:110]))
        sites[(cls, off)] = (decl, use)
    res = []
    for (cls, off), rs in sorted(wanted.items(), key=lambda x: (x[0][0], x[0][1])):
        decl, use = sites[(cls, off)]
        res.append(dict(cls=cls, offset="0x%X" % off, names=sorted({r["field"] for r in rs}), keys=sorted({r["key"] for r in rs}),
                        readers=sorted({(r["addr"], r["status"], r["pct"]) for r in rs}, key=str), declarations=decl, uses=use))
    unresolved = [r for r in keep if not r["offset"]]
    return keep, res, unresolved


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=os.environ.get("GAG_WORKTREE") or D.L.REPO_ROOT)
    ap.add_argument("--class", dest="classes", action="append", default=[])
    ap.add_argument("--include-partial", action="store_true")
    ap.add_argument("--possible", action="store_true", help="also list uses in files that merely mention the class (noisy)")
    ap.add_argument("--json")
    ap.add_argument("--limit", type=int, default=0, help="print at most N classes' offsets with sites (0 = all)")
    a = ap.parse_args(argv)
    keep, res, unresolved = analyse(a.tree, set(a.classes), a.include_partial)
    withsites = [x for x in res if x["declarations"] or any(a.possible or u["how"].startswith("method") for u in x["uses"])]
    print("%d INI statements in %d matched%s readers; %d resolved to a class offset; %d offsets still unknown elsewhere" % (
        len(keep), len({(r["cls"], r["addr"]) for r in keep}), "/partial" if a.include_partial else "", len(res), len(withsites)))
    for x in (withsites[:a.limit] if a.limit else withsites):
        print("%s +%s  %s  (INI key %s; reader %s)" % (x["cls"], x["offset"], "/".join(x["names"]), "/".join(x["keys"]),
                                                       ", ".join("%s %s%s" % (r[0], r[1], "" if r[2] in (None, 100) else " %s%%" % r[2]) for r in x["readers"])))
        for d in x["declarations"]:
            print("    declaration %s:%d  %s" % (d["file"], d["line"], d["text"]))
        uses = [u for u in x["uses"] if a.possible or u["how"].startswith("method")]
        for u in uses[:12]:
            print("    use %s:%d  [%s]  %s" % (u["file"], u["line"], u["how"], u["text"]))
        if len(uses) > 12:
            print("    ... %d more uses" % (len(uses) - 12))
    if unresolved:
        print("%d statements without a resolvable offset (no assert or +0x comment for Class::Field):" % len(unresolved))
        for r in unresolved[:10]:
            print("    %s::%s  %s  %s:%d" % (r["cls"], r["field"], r["key"], r["file"], r["line"]))
    if a.json:
        json.dump(dict(statements=keep, offsets=res), open(a.json, "w"), indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
