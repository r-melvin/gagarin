// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x829AF0 and 0x829B28 identify
// VectorClass<LightSourceClass*> and DynamicVectorClass<LightSourceClass*>; the latter's
// CHD names the former as its zero-offset base.
#include "vector_class_operations.h"
class LightSourceClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
// This specialization records the vector ABI, not the owning element class layout or original TU.
// No constructors were evidenced here. The size asserts describe these compiled vector models,
// not a complete owner object. Full spans match with /GX off; /GX shortens the dynamic
// scalar-deleting destructor. Vtable checks use conditional weak-default resolution, not final-link proof.

// FUNCTION: GAMEMD 0x555200
// DynamicVectorClass<LightSourceClass*>::Clear
// FUNCTION: GAMEMD 0x555230
// DynamicVectorClass<LightSourceClass*>::Slot5
// FUNCTION: GAMEMD 0x555250
// VectorClass<LightSourceClass*>::Slot6
// FUNCTION: GAMEMD 0x5552C0
// VectorClass<LightSourceClass*>::operator==
// FUNCTION: GAMEMD 0x555300
// VectorClass<LightSourceClass*>::SetCapacity
// FUNCTION: GAMEMD 0x5553B0
// VectorClass<LightSourceClass*>::Clear
// FUNCTION: GAMEMD 0x5553E0
// VectorClass<LightSourceClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x555420
// VectorClass<LightSourceClass*>::Slot5
// FUNCTION: GAMEMD 0x555440
// DynamicVectorClass<LightSourceClass*>::SetCapacity
// FUNCTION: GAMEMD 0x5554F0
// DynamicVectorClass<LightSourceClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x555780
// VectorClass<LightSourceClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x5557D0
// DynamicVectorClass<LightSourceClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7ECF9C -- VectorClass<LightSourceClass*>.
template class VectorClass<LightSourceClass*>;
// VTABLE: GAMEMD 0x7ECF7C -- DynamicVectorClass<LightSourceClass*>.
template class DynamicVectorClass<LightSourceClass*>;

typedef VectorClass<LightSourceClass*> GgLightSourceClassVector;
typedef DynamicVectorClass<LightSourceClass*> GgLightSourceClassDynamicVector;
GG_STATIC_ASSERT(sizeof(LightSourceClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgLightSourceClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgLightSourceClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, CapacityIncrement) == 0x14);
