// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu228_methods.h"

// FUNCTION: GAMEMD 0x6CFDF0
// Branching.
int FUN_006CFDF0(int a1)
{
    return a1 >= DAT_00B0CC20 && a1 <= DAT_00B0CD28;
}

// FUNCTION: GAMEMD 0x6CFE10
// Returns a computed value.
int FUN_006CFE10(int a1)
{
    return (a1 - DAT_00B0CC20) + 1;
}

// FUNCTION: GAMEMD 0x6D0E50
// Empty function.
void __cdecl FUN_006D0E50()
{
}

// FUNCTION: GAMEMD 0x6D0FB0
// Stores several members; pops its stack arguments.
void FUN_006D0FB0(Obj_006D0FB0* a1, int a2, int a3)
{
    a1->unknown_24 = a2;
    a1->unknown_50 = DAT_0087F6CC;
    a1->unknown_20 = a3;
    a1->unknown_2D = 0;
    a1->unknown_30 = 0;
}

// FUNCTION: GAMEMD 0x6D15F0
// Calls other functions.
void Obj_006D15F0::FUN_006D15F0()
{
    vf_13(DAT_00B0CC40);
    DAT_00887368->FUN_00724730(0xF1);
}
