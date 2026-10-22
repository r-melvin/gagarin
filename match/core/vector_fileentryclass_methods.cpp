// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVFileEntryClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class FileEntryClass;

// FUNCTION: GAMEMD 0x55A150
// DynamicVectorClass<FileEntryClass*>::Clear

// FUNCTION: GAMEMD 0x55A180
// DynamicVectorClass<FileEntryClass*>::Slot5

// FUNCTION: GAMEMD 0x55A1A0
// VectorClass<FileEntryClass*>::Slot6

// FUNCTION: GAMEMD 0x55A1B0
// VectorClass<FileEntryClass*>::operator==

// FUNCTION: GAMEMD 0x55A1F0
// VectorClass<FileEntryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x55A2A0
// VectorClass<FileEntryClass*>::Clear

// FUNCTION: GAMEMD 0x55A2D0
// VectorClass<FileEntryClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x55A310
// VectorClass<FileEntryClass*>::Slot5

// FUNCTION: GAMEMD 0x55A330
// DynamicVectorClass<FileEntryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x55A3E0
// DynamicVectorClass<FileEntryClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x55A410
// VectorClass<FileEntryClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x55A460
// DynamicVectorClass<FileEntryClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7ED32C -- VectorClass<FileEntryClass*>.
template class VectorClass<FileEntryClass*>;
typedef VectorClass<FileEntryClass*> GgFileEntryClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgFileEntryClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ED30C -- DynamicVectorClass<FileEntryClass*>.
template class DynamicVectorClass<FileEntryClass*>;
typedef DynamicVectorClass<FileEntryClass*> GgFileEntryClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(FileEntryClass*) == 4);
