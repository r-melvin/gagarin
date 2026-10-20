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
struct MPlayerScoreType;
class SmudgeTypeClass;

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