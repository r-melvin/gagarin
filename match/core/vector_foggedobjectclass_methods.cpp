// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVFoggedObjectClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class FoggedObjectClass;

// FUNCTION: GAMEMD 0x45A070
// DynamicVectorClass<FoggedObjectClass*>::Clear

// FUNCTION: GAMEMD 0x45A0A0
// DynamicVectorClass<FoggedObjectClass*>::Slot5

// FUNCTION: GAMEMD 0x45A0C0
// VectorClass<FoggedObjectClass*>::Slot6

// FUNCTION: GAMEMD 0x45A640
// VectorClass<FoggedObjectClass*>::operator==

// FUNCTION: GAMEMD 0x45A680
// DynamicVectorClass<FoggedObjectClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45A730
// DynamicVectorClass<FoggedObjectClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x45AB00
// DynamicVectorClass<FoggedObjectClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x45AB50
// VectorClass<FoggedObjectClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45AC00
// VectorClass<FoggedObjectClass*>::Clear

// FUNCTION: GAMEMD 0x45AC30
// VectorClass<FoggedObjectClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x45AC70
// VectorClass<FoggedObjectClass*>::Slot5

// SYNTHETIC: GAMEMD 0x45AC90
// VectorClass<FoggedObjectClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E4514 -- VectorClass<FoggedObjectClass*>.
template class VectorClass<FoggedObjectClass*>;
typedef VectorClass<FoggedObjectClass*> GgFoggedObjectClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E44F4 -- DynamicVectorClass<FoggedObjectClass*>.
template class DynamicVectorClass<FoggedObjectClass*>;
typedef DynamicVectorClass<FoggedObjectClass*> GgFoggedObjectClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(FoggedObjectClass*) == 4);
