// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at 0x765680 and its neighbours. The member displacements come
//   straight off the instructions — [ESI+4] Items, [ESI+8] Capacity,
//   [ESI+0xD] IsAllocated, [ESI+0x10] Count — and the element release is
//   `MOV EAX,[ECX]; PUSH 3; CALL [EAX]`, the element type's own vector-deleting
//   destructor through slot 0 with flag 3, i.e. `delete[]` on a polymorphic
//   element type. These functions carry no name in the binary or in the YRpp
//   map, so they keep placeholder names.
//
// Shape (43 bytes): the growable vector's Clear() over a polymorphic element
//   type — zero Count first, then the base Clear() inlined: release and null
//   the block if this vector owns one, then reset the allocated flag and the
//   capacity unconditionally. Four instantiations, byte-identical to one
//   another: no vtable is seated, so nothing varies at all and the whole family
//   is one body.
//
// Phrasing note: nulling Items outside the ownership test instead of inside it
//   retargets the two guarding branches and costs 9.5%. Retail's two early
//   jumps land on the IsAllocated reset, not on the Items reset.
#ifndef GG_MATCH_CORE_POLYMORPHIC_VECTOR_CLEAR_FAMILY_METHODS_H
#define GG_MATCH_CORE_POLYMORPHIC_VECTOR_CLEAR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The element type: only the virtualness of its destructor reaches the code.
class VirtualElement { public: virtual ~VirtualElement(); };

#define GG_PVEC_DYN_DECL(TAG)                                             \
struct PVecDyn_##TAG                                                      \
{                                                                         \
    char*           Vptr;             /* +0x0000 */                       \
    VirtualElement* Items;            /* +0x0004 */                       \
    int             Capacity;         /* +0x0008 */                       \
    char            _pad0C;           /* +0x000C */                       \
    char            IsAllocated;      /* +0x000D */                       \
    char            _pad0E[2];                                            \
    int             Count;            /* +0x0010 */                       \
    void Clear();                                                         \
}

#define GG_PVEC_CLEAR_BODY(TAG)                                           \
void PVecDyn_##TAG::Clear()                                               \
{                                                                         \
    this->Count = 0;                                                      \
    if (this->Items != 0 && this->IsAllocated) {                          \
        delete[] this->Items;                                             \
        this->Items = 0;                                                  \
    }                                                                     \
    this->IsAllocated = 0;                                                \
    this->Capacity = 0;                                                   \
}

GG_PVEC_DYN_DECL(00765680);
GG_PVEC_DYN_DECL(00766800);
GG_PVEC_DYN_DECL(00769C50);
GG_PVEC_DYN_DECL(0076B710);

GG_STATIC_ASSERT(offsetof(PVecDyn_00765680, Items) == 0x4 &&
                 offsetof(PVecDyn_00765680, Capacity) == 0x8 &&
                 offsetof(PVecDyn_00765680, IsAllocated) == 0xD &&
                 offsetof(PVecDyn_00765680, Count) == 0x10 &&
                 sizeof(PVecDyn_00765680) == 0x14);

#endif  // GG_MATCH_CORE_POLYMORPHIC_VECTOR_CLEAR_FAMILY_METHODS_H
