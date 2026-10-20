// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX
// Entry-origin bodies and PBV RTTI establish const pointer elements and the
// zero-offset DynamicVectorClass -> VectorClass base chain. GX reproduces
// these constructors and retains the existing pointer cluster's
// duplicate COMDAT bodies. Original TU grouping and final-link selection are
// unknown. Extra emitted methods and complete derived sizes are unclaimed.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class SmudgeTypeClass;

// FUNCTION: GAMEMD 0x67AFF0
// DynamicVectorClass<const SmudgeTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7F0DEC -- DynamicVectorClass<const SmudgeTypeClass*>.
template class DynamicVectorClass<const SmudgeTypeClass*>;
typedef DynamicVectorClass<const SmudgeTypeClass*> GgSmudgeTypeCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityDynamic, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const SmudgeTypeClass*) == 4);

// FUNCTION: GAMEMD 0x67C3A0
// VectorClass<const SmudgeTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7F0D7C -- VectorClass<const SmudgeTypeClass*>.
template class VectorClass<const SmudgeTypeClass*>;
typedef VectorClass<const SmudgeTypeClass*> GgSmudgeTypeCapacityBase;
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeCapacityBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(const SmudgeTypeClass*) == 4);
