// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI names eight ".?AV?$VectorCursor@<T><Container>@@" classes. Each is a
//   polymorphic cursor over a vector: the vptr, the vector pointer at +0x04 and the
//   index at +0x08. The retail vtables carry the destructor in slot 0, the in-range test (0x4F3FC0 and
//   its siblings) in slot 1 and the increment / decrement in slots 2 and 3. The constructors at 0x76F090 and 0x76F0C0 store both arguments
//   (vector, then index) before the vptr; the slot 2 and slot 3 bodies (0x4F3FF0,
//   0x4F4000, 0x76A5A0, 0x76A5B0) increment and decrement the +0x08 word. The
//   scalar deleting destructors are empty virtual ones (vector_cursor_ddtors.cpp).
#ifndef GG_MATCH_CORE_VECTOR_CURSOR_H
#define GG_MATCH_CORE_VECTOR_CURSOR_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class.h"

// The limit a cursor runs against: the count of a dynamic vector (+0x10) or the capacity of a plain one (+0x08).
template <class T> inline unsigned CursorLimit(const DynamicVectorClass<T>* v) { return v->Count; }
template <class T> inline unsigned CursorLimit(const VectorClass<T>* v) { return v->Capacity; }

template <class T, class Container>
class VectorCursor
{
public:
    VectorCursor() {}
    VectorCursor(Container* vector, int index) : unknown_04(vector), unknown_08(index) {}
    virtual ~VectorCursor() {}
    // Slots 1-3 are defined out of line (vector_cursor_members.h, included only by the unit that holds the
    // explicit instantiations, vector_cursor_ddtors.cpp), so that code driving a cursor calls them through the
    // vtable as retail does instead of expanding them.
    // Slot 1: is the index still below the vector's limit (unsigned compare).
    virtual bool vf_01();
    // Slots 2 and 3: step the index forward or back and return the cursor.
    virtual VectorCursor* vf_02();
    virtual VectorCursor* vf_03();

    Container* unknown_04;  // +0x04
    unsigned int unknown_08;  // +0x08
};

#endif  // GG_MATCH_CORE_VECTOR_CURSOR_H
