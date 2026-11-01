// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu266_b_methods.h"

// FUNCTION: GAMEMD 0x7598D0
// Branching.
void Obj_007598D0::FUN_007598D0(int a1)
{
    if (a1 != unknown_504)
    {
        int c0 = FUN_007C30D0(unknown_200, a1, 0);
        if (c0 != -6)
        {
            unknown_504 = a1;
        }
    }
}
