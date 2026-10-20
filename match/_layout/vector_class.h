// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout confirmed numerically across many matched TUs (Storage/Tiberium,
//   CaptureManager ControlNodes, Particle/Bullet/Campaign ::Array, …) and
//   against YRpp ArrayClasses.h. P2 layout-spine keystone — the shared
//   `VectorClass`/`DynamicVectorClass` reused by ~every `*Class::Array` global.
//
// Concrete (pointer-element) model: every retail `*Class::Array` is a vector of
// pointers, and matched functions touch `Items`/`Count` directly. `Items` is
// `void*` (the `T**` base) — index it as `((T**)v.Items)[i]`. The vtable pointer
// at +0x00 is an explicit field (`_vtable`); functions that issue a *virtual*
// vector call (inlined `AddItem`→`SetCapacity` via `[_vtable+8]`) belong to the
// P2-blocked set and will move to a real-virtual / COM-base model with the
// AbstractClass spine. (A VC6-clean template form is deferred — cl 12.00 mis-
// parses `T* member` in this layout-assert context.)
#ifndef GG_MATCH_LAYOUT_VECTOR_CLASS_H
#define GG_MATCH_LAYOUT_VECTOR_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VectorClass  (sizeof = 0x10)
struct VectorClass
{
    void* _vtable;       // +0x00  (vptr slot)
    void* Items;         // +0x04  (T** base)
    int   Capacity;      // +0x08
    int   IsAllocated;   // +0x0C  (retail: bool + 3 pad; one 4-byte cell)
};

// DynamicVectorClass  (sizeof = 0x18)
struct DynamicVectorClass
{
    void* _vtable;       // +0x00
    void* Items;         // +0x04
    int   Capacity;      // +0x08
    int   IsAllocated;   // +0x0C
    int   Count;         // +0x10
    int   CapacityIncrement;  // +0x14
};

GG_STATIC_ASSERT(offsetof(VectorClass, Items)                 == 0x04);
GG_STATIC_ASSERT(offsetof(VectorClass, Capacity)              == 0x08);
GG_STATIC_ASSERT(offsetof(VectorClass, IsAllocated)           == 0x0C);
GG_STATIC_ASSERT(sizeof(VectorClass)                          == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass, Items)          == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass, Count)          == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass)                   == 0x18);

#endif  // GG_MATCH_LAYOUT_VECTOR_CLASS_H
