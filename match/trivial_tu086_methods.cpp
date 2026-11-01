// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu086_methods.h"

// FUNCTION: GAMEMD 0x4D94A0
// Stores its argument in a member; pops its stack arguments. Vtable slot 287 of FootClass (RTTI) and 3 derived vtable(s).
void Obj_004D94A0::FUN_004D94A0(int a1)
{
    unknown_5A0 = a1;
}

// FUNCTION: GAMEMD 0x4D9C00
// Returns zero. Vtable slot 329 of FootClass (RTTI) and 3 derived vtable(s).
int Obj_004D9C00::FUN_004D9C00() const
{
    return 0;
}

// FUNCTION: GAMEMD 0x4DA020
// Stores its argument in a member; pops its stack arguments.
Arg1_004DA020* __stdcall FUN_004DA020(Arg1_004DA020* a1, Arg2_004DA020* a2)
{
    a1->unknown_00 = a2->unknown_00;
    return a1;
}

// FUNCTION: GAMEMD 0x4DA2A0
// Calls other functions.
bool Obj_004DA2A0::FUN_004DA2A0()
{
    return (vf_97() == 7) ? true : false;
}

// FUNCTION: GAMEMD 0x4DBA30
// Empty function. Vtable slot 338 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_004DBA30::FUN_004DBA30()
{
}

// FUNCTION: GAMEMD 0x4DBA40
// Empty function. Vtable slot 339 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_004DBA40::FUN_004DBA40()
{
}

// FUNCTION: GAMEMD 0x4DDC40
// Branching. Vtable slot 47 of FootClass (RTTI) and 3 derived vtable(s).
char Obj_004DDC40::FUN_004DDC40(int a1)
{
    if (unknown_684 >= 0)
    {
        return 0;
    }
    return FUN_005F6A70(a1);
}

// FUNCTION: GAMEMD 0x4DE750
// Empty function that pops its stack arguments. Vtable slot 309 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_004DE750::FUN_004DE750(int a1)
{
}

// FUNCTION: GAMEMD 0x4DE760
// Empty function that pops its stack arguments. Vtable slot 310 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_004DE760::FUN_004DE760(int a1)
{
}

// FUNCTION: GAMEMD 0x4DF1A0
// Stores several members. Vtable slot 298 of FootClass (RTTI) and 3 derived vtable(s).
void Obj_004DF1A0::FUN_004DF1A0()
{
    unknown_5C4 = -1;
    unknown_5C8 = 0;
    unknown_5CC = 0;
    unknown_5D1 = 0;
}

// FUNCTION: GAMEMD 0x4DF1C0
// Returns a comparison result. Vtable slot 299 of FootClass (RTTI) and 3 derived vtable(s).
bool Obj_004DF1C0::FUN_004DF1C0() const
{
    return unknown_5C4 != -1;
}

// FUNCTION: GAMEMD 0x4DF1D0
// Member getter (byte). Vtable slot 300 of FootClass (RTTI) and 3 derived vtable(s).
unsigned char Obj_004DF1D0::FUN_004DF1D0() const
{
    return unknown_5D1;
}

// FUNCTION: GAMEMD 0x4DF1E0
// Member getter (dword). Vtable slot 301 of FootClass (RTTI) and 3 derived vtable(s).
int Obj_004DF1E0::FUN_004DF1E0() const
{
    return unknown_5C4;
}

// FUNCTION: GAMEMD 0x4DF310
// Returns a comparison result. Vtable slot 305 of FootClass (RTTI) and 3 derived vtable(s).
bool Obj_004DF310::FUN_004DF310() const
{
    return unknown_5C4 == 0x1D;
}

// FUNCTION: GAMEMD 0x4DFA50
// Branching. Vtable slot 78 of FootClass (RTTI) and 3 derived vtable(s).
unsigned char FUN_004DFA50(Obj_004DFA50* a1, int a2)
{
    if (a1->unknown_6AD != 0)
    {
        return 0;
    }
    return FUN_005F6C30(a1, a2);
}

// FUNCTION: GAMEMD 0x4E0C30
// Empty function.
void __cdecl FUN_004E0C30()
{
}
