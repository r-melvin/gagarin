// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu155_b_methods.h"

// FUNCTION: GAMEMD 0x5D5820
// Branching.
Obj_005D5820* Obj_005D5820::FUN_005D5820(int a1, int a2)
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
    int c0 = FUN_00407000();
    if (c0 != 0)
    {
        int c1 = FUN_007D5408(a1);
        unknown_00 = c1;
        return this;
    }
    return this;
}
