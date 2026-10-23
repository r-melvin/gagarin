// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAU_DDSURFACEDESC RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct _DDSURFACEDESC;

// FUNCTION: GAMEMD 0x4A4AD0
// DynamicVectorClass<_DDSURFACEDESC*>::Clear

// FUNCTION: GAMEMD 0x4A4B00
// DynamicVectorClass<_DDSURFACEDESC*>::Slot5

// FUNCTION: GAMEMD 0x4A4B20
// VectorClass<_DDSURFACEDESC*>::Slot6

// FUNCTION: GAMEMD 0x4A4B30
// VectorClass<_DDSURFACEDESC*>::operator==

// FUNCTION: GAMEMD 0x4A4B70
// VectorClass<_DDSURFACEDESC*>::SetCapacity

// FUNCTION: GAMEMD 0x4A4C20
// VectorClass<_DDSURFACEDESC*>::Clear

// FUNCTION: GAMEMD 0x4A4C50
// VectorClass<_DDSURFACEDESC*>::FindItemIndex

// FUNCTION: GAMEMD 0x4A4C90
// VectorClass<_DDSURFACEDESC*>::Slot5

// FUNCTION: GAMEMD 0x4A4CB0
// DynamicVectorClass<_DDSURFACEDESC*>::SetCapacity

// FUNCTION: GAMEMD 0x4A4D60
// DynamicVectorClass<_DDSURFACEDESC*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4A4D90
// VectorClass<_DDSURFACEDESC*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4A4DE0
// DynamicVectorClass<_DDSURFACEDESC*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E5DEC -- VectorClass<_DDSURFACEDESC*>.
template class VectorClass<_DDSURFACEDESC*>;
typedef VectorClass<_DDSURFACEDESC*> GgDdsurfacedescVectorClass;
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E5E0C -- DynamicVectorClass<_DDSURFACEDESC*>.
template class DynamicVectorClass<_DDSURFACEDESC*>;
typedef DynamicVectorClass<_DDSURFACEDESC*> GgDdsurfacedescDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgDdsurfacedescDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(_DDSURFACEDESC*) == 4);
