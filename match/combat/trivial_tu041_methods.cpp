// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu041_methods.h"

// FUNCTION: GAMEMD 0x46C820
// Branching. Vtable slot 10 of BulletTypeClass (RTTI).
int Obj_0046C820::FUN_0046C820(int a1, int a2)
{
    if (a1 == unknown_2D8)
    {
        int t1 = unknown_2D8;
        unknown_2D8 = 0;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x46C850
// Returns a constant. Vtable slot 11 of BulletTypeClass (RTTI).
int Obj_0046C850::FUN_0046C850() const
{
    return 9;
}

// FUNCTION: GAMEMD 0x46C860
// Returns a constant. Vtable slot 12 of BulletTypeClass (RTTI).
int Obj_0046C860::FUN_0046C860() const
{
    return 0x2F8;
}

// FUNCTION: GAMEMD 0x46C870
// Returns a constant boolean; pops its stack arguments. Vtable slot 32 of BulletTypeClass (RTTI).
bool Obj_0046C870::FUN_0046C870(int a1, int a2) const
{
    return false;
}

// FUNCTION: GAMEMD 0x46C880
// Returns zero; pops its stack arguments. Vtable slot 35 of BulletTypeClass (RTTI).
int Obj_0046C880::FUN_0046C880(int a1) const
{
    return 0;
}
