// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVColorScheme RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class ColorScheme;

// FUNCTION: GAMEMD 0x627D20
// DynamicVectorClass<ColorScheme*>::Clear

// FUNCTION: GAMEMD 0x627D50
// DynamicVectorClass<ColorScheme*>::Slot5

// FUNCTION: GAMEMD 0x627D70
// VectorClass<ColorScheme*>::Slot6

// FUNCTION: GAMEMD 0x627E10
// VectorClass<ColorScheme*>::operator==

// FUNCTION: GAMEMD 0x627E50
// VectorClass<ColorScheme*>::SetCapacity

// FUNCTION: GAMEMD 0x627F00
// VectorClass<ColorScheme*>::Clear

// FUNCTION: GAMEMD 0x627F30
// VectorClass<ColorScheme*>::FindItemIndex

// FUNCTION: GAMEMD 0x627F70
// VectorClass<ColorScheme*>::Slot5

// FUNCTION: GAMEMD 0x627F90
// DynamicVectorClass<ColorScheme*>::SetCapacity

// FUNCTION: GAMEMD 0x628040
// DynamicVectorClass<ColorScheme*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x6285F0
// VectorClass<ColorScheme*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x628640
// DynamicVectorClass<ColorScheme*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EF7B0 -- VectorClass<ColorScheme*>.
template class VectorClass<ColorScheme*>;
typedef VectorClass<ColorScheme*> GgColorSchemeVectorClass;
GG_STATIC_ASSERT(offsetof(GgColorSchemeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgColorSchemeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgColorSchemeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgColorSchemeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EF790 -- DynamicVectorClass<ColorScheme*>.
template class DynamicVectorClass<ColorScheme*>;
typedef DynamicVectorClass<ColorScheme*> GgColorSchemeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ColorScheme*) == 4);
