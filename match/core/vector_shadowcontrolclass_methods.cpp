// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVShadowControlClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class ShadowControlClass;

// FUNCTION: GAMEMD 0x6DC580
// DynamicVectorClass<ShadowControlClass*>::Clear

// FUNCTION: GAMEMD 0x6DC5B0
// DynamicVectorClass<ShadowControlClass*>::Slot5

// FUNCTION: GAMEMD 0x6DC5D0
// VectorClass<ShadowControlClass*>::Slot6

// FUNCTION: GAMEMD 0x6DC9D0
// VectorClass<ShadowControlClass*>::operator==

// FUNCTION: GAMEMD 0x6DCA10
// VectorClass<ShadowControlClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6DCAC0
// VectorClass<ShadowControlClass*>::Clear

// FUNCTION: GAMEMD 0x6DCAF0
// VectorClass<ShadowControlClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x6DCB30
// VectorClass<ShadowControlClass*>::Slot5

// FUNCTION: GAMEMD 0x6DCB50
// DynamicVectorClass<ShadowControlClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6DCC00
// DynamicVectorClass<ShadowControlClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x6DCCD0
// VectorClass<ShadowControlClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x6DCD20
// DynamicVectorClass<ShadowControlClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F42FC -- VectorClass<ShadowControlClass*>.
template class VectorClass<ShadowControlClass*>;
typedef VectorClass<ShadowControlClass*> GgShadowcontrolclassVectorClass;
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F42DC -- DynamicVectorClass<ShadowControlClass*>.
template class DynamicVectorClass<ShadowControlClass*>;
typedef DynamicVectorClass<ShadowControlClass*> GgShadowcontrolclassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgShadowcontrolclassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ShadowControlClass*) == 4);
