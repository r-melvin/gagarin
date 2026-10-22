// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAUButtonFadeEffect RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct ButtonFadeEffect;

// FUNCTION: GAMEMD 0x4B9BE0
// DynamicVectorClass<ButtonFadeEffect*>::Clear

// FUNCTION: GAMEMD 0x4B9C10
// DynamicVectorClass<ButtonFadeEffect*>::Slot5

// FUNCTION: GAMEMD 0x4B9C30
// VectorClass<ButtonFadeEffect*>::Slot6

// FUNCTION: GAMEMD 0x4B9CA0
// VectorClass<ButtonFadeEffect*>::operator==

// FUNCTION: GAMEMD 0x4B9CE0
// VectorClass<ButtonFadeEffect*>::SetCapacity

// FUNCTION: GAMEMD 0x4B9D90
// VectorClass<ButtonFadeEffect*>::Clear

// FUNCTION: GAMEMD 0x4B9DC0
// VectorClass<ButtonFadeEffect*>::FindItemIndex

// FUNCTION: GAMEMD 0x4B9E00
// VectorClass<ButtonFadeEffect*>::Slot5

// FUNCTION: GAMEMD 0x4B9E20
// DynamicVectorClass<ButtonFadeEffect*>::SetCapacity

// FUNCTION: GAMEMD 0x4B9ED0
// DynamicVectorClass<ButtonFadeEffect*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4BA1B0
// VectorClass<ButtonFadeEffect*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4BA200
// DynamicVectorClass<ButtonFadeEffect*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E8500 -- VectorClass<ButtonFadeEffect*>.
template class VectorClass<ButtonFadeEffect*>;
typedef VectorClass<ButtonFadeEffect*> GgButtonfadeeffectVectorClass;
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E856C -- DynamicVectorClass<ButtonFadeEffect*>.
template class DynamicVectorClass<ButtonFadeEffect*>;
typedef DynamicVectorClass<ButtonFadeEffect*> GgButtonfadeeffectDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ButtonFadeEffect*) == 4);
