// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Append and by-index removal are expanded at 0x5576A0 and 0x557730.
// Definitions are shared with vector_class_operations.h; callers that use an
// out-of-line capacity constructor can include these algorithms separately.
#ifndef GG_MATCH_CORE_VECTOR_CLASS_MUTATION_H
#define GG_MATCH_CORE_VECTOR_CLASS_MUTATION_H
#include "vector_class.h"

// By-index removal, inline: expanded in ListClass::RemoveItem at 0x557730
// (its bound test repeats the caller's). Out-of-line instances exist where
// cl declines to inline it.
template<class T>
inline bool DynamicVectorClass<T>::Delete(int index)
{
    if (index < Count) {
        Count--;
        for (int i = index; i < Count; i++)
            this->Items[i] = this->Items[i + 1];
        return true;
    }
    return false;
}

// Append, inline: expanded in ListClass::AddItem (0x5576A0). Growth by
// CapacityIncrement happens only when the vector owns its block or has none.
// The new index is taken before the store, so Count is loaded ahead of
// Items, which is retail's order.
template<class T>
inline bool DynamicVectorClass<T>::AddItem(const T& item)
{
    if (Count >= this->Capacity) {
        if ((this->IsAllocated || this->Capacity == 0) && CapacityIncrement > 0) {
            if (!this->SetCapacity(this->Capacity + CapacityIncrement, 0))
                return false;
        } else {
            return false;
        }
    }
    int index = Count++;
    this->Items[index] = item;
    return true;
}

#endif
