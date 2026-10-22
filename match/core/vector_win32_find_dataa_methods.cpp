// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAU_WIN32_FIND_DATAA RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct _WIN32_FIND_DATAA;

// FUNCTION: GAMEMD 0x5AC4C0
// DynamicVectorClass<_WIN32_FIND_DATAA*>::Clear

// FUNCTION: GAMEMD 0x5AC4F0
// DynamicVectorClass<_WIN32_FIND_DATAA*>::Slot5

// FUNCTION: GAMEMD 0x5AC510
// VectorClass<_WIN32_FIND_DATAA*>::Slot6

// FUNCTION: GAMEMD 0x5ACA60
// VectorClass<_WIN32_FIND_DATAA*>::operator==

// FUNCTION: GAMEMD 0x5ACAA0
// VectorClass<_WIN32_FIND_DATAA*>::SetCapacity

// FUNCTION: GAMEMD 0x5ACB50
// VectorClass<_WIN32_FIND_DATAA*>::Clear

// FUNCTION: GAMEMD 0x5ACB80
// VectorClass<_WIN32_FIND_DATAA*>::FindItemIndex

// FUNCTION: GAMEMD 0x5ACBC0
// VectorClass<_WIN32_FIND_DATAA*>::Slot5

// FUNCTION: GAMEMD 0x5ACBE0
// DynamicVectorClass<_WIN32_FIND_DATAA*>::SetCapacity

// FUNCTION: GAMEMD 0x5ACC90
// DynamicVectorClass<_WIN32_FIND_DATAA*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5AD430
// VectorClass<_WIN32_FIND_DATAA*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5AD480
// DynamicVectorClass<_WIN32_FIND_DATAA*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7ED92C -- VectorClass<_WIN32_FIND_DATAA*>.
template class VectorClass<_WIN32_FIND_DATAA*>;
typedef VectorClass<_WIN32_FIND_DATAA*> GgWin32FindDataaVectorClass;
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ED94C -- DynamicVectorClass<_WIN32_FIND_DATAA*>.
template class DynamicVectorClass<_WIN32_FIND_DATAA*>;
typedef DynamicVectorClass<_WIN32_FIND_DATAA*> GgWin32FindDataaDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(_WIN32_FIND_DATAA*) == 4);
