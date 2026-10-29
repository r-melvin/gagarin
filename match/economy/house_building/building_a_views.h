// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Cluster-scoped partial views for the "building-a" part of the house/building module (BuildingClass
//   entries 0x43B740..0x44EFB0). Every field below is a [reg+disp] operand read from the retail gamemd.exe
//   v1.001 in one of the functions of this cluster (see the .cpp files for the addresses). RTTI of the
//   class is .?AVBuildingClass@@ (type descriptor 0x818D60, primary table 0x7E3EBC). The views are NOT the
//   canonical BuildingClass / BuildingTypeClass: they are address/cluster-scoped and sparse, and are to
//   be consolidated later. Slots are the retail primary-table indices (byte offset / 4);
//   the virtual declarations named vt_XXX are placeholders that only position the slots actually used.
//   The views are sparse: no vtable, class size or ctor is claimed. BuildingClass (0x43B740) is BLOCKED on the
//   canonical TechnoClass / secondary-base integration, not yet in the tree.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A_VIEWS_H

#include <stddef.h>
#include "../../_layout/session_class.h"
#include "../../_rt/gg_static_assert.h"
#include "house_building_layout.h"
#include "../../audio/voc_class_play_global_methods.h"
#include "house_building_views.h"
#include "../../_layout/cell_class.h"
#include "house_building_views.h"
#include "house_building_views.h"

class BAObjView;
class BATypeView;
class BAHouseView;
class BuildingAView;
class BACountryView;
class BAProdView;
struct BAFlashView;

// A target reference (a 32-bit value and one tag byte; copied member-wise as five bytes, passed in eight).
#pragma pack(push, 1)
// Not merged: takes this cluster's BuildingClass view (see house_building_views.h).
struct BATargetRef
{
    int           Value;   // +0x00
    unsigned char Tag;     // +0x04
    // FUNCTION: GAMEMD 0x6E6AB0 (read-only here) - builds the reference to a building in place.
    BATargetRef* FUN_006E6AB0(BuildingAView* b);
};
#pragma pack(pop)
GG_STATIC_ASSERT(sizeof(BATargetRef) == 5);

// A queued network event (0x6F bytes; opaque here).
struct BAEvent
{
    unsigned char bytes[0x6F];
    BAEvent() {}
    // FUNCTION: GAMEMD 0x4C65E0 (read-only here)
    BAEvent* FUN_004C65E0(int owner, int kind, BATargetRef target);
};
GG_STATIC_ASSERT(sizeof(BAEvent) == 0x6F);

// The outgoing event ring buffer (0x128 events) with its timestamps.
struct BAEventQueue
{
    int     Count;          // +0x00
    int     unknown_04;     // +0x04
    int     Head;           // +0x08
    BAEvent List[128];      // +0x0C
    unsigned long unknown_378C[128];   // +0x378C
};
GG_STATIC_ASSERT(offsetof(BAEventQueue, Head) == 0x08);
GG_STATIC_ASSERT(offsetof(BAEventQueue, List) == 0x0C);
GG_STATIC_ASSERT(offsetof(BAEventQueue, unknown_378C) == 0x378C);

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
    virtual int vf_37(int a, int b, int c, BAHouseView* owner);   // slot 37, +0x94

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
    BATypeView* unknown_520;   // +0x0520
};
GG_STATIC_ASSERT(offsetof(BAObjView, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(BAObjView, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BAObjView, Type) == 0xA0);
GG_STATIC_ASSERT(offsetof(BAObjView, unknown_118) == 0x118);
GG_STATIC_ASSERT(offsetof(BAObjView, unknown_520) == 0x520);

// What BuildingClass slot 254 returns: a pointer whose first member is tested.
struct BASlotView
{
    BAObjView* First;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(BASlotView, First) == 0x0);

// A map cell object (partial).
class BACellView
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
    virtual HBCoord* vf_18(HBCoord* out);   // slot 18, +0x48

    char _pad_0004[0x48];   // +0x0004
    int unknown_4C;   // +0x004C
    char _pad_0050[0x9C];   // +0x0050
    int unknown_EC;   // +0x00EC
    char _pad_00F0[0x50];   // +0x00F0
    unsigned int unknown_140;   // +0x0140
    // FUNCTION: GAMEMD 0x47C620 (read-only here)
    bool FUN_0047C620(int a, BATypeView* type, BAHouseView* owner);
};
GG_STATIC_ASSERT(offsetof(BACellView, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(BACellView, unknown_EC) == 0xEC);
GG_STATIC_ASSERT(offsetof(BACellView, unknown_140) == 0x140);

// The map object (partial).
struct BAMapView
{
    // FUNCTION: GAMEMD 0x5657A0 (read-only here)
    BACellView* FUN_005657A0(HBCell* cell);
    // FUNCTION: GAMEMD 0x5657A0 (read-only here) - the same call with canonical types.
    CellClass* FUN_005657A0(CellStruct* cell);
    // FUNCTION: GAMEMD 0x6A6300 (read-only here)
    void FUN_006A6300(int kind, int index);
    // FUNCTION: GAMEMD 0x586360 (read-only here)
    bool FUN_00586360(HBCoord* where);
};

// An object asking about a placement (partial): the cell it stands on is at +0x24.
struct BAOccupierView
{
    char _pad_0000[0x24];   // +0x0000
    HBCell Cell;   // +0x0024
};
GG_STATIC_ASSERT(offsetof(BAOccupierView, Cell) == 0x24);

// Object behind the global at 0x8871E0 (partial).
struct BARulesView
{
    char _pad_0000[0x6C8];   // +0x0000
    int unknown_6C8;   // +0x06C8
    char _pad_06CC[0x34];   // +0x06CC
    int unknown_700;   // +0x0700
    char _pad_0704[0x8];   // +0x0704
    int unknown_70C;   // +0x070C
    char _pad_0710[0x860];   // +0x0710
    int unknown_F70;   // +0x0F70
    char _pad_0F74[0x78C];   // +0x0F74
    double unknown_1700;   // +0x1700
};
GG_STATIC_ASSERT(offsetof(BARulesView, unknown_6C8) == 0x6C8);
GG_STATIC_ASSERT(offsetof(BARulesView, unknown_700) == 0x700);
GG_STATIC_ASSERT(offsetof(BARulesView, unknown_70C) == 0x70C);
GG_STATIC_ASSERT(offsetof(BARulesView, unknown_F70) == 0xF70);
GG_STATIC_ASSERT(offsetof(BARulesView, unknown_1700) == 0x1700);

// Sub-object at the owning house +0x24: COM-style slots that take the object pointer on the stack.
class BAIntervalView
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
    virtual int __stdcall vf_8();   // slot 8, +0x20
    virtual int __stdcall vf_9();   // slot 9, +0x24

};

// Object behind the global at 0x87F770 (partial).
struct BAGlobalAView
{
    // FUNCTION: GAMEMD 0x54F5C0 (read-only here)
    bool FUN_0054F5C0(int value);
};

// Object at the owning house +0x34 (partial).
struct BACountryView
{
    char _pad_0000[0xB8];   // +0x0000
    int unknown_B8;   // +0x00B8
};
GG_STATIC_ASSERT(offsetof(BACountryView, unknown_B8) == 0xB8);

// The owning house, BuildingClass +0x21C (partial; the HouseClass name is YRpp-cross-checked).
struct BAHouseView
{
    char _pad_0000[0x24];   // +0x0000
    BAIntervalView unknown_24;   // +0x0024
    char _pad_0028[0xC];   // +0x0028
    BACountryView* unknown_34;   // +0x0034
    char _pad_0038[0x34];   // +0x0038
    BuildingAView** unknown_6C;   // +0x006C
    char _pad_0070[0x8];   // +0x0070
    int unknown_78;   // +0x0078
    char _pad_007C[0x17E];   // +0x007C
    unsigned char unknown_1FA;   // +0x01FA
    char _pad_01FB[0x1];   // +0x01FB
    unsigned char unknown_1FC;   // +0x01FC
    char _pad_01FD[0x49];   // +0x01FD
    unsigned char unknown_246;   // +0x0246
    char _pad_0247[0x25];   // +0x0247
    int unknown_26C;   // +0x026C
    char _pad_0270[0x50];   // +0x0270
    unsigned char unknown_2C0;   // +0x02C0
    char _pad_02C1[0x50FB];   // +0x02C1
    int unknown_53BC[5];   // +0x53BC
    char _pad_53D0[0x180];   // +0x53D0
    HBListView unknown_5550;   // +0x5550
    // FUNCTION: GAMEMD 0x50B730 (read-only here)
    bool FUN_0050B730();
    // FUNCTION: GAMEMD 0x50B6F0 (read-only here)
    bool FUN_0050B6F0();
    // FUNCTION: GAMEMD 0x4F9750 (read-only here)
    double FUN_004F9750();
    // FUNCTION: GAMEMD 0x4F7870 (read-only here)
    int FUN_004F7870(BAObjView* item, int a, int b);
    // FUNCTION: GAMEMD 0x4F9A90 (read-only here)
    bool FUN_004F9A90(BAObjView* o);
    // FUNCTION: GAMEMD 0x4FAA10 (read-only here)
    void FUN_004FAA10(int kind, int value);
    // FUNCTION: GAMEMD 0x500510 (read-only here)
    int FUN_00500510(int kind, char flag, int zero);
    // FUNCTION: GAMEMD 0x50DB00 (read-only here)
    void FUN_0050DB00(BuildingAView* b);
    // FUNCTION: GAMEMD 0x4FF700 (read-only here)
    void FUN_004FF700(BuildingAView* b);
};
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_1FA) == 0x1FA);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_1FC) == 0x1FC);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_246) == 0x246);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_26C) == 0x26C);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_2C0) == 0x2C0);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_53BC) == 0x53BC);
GG_STATIC_ASSERT(offsetof(BAHouseView, unknown_5550) == 0x5550);

// The object at BuildingClass +0x520 (BuildingTypeClass, name YRpp-cross-checked; touched members only).
class BATypeView
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
    virtual int vf_29();   // slot 29, +0x74
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vf_33(BAHouseView* owner);   // slot 33, +0x84
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual bool vf_42(HBCell* cell, BAHouseView* owner);   // slot 42, +0xA8
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual void vt_0B8();
    virtual void vt_0BC();
    virtual int vf_48();   // slot 48, +0xC0

    char _pad_0004[0x9C];   // +0x0004
    int unknown_A0;   // +0x00A0
    char _pad_00A4[0x330];   // +0x00A4
    int unknown_3D4;   // +0x03D4
    char _pad_03D8[0x30];   // +0x03D8
    int unknown_408;   // +0x0408
    char _pad_040C[0x1E0];   // +0x040C
    unsigned char unknown_5EC;   // +0x05EC
    unsigned char unknown_5ED;   // +0x05ED
    char _pad_05EE[0x8E];   // +0x05EE
    int unknown_67C;   // +0x067C
    int unknown_680;   // +0x0680
    int unknown_684;   // +0x0684
    char _pad_0688[0x94];   // +0x0688
    int unknown_71C;   // +0x071C
    char _pad_0720[0x56E];   // +0x0720
    unsigned char unknown_C8E;   // +0x0C8E
    char _pad_0C8F[0x3F];   // +0x0C8F
    unsigned char unknown_CCE;   // +0x0CCE
    char _pad_0CCF[0x2];   // +0x0CCF
    unsigned char unknown_CD1;   // +0x0CD1
    char _pad_0CD2[0x3];   // +0x0CD2
    unsigned char unknown_CD5;   // +0x0CD5
    char _pad_0CD6[0x122];   // +0x0CD6
    int unknown_DF8;   // +0x0DF8
    char _pad_0DFC[0x48];   // +0x0DFC
    HBPoint2D unknown_E44;   // +0x0E44
    char _pad_0E4C[0x20];   // +0x0E4C
    int unknown_E6C;   // +0x0E6C
    char _pad_0E70[0x48];   // +0x0E70
    int unknown_EB8;   // +0x0EB8
    char _pad_0EBC[0x1C];   // +0x0EBC
    unsigned char unknown_ED8;   // +0x0ED8
    char _pad_0ED9[0x13];   // +0x0ED9
    int unknown_EEC;   // +0x0EEC
    char _pad_0EF0[0x128];   // +0x0EF0
    char unknown_1018[16];   // +0x1018
    char unknown_1028[16];   // +0x1028
    char _pad_1038[0x1A8];   // +0x1038
    HBPoint2D unknown_11E0;   // +0x11E0
    int unknown_11E8;   // +0x11E8
    char _pad_11EC[0x228];   // +0x11EC
    char unknown_1414[16];   // +0x1414
    char unknown_1424[16];   // +0x1424
    char _pad_1434[0x145];   // +0x1434
    unsigned char unknown_1579;   // +0x1579
    char _pad_157A[0x1];   // +0x157A
    unsigned char unknown_157B;   // +0x157B
    unsigned char unknown_157C;   // +0x157C
    char _pad_157D[0x12C];   // +0x157D
    unsigned char unknown_16A9;   // +0x16A9
    unsigned char unknown_16AA;   // +0x16AA
    unsigned char unknown_16AB;   // +0x16AB
    char _pad_16AC[0x1];   // +0x16AC
    unsigned char unknown_16AD;   // +0x16AD
    unsigned char unknown_16AE;   // +0x16AE
    unsigned char unknown_16AF;   // +0x16AF
    unsigned char unknown_16B0;   // +0x16B0
    char _pad_16B1[0x4];   // +0x16B1
    unsigned char unknown_16B5;   // +0x16B5
    char _pad_16B6[0x1];   // +0x16B6
    unsigned char unknown_16B7;   // +0x16B7
    char _pad_16B8[0x1];   // +0x16B8
    unsigned char unknown_16B9;   // +0x16B9
    char _pad_16BA[0x1];   // +0x16BA
    unsigned char unknown_16BB;   // +0x16BB
    unsigned char unknown_16BC;   // +0x16BC
    unsigned char unknown_16BD;   // +0x16BD
    char _pad_16BE[0x1];   // +0x16BE
    unsigned char unknown_16BF;   // +0x16BF
    unsigned char unknown_16C0;   // +0x16C0
    char _pad_16C1[0x2];   // +0x16C1
    unsigned char unknown_16C3;   // +0x16C3
    unsigned char unknown_16C4;   // +0x16C4
    unsigned char unknown_16C5;   // +0x16C5
    char _pad_16C6[0x4];   // +0x16C6
    unsigned char unknown_16CA;   // +0x16CA
    unsigned char unknown_16CB;   // +0x16CB
    char _pad_16CC[0x24];   // +0x16CC
    int unknown_16F0;   // +0x16F0
    char _pad_16F4[0xD];   // +0x16F4
    unsigned char unknown_1701;   // +0x1701
    char _pad_1702[0x7E];   // +0x1702
    int unknown_1780;   // +0x1780
    char _pad_1784[0x4];   // +0x1784
    HBCoord* unknown_1788;   // +0x1788
    // FUNCTION: GAMEMD 0x45EC90 (read-only here)
    int FUN_0045EC90();
    // FUNCTION: GAMEMD 0x465AF0 (read-only here)
    void FUN_00465AF0();
    // FUNCTION: GAMEMD 0x45ECA0 (read-only here)
    int FUN_0045ECA0(int a);
};
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_3D4) == 0x3D4);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_408) == 0x408);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_5EC) == 0x5EC);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_5ED) == 0x5ED);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_67C) == 0x67C);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_680) == 0x680);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_684) == 0x684);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_71C) == 0x71C);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_C8E) == 0xC8E);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_CCE) == 0xCCE);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_CD1) == 0xCD1);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_CD5) == 0xCD5);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_DF8) == 0xDF8);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_E44) == 0xE44);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_E6C) == 0xE6C);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_EB8) == 0xEB8);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_ED8) == 0xED8);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_EEC) == 0xEEC);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_1018) == 0x1018);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_1028) == 0x1028);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_11E0) == 0x11E0);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_11E8) == 0x11E8);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_1414) == 0x1414);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_1424) == 0x1424);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_1579) == 0x1579);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_157B) == 0x157B);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_157C) == 0x157C);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16A9) == 0x16A9);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16AA) == 0x16AA);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16AB) == 0x16AB);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16AD) == 0x16AD);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16AE) == 0x16AE);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16AF) == 0x16AF);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16B0) == 0x16B0);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16B5) == 0x16B5);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16B7) == 0x16B7);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16B9) == 0x16B9);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16BB) == 0x16BB);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16BC) == 0x16BC);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16BD) == 0x16BD);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16BF) == 0x16BF);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16C0) == 0x16C0);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16C3) == 0x16C3);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16C4) == 0x16C4);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16C5) == 0x16C5);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16CA) == 0x16CA);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16CB) == 0x16CB);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_16F0) == 0x16F0);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_1701) == 0x1701);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_1780) == 0x1780);
GG_STATIC_ASSERT(offsetof(BATypeView, unknown_1788) == 0x1788);

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
    virtual void vf_9();   // slot 9, +0x24
    virtual void vf_10(BAObjView* ptr, bool removed);   // slot 10, +0x28
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual int vf_14();   // slot 14, +0x38
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual HBCoord* vf_18(HBCoord* out);   // slot 18, +0x48
    virtual HBCoord* vf_19(HBCoord* out, BAObjView* arg);   // slot 19, +0x4C
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual int vf_28(HBCell* cell, char a, char b);   // slot 28, +0x70
    virtual int vf_29(BAObjView* obj, char flag);   // slot 29, +0x74
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual BATypeView* vf_33();   // slot 33, +0x84
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual bool vf_38();   // slot 38, +0x98
    virtual void vt_09C();
    virtual bool vf_40();   // slot 40, +0xA0
    virtual void vt_0A4();
    virtual HBCoord* vf_42(HBCoord* out, BAObjView* target);   // slot 42, +0xA8
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual int vf_46();   // slot 46, +0xB8
    virtual void vt_0BC();
    virtual void vt_0C0();
    virtual void vt_0C4();
    virtual void vt_0C8();
    virtual void vt_0CC();
    virtual void vt_0D0();
    virtual void vf_53();   // slot 53, +0xD4
    virtual void vt_0D8();
    virtual void vf_55(char arg);   // slot 55, +0xDC
    virtual void vt_0E0();
    virtual void vt_0E4();
    virtual void vt_0E8();
    virtual void vt_0EC();
    virtual void vt_0F0();
    virtual void vt_0F4();
    virtual void vf_62();   // slot 62, +0xF8
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
    virtual void vf_73(int arg);   // slot 73, +0x124
    virtual void vt_128();
    virtual void vt_12C();
    virtual void vt_130();
    virtual void vt_134();
    virtual void vt_138();
    virtual void vt_13C();
    virtual bool vf_80(int mode, HBCell* cell, int a3, int a4);   // slot 80, +0x140
    virtual void vt_144();
    virtual void vf_82(int arg);   // slot 82, +0x148
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
    virtual void vt_188();
    virtual void vt_18C();
    virtual void vt_190();
    virtual void vt_194();
    virtual bool vf_102(BAHouseView* house);   // slot 102, +0x198
    virtual void vf_103(int mode);   // slot 103, +0x19C
    virtual void vf_104(int mode);   // slot 104, +0x1A0
    virtual void vt_1A4();
    virtual void vt_1A8();
    virtual int vf_107(BAOccupierView* occ, int a2, int a3, int a4, int a5);   // slot 107, +0x1AC
    virtual void vt_1B0();
    virtual void vt_1B4();
    virtual HBCell* vf_110(HBCell* out);   // slot 110, +0x1B8
    virtual void vt_1BC();
    virtual void vt_1C0();
    virtual void vt_1C4();
    virtual void vt_1C8();
    virtual void vt_1CC();
    virtual int vf_116();   // slot 116, +0x1D0
    virtual void vt_1D4();
    virtual void vt_1D8();
    virtual void vt_1DC();
    virtual void vt_1E0();
    virtual void vt_1E4();
    virtual void vf_122(int mission, int arg);   // slot 122, +0x1E8
    virtual void vf_123();   // slot 123, +0x1EC
    virtual void vt_1F0();
    virtual void vt_1F4();
    virtual void vt_1F8();
    virtual void vt_1FC();
    virtual void vt_200();
    virtual void vt_204();
    virtual void vt_208();
    virtual void vt_20C();
    virtual void vt_210();
    virtual void vf_133();   // slot 133, +0x214
    virtual void vt_218();
    virtual int vf_135();   // slot 135, +0x21C
    virtual void vf_136();   // slot 136, +0x220
    virtual void vf_137();   // slot 137, +0x224
    virtual void vt_228();
    virtual void vt_22C();
    virtual void vt_230();
    virtual void vt_234();
    virtual void vt_238();
    virtual void vt_23C();
    virtual void vt_240();
    virtual int vf_145();   // slot 145, +0x244
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
    virtual int vf_157(int arg);   // slot 157, +0x274
    virtual int vf_158(int a, BAObjView* o);   // slot 158, +0x278
    virtual void vt_27C();
    virtual void vf_160(int a);   // slot 160, +0x280
    virtual bool vf_161();   // slot 161, +0x284
    virtual void vt_288();
    virtual void vt_28C();
    virtual void vt_290();
    virtual void vt_294();
    virtual void vt_298();
    virtual void vt_29C();
    virtual void vt_2A0();
    virtual void vt_2A4();
    virtual HBDir vf_170();   // slot 170, +0x2A8
    virtual bool vf_171();   // slot 171, +0x2AC
    virtual void vt_2B0();
    virtual void vt_2B4();
    virtual int vf_174();   // slot 174, +0x2B8
    virtual void vt_2BC();
    virtual void vt_2C0();
    virtual void vt_2C4();
    virtual void vt_2C8();
    virtual bool vf_179(HBCoord* where);   // slot 179, +0x2CC
    virtual void vt_2D0();
    virtual void vt_2D4();
    virtual void vt_2D8();
    virtual void vt_2DC();
    virtual void vt_2E0();
    virtual void vt_2E4();
    virtual void vt_2E8();
    virtual int vf_187();   // slot 187, +0x2EC
    virtual void vt_2F0();
    virtual void vt_2F4();
    virtual void vt_2F8();
    virtual void vt_2FC();
    virtual void vt_300();
    virtual void vt_304();
    virtual HBDir* vf_194(HBDir* out);   // slot 194, +0x308
    virtual int vf_195();   // slot 195, +0x30C
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
    virtual bool vf_212();   // slot 212, +0x350
    virtual void vt_354();
    virtual void vt_358();
    virtual void vt_35C();
    virtual void vt_360();
    virtual void vt_364();
    virtual void vt_368();
    virtual void vt_36C();
    virtual void vt_370();
    virtual void vt_374();
    virtual void vf_222(int a, BACellView* cell, int c, int d);   // slot 222, +0x378
    virtual bool vf_223();   // slot 223, +0x37C
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
    virtual bool vf_235(BAObjView* target);   // slot 235, +0x3AC
    virtual void vt_3B0();
    virtual void vt_3B4();
    virtual void vf_238(void* arg);   // slot 238, +0x3B8
    virtual void vt_3BC();
    virtual int vf_240(BAObjView* target, int b, int c);   // slot 240, +0x3C0
    virtual void vf_241(unsigned int flags, int b, int c);   // slot 241, +0x3C4
    virtual void vf_242(BAObjView* target);   // slot 242, +0x3C8
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
    virtual BASlotView* vf_254(int which);   // slot 254, +0x3F8
    virtual bool vf_255();   // slot 255, +0x3FC
    virtual void vt_400();
    virtual void vt_404();
    virtual int vf_258();   // slot 258, +0x408
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
    virtual bool vf_289(bool flag, int unused);   // slot 289, +0x484
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
    virtual int vf_310(BAObjView* target);   // slot 310, +0x4D8
    virtual void vf_311(int arg);   // slot 311, +0x4DC
    virtual void vf_312();   // slot 312, +0x4E0
    virtual void vt_4E4();
    virtual HBDir vf_314(BAObjView* target);   // slot 314, +0x4E8
    virtual void vt_4EC();
    virtual char vf_316();   // slot 316, +0x4F0

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
    BAHouseView* Owner;   // +0x021C  HouseClass*
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
    BATypeView* Type;   // +0x0520  BuildingTypeClass*
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
    // Slot 42 body: the retail slot takes a hidden out pointer and returns it; written as a by-value
    // return (see building_a_methods_3.cpp). Slots 18 and 19 are now BuildingClass::vf_18/vf_19.
    // FUNCTION: GAMEMD 0x447B20 - body of slot 42
    HBCoord FUN_00447B20(BAObjView* target);
    // FUNCTION: GAMEMD 0x443860 (read-only here)
    void FUN_00443860(HBCell* cell, int flag);
    // FUNCTION: GAMEMD 0x5F6C80 (read-only here)
    HBCoord* FUN_005F6C80(HBCoord* out, BAObjView* arg);
    // FUNCTION: GAMEMD 0x65AD90 (read-only here)
    int FUN_0065AD90(BAObjView* arg);
    // FUNCTION: GAMEMD 0x6FC0B0 (read-only here)
    int FUN_006FC0B0(BAObjView* target, int b, int c);
    // FUNCTION: GAMEMD 0x6FFEC0 (read-only here)
    int FUN_006FFEC0(BAObjView* obj, char flag);
    // FUNCTION: GAMEMD 0x700600 (read-only here)
    int FUN_00700600(HBCell* cell, char a, char b);
    // FUNCTION: GAMEMD 0x7077C0 (read-only here)
    void FUN_007077C0(BAObjView* ptr, bool removed);
    // FUNCTION: GAMEMD 0x5F5C60 (read-only here)
    double FUN_005F5C60();
    // FUNCTION: GAMEMD 0x451890 (read-only here)
    void FUN_00451890(char* name, int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x451B40 (read-only here)
    void FUN_00451B40(BAObjView* ptr);
    // FUNCTION: GAMEMD 0x65AD30 (read-only here)
    BAObjView* FUN_0065AD30(int index);
    // FUNCTION: GAMEMD 0x5F5280 (read-only here)
    void FUN_005F5280(char arg);
    // FUNCTION: GAMEMD 0x70E000 (read-only here)
    void FUN_0070E000(int arg);
    // FUNCTION: GAMEMD 0x449540 (read-only here)
    void FUN_00449540();
    // FUNCTION: GAMEMD 0x5B3A00 (read-only here)
    HBPriceView* FUN_005B3A00();
    // FUNCTION: GAMEMD 0x6F3F40 (read-only here)
    void FUN_006F3F40();
    // FUNCTION: GAMEMD 0x6FCDB0 (read-only here)
    void FUN_006FCDB0(BAObjView* target);
    // FUNCTION: GAMEMD 0x6F8DF0 (read-only here)
    void FUN_006F8DF0(unsigned int flags, int b, int c);
    // FUNCTION: GAMEMD 0x5F6BD0 (read-only here)
    int FUN_005F6BD0();
    // FUNCTION: GAMEMD 0x70FEC0 (read-only here)
    bool FUN_0070FEC0();
    // FUNCTION: GAMEMD 0x5B2E50 (read-only here)
    void FUN_005B2E50();
    // FUNCTION: GAMEMD 0x5B2E90 (read-only here)
    void FUN_005B2E90();
    // FUNCTION: GAMEMD 0x6F4960 (read-only here)
    bool FUN_006F4960(BAHouseView* house);
    // FUNCTION: GAMEMD 0x65AE30 (read-only here)
    bool FUN_0065AE30();
    // FUNCTION: GAMEMD 0x447780 (read-only here)
    void FUN_00447780(int arg);
    // FUNCTION: GAMEMD 0x708C30 (read-only here)
    int FUN_00708C30();
    // FUNCTION: GAMEMD 0x707D20 (read-only here)
    int FUN_00707D20();
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
extern HBPairXformView* DAT_00887324;
// GLOBAL: GAMEMD 0xA83CBC - an array of index entries
extern class HBIdxView** DAT_00A83CBC;
// GLOBAL: GAMEMD 0x7E27F8 - double constant
extern const double DAT_007E27F8;
// FUNCTION: GAMEMD 0x4CA160 (read-only here) - looks an object up by handle; one register argument: __fastcall.
class BAProdView* FUN_004CA160(int handle);
// FUNCTION: GAMEMD 0x4C9FF0 (read-only here) - one register argument: __fastcall.
void FUN_004C9FF0(class BAObjView* factory);
// GLOBAL: GAMEMD 0x87F770 (pointer) and 0xA8EBF8 / 0xA8EBFC
extern BAGlobalAView* DAT_0087F770;
extern int DAT_00A8EBF8;
extern int DAT_00A8EBFC;
// GLOBAL: GAMEMD 0xA83D4C (the local player's house) and the four object lists scanned by slot 312
extern BAHouseView* DAT_00A83D4C;
extern BAVector<BAObjView*> DAT_00A8B218;
extern BAVector<BAObjView*> DAT_00A83C68;
extern BAVector<BAObjView*> DAT_00A8E348;
extern BAVector<BAObjView*> DAT_00A83CE0;
// GLOBAL: GAMEMD 0xA802C8 (the outgoing event queue), 0xA8B238 / 0xA8B320
extern BAEventQueue DAT_00A802C8;
extern unsigned char DAT_00A8B320;
// IMPORT: GAMEMD 0x7E1530 (winmm timeGetTime)
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
// GLOBAL: GAMEMD 0x8B41E0 - a vector of building pointers (the registration list).
extern BAVector<BuildingAView*> DAT_008B41E0;
extern HBCoord DAT_0089C848;

// FUNCTION: GAMEMD 0x772A90 (read-only here) - one register argument: __fastcall.
unsigned int FUN_00772A90(BAObjView* entry);

// GLOBAL: GAMEMD 0x87F7E8 - the map object (its address is loaded into ECX).
extern BAMapView DAT_0087F7E8;
// GLOBAL: GAMEMD 0xA8B230 / 0x8871E0
extern HBSourceView* DAT_00A8B230;
extern BARulesView* RulesInstance;




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
