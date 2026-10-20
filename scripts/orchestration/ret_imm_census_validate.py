#!/usr/bin/env python3
# SPDX-Provenance: own-binary-via-Ghidra
#
# Validate scripts/data/ret_imm_census.json against the project's own matched
# functions.  A function in scripts/data/match_manifest.json at status=matched,
# pct=100 has a convention PROVEN correct by a byte match, so it is the oracle:
# the census must agree with it.
#
# Two checks:
#   1. convention compatibility — the census reports the *physical* shape read
#      off the instruction stream; several source spellings can be byte-
#      identical to one shape (batch forty-seven), so the test is whether the
#      census verdict admits the spelling we proved, not string equality.
#   2. ret_imm — the callee-cleanup immediate must equal the stack-argument
#      bytes implied by the proven mangled signature, for every signature whose
#      argument sizes can be derived without guessing.
#
# Usage: ret_imm_census_validate.py <census.json> [match_manifest.json]

import json
import sys

CONV = {"A": "__cdecl", "C": "__pascal", "E": "__thiscall",
        "G": "__stdcall", "I": "__fastcall"}
STATIC = set("CDKLSTOP")
FREE = set("YZ")


def conv_of(sym):
    """Calling convention from an MSVC-mangled name. After the qualified name
    comes an access/storage letter, a cv letter for non-static members only,
    then the convention letter."""
    if not sym.startswith("?"):
        return None
    i = sym.find("@@")
    if i < 0:
        return None
    rest = sym[i + 2:]
    if not rest:
        return None
    L = rest[0]
    if L in FREE or L in STATIC:
        c = rest[1] if len(rest) > 1 else None
    else:
        c = rest[2] if len(rest) > 2 else None
    return CONV.get(c)


# ---- argument stack bytes from the mangled type stream (conservative subset)

SIMPLE = {"X": 0, "D": 4, "E": 4, "F": 4, "G": 4, "H": 4, "I": 4, "J": 4,
          "K": 4, "M": 4, "N": 8, "O": 8}
SIMPLE2 = {"_N": 4, "_J": 8, "_K": 8, "_W": 4, "_D": 4, "_E": 4}


class Bail(Exception):
    pass


def parse_type(s, i, backrefs):
    """Return (size_in_stack_bytes, new_i). Raises Bail on anything whose size
    cannot be derived without guessing."""
    if i >= len(s):
        raise Bail()
    c = s[i]
    if c.isdigit():
        k = int(c)
        if k >= len(backrefs):
            raise Bail()
        return backrefs[k], i + 1
    if c == "_":
        t = s[i:i + 2]
        if t in SIMPLE2:
            return SIMPLE2[t], i + 2
        raise Bail()
    if c in SIMPLE:
        return SIMPLE[c], i + 1
    if c in "PQRS":                      # pointer
        j = skip_pointee(s, i + 1)
        backrefs.append(4)
        return 4, j
    if c in "AB":                        # reference
        j = skip_pointee(s, i + 1)
        backrefs.append(4)
        return 4, j
    if c == "W":                         # enum
        if i + 1 < len(s) and s[i + 1].isdigit():
            j = skip_name(s, i + 2)
            backrefs.append(4)
            return 4, j
        raise Bail()
    raise Bail()                         # V/U/T by value: size unknown


def skip_pointee(s, i):
    """Skip the cv letter and the pointed-to type of a pointer/reference."""
    if i >= len(s):
        raise Bail()
    if s[i] in "ABCD":                   # cv modifier
        i += 1
    else:
        raise Bail()
    if i >= len(s):
        raise Bail()
    c = s[i]
    if c in "VUT":                       # class/struct/union: skip its name
        return skip_name(s, i + 1)
    if c in SIMPLE or c == "_" or c in "PQRS" or c == "W":
        sz, j = parse_type(s, i, [])     # nested; its own backrefs unused here
        return j
    if c == "6":                         # function pointer: bail, too fiddly
        raise Bail()
    if c.isdigit():
        return i + 1
    raise Bail()


def skip_name(s, i):
    """Skip a qualified name: a run of components, each a literal ending in '@'
    or a single back-reference digit, closed by a lone '@'."""
    while True:
        if i >= len(s):
            raise Bail()
        if s[i] == "@":
            return i + 1                 # end of the component list
        if s[i].isdigit():
            i += 1                       # back-referenced component
            continue
        if s[i] == "?":
            raise Bail()                 # template / special component
        j = s.find("@", i)
        if j < 0:
            raise Bail()
        i = j + 1


def nonstatic_member(sym):
    """True for a non-static member function: `this` is a real parameter."""
    i = sym.find("@@")
    if i < 0 or len(sym) <= i + 2:
        return False
    L = sym[i + 2]
    return L not in FREE and L not in STATIC


def arg_bytes(sym):
    """Stack bytes the arguments occupy, or None if not derivable."""
    i = sym.find("@@")
    if i < 0:
        return None
    rest = sym[i + 2:]
    if not rest:
        return None
    L = rest[0]
    k = 2 if (L in FREE or L in STATIC) else 3
    s = rest[k:]
    backrefs = []
    try:
        _, j = parse_type(s, 0, backrefs)     # return type
        total = 0
        while j < len(s):
            if s[j] == "Z":
                break
            if s[j] == "@":
                break
            sz, j = parse_type(s, j, backrefs)
            if sz == 0:                        # X = void argument list
                break
            total += (sz + 3) // 4 * 4
        return total
    except Bail:
        return None


# ---- compatibility: which spellings a physical shape admits

def compatible(shape, spelled):
    if shape == "__thiscall":
        # ECX read, no EDX, RET n. A __thiscall member with n bytes of stack
        # arguments, or a __fastcall (free/static/member) whose only register
        # argument is the ECX one.
        return spelled in ("__thiscall", "__fastcall")
    if shape == "__fastcall":
        # ECX and EDX both read: a __fastcall of some flavour. A plain
        # __thiscall member cannot get a value into EDX before writing it.
        return spelled == "__fastcall"
    if shape == "__stdcall":
        # no register arguments, RET n: __stdcall, __pascal, or a member whose
        # `this` / register argument is never used (RulesClass::Read_* are
        # exactly this).
        return spelled in ("__stdcall", "__pascal", "__thiscall", "__fastcall")
    if shape == "__cdecl":
        # bare RET: caller cleans up, or there is nothing to clean. Any
        # convention with zero stack arguments looks like this.
        return True
    return None                          # excluded kinds are not data points


def main():
    census = json.load(open(sys.argv[1]))
    man_path = (sys.argv[2] if len(sys.argv) > 2
                else "scripts/data/match_manifest.json")
    by = {r["addr"]: r for r in census["functions"]}
    man = json.load(open(man_path))

    tot = ok = 0
    excluded = missing = unparsed = 0
    bad = []
    ret_tot = ret_ok = 0
    ret_bad = []
    from collections import Counter
    shape_counts = Counter()

    for e in man:
        if e.get("status") != "matched" or e.get("pct") != 100:
            continue
        spelled = conv_of(e["sym"])
        if spelled is None:
            unparsed += 1
            continue
        addr = "0x%X" % int(e["addr"], 16)
        r = by.get(addr)
        if r is None:
            missing += 1
            continue
        shape = r["inferred"]
        c = compatible(shape, spelled)
        if c is None:
            excluded += 1
            shape_counts[shape] += 1
            continue
        tot += 1
        if c:
            ok += 1
        else:
            bad.append((addr, e["name"], spelled, shape, r["ret_imm"],
                        r["reads_ecx_before_write"], r["reads_edx_before_write"]))

        # ---- ret_imm cross-check
        ab = arg_bytes(e["sym"])
        if ab is None or not isinstance(r["ret_imm"], int):
            continue
        if spelled == "__cdecl":
            expect = 0
        elif spelled == "__stdcall" or spelled == "__pascal":
            # a __stdcall/__pascal NON-STATIC member still passes `this` on the
            # stack, so the callee cleans four bytes more than the explicit
            # arguments. RA2's COM virtuals (?...@@UAG...) are exactly this.
            expect = ab + (4 if nonstatic_member(e["sym"]) else 0)
        elif spelled == "__thiscall":
            expect = ab
        elif spelled == "__fastcall":
            # first two register-eligible (4-byte) arguments go in ECX, EDX
            expect = None
        else:
            expect = None
        if expect is None:
            continue
        ret_tot += 1
        if r["ret_imm"] == expect:
            ret_ok += 1
        else:
            ret_bad.append((addr, e["name"], r["ret_imm"], expect, e["sym"]))

    print("CONVENTION COMPATIBILITY")
    print("  oracle functions scored : %d" % tot)
    print("  agree                   : %d  (%.2f%%)"
          % (ok, 100.0 * ok / max(tot, 1)))
    print("  disagree                : %d" % len(bad))
    print("  excluded shapes         : %d  %s"
          % (excluded, dict(shape_counts)))
    print("  not present in census   : %d" % missing)
    print("  mangling not parsed     : %d" % unparsed)
    for b in bad[:40]:
        print("   ", b)
    print()
    print("RET_IMM vs SIGNATURE (__cdecl / __stdcall / __thiscall, sizes derivable)")
    print("  scored : %d" % ret_tot)
    print("  agree  : %d  (%.2f%%)" % (ret_ok, 100.0 * ret_ok / max(ret_tot, 1)))
    for b in ret_bad[:40]:
        print("   ", b)


if __name__ == "__main__":
    main()
