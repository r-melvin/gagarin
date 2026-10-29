#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: own-binary (pinned retail gamemd.exe read directly; the data/*.json inputs are
# census files derived from the same image). No external source contributed any fact.
"""Evidence-graded map from every .text function to its original translation unit.

Two stages:
  extract  (needs the pinned PE, GAMEMD_BINARY or --binary)  -> scripts/data/tu_evidence.json
           assert __FILE__ push sites, vtable slot targets, scalar-deleting-destructor shapes.
  partition (no binary needed)                               -> scripts/data/original_tu_map.json
           + a markdown report.

Signals, strongest first:
  witnessed            a D:\\ra2mdpost\\*.cpp assert string is referenced from the function
  inferred-contiguity  the function lies between two functions of the same TU
  inferred-class       a vtable slot target owned by exactly one class (not inherited)
  comdat               template / compiler-generated / inline-leaked: never forced onto a TU
  unknown              bracket only (see `bracket`): sorts between two witnessed TUs
"""
import argparse
import bisect
import collections
import hashlib
import json
import os
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / "scripts" / "data"
ASSERT_PREFIX = b"D:\\ra2mdpost\\"
KINDS = ("witnessed", "inferred-class", "inferred-contiguity", "comdat", "unknown")


# --------------------------------------------------------------------------- extraction
def _load_pe(path):
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from verify_vtable import load_pe
    sha = json.loads((DATA / "rtti_classes.json").read_text())["_meta"]["sha256"]
    return load_pe(path, sha)


def _section_bytes(data, sections, name):
    for n, start, vsize, rawptr, rawsize in sections:
        if n == name:
            return start, data[rawptr:rawptr + min(vsize, rawsize)]
    raise SystemExit("no %s section" % name)


def extract_evidence(binary, rtti):
    data, base, sections = _load_pe(binary)
    tstart, text = _section_bytes(data, sections, ".text")
    tend = tstart + len(text)

    def read(va, n):
        for _, s, vs, rp, rs in sections:
            if s <= va and va + n <= s + min(vs, rs):
                return data[rp + va - s: rp + va - s + n]
        return None

    # 1. assert strings anywhere in the image
    files = {}
    for _, s, vs, rp, rs in sections:
        blob = data[rp:rp + min(vs, rs)]
        i = blob.find(ASSERT_PREFIX)
        while i >= 0:
            j = blob.index(b"\0", i)
            name = blob[i + len(ASSERT_PREFIX):j].decode("ascii")
            if name not in files:
                files[name] = {"file": name, "string_va": "0x%08X" % (s + i), "sites": []}
            i = blob.find(ASSERT_PREFIX, j)
    for f in files.values():
        va = int(f["string_va"], 16)
        pat = struct.pack("<I", va)
        p = text.find(pat)
        while p >= 0:
            site = tstart + p - 1
            if p >= 1 and text[p - 1] == 0x68:
                line = None
                if p >= 6 and text[p - 6] == 0x68:
                    line = struct.unpack_from("<I", text, p - 5)[0]
                f["sites"].append({"site": "0x%X" % site, "line": line})
            else:
                f["sites"].append({"site": "0x%X" % (tstart + p), "line": None, "non_push": True})
            p = text.find(pat, p + 1)
    # 2. vtables
    locs = []
    for cls in rtti["classes"].values():
        for loc in cls["locators"]:
            locs.append(int(loc["vtable_va"], 16))
    stops = {v - 4 for v in locs}
    vtables = {}
    targets = set()
    for cls in rtti["classes"].values():
        out = []
        for loc in cls["locators"]:
            va = int(loc["vtable_va"], 16)
            slots = []
            while len(slots) < 600:
                a = va + 4 * len(slots)
                if a in stops and slots:
                    break
                b = read(a, 4)
                if b is None:
                    break
                t = struct.unpack("<I", b)[0]
                if not (tstart <= t < tend):
                    break
                slots.append("0x%X" % t)
            out.append({"vtable_va": "0x%X" % va, "base_offset": loc["base_offset"], "slots": slots})
            targets.update(int(x, 16) for x in slots)
        vtables[cls["demangled_name"] + "|" + cls["mangled_name"]] = out
    # 3. scalar deleting destructor shape: [call dtor] ... test byte [esp+4|8],1 ... call delete
    sdd = {}
    for t in sorted(targets):
        code = text[t - tstart: t - tstart + 40]
        m = re.search(rb"\xF6\x44\x24[\x04\x08]\x01", code)
        if not m or m.start() > 24:
            continue
        c = code.find(b"\xE8")
        if 0 <= c < m.start() and c + 5 <= len(code):
            rel = struct.unpack_from("<i", code, c + 1)[0]
            sdd["0x%X" % t] = "0x%X" % ((t + c + 5 + rel) & 0xFFFFFFFF)
    return {
        "schema": "gagarin/tu_evidence/1",
        "binary_sha256": hashlib.sha256(data).hexdigest(),
        "provenance": "own-binary: direct PE read of the pinned image (scripts/vc6/tu_partition.py extract)",
        "text_range": ["0x%X" % tstart, "0x%X" % tend],
        "asserts": sorted(files.values(), key=lambda f: int(f["string_va"], 16)),
        "vtables": vtables,
        "scalar_deleting": sdd,
    }


# --------------------------------------------------------------------------- partition
def _hx(v):
    return int(v, 16) if isinstance(v, str) else v


def _stem_key(name):
    return name.rsplit(".", 1)[0].casefold()


def longest_nondecreasing(seq):
    """Indices of a longest non-decreasing subsequence of ranks (O(n^2); n is a few hundred)."""
    n = len(seq)
    if not n:
        return []
    best = [1] * n
    prev = [-1] * n
    for i in range(n):
        for j in range(i):
            if seq[j] <= seq[i] and best[j] + 1 > best[i]:
                best[i] = best[j] + 1
                prev[i] = j
    i = max(range(n), key=lambda k: best[k])
    out = []
    while i >= 0:
        out.append(i)
        i = prev[i]
    return out[::-1]


def _is_comdat_name(mangled):
    return ("?$" in mangled) or mangled.startswith(("??_G", "??_E", "??__E", "_$E", "??_F"))


def owned_targets(vtables, rtti_classes):
    """target -> class (demangled) for slot targets owned by exactly one class root.

    A target is owned by class C when C's vtables contain it and no ancestor of C does. Targets
    reachable from several unrelated roots (_purecall, folded bodies) are left unowned."""
    by_dem = collections.defaultdict(list)
    chain = {}
    for key, cls in rtti_classes.items():
        d = cls["demangled_name"]
        chain[d] = set(cls.get("base_chain", [])[1:])
        by_dem[d].append(key)
    holders = collections.defaultdict(set)
    for key, vts in vtables.items():
        dem = key.split("|", 1)[0]
        for vt in vts:
            for s in vt["slots"]:
                holders[_hx(s)].add(dem)
    owner = {}
    for t, classes in holders.items():
        roots = {c for c in classes if not (chain.get(c, set()) & classes)}
        if len(roots) == 1:
            owner[t] = next(iter(roots))
    return owner


def partition(evidence, extents, rtti, names=None):
    names = names or {}
    entries = [(int(e[0], 16), int(e[1], 16), e[4]) for e in extents["entries"]]
    entries.sort()
    starts = [e[0] for e in entries]
    n = len(entries)

    def fn_of(addr):
        i = bisect.bisect_right(starts, addr) - 1
        return i if i >= 0 else None

    out = [{"addr": "0x%X" % a, "tu": None, "tu_kind": "unknown", "evidence": ""} for a, _, _ in entries]
    for i, (a, ln, kind) in enumerate(entries):
        if kind != "engine":
            out[i]["evidence"] = "extent kind %s (library/stub, not a game TU)" % kind
    eligible = [e[2] == "engine" for e in entries]

    # ---- witnessed
    files = sorted(evidence["asserts"], key=lambda f: _hx(f["string_va"]))
    rank = {f["file"]: r for r, f in enumerate(files)}
    refs = collections.defaultdict(collections.Counter)
    stray = 0
    for f in files:
        for s in f["sites"]:
            i = fn_of(_hx(s["site"]))
            if i is None or _hx(s["site"]) >= entries[i][0] + max(entries[i][1], 1) + 16:
                stray += 1
            if i is not None:
                refs[i][f["file"]] += 1
    wit = sorted(refs)
    primary = {i: max(sorted(refs[i]), key=lambda fl: (refs[i][fl], -rank[fl])) for i in wit}
    keep = longest_nondecreasing([rank[primary[i]] for i in wit])
    core = [wit[k] for k in keep]
    core_set = set(core)
    for i in wit:
        fl = primary[i]
        multi = len(refs[i]) > 1
        txt = "assert __FILE__ %s x%d" % (fl, refs[i][fl])
        if multi:
            txt += "; also " + ",".join("%s x%d" % (k, v) for k, v in sorted(refs[i].items()) if k != fl)
        if i in core_set:
            out[i].update(tu=fl, tu_kind="witnessed", evidence=txt)
        else:
            out[i].update(tu=None, tu_kind="comdat", hint_tu=None,
                          evidence=txt + "; out of link order for its address: inlined assert from another TU")
    arank = {i: rank[primary[i]] for i in core}
    # bracket machinery over core anchors
    core_addr = [entries[i][0] for i in core]

    def bracket(i):
        k = bisect.bisect_left(core_addr, entries[i][0])
        left = out[core[k - 1]]["tu"] if k > 0 else None
        right = out[core[k]]["tu"] if k < len(core) and core[k] != i else (
            out[core[k + 1]]["tu"] if k + 1 < len(core) and core[k] == i else None)
        return [left, right]

    # window in which TU of rank r may still have code: after last core anchor of lower rank,
    # before first core anchor of higher rank
    def window(r):
        lo = 0
        hi = n
        for i in core:
            if arank[i] < r:
                lo = max(lo, i)
        for i in reversed(core):
            if arank[i] > r:
                hi = min(hi, i)
        return lo, hi

    # ---- sandwiches (same-rank anchors): contiguity
    comdat_flag = {}
    for i in range(n):
        a = entries[i][0]
        nm = names.get(a)
        if nm and _is_comdat_name(nm):
            comdat_flag[i] = "symbol shape %s" % nm[:40]
        if "0x%X" % a in evidence.get("scalar_deleting", {}):
            comdat_flag[i] = "scalar deleting destructor shape (dtor 0x%X)" % _hx(evidence["scalar_deleting"]["0x%X" % a])
    sandwich = {}
    for x, y in zip(core, core[1:]):
        if arank[x] == arank[y]:
            for i in range(x + 1, y):
                sandwich[i] = out[x]["tu"]
    for i, tu in sandwich.items():
        if out[i]["tu_kind"] != "unknown" or not eligible[i]:
            continue
        if i in comdat_flag:
            out[i].update(tu=None, tu_kind="comdat", hint_tu=tu,
                          evidence="%s; lies inside the %s interval" % (comdat_flag[i], tu))
        else:
            out[i].update(tu=tu, tu_kind="inferred-contiguity",
                          evidence="between two %s asserts" % tu)

    # ---- class ownership
    classes = rtti["classes"]
    owner = owned_targets(evidence["vtables"], classes)
    template = {c["demangled_name"] for c in classes.values() if "<" in c["demangled_name"]}
    cls_fns = collections.defaultdict(list)
    for t, c in owner.items():
        i = fn_of(t)
        if i is not None and entries[i][0] == t and eligible[i]:
            cls_fns[c].append(i)
    # the function a class-owned scalar deleting destructor calls first is that class's destructor
    dtor_note = {}
    callers = collections.defaultdict(list)  # dtor index -> [(sdd addr, class)]
    for sd, dt in evidence.get("scalar_deleting", {}).items():
        c = owner.get(_hx(sd))
        i, k = fn_of(_hx(dt)), fn_of(_hx(sd))
        if c is None or c in template or i is None or entries[i][0] != _hx(dt) or not eligible[i]:
            continue
        out[k]["class"] = c
        callers[i].append((sd, c))
    anc = {cl["demangled_name"]: set(cl.get("base_chain", [])[1:]) for cl in classes.values()}
    for i, lst in callers.items():
        cs = {c for _, c in lst}
        roots = {c for c in cs if not (anc.get(c, set()) & cs)}
        if len(roots) != 1:
            continue  # called from unrelated classes' sdds: shared, leave it alone
        c = next(iter(roots))
        sd = next(s_ for s_, c_ in lst if c_ == c)
        cls_fns[c].append(i)
        dtor_note[i] = "destructor called by the scalar deleting destructor %s of %s" % (sd, c)
    # comdat for the rest of the shape-flagged functions outside TU intervals
    for i, why in comdat_flag.items():
        if out[i]["tu_kind"] == "unknown" and eligible[i]:
            out[i].update(tu=None, tu_kind="comdat", hint_tu=None, evidence=why)
    for c, fl in cls_fns.items():
        if c in template:
            for i in fl:
                if out[i]["tu_kind"] == "unknown":
                    out[i].update(tu=None, tu_kind="comdat", hint_tu=None,
                                  evidence="vtable slot of template instantiation %s" % c[:60])
    class_tu = {}
    for c, fl in sorted(cls_fns.items()):
        if c in template:
            continue
        votes = {out[i]["tu"] for i in fl if out[i]["tu_kind"] in ("witnessed", "inferred-contiguity")}
        if len(votes) == 1:
            class_tu[c] = next(iter(votes))
    for c, fl in sorted(cls_fns.items()):
        if c in template:
            continue
        todo = [i for i in fl if out[i]["tu_kind"] == "unknown"]
        if not todo:
            continue
        if c in class_tu:
            tu = class_tu[c]
            lo, hi = window(rank[tu])
            for i in todo:
                if lo < i < hi:
                    out[i].update(tu=tu, tu_kind="inferred-class",
                                  evidence="%s; the class's other slots lie in %s"
                                  % (dtor_note.get(i, "vtable slot owned by %s" % c), tu))
        todo = [i for i in fl if out[i]["tu_kind"] == "unknown"]
        if not todo:
            continue
        # group by band (previous core anchor index)
        bands = collections.defaultdict(list)
        for i in todo:
            bands[bisect.bisect_left(core_addr, entries[i][0])].append(i)
        for k, grp in sorted(bands.items()):
            lb, rb = bracket(grp[0])
            label = "class:%s" % c if len(bands) == 1 else "class:%s@after:%s" % (c, lb)
            for i in grp:
                out[i].update(tu=label, tu_kind="inferred-class", bracket=[lb, rb],
                              evidence="%s; file sorts between %s and %s"
                              % (dtor_note.get(i, "vtable slot owned by %s" % c), lb, rb))

    # ---- contiguity over the remaining runs (comdat and library functions are transparent)
    def open_(k):
        return (out[k]["tu_kind"] == "unknown" and eligible[k]) or out[k]["tu_kind"] == "comdat" or not eligible[k]

    i = 0
    while i < n:
        if not open_(i):
            i += 1
            continue
        j = i
        while j < n and open_(j):
            j += 1
        L, R = i - 1, j
        lt = out[L]["tu"] if L >= 0 else None
        rt = out[R]["tu"] if R < n else None
        for k in range(i, j):
            if out[k]["tu_kind"] != "unknown" or not eligible[k]:
                continue
            if lt is not None and lt == rt:
                out[k].update(tu=lt, tu_kind="inferred-contiguity",
                              evidence="between two %s functions (%s .. %s) with no other class-owned slot in between"
                              % (lt, out[L]["addr"], out[R]["addr"]))
            else:
                b = bracket(k)
                out[k].update(bracket=b, evidence="no TU evidence; sorts between %s and %s" % tuple(b))
        i = j
    for i in range(n):
        if out[i]["tu_kind"] == "comdat" and "hint_tu" not in out[i]:
            out[i]["hint_tu"] = None
    tus = []
    for f in files:
        mine = [i for i in range(n) if out[i]["tu"] == f["file"] and out[i]["tu_kind"] == "witnessed"]
        tus.append({"tu": f["file"], "string_va": f["string_va"], "assert_sites": len(f["sites"]),
                    "witnessed_functions": len(mine),
                    "lo": out[mine[0]]["addr"] if mine else None, "hi": out[mine[-1]]["addr"] if mine else None})
    cnt = collections.Counter(o["tu_kind"] for o in out)
    meta = {"functions": n, "by_kind": {k: cnt.get(k, 0) for k in KINDS},
            "assert_files": len(files), "assert_sites": sum(len(f["sites"]) for f in files),
            "stray_sites": stray,
            "out_of_order_witnessed_functions": len(wit) - len(core),
            "name_order_violations": sum(1 for a, b in zip(files, files[1:]) if _stem_key(a["file"]) > _stem_key(b["file"])),
            "classes_with_owned_slots": len(cls_fns)}
    return {"schema": "gagarin/original_tu_map/1",
            "binary_sha256": evidence.get("binary_sha256"),
            "provenance": "own-binary: scripts/data/tu_evidence.json (PE read), function_extents.json, rtti_classes.json; "
                          "generated by scripts/vc6/tu_partition.py",
            "kinds": list(KINDS), "meta": meta, "link_order": tus, "functions": out}


# --------------------------------------------------------------------------- report
LEADS = (("FileStraw", 0x477770), ("FilePipe", 0x477790), ("Straw", 0x4AEC10),
         ("Pipe", 0x4AEC80), ("ShapeButtonClass", 0x4B57F0))


def _label(rec):
    return rec["tu"] if rec["tu_kind"] in ("witnessed", "inferred-contiguity", "inferred-class") else None


def _where(rec):
    if rec is None:
        return "not in extents"
    b = rec.get("bracket")
    s = "tu=%s kind=%s" % (rec["tu"], rec["tu_kind"])
    if b:
        s += " bracket=(%s .. %s)" % tuple(b)
    if rec.get("hint_tu"):
        s += " inside=%s" % rec["hint_tu"]
    return s


def lead_rows(result, evidence):
    by = {_hx(r["addr"]): r for r in result["functions"]}
    core = sorted((_hx(r["addr"]), r["tu"]) for r in result["functions"] if r["tu_kind"] == "witnessed")
    addrs = [a for a, _ in core]

    def br(a):
        k = bisect.bisect_left(addrs, a)
        return (core[k - 1][1] if k else None, core[k][1] if k < len(core) else None)

    rows = []
    for name, sdd in LEADS:
        dtor = _hx(evidence.get("scalar_deleting", {}).get("0x%X" % sdd, "0"))
        rows.append({"class": name, "sdd": sdd, "dtor": dtor or None, "sdd_bracket": br(sdd),
                     "dtor_bracket": br(dtor) if dtor else None,
                     "same_bracket": bool(dtor) and br(sdd) == br(dtor),
                     "sdd_rec": by.get(sdd), "dtor_rec": by.get(dtor)})
    return rows


def manifest_mix(result, manifest):
    lab = {_hx(r["addr"]): r for r in result["functions"]}
    files = collections.defaultdict(lambda: collections.defaultdict(set))
    seen = set()
    for m in manifest:
        a = _hx(m["addr"])
        if a in seen or a not in lab:
            continue
        seen.add(a)
        files[m["tu"]]["_all"].add(a)
        l = _label(lab[a])
        if l:
            files[m["tu"]][l].add(a)
    mixed = []
    spread = collections.defaultdict(set)
    for f, d in files.items():
        labels = {k: v for k, v in d.items() if k != "_all"}
        for l in labels:
            spread[l].add(f)
        named = {k for k in labels if not k.startswith("class:")}
        if len(labels) > 1:
            mixed.append((f, len(d["_all"]), sum(len(v) for v in labels.values()), len(labels), len(named), labels))
    mixed.sort(key=lambda x: (-x[3], -x[2], x[0]))
    return mixed, spread, len(seen)


def render_report(result, evidence, manifest):
    m = result["meta"]
    tot = m["functions"]
    L = ["# Original TU partition report", "",
         "Functions in function_extents.json: %d; assert files %d; assert sites %d (%d stray, outside any function body); "
         "witnessed functions out of link order (demoted to comdat): %d; link-order name violations: %d."
         % (tot, m["assert_files"], m["assert_sites"], m["stray_sites"],
            m["out_of_order_witnessed_functions"], m["name_order_violations"]), "",
         "## Coverage by kind", "", "| kind | functions | share |", "|---|---:|---:|"]
    for k in KINDS:
        L.append("| %s | %d | %.1f%% |" % (k, m["by_kind"][k], 100.0 * m["by_kind"][k] / tot))
    eng = [r for r in result["functions"] if not r["evidence"].startswith("extent kind")]
    named = sum(1 for r in eng if _label(r) and not r["tu"].startswith("class:"))
    anyl = sum(1 for r in eng if _label(r))
    L += ["", "Game-code functions (extent kind engine): %d. With a real TU name (witnessed or contiguity or class-in-TU): "
          "%d (%.1f%%); with any label including class:X candidates: %d (%.1f%%)."
          % (len(eng), named, 100.0 * named / len(eng), anyl, 100.0 * anyl / len(eng)), ""]
    mixed, spread, nman = manifest_mix(result, manifest)
    L += ["## match/ files mixing more than one original TU (top 50)", "",
          "%d manifest functions were looked up. `labels` counts distinct original-TU labels (class:X are candidate TUs "
          "and may be the same real TU as a neighbour); `named` counts only labels that are real TU names." % nman, "",
          "| match file | manifest fns | labelled | labels | named | labels (fns) |", "|---|---:|---:|---:|---:|---|"]
    for f, a, b, c, d, labels in mixed[:50]:
        top = ", ".join("%s(%d)" % (k, len(v)) for k, v in sorted(labels.items(), key=lambda kv: -len(kv[1]))[:4])
        L.append("| %s | %d | %d | %d | %d | %s |" % (f, a, b, c, d, top))
    L += ["", "Files with more than one label: %d; with more than one named TU: %d." %
          (len(mixed), sum(1 for x in mixed if x[4] > 1)), "",
          "## Original TUs spread over the most match/ files (top 40)", "",
          "| original TU | match files |", "|---|---:|"]
    for l, fs in sorted(spread.items(), key=lambda kv: (-len(kv[1]), kv[0]))[:40]:
        L.append("| %s | %d |" % (l, len(fs)))
    L += ["", "## Placement leads: scalar deleting destructors versus their destructors", "",
          "Bracket = the nearest witnessed TUs either side; two functions in different brackets cannot be in the same object.", ""]
    for r in lead_rows(result, evidence):
        L.append("- %s: sdd 0x%X [%s] ; dtor %s [%s] ; %s" % (
            r["class"], r["sdd"], _where(r["sdd_rec"]),
            ("0x%X" % r["dtor"]) if r["dtor"] else "none found", _where(r["dtor_rec"]),
            "SAME bracket" if r["same_bracket"] else "DIFFERENT brackets %s vs %s" % (r["sdd_bracket"], r["dtor_bracket"])))
    return "\n".join(L) + "\n"


# --------------------------------------------------------------------------- cli
def _load(p):
    return json.loads(Path(p).read_text())


def _names():
    p = DATA / "symbol_bindings.json"
    return {int(v, 16): k for k, v in _load(p).items()} if p.exists() else {}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    e = sub.add_parser("extract", help="read the pinned PE into scripts/data/tu_evidence.json")
    e.add_argument("--binary", default=os.environ.get("GAMEMD_BINARY"))
    e.add_argument("--out", default=str(DATA / "tu_evidence.json"))
    p = sub.add_parser("partition", help="write original_tu_map.json and the report (no binary needed)")
    p.add_argument("--evidence", default=str(DATA / "tu_evidence.json"))
    p.add_argument("--out", default=str(DATA / "original_tu_map.json"))
    p.add_argument("--report", default=None, help="markdown report path (also printed)")
    a = ap.parse_args(argv)
    if a.cmd == "extract":
        if not a.binary:
            ap.error("--binary or GAMEMD_BINARY required")
        ev = extract_evidence(a.binary, _load(DATA / "rtti_classes.json"))
        Path(a.out).write_text(json.dumps(ev, indent=1) + "\n")
        print("wrote", a.out)
        return 0
    ev = _load(a.evidence)
    res = partition(ev, _load(DATA / "function_extents.json"), _load(DATA / "rtti_classes.json"), _names())
    with open(a.out, "w") as fh:
        head = {k: v for k, v in res.items() if k != "functions"}
        fh.write(json.dumps(head, indent=1)[:-2] + ',\n "functions": [\n')
        fh.write(",\n".join("  " + json.dumps(r, separators=(",", ":")) for r in res["functions"]))
        fh.write("\n ]\n}\n")
    rep = render_report(res, ev, _load(DATA / "match_manifest.json"))
    if a.report:
        Path(a.report).parent.mkdir(parents=True, exist_ok=True)
        Path(a.report).write_text(rep)
    print(rep)
    return 0


if __name__ == "__main__":
    sys.exit(main())
