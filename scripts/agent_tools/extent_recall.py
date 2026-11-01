#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original. Reimplemented from the published idea of scoring function-start recall
# (precision/recall on start addresses, alternate entry points); no code taken from other projects.
# Reads the developer's own image; the proposal file holds addresses, lengths and evidence kinds only.
"""extent_recall: which code starts does scripts/data/function_extents.json not list, and why.

    GAMEMD_BINARY=gamemd.exe extent_recall.py [--census scripts/data/function_extents.json]
                                              [--out proposed_additions.json] [--examples N]

A static recompiler reports more functions for this binary than the census lists. This tool
rebuilds the candidate set the same way a recursive-descent lifter would and says what each
candidate is. Candidates are every direct call and jmp target (jumps that leave their function),
RTTI vtable slots, code pointers stored with `mov [m],imm` / `push imm` / `mov r,imm`, aligned
dwords in .rdata/.data that point into .text, and calls or vtable slots that land inside a listed
function (alternate entries). Roots are the census starts; the census is never edited.

Classes (each candidate not in the census gets exactly one):
  real_missed    code that starts a function and is not listed (confidence high/medium/low)
  alt_entry      lands inside a listed function at an instruction boundary reached by a call, a
                 vtable slot or a stored pointer (a second entry, a funclet, a catch block)
  shared_tail    inside a listed function, reached only by jumps (a shared epilogue or tail)
  data           not code: a jump or index table, a mid-instruction address, or bytes that do not
                 decode as VC6 code
  padding_thunk  CC/90 padding, or a one-instruction jump thunk

Evidence per entry lists the kinds of reference and up to 4 source sites. Confidence for real_missed
is high when a listed function calls it or an RTTI vtable holds it and it walks cleanly to a
terminator; medium when only a tail jump, stored code pointer or padding alignment backs it; low
otherwise. `proposed_additions` holds the real_missed entries with high or medium confidence, in the
census entry layout (addr, len, kind), for review only.
"""
import argparse
import bisect
import collections
import json
import os
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import x86scan as X  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
SHA256 = "1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c"
SCHEMA = "gagarin/extent_recall/1"
# Retail .text regions that are not engine code (mirrors scripts/vc6/extent_census.py REGIONS)
REGIONS = [(0x55BB90, 0x55C2B0, "lzo"), (0x7C8962, 0x7C8A3A, "thunk"), (0x7DC720, 0x7DCE62, "comsupp"),
           (0x7DCE62, 0x7DCFC3, "thunk"), (0x7C8A3A, 0x7E1000, "crt")]
CLASSES = ("real_missed", "alt_entry", "shared_tail", "data", "padding_thunk")
PROLOGUES = (b"\x55\x8b\xec", b"\x83\xec", b"\x81\xec", b"\x56", b"\x53", b"\x57", b"\x51", b"\x52", b"\x50",
             b"\x6a\xff", b"\x64\xa1", b"\x8b", b"\x33\xc0", b"\xb8", b"\xc3", b"\xc2", b"\x55", b"\xa1", b"\x8a",
             b"\xd9", b"\xdd", b"\x68", b"\x6a", b"\x32\xc0", b"\xb0", b"\x0f", b"\x89", b"\x83", b"\x85", b"\x84",
             b"\x31", b"\x3b", b"\x39", b"\x88", b"\xe8", b"\xe9", b"\xf6", b"\xff", b"\x66", b"\x80", b"\x2b", b"\x0b")


def region_kind(a):
    for lo, hi, k in REGIONS:
        if lo <= a < hi:
            return k
    return "engine"


class Census:
    """Sorted census entries with interval lookup."""

    def __init__(self, entries):
        rows = sorted((int(e[0], 16), int(e[1], 16)) for e in entries)
        self.starts = [a for a, _ in rows]
        self.lens = [n for _, n in rows]
        self.set = set(self.starts)

    def containing(self, va):
        """(start, len) of a census extent with start <= va < start+len (an exact start counts), else None."""
        i = bisect.bisect_right(self.starts, va) - 1
        for j in range(i, max(-1, i - 8), -1):
            if self.starts[j] <= va < self.starts[j] + self.lens[j]:
                return self.starts[j], self.lens[j]
        return None

    def prev_end(self, va):
        i = bisect.bisect_left(self.starts, va) - 1
        return self.starts[i] + self.lens[i] if i >= 0 else None

    def preceding(self, va):
        i = bisect.bisect_left(self.starts, va) - 1
        return (self.starts[i], self.lens[i]) if i >= 0 else None


def table_ranges(walks):
    """[(lo, hi)] of jump tables and byte index tables read during the walks, sorted."""
    r = []
    for w in walks.values():
        for tva, targets, btab, bcount in w.tables:
            if targets:
                r.append((tva, tva + 4 * len(targets)))
            if btab is not None and bcount:
                r.append((btab, btab + bcount))
    r.sort()
    return r


def in_ranges(ranges, los, va):
    i = bisect.bisect_right(los, va) - 1
    return i >= 0 and ranges[i][0] <= va < ranges[i][1]


def gather(img, census_entries):
    """Walk from the census starts plus every reference source. Returns a context dict."""
    cen = Census(census_entries)
    vt = X.rtti_vtables(img)
    vslots = {}
    for key, slots in vt.items():
        for i, t in enumerate(slots):
            vslots.setdefault(t, []).append((key[0], i))
    dptr = X.data_code_pointers(img)
    roots = set(cen.starts) | set(vslots)
    walks, starts, ev = X.discover(img, sorted(roots))
    # data pointers that no code reaches are walked too, so their own callees are seen
    extra = [t for t in dptr if t not in walks and img.in_text(t) and not cen.containing(t)]
    if extra:
        w2, s2, ev2 = X.discover(img, sorted(set(extra) - set(walks)))
        for s, w in w2.items():
            walks.setdefault(s, w)
        starts |= s2
        for t, kinds in ev2.items():
            for k, sites in kinds.items():
                ev.setdefault(t, {}).setdefault(k, []).extend(sites)
    for t, srcs in vslots.items():
        ev.setdefault(t, {}).setdefault("vtable", []).extend("%s[%d]" % (cls, i) for cls, i in srcs)
    for t, srcs in dptr.items():
        if t not in vslots:
            ev.setdefault(t, {}).setdefault("dataptr", []).extend(srcs)
    for t in X.padding_starts(img):
        if t not in cen.set:
            ev.setdefault(t, {}).setdefault("pad_aligned", []).append(t)
    ranges = table_ranges(walks)
    return dict(cen=cen, walks=walks, ev=ev, ranges=ranges, rlos=[a for a, _ in ranges], vslots=vslots, dptr=dptr)


def is_thunk(w):
    ins = sorted(w.insns)
    if not ins or len(ins) > 3:
        return False
    last = w.insns[ins[-1]]
    return last[1] in (X.JMP, X.JMPIND) and not w.calls


def classify(img, ctx, c):
    """-> (class, confidence or None, reason, extra dict) for candidate c (not a census start)."""
    cen, walks, ev = ctx["cen"], ctx["walks"], ctx["ev"]
    kinds = ev.get(c, {})
    first = img._text[c - img.text_lo] if img.in_text(c) else None
    w = walks.get(c)
    if first in (0xCC, 0x90):
        return "padding_thunk", None, "points at CC/90 padding", {}
    if in_ranges(ctx["ranges"], ctx["rlos"], c):
        return "data", None, "inside a jump or index table", {}
    inside = cen.containing(c)
    if w is None:
        w = walks[c] = X.walk(img, c, cen.set)
    clean = not w.bad and not w.suspicious and not w.out_of_text
    reach = None
    if inside:
        fw = walks.get(inside[0])
        if fw is not None and c in fw.insns:
            reach = inside[0]
    if w and w.insns and is_thunk(w) and clean and not inside:
        return "padding_thunk", None, "jump thunk", {}
    if inside:
        if reach is not None:
            call_like = any(k in kinds for k in ("call", "vtable", "codeptr", "dataptr"))
            why = "interior of 0x%X at an instruction boundary" % inside[0]
            if not call_like and "jmp" not in kinds:
                why += " (a branch target inside it; nothing outside refers to it)"
            return ("alt_entry" if call_like else "shared_tail"), None, why, {"inside": inside[0]}
        if fw is not None and _mid_instruction(fw, c):
            return "data", None, "interior of 0x%X, inside one of its instructions" % inside[0], {"inside": inside[0]}
        if img.padding_before(c) and clean and w.insns:
            return "real_missed", _confidence(img, c, w, kinds, ctx), "starts after padding inside the extent of 0x%X (merged)" % inside[0], {"inside": inside[0]}
        term = any(r[1] in (X.RET, X.JMP, X.JMPIND, X.HALT) for r in w.insns.values())
        if clean and w.insns and term and kinds.keys() & {"codeptr", "dataptr", "vtable", "call"}:
            return "alt_entry", None, "interior of 0x%X in bytes normal flow never reaches: an exception-handler or funclet entry named by a table" % inside[0], {"inside": inside[0], "sub": "eh_entry"}
        return "data", None, "interior of 0x%X, in bytes its walk never reached (not code or unreachable)" % inside[0], {"inside": inside[0]}
    # not inside any census extent
    if not clean or not w.insns:
        return "data", None, "does not decode as code (%s)" % ("undecodable" if w.bad else "data-like opcodes" if w.suspicious else "leaves .text"), {}
    pv = cen.preceding(c)
    if kinds.keys() <= {"jmp"} and pv and 0 <= c - (pv[0] + pv[1]) <= 3 and not img.padding_before(c):
        return "shared_tail", None, "continues 0x%X (its census extent ends just before)" % pv[0], {"continues": pv[0]}
    sub = _funclet(img, c, w, kinds)
    return ("real_missed", _confidence(img, c, w, kinds, ctx), "unwind/catch funclet outside every listed extent" if sub else "unlisted code start",
            {"sub": sub} if sub else {})


_STARTS_CACHE = {}


def _mid_instruction(fw, c):
    """True when c falls strictly inside an instruction of walk fw."""
    k = id(fw)
    if k not in _STARTS_CACHE:
        _STARTS_CACHE.clear()
        _STARTS_CACHE[k] = sorted(fw.insns)
    ss = _STARTS_CACHE[k]
    i = bisect.bisect_right(ss, c) - 1
    return i >= 0 and ss[i] < c < ss[i] + fw.insns[ss[i]][0]


def _funclet(img, c, w, kinds):
    """EH unwind funclet shape: only a data pointer or alignment backs it, it is short, its first
    instruction addresses the frame through ebp (mov/lea r,[ebp+x]) and it ends in a jump or ret."""
    if not (kinds.keys() <= {"dataptr", "pad_aligned"}) or "dataptr" not in kinds:
        return None
    t = img._text
    o = c - img.text_lo
    if t[o] not in (0x8B, 0x8D) or (t[o + 1] & 0xC7) not in (0x45, 0x85):
        return None
    if w.end - c > 0x60 or w.calls and len(w.calls) > 2:
        return None
    last = w.insns[max(w.insns)]
    return "eh_funclet" if last[1] in (X.JMP, X.RET) else None


def _confidence(img, c, w, kinds, ctx):
    from_census_call = False
    for site in kinds.get("call", []):
        if ctx["cen"].containing(site):
            from_census_call = True
    term = any(r[1] in (X.RET, X.JMP, X.JMPIND, X.HALT) for r in w.insns.values())
    pro = img._text[c - img.text_lo: c - img.text_lo + 3].startswith(PROLOGUES)
    pad = img.padding_before(c)
    if term and pro and (from_census_call or "vtable" in kinds) and pad:
        return "high"
    if term and pro and (kinds.keys() & {"call", "vtable", "jmp", "codeptr", "dataptr"} or (pad and "pad_aligned" in kinds)):
        return "medium"
    return "low"


def run(img, census_entries, examples=5):
    ctx = gather(img, census_entries)
    cen, walks, ev = ctx["cen"], ctx["walks"], ctx["ev"]
    cands = {t for t in ev if img.in_text(t)} - cen.set
    cands |= {s for s in walks if s not in cen.set}
    out = []
    for c in sorted(cands):
        cls, conf, reason, extra = classify(img, ctx, c)
        kinds = ev.get(c, {})
        evid = [dict(kind=k, n=len(v), sites=[("0x%X" % s) if isinstance(s, int) else s for s in sorted(v, key=str)[:4]]) for k, v in sorted(kinds.items())]
        e = dict(addr="0x%X" % c, cls=cls, reason=reason, evidence=evid)
        if conf:
            e["confidence"] = conf
        w = walks.get(c)
        if w is not None and w.insns:
            e["walk"] = dict(insns=len(w.insns), len="0x%X" % (w.end - c), clean=not (w.bad or w.suspicious or w.out_of_text))
        for k, v in extra.items():
            e[k] = v if isinstance(v, str) else "0x%X" % v
        e["padding_before"] = img.padding_before(c)
        out.append(e)
    counts = collections.Counter(e["cls"] for e in out)
    conf = collections.Counter(e.get("confidence") for e in out if e["cls"] == "real_missed")
    sub = collections.Counter(e.get("sub", "plain") for e in out if e["cls"] == "real_missed")
    alt_sub = collections.Counter(e.get("sub", "boundary") for e in out if e["cls"] == "alt_entry")
    by_src = collections.Counter()
    for e in out:
        by_src[(e["cls"], "+".join(sorted(k["kind"] for k in e["evidence"])) or "none")] += 1
    # precision/recall of the census against the real code starts it should list
    listed = len(cen.set)
    real_hi = sum(1 for e in out if e["cls"] == "real_missed" and e.get("confidence") in ("high", "medium"))
    summary = dict(census_functions=listed, candidates_not_in_census=len(out), classes=dict(counts), real_missed_confidence=dict(conf), real_missed_by_shape=dict(sub), alt_entry_by_shape=dict(alt_sub),
                   class_by_evidence={"%s | %s" % k: v for k, v in sorted(by_src.items())},
                   recall_estimate=round(listed / float(listed + real_hi), 4) if listed else None,
                   census_plus_proposed=listed + real_hi,
                   all_code_starts_if_every_class_but_data_counts=listed + sum(counts[c] for c in CLASSES if c != "data"))
    ex = {c: [e for e in out if e["cls"] == c][:examples] for c in CLASSES}
    proposed = [dict(addr=e["addr"], len=e["walk"]["len"], kind=region_kind(int(e["addr"], 16)), confidence=e["confidence"], shape=e.get("sub", "plain"),
                     evidence=e["evidence"], reason=e["reason"])
                for e in out if e["cls"] == "real_missed" and e.get("confidence") in ("high", "medium")]
    return dict(schema=SCHEMA, summary=summary, examples=ex, proposed_additions=proposed, candidates=out)


def slim(rep):
    """Report without the data-class candidates (thousands of integer constants that look like code addresses)."""
    r = dict(rep)
    r["candidates"] = [e for e in rep["candidates"] if e["cls"] != "data"]
    r["data_candidates_omitted"] = rep["summary"]["classes"].get("data", 0)
    return r


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--yr", default=os.environ.get("GAMEMD_BINARY"))
    ap.add_argument("--census", default=str(ROOT / "scripts" / "data" / "function_extents.json"))
    ap.add_argument("--out", help="write the full report JSON (candidates, examples, proposed_additions)")
    ap.add_argument("--examples", type=int, default=5)
    ap.add_argument("--all", action="store_true", help="keep the data-class candidates in --out")
    a = ap.parse_args(argv)
    if not a.yr:
        raise SystemExit("set GAMEMD_BINARY (or --yr)")
    img = X.Image(a.yr)
    if img.sha256 != SHA256:
        raise SystemExit("%s: not the pinned gamemd.exe (sha256 %s)" % (a.yr, img.sha256))
    census = json.load(open(a.census))["entries"]
    rep = run(img, census, a.examples)
    rep["image_sha256"] = img.sha256
    s = rep["summary"]
    print("census %d; candidates not in census %d" % (s["census_functions"], s["candidates_not_in_census"]))
    for c in CLASSES:
        print("  %-14s %6d" % (c, s["classes"].get(c, 0)))
    print("every non-data class counted:", s["all_code_starts_if_every_class_but_data_counts"])
    print("real_missed confidence", s["real_missed_confidence"], "-> census + proposed =", s["census_plus_proposed"], "recall", s["recall_estimate"])
    for c in CLASSES:
        for e in rep["examples"][c][: a.examples]:
            print("  e.g. %s %s: %s" % (c, e["addr"], e["reason"]))
    if a.out:
        Path(a.out).write_text(json.dumps(rep if a.all else slim(rep), indent=1) + "\n")
        print("wrote", a.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
