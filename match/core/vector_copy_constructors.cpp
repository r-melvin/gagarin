// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX
// Complete entry-origin spans (0x88 bytes, RET 4 at +0x85) and raw RTTI
// identify these copy constructors and their inherited prefix. PBV type codes
// retain pointee const; PAU identifies the non-const MPlayerScoreType pointer.
// Flags retain the verified constructor cluster. Whole-class instantiation
// is used under VC6; extra emitted virtuals/destructors remain unclaimed, and
// their final-link selection and complete class sizes are not established.
// Original TU grouping is unknown. Constructors are ordered by retail address.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"

class TeamTypeClass;
class UnitTypeClass;
class AircraftTypeClass;
class InfantryTypeClass;
class AnimTypeClass;
class BuildingTypeClass;
struct MPlayerScoreType;
class VoxelAnimTypeClass;
class SmudgeTypeClass;
class ParticleSystemTypeClass;

// FUNCTION: GAMEMD 0x50E830
// DynamicVectorClass<const TeamTypeClass*> copy constructor; base vptr 0x7EA9E4.
// VTABLE: GAMEMD 0x7EAAE8 -- DynamicVectorClass<const TeamTypeClass*>.
template class DynamicVectorClass<const TeamTypeClass*>;
typedef DynamicVectorClass<const TeamTypeClass*> GgVectorCopy0;
GG_STATIC_ASSERT(offsetof(GgVectorCopy0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy0, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy0, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy0, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy0, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const TeamTypeClass*) == 4);

// FUNCTION: GAMEMD 0x513740
// TypeList<const UnitTypeClass*> copy constructor; base vptr 0x7EAC48.
// VTABLE: GAMEMD 0x7EABE8 -- TypeList<const UnitTypeClass*>.
template class TypeList<const UnitTypeClass*>;
typedef TypeList<const UnitTypeClass*> GgVectorCopy1;
GG_STATIC_ASSERT(offsetof(GgVectorCopy1, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy1, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy1, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy1, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy1, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy1, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const UnitTypeClass*) == 4);

// FUNCTION: GAMEMD 0x5137D0
// TypeList<const AircraftTypeClass*> copy constructor; base vptr 0x7EAC68.
// VTABLE: GAMEMD 0x7EABC8 -- TypeList<const AircraftTypeClass*>.
template class TypeList<const AircraftTypeClass*>;
typedef TypeList<const AircraftTypeClass*> GgVectorCopy2;
GG_STATIC_ASSERT(offsetof(GgVectorCopy2, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy2, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy2, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy2, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy2, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy2, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const AircraftTypeClass*) == 4);

// FUNCTION: GAMEMD 0x513860
// DynamicVectorClass<const InfantryTypeClass*> copy constructor; base vptr 0x7EAC28.
// VTABLE: GAMEMD 0x7EAC88 -- DynamicVectorClass<const InfantryTypeClass*>.
template class DynamicVectorClass<const InfantryTypeClass*>;
typedef DynamicVectorClass<const InfantryTypeClass*> GgVectorCopy3;
GG_STATIC_ASSERT(offsetof(GgVectorCopy3, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy3, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy3, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy3, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy3, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy3, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const InfantryTypeClass*) == 4);

// FUNCTION: GAMEMD 0x5255F0
// TypeList<const AnimTypeClass*> copy constructor; base vptr 0x7EB6F4.
// VTABLE: GAMEMD 0x7EB6D4 -- TypeList<const AnimTypeClass*>.
template class TypeList<const AnimTypeClass*>;
typedef TypeList<const AnimTypeClass*> GgVectorCopy4;
GG_STATIC_ASSERT(offsetof(GgVectorCopy4, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy4, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy4, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy4, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy4, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy4, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const AnimTypeClass*) == 4);

// FUNCTION: GAMEMD 0x5AD660
// TypeList<const BuildingTypeClass*> copy constructor; base vptr 0x7EAA08.
// VTABLE: GAMEMD 0x7ED90C -- TypeList<const BuildingTypeClass*>.
template class TypeList<const BuildingTypeClass*>;
typedef TypeList<const BuildingTypeClass*> GgVectorCopy5;
GG_STATIC_ASSERT(offsetof(GgVectorCopy5, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy5, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy5, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy5, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy5, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy5, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const BuildingTypeClass*) == 4);

// FUNCTION: GAMEMD 0x5C4F30
// DynamicVectorClass<MPlayerScoreType*> copy constructor; base vptr 0x7EE3D0.
// VTABLE: GAMEMD 0x7EE3F0 -- DynamicVectorClass<MPlayerScoreType*>.
template class DynamicVectorClass<MPlayerScoreType*>;
typedef DynamicVectorClass<MPlayerScoreType*> GgVectorCopy6;
GG_STATIC_ASSERT(offsetof(GgVectorCopy6, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy6, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy6, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy6, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy6, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy6, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(MPlayerScoreType*) == 4);

// FUNCTION: GAMEMD 0x67C1F0
// TypeList<const VoxelAnimTypeClass*> copy constructor; base vptr 0x7F0D5C.
// VTABLE: GAMEMD 0x7F0D3C -- TypeList<const VoxelAnimTypeClass*>.
template class TypeList<const VoxelAnimTypeClass*>;
typedef TypeList<const VoxelAnimTypeClass*> GgVectorCopy7;
GG_STATIC_ASSERT(offsetof(GgVectorCopy7, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy7, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy7, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy7, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy7, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy7, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const VoxelAnimTypeClass*) == 4);

// FUNCTION: GAMEMD 0x67C280
// TypeList<const SmudgeTypeClass*> copy constructor; base vptr 0x7F0D7C.
// VTABLE: GAMEMD 0x7F0D1C -- TypeList<const SmudgeTypeClass*>.
template class TypeList<const SmudgeTypeClass*>;
typedef TypeList<const SmudgeTypeClass*> GgVectorCopy8;
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const SmudgeTypeClass*) == 4);

// FUNCTION: GAMEMD 0x717D20
// TypeList<const ParticleSystemTypeClass*> copy constructor; base vptr 0x7E4424.
// VTABLE: GAMEMD 0x7F4F9C -- TypeList<const ParticleSystemTypeClass*>.
template class TypeList<const ParticleSystemTypeClass*>;
typedef TypeList<const ParticleSystemTypeClass*> GgVectorCopy9;
GG_STATIC_ASSERT(offsetof(GgVectorCopy9, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy9, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy9, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy9, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy9, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy9, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const ParticleSystemTypeClass*) == 4);

// FUNCTION: GAMEMD 0x75E6B0
// DynamicVectorClass<const VoxelAnimTypeClass*> copy constructor; base vptr 0x7F0D5C.
// VTABLE: GAMEMD 0x7F0DCC -- DynamicVectorClass<const VoxelAnimTypeClass*>.
template class DynamicVectorClass<const VoxelAnimTypeClass*>;
typedef DynamicVectorClass<const VoxelAnimTypeClass*> GgVectorCopy10;
GG_STATIC_ASSERT(offsetof(GgVectorCopy10, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy10, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy10, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy10, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy10, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy10, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const VoxelAnimTypeClass*) == 4);
