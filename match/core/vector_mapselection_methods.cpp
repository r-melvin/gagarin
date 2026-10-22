// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x8303D8 and 0x830408 identify
// VectorClass<MapSelection*> and DynamicVectorClass<MapSelection*>; the latter's
// CHD names the former as its zero-offset base.
#include "vector_class_operations.h"
class MapSelection;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
// This specialization records the vector ABI, not the owning element class layout or original TU.
// No constructors were evidenced here. The size asserts describe these compiled vector models,
// not a complete owner object. Full spans match with /GX off; /GX shortens the dynamic
// scalar-deleting destructor. Vtable checks use conditional weak-default resolution, not final-link proof.

// FUNCTION: GAMEMD 0x5D0670
// DynamicVectorClass<MapSelection*>::Clear
// FUNCTION: GAMEMD 0x5D06A0
// DynamicVectorClass<MapSelection*>::Slot5
// FUNCTION: GAMEMD 0x5D06C0
// VectorClass<MapSelection*>::Slot6
// FUNCTION: GAMEMD 0x5D0D40
// VectorClass<MapSelection*>::operator==
// FUNCTION: GAMEMD 0x5D0D80
// VectorClass<MapSelection*>::SetCapacity
// FUNCTION: GAMEMD 0x5D0E30
// VectorClass<MapSelection*>::Clear
// FUNCTION: GAMEMD 0x5D0E60
// VectorClass<MapSelection*>::FindItemIndex
// FUNCTION: GAMEMD 0x5D0EA0
// VectorClass<MapSelection*>::Slot5
// FUNCTION: GAMEMD 0x5D0EC0
// DynamicVectorClass<MapSelection*>::SetCapacity
// FUNCTION: GAMEMD 0x5D0F70
// DynamicVectorClass<MapSelection*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x5D1800
// VectorClass<MapSelection*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x5D1850
// DynamicVectorClass<MapSelection*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EEBB4 -- VectorClass<MapSelection*>.
template class VectorClass<MapSelection*>;
// VTABLE: GAMEMD 0x7EEB14 -- DynamicVectorClass<MapSelection*>.
template class DynamicVectorClass<MapSelection*>;

typedef VectorClass<MapSelection*> GgMapSelectionVector;
typedef DynamicVectorClass<MapSelection*> GgMapSelectionDynamicVector;
GG_STATIC_ASSERT(sizeof(MapSelection*) == 4);
GG_STATIC_ASSERT(sizeof(GgMapSelectionVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapSelectionVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMapSelectionDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapSelectionDynamicVector, CapacityIncrement) == 0x14);
