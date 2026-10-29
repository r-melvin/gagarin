#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling (measurement only); reads the pinned PE ($GAMEMD_BINARY) at run time.
"""Census of the .rdata/.data/.bss bytes that the M3 hybrid link still takes from retail fill, and why.

Inputs: a link directory written by data_census_link.py (stubs/data_rejected.json with per-slot detail,
stubs/data_placed.json, stubs/plan.json) and the scripts/data tables. Output: JSON (and a TSV worklist).

Usage: GAMEMD_BINARY=... data_census.py --link build-vc6/census-link --json OUT.json --tsv OUT.tsv
"""
import argparse
import bisect
import collections
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hybrid  # noqa: E402
import pindata  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--link", type=Path, required=True)
    ap.add_argument("--json", type=Path, required=True)
    ap.add_argument("--tsv", type=Path)
    args = ap.parse_args()
    R = hybrid.Retail(pindata.retail_path())
    rd0, rdn, _, _ = R.by_name[".rdata"]
    d0, dn, _, draw = R.by_name[".data"]
    t0, tn, _, _ = R.by_name[".text"]
    RD_END, D_END, D_INIT_END, T_END = rd0 + rdn, d0 + dn, d0 + draw, t0 + tn
    word = lambda va: struct.unpack("<I", R.fill(va, 4))[0]
    in_text = lambda v: t0 <= v < T_END
    link = args.link
    placed = json.loads((link / "stubs/data_placed.json").read_text())
    rejected = json.loads((link / "stubs/data_rejected.json").read_text())
    plan = json.loads((link / "stubs/plan.json").read_text())
    bindings = json.loads((ROOT / "scripts/data/symbol_bindings.json").read_text())
    rtti = json.loads((ROOT / "scripts/data/rtti_classes.json").read_text())["classes"]
    matched = {int(p["addr"], 16): p for p in plan["placed"] if p["kind"] == "matched"}
    mspans = sorted((int(p["addr"], 16), int(p["addr"], 16) + int(p["len"], 16)) for p in plan["placed"] if p["kind"] == "matched")
    mstarts = [a for a, _ in mspans]
    is_matched_code = lambda va: (lambda i: i >= 0 and mspans[i][0] <= va < mspans[i][1])(bisect.bisect_right(mstarts, va) - 1)
    ext = json.loads((ROOT / "scripts/data/function_extents.json").read_text())["entries"]
    fn_starts = sorted(int(e[0], 16) for e in ext)
    fn_len = {int(e[0], 16): int(e[1], 16) for e in ext}
    # --- coverage by project pieces
    N = D_END - rd0
    owner = bytearray(N)   # 1 = project
    for p in placed:
        for k in range(p["va"], p["va"] + p["size"]):
            owner[k - rd0] = 1
    def in_region(va):
        return rd0 <= va < RD_END or d0 <= va < D_END
    # --- xrefs from .text (any dword that is a data VA; classed by the containing function)
    text = R.fill(t0, tn)
    xref = collections.defaultdict(lambda: {"matched": 0, "retail": 0, "ops": collections.Counter(), "sites": []})
    fsz = {0xD8: 4, 0xD9: 4, 0xDC: 8, 0xDD: 8}
    for i in range(0, len(text) - 3):
        v = struct.unpack_from("<I", text, i)[0]
        if not in_region(v):
            continue
        va = t0 + i
        side = "matched" if is_matched_code(va) else "retail"
        x = xref[v]
        x[side] += 1
        if side == "matched":
            x["sites"].append(va)
        if i >= 2 and text[i - 2] in fsz and (text[i - 1] & 0xC7) == 0x05:
            x["ops"]["f%d" % fsz[text[i - 2]]] += 1
        elif i >= 4 and text[i - 4] in (0xF3, 0xF2) and text[i - 3] == 0x0F and (text[i - 1] & 0xC7) == 0x05:
            x["ops"]["f%d" % (4 if text[i - 4] == 0xF3 else 8)] += 1
        else:
            x["ops"]["other"] += 1
    # --- classify every byte in the data sections
    LAB = {}
    cls = ["" for _ in range(N)]
    def mark(va, size, label, force=False):
        for k in range(va, min(va + size, D_END)):
            if k >= rd0 and (not cls[k - rd0] or force):
                cls[k - rd0] = label
    # imports
    iat, descr, term, ilt, _ = R.import_layout()
    for (va, size), lab in ((iat, "import"), (descr, "import"), (term, "import"), (ilt, "import")):
        mark(va, size, lab)
    at = descr[0]
    while True:
        orig, _, _, name_rva, first = struct.unpack("<IIIII", R.fill(at, 20))
        if not name_rva:
            break
        s = R.fill(0x400000 + name_rva, 64).split(b"\0")[0]
        mark(0x400000 + name_rva, len(s) + 1, "import")
        n = 0
        while True:
            e = word(0x400000 + orig + 4 * n)
            if not e:
                break
            if not e & 0x80000000:
                hn = R.fill(0x400000 + e, 80)
                ln = 2 + hn[2:].split(b"\0")[0].__len__() + 1
                mark(0x400000 + e, ln + (ln & 1), "import")
            n += 1
        at += 20
    # RTTI
    vt_starts = {}
    for c in rtti.values():
        td = int(c["type_descriptor_va"], 16)
        nm = R.fill(td + 8, 160).split(b"\0")[0]
        mark(td, 8 + len(nm) + 1 + 3 & ~3, "rtti")
        for loc in c["locators"]:
            lv = int(loc["locator_va"], 16)
            mark(lv, 24, "rtti")
            chd = int(loc["class_hierarchy_va"], 16)
            mark(chd, 16, "rtti")
            nb, bca = word(chd + 8), word(chd + 12)
            mark(bca, 4 * nb, "rtti")
            for j in range(nb):
                bcd = word(bca + 4 * j)
                mark(bcd, 28, "rtti")
            if loc["vtable_va"]:
                v = int(loc["vtable_va"], 16)
                vt_starts[v] = (c["demangled_name"], loc["base_offset"])
    for k, v in bindings.items():
        if k.startswith("??_7"):
            a = int(v, 16)
            vt_starts.setdefault(a, (k, None))
    vt_sorted = sorted(vt_starts)
    vtables = []
    for i, a in enumerate(vt_sorted):
        if not rd0 <= a < RD_END:
            continue
        n, lim = 0, (vt_sorted[i + 1] if i + 1 < len(vt_sorted) else RD_END)
        while a + 4 * n < lim and in_text(word(a + 4 * n)):
            n += 1
        if n == 0:
            continue
        vtables.append({"va": a, "slots": n, "bytes": 4 * n, "class": vt_starts[a][0], "base_offset": vt_starts[a][1]})
        mark(a, 4 * n, "vtable")
        if word(a - 4) and cls[a - 4 - rd0] != "rtti":
            mark(a - 4, 4, "vtable_colptr")
    # pointer tables into .text that are not vtables (jump tables, callback arrays)
    k = rd0
    while k < RD_END - 3:
        if not cls[k - rd0] and in_text(word(k)):
            j = k
            while j < RD_END - 3 and not cls[j - rd0] and in_text(word(j)):
                j += 4
            mark(k, j - k, "codeptr_table")
            k = j
        else:
            k += 4
    # strings (ASCII, NUL terminated, >= 4 chars) in rdata and initialised data
    str_list, flt_list = [], []
    def scan_strings(lo, hi):
        buf = R.fill(lo, hi - lo)
        for m in re.finditer(rb"[\x20-\x7e\t\r\n]{3,}\x00", buf):
            va = lo + m.start()
            if all(not cls[k - rd0] for k in range(va, va + m.end() - m.start())):
                mark(va, m.end() - m.start(), "string")
                str_list.append((va, m.end() - m.start()))
    scan_strings(rd0, RD_END)
    scan_strings(d0, D_INIT_END)
    # floats: xref'd with an FP operand
    for v, x in xref.items():
        if x["ops"]["f4"] + x["ops"]["f8"] and v < D_INIT_END and not cls[v - rd0]:
            sz = 8 if x["ops"]["f8"] > x["ops"]["f4"] else 4
            mark(v, sz, "float")
            flt_list.append((v, sz))
    # --- item segmentation of what is left: rdata tables, data, bss
    starts = set(xref)
    for k_, v_ in bindings.items():
        if k_.startswith(("?DAT_", "?STR_")) or "DAT_" in k_:
            a = int(v_, 16)
            if in_region(a):
                starts.add(a)
    for p in placed:
        starts.add(p["va"])
        starts.add(p["va"] + p["size"])
    starts = sorted(s for s in starts if in_region(s))
    # --- sizes by origin
    def region_of(va):
        if va < RD_END:
            return ".rdata"
        return ".data" if va < D_INIT_END else ".bss"
    byreg = collections.defaultdict(lambda: collections.Counter())
    for k in range(N):
        va = rd0 + k
        if va >= RD_END and va < d0:
            continue
        reg = region_of(va)
        byreg[reg]["total"] += 1
        if owner[k]:
            byreg[reg]["project"] += 1
        else:
            label = cls[k] or ("zero_or_unclassified")
            byreg[reg]["fill:" + label] += 1
    out = {"regions": {r: dict(c) for r, c in byreg.items()}}
    # --- fill items: contiguous unowned runs split at item starts
    items = []
    gaps = []
    k = 0
    while k < N:
        if owner[k] or (RD_END <= rd0 + k < d0):
            k += 1
            continue
        j = k
        while j < N and not owner[j] and not (RD_END <= rd0 + j < d0):
            j += 1
        gaps.append((rd0 + k, rd0 + j))
        k = j
    for lo, hi in gaps:
        cut = [lo] + [s for s in starts if lo < s < hi] + [hi]
        for a, b in zip(cut, cut[1:]):
            labs = collections.Counter(cls[v - rd0] or "unclassified" for v in range(a, b))
            lab = labs.most_common(1)[0][0]
            x = xref.get(a)
            items.append({"va": a, "size": b - a, "region": region_of(a), "label": lab, "labels": dict(labs) if len(labs) > 1 else None,
                          "xm": x["matched"] if x else 0, "xr": x["retail"] if x else 0,
                          "ops": dict(x["ops"]) if x else {}})
    out["items_n"] = len(items)
    several = {int(a, 16): n for a, n in ((x["addr"], x["symbol"]) for x in plan["matched_symbol_at_several_addresses"])}
    diff = json.loads((link / "data_linked_diff.json").read_text()) if (link / "data_linked_diff.json").is_file() else {}
    # ---------------- 1. vtables
    placed_vt = {p["va"] for p in placed if p["kind"] == "vtable"}
    placed_names = {n for p in placed for n in p["names"]}
    vt_by_va = {v["va"]: v for v in vtables}
    rej_va = collections.defaultdict(list)
    rej_noaddr = {}
    for r in rejected:
        if r["kind"] != "vtable":
            continue
        if r["va"] is None:
            rej_noaddr.setdefault(r["name"], []).append(r)
        else:
            rej_va[r["va"]].append(r)
    name_targets = collections.defaultdict(set)   # unknown-name -> retail values seen
    for va, recs in rej_va.items():
        for r in recs:
            for off, t, why, known, want in r.get("slots", ()):
                if why == "unknown":
                    name_targets[t].add(want)
    def slot_fix(tname, why, known, Y):
        sym = matched.get(Y, {}).get("symbol")
        if why == "unknown":
            kind = "bind" if len(name_targets[tname]) == 1 else "bind_ambiguous"
            return {"fix": kind, "Y": hex(Y), "Y_matched_as": sym, "Y_len": fn_len.get(Y)}
        if Y in several and several[Y] == tname.split("@pin")[0]:
            return {"fix": "tool_alias", "Y": hex(Y), "Y_matched_as": sym, "Y_len": fn_len.get(Y)}
        return {"fix": "override_matched" if sym else "recover_function", "Y": hex(Y), "Y_matched_as": sym,
                "Y_len": fn_len.get(Y)}
    vt_rows = []
    for va, recs in sorted(rej_va.items()):
        if va in placed_vt:
            continue
        v = vt_by_va.get(va)
        size = recs[0]["size"]
        slots = {}
        for r in recs:
            for off, t, why, known, want in r.get("slots", ()):
                slots[(off // 4, t)] = (why, known, want)
        fixes = []
        for (idx, t), (why, known, want) in sorted(slots.items()):
            f = slot_fix(t, why, known, want)
            f.update({"slot": idx, "name": t})
            fixes.append(f)
        reason = recs[0]["why"]
        for key, dl in diff.items():
            kva, ksz = key.split("+")
            if int(kva, 16) == va:
                for idx_off, linked, retail_v in dl:
                    f = {"slot": idx_off // 4, "name": several.get(retail_v, "?"), "Y": hex(retail_v),
                         "Y_matched_as": matched.get(retail_v, {}).get("symbol"), "Y_len": fn_len.get(retail_v),
                         "fix": "tool_alias" if retail_v in several else "override_matched" if retail_v in matched else "recover_function"}
                    fixes.append(f)
        vt_rows.append({"va": hex(va), "name": recs[0]["name"], "class": v["class"] if v else None, "bytes": size,
                        "slots": size // 4, "status": "rejected", "reason": reason, "objects": sorted({r["object"] for r in recs}),
                        "bad_slots": len(fixes), "fixes": fixes})
    # vtables with no retail address (no binding): try to find the retail vtable by known slot addresses
    retail_by_slots = collections.defaultdict(list)
    for v in vtables:
        retail_by_slots[v["slots"]].append(v)
    for name, recs in sorted(rej_noaddr.items()):
        if name in placed_names:
            continue
        r = recs[0]
        info = r.get("slotinfo", [])
        known = {off // 4: a for off, t, a in info if a}
        cands = []
        for v in retail_by_slots.get(r["size"] // 4, ()):
            if known and all(word(v["va"] + 4 * k) == a for k, a in known.items()):
                cands.append(v)
        vt_rows.append({"va": None, "name": name, "class": None, "bytes": r["size"], "slots": r["size"] // 4,
                        "status": "no_binding", "reason": "no retail address (no ??_7 binding)", "objects": sorted({x["object"] for x in recs}),
                        "known_slots": len(known), "candidates": [hex(c["va"]) for c in cands][:6], "bad_slots": 1,
                        "fixes": [{"fix": "bind_vtable" if len(cands) == 1 else "find_address", "Y": hex(cands[0]["va"]) if len(cands) == 1 else None}]})
    # retail vtables nobody defines
    covered = placed_vt | set(rej_va)
    nocand = []
    for v in vtables:
        if v["va"] in covered:
            continue
        tg = [word(v["va"] + 4 * k) for k in range(v["slots"])]
        um = [t for t in tg if t not in matched]
        nocand.append({"va": hex(v["va"]), "class": v["class"], "base_offset": v["base_offset"], "bytes": v["bytes"], "slots": v["slots"],
                       "unmatched_slots": len(um), "unmatched_code_bytes": sum(fn_len.get(t, 0) for t in set(um))})
    out["vtables"] = {"retail_total": len(vtables), "retail_total_bytes": sum(v["bytes"] for v in vtables),
                      "placed": len([v for v in vtables if v["va"] in placed_vt]), "rejected_rows": vt_rows, "no_candidate": nocand}
    # ---------------- 2. literals (per literal: refs from matched code, retail code, project-owned data, fill data)
    dref = collections.defaultdict(lambda: [0, 0])
    for k in range(0, D_INIT_END - rd0 - 3, 4):
        va = rd0 + k
        if RD_END <= va < d0:
            continue
        w = word(va)
        if in_region(w):
            dref[w][0 if owner[k] else 1] += 1
    xs = sorted(xref)
    def refs_in(va, size):
        m = r_ = dp = df = 0
        i0 = bisect.bisect_left(xs, va)
        while i0 < len(xs) and xs[i0] < va + size:
            m += xref[xs[i0]]["matched"]
            r_ += xref[xs[i0]]["retail"]
            i0 += 1
        ds = sorted(dref)
        return m, r_
    dsorted = sorted(dref)
    def drefs_in(va, size):
        a = bisect.bisect_left(dsorted, va)
        dp = df = 0
        while a < len(dsorted) and dsorted[a] < va + size:
            dp += dref[dsorted[a]][0]
            df += dref[dsorted[a]][1]
            a += 1
        return dp, df
    def lit_rows(lst):
        rows = []
        for va, size in lst:
            m, r_ = refs_in(va, size)
            dp, df = drefs_in(va, size)
            rows.append({"va": va, "size": size, "m": m, "r": r_, "dp": dp, "df": df})
        return rows
    lrows = {"string": lit_rows(str_list), "float": lit_rows(flt_list)}
    
    def lit_group(r):
        if r["m"]:
            return "matched_code_ref"
        if r["dp"]:
            return "project_data_ref"
        if r["r"]:
            return "retail_code_only"
        if r["df"]:
            return "retail_data_ref_only"
        return "unreferenced"
    out["literals"] = {}
    for kind, rows in lrows.items():
        c = collections.Counter()
        for r in rows:
            g = lit_group(r)
            c[g + ":n"] += 1
            c[g + ":bytes"] += r["size"]
        out["literals"][kind] = dict(c)
    rej_lit = collections.Counter()
    for r in rejected:
        if r["kind"] in ("string", "float"):
            rej_lit[(r["kind"], r["why"][:40])] += r["size"]
    out["literals_rejected_by_reason"] = {"%s|%s" % k: v for k, v in rej_lit.items()}
    out["_literal_matched_samples"] = sorted([r for k in lrows for r in lrows[k] if lit_group(r) == "matched_code_ref"], key=lambda i: -i["size"])[:60]
    # ---------------- 3. globals
    rej_at = {}
    for r in rejected:
        if r["va"] is not None and r["kind"] in ("global", "bss", "string", "float"):
            rej_at.setdefault(r["va"], []).append(r)
    glob = collections.defaultdict(collections.Counter)
    glob_items = []
    for it in items:
        if it["label"] in ("vtable", "vtable_colptr", "rtti", "import", "string", "float", "codeptr_table"):
            continue
        reg = it["region"]
        if it["va"] in rej_at:
            grp = "defined_not_adopted:" + rej_at[it["va"]][0]["why"][:40]
        elif it["xm"]:
            grp = "matched_ref_no_definition"
        elif it["xr"]:
            grp = "retail_only_ref"
        else:
            grp = "unreferenced_or_interior"
        glob[reg][grp + ":n"] += 1
        glob[reg][grp + ":bytes"] += it["size"]
        it["group"] = grp
        glob_items.append(it)
    out["globals"] = {k: dict(v) for k, v in glob.items()}
    out["_glob_items"] = sorted(glob_items, key=lambda i: -i["size"])[:400]
    out["_glob_m"] = [i for i in glob_items if i["xm"]]
    out["_lit_m"] = [dict(r, kind=k) for k, rows in lrows.items() for r in rows if r["m"]]
    out["_msites"] = {str(v): x["sites"] for v, x in xref.items() if x["sites"]}
    out["imports"] = {"import_tables_fill_bytes": sum(i["size"] for i in items if i["label"] == "import"),
                      "iat": iat, "ilt": ilt, "descriptors": descr, "thunks": len(plan["thunk_names"]),
                      "thunk_code_bytes": 6 * len(plan["thunk_names"])}
    out["initialiser_table"] = json.loads((link / "link_report.json").read_text())["data_report"]["initialiser_table"] if (link / "link_report.json").is_file() else None
    out["_rejected_all"] = [r for r in rejected if r["kind"] != "vtable"]
    out["_sizes_by_label"] = {}
    for it in items:
        out["_sizes_by_label"].setdefault(it["region"] + ":" + it["label"], 0)
        out["_sizes_by_label"][it["region"] + ":" + it["label"]] += it["size"]
    args.json.write_text(json.dumps(out, indent=0) + "\n")
    print("regions", json.dumps(out["regions"], indent=1))


if __name__ == "__main__":
    main()
