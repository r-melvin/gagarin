// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu211_methods.h"

// FUNCTION: GAMEMD 0x6A8160
// Calls other functions.
int __stdcall FUN_006A8160(int a1)
{
    int c0 = FUN_005B40B0(DAT_0083F92C, 0);
    DAT_00B07BC0 = c0;
    return c0;
}

// FUNCTION: GAMEMD 0x6A8B10
// Calls other functions.
void FUN_006A8B10(Obj_006A8B10* a1, int a2)
{
    a1->unknown_3C = 1;
    FUN_004F42F0(DAT_0087F7E8, a2, 0);
}

// FUNCTION: GAMEMD 0x6ABA20
// Branching.
int Obj_006ABA20::FUN_006ABA20()
{
    return unknown_34 != 0 && DAT_00A8ED9C == 0;
}

// FUNCTION: GAMEMD 0x6ABAC0
// Returns a comparison result.
bool Obj_006ABAC0::FUN_006ABAC0() const
{
    return unknown_54 > 0;
}

// FUNCTION: GAMEMD 0x6ABC40
// Branching.
int __cdecl FUN_006ABC40()
{
    if (DAT_00A8B238 != 0)
    {
        DAT_00A8EDA0 = 8;
    }
    return DAT_00A8B238;
}
