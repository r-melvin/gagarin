#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling. The register model is the minimum model published in the notes of the
# CC0 homm3 decompilation project (its regalloc and behavior-catalog pages, B1/B8/B14/B16) for the
# same C2.DLL 12.00.8447 back end; gagarin confirms every label against its own binary.
"""regpredict: label a register/order residual with the likely VC6 back-end cause.

Model (homm3 regalloc.md, "minimum model, not a complete allocator description"):
  * the fallback preference order is EAX, ECX, EDX, ESI, EDI, EBX, EBP, consumed first-fit;
  * call-crossing values lose EAX/ECX/EDX, so they take ESI, EDI, EBX, EBP in that order;
  * byte-sized values lose ESI/EDI/EBP;
  * small probes follow pseudo-creation order (argument evaluation order unless a name hoists a
    value), so swapping the creation order of two call-crossing values swaps their registers.
Catalogue labels used (homm3 behavior-catalog.md): B1 role swap, B8 zero-CSE, B14 creation order
(a named temporary hoists a value), B16 post-RA schedule (identical multiset, transposed
instructions, no known lever: parked).

It also recognises the operand-order patches reccmp applies (fixes.py patch_mov_commutative,
patch_cmp_swaps): `add eax,ecx` vs `add ecx,eax`, swapped base/index, `cmp a,b` vs `cmp b,a`.
The output is a label and a lever hint, never a match claim.

The functions take residual_classify.dissect tuples (shape, regs, stack, imms).
"""
import collections
import re

PREFERENCE = ("eax", "ecx", "edx", "esi", "edi", "ebx", "ebp")
CALLEE_SAVED = ("esi", "edi", "ebx", "ebp")
VOLATILE = ("eax", "ecx", "edx")
COMMUTATIVE = {"add", "and", "or", "xor", "imul", "adc", "test"}
REG_TOKEN = re.compile(r"R(?:32|16|8|F)")


def operand_swap_kind(shape, rregs, cregs):
    """'commutative' | 'cmp' | 'base-index' when two same-shape instructions differ only by an
    operand swap, else None."""
    if rregs == cregs or len(rregs) != len(cregs) or sorted(rregs) != sorted(cregs):
        return None
    mnem, _, ops = shape.partition(" ")
    if len(rregs) == 2 and rregs == cregs[::-1] and re.fullmatch(r"(R(?:32|16|8)),\1", ops):
        if mnem in COMMUTATIVE:
            return "commutative"
        if mnem == "cmp":
            return "cmp"
    m = re.search(r"\[R32\+R32\]", shape)
    if m:
        k = len(REG_TOKEN.findall(shape[:m.start()]))
        if (rregs[:k] == cregs[:k] and rregs[k:k + 2] == cregs[k:k + 2][::-1]
                and rregs[k + 2:] == cregs[k + 2:]):
            return "base-index"
    return None


def first_fit_prefix(regs_in_order):
    """True when the callee-saved registers first appear in the model's order (a prefix of ESI, EDI, EBX, EBP)."""
    seen = []
    for r in regs_in_order:
        if r in CALLEE_SAVED and r not in seen:
            seen.append(r)
    return seen == list(CALLEE_SAVED[:len(seen)])


def predict(R, C):
    """Label the residual between dissected streams R (retail) and C (compiled).

    Returns {"label", "detail", "lever"} or None when the streams have no register/order residual.
    """
    if R == C:
        return None
    if len(R) == len(C) and collections.Counter(R) == collections.Counter(C):
        return {"label": "B16-schedule", "detail": "identical instruction multiset, transposed",
                "lever": "none known (parked)"}
    if len(R) == len(C) and [x[0] for x in R] == [x[0] for x in C]:
        pairs, kinds, other = [], [], 0
        for r, c in zip(R, C):
            if r[1] == c[1]:
                continue
            k = operand_swap_kind(r[0], r[1], c[1])
            if k:
                kinds.append(k)
                continue
            if r[2] != c[2] or r[3] != c[3]:
                other += 1
            pairs += [(a, b) for a, b in zip(r[1], c[1]) if a != b]
        if kinds and not pairs:
            lab = "cmp-swap" if set(kinds) == {"cmp"} else "commutative-swap"
            return {"label": lab, "detail": "%d operand swap(s): %s" % (len(kinds), ",".join(sorted(set(kinds)))),
                    "lever": "source_perm --only commute"}
        if pairs:
            fwd = {}
            ok = True
            for a, b in pairs:
                if fwd.setdefault(a, b) != b:
                    ok = False
            rev = {b: a for a, b in fwd.items()}
            injective = len(rev) == len(fwd)
            detail = ",".join("%s->%s" % kv for kv in sorted(fwd.items()))
            retail_regs = [g for x in R for g in x[1]]
            comp_regs = [g for x in C for g in x[1]]
            ff_retail, ff_comp = first_fit_prefix(retail_regs), first_fit_prefix(comp_regs)
            if ok and injective and set(fwd) == set(fwd.values()):
                lab = "B1-role-swap"
                lever = "declaration/creation order of the two values; name a temporary (B14)"
            elif any((a in CALLEE_SAVED) != (b in CALLEE_SAVED) for a, b in fwd.items()):
                lab = "B1-call-crossing"
                lever = "whether the value lives across a call: statement order, or a named temporary"
            else:
                lab = "B1-rebind"
                lever = "creation order (B14); char locals home eagerly (B15)"
            if ff_retail and not ff_comp:
                detail += "; retail follows first-fit, ours does not"
            elif not ff_retail:
                detail += "; retail departs from first-fit (hoisted value or byte local)"
            return {"label": lab, "detail": detail, "lever": lever + ("; plus %d other" % other if other else "")}
    zr = sum(1 for x in R if x[0].startswith("xor R32,R32"))
    zc = sum(1 for x in C if x[0].startswith("xor R32,R32"))
    store0 = lambda L: sum(1 for x in L if x[0].startswith("mov [") and x[3] == ("0x0",))  # noqa: E731
    if zr > zc and store0(C) > store0(R):
        return {"label": "B8-zero-cse", "detail": "retail shares a zeroed register, we store immediates",
                "lever": "assignment form (`a = b = 0` stores b first, C4); measure"}
    return {"label": "unmodelled", "detail": "no register/order pattern in the minimal model", "lever": "manual"}
