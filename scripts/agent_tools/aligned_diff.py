#!/usr/bin/env python3
"""aligned_diff.py: score a compiled function against retail by instruction alignment.

usage:
  aligned_diff.py --obj build-vc6/foo.obj --sym '?Bar@Foo@@QAEXXZ' --addr 0x557230 --len 0x14d [--hunks] [--ctx N]

Prints the official positional score (same rule as scripts/vc6/diff_retail.py)
and an aligned score: the LCS of the two instruction streams under the same
equality rule (identical bytes, or same mnemonic and registers with every
differing byte inside a COFF relocation field). Both are % of
max(retail, compiled) instruction count. A high aligned score with a low
positional one means an insertion/deletion shifted everything after it.
--hunks lists each mismatching run (R = retail, C = compiled) with N lines of
matching context (default 1).

The retail bytes come from the pinned PE at $GAMEMD_BINARY via
diff_retail's decoder; the compiled side is the COFF symbol's own section.
This is an exploration metric. The positional score is still what counts.
"""
import argparse, os, sys

# GAMEMD_BINARY must name the user's retail image (no default).
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'vc6'))
import diff_retail as d


def load(obj, sym, addr, length):
    retail = d.raw_x86_insns(d.ghidra_bytes(addr, length), addr)
    comp, relocs = d.objdump_insns(obj, sym)
    # Same trimming as diff_retail: alignment padding, then switch tables past the span.
    while comp and (comp[-1][2] == 'nop' or (comp[-1][2] == 'lea' and '+0x0]' in comp[-1][3]
                    and d.regs(comp[-1][3])[:1] == d.regs(comp[-1][3])[1:2])):
        comp.pop()
    inside = [c for c in comp if c[0] < length]
    if len(inside) < len(comp) and inside and inside[-1][2] in ('ret', 'jmp'):
        comp = inside
    return retail, comp, relocs


def same(r, c, relocs):
    return r[1] == c[1] or (r[2] == c[2] and d.regs(r[3]) == d.regs(c[3])
                            and d.reloc_normalised_equal(r[1], c[1], c[0], relocs))


def lcs_pairs(retail, comp, relocs):
    """Matched (i, j) index pairs of a longest common subsequence."""
    n, m = len(retail), len(comp)
    eq = [[same(retail[i], comp[j], relocs) for j in range(m)] for i in range(n)]
    L = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        for j in range(m - 1, -1, -1):
            L[i][j] = L[i + 1][j + 1] + 1 if eq[i][j] else max(L[i + 1][j], L[i][j + 1])
    pairs, i, j = [], 0, 0
    while i < n and j < m:
        if eq[i][j] and L[i][j] == L[i + 1][j + 1] + 1:
            pairs.append((i, j)); i += 1; j += 1
        elif L[i + 1][j] >= L[i][j + 1]:
            i += 1
        else:
            j += 1
    return pairs


def fmt(tag, insn):
    return '  %s %04x  %s %s' % (tag, insn[0], insn[2], insn[3])


def print_hunks(retail, comp, pairs, ctx):
    bounds = pairs + [(len(retail), len(comp))]
    pi, pj, k = 0, 0, 0
    for (i, j) in bounds:
        if i > pi or j > pj:
            k += 1
            print('--- hunk %d: retail[%d:%d] compiled[%d:%d]' % (k, pi, i, pj, j))
            for x in range(max(0, pi - ctx), pi):
                print(fmt('=', retail[x]))
            for x in range(pi, i):
                print(fmt('R', retail[x]))
            for x in range(pj, j):
                print(fmt('C', comp[x]))
            for x in range(i, min(len(retail), i + ctx)):
                print(fmt('=', retail[x]))
        pi, pj = i + 1, j + 1
    return k


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--obj', required=True)
    ap.add_argument('--sym', required=True)
    ap.add_argument('--addr', required=True)
    ap.add_argument('--len', required=True)
    ap.add_argument('--hunks', action='store_true')
    ap.add_argument('--ctx', type=int, default=1)
    a = ap.parse_args()
    retail, comp, relocs = load(a.obj, a.sym, int(a.addr, 16), int(a.len, 16))
    n = max(len(retail), len(comp))
    pos = sum(1 for r, c in zip(retail, comp) if same(r, c, relocs))
    pairs = lcs_pairs(retail, comp, relocs)
    nh = print_hunks(retail, comp, pairs, a.ctx) if a.hunks else None
    print('positional %.1f%%  aligned %.1f%%  (%d/%d aligned; retail %d, compiled %d insns%s)'
          % (100.0 * pos / n, 100.0 * len(pairs) / n, len(pairs), n, len(retail), len(comp),
             '' if nh is None else '; %d hunks' % nh))


if __name__ == '__main__':
    main()
