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
class AircraftTypeClass;
class AnimTypeClass;
class BuildingTypeClass;
class InfantryTypeClass;
class UnitTypeClass;

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
