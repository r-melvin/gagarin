// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu282_methods.h"

// FUNCTION: GAMEMD 0x7730D0
// Returns a constant. Vtable slot 12 of WeaponTypeClass (RTTI).
int Obj_007730D0::FUN_007730D0() const
{
    return 0x160;
}

// FUNCTION: GAMEMD 0x7730E0
// Returns a constant. Vtable slot 11 of WeaponTypeClass (RTTI).
int Obj_007730E0::FUN_007730E0() const
{
    return 0x31;
}
