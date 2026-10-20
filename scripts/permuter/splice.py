#!/usr/bin/env python3
"""splice.py — turn a permuted C function into the real VC6 C++ translation unit.

decomp-permuter parses and rewrites *C* with pycparser; our match targets are
MSVC C++ member functions.  The bridge is a shim: the run directory holds a
`shim.cpp.in` containing the real C++ declaration of the target function with a
`@BODY@` placeholder, and `base.c` holds the same body written as a plain C
function over explicit pointers.  This script lifts the body out of the permuted
C and drops it into the shim, so the permuter only ever sees legal C while cl
only ever sees the real C++ signature.

Usage: splice.py <permuted.c> <shim.cpp.in> <func-name> <out.cpp>
"""
import sys


def extract_body(src, func):
    i = src.find(func)
    while i != -1:
        j = src.find("{", i)
        k = src.find(";", i)
        # A prototype ends in ';' before any '{' — skip it.
        if j != -1 and (k == -1 or k > j):
            depth = 0
            for p in range(j, len(src)):
                if src[p] == "{":
                    depth += 1
                elif src[p] == "}":
                    depth -= 1
                    if depth == 0:
                        return src[j + 1:p]
        i = src.find(func, i + 1)
    raise SystemExit(f"splice: no definition of {func} found")


def main():
    perm_c, shim, func, out = sys.argv[1:5]
    body = extract_body(open(perm_c).read(), func)
    tmpl = open(shim).read()
    if "@BODY@" not in tmpl:
        raise SystemExit("splice: shim has no @BODY@ placeholder")
    open(out, "w").write(tmpl.replace("@BODY@", body))


if __name__ == "__main__":
    main()
