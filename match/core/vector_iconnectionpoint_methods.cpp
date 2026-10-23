// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAUIConnectionPoint RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct IConnectionPoint;

// SYNTHETIC: GAMEMD 0x4A0E60
// DynamicVectorClass<IConnectionPoint*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x4A0F20
// DynamicVectorClass<IConnectionPoint*>::Clear

// FUNCTION: GAMEMD 0x4A0F50
// DynamicVectorClass<IConnectionPoint*>::Slot5

// FUNCTION: GAMEMD 0x4A0F70
// VectorClass<IConnectionPoint*>::Slot6

// FUNCTION: GAMEMD 0x4A1240
// VectorClass<IConnectionPoint*>::operator==

// FUNCTION: GAMEMD 0x4A1280
// VectorClass<IConnectionPoint*>::SetCapacity

// FUNCTION: GAMEMD 0x4A1330
// VectorClass<IConnectionPoint*>::Clear

// FUNCTION: GAMEMD 0x4A1360
// VectorClass<IConnectionPoint*>::FindItemIndex

// FUNCTION: GAMEMD 0x4A13A0
// VectorClass<IConnectionPoint*>::Slot5

// FUNCTION: GAMEMD 0x4A13C0
// DynamicVectorClass<IConnectionPoint*>::SetCapacity

// FUNCTION: GAMEMD 0x4A1470
// DynamicVectorClass<IConnectionPoint*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4A14F0
// VectorClass<IConnectionPoint*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E5D08 -- VectorClass<IConnectionPoint*>.
template class VectorClass<IConnectionPoint*>;
typedef VectorClass<IConnectionPoint*> GgIconnectionpointVectorClass;
GG_STATIC_ASSERT(offsetof(GgIconnectionpointVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgIconnectionpointVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgIconnectionpointVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgIconnectionpointVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E5D48 -- DynamicVectorClass<IConnectionPoint*>.
template class DynamicVectorClass<IConnectionPoint*>;
typedef DynamicVectorClass<IConnectionPoint*> GgIconnectionpointDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgIconnectionpointDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgIconnectionpointDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgIconnectionpointDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgIconnectionpointDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgIconnectionpointDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgIconnectionpointDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(IConnectionPoint*) == 4);
