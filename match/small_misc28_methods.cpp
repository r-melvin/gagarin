// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc28_methods.h"

// FUNCTION: GAMEMD 0x407F40
// Two gates before the lock is even taken, and the worker pointer is re-read
// after entering rather than reused from the test.
void Obj_00407F40::FUN_00407F40()
{
    if (unknown_88 != 0) {
        return;
    }

    if (unknown_14 == 0) {
        return;
    }

    EnterCriticalSection(&DAT_0087E7F8);

    unknown_14->FUN_004025B0();

    LeaveCriticalSection(&DAT_0087E7F8);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E7F8
CRITICAL_SECTION_ DAT_0087E7F8;
// END defined globals
