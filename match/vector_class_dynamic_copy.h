// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   DynamicVectorClass<T>'s copy constructor alone, for a reader that expands it while the vector copy
//   stays a call (0x6724E3: call 0x477B60, then the two counters copied inline).
#ifndef GG_MATCH_VECTOR_CLASS_DYNAMIC_COPY_H
#define GG_MATCH_VECTOR_CLASS_DYNAMIC_COPY_H

#include "vector_class.h"

template<class T> inline DynamicVectorClass<T>::DynamicVectorClass(const DynamicVectorClass<T>& other)
    : VectorClass<T>(other), Count(other.Count), CapacityIncrement(other.CapacityIncrement)
{
}

#endif  // GG_MATCH_VECTOR_CLASS_DYNAMIC_COPY_H
