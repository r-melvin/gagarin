// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAUAnimationPalette@Map@WorldDominationTour RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

// Opaque nested pointer spelling only; no enclosing Map or pointee layout.
namespace WorldDominationTour { class Map { struct AnimationPalette; }; }

// FUNCTION: GAMEMD 0x769CD0
// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*>::Clear

// FUNCTION: GAMEMD 0x769D00
// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*>::Slot5

// FUNCTION: GAMEMD 0x769D20
// VectorClass<WorldDominationTour::Map::AnimationPalette*>::Slot6

// FUNCTION: GAMEMD 0x76A130
// VectorClass<WorldDominationTour::Map::AnimationPalette*>::operator==

// FUNCTION: GAMEMD 0x76A170
// VectorClass<WorldDominationTour::Map::AnimationPalette*>::SetCapacity

// FUNCTION: GAMEMD 0x76A220
// VectorClass<WorldDominationTour::Map::AnimationPalette*>::Clear

// FUNCTION: GAMEMD 0x76A250
// VectorClass<WorldDominationTour::Map::AnimationPalette*>::FindItemIndex

// FUNCTION: GAMEMD 0x76A290
// VectorClass<WorldDominationTour::Map::AnimationPalette*>::Slot5

// FUNCTION: GAMEMD 0x76A2B0
// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*>::SetCapacity

// FUNCTION: GAMEMD 0x76A360
// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x76A6D0
// VectorClass<WorldDominationTour::Map::AnimationPalette*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x76A720
// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F71A4 -- VectorClass<WorldDominationTour::Map::AnimationPalette*>.
template class VectorClass<WorldDominationTour::Map::AnimationPalette*>;
typedef VectorClass<WorldDominationTour::Map::AnimationPalette*> GgAnimationpaletteVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F7144 -- DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*>.
template class DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*>;
typedef DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*> GgAnimationpaletteDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimationpaletteDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(WorldDominationTour::Map::AnimationPalette*) == 4);
