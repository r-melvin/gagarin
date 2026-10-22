// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu024_methods.h"

// FUNCTION: GAMEMD 0x423920
// Empty function.
void __cdecl FUN_00423920()
{
}

// FUNCTION: GAMEMD 0x425510
// Member getter (dword). Vtable slot 123 of AnimClass (RTTI).
int Obj_00425510::FUN_00425510() const
{
    return unknown_C8->unknown_2C0;
}

// FUNCTION: GAMEMD 0x425520
// Member getter (dword). Vtable slot 34 of AnimClass (RTTI).
int Obj_00425520::FUN_00425520() const
{
    return unknown_C8;
}

// FUNCTION: GAMEMD 0x426530
// Returns a constant. Vtable slot 12 of AnimClass (RTTI).
int AnimClass::vf_12()
{
    return 0x1C8;
}

// FUNCTION: GAMEMD 0x426580
// Returns a constant. Vtable slot 11 of AnimClass (RTTI).
int AnimClass::vf_11()
{
    return 4;
}

// FUNCTION: GAMEMD 0x426740
// Returns a constant.
int __cdecl FUN_00426740()
{
    return 0xB00;
}

// FUNCTION: GAMEMD 0x427290
// Returns the address of a member. Vtable slot 4 of AnimFile (RTTI).
int* Obj_00427290::FUN_00427290()
{
    return &unknown_50C;
}
