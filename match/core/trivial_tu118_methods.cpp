// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu118_methods.h"

// FUNCTION: GAMEMD 0x555130
// Returns a constant. Vtable slot 12 of LightSourceClass (RTTI).
int Obj_00555130::FUN_00555130() const
{
    return 0x4C;
}

// FUNCTION: GAMEMD 0x555140
// Returns a constant. Vtable slot 11 of LightSourceClass (RTTI).
int Obj_00555140::FUN_00555140() const
{
    return 0x36;
}
