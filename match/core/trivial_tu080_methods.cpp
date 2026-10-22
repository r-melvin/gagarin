// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu080_methods.h"

// FUNCTION: GAMEMD 0x4CA580
// Branching. Vtable slot 10 of FactoryClass (RTTI).
int Obj_004CA580::FUN_004CA580(int a1, int a2)
{
    if (a1 == unknown_58)
    {
        int t1 = unknown_58;
        unknown_58 = 0;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x4CA750
// Returns a constant. Vtable slot 11 of FactoryClass (RTTI).
int Obj_004CA750::FUN_004CA750() const
{
    return 0xC;
}

// FUNCTION: GAMEMD 0x4CA760
// Returns a constant. Vtable slot 12 of FactoryClass (RTTI).
int Obj_004CA760::FUN_004CA760() const
{
    return 0x74;
}

// FUNCTION: GAMEMD 0x4CAEF0
// Empty function.
void __cdecl FUN_004CAEF0()
{
}

// FUNCTION: GAMEMD 0x4CAF00
// Empty function.
void __cdecl FUN_004CAF00()
{
}

// FUNCTION: GAMEMD 0x4CAF10
// Empty function.
void __cdecl FUN_004CAF10()
{
}
