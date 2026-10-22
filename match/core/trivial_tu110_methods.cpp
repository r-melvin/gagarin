// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu110_methods.h"

// FUNCTION: GAMEMD 0x544DF0
// Empty function.
void __cdecl FUN_00544DF0()
{
}

// FUNCTION: GAMEMD 0x544FF0
// Returns a constant boolean.
bool __cdecl FUN_00544FF0()
{
    return false;
}

// FUNCTION: GAMEMD 0x547CE0
// Empty function.
void __cdecl FUN_00547CE0()
{
}

// FUNCTION: GAMEMD 0x54A140
// Returns a constant. Vtable slot 11 of IsometricTileTypeClass (RTTI).
int Obj_0054A140::FUN_0054A140() const
{
    return 0x12;
}

// FUNCTION: GAMEMD 0x54A150
// Returns a constant. Vtable slot 12 of IsometricTileTypeClass (RTTI).
int Obj_0054A150::FUN_0054A150() const
{
    return 0x30C;
}

// FUNCTION: GAMEMD 0x54A160
// Member getter (dword). Vtable slot 16 of IsometricTileTypeClass (RTTI).
int Obj_0054A160::FUN_0054A160() const
{
    return unknown_294;
}
