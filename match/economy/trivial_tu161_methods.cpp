// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu161_methods.h"

// FUNCTION: GAMEMD 0x5E2F60
// Calls other functions.
void Obj_005E2F60::FUN_005E2F60()
{
    int c0 = GetDlgItem(this, 0x5A8);
    SendMessageA(c0, 0x4B2, 0, DAT_00A8B322);
}

// FUNCTION: GAMEMD 0x5E3700
// Branching.
int FUN_005E3700(Obj_005E3700* a1, int a2)
{
    DAT_00A8DAB0 = 0;
    if (DAT_00AC116C != 0)
    {
        return FUN_007A27D0(a1, a2);
    }
    return FUN_005E23A0(a1, a2);
}

// FUNCTION: GAMEMD 0x5EE190
// Calls other functions.
int __cdecl FUN_005EE190()
{
    int c0 = DAT_008870C0.FUN_005276D0(DAT_0082642C, DAT_00831DA4, 0);
    DAT_00AC10C8 = c0;
    return c0;
}
