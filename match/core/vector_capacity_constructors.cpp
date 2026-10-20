// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX
// Entry-origin bodies and PBV RTTI establish const pointer elements and the
// zero-offset DynamicVectorClass -> VectorClass base chain. Both GX and no-GX
// reproduce these constructors; GX retains the existing pointer cluster's
// duplicate COMDAT bodies. Original TU grouping and final-link selection are
// unknown. Extra emitted methods and complete derived sizes are unclaimed.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class AnimTypeClass;
class BuildingTypeClass;

// FUNCTION: GAMEMD 0x5105A0
// VectorClass<const BuildingTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EAA08 -- VectorClass<const BuildingTypeClass*>.
template class VectorClass<const BuildingTypeClass*>;
typedef VectorClass<const BuildingTypeClass*> GgBuildingCapacityBase;
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, IsAllocated) == 0x0D);

// FUNCTION: GAMEMD 0x525250
// DynamicVectorClass<const AnimTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EB714 -- DynamicVectorClass<const AnimTypeClass*>.
template class DynamicVectorClass<const AnimTypeClass*>;
typedef DynamicVectorClass<const AnimTypeClass*> GgAnimCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgAnimCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimCapacityDynamic, CapacityIncrement) == 0x14);

// FUNCTION: GAMEMD 0x525680
// VectorClass<const AnimTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EB6F4 -- VectorClass<const AnimTypeClass*>.
template class VectorClass<const AnimTypeClass*>;
typedef VectorClass<const AnimTypeClass*> GgAnimCapacityBase;
GG_STATIC_ASSERT(offsetof(GgAnimCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimCapacityBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(const AnimTypeClass*) == 4);

// FUNCTION: GAMEMD 0x5AC900
// DynamicVectorClass<const BuildingTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EAA28 -- DynamicVectorClass<const BuildingTypeClass*>.
template class DynamicVectorClass<const BuildingTypeClass*>;
typedef DynamicVectorClass<const BuildingTypeClass*> GgBuildingCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityDynamic, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const BuildingTypeClass*) == 4);
