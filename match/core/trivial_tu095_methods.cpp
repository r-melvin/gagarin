// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu095_methods.h"

// FUNCTION: GAMEMD 0x4F7850
// Stores several members.
Obj_004F7850* Obj_004F7850::FUN_004F7850()
{
    unknown_00 = 0;
    unknown_04 = 1;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = -1;
    return this;
}

// FUNCTION: GAMEMD 0x506B70
// Empty function.
void __cdecl FUN_00506B70()
{
}

// FUNCTION: GAMEMD 0x506B80
// Empty function.
void __cdecl FUN_00506B80()
{
}

// FUNCTION: GAMEMD 0x509CC0
// Empty function that pops its stack arguments.
void __stdcall FUN_00509CC0(int a1)
{
}

// FUNCTION: GAMEMD 0x50C160
// Fp getter.
float Obj_0050C160::FUN_0050C160() const
{
    return unknown_34->unknown_148;
}

// FUNCTION: GAMEMD 0x50DA40
// Stores its argument in a member; pops its stack arguments.
void Obj_0050DA40::FUN_0050DA40(int a1)
{
    unknown_54F8 = a1;
}

// FUNCTION: GAMEMD 0x50E430
// Stores several members; pops its stack arguments.
void Obj_0050E430::FUN_0050E430(unsigned char a1, unsigned char a2, unsigned char a3)
{
    unknown_00 = a1;
    unknown_01 = a2;
    unknown_02 = a3;
}

// FUNCTION: GAMEMD 0x50E450
// Stores several members; pops its stack arguments.
Obj_0050E450* Obj_0050E450::FUN_0050E450(int a1, Arg2_0050E450* a2)
{
    unknown_00 = a1;
    unknown_04 = a2->unknown_00;
    unknown_08 = 0;
    unknown_0C = 0;
    return this;
}

// FUNCTION: GAMEMD 0x50FF40
// Empty function.
void __cdecl FUN_0050FF40()
{
}
