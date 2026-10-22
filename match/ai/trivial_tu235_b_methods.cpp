// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu235_b_methods.h"

// FUNCTION: GAMEMD 0x6EDA90
// Calls other functions.
void Obj_006EDA90::FUN_006EDA90(Arg1_006EDA90* a1, int a2)
{
    DAT_00A8B230->FUN_00689670(a1->unknown_04, 1);
    unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDAC0
// Calls other functions.
void Obj_006EDAC0::FUN_006EDAC0(Arg1_006EDAC0* a1, int a2)
{
    DAT_00A8B230->FUN_00689670(a1->unknown_04, 0);
    unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDAF0
// Calls other functions.
void Obj_006EDAF0::FUN_006EDAF0(Arg1_006EDAF0* a1, int a2)
{
    DAT_00A8B230->FUN_00689910(a1->unknown_04, 1);
    unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDB20
// Calls other functions.
void Obj_006EDB20::FUN_006EDB20(Arg1_006EDB20* a1, int a2)
{
    DAT_00A8B230->FUN_00689910(a1->unknown_04, 0);
    unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDE10
// Calls other functions.
void Obj_006EDE10::FUN_006EDE10(Arg1_006EDE10* a1, int a2)
{
    unknown_28->FUN_006915A0(a1->unknown_04 - 2);
    unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDE60
// Calls other functions.
void FUN_006EDE60(Obj_006EDE60* a1, int a2, int a3, int a4)
{
    FUN_004FCBD0(DAT_00A83D4C, a2, 0);
    a1->unknown_80 = 1;
}

// FUNCTION: GAMEMD 0x6EDEC0
// Calls other functions.
void FUN_006EDEC0(Obj_006EDEC0* a1, int a2, Arg1_006EDEC0* a3, int a4)
{
    FUN_005BF260(a3->unknown_04, -1, 1, 1, 1);
    a1->unknown_80 = 1;
}
