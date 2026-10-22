// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAUStartingTechnoStruct@HouseClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "../_layout/house_class.h"

// The nested element remains opaque in the shared HouseClass declaration.

// FUNCTION: GAMEMD 0x50E500
// DynamicVectorClass<HouseClass::StartingTechnoStruct*>::Clear

// FUNCTION: GAMEMD 0x50E530
// DynamicVectorClass<HouseClass::StartingTechnoStruct*>::Slot5

// FUNCTION: GAMEMD 0x50E550
// VectorClass<HouseClass::StartingTechnoStruct*>::Slot6

// FUNCTION: GAMEMD 0x50EC20
// VectorClass<HouseClass::StartingTechnoStruct*>::operator==

// FUNCTION: GAMEMD 0x50EC60
// VectorClass<HouseClass::StartingTechnoStruct*>::SetCapacity

// FUNCTION: GAMEMD 0x50ED10
// VectorClass<HouseClass::StartingTechnoStruct*>::Clear

// FUNCTION: GAMEMD 0x50ED40
// VectorClass<HouseClass::StartingTechnoStruct*>::FindItemIndex

// FUNCTION: GAMEMD 0x50ED80
// VectorClass<HouseClass::StartingTechnoStruct*>::Slot5

// FUNCTION: GAMEMD 0x50EDA0
// DynamicVectorClass<HouseClass::StartingTechnoStruct*>::SetCapacity

// FUNCTION: GAMEMD 0x50EE50
// DynamicVectorClass<HouseClass::StartingTechnoStruct*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x510090
// VectorClass<HouseClass::StartingTechnoStruct*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5100E0
// DynamicVectorClass<HouseClass::StartingTechnoStruct*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA964 -- VectorClass<HouseClass::StartingTechnoStruct*>.
template class VectorClass<HouseClass::StartingTechnoStruct*>;
typedef VectorClass<HouseClass::StartingTechnoStruct*> GgStartingtechnostructVectorClass;
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA944 -- DynamicVectorClass<HouseClass::StartingTechnoStruct*>.
template class DynamicVectorClass<HouseClass::StartingTechnoStruct*>;
typedef DynamicVectorClass<HouseClass::StartingTechnoStruct*> GgStartingtechnostructDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgStartingtechnostructDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(HouseClass::StartingTechnoStruct*) == 4);
