// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. Direct retail RTTI names the two types
// and confirms DynamicVectorClass<DynamicVectorClass<char*>*> derives from
// VectorClass<DynamicVectorClass<char*>*> at offset zero. Entry-origin spans
// and both seven-slot address points were checked against the pinned PE.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// The dynamic deleting-dtor full span needs /GX disabled; the remaining
// tested bodies are exact with /GX as well. Vtable weak defaults are conditional
// slot evidence, not final-link proof. The capacity constructors replace
// address-bound PodElem4 stand-ins; no complete pointee-layout or original-TU
// claim is made.
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x0049E9B0
// FUNCTION: GAMEMD 0x0049E9E0
// FUNCTION: GAMEMD 0x0049EA00
// FUNCTION: GAMEMD 0x0049EB50
// FUNCTION: GAMEMD 0x0049EB90
// FUNCTION: GAMEMD 0x0049EC40
// FUNCTION: GAMEMD 0x0049EC70
// FUNCTION: GAMEMD 0x0049ECB0
// FUNCTION: GAMEMD 0x0049ECD0
// FUNCTION: GAMEMD 0x0049ED30
// FUNCTION: GAMEMD 0x0049EDE0
// FUNCTION: GAMEMD 0x0049EFF0
// FUNCTION: GAMEMD 0x0049F040
// FUNCTION: GAMEMD 0x0049F090
template class VectorClass<DynamicVectorClass<char*>*>;
template class DynamicVectorClass<DynamicVectorClass<char*>*>;

// VTABLE: GAMEMD 0x007E5BE4 -- DynamicVectorClass<DynamicVectorClass<char*>*>.
// VTABLE: GAMEMD 0x007E5C04 -- VectorClass<DynamicVectorClass<char*>*>.
typedef VectorClass<DynamicVectorClass<char*>*> GgNestedCharVector;
typedef DynamicVectorClass<DynamicVectorClass<char*>*> GgNestedCharDynamicVector;
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<char*>*) == 4);
GG_STATIC_ASSERT(sizeof(GgNestedCharVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgNestedCharDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, CapacityIncrement) == 0x14);
