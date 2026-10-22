// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu177_c_methods.h"

// FUNCTION: GAMEMD 0x631EE0
// Branching.
unsigned char Obj_00631EE0::FUN_00631EE0(int a1)
{
    unknown_38 -= a1;
    if (unknown_38 <= 0)
    {
        unknown_38 = 0;
        return 1;
    }
    return 0;
}
