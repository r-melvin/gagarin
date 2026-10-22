// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu173_methods.h"

// FUNCTION: GAMEMD 0x629710
// Stores several members.
void Obj_00629710::FUN_00629710()
{
    unknown_50 = 0;
    unknown_4C = 0;
}

// FUNCTION: GAMEMD 0x62AF50
// Returns a constant. Vtable slot 12 of ParasiteClass (RTTI).
int Obj_0062AF50::FUN_0062AF50() const
{
    return 0x58;
}

// FUNCTION: GAMEMD 0x62AF60
// Returns a constant. Vtable slot 11 of ParasiteClass (RTTI).
int Obj_0062AF60::FUN_0062AF60() const
{
    return 0x43;
}
