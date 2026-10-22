// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu180_b_methods.h"

// FUNCTION: GAMEMD 0x63D540
// Branching.
int FUN_0063D540(Obj_0063D540* a1, int a2)
{
    int t1 = a1->unknown_0C;
    if (t1 == 0xB)
    {
        return FUN_00731CE0(a1, a2);
    }
    if (t1 == 0x1D)
    {
        return FUN_00731CD0(a1, a2);
    }
    return -1;
}
