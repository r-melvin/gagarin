// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu100_methods.h"

// FUNCTION: GAMEMD 0x523C80
// Empty function.
void __cdecl FUN_00523C80()
{
}

// FUNCTION: GAMEMD 0x524790
// Member getter (dword). Vtable slot 45 of InfantryTypeClass (RTTI).
int Obj_00524790::FUN_00524790() const
{
    return DAT_008871E0->unknown_16D8;
}

// FUNCTION: GAMEMD 0x5247A0
// Returns zero. Vtable slot 44 of InfantryTypeClass (RTTI).
int Obj_005247A0::FUN_005247A0() const
{
    return 0;
}

// FUNCTION: GAMEMD 0x5247B0
// Tail-forwards to another function. Vtable slot 40 of InfantryTypeClass (RTTI).
void Obj_005247B0::FUN_005247B0()
{
    FUN_00711E80();
}

// FUNCTION: GAMEMD 0x5247C0
// Tail-forwards to another function. Vtable slot 41 of InfantryTypeClass (RTTI).
void Obj_005247C0::FUN_005247C0()
{
    FUN_00711E90();
}

// FUNCTION: GAMEMD 0x524D40
// Returns a constant. Vtable slot 11 of InfantryTypeClass (RTTI).
int Obj_00524D40::FUN_00524D40() const
{
    return 0x10;
}

// FUNCTION: GAMEMD 0x524D50
// Returns a constant. Vtable slot 12 of InfantryTypeClass (RTTI).
int Obj_00524D50::FUN_00524D50() const
{
    return 0xED0;
}

// FUNCTION: GAMEMD 0x524D60
// Member getter (dword). Vtable slot 16 of InfantryTypeClass (RTTI).
int Obj_00524D60::FUN_00524D60() const
{
    return unknown_DF8;
}

// FUNCTION: GAMEMD 0x524EC0
// Returns its receiver.
Obj_00524EC0* Obj_00524EC0::FUN_00524EC0()
{
    return this;
}
