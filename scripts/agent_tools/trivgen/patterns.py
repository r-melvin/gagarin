#!/usr/bin/env python3
# Provenance: original. Named pattern classes for trivgen reports.
"""pattern_of(spec) -> short stable name used in counts and failure logs."""
import emit
from lift import Call, Store


def _imm_kind(v):
    return "addr" if emit.is_data_addr(v) else "int"


def pattern_of(sp):
    if sp.tree is not None:
        return "branching"
    st = sp.stmts
    calls = sp.calls
    r = sp.ret
    retn = "-retn" if sp.retn else ""
    if calls:
        c = calls[-1]
        if len(calls) == 1 and c.tail and not [s for s in st if isinstance(s, Store)]:
            if isinstance(c.target, tuple):
                return "vtable-thunk" if c.target[0] == "vt" else "import-thunk"
            if c.ecx is not None and c.ecx[0] == "ld":
                return "member-forwarder"
            if c.ecx is not None and c.ecx[0] == "imm":
                return "global-receiver-thunk"
            return "thunk"
        if c.tail:
            return "store-then-tail-call"
        return "call-wrapper"
    stores = [s for s in st if isinstance(s, Store)]
    if not stores:
        if r is None:
            return "empty" + retn
        t = r[0]
        if sp.ret_fp:
            return "global-fp-getter" if r[1][1] is None else "fp-getter"
        if t == "imm":
            v = r[1]
            if sp.ret_width == 1:
                return "const-bool" + retn
            if emit.is_data_addr(v):
                return "const-address" + retn
            return ("const-zero" if v == 0 else "const-int") + retn
        if t == "p0":
            return "return-this" + retn
        if t == "ld":
            _, base, disp, size, sg = r
            where = "global" if base is None else "member"
            kind = {4: "dword", 2: "word", 1: "byte"}.get(size, str(size))
            return f"{where}-getter-{kind}" + retn
        if t == "zx" and r[1][0] == "ld":
            return ("global" if r[1][1] is None else "member") + "-getter-" + {1: "byte", 2: "word"}[r[1][3]] + "-zx" + retn
        if t == "sx" and r[1][0] == "ld":
            return ("global" if r[1][1] is None else "member") + "-getter-" + {1: "byte", 2: "word"}[r[1][3]] + "-sx" + retn
        if t == "lea":
            return "address-of-member" + retn
        if t == "zx" and r[1][0] == "cmp":
            return "bool-test" + retn
        if t == "cmp":
            return "bool-test" + retn
        if t in ("bin", "un"):
            return "arith" + retn
        return "other-straightline"
    fp = any(s.fp for s in stores)
    allabs = all(s.base is None for s in stores)
    if allabs and fp:
        return "static-init-fp"
    if allabs:
        if len(stores) >= 2:
            return "static-init-stores"
        return "global-setter" + retn
    if all(s.base is not None for s in stores):
        if len(stores) == 1:
            s = stores[0]
            if s.value[0] == "bin":
                return "member-rmw"
            return "member-setter" + retn
        return "member-multi-store" + retn
    return "mixed-stores"


DESCR = {
    "empty": "Empty function.",
    "empty-retn": "Empty function that pops its stack arguments.",
    "const-int": "Returns a constant.",
    "const-zero": "Returns zero.",
    "const-bool": "Returns a constant boolean.",
    "const-address": "Returns the address of a global.",
    "return-this": "Returns its receiver.",
    "address-of-member": "Returns the address of a member.",
    "member-rmw": "Updates one member in place.",
    "member-setter": "Stores its argument in a member.",
    "member-multi-store": "Stores several members.",
    "global-getter": "Returns a global.",
    "global-setter": "Stores to a global.",
    "static-init-fp": "Static-initialiser shape: stores a floating-point expression of globals.",
    "static-init-stores": "Static-initialiser shape: stores constants to adjacent globals.",
    "thunk": "Tail-forwards to another function.",
    "global-receiver-thunk": "Tail-calls a method on a global object.",
    "member-forwarder": "Tail-calls a method on a member object.",
    "vtable-thunk": "Tail-calls a virtual method of its receiver.",
    "import-thunk": "Tail-calls an imported function.",
    "call-wrapper": "Calls other functions.",
    "store-then-tail-call": "Stores, then tail-calls.",
    "bool-test": "Returns a comparison result.",
    "arith": "Returns a computed value.",
}


def describe(pattern):
    base = pattern
    retn = base.endswith("-retn")
    if retn:
        base = base[:-5]
    if base.startswith("member-getter-"):
        kind = base[len("member-getter-"):]
        text = f"Member getter ({kind.replace('-', ' ')})."
    elif base.startswith("global-getter-"):
        text = f"Returns a global ({base[len('global-getter-'):].replace('-', ' ')})."
    else:
        text = DESCR.get(pattern) or DESCR.get(base) or (base.replace("-", " ").capitalize() + ".")
    if retn and pattern not in DESCR and not base.startswith("empty"):
        text = text[:-1] + "; pops its stack arguments."
    return text
