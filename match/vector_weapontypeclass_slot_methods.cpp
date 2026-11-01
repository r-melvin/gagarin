// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<WeaponTypeClass*> and
// DynamicVectorClass<WeaponTypeClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class WeaponTypeClass;

// TEMPLATE: GAMEMD 0x40FBE0
// DynamicVectorClass<WeaponTypeClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40FC00
// VectorClass<WeaponTypeClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x40FC10
// VectorClass<WeaponTypeClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x40FC50
// VectorClass<WeaponTypeClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40FD30
// VectorClass<WeaponTypeClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x40FD70
// VectorClass<WeaponTypeClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40FD90
// DynamicVectorClass<WeaponTypeClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40FE40
// DynamicVectorClass<WeaponTypeClass*>::FindItemIndex (slot 4)
template class VectorClass<WeaponTypeClass*>;
template class DynamicVectorClass<WeaponTypeClass*>;

GG_STATIC_ASSERT(sizeof(WeaponTypeClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<WeaponTypeClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<WeaponTypeClass* >) == 0x18);
