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
class AircraftTypeClass;
class BuildingTypeClass;
class InfantryTypeClass;
class UnitTypeClass;

class SmudgeTypeClass;
class VoxelAnimTypeClass;

// FUNCTION: GAMEMD 0x5105A0
// VectorClass<const BuildingTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EAA08 -- VectorClass<const BuildingTypeClass*>.
template class VectorClass<const BuildingTypeClass*>;
typedef VectorClass<const BuildingTypeClass*> GgBuildingCapacityBase;
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, IsAllocated) == 0x0D);

// FUNCTION: GAMEMD 0x512DC0
// DynamicVectorClass<const InfantryTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EAC88 -- DynamicVectorClass<const InfantryTypeClass*>.
template class DynamicVectorClass<const InfantryTypeClass*>;
typedef DynamicVectorClass<const InfantryTypeClass*> GgInfantryCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityDynamic, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const InfantryTypeClass*) == 4);

// FUNCTION: GAMEMD 0x513190
// DynamicVectorClass<const UnitTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EACA8 -- DynamicVectorClass<const UnitTypeClass*>.
template class DynamicVectorClass<const UnitTypeClass*>;
typedef DynamicVectorClass<const UnitTypeClass*> GgUnitTypeCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityDynamic, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const UnitTypeClass*) == 4);

// FUNCTION: GAMEMD 0x513560
// DynamicVectorClass<const AircraftTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EACC8 -- DynamicVectorClass<const AircraftTypeClass*>.
template class DynamicVectorClass<const AircraftTypeClass*>;
typedef DynamicVectorClass<const AircraftTypeClass*> GgAircraftTypeCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityDynamic, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const AircraftTypeClass*) == 4);

// FUNCTION: GAMEMD 0x5138F0
// VectorClass<const InfantryTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EAC28 -- VectorClass<const InfantryTypeClass*>.
template class VectorClass<const InfantryTypeClass*>;
typedef VectorClass<const InfantryTypeClass*> GgInfantryCapacityBase;
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantryCapacityBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(const InfantryTypeClass*) == 4);

// FUNCTION: GAMEMD 0x513940
// VectorClass<const UnitTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EAC48 -- VectorClass<const UnitTypeClass*>.
template class VectorClass<const UnitTypeClass*>;
typedef VectorClass<const UnitTypeClass*> GgUnitTypeCapacityBase;
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnitTypeCapacityBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(const UnitTypeClass*) == 4);

// FUNCTION: GAMEMD 0x513990
// VectorClass<const AircraftTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EAC68 -- VectorClass<const AircraftTypeClass*>.
template class VectorClass<const AircraftTypeClass*>;
typedef VectorClass<const AircraftTypeClass*> GgAircraftTypeCapacityBase;
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAircraftTypeCapacityBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(const AircraftTypeClass*) == 4);

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
// FUNCTION: GAMEMD 0x67AC70
// DynamicVectorClass<const VoxelAnimTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7F0DCC -- DynamicVectorClass<const VoxelAnimTypeClass*>.
template class DynamicVectorClass<const VoxelAnimTypeClass*>;
typedef DynamicVectorClass<const VoxelAnimTypeClass*> GgVoxelAnimTypeCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityDynamic, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const VoxelAnimTypeClass*) == 4);

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

// FUNCTION: GAMEMD 0x67C310
// VectorClass<const VoxelAnimTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7F0D5C -- VectorClass<const VoxelAnimTypeClass*>.
template class VectorClass<const VoxelAnimTypeClass*>;
typedef VectorClass<const VoxelAnimTypeClass*> GgVoxelAnimTypeCapacityBase;
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeCapacityBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(const VoxelAnimTypeClass*) == 4);

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
