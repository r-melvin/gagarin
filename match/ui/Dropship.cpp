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

#include "../_layout/swizzle_manager_class.h"

// An entry of the list, seen as a bare vtable pointer; only slot 43 is called.
struct Vtbl_004B6AB0;
struct Entry_004B6AB0
{
    Vtbl_004B6AB0* Vtbl;
};
typedef int (Entry_004B6AB0::*Slot43_004B6AB0)();
struct Vtbl_004B6AB0
{
    char            _pad000[0xAC];
    Slot43_004B6AB0 At_AC;      // +0xAC
};

// The scenario object seen through three parallel vectors at +0x34D4,
// +0x34F0 and +0x350C (items at +4, count at +0x10 of each).
struct Scenario_004B6AB0
{
    char  _pad000[0x34D8];
    Entry_004B6AB0** ItemsA;    // +0x34D8
    char  _pad34DC[0x34E4 - 0x34DC];
    int   CountA;               // +0x34E4
    char  _pad34E8[0x34F4 - 0x34E8];
    int*  ItemsB;               // +0x34F4
    char  _pad34F8[0x3510 - 0x34F8];
    int*  ItemsC;               // +0x3510
};
GG_STATIC_ASSERT(offsetof(Scenario_004B6AB0, ItemsA) == 0x34D8);
GG_STATIC_ASSERT(offsetof(Scenario_004B6AB0, CountA) == 0x34E4);
GG_STATIC_ASSERT(offsetof(Scenario_004B6AB0, ItemsB) == 0x34F4);
GG_STATIC_ASSERT(offsetof(Scenario_004B6AB0, ItemsC) == 0x3510);

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern Scenario_004B6AB0* DAT_00A8B230;
// GLOBAL: GAMEMD 0xA8ED84 -- the engine frame counter.
extern int CurrentFrame;

// A short list of up to five entries plus the total height they occupy.
class List_004B69B0
{
public:
    int              StartTime;     // +0x00
    int              unknown_04;    // +0x04
    int              unknown_08;    // +0x08
    bool             unknown_0C;    // +0x0C
    int              Count;         // +0x10
    Entry_004B6AB0*  Items[5];      // +0x14
    int              TotalHeight;   // +0x28

    // FUNCTION: GAMEMD 0x4B69B0
    List_004B69B0();
    // FUNCTION: GAMEMD 0x4B6AB0
    bool RemoveAt(int index);
    // FUNCTION: GAMEMD 0x4B6B80
    void Clear();
    // FUNCTION: GAMEMD 0x4B6BB0
    void SwizzlePointers();
};
GG_STATIC_ASSERT(offsetof(List_004B69B0, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(List_004B69B0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(List_004B69B0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(List_004B69B0, Items) == 0x14);
GG_STATIC_ASSERT(offsetof(List_004B69B0, TotalHeight) == 0x28);
GG_STATIC_ASSERT(sizeof(List_004B69B0) == 0x2C);

// FUNCTION: GAMEMD 0x4B69B0
// Start an empty list stamped with the current frame.
List_004B69B0::List_004B69B0()
{
    StartTime = CurrentFrame;
    unknown_08 = 0x7FFFFFFF;
    unknown_0C = false;
    Count = 0;
    TotalHeight = 0;
}

// FUNCTION: GAMEMD 0x4B6AB0
// Drop the entry at `index`: release its hold in the scenario's table, take
// its height off the total and slide the later entries down.
bool List_004B69B0::RemoveAt(int index)
{
    if (Count > 0 && index >= 0 && index < Count) {
        Scenario_004B6AB0* scen = DAT_00A8B230;
        int found = -1;
        if (scen->CountA != 0) {
            for (int i = 0; i < scen->CountA; i++) {
                if (scen->ItemsA[i] == Items[index] && scen->ItemsB[i] != -1) {
                    found = i;
                    break;
                }
            }
        }
        if (found != -1) {
            scen->ItemsC[found]--;
        }
        Entry_004B6AB0** slot = &Items[index];
        Entry_004B6AB0* e = *slot;
        TotalHeight -= (e->*e->Vtbl->At_AC)();
        for (int j = index; j < Count - 1; j++) {
            Items[j] = Items[j + 1];
        }
        Count--;
        Items[Count] = 0;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4B6B80
// Remove every entry and reset the total.
void List_004B69B0::Clear()
{
    unknown_0C = false;
    for (int n = Count; n > 0; n--) {
        RemoveAt(0);
    }
    Count = 0;
    TotalHeight = 0;
}

// FUNCTION: GAMEMD 0x4B6BB0
// Register each entry pointer with the swizzle manager.
void List_004B69B0::SwizzlePointers()
{
    for (int i = 0; i < Count; i++) {
        DAT_00B0C110.vf_4(&Items[i]);
    }
}

// FUNCTION: GAMEMD 0x4B6BF0
// Index of the scenario table row that holds `entry` and is still in use, or -1.
int __fastcall FUN_004B6BF0(Entry_004B6AB0* entry)
{
    int n = DAT_00A8B230->CountA;
    if (n != 0) {
        int i = 0;
        if (0 < n) {
            do {
                if (DAT_00A8B230->ItemsA[i] == entry && DAT_00A8B230->ItemsB[i] != -1) {
                    return i;
                }
                i++;
            } while (i < n);
        }
    }
    return -1;
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
