// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x407170.

#include "small_misc34_methods.h"

// LOAD-ORDER DELTA (status partial, 89.5% - 17/19). Retail loads the two
// comparands as `MOV EAX,[ESI+8]` then `MOV ECX,[ESI+4]`; we emit them the
// other way round. Two instructions, everything else exact. Hoisting the three
// reads into named locals took this from 63.2% to 89.5% by fixing the *first*
// load's position, but the remaining pair is register assignment rather than
// order - swapping the declarations does not move it, and volatile reads make
// it worse (63.2%) by forcing a load VC6 otherwise folds.
//
// The re-derivation lever that fixed the two SIB deltas was measured here and
// does not reach it. Re-deriving either comparand at the test drops to 63.2%
// (it un-does the hoist that got this to 89.5% in the first place); naming the
// target and re-deriving the current value, swapping the declaration order,
// and re-deriving the flags word instead are all 89.5%; writing the test
// target-first is 84.2%. Six variants, one compile, control included.
//
// Which value reaches the call was swept this pass and is settled: the two are
// equal on the taken arm, so either variable could be the argument, but passing
// `current` costs 5.3 points (84.2%) both with the comparison as written and
// with the declarations in retail's load order, and re-deriving the member at
// the call is 57.9%. So the argument is `target` as written, and the residual
// is purely which of EAX/ECX each of the two loads lands in. Six variants, one
// compile, control included.
//
// FUNCTION: GAMEMD 0x407170
// Clear the armed bit, refresh the 64-bit stamp only when the two counters have
// converged, and store the new rate shifted into the high half. The rate store
// happens on both paths - the JNZ lands on it, not on the return.
void __fastcall FUN_00407170c(Obj_00407170* obj, int rate)
{
    int flags = obj->Flags;
    int current = obj->unknown_08;
    int target = obj->unknown_04;

    obj->Flags = flags & ~1;

    // PERMUTER FINDING (score 0 at candidate 15, base 10): an inert `if (1) {}`
    // placed between the flags store and the comparison is what swaps the two
    // comparand loads into retail's EAX/ECX assignment. A bare `{ }` block does
    // nothing (89.5%) and the same `if (1) {}` above the loads does nothing
    // (89.5%) - it is the basic-block boundary at exactly this point that the
    // register allocator responds to. Found by decomp-permuter; see
    // docs/permuter_workflow.md.
    if (1) {
    }

    if (current == target) {
        *(__int64*)&obj->unknown_18 = FUN_004093B0(target);
    }

    obj->unknown_08 = rate << 16;
}
