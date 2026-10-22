// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu186_methods.h"

// FUNCTION: GAMEMD 0x646CE0
// Branching.
void Obj_00646CE0::FUN_00646CE0()
{
    if (unknown_334 != 0)
    {
        FUN_007C8B3D(unknown_334);
    }
}

// FUNCTION: GAMEMD 0x646D00
// Stores several members.
Obj_00646D00* Obj_00646D00::FUN_00646D00()
{
    unknown_00 = -1;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    return this;
}

// FUNCTION: GAMEMD 0x646D50
// Branching.
void __cdecl FUN_00646D50()
{
    if (DAT_00A8B238 == 4)
    {
        DAT_00A8E9C0.FUN_00543090();
    }
}

// FUNCTION: GAMEMD 0x646DB0
// Empty function.
void __cdecl FUN_00646DB0()
{
}

// FUNCTION: GAMEMD 0x652100
// Empty function.
void __cdecl FUN_00652100()
{
}

// FUNCTION: GAMEMD 0x652540
// Branching.
int Obj_00652540::FUN_00652540()
{
    if (unknown_00 != 0)
    {
        unknown_04 = (unknown_04 + 1) & 0x7F;
        unknown_00--;
    }
    return unknown_00;
}
