// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVParticleSystemClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class ParticleSystemClass;

// FUNCTION: GAMEMD 0x4E8660
// DynamicVectorClass<ParticleSystemClass*>::Clear

// FUNCTION: GAMEMD 0x4E8690
// DynamicVectorClass<ParticleSystemClass*>::Slot5

// FUNCTION: GAMEMD 0x4E86B0
// VectorClass<ParticleSystemClass*>::Slot6

// FUNCTION: GAMEMD 0x4EAB40
// VectorClass<ParticleSystemClass*>::operator==

// FUNCTION: GAMEMD 0x4EAB80
// VectorClass<ParticleSystemClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EAC30
// VectorClass<ParticleSystemClass*>::Clear

// FUNCTION: GAMEMD 0x4EAC60
// VectorClass<ParticleSystemClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EACA0
// VectorClass<ParticleSystemClass*>::Slot5

// FUNCTION: GAMEMD 0x4EACC0
// DynamicVectorClass<ParticleSystemClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EAD70
// DynamicVectorClass<ParticleSystemClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EFB70
// VectorClass<ParticleSystemClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EFBC0
// DynamicVectorClass<ParticleSystemClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9C84 -- VectorClass<ParticleSystemClass*>.
template class VectorClass<ParticleSystemClass*>;
typedef VectorClass<ParticleSystemClass*> GgParticleSystemClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9C64 -- DynamicVectorClass<ParticleSystemClass*>.
template class DynamicVectorClass<ParticleSystemClass*>;
typedef DynamicVectorClass<ParticleSystemClass*> GgParticleSystemClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleSystemClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ParticleSystemClass*) == 4);
