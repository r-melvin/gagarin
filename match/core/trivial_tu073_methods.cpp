// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu073_methods.h"

// FUNCTION: GAMEMD 0x4C1E50
// Branching.
void Obj_004C1E50::FUN_004C1E50()
{
    if (unknown_20 != 0)
    {
        unknown_20->unknown_6DC = 0;
        unknown_20 = 0;
    }
}

// FUNCTION: GAMEMD 0x4C2C30
// Returns its receiver.
Obj_004C2C30* Obj_004C2C30::FUN_004C2C30()
{
    return this;
}
