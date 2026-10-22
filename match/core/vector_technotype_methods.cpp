// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// The three raw seven-slot RTTI tables below encode PAVTechnoTypeClass,
// an unqualified pointer. Complete entry-origin bodies establish all bound
// methods. /GX emits shorter derived deleting wrappers; no GX reproduces
// the complete retail 0x49-byte bodies. Extra emitted methods are unclaimed;
// original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class TechnoTypeClass;

// FUNCTION: GAMEMD 0x4778A0
// DynamicVectorClass<TechnoTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4778D0
// DynamicVectorClass<TechnoTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4778F0
// VectorClass<TechnoTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x477A70
// TypeList<TechnoTypeClass*> scalar deleting destructor

// FUNCTION: GAMEMD 0x477FC0
// VectorClass<TechnoTypeClass*>::operator==

// FUNCTION: GAMEMD 0x478000
// VectorClass<TechnoTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4780B0
// VectorClass<TechnoTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4780E0
// VectorClass<TechnoTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x478120
// VectorClass<TechnoTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x478140
// DynamicVectorClass<TechnoTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4781F0
// DynamicVectorClass<TechnoTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x478680
// VectorClass<TechnoTypeClass*> scalar deleting destructor

// FUNCTION: GAMEMD 0x478790
// VectorClass<TechnoTypeClass*> capacity constructor

// SYNTHETIC: GAMEMD 0x4BA160
// DynamicVectorClass<TechnoTypeClass*> scalar deleting destructor

// FUNCTION: GAMEMD 0x0068C200
// DynamicVectorClass<TechnoTypeClass*> capacity constructor

// VTABLE: GAMEMD 0x7E4DF8 -- VectorClass<TechnoTypeClass*>.
template class VectorClass<TechnoTypeClass*>;
typedef VectorClass<TechnoTypeClass*> GgTechnoVectorClass;
GG_STATIC_ASSERT(offsetof(GgTechnoVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTechnoVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTechnoVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTechnoVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E858C -- DynamicVectorClass<TechnoTypeClass*>.
template class DynamicVectorClass<TechnoTypeClass*>;
typedef DynamicVectorClass<TechnoTypeClass*> GgTechnoDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTechnoDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTechnoDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTechnoDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTechnoDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTechnoDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTechnoDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7E4E18 -- TypeList<TechnoTypeClass*>.
template class TypeList<TechnoTypeClass*>;
typedef TypeList<TechnoTypeClass*> GgTechnoTypeList;
GG_STATIC_ASSERT(offsetof(GgTechnoTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeList, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTechnoTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TechnoTypeClass*) == 4);
