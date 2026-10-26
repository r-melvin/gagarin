// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Op /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Dropship.cpp. The name is the source-file string at 0x8204a8
//   in retail gamemd.exe v1.001, passed by the assert at 0x4b8c61 inside this object's
//   code range (0x4b67a0-0x4ba3af). Functions are in ascending retail address order.

#include <math.h>
#pragma intrinsic(pow)
#include "../core/empty_function_family_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x8A0908
extern int DAT_008A0908;
// GLOBAL: GAMEMD 0x8A090C
extern int DAT_008A090C;
// GLOBAL: GAMEMD 0x8A0910
extern int DAT_008A0910;


// Retail PAUButtonFadeEffect RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// Retail PAUCrossDissolveEffect RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

struct ButtonFadeEffect;

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
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgButtonfadeeffectDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ButtonFadeEffect*) == 4);

#include "../core/vector_class_operations.h"

struct CrossDissolveEffect;

// VTABLE: GAMEMD 0x7E8520 -- VectorClass<CrossDissolveEffect*>.
template class VectorClass<CrossDissolveEffect*>;
typedef VectorClass<CrossDissolveEffect*> GgCrossdissolveeffectVectorClass;
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E854C -- DynamicVectorClass<CrossDissolveEffect*>.
template class DynamicVectorClass<CrossDissolveEffect*>;
typedef DynamicVectorClass<CrossDissolveEffect*> GgCrossdissolveeffectDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(CrossDissolveEffect*) == 4);

// Declaration: GAMEMD 0x4CAC40 -- engine helper, stacked double/ST0 result.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4B67A0
// GLOBAL: GAMEMD 0x8A08A8
double DAT_008A08A8 = FUN_004CAC40(2.0 * pow(256.0, 2.0));

// SYNTHETIC: GAMEMD 0x4B67D0
// GLOBAL: GAMEMD 0x8A0918
double DAT_008A0918 = DAT_008A08A8 / 60.0;

// SYNTHETIC: GAMEMD 0x4B67F0
// GLOBAL: GAMEMD 0x8A0900
double DAT_008A0900 = 1.0 / DAT_008A0918;

// FUNCTION: GAMEMD 0x4B6970
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_004B6970()
{
    DAT_008A0910 = 0;
    DAT_008A0908 = 0x80;
    DAT_008A090C = 0x80;
}

// FUNCTION: GAMEMD 0x004B69D0
void FUN_004B69D0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4B9C40
// DynamicVectorClass<CrossDissolveEffect*>::Clear

// FUNCTION: GAMEMD 0x4B9C70
// DynamicVectorClass<CrossDissolveEffect*>::Slot5

// FUNCTION: GAMEMD 0x4B9C90
// VectorClass<CrossDissolveEffect*>::Slot6

// FUNCTION: GAMEMD 0x4B9F00
// VectorClass<CrossDissolveEffect*>::operator==

// FUNCTION: GAMEMD 0x4B9F40
// VectorClass<CrossDissolveEffect*>::SetCapacity

// FUNCTION: GAMEMD 0x4B9FF0
// VectorClass<CrossDissolveEffect*>::Clear

// FUNCTION: GAMEMD 0x4BA020
// VectorClass<CrossDissolveEffect*>::FindItemIndex

// FUNCTION: GAMEMD 0x4BA060
// VectorClass<CrossDissolveEffect*>::Slot5

// FUNCTION: GAMEMD 0x4BA080
// DynamicVectorClass<CrossDissolveEffect*>::SetCapacity

// FUNCTION: GAMEMD 0x4BA130
// DynamicVectorClass<CrossDissolveEffect*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4BA250
// VectorClass<CrossDissolveEffect*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4BA2A0
// DynamicVectorClass<CrossDissolveEffect*>::scalar deleting destructor
