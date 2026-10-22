// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu258_methods.h"

// FUNCTION: GAMEMD 0x7393B0
// Empty function.
void __cdecl FUN_007393B0()
{
}

// FUNCTION: GAMEMD 0x740E50
// Tail-forwards to another function. Vtable slot 174 of UnitClass (RTTI).
void FUN_00740E50(Obj_00740E50* a1, int a2)
{
    FUN_00708C30(a1, a2);
}

// FUNCTION: GAMEMD 0x740EE0
// Tail-forwards to another function. Vtable slot 195 of UnitClass (RTTI).
void FUN_00740EE0(Obj_00740EE0* a1, int a2)
{
    FUN_00707D20(a1, a2);
}

// FUNCTION: GAMEMD 0x741490
// Member getter (dword). Vtable slot 34 of UnitClass (RTTI).
int Obj_00741490::FUN_00741490() const
{
    return unknown_6C4;
}

// FUNCTION: GAMEMD 0x7447A0
// Tail-forwards to another function. Vtable slot 132 of UnitClass (RTTI).
void FUN_007447A0(Obj_007447A0* a1, int a2)
{
    FUN_004D4DC0(a1, a2);
}

// FUNCTION: GAMEMD 0x746400
// Returns a comparison result. Vtable slot 32 of UnitClass (RTTI).
unsigned char Obj_00746400::FUN_00746400() const
{
    return unknown_6C4->unknown_E1B == 0;
}

// FUNCTION: GAMEMD 0x746CB0
// Tail-forwards to another function. Vtable slot 303 of UnitClass (RTTI).
void FUN_00746CB0(Obj_00746CB0* a1, int a2)
{
    FUN_0070F070(a1, a2);
}

// FUNCTION: GAMEMD 0x746CC0
// Tail-forwards to another function. Vtable slot 304 of UnitClass (RTTI).
void FUN_00746CC0(Obj_00746CC0* a1, int a2)
{
    FUN_0070F090(a1, a2);
}

// FUNCTION: GAMEMD 0x746D00
// Member getter (byte).
unsigned char Obj_00746D00::FUN_00746D00() const
{
    return unknown_6C4->unknown_6AC;
}

// FUNCTION: GAMEMD 0x746D60
// Calls other functions. Vtable slot 92 of UnitClass (RTTI).
void FUN_00746D60(Obj_00746D60* a1, int a2)
{
    FUN_00738680(a1, a2);
    a1->FUN_00710460();
}

// FUNCTION: GAMEMD 0x746D80
// Member getter (byte).
unsigned char Obj_00746D80::FUN_00746D80() const
{
    return unknown_6E0;
}

// FUNCTION: GAMEMD 0x746D90
// Branching.
int Obj_00746D90::FUN_00746D90()
{
    return unknown_6E0 != 0 || unknown_6E1 != 0;
}

// FUNCTION: GAMEMD 0x746DD0
// Returns a constant. Vtable slot 12 of UnitClass (RTTI).
int Obj_00746DD0::FUN_00746DD0() const
{
    return 0x8E8;
}

// FUNCTION: GAMEMD 0x746E20
// Returns a constant. Vtable slot 11 of UnitClass (RTTI).
int Obj_00746E20::FUN_00746E20() const
{
    return 1;
}
