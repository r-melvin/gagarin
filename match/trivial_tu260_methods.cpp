// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu260_methods.h"

// FUNCTION: GAMEMD 0x74A960
// Returns a constant. Vtable slot 30 of VoxelAnimClass (RTTI).
int Obj_0074A960::FUN_0074A960() const
{
    return 3;
}

// FUNCTION: GAMEMD 0x74AB10
// Returns a constant. Vtable slot 12 of VoxelAnimClass (RTTI).
int Obj_0074AB10::FUN_0074AB10() const
{
    return 0x148;
}

// FUNCTION: GAMEMD 0x74AB20
// Returns a constant. Vtable slot 11 of VoxelAnimClass (RTTI).
int Obj_0074AB20::FUN_0074AB20() const
{
    return 0x29;
}

// FUNCTION: GAMEMD 0x74AB30
// Member getter (dword). Vtable slot 34 of VoxelAnimClass (RTTI).
int Obj_0074AB30::FUN_0074AB30() const
{
    return unknown_104;
}

// FUNCTION: GAMEMD 0x74AB40
// Returns zero; pops its stack arguments. Vtable slot 66 of VoxelAnimClass (RTTI).
int Obj_0074AB40::FUN_0074AB40(int a1) const
{
    return 0;
}
