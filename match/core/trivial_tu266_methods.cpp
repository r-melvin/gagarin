// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu266_methods.h"

// FUNCTION: GAMEMD 0x759790
// Tail-forwards to another function.
void FUN_00759790(int a1, int a2)
{
    FUN_004A4780(a1 + 0x204, a2);
}

// FUNCTION: GAMEMD 0x759810
// Branching.
int Obj_00759810::FUN_00759810()
{
    if (unknown_200 != 0)
    {
        return unknown_200->unknown_00;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x759830
// Branching.
int Obj_00759830::FUN_00759830(int a1)
{
    if (a1 != -1)
    {
        int t1 = unknown_1DC;
        unknown_1DC = a1;
        return t1;
    }
    return unknown_1DC;
}

// FUNCTION: GAMEMD 0x759E60
// Branching.
void FUN_00759E60(Obj_00759E60* a1, int a2)
{
    if (a1->unknown_514 != 0)
    {
        FUN_007C2C60(a1->unknown_200, a2);
    }
}

// FUNCTION: GAMEMD 0x759E80
// Branching.
void Obj_00759E80::FUN_00759E80()
{
    unknown_200->FUN_007C35C0();
    if (unknown_00 != 0)
    {
        unknown_00->FUN_006C9D20();
    }
}

// FUNCTION: GAMEMD 0x75A400
// Returns zero.
int __cdecl FUN_0075A400()
{
    return 0;
}

// FUNCTION: GAMEMD 0x75A410
// Empty function.
void __cdecl FUN_0075A410()
{
}

// FUNCTION: GAMEMD 0x75A420
// Empty function.
void __cdecl FUN_0075A420()
{
}
