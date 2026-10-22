// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu066_methods.h"

// FUNCTION: GAMEMD 0x4A7C70
// Returns a constant. Vtable slot 12 of DiskLaserClass (RTTI).
int Obj_004A7C70::FUN_004A7C70() const
{
    return 0x40;
}

// FUNCTION: GAMEMD 0x4A7C80
// Returns a constant. Vtable slot 11 of DiskLaserClass (RTTI).
int Obj_004A7C80::FUN_004A7C80() const
{
    return 0x49;
}
