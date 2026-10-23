// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc19_methods.h"

// FUNCTION: GAMEMD 0x41C460
// Both components zero means unset; the first is then given 100.0 and the
// second left alone.
void Pair2d::FUN_0041C460()
{
    if (x == 0.0 && y == 0.0) {
        x = 100.0;
    }
}

// FUNCTION: GAMEMD 0x433C00
void Obj_00433C00::FUN_00433C00()
{
    if (unknown_18) {
        FUN_007C8B3D(unknown_18);
    }

    if (unknown_1C) {
        FUN_007C8B3D(unknown_1C);
    }

    FUN_007C8B3D(this);
}

