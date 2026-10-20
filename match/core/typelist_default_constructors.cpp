// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX
// Entry-origin 0x22-byte bodies end in RET at +0x21. Raw RTTI PBV encodings
// identify TypeList<const Class*> and its zero-offset vector base chain.
// Both GX/no-GX constructor probes match; this TU retains the pointer copy
// cluster flags. Other emitted COMDATs are unclaimed; original TU boundaries,
// final-link selection and complete TypeList sizes remain unestablished.
#include "vector_class_operations.h"
#include "type_list.h"

class BuildingTypeClass;
class VoxelAnimTypeClass;
class SmudgeTypeClass;
class TerrainTypeClass;
class ParticleSystemTypeClass;

// FUNCTION: GAMEMD 0x5AC400
// TypeList<const BuildingTypeClass*>::TypeList(); retail vptr 0x7ED90C.
template class TypeList<const BuildingTypeClass*>;
typedef TypeList<const BuildingTypeClass*> GgTypeListDefault1;
GG_STATIC_ASSERT(offsetof(GgTypeListDefault1, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault1, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault1, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault1, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault1, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault1, CapacityIncrement) == 0x14);

// FUNCTION: GAMEMD 0x67A390
// TypeList<const VoxelAnimTypeClass*>::TypeList(); retail vptr 0x7F0D3C.
template class TypeList<const VoxelAnimTypeClass*>;
typedef TypeList<const VoxelAnimTypeClass*> GgTypeListDefault2;
GG_STATIC_ASSERT(offsetof(GgTypeListDefault2, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault2, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault2, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault2, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault2, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault2, CapacityIncrement) == 0x14);

// FUNCTION: GAMEMD 0x67A600
// TypeList<const SmudgeTypeClass*>::TypeList(); retail vptr 0x7F0D1C.
template class TypeList<const SmudgeTypeClass*>;
typedef TypeList<const SmudgeTypeClass*> GgTypeListDefault4;
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, CapacityIncrement) == 0x14);

// FUNCTION: GAMEMD 0x67A8B0
// TypeList<const TerrainTypeClass*>::TypeList(); retail vptr 0x7F0CFC.
template class TypeList<const TerrainTypeClass*>;
typedef TypeList<const TerrainTypeClass*> GgTypeListDefault6;
GG_STATIC_ASSERT(offsetof(GgTypeListDefault6, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault6, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault6, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault6, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault6, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault6, CapacityIncrement) == 0x14);

// FUNCTION: GAMEMD 0x717AF0
// TypeList<const ParticleSystemTypeClass*>::TypeList(); retail vptr 0x7F4F9C.
template class TypeList<const ParticleSystemTypeClass*>;
typedef TypeList<const ParticleSystemTypeClass*> GgTypeListDefault7;
GG_STATIC_ASSERT(offsetof(GgTypeListDefault7, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault7, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault7, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault7, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault7, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault7, CapacityIncrement) == 0x14);
