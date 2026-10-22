// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu278_methods.h"

// FUNCTION: GAMEMD 0x76F000
// Calls other functions.
int Obj_0076F000::FUN_0076F000(int a1, int a2)
{
    FUN_0076FF40(a1, &unknown_2C, a2);
    return a1;
}

// FUNCTION: GAMEMD 0x76F160
// Updates one member in place. Vtable slot 2 of VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*>> (RTTI).
Obj_0076F160* Obj_0076F160::FUN_0076F160()
{
    unknown_08++;
    return this;
}

// FUNCTION: GAMEMD 0x76F170
// Updates one member in place. Vtable slot 3 of VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*>> (RTTI).
Obj_0076F170* Obj_0076F170::FUN_0076F170()
{
    unknown_08--;
    return this;
}

// FUNCTION: GAMEMD 0x76F180
// Updates one member in place. Vtable slot 2 of VectorCursor<WorldDominationTour::VTerritory::V?$rc_ptr::V?$DynamicVectorClass::rc_ptr<WorldDominationTour::Territory>> (RTTI).
Obj_0076F180* Obj_0076F180::FUN_0076F180()
{
    unknown_08++;
    return this;
}

// FUNCTION: GAMEMD 0x76F190
// Updates one member in place. Vtable slot 3 of VectorCursor<WorldDominationTour::VTerritory::V?$rc_ptr::V?$DynamicVectorClass::rc_ptr<WorldDominationTour::Territory>> (RTTI).
Obj_0076F190* Obj_0076F190::FUN_0076F190()
{
    unknown_08--;
    return this;
}

// FUNCTION: GAMEMD 0x76F1A0
// Updates one member in place. Vtable slot 2 of VectorCursor<MSAnim*, DynamicVectorClass<MSAnim*>> (RTTI).
Obj_0076F1A0* Obj_0076F1A0::FUN_0076F1A0()
{
    unknown_08++;
    return this;
}

// FUNCTION: GAMEMD 0x76F1B0
// Updates one member in place. Vtable slot 3 of VectorCursor<MSAnim*, DynamicVectorClass<MSAnim*>> (RTTI).
Obj_0076F1B0* Obj_0076F1B0::FUN_0076F1B0()
{
    unknown_08--;
    return this;
}
