// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x551A90 (0x8C bytes, RET 4).
#include "../_layout/layer_class.h"
#include "../_layout/object_class.h"

// FUNCTION: GAMEMD 0x551A90
// Insert an object into the layer ahead of the first element that
// ObjectClass::FUN_005F6220 ranks after it, growing the vector first if full.
int LayerClass::SortedAdd(ObjectClass* pObject)
{
    if (Count >= Capacity) {
        if ((!IsAllocated && Capacity != 0) || CapacityIncrement <= 0
            || !SetCapacity(Capacity + CapacityIncrement, 0)) {
            return 0;
        }
    }
    int i;
    for (i = 0; i < Count; i++) {
        if (Items[i]->FUN_005F6220(pObject)) {
            break;
        }
    }
    for (int j = Count - 1; j >= i; j--) {
        Items[j + 1] = Items[j];
    }
    Items[i] = pObject;
    Count = Count + 1;
    return 1;
}
