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
    TypeList(const TypeList<T>& other) : DynamicVectorClass<T>(other) {}
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
    unsigned char unknown_18[4]; // observed storage, no scalar meaning or initialization claim
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
