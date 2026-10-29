#!/usr/bin/env python3
# Provenance: original. Placement stage for trivgen: put verified functions into the migrated original-TU files.
"""cheapgen.py  place | gates   (after `trivgen.py run`; see README "Placement").

place: take WORK/run_state.json (verified-exact set from the probe), then
  * hold static-initialiser shapes unless their address falls inside a migrated original-TU file
    (match/**/<AssertName>.cpp whose tu_map text range holds it);
  * hold vtable-slot members whose RTTI class already has a header (never add a per-TU view of such a class);
  * insert the remaining functions into the migrated TU file that holds their address (decl block + bodies, ascending
    address order), or write a new trivial_tuNNN_* file for TUs that have no migrated file yet;
  * compile every touched file, verify every new row (raw_match + strict verify_relocations with the central bindings),
    drop what fails and rebuild, until stable.
Writes WORK/place_state.json and leaves the sources in the worktree.
"""
import collections
import csv
import json
import os
import re
import subprocess
import sys
from pathlib import Path

import trivgen as T
import canon
import data
import gen
import verify
from lift import Unsupported

WT, WORK = T.WT, T.WORK
INC_STD = '#include <stddef.h>'


def tracked_names():
    r = subprocess.run(["git", "-C", str(WT), "ls-files", "match"], capture_output=True, text=True)
    return r.stdout.split()


def migrated_files():
    """tu file (match/..cpp) -> (lo, hi, tu_id): an assert-named original TU that exists in the manifest."""
    rows = list(csv.DictReader(open(data.TUMAP)))
    byname = collections.defaultdict(list)
    for r in rows:
        n = r["name_or_bound"]
        if re.search(r"\.(cpp|CPP)$", n) and " " not in n:
            byname[n.lower()].append(r)
    man = json.load(open(WT / "scripts/data/match_manifest.json"))
    tus = {m["tu"] for m in man}
    out = {}
    for f in sorted(tus):
        b = os.path.basename(f).lower()
        for r in byname.get(b, [])[:1]:
            out.setdefault(r["tu_id"], []).append((f, int(r["text_lo"], 16), int(r["text_hi"], 16)))
    return out


def trivial_dirs():
    d = {}
    for p in tracked_names():
        m = re.search(r"match/(.+)/trivial_(tu\d+)(?:_init)?(?:_[a-z])?_methods\.", p)
        if m:
            d.setdefault(m.group(2).upper(), m.group(1))
    return d


def class_has_header(cls_full):
    cls = cls_full.split("::")[-1]
    return bool(canon.headers().get(cls))


def all_vtable_classes(it):
    return sorted({e[0] for e in it["vtable"]})


# ------------------------------------------------------------------ classification
def classify(items, exact, mig):
    """-> dict addr -> ('hold', reason) | ('file', path) | ('bin', None)"""
    plan = {}
    for it in items:
        a = it["addr"]
        if a not in exact:
            continue
        init = it["pattern"] in T.INIT_PATTERNS
        tu = it["tu_id"]
        home = None
        for f, lo, hi in mig.get(tu, []):
            if lo <= a <= hi:
                home = f
                break
        if home is None:
            # an address can lie in a migrated TU whose tu_id differs from the worklist's
            for tid, lst in mig.items():
                for f, lo, hi in lst:
                    if lo <= a <= hi:
                        home = f
        if init:
            plan[a] = ("file", home) if home else ("hold", f"static initialiser: TU {tu} has no migrated original-TU file yet")
            continue
        if it.get("vtable"):
            classes = all_vtable_classes(it)
            top, slot, _ = canon.owner_of(it["vtable"])
            owner_hdr = [c for c in classes if class_has_header(c)]
            if owner_hdr and not exact[a]["var"].get("canon"):
                plan[a] = ("hold", f"vtable slot {slot} of {top}: {', '.join(owner_hdr)} has a header; "
                                   "the slot is not declared there (header proposal, no per-TU view)")
                continue
        plan[a] = ("file", home) if home else ("bin", None)
    return plan


# ------------------------------------------------------------------ insertion into an existing TU file
MARK = re.compile(r"^// (?:FUNCTION|SYNTHETIC|STUB|TEMPLATE|LIBRARY): GAMEMD (0x[0-9A-Fa-f]+)(.*)$")


def insertion_points(lines):
    """[(address, line_index_of_first_comment_line_of_its_block)] for column-zero body markers, in file order."""
    pts = []
    for i, l in enumerate(lines):
        m = MARK.match(l)
        if not m or "decl;" in m.group(2) or "declaration" in m.group(2):
            continue
        j = i
        while j > 0 and lines[j - 1].startswith("//") and not MARK.match(lines[j - 1]):
            j -= 1
        pts.append((int(m.group(1), 16), j))
    return pts


def decl_block(outs, module_dir):
    """Declarations (views, globals, callee prototypes, canonical includes) for outs, as text for a .cpp."""
    b = gen.Bin("x", module_dir)
    for o in outs:
        b.add(o)
    full = b.header_text(None).split("\n")
    # drop the preamble through the static-assert include, and the guard
    k = next(i for i, l in enumerate(full) if "gg_static_assert.h" in l)
    body = full[k + 1:]
    while body and body[-1] in ("", f"#endif  // {b.guard()}"):
        body.pop()
    # methods of views are defined out of line below: keep the struct text as the generator wrote it
    # callee prototypes in a .cpp must not read as body claims: use the decl; reloc marker form
    body = [l.replace(" (declaration)", " (decl; reloc)") if l.startswith("// FUNCTION: GAMEMD") else l for l in body]
    return "\n".join(body).strip("\n").replace(" (declaration)", " (decl; reloc)"), b


def build_file_text(orig, outs, path_rel):
    """orig: original text; outs: Out list for this file. Returns (new_text, spans{addr:(first,last) 1-based lines})."""
    lines = orig.split("\n")
    pts = insertion_points(lines)
    mod = str(Path(path_rel).parent.relative_to("match"))
    rel_static = os.path.relpath(WT / "match/_rt/gg_static_assert.h", WT / "match" / mod)
    block, b = decl_block(outs, mod)
    ins = collections.defaultdict(list)    # line index -> text blocks (in order)
    ordered = sorted(outs, key=lambda o: o.spec.addr)
    first_done = False
    for o in ordered:
        a = o.spec.addr
        at = next((j for (pa, j) in pts if pa > a), len(lines))
        txt = [f"// FUNCTION: GAMEMD 0x{a:X}"]
        if o.pattern:
            txt.append(f"// {o.pattern}")
        txt.append(o.body.rstrip("\n"))
        txt.append("")
        ins[at].append((a, "\n".join(txt)))
    pre = [INC_STD, f'#include "{rel_static}"', ""]
    if all(INC_STD not in l for l in lines):
        pass
    out_lines = []
    spans = {}
    cur = 0
    first_at = min(ins)
    for idx in range(len(lines) + 1):
        if idx in ins:
            if idx == first_at:
                blk = [l for l in pre if not l.strip() or not any(l.strip() == x.strip() for x in lines[:idx])]
                out_lines += blk + block.split("\n") + [""]
            for a, t in sorted(ins[idx]):
                start = len(out_lines) + 1
                out_lines += t.split("\n")
                spans[a] = (start, len(out_lines))
        if idx < len(lines):
            out_lines.append(lines[idx])
    return "\n".join(out_lines), spans, b


# ------------------------------------------------------------------ the place command
def place():
    d = T.load_items()
    items = T.do_lift(d["items"])
    state = json.loads((WORK / "run_state.json").read_text())
    exact = {int(k, 16): v for k, v in state["exact"].items()}
    mig = migrated_files()
    plan = classify(items, exact, mig)
    byaddr = {i["addr"]: i for i in items}
    held = {a: p[1] for a, p in plan.items() if p[0] == "hold"}
    T.TAKEN.update(os.path.basename(p) for p in tracked_names())
    tdirs = trivial_dirs()
    tus, votes = data.tu_info()
    T.module_for_tu = lambda tu, v: tdirs.get(tu) or max((v.get(tu) or {"core": 1}).items(), key=lambda kv: kv[1])[0]

    dropped = {}
    for attempt in range(6):
        keep = {a for a, p in plan.items() if p[0] in ("file", "bin") and a not in dropped}
        # clean previous generation
        T.clean_generated()
        subprocess.run(["git", "-C", str(WT), "checkout", "--", "match"], check=True)
        outs = {}
        for a in sorted(keep):
            it = byaddr[a]
            try:
                o = T.emit_item(it, exact[a]["var"])
            except Unsupported as e:
                dropped[a] = "emit: " + str(e)
                continue
            o.pattern = T.patterns.describe(it["pattern"]) + T.describe_owner(it)
            outs[a] = o
        bins_items = [byaddr[a] for a in sorted(outs) if plan[a][0] == "bin"]
        bins = T.plan_bins(bins_items, {a: exact[a]["var"] for a in outs}, votes, None) if bins_items else []
        T.write_bins(bins)
        files = collections.defaultdict(list)
        for a, o in outs.items():
            if plan[a][0] == "file":
                files[plan[a][1]].append(o)
        spans, fbins = {}, {}
        for f, os_ in files.items():
            orig = subprocess.run(["git", "-C", str(WT), "show", f"HEAD:{f}"], capture_output=True, text=True).stdout
            try:
                text, sp, b = build_file_text(orig, os_, f)
            except Unsupported as e:
                for o in os_:
                    dropped[o.spec.addr] = "insert: " + str(e)
                continue
            (WT / f).write_text(text)
            spans[f] = sp
            fbins[f] = b
        # compile everything touched
        targets = [(f"match/{b.module}/{b.name}.cpp", b, None) for b in bins] + [(f, fbins[f], spans[f]) for f in fbins]
        bad_now = {}
        results = {}
        for rel, b, sp in targets:
            obj, errs, text = verify.compile_bin(rel)
            results[rel] = (obj, errs, text)
            if obj is not None:
                continue
            bad = set()
            if sp is None:
                bad, _ = T.attribute_errors(b, errs)
            else:
                lines = (WT / rel).read_text().split("\n")
                for fn, line, code, msg in errs:
                    hit = [a for a, (lo, hi) in sp.items() if lo <= line <= hi]
                    if hit:
                        bad.update(hit)
                        continue
                    names = re.findall(r"(?:Obj|Arg\d+|Sub|Gbl|Gptr)_([0-9A-F]{8})|(?:FUN|DAT)_([0-9A-F]{8})", lines[line - 1] if 0 < line <= len(lines) else "")
                    for x in names:
                        h = x[0] or x[1]
                        bad.add(int(h, 16))
            if not bad or not (bad & set(outs)):
                bad = {o.spec.addr for o in b.items} if sp is None else {a for a in sp}
            reason = (errs[0][2] + " " + errs[0][3]) if errs else "compile"
            for a in bad & set(outs):
                bad_now[a] = f"compile ({rel}): {reason}"
        if bad_now:
            dropped.update(bad_now)
            print(f"attempt {attempt}: compile failures {len(bad_now)}", file=sys.stderr)
            continue
        # verify
        jobs = []
        for rel, b, sp in targets:
            obj = results[rel][0]
            smp = WORK / ("smap_" + Path(rel).stem + ".json")
            smp.write_text(json.dumps(verify.symbol_map(obj)))
            for o in (b.items if sp is None else [outs[a] for a in sp if a in outs]):
                jobs.append((rel, obj, o, smp))
        import concurrent.futures as cf

        def chk(j):
            rel, obj, o, smp = j
            return o, rel, verify.check_function(obj, o.spec.addr, o.spec.size, smp, hint=o.sym_hint)

        checks = {}
        with cf.ThreadPoolExecutor(8) as ex:
            for o, rel, r in ex.map(chk, jobs):
                r["file"] = rel
                checks[o.spec.addr] = r
        fails = {a: "gate: " + r["why"] for a, r in checks.items() if not r["ok"]}
        if fails:
            dropped.update(fails)
            print(f"attempt {attempt}: gate failures {len(fails)}", file=sys.stderr)
            continue
        break
    else:
        raise SystemExit("did not stabilise")
    for a, w in dropped.items():
        held[a] = w
    st = dict(plan={hex(a): list(p) for a, p in plan.items()}, held={hex(a): w for a, w in held.items()},
              checks={hex(a): {k: v for k, v in r.items() if k != "rout"} for a, r in checks.items()},
              files={hex(a): plan[a][1] for a in checks if plan[a][0] == "file"})
    (WORK / "place_state.json").write_text(json.dumps(st, indent=1))
    c = collections.Counter(("exact:" + plan[a][0]) for a in checks)
    print("placed", dict(c), "held", len(held))
    cw = collections.Counter(w.split(":")[0] for w in held.values())
    print(dict(cw))


def packet():
    """Rows, results, header proposals and held list from place_state.json (gates are run by the caller)."""
    st = json.loads((WORK / "place_state.json").read_text())
    d = T.load_items()
    items = T.do_lift(d["items"])
    byaddr = {i["addr"]: i for i in items}
    exact = {int(k, 16): v for k, v in json.loads((WORK / "run_state.json").read_text())["exact"].items()}
    rows, results = [], []
    for ha, r in sorted(st["checks"].items(), key=lambda kv: int(kv[0], 16)):
        a = int(ha, 16)
        it = byaddr[a]
        o = T.emit_item(it, exact[a]["var"])
        rel = r["file"]
        name = o.mname or (f"{o.member_of}::FUN_{a:08X}" if o.member_of else f"FUN_{a:08X}")
        rows.append(dict(tu=rel, addr=f"0x{a:X}", sym=r["sym"], len=hex(o.spec.size), name=name, status="matched", pct=100))
        ev = [T.describe_owner(it).strip() or "no-vtable-slot"]
        results.append((f"0x{a:X}", r["sym"], 100, "match: 100.0%", r.get("relocs", ""), "matched", o.kind, it["pattern"], "; ".join(ev)))
    (WORK / "rows.json").write_text(json.dumps(rows, indent=1) + "\n")
    (WORK / "results.tsv").write_text("addr\tsymbol\tpct\traw\trelocs\tstatus\tconvention\tpattern\tevidence\n" +
                                      "\n".join("\t".join(map(str, x)) for x in results) + "\n")
    props = []
    for ha, why in sorted(st["held"].items(), key=lambda kv: int(kv[0], 16)):
        a = int(ha, 16)
        it = byaddr[a]
        props.append((ha, it["pattern"], it.get("tu_id", ""), why))
    (WORK / "held.tsv").write_text("addr\tpattern\ttu\treason\n" + "\n".join("\t".join(p) for p in props) + "\n")
    print(len(rows), "rows;", len(props), "held")


if __name__ == "__main__":
    {"place": place, "packet": packet}[sys.argv[1]]()
