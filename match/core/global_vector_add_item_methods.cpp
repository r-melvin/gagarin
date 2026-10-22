// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Append of a pointer to a global DynamicVectorClass, repeated for three
// element types: the canonical inline AddItem expanded at each site, with the
// result discarded. The element types are named only by placeholder; the
// global vectors are named by retail address.

#include "vector_class_operations.h"

struct Obj_005D4E70;
extern DynamicVectorClass<Obj_005D4E70*> DAT_00ABFC90;

// FUNCTION: GAMEMD 0x005D4E70
void FUN_005D4E70(Obj_005D4E70* item)
{
    DynamicVectorClass<Obj_005D4E70*>& v = DAT_00ABFC90;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            if (!v.SetCapacity(v.CapacityIncrement + v.Capacity, 0))
                return;
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index] = item;
}

struct Obj_00638A20;
extern DynamicVectorClass<Obj_00638A20*> DAT_00AC4C18;


struct Obj_00638DC0;
extern DynamicVectorClass<Obj_00638DC0*> DAT_00AC4B30;

