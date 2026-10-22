// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu235_methods.h"

// FUNCTION: GAMEMD 0x6EDE40
// Calls other functions.
void FUN_006EDE40(Obj_006EDE40* a1, int a2, int a3, int a4)
{
    FUN_004FC9E0(DAT_00A83D4C, a2, 0);
    a1->unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDE80
// Stores its argument in a member; pops its stack arguments.
void Obj_006EDE80::FUN_006EDE80(int a1, int a2)
{
    unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDEF0
// Calls other functions.
void FUN_006EDEF0(Obj_006EDEF0* a1, int a2, Arg1_006EDEF0* a3, int a4)
{
    FUN_00720B20(DAT_00A83D10, a2, a3->unknown_04);
    a1->unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDF90
// Stores several members; pops its stack arguments.
void Obj_006EDF90::FUN_006EDF90(int a1, int a2)
{
    unknown_2C->unknown_1EE = true;
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EDFB0
// Stores several members; pops its stack arguments.
void Obj_006EDFB0::FUN_006EDFB0(int a1, int a2)
{
    unknown_2C->unknown_250 = 4;
    unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EE1B0
// Calls other functions.
void FUN_006EE1B0(Obj_006EE1B0* a1, int a2, int a3, int a4)
{
    FUN_00577BB0(DAT_0087F7E8, a2, 0);
    a1->unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EE1D0
// Calls other functions.
void FUN_006EE1D0(Obj_006EE1D0* a1, int a2, int a3, int a4)
{
    FUN_00577F30(DAT_0087F7E8, a2, 0);
    a1->unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6F0430
// Returns a constant. Vtable slot 12 of TeamClass (RTTI).
int Obj_006F0430::FUN_006F0430() const
{
    return 0xA0;
}

// FUNCTION: GAMEMD 0x6F0440
// Returns a constant. Vtable slot 11 of TeamClass (RTTI).
int Obj_006F0440::FUN_006F0440() const
{
    return 0x22;
}
