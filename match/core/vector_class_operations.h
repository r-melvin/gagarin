// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Pointer-element removal is inlined in ToolTipManager::Remove at 0x724730:
// find index via slot 4, decrement Count, then shift the remaining entries.
// This definition is separate so storage/Clear-only instantiations can use
// forward-declared aggregate types without instantiating element assignment.
#ifndef GG_MATCH_CORE_VECTOR_CLASS_OPERATIONS_H
#define GG_MATCH_CORE_VECTOR_CLASS_OPERATIONS_H
#include "vector_class.h"

template<class T>
bool DynamicVectorClass<T>::RemoveItem(const T& item)
{
    int index = FindItemIndex(item);
    if (index != -1 && index < Count) {
        Count = Count - 1;
        for (; index < Count; ++index)
            this->Items[index] = this->Items[index + 1];
        return true;
    }
    return false;
}
#endif
