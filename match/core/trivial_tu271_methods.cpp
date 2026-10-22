// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu271_methods.h"

// FUNCTION: GAMEMD 0x764FA0
// Calls other functions.
unsigned char Obj_00764FA0::FUN_00764FA0()
{
    return unknown_30 != unknown_0C->FUN_0076BFA0();
}

// FUNCTION: GAMEMD 0x765B40
// Updates one member in place. Vtable slot 2 of VectorCursor<WorldDominationTour::VConflict::V?$rc_ptr::V?$DynamicVectorClass::rc_ptr<WorldDominationTour::Conflict>> (RTTI).
Obj_00765B40* Obj_00765B40::FUN_00765B40()
{
    unknown_08++;
    return this;
}

// FUNCTION: GAMEMD 0x765B50
// Updates one member in place. Vtable slot 3 of VectorCursor<WorldDominationTour::VConflict::V?$rc_ptr::V?$DynamicVectorClass::rc_ptr<WorldDominationTour::Conflict>> (RTTI).
Obj_00765B50* Obj_00765B50::FUN_00765B50()
{
    unknown_08--;
    return this;
}
