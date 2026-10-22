// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x823108 and 0x823138 identify
// VectorClass<ParticleClass*> and DynamicVectorClass<ParticleClass*>; the latter's
// CHD names the former as its zero-offset base.
#include "vector_class_operations.h"
class ParticleClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
// This specialization records the vector ABI, not the owning element class layout or original TU.
// No constructors were evidenced here. The size asserts describe these compiled vector models,
// not a complete owner object. Full spans match with /GX off; /GX shortens the dynamic
// scalar-deleting destructor. Vtable checks use conditional weak-default resolution, not final-link proof.

// FUNCTION: GAMEMD 0x4E8470
// DynamicVectorClass<ParticleClass*>::Clear
// FUNCTION: GAMEMD 0x4E84A0
// DynamicVectorClass<ParticleClass*>::Slot5
// FUNCTION: GAMEMD 0x4E84C0
// VectorClass<ParticleClass*>::Slot6
// FUNCTION: GAMEMD 0x4E9DE0
// VectorClass<ParticleClass*>::operator==
// FUNCTION: GAMEMD 0x4E9E20
// VectorClass<ParticleClass*>::SetCapacity
// FUNCTION: GAMEMD 0x4E9ED0
// VectorClass<ParticleClass*>::Clear
// FUNCTION: GAMEMD 0x4E9F00
// VectorClass<ParticleClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x4E9F40
// VectorClass<ParticleClass*>::Slot5
// FUNCTION: GAMEMD 0x4E9F60
// DynamicVectorClass<ParticleClass*>::SetCapacity
// FUNCTION: GAMEMD 0x4EA010
// DynamicVectorClass<ParticleClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x4EF800
// VectorClass<ParticleClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x4EF850
// DynamicVectorClass<ParticleClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9D84 -- VectorClass<ParticleClass*>.
template class VectorClass<ParticleClass*>;
// VTABLE: GAMEMD 0x7E9D64 -- DynamicVectorClass<ParticleClass*>.
template class DynamicVectorClass<ParticleClass*>;

typedef VectorClass<ParticleClass*> GgParticleClassVector;
typedef DynamicVectorClass<ParticleClass*> GgParticleClassDynamicVector;
GG_STATIC_ASSERT(sizeof(ParticleClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgParticleClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgParticleClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgParticleClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgParticleClassDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleClassDynamicVector, CapacityIncrement) == 0x14);
