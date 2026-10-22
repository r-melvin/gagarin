// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Raw PBVTechnoTypeClass RTTI identifies const pointer elements and the
// DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// No TypeList specialization or constructor address is claimed. Original TU
// boundaries, final link and complete object sizes remain unestablished.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class TechnoTypeClass;

// FUNCTION: GAMEMD 0x4CA890
// DynamicVectorClass<const TechnoTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4CA8C0
// DynamicVectorClass<const TechnoTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4CA8E0
// VectorClass<const TechnoTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4CA8F0
// VectorClass<const TechnoTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4CA930
// VectorClass<const TechnoTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4CA9E0
// VectorClass<const TechnoTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4CAA10
// VectorClass<const TechnoTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4CAA50
// VectorClass<const TechnoTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4CAA70
// DynamicVectorClass<const TechnoTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4CAB20
// DynamicVectorClass<const TechnoTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4CAB50
// VectorClass<const TechnoTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4CABA0
// DynamicVectorClass<const TechnoTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E8954 -- VectorClass<const TechnoTypeClass*>.
template class VectorClass<const TechnoTypeClass*>;
typedef VectorClass<const TechnoTypeClass*> GgTechnoTypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgTechnoTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E8934 -- DynamicVectorClass<const TechnoTypeClass*>.
template class DynamicVectorClass<const TechnoTypeClass*>;
typedef DynamicVectorClass<const TechnoTypeClass*> GgTechnoTypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTechnoTypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const TechnoTypeClass*) == 4);
