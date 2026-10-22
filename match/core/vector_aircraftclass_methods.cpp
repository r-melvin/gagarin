// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVAircraftClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class AircraftClass;

// FUNCTION: GAMEMD 0x4E8840
// DynamicVectorClass<AircraftClass*>::Clear

// FUNCTION: GAMEMD 0x4E8870
// DynamicVectorClass<AircraftClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8890
// VectorClass<AircraftClass*>::Slot6

// FUNCTION: GAMEMD 0x4EB720
// VectorClass<AircraftClass*>::operator==

// FUNCTION: GAMEMD 0x4EB760
// VectorClass<AircraftClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EB810
// VectorClass<AircraftClass*>::Clear

// FUNCTION: GAMEMD 0x4EB840
// VectorClass<AircraftClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EB880
// VectorClass<AircraftClass*>::Slot5

// FUNCTION: GAMEMD 0x4EB8A0
// DynamicVectorClass<AircraftClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EB950
// DynamicVectorClass<AircraftClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EFE90
// VectorClass<AircraftClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EFEE0
// DynamicVectorClass<AircraftClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9E84 -- VectorClass<AircraftClass*>.
template class VectorClass<AircraftClass*>;
typedef VectorClass<AircraftClass*> GgAircraftClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgAircraftClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircraftClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircraftClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircraftClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9E64 -- DynamicVectorClass<AircraftClass*>.
template class DynamicVectorClass<AircraftClass*>;
typedef DynamicVectorClass<AircraftClass*> GgAircraftClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAircraftClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircraftClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircraftClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircraftClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAircraftClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAircraftClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(AircraftClass*) == 4);
