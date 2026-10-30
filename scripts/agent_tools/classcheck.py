#!/usr/bin/env python3
# Provenance: original; compiles a probe with our VC6 wrapper and compares with our binary-mined data.
"""classcheck.py — verify one class's declared layout against binary evidence.

Usage: classcheck.py CLASS [--header match/path.h] [--json] [--no-write]

1. Finds every `class CLASS {` / `struct CLASS {` / `: ... CLASS` view definition
   under match/ and reports duplicates/conflicts. The canonical header is
   --header, else match/_layout/*, else the only definition.
2. Compiles a probe TU with the worktree's scripts/vc6/vc6cl.sh (locked default
   flags) that #includes the header and stores sizeof/offsetof of every
   parsed data member into initialised globals; the values are read back from
   the probe .obj. A derived probe class adds one virtual and defines its
   destructor so cl emits its vtables: the index of the added slot is the
   declared primary vtable slot count; other vtables' sizes are listed too.
3. Checks against binary evidence:
     class_sizes.json        PUSH n; CALL operator new sizes (confidence, sites)
     ctor_field_offsets.json constructor stores: each mined offset must start a
                             member or fall inside one (never in no member)
     rtti_classes.json       RTTI name, base chain, vtable VAs per base offset
     cache/vtable_slots.json retail slot count per vtable, and the manifest
                             name of each slot target
4. Writes $GAG_WORKTREE/state/orchestration/class_reports/CLASS.json with
   "verified" (a declared value agreeing with a binary-derived value) and
   "unproven" (no evidence, or disagreement) lists.

Limits: the member parser is line/regex based (no templates in member types
with commas, no bitfields, no nested class bodies); private members are made
reachable by #define private/protected public in the probe only.
"""
import argparse
import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common  # noqa: E402

KW_SKIP = ("typedef", "static", "friend", "enum", "using", "template", "public:", "private:",
           "protected:", "virtual", "explicit", "inline", "operator", "#", "class ", "struct ", "union ")


def strip_comments(t):
    t = re.sub(r"/\*.*?\*/", " ", t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


def find_definitions(cls):
    """Every definition of cls, and every class whose base list or name says it views cls."""
    defs, views = [], []
    pat = re.compile(r"^\s*(?:class|struct)\s+(?:__declspec\([^)]*\)\s*)?(" + re.escape(cls) + r")\s*(?::[^{;]*)?\{", re.M)
    view_pat = re.compile(r"^\s*(?:class|struct)\s+(\w*" + re.escape(cls.replace("Class", "")) + r"\w*View\w*)\b[^;{]*\{", re.M)
    for p in sorted((common.WORKTREE / "match").rglob("*")):
        if p.suffix not in (".h", ".hpp", ".cpp"):
            continue
        t = p.read_text(errors="replace")
        rel = str(p.relative_to(common.WORKTREE))
        for m in pat.finditer(t):
            defs.append(dict(file=rel, line=t.count("\n", 0, m.start()) + 1))
        for m in view_pat.finditer(t):
            views.append(dict(file=rel, line=t.count("\n", 0, m.start()) + 1, name=m.group(1)))
    return defs, views


def class_body(text, cls):
    t = strip_comments(text)
    m = re.search(r"(?:class|struct)\s+(?:__declspec\([^)]*\)\s*)?" + re.escape(cls) + r"\s*(:[^{;]*)?\{", t)
    if not m:
        return None, None
    i, depth = m.end(), 1
    while depth and i < len(t):
        depth += {"{": 1, "}": -1}.get(t[i], 0)
        i += 1
    return t[m.end():i - 1], (m.group(1) or "").lstrip(":").strip()


def parse_members(body):
    """Data members at brace depth 0 of the class body, in order."""
    out, depth, cur = [], 0, ""
    for ch in body:
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                cur = ""
            continue
        if depth:
            continue
        if ch == ";":
            decl = " ".join(cur.split())
            cur = ""
            decl = re.sub(r"^(public|private|protected)\s*:\s*", "", decl)
            if not decl or decl.startswith(KW_SKIP) or ":" in decl.replace("::", ""):
                continue
            if "(" in decl and not re.search(r"\(\s*(?:__\w+\s+)?\*\s*\w+\s*\)", decl):
                continue  # function declaration
            fp = re.search(r"\(\s*(?:__\w+\s+)?\*\s*(\w+)\s*\)", decl)
            if fp:
                out.append(fp.group(1))
                continue
            first = re.search(r"(\w+)\s*(\[[^\]]*\]\s*)*(=.*)?$", decl.split(",")[0])
            if first:
                out.append(first.group(1))
            for p in decl.split(",")[1:]:
                m = re.match(r"\s*[*&]*\s*(\w+)", p)
                if m:
                    out.append(m.group(1))
            continue
        cur += ch
        if ch == ":" and re.search(r"\b(public|private|protected)\s*:$", cur):
            cur = ""
    return out


def winpath(p):
    return "Z:" + str(p).replace("/", "\\")


def compile_probe(header, cls, members, vtable=True):
    lines = ["#define private public", "#define protected public",
             f'#include "{winpath(header)}"', "#undef private", "#undef protected", "#include <stddef.h>",
             f"int gg_probe_sizeof = sizeof({cls});"]
    for i, m in enumerate(members):
        lines.append(f"int gg_probe_off_{i} = offsetof({cls}, {m});")
    probe = lines + [f"struct GGProbe : public {cls} {{ virtual void gg_probe_end(); ~GGProbe(); }};",
                     "GGProbe::~GGProbe() {}"]
    tmp = Path(tempfile.mkdtemp(prefix="classcheck_", dir=common.CACHE))
    res = {}
    for variant, src in ((("full", probe),) if vtable else ()) + (("layout", lines),):
        cpp = tmp / f"probe_{variant}.cpp"
        cpp.write_text("\n".join(src) + "\n")
        try:
            r = subprocess.run(["bash", str(common.WORKTREE / "scripts/vc6/vc6cl.sh"), f"/Foprobe_{variant}.obj", cpp.name],
                           cwd=tmp, capture_output=True, text=True, timeout=90,
                           # /Od keeps the probe destructor's vptr store (so cl emits the
                           # vtable); layout does not depend on optimisation.
                           env=dict(os.environ, VC6_FLAGS="/nologo /c /Od /DNDEBUG"))
        except subprocess.TimeoutExpired:
            res = {"compiler_output": "probe compile timed out (90 s)"}
            continue
        obj = tmp / f"probe_{variant}.obj"
        if obj.exists():
            res = read_probe(obj, len(members))
            res["probe_variant"] = variant
            res["compiler_output"] = None
            break
        res = {"compiler_output": (r.stdout + r.stderr)[-3000:]}
    for p in tmp.iterdir():
        p.unlink()
    tmp.rmdir()
    return res


def read_probe(obj, n):
    data, sections, symbols, _ = common.parse_coff(obj)
    vals, vt = {}, {}
    by_name = {s["name"]: (i, s) for i, s in symbols.items()}
    for name, (i, s) in by_name.items():
        if name.startswith(("?gg_probe_sizeof", "?gg_probe_off_")) and s["section"] > 0:
            sec = sections[s["section"]]
            if sec["uninitialized"]:
                vals[name] = 0  # zero-valued globals land in .bss
                continue
            vals[name] = int.from_bytes(data[sec["raw_ptr"] + s["value"]: sec["raw_ptr"] + s["value"] + 4], "little")
        if name.startswith("??_7GGProbe@@6B") and s["section"] > 0:
            sec = sections[s["section"]]
            slots = [(r[0] - s["value"]) // 4 for r in sec["relocs"]]
            end_idx = None
            for rva, symidx, _ in sec["relocs"]:
                if "gg_probe_end" in symbols.get(symidx, {}).get("name", ""):
                    end_idx = (rva - s["value"]) // 4
            vt[name] = dict(slots=end_idx if end_idx is not None else (max(slots) + 1 if slots else 0),
                            primary=end_idx is not None)
    size = next((v for k, v in vals.items() if k.startswith("?gg_probe_sizeof")), None)
    offs = [next((v for k, v in vals.items() if k.startswith(f"?gg_probe_off_{i}@")), None) for i in range(n)]
    return dict(sizeof=size, offsets=offs, vtables=vt)


def evidence(cls):
    ev = {}
    cs = [r for r in common.load_json("class_sizes.json")["classes"] if r.get("class") == cls]
    ev["alloc_sizes"] = [dict(ctor=r["constructor"], size=r["sizeof"], sites=r["allocation_sites"],
                              agreeing=r["sites_agreeing"], confidence=r.get("size_confidence"),
                              base_ctor=r.get("is_base_constructor", False)) for r in cs]
    offs = {}
    for c in common.load_json("ctor_field_offsets.json")["constructors"]:
        if c.get("class") != cls:
            continue
        for f in c["fields"]:
            o = offs.setdefault(f["offset"], dict(width=set(), kinds=set(), proofs=[]))
            o["width"].add(f["width"])
            o["kinds"].update(f["kinds"])
            o["proofs"].append(f["proofs"][0]["at"])
    ev["ctor_offsets"] = offs
    rt = [v for v in common.load_json("rtti_classes.json")["classes"].values() if v["demangled_name"] == cls]
    ev["rtti"] = rt[0] if rt else None
    vtf = common.CACHE / "vtable_slots.json"
    if vtf.exists():
        vts = json.loads(vtf.read_text())["vtables"]
    else:
        print("classcheck: %s is missing, so vtable slot checks are skipped (reported unproven). Build it with:\n"
              "  python3 scripts/orchestration/vtable_slots.py \"$GAMEMD_BINARY\" scripts/data/rtti_classes.json "
              "scripts/agent_tools/cache/vtable_slots.json --manifest scripts/data/match_manifest.json" % vtf,
              file=sys.stderr)
        vts = []
    ev["vtables"] = [v for v in vts if v["class"] == cls]
    return ev


def check(cls, header=None):
    defs, views = find_definitions(cls)
    if header is None:
        lay = [d for d in defs if d["file"].startswith("match/_layout/")]
        pick = lay or defs
        if not pick:
            raise SystemExit(f"no definition of {cls} under match/; pass --header")
        header = pick[0]["file"]
    hp = common.WORKTREE / header
    body, bases = class_body(hp.read_text(errors="replace"), cls)
    if body is None:
        raise SystemExit(f"{header}: no body for {cls}")
    members = parse_members(body)
    probe = compile_probe(hp, cls, members)
    ev = evidence(cls)
    rep = dict(cls=cls, header=header, bases=bases, definitions=defs, view_classes=views,
               duplicate_definitions=len(defs) > 1, probe={k: v for k, v in probe.items() if k != "offsets"},
               members=[dict(name=m, offset=hex(o) if o is not None else None)
                        for m, o in zip(members, probe.get("offsets") or [None] * len(members))])
    verified, unproven = [], []
    size = probe.get("sizeof")
    # sizeof
    good = [a for a in ev["alloc_sizes"] if not a["base_ctor"]]
    if size is None:
        unproven.append("sizeof: probe did not compile")
    elif good:
        sizes = {a["size"] for a in good}
        if sizes == {size}:
            verified.append(f"sizeof {size:#x} == operator-new size at {sum(a['agreeing'] for a in good)} site(s) "
                            f"(ctors {', '.join(str(a['ctor']) for a in good if a['ctor'])})")
        else:
            unproven.append(f"sizeof {size:#x} DISAGREES with allocation sizes {sorted(hex(s) for s in sizes)}")
    else:
        unproven.append(f"sizeof {size:#x}: no direct allocation site in class_sizes.json")
    # offsets
    starts = sorted((o, m) for m, o in zip(members, probe.get("offsets") or []) if o is not None)
    covered, inherited = set(), 0
    for off, info in sorted(ev["ctor_offsets"].items()):
        if "vptr" in info["kinds"]:
            continue
        if starts and off < starts[0][0]:
            inherited += 1
            continue  # base-class region: not parsed here, check the base header
        exact = [m for o, m in starts if o == off]
        inner = [m for o, m in starts if o < off] if starts else []
        if exact:
            verified.append(f"+{off:#x} {exact[0]}: ctor store at {info['proofs'][0]} (width {sorted(info['width'])})")
            covered.add(exact[0])
        elif inner and size is not None and off < size:
            unproven.append(f"+{off:#x}: ctor store at {info['proofs'][0]} falls inside {inner[-1]} (interior; ok for arrays/structs)")
        else:
            unproven.append(f"+{off:#x}: ctor store at {info['proofs'][0]} is outside every declared member")
    if inherited:
        unproven.append(f"{inherited} ctor store offset(s) below the first own member ({starts[0][0]:#x}) "
                        "belong to the base class; run classcheck on the base")
    for o, m in starts:
        if m not in covered and not m.startswith(("_vtable", "unknown_", "_pad", "pad")):
            unproven.append(f"+{o:#x} {m}: no constructor store mined (needs another instruction)")
    # rtti / vtables
    rt = ev["rtti"]
    if rt:
        verified.append(f"RTTI {rt['mangled_name']} TD {rt['type_descriptor_va']}; bases {' > '.join(rt['base_chain'][:6])}")
        rep["rtti_vtables"] = [dict(base_offset=l["base_offset"], vtable=l["vtable_va"]) for l in rt["locators"]]
    else:
        unproven.append(f"no RTTI TypeDescriptor named {cls}")
    slot_rows = []
    for v in ev["vtables"]:
        names = []
        for i, s in enumerate(v["slots"]):
            r = common.manifest_by_addr().get(int(s, 16))
            names.append(dict(slot=i, addr=s, name=(r[0]["name"] if r else common.name_of(int(s, 16))),
                              status=(r[0]["status"] if r else None)))
        slot_rows.append(dict(base_offset=v["base_offset"], vtable=v["vtable_va"], retail_slots=len(v["slots"]), slots=names))
    rep["retail_vtables"] = slot_rows
    prim = [v for v in probe.get("vtables", {}).values() if v["primary"]]
    retail_prim = [v for v in slot_rows if v["base_offset"] == 0]
    if prim and retail_prim and prim[0]["slots"] == 0:
        unproven.append(f"primary vtable: retail {retail_prim[0]['retail_slots']} slots; the declared class has no "
                        "C++ virtuals (vptrs modelled as fields), so slots are not checked")
    elif prim and retail_prim:
        a, b = prim[0]["slots"], retail_prim[0]["retail_slots"]
        (verified if a == b else unproven).append(
            f"primary vtable: declared {a} slot(s), retail {b} (vtable {retail_prim[0]['vtable']})"
            + ("" if a == b else " — MISMATCH (retail walk stops at first non-.text dword; check by hand)"))
    elif retail_prim:
        unproven.append(f"primary vtable: retail {retail_prim[0]['retail_slots']} slots; declared class has no "
                        "C++ virtuals (vptrs modelled as fields?) or the vtable probe did not compile")
    rep["definition_probes"] = []
    canon = {m["name"]: m["offset"] for m in rep["members"]}
    for d in defs:
        if d["file"] == header or not d["file"].endswith(".h"):
            continue
        b, _ = class_body((common.WORKTREE / d["file"]).read_text(errors="replace"), cls)
        ms = parse_members(b or "")
        pr = compile_probe(common.WORKTREE / d["file"], cls, ms, vtable=False)
        if pr.get("sizeof") is None:
            rep["definition_probes"].append(dict(file=d["file"], error="probe did not compile"))
            continue
        offs = {m: hex(o) for m, o in zip(ms, pr["offsets"]) if o is not None}
        clash = {m: (canon[m], o) for m, o in offs.items() if m in canon and canon[m] != o}
        rep["definition_probes"].append(dict(file=d["file"], sizeof=hex(pr["sizeof"]), members=len(ms),
                                             offset_conflicts=clash))
        if clash or (size is not None and pr["sizeof"] > size):
            unproven.append(f"CONFLICT {d['file']}: sizeof {pr['sizeof']:#x} vs {size:#x}" +
                            (f"; offsets {clash}" if clash else ""))
    if len(defs) > 1:
        unproven.append(f"{len(defs)} definitions of {cls}: " + ", ".join(f"{d['file']}:{d['line']}" for d in defs))
    rep["verified"], rep["unproven"] = verified, unproven
    return rep


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cls")
    ap.add_argument("--header")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--no-write", action="store_true")
    a = ap.parse_args(argv)
    rep = check(a.cls, a.header)
    if not a.no_write:
        out = common.STATE / "class_reports" / f"{a.cls.replace('<', '_').replace('>', '_').replace('*', 'P')}.json"
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(rep, indent=1, default=sorted))
    if a.json:
        print(json.dumps(rep, indent=1, default=sorted))
        return
    pr = rep["probe"]
    print(f"== {rep['cls']}  header {rep['header']}  bases: {rep['bases'] or '-'}")
    if pr.get("compiler_output"):
        print("  PROBE FAILED:\n    " + pr["compiler_output"].strip().replace("\n", "\n    "))
    else:
        print(f"  sizeof {pr['sizeof']:#x}   probe vtables: " +
              (", ".join(f"{k}={v['slots']}{'*' if v['primary'] else ''}" for k, v in pr["vtables"].items()) or "none"))
    for m in rep["members"]:
        print(f"    {m['offset'] or '?':>7}  {m['name']}")
    print(f"  definitions: {len(rep['definitions'])}  view classes: " + (", ".join(v["name"] for v in rep["view_classes"]) or "-"))
    for d in rep["definitions"]:
        pr = next((x for x in rep["definition_probes"] if x["file"] == d["file"]), None)
        print(f"    {d['file']}:{d['line']}" + (f"  -> {pr}" if pr else ""))
    for v in rep["retail_vtables"]:
        print(f"  retail vtable +{v['base_offset']} {v['vtable']}: {v['retail_slots']} slots, "
              f"{sum(1 for s in v['slots'] if s['status'] == 'matched')} matched in manifest")
    print("-- verified facts")
    for s in rep["verified"]:
        print("  + " + s)
    print("-- unproven")
    for s in rep["unproven"]:
        print("  ? " + s)


if __name__ == "__main__":
    main()
