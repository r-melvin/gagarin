// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The dynamic vector's search and by-value removal, split from vector_class_operations.h so that a
// translation unit whose vector base constructor is out of line in retail (the type-class constructors,
// which call 0x525680 / 0x477BE0 and expand only the dynamic tail) can still see the inlined
// FindItemIndex and RemoveItem bodies without the base constructor.
#ifndef GG_MATCH_CORE_VECTOR_CLASS_SEARCH_H
#define GG_MATCH_CORE_VECTOR_CLASS_SEARCH_H
#include "vector_class.h"

// By-value removal through the virtual FindItemIndex (slot +0x10). Inline in
// SuperClass::Lose (0x6CB7B0) and ToolTipManager::Remove (0x724730); the call
// through `this` inside the inlined body keeps the dispatch indirect.
template<class T>
inline bool DynamicVectorClass<T>::RemoveItem(const T& item)
{
    int index = FindItemIndex(item);
    if (index != -1)
        return Delete(index);
    return false;
}

template<class T> int DynamicVectorClass<T>::FindItemIndex(const T& item) const
{
    for (int i = 0; i < this->Count; ++i) {
        if (this->Items[i] == item) return i;
    }
    return -1;
}

#endif
