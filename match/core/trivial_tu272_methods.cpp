// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu272_methods.h"

// FUNCTION: GAMEMD 0x766FA0
// Updates one member in place. Vtable slot 2 of VectorCursor<WorldDominationTour::VGameOption::V?$rc_ptr::V?$DynamicVectorClass::rc_ptr<WorldDominationTour::GameOption>> (RTTI).
Obj_00766FA0* Obj_00766FA0::FUN_00766FA0()
{
    unknown_08++;
    return this;
}

// FUNCTION: GAMEMD 0x766FB0
// Updates one member in place. Vtable slot 3 of VectorCursor<WorldDominationTour::VGameOption::V?$rc_ptr::V?$DynamicVectorClass::rc_ptr<WorldDominationTour::GameOption>> (RTTI).
Obj_00766FB0* Obj_00766FB0::FUN_00766FB0()
{
    unknown_08--;
    return this;
}
