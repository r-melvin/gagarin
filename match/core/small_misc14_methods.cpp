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

