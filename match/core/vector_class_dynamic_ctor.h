// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x595CEF calls the base constructor, then 0x595CF4..0x595D09
// seats the dynamic table and initializes growth/count. Keep the derived
// construction body available independently of base allocation construction.
#ifndef GG_MATCH_CORE_VECTOR_CLASS_DYNAMIC_CTOR_H
#define GG_MATCH_CORE_VECTOR_CLASS_DYNAMIC_CTOR_H
#include "vector_class.h"

template<class T> DynamicVectorClass<T>::DynamicVectorClass(int capacity, T* pMem)
    : VectorClass<T>(capacity, pMem)
{
    this->CapacityIncrement = 10;
    this->Count = 0;
}

#endif
