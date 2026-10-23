// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAUHWND__ RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct HWND__;

// FUNCTION: GAMEMD 0x5D5080
// DynamicVectorClass<HWND__*>::Clear

// FUNCTION: GAMEMD 0x5D50B0
// DynamicVectorClass<HWND__*>::Slot5

// FUNCTION: GAMEMD 0x5D50D0
// VectorClass<HWND__*>::Slot6

// FUNCTION: GAMEMD 0x5D5150
// VectorClass<HWND__*>::operator==

// FUNCTION: GAMEMD 0x5D5190
// VectorClass<HWND__*>::SetCapacity

// FUNCTION: GAMEMD 0x5D5240
// VectorClass<HWND__*>::Clear

// FUNCTION: GAMEMD 0x5D5270
// VectorClass<HWND__*>::FindItemIndex

// FUNCTION: GAMEMD 0x5D52B0
// VectorClass<HWND__*>::Slot5

// FUNCTION: GAMEMD 0x5D52D0
// DynamicVectorClass<HWND__*>::SetCapacity

// FUNCTION: GAMEMD 0x5D5380
// DynamicVectorClass<HWND__*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5D56E0
// VectorClass<HWND__*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5D5730
// DynamicVectorClass<HWND__*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EECAC -- VectorClass<HWND__*>.
template class VectorClass<HWND__*>;
typedef VectorClass<HWND__*> GgHwndVectorClass;
GG_STATIC_ASSERT(offsetof(GgHwndVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgHwndVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgHwndVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgHwndVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EEC8C -- DynamicVectorClass<HWND__*>.
template class DynamicVectorClass<HWND__*>;
typedef DynamicVectorClass<HWND__*> GgHwndDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgHwndDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgHwndDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgHwndDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgHwndDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgHwndDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgHwndDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(HWND__*) == 4);
