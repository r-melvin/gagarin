// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc14_methods.h"

// FUNCTION: GAMEMD 0x4068F0
// The guard tests the *decremented* count as its own value, which is what lets
// VC6 branch on the flags DEC already set (`DEC EAX; JS`). Written as a
// `for (i = count - 1; i >= 0; i--)` the compiler re-tests with `TEST EAX,EAX;
// JL` and every instruction after shifts by one.
void __stdcall FUN_004068F0(char* base, int stride, int count, ElemFn fn)
{
    if (--count < 0) {
        return;
    }

    for (int i = count; i >= 0; i--) {
        fn(base);

        base += stride;
    }
}

// FUNCTION: GAMEMD 0x411510
// The first two fields come back zeroed; only the last two carry values.
Quad4i Obj_00411510::FUN_00411510() const
{
    Quad4i result;

    result.a = 0;
    result.b = 0;
    result.c = unknown_04;
    result.d = unknown_08;

    return result;
}

// FUNCTION: GAMEMD 0x431060
// Clear bit 1 on every live slot - eight groups of three, walked as one
// pointer. The whole sweep is skipped unless the field at +0x60 is set.
void Obj_00431060::FUN_00431060()
{
    if (unknown_60 == 0) {
        return;
    }

    Flagged_00431060** slot = Slots;

    for (int group = 8; group != 0; group--) {
        for (int i = 3; i != 0; i--) {
            if (*slot) {
                (*slot)->at0C &= ~2;
            }

            slot++;
        }
    }
}
