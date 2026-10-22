// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at 0x42D490.

#include "adjacent_cell_methods.h"

// FUNCTION: GAMEMD 0x42D490
//
// Step `src` one square in direction `dir`. Direction 8 is not a step but a
// lookup: the singleton resolves the cell to an id, and the slot that id names
// supplies the pair. An unresolved cell yields the zero pair.
//
// The X half is written as src + step and the Y half as step + src — the
// asymmetry is retail's, and the operand order is what selects the two ADD
// forms it emits.
//
// PERMUTER FINDING (78.4% -> 91.9% -> 100%, two runs of ~44k candidates each,
// score 300 -> 55 -> 20 = the five-relocation floor). Minimised to TWO
// constructs, both required:
//   * the step-table entry is bound to a `Pair*` and both halves read through
//     it, rather than subscripting the table twice (worth 78.4 -> 91.9);
//   * the slot pair is copied into a named local before the store to `*dest`,
//     rather than assigned straight through (worth 91.9 -> 100).
// A third construct the permuter also produced - the zero arm's `*dest` store
// made through a `Pair* outp = dest` alias - is NOT load-bearing and was
// dropped. Note the first run's best (55) was a local optimum; restarting the
// search from it is what found the second construct.
Pair_0042D490* FUN_0042D490(Pair_0042D490* dest, Pair_0042D490* src,
                            int dir)
{
    Pair_0042D490 out;

    if (dir == 8) {
        int id = DAT_0087F7E8.FUN_005657A0(src)->At_116;

        if (id != -1) {
            Pair_0042D490 slot = DAT_008B413C[id]->At_28;
            *dest = slot;
            return dest;
        }

        out.X = 0;
        out.Y = 0;

        *dest = out;
        return dest;
    }

    Pair_0042D490* step = &DAT_0089F688[dir];

    out.X = (short)(src->X + (*step).X);
    out.Y = (short)((*step).Y + src->Y);
    *dest = out;
    return dest;
}
