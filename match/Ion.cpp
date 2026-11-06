// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Ion.cpp. The name is the source-file string at 0x828034
//   in retail gamemd.exe v1.001, passed by the assert at 0x53a062 inside this object's
//   code range (0x539350-0x53c81f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.

#include <math.h>
#include "lightning_storm_methods.h"

#include "techno_class_mindcontrol_query_methods.h"

#include "trivial_tu104_methods.h"

#include <windows.h>
#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "runtime_misc_globals.h"
#include "_layout/cell.h"
#include "header_init_shapes.h"
#include "_layout/anim_class.h"
#include "_layout/anim_type_class.h"
#include "_layout/rules_class.h"
#include "_layout/shp_struct.h"
#include "_layout/cell_class.h"
#include "_layout/map_0087f7e8.h"
#include "_layout/scenario_ptr_00a8b230.h"
#include "dsurface_class.h"
#include "composite_surface.h"
#include "_rt/gg_istream.h"
#include "_layout/audio_controller.h"
#include "small_misc5_methods.h"
#include "wdt_voice_classes.h"
#include "message_list_class_methods.h"
#include "scenario_session_globals.h"
#include "trivial_tu263_methods.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
#include "_layout/cell.h"

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

#include "_layout/team_005095d0.h"

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

#include "_layout/obj_005095d0.h"



#include "_layout/obj_0053ecb0.h"

#include "_layout/triple_0053eda0.h"

#include "_layout/obj_0053eda0.h"

#include "_layout/obj_005402b0.h"

#include "_layout/obj_00542fc0.h"

#include "_layout/entry_005657a0.h"

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

#include "_layout/obj_005657a0.h"


#include "_layout/iface_005bf500.h"

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

#include "_layout/vector_005c6120.h"

#include "_layout/obj_005f9710.h"

#include "_layout/quad_00645c30.h"

#include "_layout/record_00656580.h"

#include "_layout/key_00656580.h"

#include "_layout/obj_00656580.h"


#include "_layout/pair_0065c890.h"

#include "_layout/obj_0068bcb0.h"

#include "_layout/obj_0068c030.h"

#include "_layout/owner_006915d0.h"

#include "_layout/cursor_006915d0.h"

#include "_layout/obj_00696f10.h"

#include "_layout/obj_0069b540.h"


#include "_layout/type_006a46d0.h"

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA9FA78
extern int DAT_00A9FA78;
// GLOBAL: GAMEMD 0xA9FA7C
extern int DAT_00A9FA7C;
// GLOBAL: GAMEMD 0xA9FA80
extern int DAT_00A9FA80;


// Raw PBVAnimClass RTTI identifies const pointer elements and the
// DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// No TypeList or constructor address is claimed. Original TU boundaries,
// final link and complete object sizes remain unestablished.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "vector_class_operations.h"
#include "house_class_methods.h"
#include "scenario_class_lighting_recalc_methods.h"
class AnimClass;

// VTABLE: GAMEMD 0x7EBFEC -- VectorClass<const AnimClass*>.
template class VectorClass<const AnimClass*>;
typedef VectorClass<const AnimClass*> GgAnimVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EBFCC -- DynamicVectorClass<const AnimClass*>.
template class DynamicVectorClass<const AnimClass*>;
typedef DynamicVectorClass<const AnimClass*> GgAnimDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const AnimClass*) == 4);

// Declaration: GAMEMD 0x4CAC40 -- engine helper, stacked double/ST0 result.
double __cdecl FUN_004CAC40(double value);

// GLOBAL: GAMEMD 0xA9FA00
extern double DAT_00A9FA00;

// GLOBAL: GAMEMD 0xA9FA88
extern double DAT_00A9FA88;

// GLOBAL: GAMEMD 0xA9FA58
extern double DAT_00A9FA58;

// SYNTHETIC: GAMEMD 0x00539560
// GLOBAL: GAMEMD 0x00A9F9CC
CellStruct DAT_00A9F9CC = DAT_00A9F9F8;

// SYNTHETIC: GAMEMD 0x00539570
// GLOBAL: GAMEMD 0x00A9FA48
CellStruct DAT_00A9FA48 = DAT_00A9F9F8;

// Included here, after the dynamic initialisers above: each static data member a header declares
// advances the compiler-generated initialiser numbering (_$E<n>) that the earlier rows are named by.
#include "_layout/staticvectorholder_00a9f9d0.h"
#include "_layout/staticvectorholder_00a9fa60.h"
#include "_layout/staticvectorholder_00a9fa18.h"
#include "_layout/voc_class.h"
// GLOBAL: GAMEMD 0xA9FAB8
extern int DAT_00A9FAB8;
// GLOBAL: GAMEMD 0xA9FACC
extern HouseClass* DAT_00A9FACC;
// GLOBAL: GAMEMD 0xA9FAD0
extern unsigned char DAT_00A9FAD0;

// GLOBAL: GAMEMD 0x8871E0
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0x827FC0
extern int DAT_00827FC0;
// GLOBAL: GAMEMD 0x827FC4
extern int DAT_00827FC4;
// GLOBAL: GAMEMD 0x827FC8
extern int DAT_00827FC8;
// GLOBAL: GAMEMD 0x827FCC
extern int DAT_00827FCC;
// GLOBAL: GAMEMD 0xA9FA98
extern int DAT_00A9FA98;
// GLOBAL: GAMEMD 0xA9FA9C
extern DSurface* DAT_00A9FA9C;
// GLOBAL: GAMEMD 0xA9FAA0
extern int DAT_00A9FAA0;
// GLOBAL: GAMEMD 0xA9FAA4
extern int DAT_00A9FAA4;
// GLOBAL: GAMEMD 0xA9FAC4
extern AnimClass* DAT_00A9FAC4;
// GLOBAL: GAMEMD 0xA9FAC8
extern int DAT_00A9FAC8;

// FUNCTION: GAMEMD 0x539760
// Resets the lightning storm: sentinels, state words, the three animation lists, the saved
// light level, the offscreen surface; then relights the map with no tint.
void __fastcall FUN_00539760()
{
    DAT_00A9FA48 = DAT_00A9F9F8;
    DAT_00A9F9CC = DAT_00A9F9F8;
    DAT_00A9FAB4 = 0;
    DAT_00A9FABC = 0;
    DAT_00827FC0 = -1;
    DAT_00827FC4 = -1;
    DAT_00827FC8 = -1;
    DAT_00827FCC = -1;
    DAT_00A9FAC0 = 0;
    DAT_00A9FAC4 = 0;
    DAT_00A9FAC8 = 0;
    DAT_00A9FAB8 = 0;
    DAT_00A9FACC = 0;
    StaticVectorHolder_00A9FA60::DAT_00A9FA60.Clear();
    StaticVectorHolder_00A9F9D0::DAT_00A9F9D0.Clear();
    StaticVectorHolder_00A9FA18::DAT_00A9FA18.Clear();
    DAT_00A8B230->unknown_3530 = DAT_00A8B230->unknown_3528;
    delete DAT_00A9FA9C;
    DAT_00A9FA98 = 0;
    DAT_00A9FA9C = 0;
    DAT_00A9FAB0 = 0;
    ScenarioClass::RecalcLighting(-1, -1, -1, false);
}

// FUNCTION: GAMEMD 0x539890
// Writes the storm state to a save stream (single flags, then the three animation lists as
// count plus pointers), stopping at the first failure.
long __fastcall FUN_00539890(Gg_IStream* stream)
{
    long hr;
    int count;
    int i;

    hr = stream->Write(&DAT_00A9FAB4, 1, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00827FC0, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00827FC4, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9FAB8, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9FAD0, 1, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00827FC8, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00827FCC, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9FABC, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9FAC0, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9FAC4, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9F9CC, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9FA48, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9FACC, 4, 0);
    if (hr < 0) return hr;
    hr = stream->Write(&DAT_00A9FAC8, 4, 0);
    if (hr < 0) return hr;

    count = StaticVectorHolder_00A9FA60::DAT_00A9FA60.Count;
    hr = stream->Write(&count, 4, 0);
    if (hr < 0) return hr;
    for (i = 0; i < count; i++) {
        const AnimClass* item = StaticVectorHolder_00A9FA60::DAT_00A9FA60.Items[i];
        hr = stream->Write(&item, 4, 0);
        if (hr < 0) return hr;
    }

    count = StaticVectorHolder_00A9F9D0::DAT_00A9F9D0.Count;
    hr = stream->Write(&count, 4, 0);
    if (hr < 0) return hr;
    for (i = 0; i < count; i++) {
        const AnimClass* item = StaticVectorHolder_00A9F9D0::DAT_00A9F9D0.Items[i];
        hr = stream->Write(&item, 4, 0);
        if (hr < 0) return hr;
    }

    count = StaticVectorHolder_00A9FA18::DAT_00A9FA18.Count;
    hr = stream->Write(&count, 4, 0);
    if (hr < 0) return hr;
    for (i = 0; i < count; i++) {
        const AnimClass* item = StaticVectorHolder_00A9FA18::DAT_00A9FA18.Items[i];
        hr = stream->Write(&item, 4, 0);
        if (hr < 0) return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x539EA0
// Stores to a global.
void FUN_00539EA0(int a1)
{
    DAT_00A9FAB4 = a1;
}

// GLOBAL: GAMEMD 0x87F914
extern int DAT_0087F914;
// GLOBAL: GAMEMD 0x87F918
extern int DAT_0087F918;
// GLOBAL: GAMEMD 0xA8BC60 -- MessageListClass::Instance.
extern MessageListClass DAT_00A8BC60;
// FUNCTION: GAMEMD 0x65FA70 (decl; reloc)
bool FUN_0065FA70(int a, CellStruct cell);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- localised string lookup(label, index-out, file, line).
const wchar_t* FUN_00734E60(const char* label, int* index, const char* file, int line);

// FUNCTION: GAMEMD 0x539EB0
// Starts or schedules a storm: picks a legal target cell when none was given, records the
// owner, and either queues the delay or begins the storm (radar outage for the other
// houses, relight, message, sound).
void __fastcall FUN_00539EB0(int duration, int deferment, CellStruct cell, void* house)
{
    int i;

    if (cell == DAT_00A9F9F8) {
        while (!DAT_0087F7E8.FUN_00568300(&cell))
            cell = CellStructInit(DAT_00A8B230->unknown_0218.RandomRanged(0, DAT_0087F914),
                                  DAT_00A8B230->unknown_0218.RandomRanged(0, DAT_0087F918));
    }
    DAT_00A9F9CC = cell;
    DAT_00A9FACC = static_cast<HouseClass*>(house);
    if (DAT_00A9FAB4 != 0)
        return;
    if (deferment != 0) {
        if (DAT_00A9FAB8 == 0 || DAT_00A9FAB8 >= deferment)
            DAT_00A9FAB8 = deferment;
        DAT_00827FC4 = duration;
        return;
    }
    FUN_0065FA70(13, cell);
    DAT_00827FC4 = duration;
    DAT_00827FC0 = CurrentFrame;
    DAT_00A9FAB4 = 1;
    for (i = 0; i < HouseClass_Array.Count; i++) {
        if (DAT_00A9FACC == 0 || !DAT_00A9FACC->IsAlliedWith(HouseClass_Array.Items[i])) {
            if (!HouseClass_Array.Items[i]->Defeated && DAT_00A8B538 == 0)
                HouseClass_Array.Items[i]->CreateRadarOutage(duration);
        }
    }
    if (CurrentPlayer)
        CurrentPlayer->RecheckRadar = true;
    ScenarioClass::UpdateLighting();
    if (DAT_008871E0->LightningPrintText) {
        int scheme = 3;
        if (CurrentPlayer)
            scheme = CurrentPlayer->ColorSchemeIndex;
        VocClass::PlayGlobal(DAT_008871E0->StormSound, 1.0f, 0x2000, 0);
        DAT_00A8BC60.FUN_005D3BA0(0, 0,
                                  FUN_00734E60("TXT_LIGHTNING_STORM", 0, "D:\\ra2mdpost\\Ion.cpp", 531),
                                  scheme, 0x4046, 150, 0);
    }
    DAT_0087F7E8.FUN_004F42F0(1);
}



// FUNCTION: GAMEMD 0x53A090
unsigned char __cdecl FUN_0053A090();
// FUNCTION: GAMEMD 0x53A0B0
void FUN_0053A0B0(int a1, int a2);

// FUNCTION: GAMEMD 0x53A090
// Branching.
unsigned char __cdecl FUN_0053A090()
{
    if (DAT_00A9FAB4 != 0)
    {
        DAT_00A9FAD0 = 1;
    }
    return DAT_00A9FAB4;
}

// FUNCTION: GAMEMD 0x53A0B0
// Branching.
void FUN_0053A0B0(int a1, int a2)
{
    if (DAT_00A9FAB4 != (unsigned char)0)
    {
        unsigned char t1 = DAT_00A9FAB4;
        DAT_00A9FAB4 = 0;
        DAT_00A9FACC = 0;
        DAT_00A9F9CC = DAT_00A9F9F8;
        ScenarioClass::UpdateLighting();
    }
}

// FUNCTION: GAMEMD 0x53A0E0
// Branching.
bool __cdecl FUN_0053A0E0()
{
    return DAT_00A9FAB4 != 0 || DAT_00A9FAB8 > 0;
}

// FUNCTION: GAMEMD 0x53A110
// Returns a comparison result.
bool __cdecl FUN_0053A110()
{
    return DAT_00A9FABC == 1;
}

// FUNCTION: GAMEMD 0x53A120
// Returns a comparison result.
bool __cdecl FUN_0053A120()
{
    return DAT_00A9FABC == 2;
}

// FUNCTION: GAMEMD 0x53A130  HouseClass::IonSensitivesShouldBeOffline (__thiscall)
//   XOR AL,AL ; RET   (unconditional false)
bool HouseClass::IonSensitivesShouldBeOffline() const
{
    return false;
}

// GLOBAL: GAMEMD 0xA9FA84
extern int DAT_00A9FA84;
// GLOBAL: GAMEMD 0xA9FA90
extern int DAT_00A9FA90;
// GLOBAL: GAMEMD 0xA9FA30
extern HeaderCoordInit DAT_00A9FA30;
// FUNCTION: GAMEMD 0x6D2120 (decl; reloc)
int FUN_006D2120(int);

// FUNCTION: GAMEMD 0x53A140
// Spawns one cloud animation over a cell unless it is the cell already used; the animation
// goes on two of the animation lists.
void __stdcall FUN_0053A140(CellStruct cell)
{
    CellClass* cellObj = DAT_0087F7E8.FUN_005657A0(&cell);
    int half = static_cast<SHPStruct*>(const_cast<AnimTypeClass*>(DAT_008871E0->WeatherConBolts.Items[0])->vf_39())->unknown_04 / 2;
    int base = FUN_006D2120(half);
    int z = base + ((cellObj->Flags & 0x100) ? DAT_00A9FA84 : 0) + cellObj->Level * DAT_00A9FA90;
    CoordStruct coord;
    coord.X = (cell.X << 8) + 0x80;
    coord.Y = (cell.Y << 8) + 0x80;
    coord.Z = z;
    if (coord.X != DAT_00A9FA30.X || coord.Y != DAT_00A9FA30.Y || coord.Z != DAT_00A9FA30.Z) {
        unsigned int pick = (unsigned int)DAT_00A8B230->unknown_0218.Random() % DAT_008871E0->WeatherConClouds.Count;
        AnimTypeClass* type = const_cast<AnimTypeClass*>(DAT_008871E0->WeatherConClouds.Items[pick]);
        AnimClass* anim = new AnimClass(type, coord, 0, 1, 0x600, 0, 0);
        StaticVectorHolder_00A9FA60::DAT_00A9FA60.AddItem(anim);
        StaticVectorHolder_00A9F9D0::DAT_00A9F9D0.AddItem(anim);
    }
}

// FUNCTION: GAMEMD 0x53AB50  LightningStorm::Init (__fastcall, static)
// Re-light the map for the storm, then raise the local player's flag. The
// lighting call takes no arguments, so retail issues it before touching the
// global at all.
void LightningStorm::Init()
{
    ScenarioClass::UpdateLighting();
    CurrentPlayer->RecheckRadar = true;
}

// FUNCTION: GAMEMD 0x53AB70
// Other translation units declare this entry extern "C"; the definition keeps that linkage.
// Starts the storm sequence: the timer takes the current frame and the
// duration 1 (its middle word is left as it was on the stack), the light
// level switches to the storm tint.
extern "C" void __fastcall FUN_0053AB70()
{
    DAT_00A9FABC = 1;
    DAT_00827FCC = 30;
    DAT_00827FC8 = CurrentFrame;
    DAT_00A8B230->unknown_1248 = ScenarioTimer(1);
    DAT_00A8B230->unknown_3530 = DAT_00A8B230->unknown_3560;
    ScenarioClass::RecalcLighting(DAT_00A8B230->unknown_3564 * 1000 / 100,
                                  DAT_00A8B230->unknown_3568 * 1000 / 100,
                                  DAT_00A8B230->unknown_356C * 1000 / 100, true);
    DAT_0087F7E8.FUN_004F42F0(1);
}

// FUNCTION: GAMEMD 0x53AD00
//
// Push a new ambient tint through every light converter: the registry of
// converters, the converter of each colour scheme that has more than one
// remap level, and the converters of every per-palette scheme vector the hash
// iterator yields. Then the map re-sweeps its cell lighting and the sidebar is
// flagged for redraw.
void ScenarioClass::RecalcLighting(int r, int g, int b, bool tint)
{
    int i;

    for (i = 0; i < DAT_0087F698.Count; i++) {
        LightConvert_0053AD00* lc = DAT_0087F698.Items[i];
        (lc->*lc->Vtbl->At_04)(r, g, b, tint);
    }

    for (i = 0; i < DAT_00B054D0.Count; i++) {
        ColorScheme_0053AD00* scheme = DAT_00B054D0.Items[i];
        if (scheme->At_310 > 1) {
            LightConvert_0053AD00* lc = scheme->LightConvert;
            (lc->*lc->Vtbl->At_04)(r, g, b, tint);
        }
    }

    HashIterator_0053AD00 it;
    it.At_00 = 0;
    it.At_04 = 0;
    it.At_08 = 0;
    ColorSchemeVec_0053AD00* vec = FUN_00626690(&it);
    while (vec != 0) {
        int count = FUN_00626C60();
        for (i = 0; i < count; i++) {
            LightConvert_0053AD00* lc = vec->Items[i]->LightConvert;
            (lc->*lc->Vtbl->At_04)(r, g, b, tint);
        }
        vec = FUN_00626690(&it);
    }

    MapInstance.FUN_004AE4C0();
    MapInstance.FlagToRedraw(1);
}

// FUNCTION: GAMEMD 0x53AE50
// Starts the dominator sequence on a cell: the first animation above the cell, the timer and the tint.
void __fastcall FUN_0053AE50(int a, CellStruct cell)
{
    if (DAT_008871E0->DominatorFirstAnim != 0 && DAT_008871E0->DominatorSecondAnim != 0) {
        DAT_00A9FA48 = cell;
        DAT_00A9FAC8 = a;
        AnimTypeClass* type = DAT_008871E0->DominatorFirstAnim;
        CoordStruct coord = DAT_0087F7E8.FUN_005657A0(&DAT_00A9FA48)->vf_18();
        coord.Z += 0x2EE;
        DAT_00A9FAC4 = new AnimClass(type, coord, 0, 1, 0x600, 0, 0);
        DAT_00A9FAC0 = 1;
        DAT_00A8B230->unknown_1248 = ScenarioTimer(1);
        ScenarioClass::UpdateLighting();
    }
}

// GLOBAL: GAMEMD 0xA9F9B8
extern AudioController DAT_00A9F9B8;
// GLOBAL: GAMEMD 0xA9FAA8
extern int DAT_00A9FAA8;
// GLOBAL: GAMEMD 0xA9FAD1
extern unsigned char DAT_00A9FAD1;
// FUNCTION: GAMEMD 0x684240 (decl; reloc)
void __cdecl FUN_00684240();
// FUNCTION: GAMEMD 0x753570 (decl; reloc)
void FUN_00753570();
// Forward declaration of 0x53BAF0, defined below.
void __fastcall FUN_0053BAF0();

// FUNCTION: GAMEMD 0x53B3F0
// Empty function.
void __cdecl FUN_0053B3F0()
{
}

// FUNCTION: GAMEMD 0x53B400
// Returns a comparison result.
bool __cdecl FUN_0053B400()
{
    return (DAT_00A9FAC0 != 0) ? true : false;
}

// FUNCTION: GAMEMD 0x53B460
// Begins a storm of the given length: refreshes the offscreen copy of the screen, flags the
// state, plays the sound and sets the follow-up globals.
void FUN_0053B460(int value)
{
    if (value > 0) {
        FUN_0053BAF0();
        DAT_00A9FA98 = value;
        DAT_00A9FAA8 = value;
        DAT_00A9FAB0 = 1;
        FUN_00406E80();
        FUN_007529A0(true);
        DAT_00A9F9B8.FUN_00405BE0();
        VocClass::PlayGlobal(DAT_008871E0->LetsDoTheTimeWarpOutAgain, 1.0f, 0x2000, &DAT_00A9F9B8);
        FUN_007518C0(0);
        DAT_00A9FAD1 = DAT_00A8B230->unknown_35A2;
        FUN_00684240();
        FUN_00753570();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0053BAD0
bool FUN_0053BAD0()
{
    return DAT_00A9FAB0 != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0053BAE0
bool FUN_0053BAE0()
{
    return DAT_00A9FAB0 != 0;
}

// FUNCTION: GAMEMD 0x53BAF0
// Replaces the offscreen copy of the display surface with a fresh one.
void __fastcall FUN_0053BAF0()
{
    if (DAT_00A9FA9C) {
        delete DAT_00A9FA9C;
        DAT_00A9FA9C = 0;
    }
    DAT_00A9FA9C = new DSurface(DAT_0088731C->GetWidth(), DAT_0088731C->GetHeight(), true, false);
    DAT_00A9FA9C->CopyFromWhole(DAT_0088731C, false, true);
    DAT_00A9FAA0 = 0;
    DAT_00A9FAA4 = 0;
}

// FUNCTION: GAMEMD 0x53C280  ScenarioClass::UpdateLighting
// Picks the tint for the current lightning-storm phase and pushes it through
// every converter.
void ScenarioClass::UpdateLighting()
{
    if (DAT_00A9FABC != 1 && DAT_00A9FAB0 == 0) {
        if (DAT_00A9FAB4) {
            DAT_00A8B230->unknown_3530 = DAT_00A8B230->unknown_3548;
            RecalcLighting(DAT_00A8B230->unknown_354C * 1000 / 100,
                           DAT_00A8B230->unknown_3550 * 1000 / 100,
                           DAT_00A8B230->unknown_3554 * 1000 / 100, true);
        } else if (DAT_00A9FAC0 != 0 && DAT_00A9FAC0 != 5) {
            DAT_00A8B230->unknown_3530 = DAT_00A8B230->unknown_357C;
            RecalcLighting(DAT_00A8B230->unknown_3580 * 1000 / 100,
                           DAT_00A8B230->unknown_3584 * 1000 / 100,
                           DAT_00A8B230->unknown_3588 * 1000 / 100, true);
        } else {
            DAT_00A8B230->unknown_3530 = DAT_00A8B230->unknown_3528;
            RecalcLighting(-1, -1, -1, false);
        }
    } else {
        DAT_00A8B230->unknown_3530 = DAT_00A8B230->unknown_3560;
        RecalcLighting(DAT_00A8B230->unknown_3564 * 1000 / 100,
                       DAT_00A8B230->unknown_3568 * 1000 / 100,
                       DAT_00A8B230->unknown_356C * 1000 / 100, true);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x53C450  TechnoClass::CanBePermaMindControlled (__thiscall)
// A chain of disqualifiers, each returning early — which is why retail carries
// five separate `XOR AL,AL; POP ESI; RET` epilogues rather than one shared exit.
// It opens by testing `this` itself, so retail expects to be called on a
// possibly-null pointer.
//
// The final disqualifier is written as a branch, not a negation. `return !x;`,
// `x == 0` and `x == false` all compile to the full-width bool idiom
// `NEG AL; SBB EAX,EAX; INC EAX` regardless of whether the slot is typed bool,
// unsigned char or int — a standalone probe confirmed all six combinations.
// Writing it as a branch instead (`if (x) return false; return true;`, or the
// equivalent ternary) gives retail's `TEST AL,AL; SETE AL`. That is the whole
// difference between the earlier 91.8% and byte parity here.
bool TechnoClass::CanBePermaMindControlled()
{
    // Retail entry: mov esi,ecx / test esi,esi at 0x53C453; the null arm returns false.
    // THISNULL: GAMEMD 0x53C450
    if (this == 0)
        return false;

    if (TECHNO_WHAT_AM_I(this) == ABS_BUILDING)
        return false;

    if (TECHNO_GET_TYPE(this)->ImmuneToPsionics)
        return false;

    if (TECHNO_SLOT_160(this))
        return false;

    if (TECHNO_GET_TYPE(this)->BalloonHover)
        return false;

    if (TECHNO_SLOT_54(this))
        return false;

    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x53C4C0
// DynamicVectorClass<const AnimClass*>::Clear

// FUNCTION: GAMEMD 0x53C4F0
// DynamicVectorClass<const AnimClass*>::Slot5

// FUNCTION: GAMEMD 0x53C510
// VectorClass<const AnimClass*>::Slot6

// FUNCTION: GAMEMD 0x53C520
// VectorClass<const AnimClass*>::operator==

// FUNCTION: GAMEMD 0x53C560
// VectorClass<const AnimClass*>::SetCapacity

// FUNCTION: GAMEMD 0x53C610
// VectorClass<const AnimClass*>::Clear

// FUNCTION: GAMEMD 0x53C640
// VectorClass<const AnimClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x53C680
// VectorClass<const AnimClass*>::Slot5

// FUNCTION: GAMEMD 0x53C6A0
// DynamicVectorClass<const AnimClass*>::SetCapacity

// FUNCTION: GAMEMD 0x53C750
// DynamicVectorClass<const AnimClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x53C780
// VectorClass<const AnimClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x53C7D0
// DynamicVectorClass<const AnimClass*>::scalar deleting destructor

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA9FAB4
unsigned char DAT_00A9FAB4;
// GLOBAL: GAMEMD 0xA9FABC
int DAT_00A9FABC;
// GLOBAL: GAMEMD 0xA9FAC0
int DAT_00A9FAC0;
// GLOBAL: GAMEMD 0xA9FACC
HouseClass* DAT_00A9FACC;
// GLOBAL: GAMEMD 0xA9FAD0
unsigned char DAT_00A9FAD0;
// GLOBAL: GAMEMD 0xA9FAB8
int DAT_00A9FAB8;
// GLOBAL: GAMEMD 0x87F698
extern LightConvertVec_0053AD00 DAT_0087F698;
// GLOBAL: GAMEMD 0xB054D0
extern ColorSchemeVec_0053AD00 DAT_00B054D0;
// END defined globals
