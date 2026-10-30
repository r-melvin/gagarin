#!/usr/bin/env python3
# Provenance: original. Finds a canonical class declaration (main's headers) for a vtable-slot function.
"""find(item) -> dict(cls, header, name, rt, params, const) when an RTTI class holding the function at its
vtable slot has a header in the worktree that already declares that member (by address annotation or `vf_<slot>`)."""
import functools
import glob
import re
from collections import defaultdict
from pathlib import Path

import data

DECL = re.compile(r"virtual\s+(?P<rt>[^;(]+?)\s+(?P<name>\w+)\s*\((?P<params>[^)]*)\)\s*(?P<const>const)?\s*;")


@functools.lru_cache(None)
def chains():
    rt = data.common.load_json("rtti_classes.json")["classes"]
    return {v["demangled_name"]: v["base_chain"] for v in rt.values()}


def owner_of(entries):
    """(class, slot, n_classes) of the topmost RTTI class holding the function in its primary vtable.
    entries: [[class, slot, base_offset, vtable_va], ...]"""
    ents = [e for e in entries if e[2] == 0] or list(entries)
    ch = chains()
    names = {e[0] for e in ents}
    best = None
    for n in sorted(names):
        if all(n in ch.get(o, [o]) for o in names):
            best = n
            break
    if best is None:
        best = min(sorted(names), key=lambda n: len(ch.get(n, [n])))
    slot = next(e[1] for e in ents if e[0] == best)
    return best, slot, len(names)


@functools.lru_cache(None)
def headers():
    idx = defaultdict(list)
    for p in glob.glob(str(data.WT / "match") + "/**/*", recursive=True):
        if not p.lower().endswith(".h"):
            continue
        if "trivial_tu" in p:
            continue
        tx = Path(p).read_text(errors="replace")
        for m in re.finditer(r"(?m)^(?:class|struct)\s+(\w+)\s*(?::[^{;]*)?\{", tx):
            idx[m.group(1)].append((p, tx, m.start()))
    return idx


def class_body(tx, start):
    i = tx.index("{", start)
    depth = 0
    for j in range(i, len(tx)):
        if tx[j] == "{":
            depth += 1
        elif tx[j] == "}":
            depth -= 1
            if depth == 0:
                return tx[i:j]
    return tx[i:]


def find(addr, vtable):
    """vtable: [[class, slot, base_offset, vtable_va], ...]"""
    ents = [e for e in vtable if e[2] == 0] or vtable
    top, top_slot, _ = owner_of(vtable)
    order = [(top, top_slot)] + [(e[0], e[1]) for e in sorted(ents, key=lambda e: (len(e[0]), e[0])) if e[0] != top]
    for cls_full, slot in order:
        cls = cls_full.split("::")[-1]
        for path, tx, st in headers().get(cls, []):
            body = class_body(tx, st)
            m = re.search(r"//\s*FUNCTION:\s*GAMEMD\s+0x%X\b[^\n]*\n\s*([^\n]*)" % addr, body, re.I)
            line = m.group(1) if m else None
            if line is None:
                m2 = re.search(r"[^\n]*\bvf_%d\s*\([^\n]*" % slot, body)
                line = m2.group(0) if m2 else None
            if not line:
                continue
            d = DECL.search(line)
            if not d:
                continue
            return dict(cls=cls, header=path, name=d.group("name"), rt=d.group("rt").strip(),
                        params=d.group("params").strip(), const=bool(d.group("const")), slot=slot)
    return None
