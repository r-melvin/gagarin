// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Layout and element sizes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI (representative 0x477BE0).
//   RA1's VectorClass is a naming/structure reference only.
//
// A 48-member family of VectorClass<T> two-argument constructors over
// *trivial* element types: 74 bytes each, identical apart from the vtable
// constant stored at +0 and the element-size shift feeding operator new[].
// Distinct from the 0x42FC40 pair, whose element types carry a user-declared
// constructor and therefore emit the array-new counter preamble in both arms.
#ifndef GG_MATCH_CORE_VECTOR_CTOR_POD_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_CTOR_POD_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One trivial element type per width. No user-declared constructor, so
// `new T[n]` is a bare `operator new[](n * sizeof(T))` with no iterator
// preamble — retail's `SHL EAX,2 / PUSH EAX / CALL / ADD ESP,4`.
struct PodElem4 { int Value; };
struct PodElem8 { int A, B; };
GG_STATIC_ASSERT(sizeof(PodElem4) == 4);
GG_STATIC_ASSERT(sizeof(PodElem8) == 8);

// Declares one instantiation of the family.
//   NAME  — the struct name (address-anchored)
//   ELEM  — PodElem4 or PodElem8
//   VTBL  — the extern vtable array stored at +0
#define GG_VECTOR_CTOR_POD_DECL(NAME, ELEM)                                   \
    struct NAME                                                               \
    {                                                                         \
        const void* Vptr;        /* +0x0000 */                                \
        ELEM* Vector;            /* +0x0004 */                                \
        int   VectorMax;         /* +0x0008 */                                \
        char  IsValid;           /* +0x000C */                                \
        char  IsAllocated;       /* +0x000D */                                \
        NAME* Ctor(unsigned int size, ELEM* array);                           \
    };                                                                        \
    GG_STATIC_ASSERT(offsetof(NAME, Vptr) == 0x0);                            \
    GG_STATIC_ASSERT(offsetof(NAME, Vector) == 0x4);                          \
    GG_STATIC_ASSERT(offsetof(NAME, VectorMax) == 0x8);                       \
    GG_STATIC_ASSERT(offsetof(NAME, IsValid) == 0xC);                         \
    GG_STATIC_ASSERT(offsetof(NAME, IsAllocated) == 0xD);                     \
    GG_STATIC_ASSERT(sizeof(NAME) == 0x10)

// The shared body. `vtbl` is the instantiation's vtable address constant.
#define GG_VECTOR_CTOR_POD_BODY(NAME, ELEM, VTBL)                             \
    NAME* NAME::Ctor(unsigned int size, ELEM* array)                          \
    {                                                                         \
        this->Vector = 0;                                                     \
        this->VectorMax = size;                                               \
        this->IsValid = 1;                                                    \
        this->IsAllocated = 0;                                                \
        this->Vptr = (const void*)VTBL;                                       \
        if (size) {                                                           \
            if (array) {                                                      \
                this->Vector = array;                                         \
            } else {                                                          \
                this->Vector = new ELEM[size];                                \
                this->IsAllocated = 1;                                        \
            }                                                                 \
        }                                                                     \
        return this;                                                          \
    }

// One declaration per retail instantiation, ascending by address.
GG_VECTOR_CTOR_POD_DECL(VectorClass_00477BE0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00478790, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00488080, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0048B070, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0049F090, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_004A4E30, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_004BA2F0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_004BA340, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_004CABF0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_004D0440, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_004E0E80, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_004F2C00, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00510500, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00510550, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005105A0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005105F0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00510640, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00510690, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005138F0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00513940, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00513990, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00525680, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_00538B30, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0054A850, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0054EBF0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0055BB40, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005AD6F0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005AD740, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005AD820, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005ADAB0, PodElem8);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005C59E0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005C5A30, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005D8950, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005D89A0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005D89F0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_005EF0B0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0067C310, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0067C3A0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0067C430, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0069D770, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0069D870, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_006B1AB0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_006B8880, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_006CABA0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_007343E0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0076F1C0, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_0076F210, PodElem4);
GG_VECTOR_CTOR_POD_DECL(VectorClass_007AECD0, PodElem4);

#endif  // GG_MATCH_CORE_VECTOR_CTOR_POD_FAMILY_METHODS_H
