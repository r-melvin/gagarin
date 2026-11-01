// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu226_methods.h"

// FUNCTION: GAMEMD 0x6CE8F0
// Returns a constant. Vtable slot 11 of SuperWeaponTypeClass (RTTI).
int Obj_006CE8F0::FUN_006CE8F0() const
{
    return 0x20;
}

// FUNCTION: GAMEMD 0x6CE900
// Returns a constant. Vtable slot 12 of SuperWeaponTypeClass (RTTI).
int Obj_006CE900::FUN_006CE900() const
{
    return 0x100;
}

// FUNCTION: GAMEMD 0x6CEA10
// Member getter (dword). Vtable slot 16 of SuperWeaponTypeClass (RTTI).
int Obj_006CEA10::FUN_006CEA10() const
{
    return unknown_98;
}
