// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// TypeList<int> RTTI and vtable at 0x7E4DD8 establish the primary chain
// TypeList<int> : DynamicVectorClass<int> : VectorClass<int>, offset zero.
// Copy body 0x4777B0 and deleting body 0x477990 touch the inherited prefix.
// By-value readers 0x4764F0/0x475D70 consume a 0x1C-byte default argument
// (RET 0x28 with hidden result, section and key). Assignment at
// 0x68A3F8/0x68A3FF copies the trailing four bytes; constructors leave them untouched.
#ifndef GG_MATCH_CORE_TYPE_LIST_H
#define GG_MATCH_CORE_TYPE_LIST_H
#include "vector_class.h"

struct IStream;

template<class T> class TypeList : public DynamicVectorClass<T>
{
public:
    // Default-constructor stores are verified in the int and pointer TUs.
    TypeList() : DynamicVectorClass<T>() {}
    // Capacity constructor, expanded inline in the INI readers (call 0x525250, then the list vptr store).
    // A member template, so that the explicit instantiations that stand for retail's out-of-line list
    // functions do not emit a function retail does not have.
    template<class N> TypeList(N capacity, T* pMem) : DynamicVectorClass<T>(capacity, pMem) {}
    // Copy constructor: a separate function in retail (0x5255F0 for animation type lists) that the INI
    // readers call; defined in vector_class_operations.h, so TUs that only include this header call it.
    TypeList(const TypeList<T>& other);
    // No-init constructor (vptr only), as the HouseTypeClass no-init constructor builds its veteran lists.
    TypeList(const AbstractNoInit& noInit) : DynamicVectorClass<T>(noInit) {}
    // DynamicVectorClass::AddItem with early returns and `Items[Count++] = item`, the form retail keeps out
    // of line for the house type's veteran lists (0x512F20 / 0x5132F0 / 0x5136C0); defined where used
    // (match/economy/house_building/types_shared.h).
    bool AddItemEarlyOut(const T& item);
    // Nonvirtual stream helper declarations; selected specializations and
    // native entry addresses are declared in vector_stream_save_family_methods.h.
    int FUN_0067A4A0(IStream* stream);
    int FUN_0067A520(IStream* stream);
    int FUN_00717B20(IStream* stream);
    // Typed save helpers of the RulesClass stream save (0x674730); bodies in vector_stream_save_family_methods.cpp.
    int FUN_0067A3C0(IStream* stream);
    int FUN_0067A630(IStream* stream);
    int FUN_0067A6E0(IStream* stream);
    int FUN_0067A770(IStream* stream);
    int FUN_0067A7D0(IStream* stream);
    int FUN_0067A850(IStream* stream);
    int FUN_0067A8E0(IStream* stream);
    unsigned int unknown_18; // observed storage, copied as one dword by the assignment in the INI readers (e.g. 0x721C1E); no scalar meaning claimed
};
#if GG_TARGET_ABI_32
class TechnoTypeClass;
typedef TypeList<int> TypeListIntLayoutCheck;
typedef TypeList<TechnoTypeClass*> TypeListTechnoLayoutCheck;
// Complete each specialization before offsetof for the VC6 parser.
GG_STATIC_ASSERT(sizeof(TypeListIntLayoutCheck) == 0x1C);
GG_STATIC_ASSERT(offsetof(TypeListIntLayoutCheck, unknown_18) == 0x18);
GG_STATIC_ASSERT(sizeof(((TypeListIntLayoutCheck*)0)->unknown_18) == 4);
GG_STATIC_ASSERT(sizeof(TypeListTechnoLayoutCheck) == 0x1C);
GG_STATIC_ASSERT(offsetof(TypeListTechnoLayoutCheck, unknown_18) == 0x18);
#endif
#endif
