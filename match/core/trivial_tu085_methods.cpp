// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu085_methods.h"

// FUNCTION: GAMEMD 0x4D27B0
// Returns a constant. Vtable slot 11 of FoggedObjectClass (RTTI).
int Obj_004D27B0::FUN_004D27B0() const
{
    return 0x3D;
}

// FUNCTION: GAMEMD 0x4D27C0
// Returns a constant. Vtable slot 12 of FoggedObjectClass (RTTI).
int Obj_004D27C0::FUN_004D27C0() const
{
    return 0x78;
}
