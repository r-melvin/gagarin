// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI names eight ".?AV?$VectorCursor@<T><Container>@@" classes. Each is a
//   polymorphic cursor over a vector: the vptr, the vector pointer at +0x04 and the
//   index at +0x08. The constructors at 0x76F090 and 0x76F0C0 store both arguments
//   (vector, then index) before the vptr; the slot 2 and slot 3 bodies (0x4F3FF0,
//   0x4F4000, 0x76A5A0, 0x76A5B0) increment and decrement the +0x08 word. The
//   scalar deleting destructors are empty virtual ones (vector_cursor_ddtors.cpp).
#ifndef GG_MATCH_CORE_VECTOR_CURSOR_H
#define GG_MATCH_CORE_VECTOR_CURSOR_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

template <class T, class Container>
class VectorCursor
{
public:
    VectorCursor() {}
    VectorCursor(Container* vector, int index) : unknown_04(vector), unknown_08(index) {}
    virtual ~VectorCursor() {}

    Container* unknown_04;  // +0x04
    int unknown_08;         // +0x08
};

#endif  // GG_MATCH_CORE_VECTOR_CURSOR_H
