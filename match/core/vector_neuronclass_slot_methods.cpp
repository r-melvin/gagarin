// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<NeuronClass*> and
// DynamicVectorClass<NeuronClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class NeuronClass;

// TEMPLATE: GAMEMD 0x43AB20
// VectorClass<NeuronClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x43AB30
// VectorClass<NeuronClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x43AB70
// VectorClass<NeuronClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x43AC50
// VectorClass<NeuronClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x43AC90
// VectorClass<NeuronClass*>::Slot5 (slot 5)
template class VectorClass<NeuronClass*>;
template class DynamicVectorClass<NeuronClass*>;

GG_STATIC_ASSERT(sizeof(NeuronClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<NeuronClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<NeuronClass* >) == 0x18);
