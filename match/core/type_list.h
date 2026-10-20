// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// TypeList<int> RTTI and vtable at 0x7E4DD8 establish the primary chain
// TypeList<int> : DynamicVectorClass<int> : VectorClass<int>, offset zero.
// Copy body 0x4777B0 and deleting body 0x477990 touch only the inherited
// prefix. No complete TypeList size or extra-member absence is established.
#ifndef GG_MATCH_CORE_TYPE_LIST_H
#define GG_MATCH_CORE_TYPE_LIST_H
#include "vector_class.h"

template<class T> class TypeList : public DynamicVectorClass<T>
{
public:
    // Default-constructor stores are verified in the int and pointer TUs.
    TypeList() : DynamicVectorClass<T>() {}
    TypeList(const TypeList<T>& other) : DynamicVectorClass<T>(other) {}
};
#endif
