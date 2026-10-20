// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Raw PBVParticleSystemTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class ParticleSystemTypeClass;

// FUNCTION: GAMEMD 0x459F90
// DynamicVectorClass<const ParticleSystemTypeClass*>::Clear

// FUNCTION: GAMEMD 0x459FC0
// DynamicVectorClass<const ParticleSystemTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x459FE0
// VectorClass<const ParticleSystemTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x45A180
// VectorClass<const ParticleSystemTypeClass*>::operator==

// FUNCTION: GAMEMD 0x45A1C0
// VectorClass<const ParticleSystemTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45A270
// VectorClass<const ParticleSystemTypeClass*>::Clear

// FUNCTION: GAMEMD 0x45A2A0
// VectorClass<const ParticleSystemTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x45A2E0
// VectorClass<const ParticleSystemTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x45A300
// DynamicVectorClass<const ParticleSystemTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45A3B0
// DynamicVectorClass<const ParticleSystemTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x45A9C0
// VectorClass<const ParticleSystemTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x45AA10
// DynamicVectorClass<const ParticleSystemTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x45AD80
// VectorClass<const ParticleSystemTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x717AF0
// TypeList<const ParticleSystemTypeClass*>::default constructor

// SYNTHETIC: GAMEMD 0x717B70
// TypeList<const ParticleSystemTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x717C70
// DynamicVectorClass<const ParticleSystemTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x717D20
// TypeList<const ParticleSystemTypeClass*>::copy constructor

// VTABLE: GAMEMD 0x7E4424 -- VectorClass<const ParticleSystemTypeClass*>.
template class VectorClass<const ParticleSystemTypeClass*>;
typedef VectorClass<const ParticleSystemTypeClass*> GgParticleSystemTypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E4444 -- DynamicVectorClass<const ParticleSystemTypeClass*>.
template class DynamicVectorClass<const ParticleSystemTypeClass*>;
typedef DynamicVectorClass<const ParticleSystemTypeClass*> GgParticleSystemTypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7F4F9C -- TypeList<const ParticleSystemTypeClass*>.
template class TypeList<const ParticleSystemTypeClass*>;
typedef TypeList<const ParticleSystemTypeClass*> GgParticleSystemTypeTypeList;
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const ParticleSystemTypeClass*) == 4);
