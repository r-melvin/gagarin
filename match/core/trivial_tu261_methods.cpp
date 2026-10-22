// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu261_methods.h"

// FUNCTION: GAMEMD 0x74B9F0
// Returns a constant. Vtable slot 11 of VoxelAnimTypeClass (RTTI).
int Obj_0074B9F0::FUN_0074B9F0() const
{
    return 0x2A;
}

// FUNCTION: GAMEMD 0x74BA00
// Returns a constant. Vtable slot 12 of VoxelAnimTypeClass (RTTI).
int Obj_0074BA00::FUN_0074BA00() const
{
    return 0x308;
}

// FUNCTION: GAMEMD 0x74BA10
// Returns a constant boolean; pops its stack arguments. Vtable slot 32 of VoxelAnimTypeClass (RTTI).
bool Obj_0074BA10::FUN_0074BA10(int a1, int a2) const
{
    return false;
}

// FUNCTION: GAMEMD 0x74BA20
// Returns zero; pops its stack arguments. Vtable slot 35 of VoxelAnimTypeClass (RTTI).
int Obj_0074BA20::FUN_0074BA20(int a1) const
{
    return 0;
}
