// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x456FB0.

#include "small_misc53_methods.h"

// FUNCTION: GAMEMD 0x456FB0
//
// BLOCK-ORDER DELTA (status partial, 76.2% - 32/42). Everything through the
// branchless cast and the holder comparison is exact. What is left is which of
// the two tails VC6 lays down first: retail puts the override call at 0x457002
// and the plain return at 0x45700F, and we emit them the other way round, which
// inverts the last two branches with them. Four layouts were tried - the
// override as the last statement, as an `else`, reached by `goto` with the
// plain return labelled after it, and with both guards inverted - and VC6 keeps
// the plain return first every time. The instruction stream is otherwise
// identical.
int Obj_00456FB0::FUN_00456FB0(int value)
{
    int answer = vt_464(value);

    if (!vt_160()) {
        // Positive guard: retail's `JZ` at 0x456FDB jumps forward to the plain
        // return, so the holder-present case is the fall-through.
        if (Holder == 0) {
            goto plain;
        }

        // The null check is a real branch and only the type test is branchless,
        // so the two are written as separate constructs. Folded into one `&&`
        // VC6 branches on the type test as well. The zero arm is the
        // fall-through, which is why it is written as `this == 0` first.
        Obj_00456FB0* typed;

        if (this == 0) {
            typed = 0;
        } else {
            typed = (WhatAmI() == 6) ? this : 0;
        }

        if (Holder->Current != typed) {
            goto plain;
        }
    }

    // The override takes the *answer*, not the original argument: retail pushes
    // EDI, which `MOV EDI,EAX` loaded from the first call's result. It is
    // written before the plain return so VC6 lays its block out first, matching
    // retail's 0x457002-then-0x45700F order.
    return FUN_0070E360(answer);

plain:
    return answer;
}
