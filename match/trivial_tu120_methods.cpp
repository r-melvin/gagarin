// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu120_methods.h"

// FUNCTION: GAMEMD 0x556B30
// Branching.
void Obj_00556B30::FUN_00556B30()
{
    if (unknown_04 != 0)
    {
        unknown_04->unknown_A8 = 0;
        unknown_04 = 0;
    }
}
