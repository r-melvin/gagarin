// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<ScriptClass*> and
// DynamicVectorClass<ScriptClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class ScriptClass;

// TEMPLATE: GAMEMD 0x40E820
// DynamicVectorClass<ScriptClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40E840
// VectorClass<ScriptClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x40E850
// VectorClass<ScriptClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x40E890
// VectorClass<ScriptClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40E970
// VectorClass<ScriptClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x40E9B0
// VectorClass<ScriptClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40E9D0
// DynamicVectorClass<ScriptClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40EA80
// DynamicVectorClass<ScriptClass*>::FindItemIndex (slot 4)
template class VectorClass<ScriptClass*>;
template class DynamicVectorClass<ScriptClass*>;

GG_STATIC_ASSERT(sizeof(ScriptClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<ScriptClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<ScriptClass* >) == 0x18);
