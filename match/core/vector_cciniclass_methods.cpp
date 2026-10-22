// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVCCINIClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class CCINIClass;

// FUNCTION: GAMEMD 0x5384C0
// DynamicVectorClass<CCINIClass*>::Clear

// FUNCTION: GAMEMD 0x5384F0
// DynamicVectorClass<CCINIClass*>::Slot5

// FUNCTION: GAMEMD 0x538510
// VectorClass<CCINIClass*>::Slot6

// FUNCTION: GAMEMD 0x538520
// VectorClass<CCINIClass*>::operator==

// FUNCTION: GAMEMD 0x538560
// VectorClass<CCINIClass*>::SetCapacity

// FUNCTION: GAMEMD 0x538610
// VectorClass<CCINIClass*>::Clear

// FUNCTION: GAMEMD 0x538640
// VectorClass<CCINIClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x538680
// VectorClass<CCINIClass*>::Slot5

// FUNCTION: GAMEMD 0x5386A0
// DynamicVectorClass<CCINIClass*>::SetCapacity

// FUNCTION: GAMEMD 0x538750
// DynamicVectorClass<CCINIClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x538A90
// VectorClass<CCINIClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x538AE0
// DynamicVectorClass<CCINIClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EB80C -- VectorClass<CCINIClass*>.
template class VectorClass<CCINIClass*>;
typedef VectorClass<CCINIClass*> GgCCINIClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgCCINIClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCCINIClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCCINIClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCCINIClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EB82C -- DynamicVectorClass<CCINIClass*>.
template class DynamicVectorClass<CCINIClass*>;
typedef DynamicVectorClass<CCINIClass*> GgCCINIClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgCCINIClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCCINIClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCCINIClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCCINIClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCCINIClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCCINIClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(CCINIClass*) == 4);
