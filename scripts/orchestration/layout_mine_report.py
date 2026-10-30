#!/usr/bin/env python3
# SPDX-Provenance: own-binary-via-Ghidra
#
# Stage 2 of layout_mine: turn the raw receiver-tracked mine into the two
# published lead files, and score the result against the 31 already-proven
# layout headers in match/_layout/.
#
# Usage: layout_mine_report.py <raw_mine.json> <rtti_classes.json>
#                              <match/_layout> <scripts/data> [--write]

import json
import os
import re
import sys
from collections import defaultdict, Counter

SHA = "1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c"


# ------------------------------------------------- the proven-header oracle

MEMBER_RE = re.compile(r"^\s{4}([A-Za-z_][\w:<>* ]*?)\s+(\*?\w+)\s*(\[[^\]]*\])?\s*;"
                       r".*?//\s*\+0x([0-9A-Fa-f]+)")
STRUCT_RE = re.compile(r"^struct\s+(\w+)\s*(?::\s*(?:public\s+)?(\w+))?\s*$")
SIZE_RE = re.compile(r"GG_STATIC_ASSERT\(\s*sizeof\((\w+)\)\s*==\s*(0x[0-9A-Fa-f]+|\d+)\s*\)")
OFF_RE = re.compile(r"GG_STATIC_ASSERT\(\s*offsetof\((\w+)\s*,\s*[\w\[\]]+\)\s*==\s*"
                    r"(0x[0-9A-Fa-f]+|\d+)\s*\)")


def parse_headers(d):
    sizes, bases, members, asserted = {}, {}, defaultdict(list), defaultdict(set)
    for fn in sorted(os.listdir(d)):
        if not fn.lower().endswith(".h"):
            continue
        cur = None
        for line in open(os.path.join(d, fn)):
            m = SIZE_RE.search(line)
            if m:
                sizes[m.group(1)] = int(m.group(2), 0)
            m = OFF_RE.search(line)
            if m:
                asserted[m.group(1)].add(int(m.group(2), 0))
            s = STRUCT_RE.match(line.rstrip())
            if s:
                cur = s.group(1)
                if s.group(2):
                    bases[cur] = s.group(2)
                continue
            if line.startswith("};"):
                cur = None
                continue
            if cur:
                mm = MEMBER_RE.match(line.rstrip())
                if mm:
                    name = mm.group(2).lstrip("*")
                    pad = (name.startswith("align_") or name.startswith("padding_")
                           or "PROTECTED_PROPERTY" in line)
                    members[cur].append((int(mm.group(4), 16), name, pad))
    return sizes, bases, members, asserted


def flatten(cls, sizes, bases, members, seen=None):
    """Merged member list for cls including its base chain, sorted by offset."""
    seen = seen or set()
    if cls in seen:
        return []
    seen.add(cls)
    out = []
    b = bases.get(cls)
    if b:
        out += flatten(b, sizes, bases, members, seen)
    out += members.get(cls, [])
    return sorted(set(out))


def spans(flat, size):
    """(start, end, name, is_pad) for each member, end inferred from the next."""
    out = []
    for i, (off, name, pad) in enumerate(flat):
        end = flat[i + 1][0] if i + 1 < len(flat) else (size or off + 4)
        out.append((off, max(end, off + 1), name, pad))
    return out


# ------------------------------------------------------------------- main

def main():
    raw_p, rtti_p, layout_d, data_d = sys.argv[1:5]
    write = "--write" in sys.argv
    raw = json.load(open(raw_p))
    rtti = json.load(open(rtti_p))

    vt2cls = {}
    depth = {}
    for mangled, c in rtti["classes"].items():
        name = c.get("demangled_name") or mangled
        depth[name] = len(c.get("base_chain") or [name])
        for loc in c["locators"]:
            vt = loc.get("vtable_va")
            if vt:
                vt2cls.setdefault(int(vt, 16), []).append((name, loc["base_offset"]))

    results = raw["results"]

    # ---- constructor vs destructor, and class identity.
    #
    # Both a ctor and a dtor store a vptr at offset 0, so "it stores a vtable"
    # alone does not separate them -- and getting it wrong mis-binds the class.
    # A ctor runs base-first, so its offset-0 vptr stores go from the most-base
    # class to the most-derived one as the address increases; a dtor runs
    # derived-first and the sequence descends.  RTTI's base_chain gives the
    # depth, so the direction of that sequence IS the discriminator, read off
    # the binary.  With only one vptr class the fallback is returns_this: MSVC
    # constructors return `this` in EAX.
    ctor_class, role = {}, {}
    for a, r in results.items():
        seq = []
        for iaddr, disp, vt in r["vptrs"]:
            if disp != 0:
                continue
            names = vt2cls.get(int(vt, 16), [])
            prim = [n for n, bo in names if bo == 0] or [n for n, _ in names]
            if prim:
                seq.append(prim[0])
        if not seq:
            role[a] = "ctor" if r.get("alloc_bound") else "unknown"
            continue
        ds = [depth.get(n, 1) for n in seq]
        if len(set(seq)) >= 2 and ds[-1] < ds[0]:
            role[a] = "dtor"
        elif len(set(seq)) >= 2:
            role[a] = "ctor"
        else:
            role[a] = "ctor" if (r.get("returns_this") or r.get("alloc_bound")) else "dtor"
        ctor_class[a] = seq[ds.index(max(ds))]     # the most-derived class seen

    # a ctor called from inside another ctor is a BASE ctor: its allocation-site
    # size may belong to a derived object whose own ctor the compiler inlined.
    base_ctors = set()
    for a, r in results.items():
        if role.get(a) != "ctor":
            continue
        for c in r.get("callees", []):
            if c in results and c != a:
                base_ctors.add(c)

    ctors_only = set(a for a in results if role.get(a) == "ctor")
    n_dtor = sum(1 for a in results if role.get(a) == "dtor")

    # ---- sizes from the allocation sites
    by_ctor = defaultdict(list)
    for s in raw["sites"]:
        if s["kind"] == "ok":
            by_ctor["0x%X" % s["ctor"]].append(s)

    size_records = []
    for ctor, ss in sorted(by_ctor.items(), key=lambda kv: int(kv[0], 16)):
        cnt = Counter(s["size"] for s in ss)
        size, n = cnt.most_common(1)[0]
        rec = {
            "constructor": ctor,
            "class": ctor_class.get(ctor),
            "sizeof": size,
            "sizeof_hex": "0x%X" % size,
            "allocation_sites": len(ss),
            "sites_agreeing": n,
            "unanimous": len(cnt) == 1,
            "evidence": [
                {"push_at": "0x%X" % s["push_at"], "new_at": "0x%X" % s["new_at"],
                 "ctor_call_at": "0x%X" % s["ctor_call_at"], "size": s["size"]}
                for s in ss[:4]],
            "ghidra_name": results.get(ctor, {}).get("ghidra_name"),
        }
        if len(cnt) > 1:
            rec["conflicting_sizes"] = {str(k): v for k, v in sorted(cnt.items())}
        rec["role"] = role.get(ctor)
        rec["source"] = "direct-constructor-call"
        if ctor in base_ctors:
            rec["is_base_constructor"] = True
            rec["size_confidence"] = "low"
            rec["size_caveat"] = ("this constructor is also called from another "
                                  "constructor, so it is a base-class ctor; an "
                                  "allocation site that calls it directly is "
                                  "allocating a DERIVED object whose own ctor was "
                                  "inlined, and the size belongs to that derived "
                                  "class, not to this one")
        else:
            rec["size_confidence"] = "high" if rec["unanimous"] else "medium"
        if ctor in results:
            offs = [x[1] for x in results[ctor]["stores"]]
            if offs:
                rec["max_mined_offset"] = "0x%X" % max(offs)
                rec["closes"] = max(offs) < size
        size_records.append(rec)

    # ---- sizes recovered from sites whose constructor the compiler INLINED:
    # the vptr store through the freshly-returned pointer names the class.
    by_inl = defaultdict(list)
    for st in raw["sites"]:
        if st["kind"] != "inlined-ctor":
            continue
        names = vt2cls.get(int(st["vtable"], 16) if isinstance(st["vtable"], str)
                           else st["vtable"], [])
        prim = [n for n, bo in names if bo == 0] or [n for n, _ in names]
        if prim:
            by_inl[prim[0]].append(st)
    sized_classes = set(r["class"] for r in size_records if r["class"])
    for cls, ss in sorted(by_inl.items()):
        cnt = Counter(s["size"] for s in ss)
        size, n = cnt.most_common(1)[0]
        rec = {"constructor": None, "class": cls, "sizeof": size,
               "sizeof_hex": "0x%X" % size, "allocation_sites": len(ss),
               "sites_agreeing": n, "unanimous": len(cnt) == 1,
               "source": "inlined-constructor",
               "size_confidence": "high" if len(cnt) == 1 else "medium",
               "evidence": [{"push_at": "0x%X" % s["push_at"],
                             "new_at": "0x%X" % s["new_at"],
                             "vptr_store_at": "0x%X" % s["vptr_at"],
                             "vtable": "0x%X" % s["vtable"], "size": s["size"]}
                            for s in ss[:4]]}
        if len(cnt) > 1:
            rec["conflicting_sizes"] = {str(k): v for k, v in sorted(cnt.items())}
        if cls in sized_classes:
            rec["note"] = "class also sized from a direct constructor call"
        size_records.append(rec)

    # ---- field offsets per constructor
    field_records = []
    for a in sorted(results, key=lambda x: int(x, 16)):
        if a not in ctors_only:
            continue                      # constructors only -- see the_trap
        r = results[a]
        st = r["stores"]
        if not st:
            continue
        agg = {}
        for iaddr, disp, w, mnem, kind, src in st:
            e = agg.setdefault(disp, {"offset": disp, "offset_hex": "0x%X" % disp,
                                      "width": 0, "kinds": set(), "proofs": []})
            e["width"] = max(e["width"], w)
            e["kinds"].add(kind)
            if len(e["proofs"]) < 4:
                e["proofs"].append({"at": iaddr, "insn": mnem, "kind": kind,
                                    "width": w, "src": src})
        fields = []
        for disp in sorted(agg):
            e = agg[disp]
            e["kinds"] = sorted(e["kinds"])
            fields.append(e)
        field_records.append({
            "constructor": a,
            "class": ctor_class.get(a),
            "ghidra_name": r["ghidra_name"],
            "function_end": r["limit"],
            "vptr_stores": [{"at": v[0], "offset": v[1], "offset_hex": "0x%X" % v[1],
                             "vtable": v[2],
                             "class": (vt2cls.get(int(v[2], 16)) or [[None]])[0][0]}
                            for v in r["vptrs"]],
            "returns_this": r.get("returns_this"),
            "allocation_bound": r.get("alloc_bound"),
            "is_base_constructor": a in base_ctors,
            "sizeof_from_allocation": next(
                (x["sizeof"] for x in size_records if x["constructor"] == a), None),
            "fields": fields,
        })

    # ---- validation against the 31 proven headers
    sizes, bases, members, asserted = parse_headers(layout_d)
    size_by_class = {}
    for r in size_records:
        if r["class"] and (r["class"] not in size_by_class
                           or r.get("size_confidence") != "low"):
            size_by_class[r["class"]] = r
    mined_by_class = defaultdict(list)
    for r in field_records:
        if r["class"]:
            mined_by_class[r["class"]].append(r)

    val = {"size_checks": [], "offset_checks": [], "totals": {}}
    ok_s = bad_s = 0
    for cls, want in sorted(sizes.items()):
        got = size_by_class.get(cls)
        if not got or got.get("size_confidence") == "low":
            continue
        agree = got["sizeof"] == want
        ok_s += agree
        bad_s += (not agree)
        val["size_checks"].append({"class": cls, "header": "0x%X" % want,
                                   "mined": got["sizeof_hex"], "agree": agree,
                                   "sites": got["allocation_sites"]})

    tot_exact = tot_interior = tot_pad = tot_over = 0
    for cls in sorted(mined_by_class):
        if cls not in members and cls not in sizes:
            continue
        flat = flatten(cls, sizes, bases, members)
        if not flat:
            continue
        size = sizes.get(cls)
        sp = spans(flat, size)
        starts = set(o for o, _, _ in flat)
        offs = set()
        for r in mined_by_class[cls]:
            for f in r["fields"]:
                offs.add(f["offset"])
        exact = interior = pad = over = 0
        bad = []
        for o in sorted(offs):
            if size is not None and o >= size:
                over += 1
                bad.append({"offset": "0x%X" % o, "why": "beyond sizeof 0x%X" % size})
                continue
            if o in starts:
                exact += 1
                continue
            hit = [s for s in sp if s[0] <= o < s[1]]
            if hit and hit[0][3]:
                pad += 1
                bad.append({"offset": "0x%X" % o,
                            "why": "inside declared padding %s" % hit[0][2]})
            elif hit:
                interior += 1
            else:
                over += 1
                bad.append({"offset": "0x%X" % o, "why": "no declared member covers it"})
        tot_exact += exact
        tot_interior += interior
        tot_pad += pad
        tot_over += over
        val["offset_checks"].append({
            "class": cls, "header_members": len(flat), "mined_offsets": len(offs),
            "exact": exact, "interior": interior,
            "contradicts_padding": pad, "uncovered": over,
            "agreement_pct": round(100.0 * (exact + interior) / max(1, len(offs)), 2),
            "contradictions": bad[:12]})

    n = tot_exact + tot_interior + tot_pad + tot_over
    val["totals"] = {
        "classes_size_checked": ok_s + bad_s, "sizes_agree": ok_s,
        "sizes_disagree": bad_s,
        "offsets_checked": n, "exact_member_start": tot_exact,
        "interior_to_a_declared_member": tot_interior,
        "contradicts_declared_padding": tot_pad, "uncovered_by_any_member": tot_over,
        "agreement_pct": round(100.0 * (tot_exact + tot_interior) / max(1, n), 2),
    }

    # ---- closure: a class's mined layout must fit inside its mined sizeof
    mx = defaultdict(int)
    for r in field_records:
        if r["class"]:
            for f in r["fields"]:
                mx[r["class"]] = max(mx[r["class"]],
                                     f["offset"] + max(f["width"], 1))
    closes = overrun = 0
    overruns = []
    seen_cls = set()
    for r in size_records:
        c = r["class"]
        if not c or c in seen_cls or r.get("size_confidence") == "low":
            continue
        seen_cls.add(c)
        if c not in mx:
            continue
        if mx[c] <= r["sizeof"]:
            closes += 1
        else:
            overrun += 1
            overruns.append({"class": c, "sizeof": r["sizeof_hex"],
                             "past_the_end": "0x%X" % mx[c]})
    val["totals"]["classes_whose_mined_layout_closes_on_its_mined_sizeof"] = closes
    val["totals"]["classes_overrunning_their_mined_sizeof"] = overrun
    val["closure_overruns"] = overruns

    counts = {
        "operator_new_sites": len(raw["sites"]),
        "allocation_sites_bound_to_a_constructor":
            sum(1 for s in raw["sites"] if s["kind"] == "ok"),
        "constructors_with_a_size": len(size_records),
        "constructors_with_a_size_and_an_RTTI_class":
            sum(1 for r in size_records if r["class"]),
        "distinct_classes_sized": len(set(r["class"] for r in size_records if r["class"])),
        "sizes_from_an_inlined_constructor": len(by_inl),
        "operator_new_sites_with_no_constructor_and_no_vptr":
            sum(1 for s in raw["sites"] if s["kind"] == "no-ctor"),
        "constructors_mined": len(field_records),
        "constructors_mined_with_an_RTTI_class": len(
            [r for r in field_records if r["class"]]),
        "distinct_classes_with_offsets": len(mined_by_class),
        "field_offsets_total": sum(len(r["fields"]) for r in field_records),
        "constructors_classified_as_destructors_and_excluded": n_dtor,
        "distinct_class_offset_pairs": len(set(
            (r["class"], f["offset"]) for r in field_records if r["class"]
            for f in r["fields"])),
    }
    print(json.dumps({"counts": counts, "validation": val["totals"]}, indent=1))
    for c in val["offset_checks"]:
        if c["contradicts_padding"] or c["uncovered"]:
            print(json.dumps(c, indent=1))
    for c in val["size_checks"]:
        if not c["agree"]:
            print("SIZE MISMATCH", json.dumps(c))

    if write:
        emit(data_d, size_records, field_records, val, counts)


def emit(data_d, size_records, field_records, val, counts):
    common = {
        "target": "GAMEMD gamemd.exe v1.001",
        "sha256": SHA,
        "provenance": "own-binary-via-Ghidra (function entry points + RTTI vtable map) "
                      "+ objdump -d -M intel over .text of the same sha256-pinned file",
        "generated_by": "scripts/orchestration/layout_mine.py + layout_mine_report.py",
        "status": "LEADS, NOT FACTS. Every row carries the instruction address that "
                  "produced it. Per project rule a number enters a layout header or "
                  "the manifest only after that instruction has been read back and "
                  "cited in the header itself. Nothing here is a confirmed fact.",
    }
    hdr_sz = dict(common)
    hdr_sz.update({
        "schema": "gagarin/class_sizes/1",
        "what_this_is":
            "`PUSH <n>; CALL operator new (0x7C8E17)` immediately before a "
            "constructor call gives the object's exact size. Each row binds one "
            "constructor to the size pushed at its allocation sites, and to the "
            "RTTI class name of the vtable that constructor stores at offset 0.",
        "method": [
            "every direct CALL to 0x7C8E17 in .text is an allocation site;",
            "the single argument is the last PUSH before that call (immediate only; "
            "a PUSH of a register is a computed size and the site is dropped);",
            "the returned pointer is followed forward through register and frame-slot "
            "moves until a CALL is reached with that pointer in ECX -- that callee is "
            "the constructor;",
            "sites disagreeing on the size are reported in conflicting_sizes and the "
            "majority value is taken (unanimous=false).",
        ],
        "field_notes": {
            "closes": "false means the constructor writes at or beyond the allocated "
                      "size -- either the size binding or the receiver tracking is "
                      "wrong for that row, so read it by hand.",
            "unanimous": "every allocation site pushed the same size.",
        },
        "counts": counts,
        "validation_against_match_layout": val["totals"],
    })
    json.dump({"header": hdr_sz,
               "size_checks_vs_proven_headers": val["size_checks"],
               "classes": size_records},
              open(os.path.join(data_d, "class_sizes.json"), "w"), indent=1)

    hdr_f = dict(common)
    hdr_f.update({
        "schema": "gagarin/ctor_field_offsets/1",
        "what_this_is":
            "Constructor-mined member offsets: every [receiver+disp] store inside a "
            "constructor body, with the width of the store and the instruction "
            "address that proves it.",
        "the_trap_and_the_defence": [
            "UnitClass::TryToDeploy writes [EBX+0x6CA] where EBX is the BuildingClass "
            "being deployed, not the unit -- the same body reads [EBX+0x520] as a type "
            "pointer. A sweep over a class's methods invents members that do not exist.",
            "Defence 1: constructors only. A candidate is a function that stores a "
            "known RTTI vtable through its receiver, or that is called on the pointer "
            "returned by operator new. Arbitrary methods are never mined.",
            "Defence 2: a forward dataflow from the entry tracks which registers and "
            "ebp-relative frame slots still provably hold the entry ECX. MOV ESI,ECX "
            "propagates it; a reload of ESI from anywhere else, a partial-register "
            "write, a POP, or a CALL (for the volatile EAX/ECX/EDX) drops it. Only "
            "stores through a location still in that set are recorded. Paths are "
            "merged by INTERSECTION at join points, so an offset survives only if the "
            "register holds the receiver on every path that reaches it.",
            "Known-rejected examples this reproduces: BulletClass +0xE4 (the only "
            "[reg+0xE4] in BulletClass code is off a virtual-call result, and the ctor "
            "never writes it) and CellClass +0x14C (past sizeof 0x148) are both absent "
            "from this file.",
        ],
        "field_notes": {
            "kinds": "store = a plain move into the member; rmw = a read-modify-write "
                     "(and/or/xor/add/...), which usually means a bitfield; vptr = a "
                     "32-bit immediate in .rdata/.data range, i.e. a vtable pointer; "
                     "lea = the receiver-relative address was TAKEN, not written -- it "
                     "proves a sub-object or array starts there (a base ctor call, or "
                     "the EDI of a REP STOS run).",
            "width": "bytes moved by the widest store seen at that offset; 0 for a "
                     "lea-only offset, where the width is unknown.",
            "proofs": "up to four instruction addresses, each of which can be read "
                      "back with `ghidra disasm` to confirm the row.",
            "class": "null when the constructor stores no vtable at offset 0 (a "
                     "non-polymorphic class, or a sub-object constructor); the offsets "
                     "are still receiver-tracked and still good leads.",
        },
        "counts": counts,
        "validation_against_match_layout": val["totals"],
    })
    json.dump({"header": hdr_f,
               "offset_checks_vs_proven_headers": val["offset_checks"],
               "constructors": field_records},
              open(os.path.join(data_d, "ctor_field_offsets.json"), "w"), indent=1)
    print("written to", data_d)


if __name__ == "__main__":
    main()
