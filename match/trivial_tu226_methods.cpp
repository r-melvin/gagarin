// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu226_methods.h"
#include "_layout/super_weapon_type_class.h"

// FUNCTION: GAMEMD 0x6CE8F0
// Returns a constant. Vtable slot 11 of SuperWeaponTypeClass (RTTI).
int SuperWeaponTypeClass::vf_11()
{
    return 0x20;
}

// FUNCTION: GAMEMD 0x6CE900
// Returns a constant. Vtable slot 12 of SuperWeaponTypeClass (RTTI).
int SuperWeaponTypeClass::vf_12()
{
    return 0x100;
}

// FUNCTION: GAMEMD 0x6CEA10
// Member getter (dword). Vtable slot 16 of SuperWeaponTypeClass (RTTI).
int SuperWeaponTypeClass::vf_16()
{
    return ArrayIndex;
}
