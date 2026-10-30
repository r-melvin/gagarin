// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Support declarations for the BuildingClass bodies of the tu038 cluster (entries 0x43B740..0x44EFB0). The
//   bodies are written against the canonical BuildingClass, HouseClass, BuildingTypeClass, CellClass, FactoryClass
//   and RulesClass in _layout; what remains here are small partial views of objects that have no canonical
//   header yet (the production object, the event queue, the map and global index singletons), the retail entry
//   points those bodies call, and BuildingAView, a sparse stand-in for BuildingClass that only carries the two
//   bodies that cannot move: vf_10 (the pointer-expiry slot, whose argument the body inspects as an object while
//   every base declares it void*) and vf_194 (a DirStruct written straight into the hidden return slot, which
//   needs the pointer spelling that TechnoClass::vf_194 and UnitClass::vf_194 do not share). RTTI of the class is
//   .?AVBuildingClass@@ (type descriptor 0x818D60, primary table 0x7E3EBC). Slots are the retail primary-table
//   indices (byte offset / 4); the virtual declarations named vt_XXX are placeholders that only position the
//   slots actually used.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A_VIEWS_H

#include <stddef.h>
#include "../../_layout/session_class.h"
#include "../../core/vector_class.h"
#include "../../_rt/gg_static_assert.h"
#include "house_building_layout.h"
#include "../../audio/voc_class_play_global_methods.h"
#include "house_building_views.h"
#include "../../_layout/cell_class.h"
#include "../../_layout/map_0087f7e8.h"
#include "../../network/event_queue.h"
#include "house_building_views.h"
#include "house_building_views.h"

class BAObjView;
class HouseClass;
class BuildingTypeClass;
class BuildingAView;
class BAProdView;
struct BAFlashView;

// The member at BuildingClass +0x150 (partial): only the method reached from the registration code.
struct BAFlashView
{
    // FUNCTION: GAMEMD 0x750090 (read-only here)
    void FUN_00750090(int arg);
};

// The audio controller member at BuildingClass +0x6A0 (partial).
struct BAAudioView
{
    // FUNCTION: GAMEMD 0x406060 (read-only here)
    void FUN_00406060();
};

// The facing member at BuildingClass +0x388 (partial).
struct BAFacing
{
    // FUNCTION: GAMEMD 0x4C93D0 (read-only here)
    HBDir FUN_004C93D0();
    // FUNCTION: GAMEMD 0x4C9680 (read-only here)
    void FUN_004C9680(int value);
    // FUNCTION: GAMEMD 0x4C9300 (read-only here)
    void FUN_004C9300(HBDir* dir);
};

// A vector of pointers (vptr, Items, Capacity, IsInitialized, IsAllocated, Count, CapacityIncrement; 0x18
// bytes). Only slot 2 (SetCapacity) is reached by the inlined AddItem.
template <class T> class BAVector
{
public:
    virtual void vt_0();
    virtual bool vt_1();
    virtual bool SetCapacity(int capacity, T* mem);   // slot 2
    virtual void vt_3();
    virtual int FindItemIndex(T* item);              // slot 4

    T*            Items;               // +0x04
    int           Capacity;            // +0x08
    bool          IsInitialized;       // +0x0C
    bool          IsAllocated;         // +0x0D
    unsigned char unknown_0E[2];       // +0x0E
    int           Count;               // +0x10
    int           CapacityIncrement;   // +0x14

    // DynamicVectorClass::RemoveItem, expanded inline by the original.
    bool RemoveItem(T item)
    {
        int index = FindItemIndex(&item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index) {
                Items[index] = Items[index + 1];
            }
            return true;
        }
        return false;
    }

    // DynamicVectorClass::AddItem, expanded inline by the original as one short-circuit condition.
    bool AddItem(const T& item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && SetCapacity(CapacityIncrement + cap, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(sizeof(BAVector<int*>) == 0x18);

// GLOBAL: GAMEMD 0x7E2820 / 0x7E2818 - the two double constants of the facing-angle conversion.
extern const double DAT_007E2820;
extern const double DAT_007E2818;
// GLOBAL: GAMEMD 0xA8E7AC / 0xA8ED6B
extern int DAT_00A8E7AC;
extern unsigned char DAT_00A8ED6B;

// STRING: GAMEMD 0x818F18 / 0x818F28 - the EVA speech names.
extern const char s_EVA_Repairing_00818F18[];
extern const char s_EVA_PrimaryBuildingSelected_00818F28[];
// FUNCTION: GAMEMD 0x752700 (read-only here) - the string in ECX, two further arguments (EDX and the stack).
void FUN_00752700(const char* name, int a, int b);
// FUNCTION: GAMEMD 0x7509E0 (read-only here) - plays a sound at a position.
void FUN_007509E0(int sound, HBCoord* where, void* unused);
// FUNCTION: GAMEMD 0x7509E0 (read-only here) - the same call with the canonical coordinate.
void FUN_007509E0(int sound, CoordStruct* where, void* unused);
// FUNCTION: GAMEMD 0x750D40 (read-only here) - stops/plays the sound of an audio controller at a position.
void FUN_00750D40(HBCoord* where, struct BAAudioView* audio);
// FUNCTION: GAMEMD 0x750D40 (read-only here) - the same call with the canonical coordinate and controller.
void FUN_00750D40(const CoordStruct* where, AudioController* audio);

// FUNCTION: GAMEMD 0x6D20E0 (read-only here) - one register argument: __fastcall.
int FUN_006D20E0(int key);
// FUNCTION: GAMEMD 0x4CAE30 (read-only here)
double __cdecl FUN_004CAE30(double a, double b);
// FUNCTION: GAMEMD 0x4CAC40 (read-only here)
double __cdecl FUN_004CAC40(double a);

// The IRTTITypeInfo table at +0x04 of an object (stdcall slots).
class BARttiView
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual int __stdcall vf_3();   // slot 3, +0xC

};

// Second-level object reached through slot 33 of a production object (partial).
class BAProdTypeView
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual int vf_16(int a, int b);   // slot 16, +0x40
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual int vf_37(int a, int b, int c, HouseClass* owner);   // slot 37, +0x94

};

// Object returned by FUN_004CA160 (partial).
class BAProdView
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual BAProdTypeView* vf_33();   // slot 33, +0x84

};

// Type object of a BAObjView (partial).
struct BAObjTypeView
{
    char _pad_0000[0x233];   // +0x0000
    unsigned char unknown_233;   // +0x0233
    char _pad_0234[0x70];   // +0x0234
    unsigned char unknown_2A4;   // +0x02A4
    unsigned char unknown_2A5;   // +0x02A5
};
GG_STATIC_ASSERT(offsetof(BAObjTypeView, unknown_233) == 0x233);
GG_STATIC_ASSERT(offsetof(BAObjTypeView, unknown_2A4) == 0x2A4);
GG_STATIC_ASSERT(offsetof(BAObjTypeView, unknown_2A5) == 0x2A5);

// A target / object seen through a slot (partial): only the slots used.
class BAObjView
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vf_8(int flag);   // slot 8, +0x20
    virtual void vt_024();
    virtual void vt_028();
    virtual int vf_11();   // slot 11, +0x2C
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual HBCoord* vf_18(HBCoord* out);   // slot 18, +0x48
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual BAObjTypeView* vf_34();   // slot 34, +0x88
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual void vt_0A8();
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual void vt_0B8();
    virtual void vt_0BC();
    virtual void vt_0C0();
    virtual void vt_0C4();
    virtual void vt_0C8();
    virtual void vt_0CC();
    virtual void vt_0D0();
    virtual void vt_0D4();
    virtual void vt_0D8();
    virtual void vt_0DC();
    virtual void vt_0E0();
    virtual void vt_0E4();
    virtual void vt_0E8();
    virtual void vt_0EC();
    virtual void vt_0F0();
    virtual void vt_0F4();
    virtual void vt_0F8();
    virtual void vt_0FC();
    virtual void vt_100();
    virtual void vt_104();
    virtual void vt_108();
    virtual void vt_10C();
    virtual void vt_110();
    virtual void vt_114();
    virtual void vt_118();
    virtual void vt_11C();
    virtual void vt_120();
    virtual void vt_124();
    virtual void vt_128();
    virtual void vt_12C();
    virtual void vt_130();
    virtual void vt_134();
    virtual void vt_138();
    virtual void vt_13C();
    virtual void vt_140();
    virtual void vt_144();
    virtual void vt_148();
    virtual void vt_14C();
    virtual void vt_150();
    virtual void vt_154();
    virtual void vt_158();
    virtual void vt_15C();
    virtual void vt_160();
    virtual void vt_164();
    virtual void vt_168();
    virtual void vt_16C();
    virtual void vt_170();
    virtual void vt_174();
    virtual void vt_178();
    virtual void vt_17C();
    virtual void vt_180();
    virtual int vf_97();   // slot 97, +0x184

    BARttiView unknown_04;   // +0x0004
    char _pad_0008[0xC];   // +0x0008
    unsigned char unknown_14;   // +0x0014
    char _pad_0015[0x8B];   // +0x0015
    BAObjTypeView* Type;   // +0x00A0
    char _pad_00A4[0x74];   // +0x00A4
    unsigned char unknown_118;   // +0x0118
    char _pad_0119[0x407];   // +0x0119
    BuildingTypeClass* unknown_520;   // +0x0520
};
GG_STATIC_ASSERT(offsetof(BAObjView, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(BAObjView, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BAObjView, Type) == 0xA0);
GG_STATIC_ASSERT(offsetof(BAObjView, unknown_118) == 0x118);
GG_STATIC_ASSERT(offsetof(BAObjView, unknown_520) == 0x520);

// Object behind the global at 0x87F770 (partial).
struct BAGlobalAView
{
    // FUNCTION: GAMEMD 0x54F5C0 (read-only here)
    bool FUN_0054F5C0(int value);
};

// Partial BuildingClass view (sizeof not modelled).
class BuildingAView
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vf_10(BAObjView* ptr, bool removed);   // slot 10, +0x28
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual void vt_0A8();
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual void vt_0B8();
    virtual void vt_0BC();
    virtual void vt_0C0();
    virtual void vt_0C4();
    virtual void vt_0C8();
    virtual void vt_0CC();
    virtual void vt_0D0();
    virtual void vt_0D4();
    virtual void vt_0D8();
    virtual void vt_0DC();
    virtual void vt_0E0();
    virtual void vt_0E4();
    virtual void vt_0E8();
    virtual void vt_0EC();
    virtual void vt_0F0();
    virtual void vt_0F4();
    virtual void vt_0F8();
    virtual void vt_0FC();
    virtual void vt_100();
    virtual void vt_104();
    virtual void vt_108();
    virtual void vt_10C();
    virtual void vt_110();
    virtual void vt_114();
    virtual void vt_118();
    virtual void vt_11C();
    virtual void vt_120();
    virtual void vt_124();
    virtual void vt_128();
    virtual void vt_12C();
    virtual void vt_130();
    virtual void vt_134();
    virtual void vt_138();
    virtual void vt_13C();
    virtual void vt_140();
    virtual void vt_144();
    virtual void vt_148();
    virtual void vt_14C();
    virtual void vt_150();
    virtual void vt_154();
    virtual void vt_158();
    virtual void vt_15C();
    virtual void vt_160();
    virtual void vt_164();
    virtual void vt_168();
    virtual void vt_16C();
    virtual void vt_170();
    virtual void vt_174();
    virtual void vt_178();
    virtual void vt_17C();
    virtual void vt_180();
    virtual void vt_184();
    virtual void vt_188();
    virtual void vt_18C();
    virtual void vt_190();
    virtual void vt_194();
    virtual void vt_198();
    virtual void vt_19C();
    virtual void vt_1A0();
    virtual void vt_1A4();
    virtual void vt_1A8();
    virtual void vt_1AC();
    virtual void vt_1B0();
    virtual void vt_1B4();
    virtual void vt_1B8();
    virtual void vt_1BC();
    virtual void vt_1C0();
    virtual void vt_1C4();
    virtual void vt_1C8();
    virtual void vt_1CC();
    virtual void vt_1D0();
    virtual void vt_1D4();
    virtual void vt_1D8();
    virtual void vt_1DC();
    virtual void vt_1E0();
    virtual void vt_1E4();
    virtual void vt_1E8();
    virtual void vt_1EC();
    virtual void vt_1F0();
    virtual void vt_1F4();
    virtual void vt_1F8();
    virtual void vt_1FC();
    virtual void vt_200();
    virtual void vt_204();
    virtual void vt_208();
    virtual void vt_20C();
    virtual void vt_210();
    virtual void vt_214();
    virtual void vt_218();
    virtual void vt_21C();
    virtual void vt_220();
    virtual void vt_224();
    virtual void vt_228();
    virtual void vt_22C();
    virtual void vt_230();
    virtual void vt_234();
    virtual void vt_238();
    virtual void vt_23C();
    virtual void vt_240();
    virtual void vt_244();
    virtual void vt_248();
    virtual void vt_24C();
    virtual void vt_250();
    virtual void vt_254();
    virtual void vt_258();
    virtual void vt_25C();
    virtual void vt_260();
    virtual void vt_264();
    virtual void vt_268();
    virtual void vt_26C();
    virtual void vt_270();
    virtual void vt_274();
    virtual void vt_278();
    virtual void vt_27C();
    virtual void vt_280();
    virtual void vt_284();
    virtual void vt_288();
    virtual void vt_28C();
    virtual void vt_290();
    virtual void vt_294();
    virtual void vt_298();
    virtual void vt_29C();
    virtual void vt_2A0();
    virtual void vt_2A4();
    virtual void vt_2A8();
    virtual void vt_2AC();
    virtual void vt_2B0();
    virtual void vt_2B4();
    virtual void vt_2B8();
    virtual void vt_2BC();
    virtual void vt_2C0();
    virtual void vt_2C4();
    virtual void vt_2C8();
    virtual void vt_2CC();
    virtual void vt_2D0();
    virtual void vt_2D4();
    virtual void vt_2D8();
    virtual void vt_2DC();
    virtual void vt_2E0();
    virtual void vt_2E4();
    virtual void vt_2E8();
    virtual void vt_2EC();
    virtual void vt_2F0();
    virtual void vt_2F4();
    virtual void vt_2F8();
    virtual void vt_2FC();
    virtual void vt_300();
    virtual void vt_304();
    virtual HBDir* vf_194(HBDir* out);   // slot 194, +0x308
    virtual void vt_30C();
    virtual void vt_310();
    virtual void vt_314();
    virtual void vt_318();
    virtual void vt_31C();
    virtual void vt_320();
    virtual void vt_324();
    virtual void vt_328();
    virtual void vt_32C();
    virtual void vt_330();
    virtual void vt_334();
    virtual void vt_338();
    virtual void vt_33C();
    virtual void vt_340();
    virtual void vt_344();
    virtual void vt_348();
    virtual void vt_34C();
    virtual void vt_350();
    virtual void vt_354();
    virtual void vt_358();
    virtual void vt_35C();
    virtual void vt_360();
    virtual void vt_364();
    virtual void vt_368();
    virtual void vt_36C();
    virtual void vt_370();
    virtual void vt_374();
    virtual void vt_378();
    virtual void vt_37C();
    virtual void vt_380();
    virtual void vt_384();
    virtual void vt_388();
    virtual void vt_38C();
    virtual void vt_390();
    virtual void vt_394();
    virtual void vt_398();
    virtual void vt_39C();
    virtual void vt_3A0();
    virtual void vt_3A4();
    virtual void vt_3A8();
    virtual void vt_3AC();
    virtual void vt_3B0();
    virtual void vt_3B4();
    virtual void vt_3B8();
    virtual void vt_3BC();
    virtual void vt_3C0();
    virtual void vt_3C4();
    virtual void vt_3C8();
    virtual void vt_3CC();
    virtual void vt_3D0();
    virtual void vt_3D4();
    virtual void vt_3D8();
    virtual void vt_3DC();
    virtual void vt_3E0();
    virtual void vt_3E4();
    virtual void vt_3E8();
    virtual void vt_3EC();
    virtual void vt_3F0();
    virtual void vt_3F4();
    virtual void vt_3F8();
    virtual bool vf_255();   // slot 255, +0x3FC
    virtual void vt_400();
    virtual void vt_404();
    virtual void vt_408();
    virtual void vt_40C();
    virtual void vt_410();
    virtual void vt_414();
    virtual void vt_418();
    virtual void vt_41C();
    virtual void vt_420();
    virtual void vt_424();
    virtual void vt_428();
    virtual void vt_42C();
    virtual void vt_430();
    virtual void vt_434();
    virtual void vt_438();
    virtual void vt_43C();
    virtual void vt_440();
    virtual void vt_444();
    virtual void vt_448();
    virtual void vt_44C();
    virtual void vt_450();
    virtual void vt_454();
    virtual void vt_458();
    virtual void vt_45C();
    virtual void vt_460();
    virtual void vt_464();
    virtual void vt_468();
    virtual void vt_46C();
    virtual void vt_470();
    virtual void vt_474();
    virtual void vt_478();
    virtual void vt_47C();
    virtual void vt_480();
    virtual void vt_484();
    virtual void vt_488();
    virtual void vt_48C();
    virtual void vt_490();
    virtual void vt_494();
    virtual void vt_498();
    virtual void vt_49C();
    virtual void vt_4A0();
    virtual void vt_4A4();
    virtual void vt_4A8();
    virtual void vt_4AC();
    virtual void vt_4B0();
    virtual void vt_4B4();
    virtual void vt_4B8();
    virtual void vt_4BC();
    virtual void vt_4C0();
    virtual void vt_4C4();
    virtual void vt_4C8();
    virtual void vt_4CC();
    virtual void vt_4D0();
    virtual void vt_4D4();
    virtual void vt_4D8();
    virtual void vt_4DC();
    virtual void vt_4E0();
    virtual void vt_4E4();
    virtual HBDir vf_314(BAObjView* target);   // slot 314, +0x4E8
    virtual void vt_4EC();
    virtual void vt_4F0();

    char _pad_0004[0x68];   // +0x0004
    int unknown_6C;   // +0x006C
    int unknown_70;   // +0x0070
    unsigned char unknown_74;   // +0x0074
    char _pad_0075[0xB];   // +0x0075
    unsigned char unknown_80;   // +0x0080
    unsigned char unknown_81;   // +0x0081
    char _pad_0082[0x1A];   // +0x0082
    HBCoord Location;   // +0x009C
    char _pad_00A8[0x4];   // +0x00A8
    int unknown_AC;   // +0x00AC
    char _pad_00B0[0x4];   // +0x00B0
    int unknown_B4;   // +0x00B4
    char _pad_00B8[0x4];   // +0x00B8
    int unknown_BC;   // +0x00BC
    char _pad_00C0[0x4];   // +0x00C0
    int unknown_C4;   // +0x00C4
    char _pad_00C8[0x20];   // +0x00C8
    int unknown_E8;   // +0x00E8
    char _pad_00EC[0x28];   // +0x00EC
    int unknown_114;   // +0x0114
    char _pad_0118[0x38];   // +0x0118
    BAFlashView unknown_150;   // +0x0150
    char _pad_0151[0xCB];   // +0x0151
    HouseClass* Owner;   // +0x021C
    char _pad_0220[0x48];   // +0x0220
    unsigned char unknown_268;   // +0x0268
    char _pad_0269[0x4B];   // +0x0269
    BAObjView* Target;   // +0x02B4
    char _pad_02B8[0x8];   // +0x02B8
    int unknown_2C0;   // +0x02C0
    char _pad_02C4[0x38];   // +0x02C4
    int unknown_2FC;   // +0x02FC
    char _pad_0300[0x88];   // +0x0300
    BAFacing Facing;   // +0x0388
    char _pad_0389[0x4A];   // +0x0389
    unsigned char unknown_3D3;   // +0x03D3
    char _pad_03D4[0x47];   // +0x03D4
    unsigned char unknown_41B;   // +0x041B
    char _pad_041C[0x104];   // +0x041C
    BuildingTypeClass* Type;   // +0x0520
    BAObjView* Factory;   // +0x0524
    char _pad_0528[0xC];   // +0x0528
    int BState;   // +0x0534
    char _pad_0538[0x4];   // +0x0538
    int unknown_53C;   // +0x053C
    BAObjView* C4AppliedBy;   // +0x0540
    char _pad_0544[0x4];   // +0x0544
    BAObjView* FirestormAnim;   // +0x0548
    char _pad_054C[0x10];   // +0x054C
    BAObjView* Anims[0x15];   // +0x055C
    char _pad_05B0[0x18];   // +0x05B0
    BAObjView* DamageFireAnims[8];   // +0x05C8
    char _pad_05E8[0x4];   // +0x05E8
    BAObjView* Upgrades[3];   // +0x05EC
    char _pad_05F8[0x8];   // +0x05F8
    BAObjView* Spotlight;   // +0x0600
    char _pad_0604[0x10];   // +0x0604
    BAObjView* LightSource;   // +0x0614
    char _pad_0618[0x48];   // +0x0618
    unsigned char unknown_660;   // +0x0660
    char _pad_0661[0xB];   // +0x0661
    BAVector<BAObjView*> Overpowerers;   // +0x066C
    BAVector<BAObjView*> Occupants;   // +0x0684
    char _pad_069C[0x4];   // +0x069C
    BAAudioView unknown_6A0;   // +0x06A0
    char _pad_06A1[0x3B];   // +0x06A1
    unsigned char unknown_6DC;   // +0x06DC
    unsigned char unknown_6DD;   // +0x06DD
    unsigned char unknown_6DE;   // +0x06DE
    unsigned char unknown_6DF;   // +0x06DF
    char _pad_06E0[0x3];   // +0x06E0
    unsigned char unknown_6E3;   // +0x06E3
    char _pad_06E4[0x4];   // +0x06E4
    unsigned char unknown_6E8;   // +0x06E8
    unsigned char unknown_6E9;   // +0x06E9
    char _pad_06EA[0x2A];   // +0x06EA
    int unknown_714;   // +0x0714
    // FUNCTION: GAMEMD 0x7077C0 (read-only here)
    void FUN_007077C0(BAObjView* ptr, bool removed);
    // FUNCTION: GAMEMD 0x5F5C60 (read-only here)
    double FUN_005F5C60();
    // FUNCTION: GAMEMD 0x451890 (read-only here)
    void FUN_00451890(char* name, int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x451B40 (read-only here)
    void FUN_00451B40(BAObjView* ptr);
};
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_81) == 0x81);
GG_STATIC_ASSERT(offsetof(BuildingAView, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_E8) == 0xE8);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_150) == 0x150);
GG_STATIC_ASSERT(offsetof(BuildingAView, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_268) == 0x268);
GG_STATIC_ASSERT(offsetof(BuildingAView, Target) == 0x2B4);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_2C0) == 0x2C0);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(BuildingAView, Facing) == 0x388);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_3D3) == 0x3D3);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_41B) == 0x41B);
GG_STATIC_ASSERT(offsetof(BuildingAView, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingAView, Factory) == 0x524);
GG_STATIC_ASSERT(offsetof(BuildingAView, BState) == 0x534);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_53C) == 0x53C);
GG_STATIC_ASSERT(offsetof(BuildingAView, C4AppliedBy) == 0x540);
GG_STATIC_ASSERT(offsetof(BuildingAView, FirestormAnim) == 0x548);
GG_STATIC_ASSERT(offsetof(BuildingAView, Anims) == 0x55C);
GG_STATIC_ASSERT(offsetof(BuildingAView, DamageFireAnims) == 0x5C8);
GG_STATIC_ASSERT(offsetof(BuildingAView, Upgrades) == 0x5EC);
GG_STATIC_ASSERT(offsetof(BuildingAView, Spotlight) == 0x600);
GG_STATIC_ASSERT(offsetof(BuildingAView, LightSource) == 0x614);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_660) == 0x660);
GG_STATIC_ASSERT(offsetof(BuildingAView, Overpowerers) == 0x66C);
GG_STATIC_ASSERT(offsetof(BuildingAView, Occupants) == 0x684);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6A0) == 0x6A0);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6DC) == 0x6DC);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6DD) == 0x6DD);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6DE) == 0x6DE);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6DF) == 0x6DF);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6E3) == 0x6E3);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6E8) == 0x6E8);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6E9) == 0x6E9);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_714) == 0x714);

// GLOBAL: GAMEMD 0x887324 (pointer to the object above) and 0x89C848 (a zero coordinate triple)
extern class Tactical* DAT_00887324;
// GLOBAL: GAMEMD 0xA83CBC - an array of index entries
extern class HBIdxView** DAT_00A83CBC;
// GLOBAL: GAMEMD 0x7E27F8 - double constant
extern const double DAT_007E27F8;
// FUNCTION: GAMEMD 0x4CA160 (read-only here) - looks an object up by handle; one register argument: __fastcall.
class BAProdView* FUN_004CA160(class FactoryClass* factory);
// FUNCTION: GAMEMD 0x4C9FF0 (read-only here) - one register argument: __fastcall.
void FUN_004C9FF0(class BAObjView* factory);
// GLOBAL: GAMEMD 0x87F770 (pointer) and 0xA8EBF8 / 0xA8EBFC
extern BAGlobalAView* DAT_0087F770;
extern int DAT_00A8EBF8;
extern int DAT_00A8EBFC;
// GLOBAL: GAMEMD 0xA83D4C (the local player's house) and the four object lists scanned by slot 312
extern HouseClass* DAT_00A83D4C;
extern DynamicVectorClass<TechnoTypeClass*> DAT_00A8B218;
extern DynamicVectorClass<TechnoTypeClass*> DAT_00A83C68;
extern DynamicVectorClass<TechnoTypeClass*> DAT_00A8E348;
extern DynamicVectorClass<TechnoTypeClass*> DAT_00A83CE0;
// IMPORT: GAMEMD 0x7E1530 (winmm timeGetTime)
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
// GLOBAL: GAMEMD 0x8B41E0 - a vector of building pointers (the registration list).
extern BAVector<BuildingClass*> DAT_008B41E0;
extern CoordStruct DAT_0089C848;

// FUNCTION: GAMEMD 0x772A90 (read-only here) - one register argument: __fastcall.
unsigned int FUN_00772A90(BAObjView* entry);

// GLOBAL: GAMEMD 0xA8B230 / 0x8871E0
#include "../../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;




// BEGIN canonical-layout asserts
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6C) == HB_BLD_HEALTH);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_70) == HB_BLD_UNKNOWN_70);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_80) == HB_BLD_NEEDS_REDRAW);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_81) == HB_BLD_IN_LIMBO);
GG_STATIC_ASSERT(offsetof(BuildingAView, Location) == HB_BLD_LOCATION);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_AC) == HB_BLD_CURRENT_MISSION);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_B4) == HB_BLD_UNKNOWN_B4);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_BC) == HB_BLD_STATUS);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_C4) == HB_BLD_UNKNOWN_C4);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_E8) == HB_BLD_UNKNOWN_E8);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_114) == HB_BLD_UNKNOWN_114);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_150) == HB_BLD_UNKNOWN_150);
GG_STATIC_ASSERT(offsetof(BuildingAView, Owner) == HB_BLD_OWNER);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_268) == HB_BLD_UNKNOWN_268);
GG_STATIC_ASSERT(offsetof(BuildingAView, Target) == HB_BLD_TARGET);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_2C0) == HB_BLD_MIND_CONTROLLED_BY);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_2FC) == HB_BLD_UNKNOWN_2FC);
GG_STATIC_ASSERT(offsetof(BuildingAView, Facing) == HB_BLD_FACING);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_3D3) == HB_BLD_UNKNOWN_3D3);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_41B) == HB_BLD_UNKNOWN_41B);
GG_STATIC_ASSERT(offsetof(BuildingAView, Type) == HB_BLD_TYPE);
GG_STATIC_ASSERT(offsetof(BuildingAView, Factory) == HB_BLD_FACTORY);
GG_STATIC_ASSERT(offsetof(BuildingAView, BState) == HB_BLD_BSTATE);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_53C) == HB_BLD_OWNER_COUNTRY_INDEX);
GG_STATIC_ASSERT(offsetof(BuildingAView, C4AppliedBy) == HB_BLD_C4_APPLIED_BY);
GG_STATIC_ASSERT(offsetof(BuildingAView, FirestormAnim) == HB_BLD_FIRESTORM_ANIM);
GG_STATIC_ASSERT(offsetof(BuildingAView, Anims) == HB_BLD_ANIMS);
GG_STATIC_ASSERT(offsetof(BuildingAView, DamageFireAnims) == HB_BLD_DAMAGE_FIRE_ANIMS);
GG_STATIC_ASSERT(offsetof(BuildingAView, Upgrades) == HB_BLD_UPGRADES);
GG_STATIC_ASSERT(offsetof(BuildingAView, Spotlight) == HB_BLD_SPOTLIGHT);
GG_STATIC_ASSERT(offsetof(BuildingAView, LightSource) == HB_BLD_LIGHT_SOURCE);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_660) == HB_BLD_HAS_POWER);
GG_STATIC_ASSERT(offsetof(BuildingAView, Overpowerers) == HB_BLD_OVERPOWERERS);
GG_STATIC_ASSERT(offsetof(BuildingAView, Occupants) == HB_BLD_OCCUPANTS);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6A0) == HB_BLD_AUDIO7);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6DC) == HB_BLD_UNKNOWN_6DC);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6DD) == HB_BLD_IS_READY_TO_COMMENCE);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6DE) == HB_BLD_NEEDS_REPAIRS);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6DF) == HB_BLD_C4_APPLIED);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6E3) == HB_BLD_HAS_BEEN_CAPTURED);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_6E8) == HB_BLD_IS_BEING_REPAIRED);
GG_STATIC_ASSERT(offsetof(BuildingAView, unknown_714) == HB_BLD_UNKNOWN_714);
// END canonical-layout asserts

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A_VIEWS_H
