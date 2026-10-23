// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Raw PBVAircraftTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class AircraftTypeClass;

// FUNCTION: GAMEMD 0x512960
// TypeList<const AircraftTypeClass*>::default constructor

// FUNCTION: GAMEMD 0x512990
// DynamicVectorClass<const AircraftTypeClass*>::Clear

// FUNCTION: GAMEMD 0x5129C0
// DynamicVectorClass<const AircraftTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x5129E0
// VectorClass<const AircraftTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x512A90
// TypeList<const AircraftTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x512B80
// VectorClass<const AircraftTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5133E0
// VectorClass<const AircraftTypeClass*>::operator==

// FUNCTION: GAMEMD 0x513420
// VectorClass<const AircraftTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5134D0
// VectorClass<const AircraftTypeClass*>::Clear

// FUNCTION: GAMEMD 0x513500
// VectorClass<const AircraftTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x513540
// VectorClass<const AircraftTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x513560
// DynamicVectorClass<const AircraftTypeClass*>::capacity constructor

// SYNTHETIC: GAMEMD 0x5135C0
// DynamicVectorClass<const AircraftTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x513610
// DynamicVectorClass<const AircraftTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x513710
// DynamicVectorClass<const AircraftTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x5137D0
// TypeList<const AircraftTypeClass*>::copy constructor

// FUNCTION: GAMEMD 0x513990
// VectorClass<const AircraftTypeClass*>::capacity constructor

// VTABLE: GAMEMD 0x7EAC68 -- VectorClass<const AircraftTypeClass*>.
template class VectorClass<const AircraftTypeClass*>;
typedef VectorClass<const AircraftTypeClass*> GgAircrafttypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgAircrafttypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EACC8 -- DynamicVectorClass<const AircraftTypeClass*>.
template class DynamicVectorClass<const AircraftTypeClass*>;
typedef DynamicVectorClass<const AircraftTypeClass*> GgAircrafttypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAircrafttypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7EABC8 -- TypeList<const AircraftTypeClass*>.
template class TypeList<const AircraftTypeClass*>;
typedef TypeList<const AircraftTypeClass*> GgAircrafttypeTypeList;
GG_STATIC_ASSERT(offsetof(GgAircrafttypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAircrafttypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const AircraftTypeClass*) == 4);
