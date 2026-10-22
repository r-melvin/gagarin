// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu092_methods.h"

// FUNCTION: GAMEMD 0x4F1710
// Empty function.
void __cdecl FUN_004F1710()
{
}

// FUNCTION: GAMEMD 0x4F2B40
// Updates one member in place. Vtable slot 2 of VectorCursor<GraphicMenuItem*, DynamicVectorClass<GraphicMenuItem*>> (RTTI).
Obj_004F2B40* Obj_004F2B40::FUN_004F2B40()
{
    unknown_08++;
    return this;
}

// FUNCTION: GAMEMD 0x4F2B50
// Updates one member in place. Vtable slot 3 of VectorCursor<GraphicMenuItem*, DynamicVectorClass<GraphicMenuItem*>> (RTTI).
Obj_004F2B50* Obj_004F2B50::FUN_004F2B50()
{
    unknown_08--;
    return this;
}
