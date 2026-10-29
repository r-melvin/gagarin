// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   This header is a layout-only view of vector-shaped objects. Retail RTTI
//   identifies the canonical VectorClass<T> and DynamicVectorClass<T> types;
//   those template definitions live separately under match/core. This view
//   pins only the byte layout used by legacy consumers that access raw fields.
//   The DWORD at +0x0C is kept opaque because some sites read or write the
//   whole cell while others inspect its individual bytes.
#ifndef GG_MATCH_LAYOUT_VECTOR_CLASS_LAYOUT_H
#define GG_MATCH_LAYOUT_VECTOR_CLASS_LAYOUT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VectorClass layout view  (sizeof = 0x10)
struct VectorClassLayout
{
    void* _vtable;       // +0x00  (vptr slot)
    void* Items;         // +0x04  (T** base)
    int   Capacity;      // +0x08
    unsigned long unknown_0C; // +0x0C (retail reads bytes +0x0C and +0x0D)
};

// VectorClass layout view with a typed element pointer (sizeof = 0x10).
template <class T> struct VectorClassLayoutOf
{
    void* _vtable;       // +0x00  (vptr slot)
    T*    Items;         // +0x04
    int   Capacity;      // +0x08
    unsigned long unknown_0C; // +0x0C (retail reads bytes +0x0C and +0x0D)
};

// DynamicVectorClass layout view  (sizeof = 0x18)
struct DynamicVectorClassLayout
{
    void* _vtable;       // +0x00
    void* Items;         // +0x04
    int   Capacity;      // +0x08
    unsigned long unknown_0C; // +0x0C (retail reads bytes +0x0C and +0x0D)
    int   Count;         // +0x10
    int   CapacityIncrement;  // +0x14
};

// DynamicVectorClass layout view with a typed element pointer (sizeof = 0x18).
template <class T> struct DynamicVectorClassLayoutOf
{
    void* _vtable;       // +0x00
    T*    Items;         // +0x04
    int   Capacity;      // +0x08
    unsigned long unknown_0C; // +0x0C (retail reads bytes +0x0C and +0x0D)
    int   Count;         // +0x10
    int   CapacityIncrement;  // +0x14
};

GG_STATIC_ASSERT(offsetof(VectorClassLayout, Items)                 == 0x04);
GG_STATIC_ASSERT(offsetof(VectorClassLayout, Capacity)              == 0x08);
GG_STATIC_ASSERT(offsetof(VectorClassLayout, unknown_0C)             == 0x0C);
GG_STATIC_ASSERT(offsetof(VectorClassLayout, unknown_0C) + 1 == 0x0D);
GG_STATIC_ASSERT(sizeof(VectorClassLayout)                          == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Items)          == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Capacity)       == 0x08);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, unknown_0C)     == 0x0C);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Count)          == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, unknown_0C) + 1 == 0x0D);
GG_STATIC_ASSERT(sizeof(DynamicVectorClassLayout)                   == 0x18);

#endif  // GG_MATCH_LAYOUT_VECTOR_CLASS_LAYOUT_H
