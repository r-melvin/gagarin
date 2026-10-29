// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVIonBlastClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class IonBlastClass;

// FUNCTION: GAMEMD 0x53DA40
// DynamicVectorClass<IonBlastClass*>::Clear

// FUNCTION: GAMEMD 0x53DA70
// DynamicVectorClass<IonBlastClass*>::Slot5

// FUNCTION: GAMEMD 0x53DA90
// VectorClass<IonBlastClass*>::Slot6

// FUNCTION: GAMEMD 0x53DAA0
// VectorClass<IonBlastClass*>::operator==

// FUNCTION: GAMEMD 0x53DAE0
// VectorClass<IonBlastClass*>::SetCapacity

// FUNCTION: GAMEMD 0x53DB90
// VectorClass<IonBlastClass*>::Clear

// FUNCTION: GAMEMD 0x53DBC0
// VectorClass<IonBlastClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x53DC00
// VectorClass<IonBlastClass*>::Slot5

// FUNCTION: GAMEMD 0x53DC20
// DynamicVectorClass<IonBlastClass*>::SetCapacity

// FUNCTION: GAMEMD 0x53DCD0
// DynamicVectorClass<IonBlastClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x53DD00
// VectorClass<IonBlastClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x53DD50
// DynamicVectorClass<IonBlastClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EC07C -- VectorClass<IonBlastClass*>.
template class VectorClass<IonBlastClass*>;
typedef VectorClass<IonBlastClass*> GgIonblastclassVectorClass;
GG_STATIC_ASSERT(offsetof(GgIonblastclassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgIonblastclassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgIonblastclassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgIonblastclassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EC05C -- DynamicVectorClass<IonBlastClass*>.
template class DynamicVectorClass<IonBlastClass*>;
typedef DynamicVectorClass<IonBlastClass*> GgIonblastclassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgIonblastclassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgIonblastclassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgIonblastclassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgIonblastclassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgIonblastclassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgIonblastclassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(IonBlastClass*) == 4);
