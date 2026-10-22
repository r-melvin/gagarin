// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu200_methods.h"

// FUNCTION: GAMEMD 0x67FDC0
// Empty function.
void __cdecl FUN_0067FDC0()
{
}

// FUNCTION: GAMEMD 0x681070
// Member getter (dword).
int Obj_00681070::FUN_00681070() const
{
    return unknown_04;
}

// FUNCTION: GAMEMD 0x6810A0
// Calls other functions.
void Obj_006810A0::FUN_006810A0(int a1)
{
    unknown_106 = 0;
    FUN_007CA422(&unknown_08, a1, 0x7F);
}

// FUNCTION: GAMEMD 0x681180
// Returns the address of a member.
int* Obj_00681180::FUN_00681180()
{
    return &unknown_190;
}

// FUNCTION: GAMEMD 0x681190
// Calls other functions.
void Obj_00681190::FUN_00681190(int a1)
{
    unknown_2D3 = 0;
    FUN_007C91D0(&unknown_294, a1, 0x3F);
}

// FUNCTION: GAMEMD 0x6811F0
// Returns the address of a member.
int* Obj_006811F0::FUN_006811F0()
{
    return &unknown_2D4;
}

// FUNCTION: GAMEMD 0x681220
// Stores several members; pops its stack arguments.
Arg1_00681220* Obj_00681220::FUN_00681220(Arg1_00681220* a1)
{
    a1->unknown_00 = unknown_3D8;
    a1->unknown_04 = unknown_3DC;
    return a1;
}

// FUNCTION: GAMEMD 0x681260
// Stores several members; pops its stack arguments.
Arg1_00681260* Obj_00681260::FUN_00681260(Arg1_00681260* a1)
{
    a1->unknown_00 = unknown_3E0;
    a1->unknown_04 = unknown_3E4;
    return a1;
}

// FUNCTION: GAMEMD 0x6812A0
// Stores several members; pops its stack arguments.
Arg1_006812A0* Obj_006812A0::FUN_006812A0(Arg1_006812A0* a1)
{
    a1->unknown_00 = unknown_3E8;
    a1->unknown_04 = unknown_3EC;
    return a1;
}
