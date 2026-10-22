// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu025_methods.h"

// FUNCTION: GAMEMD 0x428C10
// Branching. Vtable slot 10 of AnimTypeClass (RTTI).
int Obj_00428C10::FUN_00428C10(int a1, int a2)
{
    int t1 = unknown_2C8;
    if (t1 == a1)
    {
        unknown_2C8 = 0;
    }
    return t1;
}

// FUNCTION: GAMEMD 0x428E50
// Returns a constant. Vtable slot 11 of AnimTypeClass (RTTI).
int Obj_00428E50::FUN_00428E50() const
{
    return 5;
}

// FUNCTION: GAMEMD 0x428E60
// Member getter (dword). Vtable slot 16 of AnimTypeClass (RTTI).
int Obj_00428E60::FUN_00428E60() const
{
    return unknown_294;
}

// FUNCTION: GAMEMD 0x428E70
// Returns a constant. Vtable slot 12 of AnimTypeClass (RTTI).
int Obj_00428E70::FUN_00428E70() const
{
    return 0x378;
}

// FUNCTION: GAMEMD 0x428E80
// Returns a constant boolean; pops its stack arguments. Vtable slot 32 of AnimTypeClass (RTTI).
bool Obj_00428E80::FUN_00428E80(int a1, int a2) const
{
    return false;
}

// FUNCTION: GAMEMD 0x428E90
// Returns zero; pops its stack arguments. Vtable slot 35 of AnimTypeClass (RTTI).
int Obj_00428E90::FUN_00428E90(int a1) const
{
    return 0;
}
