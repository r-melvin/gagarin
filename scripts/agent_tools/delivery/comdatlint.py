#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original. COMDAT checks behind the pktlint rule `comdat` (reads compiled objects, no link).
"""comdatlint.py: catch an orphan COMDAT or a COMDAT/FUNCTION-row clash from the changed TUs' objects alone.

A packet can pass every gate and still fail the M3 link when a template or inline body becomes a COMDAT
function the manifest does not know: the link keeps it (a live relocation points at it) and it lands past
retail's text end, or the same name is also a strong definition in another TU (LNK2005).

Two findings, both from the COMDAT sections of the post-patch object of a changed TU (objects are read with
wwstruct/wwlib.py, the parser emitter_map.py uses):
  orphan     a function COMDAT whose symbol is neither a manifest row symbol nor a symbol_bindings.json / packet map
             key (for a bound symbol: its address has no row), that a live relocation reaches, and that the base compile of the same TU (with the base manifest)
             did not already leave reached, and that the link does not fold into the row at its bound address
             (stubgen.plan_folds: equal code and relocation targets, checked with coff_equivalence.fingerprint; an
             undecidable fold is a warning). An existing emission is not this packet's: from a non-COMDAT section (a matched body, data), or transitively from a COMDAT
             that is itself claimed or reached. Debug sections are discardable and do not count.
  clash      a COMDAT function of this object whose symbol is a matched manifest row of another TU annotated FUNCTION
             there (the link places it as a strong definition at the retail address; the copy is LNK2005). TEMPLATE
             and SYNTHETIC rows are COMDATs and merge; a template-instantiation symbol only warns (uncertain sub-case).

Library only: pktlint's rule `comdat` compiles the changed TUs and calls check().
"""
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "wwstruct"))
sys.path.insert(0, os.path.join(HERE, "..", "..", "vc6"))
import coffgen  # noqa: E402
import wwlib  # noqa: E402

IMAGE_SCN_CNT_CODE = 0x20
IMAGE_SCN_LNK_COMDAT = 0x1000
IMAGE_SCN_MEM_DISCARDABLE = 0x02000000


def read_object(path):
    """dict(secs, defs, rel, sym): secs = wwlib.sections list; defs = {symbol: section no} (external, defined);
    rel = {section no: set of target section nos} (defined targets only); sym = {name: section no}."""
    data = open(path, "rb").read()
    secs = wwlib.sections(data)
    syms = coffgen.read_symbols(data)
    sec_of = {i: s for i, n, v, s, scl, a in syms}
    defs = {n: s for i, n, v, s, scl, a in syms if scl == 2 and s > 0}
    rel = {}
    for k in range(1, len(secs) + 1):
        tgt = set()
        for off, idx, typ in wwlib.section_relocs(data, k):
            s = sec_of.get(idx, 0)
            if s > 0 and s != k:
                tgt.add(s)
        rel[k] = tgt
    return dict(secs=secs, defs=defs, rel=rel)


def _chars(o, sec):
    return o["secs"][sec - 1][3]


def comdat_functions(o):
    """{symbol: section no} of the external function COMDATs."""
    return {n: s for n, s in o["defs"].items() if _chars(o, s) & IMAGE_SCN_LNK_COMDAT and _chars(o, s) & IMAGE_SCN_CNT_CODE}


def reached(o, claimed, cut=(), cut_data=False):
    """Set of section numbers a link keeps: from every live non-COMDAT section and every COMDAT section holding a
    CLAIMED symbol, along relocations. A COMDAT DATA section holding a CUT (bound) symbol, a vtable at its retail
    address, is replaced by retail's and passes nothing on."""
    cutsec = {s for n, s in o["defs"].items() if (n in cut or cut_data) and not _chars(o, s) & IMAGE_SCN_CNT_CODE and _chars(o, s) & IMAGE_SCN_LNK_COMDAT}
    comdat = lambda s: _chars(o, s) & IMAGE_SCN_LNK_COMDAT
    live = lambda s: not (_chars(o, s) & IMAGE_SCN_MEM_DISCARDABLE)
    roots = [s for s in range(1, len(o["secs"]) + 1) if live(s) and not comdat(s)]
    roots += [s for n, s in o["defs"].items() if n in claimed and live(s)]
    seen, todo = set(roots), list(roots)
    while todo:
        cur = todo.pop()
        if cur in cutsec:
            continue
        for t in o["rel"].get(cur, ()):
            if t not in seen and live(t):
                seen.add(t)
                todo.append(t)
    return seen


def orphans(o, claimed, cut=()):
    """[symbol] of unclaimed function COMDATs of O that a live relocation reaches."""
    live = reached(o, claimed, cut)
    return sorted(n for n, s in comdat_functions(o).items() if n not in claimed and s in live)


def clashes(new, rows_by_sym, tu, is_strong, claimed=(), cut=()):
    """[(symbol, owner tu)]: a function COMDAT of NEW whose symbol is a matched row of ANOTHER TU that defines it as a
    FUNCTION (IS_STRONG(owner tu, addr)). The M3 link places such a row as a strong definition at its retail address, so
    the COMDAT copy collides (LNK2005); a TEMPLATE/SYNTHETIC row is a COMDAT itself and the copies merge. Only a copy
    a live relocation reaches counts, from code and the TU's own rows (CLAIMED), not through COMDAT data: a vtable's
    eagerly emitted virtuals are discarded unreferenced."""
    out = []
    live = reached(new, claimed, cut, True)
    for n, sec in comdat_functions(new).items():
        r = rows_by_sym.get(n)
        if sec in live and r and r.get("tu") != tu and is_strong(r["tu"], r["addr"]):
            out.append((n, r["tu"]))
    return sorted(out)


def load_bindings(manifest, bound):
    """stubgen's name -> (va, source) table for MANIFEST rows and the BOUND {symbol: address} bindings."""
    import stubgen
    return stubgen.load_bindings([r for r in manifest if r.get("sym") and r.get("addr")], bound)[0]


def row_va(r):
    return int(r["addr"], 16)


def same_body(prov_obj, prov_sym, obj, sym, extent, va, binds, cache):
    """Would the link fold SYM of OBJ into PROV_SYM of PROV_OBJ (coff_equivalence.fingerprint equal)? None-raising errors
    (VerifyError and friends) mean the fold is refused, which is False; anything else propagates."""
    import coff_equivalence as CE
    from verify_vtable import VerifyError
    try:
        a = CE.fingerprint(prov_obj, prov_sym, extent, va, binds, cache)
        b = CE.fingerprint(obj, sym, extent, va, binds, cache)
    except (VerifyError, KeyError, IndexError, struct.error):
        return False
    return a == b


def _addr(v):
    try:
        return int(str(v), 16)
    except ValueError:
        return None


def claimed_syms(manifest, bound):
    """Row symbols, plus every bound symbol whose retail address has no manifest row: retail supplies that body. A bound
    symbol whose address has a row under ANOTHER symbol (a placeholder view) is not claimed: the build keeps the COMDAT
    copy, and it links past retail .text (0x6B8880, 0x6B1AB0)."""
    rows = {_addr(r["addr"]) for r in manifest if r.get("addr")}
    out = {r["sym"] for r in manifest if r.get("sym")}
    out |= {n for n, a in bound.items() if _addr(a) not in rows}
    return out


def check(tus, new_objs, base_objs, manifest, base_manifest, bound, is_strong=None, folds=None):
    """[(kind, tu, symbol, detail)]. NEW_OBJS/BASE_OBJS: {tu: object path or None}; MANIFEST: rows after the delta;
    BOUND: {symbol: address} of bindings; FOLDS(sym, tu) -> True when the link folds the COMDAT into the matched row at its bound address (stubgen.plan_folds:
    equal code and relocation targets), False when it does not, None when that cannot be decided;
    IS_STRONG(tu, addr) says whether TU's annotation for ADDR is FUNCTION (clash check; None skips it)."""
    claimed = claimed_syms(manifest, bound)
    claimed0 = claimed_syms(base_manifest, bound)
    by_sym = {r["sym"]: r for r in manifest if r.get("sym") and r.get("status") == "matched"}
    out = []
    for tu in tus:
        if not new_objs.get(tu):
            continue
        new = read_object(new_objs[tu])
        base = read_object(base_objs[tu]) if base_objs.get(tu) else None
        old = set(orphans(base, claimed0, bound)) if base else set()
        for n in sorted(set(orphans(new, claimed, bound)) - old):
            f = folds(n, tu) if folds else False
            if f:
                continue        # collocated COMDAT: the link renames it away and the caller binds to the row (M3 identical at ad52bbff, 03a8d604, 3c139f27)
            if f is None:
                out.append(("orphan-unsure", tu, n, "function COMDAT with no row; whether the link folds it into the row at its bound address could not be decided"))
                continue
            out.append(("orphan", tu, n, "function COMDAT with no manifest row or binding, newly reached by a live relocation: "
                        "it links past retail .text (M3 differs or the image grows)"))
        if is_strong:
            own = {r["sym"] for r in manifest if r.get("sym") and r.get("tu") == tu}
            own0 = {r["sym"] for r in base_manifest if r.get("sym") and r.get("tu") == tu}
            old = {n for n, t in clashes(base, by_sym, tu, is_strong, own0, bound)} if base else set()
            for n, t in clashes(new, by_sym, tu, is_strong, own, bound):
                if n in old:
                    continue
                if "?$" in n:
                    # Uncertain sub-case: a template instantiation that is also a FUNCTION row elsewhere. M3 was identical
                    # with such pairs (ad52bbff, 03a8d604, 3c139f27); the LNK2005 failures were plain members
                    # (GenericNode::Link, GenericNode::GenericNode), so templates only warn.
                    out.append(("clash-template", tu, n, "template COMDAT also a FUNCTION row in %s (instantiations merge; not an error)" % t))
                    continue
                out.append(("clash", tu, n, "COMDAT here, a FUNCTION row (strong definition) in %s, newly reached: LNK2005 at link" % t))
    return out
