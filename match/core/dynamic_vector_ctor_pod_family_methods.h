// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, element width and both vtable constants read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI (representative
//   0x477DB0). The class names come from the retail RTTI descriptors.
//
// A 19-member family of DynamicVectorClass<T>(size, array) constructors over
// 4-byte element types: 93 bytes each. The body is the already-matched
// VectorClass<T> two-argument constructor (see vector_ctor_pod_family_methods)
// with the derived class's own vtable seated over the base's afterwards and
// the two DynamicVectorClass members initialised — CapacityIncrement to 10 and
// Count to 0, in that order.
//
// The only per-instance variation is the pair of vtable constants: the base
// VectorClass vtable stored during the inlined base construction, and the
// derived DynamicVectorClass vtable stored after it. Every member allocates
// through `SHL EAX,2` (4-byte elements) and calls operator new at 0x7C8E17.
#ifndef GG_MATCH_CORE_DYNAMIC_VECTOR_CTOR_POD_FAMILY_METHODS_H
#define GG_MATCH_CORE_DYNAMIC_VECTOR_CTOR_POD_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The trivial 4-byte element. No user-declared constructor, so `new T[n]` is a
// bare `operator new[](n * 4)` with no array-new counter preamble — retail's
// `SHL EAX,2 / PUSH EAX / CALL 0x7C8E17 / ADD ESP,4`.
struct DynPodElem4 { int Value; };
GG_STATIC_ASSERT(sizeof(DynPodElem4) == 4);

// Declares one instantiation of the family.
//   NAME — the struct name (address-anchored)
#define GG_DYNVECTOR_CTOR_POD_DECL(NAME)                                      \
    struct NAME                                                               \
    {                                                                         \
        const void*  Vptr;              /* +0x0000 */                         \
        DynPodElem4* Vector;            /* +0x0004 */                         \
        int          Capacity;         /* +0x0008 */                         \
        char         IsValid;           /* +0x000C */                         \
        char         IsAllocated;       /* +0x000D */                         \
        char         unknown_0E[2];     /* +0x000E tail padding */            \
        int          Count;       /* +0x0010 */                         \
        int          CapacityIncrement; /* +0x0014 */                         \
        NAME* Ctor(unsigned int size, DynPodElem4* array);                     \
    };                                                                        \
    GG_STATIC_ASSERT(offsetof(NAME, Vptr) == 0x0);                            \
    GG_STATIC_ASSERT(offsetof(NAME, Vector) == 0x4);                          \
    GG_STATIC_ASSERT(offsetof(NAME, Capacity) == 0x8);                       \
    GG_STATIC_ASSERT(offsetof(NAME, IsValid) == 0xC);                         \
    GG_STATIC_ASSERT(offsetof(NAME, IsAllocated) == 0xD);                     \
    GG_STATIC_ASSERT(offsetof(NAME, Count) == 0x10);                    \
    GG_STATIC_ASSERT(offsetof(NAME, CapacityIncrement) == 0x14);              \
    GG_STATIC_ASSERT(sizeof(NAME) == 0x18)

// The shared body. BASEVT is the inlined VectorClass base vtable constant,
// DERIVEDVT the DynamicVectorClass vtable seated over it afterwards.
#define GG_DYNVECTOR_CTOR_POD_BODY(NAME, BASEVT, DERIVEDVT)                   \
    NAME* NAME::Ctor(unsigned int size, DynPodElem4* array)                    \
    {                                                                         \
        this->Vector = 0;                                                     \
        this->Capacity = size;                                               \
        this->IsValid = 1;                                                    \
        this->IsAllocated = 0;                                                \
        this->Vptr = (const void*)BASEVT;                                     \
        if (size) {                                                           \
            if (array) {                                                      \
                this->Vector = array;                                         \
            } else {                                                          \
                this->Vector = new DynPodElem4[size];                          \
                this->IsAllocated = 1;                                        \
            }                                                                 \
        }                                                                     \
        this->Vptr = (const void*)DERIVEDVT;                                  \
        this->CapacityIncrement = 10;                                         \
        this->Count = 0;                                                \
        return this;                                                          \
    }

// One declaration per retail instantiation, ascending by address.
GG_DYNVECTOR_CTOR_POD_DECL(DynamicVectorClass_005D86D0);
GG_DYNVECTOR_CTOR_POD_DECL(DynamicVectorClass_0063DEC0);
GG_DYNVECTOR_CTOR_POD_DECL(DynamicVectorClass_0063E1D0);
GG_DYNVECTOR_CTOR_POD_DECL(DynamicVectorClass_006B83A0);
GG_DYNVECTOR_CTOR_POD_DECL(DynamicVectorClass_006F2230);
GG_DYNVECTOR_CTOR_POD_DECL(DynamicVectorClass_007342D0);
GG_DYNVECTOR_CTOR_POD_DECL(DynamicVectorClass_007632D0);

#endif  // GG_MATCH_CORE_DYNAMIC_VECTOR_CTOR_POD_FAMILY_METHODS_H
