// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu040_methods.h"

// FUNCTION: GAMEMD 0x4666B0
// Empty function.
void __cdecl FUN_004666B0()
{
}

// FUNCTION: GAMEMD 0x46AFD0
// Calls other functions. Vtable slot 1 of BulletClass (RTTI).
void Obj_0046AFD0::FUN_0046AFD0(int a1)
{
    DAT_00ABCD3C++;
    InterlockedIncrement(a1 + 0x1C);
}

// FUNCTION: GAMEMD 0x46B030
// Returns a comparison result.
bool Obj_0046B030::FUN_0046B030() const
{
    return (unknown_AC->unknown_2DC > 0) ? true : false;
}

// FUNCTION: GAMEMD 0x46B5A0
// Stores its argument in a member; pops its stack arguments. Vtable slot 123 of BulletClass (RTTI).
void Obj_0046B5A0::FUN_0046B5A0(int a1)
{
    unknown_10C = a1;
}

// FUNCTION: GAMEMD 0x46B5B0
// Member getter (dword). Vtable slot 34 of BulletClass (RTTI).
int Obj_0046B5B0::FUN_0046B5B0() const
{
    return unknown_AC;
}
