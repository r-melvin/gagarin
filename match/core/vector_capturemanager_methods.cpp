// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x81B5E8 and 0x81B620 identify
// VectorClass<CaptureManagerClass*> and DynamicVectorClass<CaptureManagerClass*>;
// the latter's CHD gives the former as a zero-offset base. Complete entry-origin
// spans bind these methods; no standalone constructor or original TU is claimed.
// GX shortens the derived deleting wrapper; no GX matches its full retail body.
#include "vector_class_operations.h"
#include "../_layout/capture_manager_class.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x472AE0
// DynamicVectorClass<CaptureManagerClass*>::Clear
// FUNCTION: GAMEMD 0x472B10
// DynamicVectorClass<CaptureManagerClass*>::Slot5
// FUNCTION: GAMEMD 0x472B30
// VectorClass<CaptureManagerClass*>::Slot6
// FUNCTION: GAMEMD 0x472DA0
// VectorClass<CaptureManagerClass*>::operator==
// FUNCTION: GAMEMD 0x472DE0
// VectorClass<CaptureManagerClass*>::SetCapacity
// FUNCTION: GAMEMD 0x472E90
// VectorClass<CaptureManagerClass*>::Clear
// FUNCTION: GAMEMD 0x472EC0
// VectorClass<CaptureManagerClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x472F00
// VectorClass<CaptureManagerClass*>::Slot5
// FUNCTION: GAMEMD 0x472F20
// DynamicVectorClass<CaptureManagerClass*>::SetCapacity
// FUNCTION: GAMEMD 0x472FD0
// DynamicVectorClass<CaptureManagerClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x4730A0
// VectorClass<CaptureManagerClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x4730F0
// DynamicVectorClass<CaptureManagerClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E4AF4 -- VectorClass<CaptureManagerClass*>.
template class VectorClass<CaptureManagerClass*>;
// VTABLE: GAMEMD 0x7E4AD4 -- DynamicVectorClass<CaptureManagerClass*>.
template class DynamicVectorClass<CaptureManagerClass*>;

typedef VectorClass<CaptureManagerClass*> GgCaptureManagerVector;
typedef DynamicVectorClass<CaptureManagerClass*> GgCaptureManagerDynamicVector;
GG_STATIC_ASSERT(sizeof(CaptureManagerClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgCaptureManagerVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgCaptureManagerDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, CapacityIncrement) == 0x14);
