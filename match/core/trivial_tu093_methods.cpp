// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu093_methods.h"

// FUNCTION: GAMEMD 0x4F3AD0
// Empty function that pops its stack arguments. Vtable slot 4 of GraphicMenuItem (RTTI) and 2 derived vtable(s).
void Obj_004F3AD0::FUN_004F3AD0(int a1)
{
}

// FUNCTION: GAMEMD 0x4F3AE0
// Empty function that pops its stack arguments. Vtable slot 5 of GraphicMenuItem (RTTI) and 2 derived vtable(s).
void Obj_004F3AE0::FUN_004F3AE0(int a1)
{
}

// FUNCTION: GAMEMD 0x4F3FF0
// Updates one member in place. Vtable slot 2 of VectorCursor<unsigned int, DynamicVectorClass<unsigned int>> (RTTI).
Obj_004F3FF0* Obj_004F3FF0::FUN_004F3FF0()
{
    unknown_08++;
    return this;
}

// FUNCTION: GAMEMD 0x4F4000
// Updates one member in place. Vtable slot 3 of VectorCursor<unsigned int, DynamicVectorClass<unsigned int>> (RTTI).
Obj_004F4000* Obj_004F4000::FUN_004F4000()
{
    unknown_08--;
    return this;
}
