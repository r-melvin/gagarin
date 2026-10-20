// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x63AB00.

#include <stdlib.h>
#include "planning_manager_rbutton_methods.h"

// FUNCTION: GAMEMD 0x63AB00
//
// Right-button release in planning mode. The drag flag is always cleared;
// then, if planning mode is on, nothing at 0xA8ECC8 is outstanding, and a
// token is pending, a release within 3 pixels of the anchor on both axes
// drops the token.
void __stdcall FUN_0063AB00(int x, int y)
{
    DAT_00AC4CB0 = false;

    if (DAT_00AC4CF4
        && DAT_00A8ECC8 <= 0
        && DAT_00AC4BF0 != 0
        && abs(x - DAT_00AC4C68) <= 3
        && abs(y - DAT_00AC4C6C) <= 3) {
        DAT_00AC4BF0 = 0;
    }
}
