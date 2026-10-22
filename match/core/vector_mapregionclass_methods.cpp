// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVMapRegionClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class MapRegionClass;

// FUNCTION: GAMEMD 0x5AC3A0
// DynamicVectorClass<MapRegionClass*>::Clear

// FUNCTION: GAMEMD 0x5AC3D0
// DynamicVectorClass<MapRegionClass*>::Slot5

// FUNCTION: GAMEMD 0x5AC3F0
// VectorClass<MapRegionClass*>::Slot6

// FUNCTION: GAMEMD 0x5AC6A0
// VectorClass<MapRegionClass*>::operator==

// FUNCTION: GAMEMD 0x5AC6E0
// VectorClass<MapRegionClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5AC790
// VectorClass<MapRegionClass*>::Clear

// FUNCTION: GAMEMD 0x5AC7C0
// VectorClass<MapRegionClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x5AC800
// VectorClass<MapRegionClass*>::Slot5

// FUNCTION: GAMEMD 0x5AC820
// DynamicVectorClass<MapRegionClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5AC8D0
// DynamicVectorClass<MapRegionClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5AD390
// VectorClass<MapRegionClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5AD3E0
// DynamicVectorClass<MapRegionClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7ED878 -- VectorClass<MapRegionClass*>.
template class VectorClass<MapRegionClass*>;
typedef VectorClass<MapRegionClass*> GgMapregionclassVectorClass;
GG_STATIC_ASSERT(offsetof(GgMapregionclassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapregionclassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapregionclassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapregionclassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ED858 -- DynamicVectorClass<MapRegionClass*>.
template class DynamicVectorClass<MapRegionClass*>;
typedef DynamicVectorClass<MapRegionClass*> GgMapregionclassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(MapRegionClass*) == 4);
