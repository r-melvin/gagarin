// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu140_methods.h"

// FUNCTION: GAMEMD 0x5BE940
// Branching.
void FUN_005BE940(int a1, int a2)
{
    int t1 = DAT_00ABF294;
    if (t1 != 0)
    {
        FUN_0069E500(t1, a2);
        FUN_007C8B3D(t1);
        DAT_00ABF2DC = 0;
        DAT_00ABF294 = 0;
    }
    DAT_00ABF294 = 0;
}
