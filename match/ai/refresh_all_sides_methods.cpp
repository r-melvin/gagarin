// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x452D40.

#include "refresh_all_sides_methods.h"

// FUNCTION: GAMEMD 0x452D40
//
// Refresh all four sides of every eligible object, then mark it done.
//
// PARTIAL (82.2%, 37/45; mnemonic multiset identical, registers identical).
// The whole body is retail's, in retail's order; the only delta is the order of
// the receiver load against the argument push in the call run. Retail emits
// `MOV ECX,ESI` and then `PUSH imm` for the second, third, fourth and fifth
// calls (the first call is `PUSH 0; MOV ECX,ESI` on both sides); cl 8804 pushes
// first every time. Five transpositions, ten instructions, nothing else.
//
// This is the open "`this`-load / argument-push order in a call run" entry, and
// ten spellings were measured against a labelled control in one compile, all
// 82.2% or worse: the receiver re-derived from the array at each call site
// (8.7%), the four arguments as named locals, one argument variable stepped
// between the calls, the receiver taken as a reference, the first call split
// off from the rest by an intervening declaration, a forced-inline free helper
// taking the receiver (the tenth-batch reshape), the run written as one comma
// expression, a volatile receiver pointer (10.9%), and the run as a stepped
// loop (6.7%). Every 82.2% variant is BYTE-IDENTICAL to the control, which per
// the fifteenth batch is stronger evidence than the percentage: cl's schedule
// here is invariant to the source. Filed with 0x50C8C0, 0x458200, 0x683EB0,
// 0x41C2E0 and 0x40A850, which carry the same residual.
//
// PERMUTER FINDING (negative, and a caveat about the permuter's own score).
// The 0x41C2E0 comma lever was tried first, by hand, on all five calls:
// `(0, obj->FUN_00452DC0(0));` and so on. 82.2%, byte-identical to the
// committed spelling. It still does not transfer, now on a third sibling.
//
// decomp-permuter then ran 121,332 candidates over three runs, each restarted
// from the previous run's best. Base score 470 against a relocation floor of
// 20; best 230, then 200. NEITHER IS A REAL IMPROVEMENT. The 230 candidate
// re-reads the object out of the global array between the third and fifth
// calls, and that spelling scores 47.8% under diff_retail -- far WORSE than the
// committed 82.2% -- while the 200 candidate reaches its score by indexing the
// array at [0] instead of [i], which is not the same program. The base's
// penalty list charged this body one phantom insertion and one phantom deletion
// for the alignment of its four transpositions, and both "improvements" bought
// those 200 points back by changing the instruction COUNT rather than its
// order.
//
// The operational rule this establishes: when the base's penalty list shows
// insertions or deletions that diff_retail does not, the permuter's delta is
// steering on an alignment artifact. Certify intermediate candidates with
// match.sh before believing a trajectory -- not just the final winner.
//
// The global suppressor at 0xA8E7AC is tested inside the loop rather than once
// before it -- retail reloads it per object -- so a value that changes mid-pass
// would take effect immediately. That is why it is not hoisted.
void FUN_00452D40()
{
    int i = 0;

    while (i < DAT_00A8EB50) {
        Obj_00452D40* obj = DAT_00A8EB44[i];

        if (obj != 0 && obj->Owner->At_16BE != 0 && DAT_00A8E7AC == 0
            && obj->At_90 != 0 && obj->At_81 == 0) {
            obj->FUN_00452DC0(0);
            obj->FUN_00452DC0(2);
            obj->FUN_00452DC0(4);
            obj->FUN_00452DC0(6);
            obj->FUN_004533A0(1);
        }

        i++;
    }
}
