// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Raw PBVTeamTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class TeamTypeClass;

// FUNCTION: GAMEMD 0x50E6A0
// DynamicVectorClass<const TeamTypeClass*>::Clear

// FUNCTION: GAMEMD 0x50E6D0
// DynamicVectorClass<const TeamTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x50E6F0
// VectorClass<const TeamTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x50E7E0
// TypeList<const TeamTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x50E830
// DynamicVectorClass<const TeamTypeClass*>::copy constructor

// SYNTHETIC: GAMEMD 0x50E8C0
// DynamicVectorClass<const TeamTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x50F740
// VectorClass<const TeamTypeClass*>::operator==

// FUNCTION: GAMEMD 0x50F780
// VectorClass<const TeamTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x50F830
// VectorClass<const TeamTypeClass*>::Clear

// FUNCTION: GAMEMD 0x50F860
// VectorClass<const TeamTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x50F8A0
// VectorClass<const TeamTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x50F8C0
// DynamicVectorClass<const TeamTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x50F970
// DynamicVectorClass<const TeamTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x510310
// VectorClass<const TeamTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA9E4 -- VectorClass<const TeamTypeClass*>.
template class VectorClass<const TeamTypeClass*>;
typedef VectorClass<const TeamTypeClass*> GgTeamTypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgTeamTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamTypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamTypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamTypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EAAE8 -- DynamicVectorClass<const TeamTypeClass*>.
template class DynamicVectorClass<const TeamTypeClass*>;
typedef DynamicVectorClass<const TeamTypeClass*> GgTeamTypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7EA9C4 -- TypeList<const TeamTypeClass*>.
template class TypeList<const TeamTypeClass*>;
typedef TypeList<const TeamTypeClass*> GgTeamTypeTypeList;
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const TeamTypeClass*) == 4);
