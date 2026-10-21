// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x8181B8 and 0x8181F8 identify
// VectorClass<AlphaLightingRemapClass*> and DynamicVectorClass<AlphaLightingRemapClass*>; the latter's
// CHD names the former as its zero-offset base.
// Full entry spans bind these methods; original TUs and standalone constructors
// are not established. No GX matches the complete derived deleting wrapper.
#include "vector_class_operations.h"
class AlphaLightingRemapClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x420370
// DynamicVectorClass<AlphaLightingRemapClass*>::Clear
// FUNCTION: GAMEMD 0x4203A0
// DynamicVectorClass<AlphaLightingRemapClass*>::Slot5
// FUNCTION: GAMEMD 0x4203C0
// VectorClass<AlphaLightingRemapClass*>::Slot6
// FUNCTION: GAMEMD 0x4203D0
// VectorClass<AlphaLightingRemapClass*>::operator==
// FUNCTION: GAMEMD 0x420410
// VectorClass<AlphaLightingRemapClass*>::SetCapacity
// FUNCTION: GAMEMD 0x4204C0
// VectorClass<AlphaLightingRemapClass*>::Clear
// FUNCTION: GAMEMD 0x4204F0
// VectorClass<AlphaLightingRemapClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x420530
// VectorClass<AlphaLightingRemapClass*>::Slot5
// FUNCTION: GAMEMD 0x420550
// DynamicVectorClass<AlphaLightingRemapClass*>::SetCapacity
// FUNCTION: GAMEMD 0x420600
// DynamicVectorClass<AlphaLightingRemapClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x420630
// VectorClass<AlphaLightingRemapClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x420680
// DynamicVectorClass<AlphaLightingRemapClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E2AF0 -- VectorClass<AlphaLightingRemapClass*>.
template class VectorClass<AlphaLightingRemapClass*>;
// VTABLE: GAMEMD 0x7E2AD0 -- DynamicVectorClass<AlphaLightingRemapClass*>.
template class DynamicVectorClass<AlphaLightingRemapClass*>;

typedef VectorClass<AlphaLightingRemapClass*> GgAlphaLightingRemapVector;
typedef DynamicVectorClass<AlphaLightingRemapClass*> GgAlphaLightingRemapDynamicVector;
GG_STATIC_ASSERT(sizeof(AlphaLightingRemapClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgAlphaLightingRemapVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgAlphaLightingRemapDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, CapacityIncrement) == 0x14);
