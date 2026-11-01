// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x412A40.

#include "grid_offset_methods.h"

#define GG_MAX(a, b) ((a) < (b) ? (b) : (a))
#define GG_MIN(a, b) ((a) > (b) ? (b) : (a))

// FUNCTION: GAMEMD 0x412A40
//
// Offset a cell index within a 20x20 grid, clamping each axis to the grid
// rather than letting it wrap. Splitting the index and recombining it is what
// keeps a step off the right edge from landing on the next row's left edge.
//
// PARTIAL (55.6%, 25/45). The clamp shape is solved and byte-exact; what is
// left is register naming.
//
// The clamp is the interesting part. Retail tests the sign, jumps into a
// branchless low clamp (`XOR`/`TEST`/`SETL`/`DEC`/`AND`, which computes
// `v >= 0 ? v : 0`), and if the sign test fails compares against 0x13 and lands
// on that *same* block when it is in range. So one copy of the low clamp serves
// both the negative case (where it yields 0) and the in-range case (where it
// yields v), and the sign test in front of it is redundant with the compare.
// That is the codegen for an explicit disjunction — `(v < 0 || v <= 0x13)`
// selecting the low clamp, else 0x13 — and nothing else reproduces it:
// `if (v < 0) v = 0; else if (v > 0x13) v = 0x13;`, a nested ternary either way
// round, a min-of-max with duplicated argument, and a guarded `&&` all score
// 2.2% or 13.3%. Writing it this way is also what brings back retail's separate
// `TEST` before the `SETL`: the block has two predecessors, so the flags from
// the addition are not live there.
//
// The residual is that retail holds `cell` in ECX with the divisor in ESI and
// forms the sum with `LEA EAX,[ECX+ESI]`, while VC6 swaps those two registers
// and reuses the remainder's register for the sum with `ADD`. Same instruction
// count, same operands. Swapping the addition's operand order, naming the
// stride, and hoisting both divisions were all tried; the first two change
// nothing and the third makes VC6 emit the magic-multiply before the `IDIV`
// (2.2%). Only the interleaved order — remainder, sum, quotient — puts the two
// divisions where retail has them.
//
// The two divisions are not shared. The remainder comes from a real `IDIV` and
// the quotient from the 0x66666667 magic-multiply, because each is its own
// expression and VC6 costs them separately.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (a single prologue
// ESI on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
int __stdcall FUN_00412A40(int cell, int dx, int dy)
{
    int column = cell % 0x14;
    int x = dx + column;
    int row = cell / 0x14;
    x = (x < 0 || x <= 0x13) ? GG_MAX(x, 0) : 0x13;

    int y = dy + row;
    y = (y < 0 || y <= 0x13) ? GG_MAX(y, 0) : 0x13;

    return x + y * 0x14;
}
