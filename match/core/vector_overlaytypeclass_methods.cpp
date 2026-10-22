// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVOverlayTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class OverlayTypeClass;

// FUNCTION: GAMEMD 0x4E8C60
// DynamicVectorClass<OverlayTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8C90
// DynamicVectorClass<OverlayTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8CB0
// VectorClass<OverlayTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4ED140
// VectorClass<OverlayTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4ED180
// VectorClass<OverlayTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ED230
// VectorClass<OverlayTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4ED260
// VectorClass<OverlayTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4ED2A0
// VectorClass<OverlayTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4ED2C0
// DynamicVectorClass<OverlayTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ED370
// DynamicVectorClass<OverlayTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0570
// VectorClass<OverlayTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F05C0
// DynamicVectorClass<OverlayTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA184 -- VectorClass<OverlayTypeClass*>.
template class VectorClass<OverlayTypeClass*>;
typedef VectorClass<OverlayTypeClass*> GgOverlayTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA164 -- DynamicVectorClass<OverlayTypeClass*>.
template class DynamicVectorClass<OverlayTypeClass*>;
typedef DynamicVectorClass<OverlayTypeClass*> GgOverlayTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgOverlayTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(OverlayTypeClass*) == 4);
