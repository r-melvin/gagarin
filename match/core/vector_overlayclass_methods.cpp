// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVOverlayClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class OverlayClass;

// FUNCTION: GAMEMD 0x4E8720
// DynamicVectorClass<OverlayClass*>::Clear

// FUNCTION: GAMEMD 0x4E8750
// DynamicVectorClass<OverlayClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8770
// VectorClass<OverlayClass*>::Slot6

// FUNCTION: GAMEMD 0x4EB000
// VectorClass<OverlayClass*>::operator==

// FUNCTION: GAMEMD 0x4EB040
// VectorClass<OverlayClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EB0F0
// VectorClass<OverlayClass*>::Clear

// FUNCTION: GAMEMD 0x4EB120
// VectorClass<OverlayClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EB160
// VectorClass<OverlayClass*>::Slot5

// FUNCTION: GAMEMD 0x4EB180
// DynamicVectorClass<OverlayClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EB230
// DynamicVectorClass<OverlayClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EFCB0
// VectorClass<OverlayClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EFD00
// DynamicVectorClass<OverlayClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9D44 -- VectorClass<OverlayClass*>.
template class VectorClass<OverlayClass*>;
typedef VectorClass<OverlayClass*> GgOverlayClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgOverlayClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgOverlayClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgOverlayClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgOverlayClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9D24 -- DynamicVectorClass<OverlayClass*>.
template class DynamicVectorClass<OverlayClass*>;
typedef DynamicVectorClass<OverlayClass*> GgOverlayClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgOverlayClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgOverlayClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgOverlayClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgOverlayClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgOverlayClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgOverlayClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(OverlayClass*) == 4);
