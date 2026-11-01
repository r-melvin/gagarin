// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVWaypointPathClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class WaypointPathClass;

// FUNCTION: GAMEMD 0x763F90
// DynamicVectorClass<WaypointPathClass*>::Clear

// FUNCTION: GAMEMD 0x763FC0
// DynamicVectorClass<WaypointPathClass*>::Slot5

// FUNCTION: GAMEMD 0x763FE0
// VectorClass<WaypointPathClass*>::Slot6

// FUNCTION: GAMEMD 0x764460
// VectorClass<WaypointPathClass*>::operator==

// FUNCTION: GAMEMD 0x7644A0
// VectorClass<WaypointPathClass*>::SetCapacity

// FUNCTION: GAMEMD 0x764550
// VectorClass<WaypointPathClass*>::Clear

// FUNCTION: GAMEMD 0x764580
// VectorClass<WaypointPathClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x7645C0
// VectorClass<WaypointPathClass*>::Slot5

// FUNCTION: GAMEMD 0x7645E0
// DynamicVectorClass<WaypointPathClass*>::SetCapacity

// FUNCTION: GAMEMD 0x764690
// DynamicVectorClass<WaypointPathClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x7646C0
// VectorClass<WaypointPathClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x764710
// DynamicVectorClass<WaypointPathClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F6E24 -- VectorClass<WaypointPathClass*>.
template class VectorClass<WaypointPathClass*>;
typedef VectorClass<WaypointPathClass*> GgWaypointPathClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F6E04 -- DynamicVectorClass<WaypointPathClass*>.
template class DynamicVectorClass<WaypointPathClass*>;
typedef DynamicVectorClass<WaypointPathClass*> GgWaypointPathClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgWaypointPathClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(WaypointPathClass*) == 4);
