// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVAircraftTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class AircraftTypeClass;

// FUNCTION: GAMEMD 0x4E8DE0
// DynamicVectorClass<AircraftTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8E10
// DynamicVectorClass<AircraftTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8E30
// VectorClass<AircraftTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EDAC0
// VectorClass<AircraftTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EDB00
// VectorClass<AircraftTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EDBB0
// VectorClass<AircraftTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EDBE0
// VectorClass<AircraftTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EDC20
// VectorClass<AircraftTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EDC40
// DynamicVectorClass<AircraftTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EDCF0
// DynamicVectorClass<AircraftTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F07F0
// VectorClass<AircraftTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0840
// DynamicVectorClass<AircraftTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA284 -- VectorClass<AircraftTypeClass*>.
template class VectorClass<AircraftTypeClass*>;
typedef VectorClass<AircraftTypeClass*> GgAircraftTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA264 -- DynamicVectorClass<AircraftTypeClass*>.
template class DynamicVectorClass<AircraftTypeClass*>;
typedef DynamicVectorClass<AircraftTypeClass*> GgAircraftTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(AircraftTypeClass*) == 4);
