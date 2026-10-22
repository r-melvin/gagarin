// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slot displacements and vtable addresses read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x43A600.
//
// BrainClass's destructor. 0x43A600 stores vtable 0x7E3E74, whose RTTI
// locator names BrainClass; that vtable has one slot, the deleting
// destructor 0x43AA90. The vector it tears down at +0x04 is reseated to
// 0x7E3E54, which RTTI names VectorClass<NeuronClass*>: a
// DynamicVectorClass<NeuronClass*> member, destroyed through the inline
// ~VectorClass because DynamicVectorClass has no destructor of its own.
//
// NeuronClass's primary vtable 0x7E3DF0 has its deleting destructor at slot 8
// (+0x20; 0x43A9C0 reseats the NeuronClass vtables and frees the object), so
// `delete` on an element is the `PUSH 1; CALL [EDX+0x20]` in 0x43A600. Its
// first eight slots are placeholders here; nothing in this TU calls them.
//
// small_misc38_methods.h models the same object's release loop (0x43A670) as
// an opaque prefix view; it is left as it is.
#ifndef GG_MATCH_CORE_VECTOR_OWNER_DTOR_METHODS_H
#define GG_MATCH_CORE_VECTOR_OWNER_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"

class NeuronClass
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0C();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual ~NeuronClass();   // +0x20
};

// VTABLE: GAMEMD 0x7E3E74 -- BrainClass
class BrainClass
{
public:
    // FUNCTION: GAMEMD 0x43A600
    virtual ~BrainClass();

    DynamicVectorClass<NeuronClass*> Neurons;   // +0x04
};

GG_STATIC_ASSERT(offsetof(BrainClass, Neurons) == 0x04);
GG_STATIC_ASSERT(sizeof(BrainClass) == 0x1C);

#endif  // GG_MATCH_CORE_VECTOR_OWNER_DTOR_METHODS_H
