// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVEMPulseClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class EMPulseClass;

// FUNCTION: GAMEMD 0x4C5B60
// DynamicVectorClass<EMPulseClass*>::Clear

// FUNCTION: GAMEMD 0x4C5B90
// DynamicVectorClass<EMPulseClass*>::Slot5

// FUNCTION: GAMEMD 0x4C5BB0
// VectorClass<EMPulseClass*>::Slot6

// FUNCTION: GAMEMD 0x4C5BC0
// VectorClass<EMPulseClass*>::operator==

// FUNCTION: GAMEMD 0x4C5C00
// VectorClass<EMPulseClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4C5CB0
// VectorClass<EMPulseClass*>::Clear

// FUNCTION: GAMEMD 0x4C5CE0
// VectorClass<EMPulseClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4C5D20
// VectorClass<EMPulseClass*>::Slot5

// FUNCTION: GAMEMD 0x4C5D40
// DynamicVectorClass<EMPulseClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4C5DF0
// DynamicVectorClass<EMPulseClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4C5E20
// VectorClass<EMPulseClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4C5E70
// DynamicVectorClass<EMPulseClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E875C -- VectorClass<EMPulseClass*>.
template class VectorClass<EMPulseClass*>;
typedef VectorClass<EMPulseClass*> GgEMPulseClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgEMPulseClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEMPulseClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEMPulseClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEMPulseClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E873C -- DynamicVectorClass<EMPulseClass*>.
template class DynamicVectorClass<EMPulseClass*>;
typedef DynamicVectorClass<EMPulseClass*> GgEMPulseClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgEMPulseClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEMPulseClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEMPulseClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEMPulseClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEMPulseClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEMPulseClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(EMPulseClass*) == 4);
