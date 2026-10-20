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
class BuildingTypeClass;
class ParticleSystemTypeClass;
class SmudgeTypeClass;
class TerrainTypeClass;
class VoxelAnimTypeClass;

// FUNCTION: GAMEMD 0x45AD80
// VectorClass<const ParticleSystemTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7E4424 -- VectorClass<const ParticleSystemTypeClass*>.
template class VectorClass<const ParticleSystemTypeClass*>;
typedef VectorClass<const ParticleSystemTypeClass*> GgParticleSystemTypeCapacityBase;
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(const ParticleSystemTypeClass*) == 4);

// FUNCTION: GAMEMD 0x5105A0
// VectorClass<const BuildingTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7EAA08 -- VectorClass<const BuildingTypeClass*>.
template class VectorClass<const BuildingTypeClass*>;
typedef VectorClass<const BuildingTypeClass*> GgBuildingCapacityBase;
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingCapacityBase, IsAllocated) == 0x0D);

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

// FUNCTION: GAMEMD 0x67B370
// DynamicVectorClass<const TerrainTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7F0E0C -- DynamicVectorClass<const TerrainTypeClass*>.
template class DynamicVectorClass<const TerrainTypeClass*>;
typedef DynamicVectorClass<const TerrainTypeClass*> GgTerrainTypeCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityDynamic, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const TerrainTypeClass*) == 4);

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
// FUNCTION: GAMEMD 0x67C430
// VectorClass<const TerrainTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7F0D9C -- VectorClass<const TerrainTypeClass*>.
template class VectorClass<const TerrainTypeClass*>;
typedef VectorClass<const TerrainTypeClass*> GgTerrainTypeCapacityBase;
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityBase, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityBase, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityBase, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeCapacityBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(const TerrainTypeClass*) == 4);

// FUNCTION: GAMEMD 0x717C70
// DynamicVectorClass<const ParticleSystemTypeClass*> capacity constructor; RET 8.
// VTABLE: GAMEMD 0x7E4444 -- DynamicVectorClass<const ParticleSystemTypeClass*>.
template class DynamicVectorClass<const ParticleSystemTypeClass*>;
typedef DynamicVectorClass<const ParticleSystemTypeClass*> GgParticleSystemTypeCapacityDynamic;
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityDynamic, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityDynamic, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityDynamic, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityDynamic, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityDynamic, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleSystemTypeCapacityDynamic, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const ParticleSystemTypeClass*) == 4);
