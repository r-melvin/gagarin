#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; reads only the project's own compiled objects and
# the pinned PE through diff_retail.py.
"""Label what is still wrong with each near-miss partial row.

For every manifest row with status "partial" and pct >= --min-pct (default 80),
compile its TU once (a private object under a temp dir), run diff_retail.py with
--dump-streams for each row, and classify the residual between the retail and
compiled instruction streams:

  register-swap    same instruction shapes, same order, only register operands differ
  stack-slot       same shapes/order, only [esp+N]/[ebp+N] displacements (or frame
                   size adjustments of esp) differ
  constant         same shapes/order, only non-address immediates/displacements differ
  scheduling       same multiset of instruction shapes, different order
  branch-target    same instructions in the same order but direct jumps land on
                   different instructions (block layout)
  branch-polarity  every non-branch instruction matches as a multiset; the conditional
                   branches differ only by inversion/mirroring (je<->jne, jl<->jg,
                   ...), possibly with a jmp added or removed
  missing-extra    the instruction multiset differs (mnemonics or operand shapes)
  reloc-or-table   streams look identical but the score is below 100 (relocation
                   target, switch table or float literal)

A row can carry several labels. `eligible` is true when no missing-extra or
constant label is present, i.e. the permuter has something to search.

Usage:
  residual_classify.py [--manifest M] [--out scripts/data/partial_residuals.json]
                       [--min-pct 80] [-j 4] [--only ADDR ...]
"""
import argparse
import collections
import concurrent.futures
import json
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from diff_retail import canon_mnemonic  # noqa: E402

REG_RE = re.compile(
    r"\b(e(?:ax|bx|cx|dx|si|di|bp|sp)|ax|bx|cx|dx|si|di|bp|sp"
    r"|[abcd][lh]|st\(\d\)|st|mm\d|xmm\d+)\b")
HEX_RE = re.compile(r"\b0x[0-9a-f]+\b")
DEC_RE = re.compile(r"(?<![\w.])\d+\b")
BRACKET_RE = re.compile(r"\[[^\]]*\]")

# conditional jumps and setcc grouped by comparison family
_CC_GROUP = {}
for _fam, _ccs in {"eq": ("e", "ne"), "sgn": ("l", "ge", "g", "le"),
                   "uns": ("b", "ae", "a", "be"), "s": ("s", "ns"),
                   "p": ("pe", "po")}.items():
    for _cc in _ccs:
        _CC_GROUP["j" + _cc] = "jcc_" + _fam
        _CC_GROUP["set" + _cc] = "setcc_" + _fam
        _CC_GROUP["cmov" + _cc] = "cmovcc_" + _fam


def reg_width(name):
    if name.startswith("e"):
        return "R32"
    if name in ("al", "bl", "cl", "dl", "ah", "bh", "ch", "dh"):
        return "R8"
    if name.startswith(("st", "mm", "xmm")):
        return "RF"
    return "R16"


def is_branch(mnem):
    return mnem == "jmp" or mnem in _CC_GROUP and mnem.startswith("j")


def dissect(mnem, ops, relocvals, retail_side):
    """Split an instruction into (shape, regs, stack, imms).

    shape: mnemonic plus operands with registers, numbers and addresses masked
    regs:  register names in order
    stack: numbers inside [esp...]/[ebp...] brackets, and the immediate of an
           esp adjustment (sub/add esp,N), i.e. frame layout
    imms:  every other number that is not a relocation/address/branch target
    """
    mnem = canon_mnemonic(mnem)
    ops = ops.lower()
    if (mnem == "call" or mnem[0] == "j" or mnem.startswith("loop")) and re.fullmatch(
            r"(0x)?[0-9a-f]+(\s*<.*>)?", ops):
        return (mnem + " T", (), (), ())
    ops = re.sub(r"\s*<[^>]*>", "", ops)

    def is_addr(tok):
        v = int(tok, 16)
        if retail_side:
            return 0x400000 <= v < 0x1000000
        return v in relocvals

    stack, imms = [], []

    def bracket(m):
        body = m.group(0)
        if re.search(r"\b(esp|ebp)\b", body):
            stack.extend(HEX_RE.findall(body))
            return "[" + HEX_RE.sub("N", body[1:-1]) + "]"

        def sub(mm):
            tok = mm.group(0)
            if is_addr(tok):
                return "A"
            imms.append(tok)
            return "N"
        return "[" + HEX_RE.sub(sub, body[1:-1]) + "]"

    shape = BRACKET_RE.sub(bracket, ops)
    # numbers outside brackets
    esp_adj = mnem in ("sub", "add") and shape.startswith("esp,")

    def sub_out(mm):
        tok = mm.group(0)
        if esp_adj:
            stack.append(tok)
            return "N"
        if is_addr(tok):
            return "A"
        imms.append(tok)
        return "N"

    shape = HEX_RE.sub(sub_out, shape)
    shape = DEC_RE.sub(lambda m: imms.append(m.group(0)) or "N", shape)
    regs = tuple(REG_RE.findall(shape))
    shape = REG_RE.sub(lambda m: reg_width(m.group(1)), shape)
    return (mnem + " " + shape, regs, tuple(stack), tuple(imms))


def reloc_values(comp, relocs):
    """Per compiled instruction, the 32-bit values sitting in relocation slots."""
    out = []
    for off, hx, _m, _o in comp:
        ln = len(hx) // 2
        vals = set()
        for r in relocs:
            if off <= r < off + ln and r + 4 <= off + ln:
                b = bytes.fromhex(hx)[r - off:r - off + 4]
                vals.add(int.from_bytes(b, "little"))
        out.append(vals)
    return out


def branch_targets(insns, base):
    """{insn index: target insn index} for direct in-function jumps."""
    at = {off: i for i, (off, _h, _m, _o) in enumerate(insns)}
    out = {}
    for i, (_off, _h, m, o) in enumerate(insns):
        m = canon_mnemonic(m)
        if m[0] == "j" and re.fullmatch(r"(0x)?[0-9a-f]+(\s*<.*>)?", o.strip()):
            tok = o.split()[0]
            out[i] = at.get(int(tok, 16) - base, -1)
    return out


def classify(retail, comp, relocs=(), base=0):
    """Classify the residual between two instruction streams.

    retail/comp: lists of (offset, hexbytes, mnemonic, operands).
    Returns {"labels": [...], ...counts...}.
    """
    rv = [set() for _ in retail]
    cv = reloc_values(comp, relocs)
    R = [dissect(m, o, rv[i], True) for i, (_, _, m, o) in enumerate(retail)]
    C = [dissect(m, o, cv[i], False) for i, (_, _, m, o) in enumerate(comp)]
    res = {"retail_insns": len(retail), "comp_insns": len(comp), "labels": []}
    if R == C and branch_targets(retail, base) == branch_targets(comp, 0):
        res["labels"] = ["reloc-or-table"]
        return res

    def grouped(sh):
        m, _, rest = sh.partition(" ")
        return (_CC_GROUP.get(m, m) + " " + rest).strip()

    rm = collections.Counter(canon_mnemonic(i[2]) for i in retail)
    cm = collections.Counter(canon_mnemonic(i[2]) for i in comp)
    res["only_retail"] = dict(rm - cm)
    res["only_compiled"] = dict(cm - rm)

    # non-branch instructions drive the multiset test; branches are judged apart
    def nb(items):
        return [x for x in items if not is_branch(x[0].split()[0])]

    Rn, Cn = nb(R), nb(C)
    shape_r = collections.Counter(x[0] for x in Rn)
    shape_c = collections.Counter(x[0] for x in Cn)
    labels = []
    if shape_r != shape_c:
        res["only_retail_shapes"] = dict(shape_r - shape_c)
        res["only_compiled_shapes"] = dict(shape_c - shape_r)
        labels.append("missing-extra")
        res["labels"] = labels
        return res

    jr = collections.Counter(x[0] for x in R if is_branch(x[0].split()[0]))
    jc = collections.Counter(x[0] for x in C if is_branch(x[0].split()[0]))
    if jr != jc:
        gr = collections.Counter(grouped(k) for k in jr.elements() if k.split()[0] != "jmp")
        gc = collections.Counter(grouped(k) for k in jc.elements() if k.split()[0] != "jmp")
        if gr == gc:
            labels.append("branch-polarity")
        else:
            labels.append("missing-extra")
            res["labels"] = labels
            return res

    if len(R) == len(C) and [x[0] for x in R] == [x[0] for x in C]:
        # same shape at every position: aspects per position
        res["sched"] = False
        if branch_targets(retail, base) != branch_targets(comp, 0):
            labels.append("branch-target")
        nreg = nstk = nimm = 0
        for r, c in zip(R, C):
            if r[1] != c[1]:
                nreg += 1
            if r[2] != c[2]:
                nstk += 1
            if r[3] != c[3]:
                nimm += 1
    else:
        if "branch-polarity" not in labels:
            labels.append("scheduling")
        else:
            res["sched"] = True
        # aspects by multiset
        def msd(idx):
            a = collections.Counter((x[0], x[idx]) for x in Rn)
            b = collections.Counter((x[0], x[idx]) for x in Cn)
            return sum(((a - b)).values())
        nreg, nstk, nimm = msd(1), msd(2), msd(3)
    res.update({"reg_diffs": nreg, "stack_diffs": nstk, "imm_diffs": nimm})
    if nreg:
        labels.append("register-swap")
    if nstk:
        labels.append("stack-slot")
    if nimm:
        labels.append("constant")
    if not labels:
        labels = ["reloc-or-table"]
    res["labels"] = labels
    return res


PRIORITY = ["missing-extra", "constant", "branch-polarity", "scheduling", "branch-target",
            "register-swap", "stack-slot", "reloc-or-table"]
PERMUTABLE = {"register-swap", "stack-slot", "scheduling", "branch-polarity",
              "branch-target"}


def primary(labels):
    for p in PRIORITY:
        if p in labels:
            return p
    return "exact"


def compile_tu(tu, tmp):
    src = os.path.join(ROOT, tu)
    obj = os.path.join(tmp, os.path.basename(src).rsplit(".", 1)[0] + ".obj")
    subprocess.run(["bash", os.path.join(ROOT, "scripts/vc6/vc6cl.sh"),
                    "/Fo" + obj, os.path.basename(src)],
                   cwd=os.path.dirname(src), stdout=subprocess.DEVNULL,
                   stderr=subprocess.DEVNULL)
    return obj if os.path.exists(obj) else None


def run_tu(tu, rows):
    out = []
    with tempfile.TemporaryDirectory(prefix="residual_") as tmp:
        obj = compile_tu(tu, tmp)
        for e in rows:
            rec = {"addr": e["addr"], "name": e["name"], "tu": tu, "sym": e["sym"],
                   "len": e["len"], "manifest_pct": e.get("pct")}
            if not obj:
                rec.update(labels=["compile-fail"], primary="compile-fail", eligible=False)
                out.append(rec)
                continue
            dump = os.path.join(tmp, "streams.json")
            if os.path.exists(dump):
                os.unlink(dump)
            p = subprocess.run(
                [sys.executable, os.path.join(ROOT, "scripts/vc6/diff_retail.py"),
                 "--obj", obj, "--sym", e["sym"], "--addr", e["addr"], "--len", e["len"],
                 "--dump-streams", dump], capture_output=True, text=True)
            m = re.search(r"match: ([\d.]+)%", p.stdout)
            rec["pct"] = float(m.group(1)) if m else None
            if "table:" in p.stdout and re.search(r"table: (\d+)/(\d+)", p.stdout):
                g, t = re.search(r"table: (\d+)/(\d+)", p.stdout).groups()
                rec["table"] = f"{g}/{t}"
            if not os.path.exists(dump):
                rec.update(labels=["no-score"], primary="no-score", eligible=False,
                           note=(p.stdout + p.stderr).strip().splitlines()[-1:] or "")
                out.append(rec)
                continue
            d = json.load(open(dump))
            res = classify([tuple(x) for x in d["retail"]],
                           [tuple(x) for x in d["comp"]], d["relocs"],
                           int(e["addr"], 16))
            rec.update(res)
            rec["primary"] = primary(res["labels"])
            rec["eligible"] = (bool(res["labels"]) and
                               set(res["labels"]) <= PERMUTABLE)
            out.append(rec)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--manifest", default=os.path.join(ROOT, "scripts/data/match_manifest.json"))
    ap.add_argument("--patches", default=os.path.join(ROOT, "scripts/data/distribution_patches.json"))
    ap.add_argument("--out", default=os.path.join(ROOT, "scripts/data/partial_residuals.json"))
    ap.add_argument("--min-pct", type=float, default=80.0)
    ap.add_argument("-j", type=int, default=4)
    ap.add_argument("--only", nargs="*", default=[])
    a = ap.parse_args()
    patched = {p["addr"].lower() for p in json.load(open(a.patches))["patches"]}
    rows = [e for e in json.load(open(a.manifest))
            if e["status"] == "partial" and e.get("pct", 0) >= a.min_pct
            and e["addr"].lower() not in patched
            and e["addr"].lower() != "0x64dea0"
            and (not a.only or e["addr"].lower() in {x.lower() for x in a.only})]
    by_tu = collections.defaultdict(list)
    for e in rows:
        by_tu[e["tu"]].append(e)
    results = []
    with concurrent.futures.ThreadPoolExecutor(a.j) as ex:
        for part in ex.map(lambda kv: run_tu(*kv), by_tu.items()):
            results.extend(part)
    results.sort(key=lambda r: int(r["addr"], 16))
    with open(a.out, "w") as f:
        json.dump(results, f, indent=1)
        f.write("\n")
    hist = collections.Counter(r["primary"] for r in results)
    anyl = collections.Counter(l for r in results for l in r["labels"])
    print(f"{len(results)} rows in {len(by_tu)} TUs -> {a.out}")
    print("primary label:", dict(hist.most_common()))
    print("any label:    ", dict(anyl.most_common()))
    print("permuter-eligible:", sum(1 for r in results if r["eligible"]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
