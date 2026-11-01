// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   DynamicVectorClass::AddItem as retail expands it inline at call sites,
//   checked against the disassembly of the callers listed in each TU.
#ifndef GG_MATCH_CORE_VECTOR_ADD_ITEM_FREE_H
#define GG_MATCH_CORE_VECTOR_ADD_ITEM_FREE_H

// Append as a free function taking the vector (any layout with Count,
// Capacity, IsAllocated, CapacityIncrement, Items and SetCapacity). As a free
// function the inlined grow path accumulates into the increment's register
// (`ADD ECX,EAX`) as retail does; the member spelling accumulates into the
// capacity's (`ADD EAX,ECX`).
template<class V, class U>
inline bool DynamicVectorAddItemFree(V* v, U item)
{
    if (v->Count >= v->Capacity) {
        if (!v->IsAllocated && v->Capacity != 0)
            return false;
        if (v->CapacityIncrement <= 0)
            return false;
        if (!v->SetCapacity(v->Capacity + v->CapacityIncrement, 0))
            return false;
    }
    int index = v->Count++;
    v->Items[index] = item;
    return true;
}

#endif
