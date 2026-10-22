// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu270_methods.h"

// FUNCTION: GAMEMD 0x763E00
// Returns a constant. Vtable slot 12 of WaypointPathClass (RTTI).
int Obj_00763E00::FUN_00763E00() const
{
    return 0x40;
}

// FUNCTION: GAMEMD 0x763E10
// Returns a constant. Vtable slot 11 of WaypointPathClass (RTTI).
int Obj_00763E10::FUN_00763E10() const
{
    return 0x33;
}
