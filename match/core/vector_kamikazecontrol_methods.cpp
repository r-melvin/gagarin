// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAUKamikazeControl RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct KamikazeControl;

// FUNCTION: GAMEMD 0x54E890
// DynamicVectorClass<KamikazeControl*>::Clear

// FUNCTION: GAMEMD 0x54E8C0
// DynamicVectorClass<KamikazeControl*>::Slot5

// FUNCTION: GAMEMD 0x54E8E0
// VectorClass<KamikazeControl*>::Slot6

// FUNCTION: GAMEMD 0x54E8F0
// VectorClass<KamikazeControl*>::operator==

// FUNCTION: GAMEMD 0x54E930
// VectorClass<KamikazeControl*>::SetCapacity

// FUNCTION: GAMEMD 0x54E9E0
// VectorClass<KamikazeControl*>::Clear

// FUNCTION: GAMEMD 0x54EA10
// VectorClass<KamikazeControl*>::FindItemIndex

// FUNCTION: GAMEMD 0x54EA50
// VectorClass<KamikazeControl*>::Slot5

// FUNCTION: GAMEMD 0x54EA70
// DynamicVectorClass<KamikazeControl*>::SetCapacity

// FUNCTION: GAMEMD 0x54EB20
// DynamicVectorClass<KamikazeControl*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x54EB50
// VectorClass<KamikazeControl*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x54EBA0
// DynamicVectorClass<KamikazeControl*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7ECE9C -- VectorClass<KamikazeControl*>.
template class VectorClass<KamikazeControl*>;
typedef VectorClass<KamikazeControl*> GgKamikazecontrolVectorClass;
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ECE7C -- DynamicVectorClass<KamikazeControl*>.
template class DynamicVectorClass<KamikazeControl*>;
typedef DynamicVectorClass<KamikazeControl*> GgKamikazecontrolDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgKamikazecontrolDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(KamikazeControl*) == 4);
