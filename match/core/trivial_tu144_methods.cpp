// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu144_methods.h"

// FUNCTION: GAMEMD 0x5C1CB0
// Stores its argument in a member. Vtable slot 9 of MPCooperative (RTTI).
void Obj_005C1CB0::FUN_005C1CB0()
{
    unknown_340 = 1;
}

// FUNCTION: GAMEMD 0x5C36F0
// Tail-forwards to another function. Vtable slot 35 of MPCooperative (RTTI).
void Obj_005C36F0::FUN_005C36F0()
{
    FUN_005D7570();
}

// FUNCTION: GAMEMD 0x5C3700
// Returns a constant boolean. Vtable slot 15 of MPCooperative (RTTI).
bool Obj_005C3700::FUN_005C3700() const
{
    return false;
}

// FUNCTION: GAMEMD 0x5C42C0
// Returns a constant. Vtable slot 38 of MPCooperative (RTTI).
int Obj_005C42C0::FUN_005C42C0() const
{
    return 2;
}

// FUNCTION: GAMEMD 0x5C4EE0
// Returns a constant boolean. Vtable slot 1 of MPCooperative (RTTI).
bool Obj_005C4EE0::FUN_005C4EE0() const
{
    return true;
}

// FUNCTION: GAMEMD 0x5C4EF0
// Returns a constant boolean. Vtable slot 2 of MPCooperative (RTTI).
bool Obj_005C4EF0::FUN_005C4EF0() const
{
    return true;
}

// FUNCTION: GAMEMD 0x5C4F00
// Returns a constant boolean. Vtable slot 47 of MPCooperative (RTTI).
bool Obj_005C4F00::FUN_005C4F00() const
{
    return false;
}
