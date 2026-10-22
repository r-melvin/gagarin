// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVParticleSystemTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class ParticleSystemTypeClass;

// FUNCTION: GAMEMD 0x4E90E0
// DynamicVectorClass<ParticleSystemTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E9110
// DynamicVectorClass<ParticleSystemTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E9130
// VectorClass<ParticleSystemTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EEDC0
// VectorClass<ParticleSystemTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EEE00
// VectorClass<ParticleSystemTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EEEB0
// VectorClass<ParticleSystemTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EEEE0
// VectorClass<ParticleSystemTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EEF20
// VectorClass<ParticleSystemTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EEF40
// DynamicVectorClass<ParticleSystemTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EEFF0
// DynamicVectorClass<ParticleSystemTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0CF0
// VectorClass<ParticleSystemTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0D40
// DynamicVectorClass<ParticleSystemTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA484 -- VectorClass<ParticleSystemTypeClass*>.
template class VectorClass<ParticleSystemTypeClass*>;
typedef VectorClass<ParticleSystemTypeClass*> GgParticleSystemTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA464 -- DynamicVectorClass<ParticleSystemTypeClass*>.
template class DynamicVectorClass<ParticleSystemTypeClass*>;
typedef DynamicVectorClass<ParticleSystemTypeClass*> GgParticleSystemTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ParticleSystemTypeClass*) == 4);
