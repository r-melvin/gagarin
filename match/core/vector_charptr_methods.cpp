// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. Direct retail RTTI confirms the non-const
// char* specialization and its zero-offset dynamic base. All entry-origin
// spans and both seven-slot address points are verified against the pinned PE.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// The DynamicVectorClass deleting-dtor full span requires /GX disabled; other
// methods are tested independently. Vtable weak defaults are conditional, not
// final-link proof. The separate const-char* family is not described here.
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x0049E950
// FUNCTION: GAMEMD 0x0049E980
// FUNCTION: GAMEMD 0x0049E9A0
// FUNCTION: GAMEMD 0x0049EA30
// FUNCTION: GAMEMD 0x0049EA70
// FUNCTION: GAMEMD 0x0049EB20
// FUNCTION: GAMEMD 0x0049EE10
// FUNCTION: GAMEMD 0x0049EE60
// FUNCTION: GAMEMD 0x0049EF10
// FUNCTION: GAMEMD 0x0049EF40
// FUNCTION: GAMEMD 0x0049EF80
// FUNCTION: GAMEMD 0x0049EFA0
template class VectorClass<char*>;
template class DynamicVectorClass<char*>;

// VTABLE: GAMEMD 0x007E5BC4 -- DynamicVectorClass<char*>.
// VTABLE: GAMEMD 0x007E5C24 -- VectorClass<char*>.
typedef VectorClass<char*> GgCharPtrVector;
typedef DynamicVectorClass<char*> GgCharPtrDynamicVector;
GG_STATIC_ASSERT(sizeof(char*) == 4);
GG_STATIC_ASSERT(sizeof(GgCharPtrVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgCharPtrDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, CapacityIncrement) == 0x14);
