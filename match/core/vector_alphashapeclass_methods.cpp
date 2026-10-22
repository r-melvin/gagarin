// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x818238 and 0x818270 identify
// VectorClass<AlphaShapeClass*> and DynamicVectorClass<AlphaShapeClass*>; the latter's
// CHD names the former as its zero-offset base.
// Complete entry spans bind these methods. Original TUs and standalone
// constructors are unestablished; the derived deleting body needs GX off.
#include "vector_class_operations.h"
class AlphaShapeClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x421800
// DynamicVectorClass<AlphaShapeClass*>::Clear
// FUNCTION: GAMEMD 0x421830
// DynamicVectorClass<AlphaShapeClass*>::Slot5
// FUNCTION: GAMEMD 0x421850
// VectorClass<AlphaShapeClass*>::Slot6
// FUNCTION: GAMEMD 0x421860
// VectorClass<AlphaShapeClass*>::operator==
// FUNCTION: GAMEMD 0x4218A0
// VectorClass<AlphaShapeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x421950
// VectorClass<AlphaShapeClass*>::Clear
// FUNCTION: GAMEMD 0x421980
// VectorClass<AlphaShapeClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x4219C0
// VectorClass<AlphaShapeClass*>::Slot5
// FUNCTION: GAMEMD 0x4219E0
// DynamicVectorClass<AlphaShapeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x421A90
// DynamicVectorClass<AlphaShapeClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x421AC0
// VectorClass<AlphaShapeClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x421B10
// DynamicVectorClass<AlphaShapeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E3258 -- VectorClass<AlphaShapeClass*>.
template class VectorClass<AlphaShapeClass*>;
// VTABLE: GAMEMD 0x7E3238 -- DynamicVectorClass<AlphaShapeClass*>.
template class DynamicVectorClass<AlphaShapeClass*>;

typedef VectorClass<AlphaShapeClass*> GgAlphaShapeVector;
typedef DynamicVectorClass<AlphaShapeClass*> GgAlphaShapeDynamicVector;
GG_STATIC_ASSERT(sizeof(AlphaShapeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgAlphaShapeVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgAlphaShapeDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, CapacityIncrement) == 0x14);
