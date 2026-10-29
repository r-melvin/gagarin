// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Address-scoped partial views for the "building-a2" cluster of the house/building module (the six large
//   BuildingClass bodies at 0x43C2D0, 0x442230, 0x443C60, 0x449C30, 0x44E440, 0x44EFB0). Every field and slot
//   below is an operand read from the retail gamemd.exe v1.001 in one of those functions. These views are NOT
//   the canonical BuildingClass / BuildingTypeClass: they are sparse, BA2-prefixed and cluster-scoped, and are to
//   be consolidated later. Slots are retail primary-table indices (byte offset / 4); the
//   vt_XXX virtuals only position the slots actually used.
//   Maintained by hand since the module consolidation; shared types come from house_building_common_types.h.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A2_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A2_VIEWS_H

#include <stddef.h>
#include "../../_layout/session_class.h"
#include "../../_rt/gg_static_assert.h"
#include "house_building_layout.h"
#include "../../core/cell_step_tables.h"
#include "house_building_common_types.h"
#include "house_building_common_types.h"
#include "house_building_common_types.h"


class BA2Obj;
class BA2Occupant;
class BA2Tech;
class BA2Infantry;
class BA2Unit;
class BA2Tether;
class BA2PassengerList;
struct BA2UnitType;
struct BA2InfType;
struct BA2InfSize;
class BA2Other;
class BA2Type;
class BA2House;
class BA2Building;
class BA2Anim;
struct BA2Slot;
struct BA2AnimTypeRef;
struct BA2Warhead;
struct BA2Price;
class BA2CellObj;
struct BA2Rules;
struct BA2Source;
struct BA2Screen;
struct BA2Map;
class BA2First;
struct BA2ObjType;
struct BA2Link;
struct BA2Link2;
struct BA2Special;
struct BA2Entry;
class BA2EntryList;
struct BA2Light;
struct BA2Floater;

// A facing value (a 16-bit direction in the low half of a dword).
// Not merged into HBDir: the half is read unsigned here (see house_building_views.h).
struct BA2Dir
{
    union {
        unsigned int Whole;   // +0x00
        unsigned short Raw;   // +0x00
        struct {
            unsigned short Lo : 8;
            unsigned short Hi : 8;
        } Bytes;
    };
    BA2Dir() {}
};
GG_STATIC_ASSERT(sizeof(BA2Dir) == 4);

// Four integers returned by slot 75 (a rectangle or two coordinate pairs); copied by value onto the stack.
struct BA2Quad
{
    int A;   // +0x00
    int B;   // +0x04
    int C;   // +0x08
    int D;   // +0x0C
    BA2Quad() {}
};
GG_STATIC_ASSERT(sizeof(BA2Quad) == 0x10);

// The countdown timer embedded at BuildingClass +0x604 (four dwords; the second one is never written by the
// start sequence, which copies a partly initialised temporary over it).
// Not merged: cluster timers differ in constructors and inline bodies (see house_building_views.h).
struct BA2Timer
{
    int StartTime;   // +0x00
    int unknown_04;  // +0x04
    int TimeLeft;    // +0x08
    int Duration;    // +0x0C
    BA2Timer() {}
};
GG_STATIC_ASSERT(sizeof(BA2Timer) == 0x10);

// The base of the vector family (vptr, Items, Capacity, IsInitialized, IsAllocated; 0x10 bytes). The base
// constructor is out of line; the destructor frees an owned array.
template <class T> class BA2VectorBase
{
public:
    // FUNCTION: GAMEMD 0x40BD00 (read-only here) - the base constructor (capacity, preallocated array)
    BA2VectorBase(int capacity, T* array);
    virtual ~BA2VectorBase()
    {
        if (Items && IsAllocated)
            operator delete(Items);
    }
    virtual bool vf_1();
    virtual bool SetCapacity(int capacity, T* mem);   // slot 2
    virtual void Clear();                             // slot 3
    virtual int FindItemIndex(const T* item);            // slot 4
    T*            Items;               // +0x04
    int           Capacity;            // +0x08
    bool          IsInitialized;       // +0x0C
    bool          IsAllocated;         // +0x0D
};

// DynamicVectorClass<T*> (0x18 bytes) with the inlined AddItem / RemoveItem the original expanded.
template <class T> class BA2DynVector : public BA2VectorBase<T>
{
public:
    int Count;               // +0x10
    int CapacityIncrement;   // +0x14
    BA2DynVector() : BA2VectorBase<T>(0, 0)
    {
        CapacityIncrement = 10;
        Count = 0;
    }
    virtual ~BA2DynVector() {}
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
    bool RemoveItem(const T& item)
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
};

// The same vector family as above where the (capacity 0, no array) base constructor was expanded inline.
template <class T> class BA2InlineVectorBase
{
public:
    BA2InlineVectorBase()
    {
        Items = 0;
        Capacity = 0;
        IsInitialized = true;
        IsAllocated = false;
    }
    virtual ~BA2InlineVectorBase()
    {
        if (Items && IsAllocated)
            operator delete(Items);
    }
    virtual bool vf_1();
    virtual bool SetCapacity(int capacity, T* mem);   // slot 2
    virtual void Clear();                             // slot 3
    virtual int FindItemIndex(const T* item);         // slot 4
    T*            Items;               // +0x04
    int           Capacity;            // +0x08
    bool          IsInitialized;       // +0x0C
    bool          IsAllocated;         // +0x0D
};
template <class T> class BA2InlineDynVector : public BA2InlineVectorBase<T>
{
public:
    int Count;               // +0x10
    int CapacityIncrement;   // +0x14
    BA2InlineDynVector()
    {
        CapacityIncrement = 10;
        Count = 0;
    }
    virtual ~BA2InlineDynVector() {}
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

// GLOBAL: GAMEMD 0xA8ED84 - the current frame counter.
extern int Frame_A8ED84;

// One damage-state animation entry of the type (0x44 bytes: two names).
struct BA2AnimName
{
    char Normal[0x10];   // +0x0000
    char Low[0x34];   // +0x0010
};
GG_STATIC_ASSERT(offsetof(BA2AnimName, Normal) == 0x0);
GG_STATIC_ASSERT(offsetof(BA2AnimName, Low) == 0x10);
GG_STATIC_ASSERT(sizeof(BA2AnimName) == 0x44);

// The map object at 0x87F7E8 (partial).
struct BA2Map
{
    // FUNCTION: GAMEMD 0x568300 (read-only here) - is the cell inside the map
    bool FUN_00568300(HBCell* cell);
    // FUNCTION: GAMEMD 0x5657A0 (read-only here)
    BA2CellObj* FUN_005657A0(HBCell* cell);
    // FUNCTION: GAMEMD 0x578080 (read-only here) - the ground height at a coordinate
    int FUN_00578080(HBCoord* where);
    // FUNCTION: GAMEMD 0x565730 (read-only here) - the cell object at a coordinate
    BA2CellObj* FUN_00565730(HBCoord* where);
    // FUNCTION: GAMEMD 0x578460 (read-only here)
    bool FUN_00578460(HBCell* cell, int arg);
    // FUNCTION: GAMEMD 0x588570 (read-only here)
    void FUN_00588570(HBCell* cell, BA2House* house, BA2Type* type);
    // FUNCTION: GAMEMD 0x588750 (read-only here)
    void FUN_00588750(HBCell* cell, BA2House* house, BA2Type* type);
    // FUNCTION: GAMEMD 0x56DC20 (read-only here)
    HBCell* FUN_0056DC20(HBCell* out, HBCell* from, int type, int a, int b, int c, int d, int e, int f, int g, int h, int i, HBCell* j, int k, int l);
};

// The animation stage member at BuildingClass +0x350 (partial: methods only).
struct BA2Stage
{
    // FUNCTION: GAMEMD 0x4A5110 (read-only here)
    bool FUN_004A5110();
    // FUNCTION: GAMEMD 0x4A5130 (read-only here)
    bool FUN_004A5130();
    // FUNCTION: GAMEMD 0x4A51B0 (read-only here)
    bool FUN_004A51B0();
    // FUNCTION: GAMEMD 0x4A51D0 (read-only here)
    bool FUN_004A51D0();
    // FUNCTION: GAMEMD 0x4A51F0 (read-only here)
    void FUN_004A51F0(double rate);
    // FUNCTION: GAMEMD 0x4A5240 (read-only here)
    void FUN_004A5240(double rate);
    // FUNCTION: GAMEMD 0x4A5290 (read-only here)
    void FUN_004A5290();
    // FUNCTION: GAMEMD 0x4A52F0 (read-only here)
    double FUN_004A52F0();
};

// The facing member at BuildingClass +0x388 (partial: methods only).
struct BA2Facing
{
    // FUNCTION: GAMEMD 0x4C9480 (read-only here)
    bool FUN_004C9480();
    // FUNCTION: GAMEMD 0x4C9220 (read-only here)
    void FUN_004C9220(BA2Dir* dir);
    // FUNCTION: GAMEMD 0x4C9300 (read-only here)
    void FUN_004C9300(BA2Dir* dir);
    // FUNCTION: GAMEMD 0x4C93D0 (read-only here)
    BA2Dir* FUN_004C93D0(BA2Dir* out);
};

// Object behind the global at 0x8871E0 (partial).
struct BA2Rules
{
    char _pad_0000[0x404];   // +0x0000
    int unknown_404;   // +0x0404
    int unknown_408;   // +0x0408
    char _pad_040C[0x298];   // +0x040C
    int unknown_6A4;   // +0x06A4
    char _pad_06A8[0x6C];   // +0x06A8
    int unknown_714;   // +0x0714
    char _pad_0718[0x164];   // +0x0718
    BA2Type* unknown_87C;   // +0x087C
    char _pad_0880[0x2F8];   // +0x0880
    BA2AnimTypeRef** unknown_B78;   // +0x0B78
    char _pad_0B7C[0x2CC];   // +0x0B7C
    int unknown_E48;   // +0x0E48
    char _pad_0E4C[0x15C];   // +0x0E4C
    BA2Warhead* unknown_FA8;   // +0x0FA8
    char _pad_0FAC[0x754];   // +0x0FAC
    double unknown_1700;   // +0x1700
    char _pad_1708[0xE4];   // +0x1708
    unsigned char unknown_17EC;   // +0x17EC
};
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_404) == 0x404);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_408) == 0x408);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_6A4) == 0x6A4);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_714) == 0x714);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_87C) == 0x87C);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_B78) == 0xB78);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_E48) == 0xE48);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_FA8) == 0xFA8);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_1700) == 0x1700);
GG_STATIC_ASSERT(offsetof(BA2Rules, unknown_17EC) == 0x17EC);



// Object behind the global at 0x887324 (partial).
struct BA2Screen
{
    // FUNCTION: GAMEMD 0x6D2790 (read-only here) - a 16-byte value and a flag.
    void FUN_006D2790(BA2Quad q, int flag);
};

// What FUN_005B3A00 returns (partial).
struct BA2Price
{
    char _pad_0000[0x10];   // +0x0000
    double unknown_10;   // +0x0010
    double unknown_18;   // +0x0018
};
GG_STATIC_ASSERT(offsetof(BA2Price, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(BA2Price, unknown_18) == 0x18);

// An animation type (opaque here).
struct BA2AnimTypeRef
{
};

// The warhead passed to ReceiveDamage (partial).
struct BA2Warhead
{
    char _pad_0000[0x14A];   // +0x0000
    unsigned char unknown_14A;   // +0x014A
};
GG_STATIC_ASSERT(offsetof(BA2Warhead, unknown_14A) == 0x14A);

// Type object of a BA2First (partial).
struct BA2ObjType
{
    char _pad_0000[0x2A4];   // +0x0000
    unsigned char unknown_2A4;   // +0x02A4
};
GG_STATIC_ASSERT(offsetof(BA2ObjType, unknown_2A4) == 0x2A4);

// A newly created animation (sizeof 0x1C8 from the allocation).
class BA2Anim
{
public:
    char _pad_0000[0x1C8];   // +0x0000
    // FUNCTION: GAMEMD 0x421EA0 (read-only here) - the constructor
    BA2Anim(BA2AnimTypeRef* type, HBCoord* where, int delay, int loops, int flags, int zAdjust, int override);
    // FUNCTION: GAMEMD 0x424B50 (read-only here)
    void FUN_00424B50(BA2Building* owner);
};
GG_STATIC_ASSERT(sizeof(BA2Anim) == 0x1C8);

// The object at BuildingClass +0x2BC (partial).
struct BA2Link
{
    // FUNCTION: GAMEMD 0x472140 (read-only here)
    void FUN_00472140();
    // FUNCTION: GAMEMD 0x4722C0 (read-only here)
    bool FUN_004722C0();
};

// The object at BuildingClass +0x614 (partial).
struct BA2Light
{
    // FUNCTION: GAMEMD 0x554A80 (read-only here)
    void FUN_00554A80(int arg);
};

// The object at BuildingClass +0x30C (partial).
struct BA2Floater
{
    char _pad_0000[0xE8];   // +0x0000
    float unknown_E8;   // +0x00E8
};
GG_STATIC_ASSERT(offsetof(BA2Floater, unknown_E8) == 0xE8);

// An object with a flag at +0x2A8 (partial).
struct BA2Special
{
    char _pad_0000[0x2A8];   // +0x0000
    unsigned char unknown_2A8;   // +0x02A8
};
GG_STATIC_ASSERT(offsetof(BA2Special, unknown_2A8) == 0x2A8);

// A 16-byte entry of the house list at +0x5704 (partial).
struct BA2Entry
{
    int Key;   // +0x0000
    HBCell Cell;   // +0x0004
    int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(BA2Entry, Key) == 0x0);
GG_STATIC_ASSERT(offsetof(BA2Entry, Cell) == 0x4);
GG_STATIC_ASSERT(offsetof(BA2Entry, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(BA2Entry, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(BA2Entry) == 0x10);

// The entry list at BuildingClass owner +0x5704 (a vector of BA2Entry; partial).
class BA2EntryList
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual int vf_5(BA2Entry* e);   // slot 5, +0x14

    BA2Entry* Items;   // +0x0004
    char _pad_0008[0x8];   // +0x0008
    int Count;   // +0x0010
    char _pad_0014[0x4];   // +0x0014
    // DynamicVectorClass::RemoveItem by index, expanded inline by the original.
    void RemoveAt(int index) { if (index < Count) { Count--; for (; index < Count; index++) { Items[index] = Items[index + 1]; } } }
};
GG_STATIC_ASSERT(offsetof(BA2EntryList, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(BA2EntryList, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(BA2EntryList) == 0x18);

// The entry index at house +0x5700 (partial: the list lives at +4).
struct BA2EntryIndex
{
    char _pad_0000[0x4];   // +0x0000
    BA2EntryList List;   // +0x0004
    // FUNCTION: GAMEMD 0x42EB20 (read-only here)
    BA2Entry* FUN_0042EB20(int key);
    // FUNCTION: GAMEMD 0x42EB50 (read-only here)
    int FUN_0042EB50(int key);
    // FUNCTION: GAMEMD 0x42F380 (read-only here)
    int FUN_0042F380(BA2Entry* e);
};
GG_STATIC_ASSERT(offsetof(BA2EntryIndex, List) == 0x4);

// The polymorphic base of the type view (partial: slot 35 only).
class BA2TypeBase
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
    virtual void vt_084();
    virtual void vt_088();
    virtual BA2Other* vf_35(BA2House* house);   // slot 35, +0x8C

};
GG_STATIC_ASSERT(sizeof(BA2TypeBase) == 0x4);

// The object at BuildingClass +0x520 (BuildingTypeClass, name YRpp-cross-checked; touched members only).
class BA2Type : public BA2TypeBase
{
public:
    char _pad_0004[0x9C];   // +0x0004
    int unknown_A0;   // +0x00A0
    char _pad_00A4[0x18E];   // +0x00A4
    unsigned char unknown_232;   // +0x0232
    unsigned char unknown_233;   // +0x0233
    char _pad_0234[0x14C];   // +0x0234
    double unknown_380;   // +0x0380
    double unknown_388;   // +0x0388
    char _pad_0390[0x38];   // +0x0390
    double unknown_3C8;   // +0x03C8
    char _pad_03D0[0x38];   // +0x03D0
    BA2UnitType* unknown_408;   // +0x0408
    char _pad_040C[0x12C];   // +0x040C
    int unknown_538;   // +0x0538
    char _pad_053C[0x30];   // +0x053C
    int unknown_56C;   // +0x056C
    char _pad_0570[0x44];   // +0x0570
    int unknown_5B4;   // +0x05B4
    char _pad_05B8[0x28];   // +0x05B8
    int unknown_5E0;   // +0x05E0
    char _pad_05E4[0x98];   // +0x05E4
    int unknown_67C;   // +0x067C
    char _pad_0680[0x620];   // +0x0680
    unsigned char unknown_CA0;   // +0x0CA0
    char _pad_0CA1[0x2D];   // +0x0CA1
    unsigned char unknown_CCE;   // +0x0CCE
    char _pad_0CCF[0x5];   // +0x0CCF
    unsigned char unknown_CD4;   // +0x0CD4
    char _pad_0CD5[0x95];   // +0x0CD5
    unsigned char unknown_D6A;   // +0x0D6A
    char _pad_0D6B[0x29];   // +0x0D6B
    unsigned char unknown_D94;   // +0x0D94
    char _pad_0D95[0x63];   // +0x0D95
    int unknown_DF8;   // +0x0DF8
    char _pad_0DFC[0x2C];   // +0x0DFC
    double unknown_E28;   // +0x0E28
    char _pad_0E30[0x24];   // +0x0E30
    BA2Special* unknown_E54;   // +0x0E54
    char _pad_0E58[0x18];   // +0x0E58
    int unknown_E70;   // +0x0E70
    char _pad_0E74[0x14];   // +0x0E74
    unsigned char unknown_E88;   // +0x0E88
    char _pad_0E89[0x2F];   // +0x0E89
    int unknown_EB8;   // +0x0EB8
    char _pad_0EBC[0xC];   // +0x0EBC
    HBCoord ExitOffset;   // +0x0EC8
    HBCell* unknown_ED4;   // +0x0ED4
    int unknown_ED8;   // +0x0ED8
    char _pad_0EDC[0x70];   // +0x0EDC
    BA2AnimName unknown_F4C[0x15];   // +0x0F4C
    char _pad_14E0[0x91];   // +0x14E0
    unsigned char unknown_1571;   // +0x1571
    char _pad_1572[0x9];   // +0x1572
    unsigned char unknown_157B;   // +0x157B
    char _pad_157C[0x12D];   // +0x157C
    unsigned char unknown_16A9;   // +0x16A9
    unsigned char unknown_16AA;   // +0x16AA
    unsigned char unknown_16AB;   // +0x16AB
    unsigned char unknown_16AC;   // +0x16AC
    unsigned char unknown_16AD;   // +0x16AD
    unsigned char unknown_16AE;   // +0x16AE
    unsigned char unknown_16AF;   // +0x16AF
    char _pad_16B0[0x3];   // +0x16B0
    unsigned char unknown_16B3;   // +0x16B3
    char _pad_16B4[0x2];   // +0x16B4
    unsigned char unknown_16B6;   // +0x16B6
    unsigned char unknown_16B7;   // +0x16B7
    char _pad_16B8[0x1];   // +0x16B8
    unsigned char unknown_16B9;   // +0x16B9
    char _pad_16BA[0x1];   // +0x16BA
    unsigned char unknown_16BB;   // +0x16BB
    unsigned char unknown_16BC;   // +0x16BC
    unsigned char unknown_16BD;   // +0x16BD
    unsigned char unknown_16BE;   // +0x16BE
    unsigned char unknown_16BF;   // +0x16BF
    unsigned char unknown_16C0;   // +0x16C0
    unsigned char unknown_16C1;   // +0x16C1
    unsigned char unknown_16C2;   // +0x16C2
    char _pad_16C3[0x1];   // +0x16C3
    unsigned char unknown_16C4;   // +0x16C4
    char _pad_16C5[0x2];   // +0x16C5
    unsigned char unknown_16C7;   // +0x16C7
    char _pad_16C8[0x2];   // +0x16C8
    unsigned char unknown_16CA;   // +0x16CA
    unsigned char unknown_16CB;   // +0x16CB
    char _pad_16CC[0x18];   // +0x16CC
    unsigned char unknown_16E4;   // +0x16E4
    unsigned char unknown_16E5;   // +0x16E5
    unsigned char unknown_16E6;   // +0x16E6
    char _pad_16E7[0x11];   // +0x16E7
    int unknown_16F8;   // +0x16F8
    char _pad_16FC[0xA];   // +0x16FC
    unsigned char unknown_1706;   // +0x1706
    unsigned char unknown_1707;   // +0x1707
    char _pad_1708[0x8];   // +0x1708
    int unknown_1710;   // +0x1710
    // FUNCTION: GAMEMD 0x45EE70 (read-only here)
    int FUN_0045EE70(HBCell* cell, BA2House* house);
    // FUNCTION: GAMEMD 0x465D70 (read-only here)
    int FUN_00465D70();
    // FUNCTION: GAMEMD 0x45EC90 (read-only here)
    int FUN_0045EC90();
    // FUNCTION: GAMEMD 0x45ECA0 (read-only here)
    int FUN_0045ECA0(int a);
};
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_232) == 0x232);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_233) == 0x233);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_380) == 0x380);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_388) == 0x388);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_3C8) == 0x3C8);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_408) == 0x408);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_538) == 0x538);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_56C) == 0x56C);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_5B4) == 0x5B4);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_5E0) == 0x5E0);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_67C) == 0x67C);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_CA0) == 0xCA0);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_CCE) == 0xCCE);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_CD4) == 0xCD4);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_D6A) == 0xD6A);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_D94) == 0xD94);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_DF8) == 0xDF8);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_E28) == 0xE28);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_E54) == 0xE54);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_E70) == 0xE70);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_E88) == 0xE88);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_EB8) == 0xEB8);
GG_STATIC_ASSERT(offsetof(BA2Type, ExitOffset) == 0xEC8);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_ED4) == 0xED4);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_ED8) == 0xED8);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_F4C) == 0xF4C);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_1571) == 0x1571);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_157B) == 0x157B);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16A9) == 0x16A9);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16AA) == 0x16AA);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16AB) == 0x16AB);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16AC) == 0x16AC);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16AD) == 0x16AD);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16AE) == 0x16AE);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16AF) == 0x16AF);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16B3) == 0x16B3);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16B6) == 0x16B6);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16B7) == 0x16B7);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16B9) == 0x16B9);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16BB) == 0x16BB);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16BC) == 0x16BC);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16BD) == 0x16BD);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16BE) == 0x16BE);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16BF) == 0x16BF);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16C0) == 0x16C0);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16C1) == 0x16C1);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16C2) == 0x16C2);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16C4) == 0x16C4);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16C7) == 0x16C7);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16CA) == 0x16CA);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16CB) == 0x16CB);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16E4) == 0x16E4);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16E5) == 0x16E5);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16E6) == 0x16E6);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_16F8) == 0x16F8);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_1706) == 0x1706);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_1707) == 0x1707);
GG_STATIC_ASSERT(offsetof(BA2Type, unknown_1710) == 0x1710);

// The owning house (partial).
struct BA2House
{
    char _pad_0000[0x30];   // +0x0000
    int unknown_30;   // +0x0030
    char _pad_0034[0x38];   // +0x0034
    BA2Building** unknown_6C;   // +0x006C
    char _pad_0070[0x8];   // +0x0070
    int unknown_78;   // +0x0078
    char _pad_007C[0x80];   // +0x007C
    BA2Building** unknown_FC;   // +0x00FC
    char _pad_0100[0x8];   // +0x0100
    int unknown_108;   // +0x0108
    char _pad_010C[0xF0];   // +0x010C
    unsigned char unknown_1FC;   // +0x01FC
    char _pad_01FD[0xF7];   // +0x01FD
    int unknown_2F4;   // +0x02F4
    char _pad_02F8[0x51E0];   // +0x02F8
    int unknown_54D8;   // +0x54D8
    int unknown_54DC;   // +0x54DC
    char _pad_54E0[0x16C];   // +0x54E0
    int unknown_564C;   // +0x564C
    int unknown_5650;   // +0x5650
    int unknown_5654;   // +0x5654
    int unknown_5658;   // +0x5658
    char _pad_565C[0xA4];   // +0x565C
    BA2EntryIndex unknown_5700;   // +0x5700
    char _pad_571C[0x5C];   // +0x571C
    unsigned char unknown_5778;   // +0x5778
    unsigned char unknown_5779;   // +0x5779
    // FUNCTION: GAMEMD 0x4F9950 (read-only here)
    void FUN_004F9950(int id);
    // FUNCTION: GAMEMD 0x509700 (read-only here)
    void FUN_00509700(int kind);
    // FUNCTION: GAMEMD 0x5060B0 (read-only here)
    HBCell FUN_005060B0(BA2Type* t, void (*callback)(), int arg);
    // FUNCTION: GAMEMD 0x506B90 (read-only here)
    HBCell FUN_00506B90(BA2Type* t);
    // FUNCTION: GAMEMD 0x50B760 (read-only here)
    bool FUN_0050B760(BA2Type* t, HBCell* cell);
    // FUNCTION: GAMEMD 0x500200 (read-only here)
    HBCell FUN_00500200(BA2Other* o);
    // FUNCTION: GAMEMD 0x53A130 (read-only here)
    bool FUN_0053A130();
    // FUNCTION: GAMEMD 0x4F9610 (read-only here)
    double FUN_004F9610(float value, int index);
    // FUNCTION: GAMEMD 0x50B6F0 (read-only here)
    bool FUN_0050B6F0();
    // FUNCTION: GAMEMD 0x4F93E0 (read-only here)
    void FUN_004F93E0(BA2Building* b);
    // FUNCTION: GAMEMD 0x4F9A90 (read-only here)
    bool FUN_004F9A90(BA2Obj* o);
    // FUNCTION: GAMEMD 0x50B730 (read-only here)
    bool FUN_0050B730();
};
GG_STATIC_ASSERT(offsetof(BA2House, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_FC) == 0xFC);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_108) == 0x108);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_1FC) == 0x1FC);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_2F4) == 0x2F4);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_54D8) == 0x54D8);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_54DC) == 0x54DC);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_564C) == 0x564C);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_5650) == 0x5650);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_5654) == 0x5654);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_5658) == 0x5658);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_5700) == 0x5700);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_5778) == 0x5778);
GG_STATIC_ASSERT(offsetof(BA2House, unknown_5779) == 0x5779);

// An object seen through its primary table (partial): the slots used by the cluster.
class BA2Obj
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
    virtual BA2House* vf_15();   // slot 15, +0x3C
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
    virtual bool vf_32();   // slot 32, +0x80
    virtual BA2Type* vf_33();   // slot 33, +0x84
    virtual BA2Type* vf_34();   // slot 34, +0x88
    virtual BA2Other* vf_35(BA2House* house);   // slot 35, +0x8C
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual HBCoord* vf_42(HBCoord* out, BA2Obj* target);   // slot 42, +0xA8
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual HBCoord* vf_45(HBCoord* out, int arg);   // slot 45, +0xB4
    virtual void vt_0B8();
    virtual void vt_0BC();
    virtual void vt_0C0();
    virtual void vt_0C4();
    virtual void vt_0C8();
    virtual void vt_0CC();
    virtual void vt_0D0();
    virtual void vf_53();   // slot 53, +0xD4
    virtual bool vf_54(HBCoord* where, int facing);   // slot 54, +0xD8
    virtual void vf_55(int arg);   // slot 55, +0xDC
    virtual void vf_56(int arg);   // slot 56, +0xE0
    virtual void vt_0E4();
    virtual void vt_0E8();
    virtual void vt_0EC();
    virtual void vt_0F0();
    virtual void vt_0F4();
    virtual void vf_62();   // slot 62, +0xF8
    virtual void vt_0FC();
    virtual int vf_64(BA2Other* obj, HBCell where);   // slot 64, +0x100
    virtual void vt_104();
    virtual HBCell* vf_66(int arg);   // slot 66, +0x108
    virtual void vt_10C();
    virtual void vt_110();
    virtual void vt_114();
    virtual void vt_118();
    virtual void vt_11C();
    virtual void vt_120();
    virtual void vf_73(int arg);   // slot 73, +0x124
    virtual void vt_128();
    virtual BA2Quad vf_75();   // slot 75, +0x12C
    virtual void vt_130();
    virtual void vt_134();
    virtual void vt_138();
    virtual void vt_13C();
    virtual void vt_140();
    virtual void vt_144();
    virtual void vt_148();
    virtual void vf_83();   // slot 83, +0x14C
    virtual void vt_150();
    virtual void vt_154();
    virtual void vt_158();
    virtual void vt_15C();
    virtual void vt_160();
    virtual void vt_164();
    virtual void vt_168();
    virtual int vf_91(int* damage, int distance, BA2Warhead* warhead, BA2Obj* attacker, bool ignoreDefenses, bool preventsPassengerEscape, BA2House* sourceHouse);   // slot 91, +0x16C
    virtual void vt_170();
    virtual void vf_93(HBCoord* where, int a, int b);   // slot 93, +0x174
    virtual void vt_178();
    virtual void vt_17C();
    virtual void vt_180();
    virtual int vf_97();   // slot 97, +0x184
    virtual void vt_188();
    virtual void vt_18C();
    virtual void vt_190();
    virtual int vf_101(BA2Other* from, int message, BA2Obj*& param);   // slot 101, +0x194
    virtual void vt_198();
    virtual void vf_103(int mode);   // slot 103, +0x19C
    virtual void vt_1A0();
    virtual void vt_1A4();
    virtual void vt_1A8();
    virtual int vf_107(BA2CellObj* cell, int a, int b, int c, int d);   // slot 107, +0x1AC
    virtual void vt_1B0();
    virtual void vf_109(HBCoord* where);   // slot 109, +0x1B4
    virtual HBCell vf_110();   // slot 110, +0x1B8
    virtual BA2Obj* vf_111();   // slot 111, +0x1BC
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
    virtual void vf_122(int mission, int arg);   // slot 122, +0x1E8
    virtual void vf_123();   // slot 123, +0x1EC
    virtual void vf_124(int arg);   // slot 124, +0x1F0
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
    virtual int vf_146();   // slot 146, +0x248
    virtual void vt_24C();
    virtual void vt_250();
    virtual int vf_149();   // slot 149, +0x254
    virtual void vt_258();
    virtual void vt_25C();
    virtual void vt_260();
    virtual void vt_264();
    virtual void vt_268();
    virtual void vt_26C();
    virtual void vt_270();
    virtual int vf_157(int arg);   // slot 157, +0x274
    virtual int vf_158(int a, BA2Obj* o);   // slot 158, +0x278
    virtual int vf_159(int a, BA2Obj*& param, BA2Obj* from);   // slot 159, +0x27C
    virtual void vf_160(int a);   // slot 160, +0x280
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
    virtual int vf_175();   // slot 175, +0x2BC
    virtual void vt_2C0();
    virtual void vt_2C4();
    virtual void vt_2C8();
    virtual void vt_2CC();
    virtual int vf_180();   // slot 180, +0x2D0
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
    virtual void vt_308();
    virtual BA2InfSize* vf_195();   // slot 195, +0x30C
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
    virtual void vf_219();   // slot 219, +0x36C
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
    virtual bool vf_235(BA2Obj* target);   // slot 235, +0x3AC
    virtual void vt_3B0();
    virtual void vt_3B4();
    virtual void vt_3B8();
    virtual void vt_3BC();
    virtual void vt_3C0();
    virtual void vt_3C4();
    virtual void vf_242(BA2Obj* target);   // slot 242, +0x3C8
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
    virtual BA2Slot* vf_254(int which);   // slot 254, +0x3F8
    virtual void vt_3FC();
    virtual void vt_400();
    virtual void vt_404();
    virtual int vf_258();   // slot 258, +0x408
    virtual void vt_40C();
    virtual void vf_260(int arg);   // slot 260, +0x410
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
    virtual void vf_288(BA2Obj* o, int flag);   // slot 288, +0x480
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
    virtual HBCell vf_309(BA2Obj* who, HBCell preferred);   // slot 309, +0x4D4
    virtual void vt_4D8();
    virtual void vt_4DC();
    virtual void vt_4E0();
    virtual void vt_4E4();
    virtual void vt_4E8();
    virtual void vf_315(int a, BA2Obj* attacker, bool flag, HBCell* cells);   // slot 315, +0x4EC

};
GG_STATIC_ASSERT(sizeof(BA2Obj) == 0x4);

// The object at +0x218 of a building (partial).
class BA2Tether : public BA2Obj
{
public:
    char _pad_0004[0xE8];   // +0x0004
    int unknown_EC;   // +0x00EC
};
GG_STATIC_ASSERT(offsetof(BA2Tether, unknown_EC) == 0xEC);

// A map cell object (partial).
class BA2CellObj : public BA2Obj
{
public:
    char _pad_0004[0xE8];   // +0x0004
    int unknown_EC;   // +0x00EC
    // FUNCTION: GAMEMD 0x481180 (read-only here)
    HBCoord* FUN_00481180(HBCoord* out, HBCoord* from, int a, int b, int c);
    // FUNCTION: GAMEMD 0x47C520 (read-only here)
    BA2Obj* FUN_0047C520();
    // FUNCTION: GAMEMD 0x47C3D0 (read-only here)
    int FUN_0047C3D0(HBCell* buffer, int a, int b);
    // FUNCTION: GAMEMD 0x480A30 (read-only here)
    HBCoord* FUN_00480A30(HBCoord* out);
};
GG_STATIC_ASSERT(offsetof(BA2CellObj, unknown_EC) == 0xEC);

// The object at +0x6C4 of a sender (partial).
struct BA2Cargo
{
    char _pad_0000[0xE0D];   // +0x0000
    unsigned char unknown_E0D;   // +0x0E0D
    unsigned char unknown_E0E;   // +0x0E0E
    unsigned char unknown_E0F;   // +0x0E0F
};
GG_STATIC_ASSERT(offsetof(BA2Cargo, unknown_E0D) == 0xE0D);
GG_STATIC_ASSERT(offsetof(BA2Cargo, unknown_E0E) == 0xE0E);
GG_STATIC_ASSERT(offsetof(BA2Cargo, unknown_E0F) == 0xE0F);

// The IRTTITypeInfo table at +0x04 of an object (stdcall slots).
class BA2Rtti
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual int __stdcall vf_3();   // slot 3, +0xC

};
GG_STATIC_ASSERT(sizeof(BA2Rtti) == 0x4);

// The sender of a radio message (partial).
class BA2Other : public BA2Obj
{
public:
    BA2Rtti unknown_04;   // +0x0004
    char _pad_0008[0xC];   // +0x0008
    unsigned char unknown_14;   // +0x0014
    char _pad_0015[0x87];   // +0x0015
    HBCoord Location;   // +0x009C
    char _pad_00A8[0x4];   // +0x00A8
    int unknown_AC;   // +0x00AC
    char _pad_00B0[0x4];   // +0x00B0
    int unknown_B4;   // +0x00B4
    char _pad_00B8[0x204];   // +0x00B8
    BA2Link* unknown_2BC;   // +0x02BC
    char _pad_02C0[0x18];   // +0x02C0
    BA2Link2* unknown_2D8;   // +0x02D8
    char _pad_02DC[0xAC];   // +0x02DC
    BA2Facing Facing;   // +0x0388
    char _pad_0389[0x4C];   // +0x0389
    unsigned char unknown_3D5;   // +0x03D5
    char _pad_03D6[0x14A];   // +0x03D6
    BA2Type* Type;   // +0x0520
    char _pad_0524[0x80];   // +0x0524
    BA2Obj* unknown_5A4;   // +0x05A4
    char _pad_05A8[0x11C];   // +0x05A8
    BA2Cargo* unknown_6C4;   // +0x06C4
    char _pad_06C8[0x4];   // +0x06C8
    BA2Building* unknown_6CC;   // +0x06CC
    // FUNCTION: GAMEMD 0x70FB50 (read-only here)
    bool FUN_0070FB50();
    // FUNCTION: GAMEMD 0x7105E0 (read-only here)
    bool FUN_007105E0();
    // FUNCTION: GAMEMD 0x5F6060 (read-only here)
    void FUN_005F6060(int arg);
    // FUNCTION: GAMEMD 0x703590 (read-only here)
    HBCell FUN_00703590(BA2Building* b);
    // FUNCTION: GAMEMD 0x417FD0 (read-only here)
    int FUN_00417FD0();
    // FUNCTION: GAMEMD 0x70C610 (read-only here)
    void FUN_0070C610(BA2Obj* o);
    // FUNCTION: GAMEMD 0x4DA0E0 (read-only here)
    void FUN_004DA0E0(BA2Obj* o);
};
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BA2Other, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_2BC) == 0x2BC);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_2D8) == 0x2D8);
GG_STATIC_ASSERT(offsetof(BA2Other, Facing) == 0x388);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_3D5) == 0x3D5);
GG_STATIC_ASSERT(offsetof(BA2Other, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_5A4) == 0x5A4);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_6C4) == 0x6C4);
GG_STATIC_ASSERT(offsetof(BA2Other, unknown_6CC) == 0x6CC);

// An occupant object (partial).
class BA2Occupant : public BA2Obj
{
public:
    char _pad_0004[0x4FC];   // +0x0004
    int unknown_500;   // +0x0500
};
GG_STATIC_ASSERT(offsetof(BA2Occupant, unknown_500) == 0x500);

// The object reached through the first member of the slot-254 result (partial).
class BA2First : public BA2Obj
{
public:
    char _pad_0004[0x9C];   // +0x0004
    BA2ObjType* ObjType;   // +0x00A0
};
GG_STATIC_ASSERT(offsetof(BA2First, ObjType) == 0xA0);

// What slot 254 returns: a pointer whose first member is an object.
struct BA2Slot
{
    BA2First* First;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(BA2Slot, First) == 0x0);

// The audio controller member at BuildingClass +0x6A0 (partial).
struct BA2AudioCtl
{
    // FUNCTION: GAMEMD 0x406060 (read-only here)
    void FUN_00406060();
};

// A five-dword block copied between objects.
struct BA2Block5
{
    int Values[5];   // +0x0000
};
GG_STATIC_ASSERT(offsetof(BA2Block5, Values) == 0x0);

// A unit type (opaque here).
struct BA2UnitType
{
};

// The type object of an infantry (partial).
struct BA2InfType
{
    char _pad_0000[0xC9E];   // +0x0000
    unsigned char unknown_C9E;   // +0x0C9E
};
GG_STATIC_ASSERT(offsetof(BA2InfType, unknown_C9E) == 0xC9E);

// What slot 195 returns (partial).
struct BA2InfSize
{
    char _pad_0000[0xEC3];   // +0x0000
    unsigned char unknown_EC3;   // +0x0EC3
};
GG_STATIC_ASSERT(offsetof(BA2InfSize, unknown_EC3) == 0xEC3);

// The object at +0x34 of a unit-making building (partial).
struct BA2Link34
{
    char _pad_0000[0x2C];   // +0x0000
    int unknown_2C;   // +0x002C
};
GG_STATIC_ASSERT(offsetof(BA2Link34, unknown_2C) == 0x2C);

// The object at BuildingClass +0x2D8 (partial).
struct BA2Link2
{
    // FUNCTION: GAMEMD 0x6B0DB0 (read-only here)
    void FUN_006B0DB0();
    // FUNCTION: GAMEMD 0x6B0D60 (read-only here)
    void FUN_006B0D60();
    // FUNCTION: GAMEMD 0x6AF580 (read-only here)
    void FUN_006AF580(BA2Unit* u);
};

// The float vector member at BuildingClass +0x33C (partial: methods only).
struct BA2FloatVec
{
    // FUNCTION: GAMEMD 0x6C9820 (read-only here) - the next index or -1
    int FUN_006C9820();
    // FUNCTION: GAMEMD 0x6C9680 (read-only here)
    float FUN_006C9680(int index);
    // FUNCTION: GAMEMD 0x6C96B0 (read-only here)
    float FUN_006C96B0(float value, int index);
};

// The passenger list member at BuildingClass +0x114 (partial).
struct BA2PassengerList
{
    int Count;   // +0x0000
    // FUNCTION: GAMEMD 0x473430 (read-only here) - the next passenger or 0
    BA2Infantry* FUN_00473430();
};
GG_STATIC_ASSERT(offsetof(BA2PassengerList, Count) == 0x0);

// The TechnoClass part of the building views (partial): fields below +0x2BC.
class BA2Tech : public BA2Obj
{
public:
    char _pad_0004[0x30];   // +0x0004
    BA2Link34* unknown_34;   // +0x0034
    char _pad_0038[0x34];   // +0x0038
    int unknown_6C;   // +0x006C
    int unknown_70;   // +0x0070
    char _pad_0074[0xC];   // +0x0074
    unsigned char unknown_80;   // +0x0080
    unsigned char unknown_81;   // +0x0081
    char _pad_0082[0x1];   // +0x0082
    unsigned char unknown_83;   // +0x0083
    char _pad_0084[0x8];   // +0x0084
    unsigned char unknown_8C;   // +0x008C
    char _pad_008D[0x3];   // +0x008D
    unsigned char unknown_90;   // +0x0090
    char _pad_0091[0xB];   // +0x0091
    HBCoord Location;   // +0x009C
    char _pad_00A8[0x4];   // +0x00A8
    int unknown_AC;   // +0x00AC
    char _pad_00B0[0xC];   // +0x00B0
    int unknown_BC;   // +0x00BC
    char _pad_00C0[0x28];   // +0x00C0
    int unknown_E8;   // +0x00E8
    char _pad_00EC[0x28];   // +0x00EC
    BA2PassengerList unknown_114;   // +0x0114
    int unknown_118;   // +0x0118
    char _pad_011C[0x34];   // +0x011C
    int unknown_150;   // +0x0150
    char _pad_0154[0xC0];   // +0x0154
    int unknown_214;   // +0x0214
    BA2Tether* unknown_218;   // +0x0218
    BA2House* Owner;   // +0x021C
    char _pad_0220[0x8C];   // +0x0220
    int unknown_2AC;   // +0x02AC
    char _pad_02B0[0x4];   // +0x02B0
    BA2Obj* unknown_2B4;   // +0x02B4
    char _pad_02B8[0x4];   // +0x02B8
};
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_81) == 0x81);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_83) == 0x83);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(BA2Tech, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_E8) == 0xE8);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_118) == 0x118);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_150) == 0x150);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_214) == 0x214);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_218) == 0x218);
GG_STATIC_ASSERT(offsetof(BA2Tech, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_2AC) == 0x2AC);
GG_STATIC_ASSERT(offsetof(BA2Tech, unknown_2B4) == 0x2B4);
GG_STATIC_ASSERT(sizeof(BA2Tech) == 0x2BC);

// An infantry soldier (sizeof 0x6F0 from the allocation; partial).
class BA2Infantry : public BA2Tech
{
public:
    char _pad_02BC[0x17C];   // +0x02BC
    unsigned char unknown_438;   // +0x0438
    unsigned char unknown_439;   // +0x0439
    char _pad_043A[0x286];   // +0x043A
    BA2InfType* unknown_6C0;   // +0x06C0
    char _pad_06C4[0x15];   // +0x06C4
    unsigned char unknown_6D9;   // +0x06D9
    char _pad_06DA[0x16];   // +0x06DA
    // FUNCTION: GAMEMD 0x517A50 (read-only here) - the constructor
    BA2Infantry(BA2InfSize* type, BA2House* owner);
};
GG_STATIC_ASSERT(offsetof(BA2Infantry, unknown_438) == 0x438);
GG_STATIC_ASSERT(offsetof(BA2Infantry, unknown_439) == 0x439);
GG_STATIC_ASSERT(offsetof(BA2Infantry, unknown_6C0) == 0x6C0);
GG_STATIC_ASSERT(offsetof(BA2Infantry, unknown_6D9) == 0x6D9);
GG_STATIC_ASSERT(sizeof(BA2Infantry) == 0x6F0);

// A unit (sizeof 0x8E8 from the allocation; partial).
class BA2Unit : public BA2Tech
{
public:
    char _pad_02BC[0xB4];   // +0x02BC
    BA2Facing Turret;   // +0x0370
    char _pad_0371[0x16B];   // +0x0371
    BA2Block5 unknown_4DC;   // +0x04DC
    int unknown_4F0;   // +0x04F0
    int unknown_4F4;   // +0x04F4
    char _pad_04F8[0x3F0];   // +0x04F8
    // FUNCTION: GAMEMD 0x7353C0 (read-only here) - the constructor
    BA2Unit(BA2UnitType* type, BA2House* owner);
    // FUNCTION: GAMEMD 0x5F5B50 (read-only here)
    void FUN_005F5B50(BA2Link34* link);
};
GG_STATIC_ASSERT(offsetof(BA2Unit, Turret) == 0x370);
GG_STATIC_ASSERT(offsetof(BA2Unit, unknown_4DC) == 0x4DC);
GG_STATIC_ASSERT(offsetof(BA2Unit, unknown_4F0) == 0x4F0);
GG_STATIC_ASSERT(offsetof(BA2Unit, unknown_4F4) == 0x4F4);
GG_STATIC_ASSERT(sizeof(BA2Unit) == 0x8E8);

// Partial BuildingClass view (sizeof not modelled).
class BA2Building : public BA2Tech
{
public:
    BA2Link* unknown_2BC;   // +0x02BC
    int unknown_2C0;   // +0x02C0
    char _pad_02C4[0x14];   // +0x02C4
    BA2Link2* unknown_2D8;   // +0x02D8
    char _pad_02DC[0x8];   // +0x02DC
    BA2Occupant* unknown_2E4;   // +0x02E4
    char _pad_02E8[0x14];   // +0x02E8
    int unknown_2FC;   // +0x02FC
    char _pad_0300[0xC];   // +0x0300
    BA2Floater* unknown_30C;   // +0x030C
    char _pad_0310[0x2C];   // +0x0310
    BA2FloatVec unknown_33C;   // +0x033C
    char _pad_033D[0x13];   // +0x033D
    BA2Stage Stage;   // +0x0350
    char _pad_0351[0x1F];   // +0x0351
    BA2Facing Turret;   // +0x0370
    char _pad_0371[0x17];   // +0x0371
    BA2Facing Facing;   // +0x0388
    char _pad_0389[0x8F];   // +0x0389
    unsigned char unknown_418;   // +0x0418
    char _pad_0419[0x1];   // +0x0419
    unsigned char unknown_41A;   // +0x041A
    char _pad_041B[0xC1];   // +0x041B
    BA2Block5 unknown_4DC;   // +0x04DC
    int unknown_4F0;   // +0x04F0
    int unknown_4F4;   // +0x04F4
    char _pad_04F8[0x28];   // +0x04F8
    BA2Type* Type;   // +0x0520
    int unknown_524;   // +0x0524
    int unknown_528;   // +0x0528
    char _pad_052C[0x4];   // +0x052C
    int unknown_530;   // +0x0530
    int BState;   // +0x0534
    char _pad_0538[0x4];   // +0x0538
    int unknown_53C;   // +0x053C
    char _pad_0540[0x1C];   // +0x0540
    BA2Obj* Anims[0x15];   // +0x055C
    char _pad_05B0[0x18];   // +0x05B0
    BA2Obj* DamageFireAnims[8];   // +0x05C8
    BA2Obj* UpgradeSlots[4];   // +0x05E8
    char _pad_05F8[0xC];   // +0x05F8
    BA2Timer Timer;   // +0x0604
    BA2Light* LightSource;   // +0x0614
    char _pad_0618[0x48];   // +0x0618
    unsigned char unknown_660;   // +0x0660
    char _pad_0661[0x3F];   // +0x0661
    BA2AudioCtl Audio;   // +0x06A0
    char _pad_06A1[0x3C];   // +0x06A1
    unsigned char unknown_6DD;   // +0x06DD
    char _pad_06DE[0x2];   // +0x06DE
    unsigned char unknown_6E0;   // +0x06E0
    char _pad_06E1[0x5];   // +0x06E1
    bool unknown_6E6;   // +0x06E6
    char _pad_06E7[0x4];   // +0x06E7
    unsigned char unknown_6EB;   // +0x06EB
    unsigned char unknown_6EC;   // +0x06EC
    char _pad_06ED[0x15];   // +0x06ED
    signed char unknown_702;   // +0x0702
    signed char unknown_703;   // +0x0703
    virtual int vf_91(int* damage, int distance, BA2Warhead* warhead, BA2Obj* attacker, bool ignoreDefenses, bool preventsPassengerEscape, BA2House* sourceHouse);
    virtual int vf_101(BA2Other* from, int message, BA2Obj*& param);
    virtual int vf_149();
    virtual int vf_146();
    virtual int vf_64(BA2Other* obj, HBCell where);
    // the unit-spawn condition shared by the sell sequence (defined inline in building_a2_sell.cpp)
    bool SpawnsUnit();
    virtual HBCell vf_309(BA2Obj* who, HBCell preferred);
    // the damage-state animation refresh (defined inline in building_a2_damage.cpp)
    void RefreshAnimStates();
    // FUNCTION: GAMEMD 0x44E3A0 (read-only here)
    bool FUN_0044E3A0();
    // FUNCTION: GAMEMD 0x65ADC0 (read-only here)
    bool FUN_0065ADC0();
    // FUNCTION: GAMEMD 0x65AE30 (read-only here)
    bool FUN_0065AE30();
    // FUNCTION: GAMEMD 0x451690 (read-only here)
    void FUN_00451690();
    // FUNCTION: GAMEMD 0x4533A0 (read-only here)
    void FUN_004533A0(int arg);
    // FUNCTION: GAMEMD 0x6F4AB0 (read-only here) - the base-class radio handler
    int FUN_006F4AB0(BA2Other* from, int message, BA2Obj*& param);
    // FUNCTION: GAMEMD 0x65ADF0 (read-only here)
    bool FUN_0065ADF0(BA2Other* o);
    // FUNCTION: GAMEMD 0x65AD50 (read-only here)
    bool FUN_0065AD50(BA2Other* o);
    // FUNCTION: GAMEMD 0x451E40 (read-only here)
    void FUN_00451E40(int arg);
    // FUNCTION: GAMEMD 0x447780 (read-only here)
    void FUN_00447780(int arg);
    // FUNCTION: GAMEMD 0x5B3A00 (read-only here)
    BA2Price* FUN_005B3A00();
    // FUNCTION: GAMEMD 0x5F5C60 (read-only here)
    double FUN_005F5C60();
    // FUNCTION: GAMEMD 0x43EF90 (read-only here)
    int FUN_0043EF90();
    // FUNCTION: GAMEMD 0x708080 (read-only here)
    void FUN_00708080(BA2Obj* attacker);
    // FUNCTION: GAMEMD 0x65AD30 (read-only here)
    BA2Occupant* FUN_0065AD30(int index);
    // FUNCTION: GAMEMD 0x4593A0 (read-only here)
    void FUN_004593A0();
    // FUNCTION: GAMEMD 0x70FEE0 (read-only here)
    void FUN_0070FEE0(int arg);
    // FUNCTION: GAMEMD 0x457DE0 (read-only here)
    void FUN_00457DE0(int a, int b);
    // FUNCTION: GAMEMD 0x441F60 (read-only here)
    void FUN_00441F60();
    // FUNCTION: GAMEMD 0x451890 (read-only here)
    void FUN_00451890(char* name, int index, int flag, int a, int b);
    // FUNCTION: GAMEMD 0x701900 (read-only here) - the base-class ReceiveDamage
    int FUN_00701900(int* damage, int distance, BA2Warhead* warhead, BA2Obj* attacker, bool ignoreDefenses, bool preventsPassengerEscape, BA2House* sourceHouse);
};
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_2BC) == 0x2BC);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_2C0) == 0x2C0);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_2D8) == 0x2D8);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_2E4) == 0x2E4);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_30C) == 0x30C);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_33C) == 0x33C);
GG_STATIC_ASSERT(offsetof(BA2Building, Stage) == 0x350);
GG_STATIC_ASSERT(offsetof(BA2Building, Turret) == 0x370);
GG_STATIC_ASSERT(offsetof(BA2Building, Facing) == 0x388);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_418) == 0x418);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_41A) == 0x41A);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_4DC) == 0x4DC);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_4F0) == 0x4F0);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_4F4) == 0x4F4);
GG_STATIC_ASSERT(offsetof(BA2Building, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_524) == 0x524);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_528) == 0x528);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_530) == 0x530);
GG_STATIC_ASSERT(offsetof(BA2Building, BState) == 0x534);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_53C) == 0x53C);
GG_STATIC_ASSERT(offsetof(BA2Building, Anims) == 0x55C);
GG_STATIC_ASSERT(offsetof(BA2Building, DamageFireAnims) == 0x5C8);
GG_STATIC_ASSERT(offsetof(BA2Building, UpgradeSlots) == 0x5E8);
GG_STATIC_ASSERT(offsetof(BA2Building, Timer) == 0x604);
GG_STATIC_ASSERT(offsetof(BA2Building, LightSource) == 0x614);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_660) == 0x660);
GG_STATIC_ASSERT(offsetof(BA2Building, Audio) == 0x6A0);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6DD) == 0x6DD);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6E0) == 0x6E0);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6E6) == 0x6E6);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6EB) == 0x6EB);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6EC) == 0x6EC);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_702) == 0x702);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_703) == 0x703);


// GLOBAL: GAMEMD 0x8871E0 / 0xA8B230 / 0x887324 - the rules, the source object and the screen object.
extern BA2Rules* RulesInstance_8871E0;
#include "../../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;
extern BA2Screen* DAT_00887324;
// GLOBAL: GAMEMD 0x87F7E8 - the map; 0x89C818 - the invalid cell.
extern BA2Map DAT_0087F7E8;
extern HBCell DAT_0089C818;
// GLOBAL: GAMEMD 0x89F698 / 0x89F69C (cell offsets), 0xA83C6C (the type table)
extern HBCell DAT_0089F698;
extern HBCell DAT_0089F69C;
extern BA2Type** DAT_00A83C6C;
// GLOBAL: GAMEMD 0x7E2820 / 0x7E2818 - the two double constants of the facing-angle conversion.
extern const double DAT_007E2820;
extern const double DAT_007E2818;
// FUNCTION: GAMEMD 0x4CAE30 (read-only here) - the angle of a vector
double __cdecl FUN_004CAE30(double a, double b);
// FUNCTION: GAMEMD 0x505F80 (read-only here) - a callback address
void FUN_00505F80();
// GLOBAL: GAMEMD 0x87F8DC / 0x87F8E4 / 0x87F8E8 / 0x87F8EC / 0x87F8F0 - placement settings (ints used as shorts)
extern int DAT_0087F8DC;
extern int DAT_0087F8E4;
extern int DAT_0087F8E8;
extern int DAT_0087F8EC;
extern int DAT_0087F8F0;
extern unsigned char DAT_00A8B320;
extern int DAT_00A8EC88;
extern BA2Tech** DAT_00A8EC7C;
extern int DAT_0089F6F0;
extern int DAT_0089F6F4;
extern unsigned char DAT_00822CF2;
// STRING: GAMEMD 0x819030 - the EVA speech name.
extern const char s_EVA_StructureSold_00819030[];
// FUNCTION: GAMEMD 0x752700 (read-only here) - the string in ECX, two further arguments (EDX and the stack).
void FUN_00752700(const char* name, int a, int b);
// FUNCTION: GAMEMD 0x750D40 (read-only here) - stops/plays the sound of an audio controller at a position.
void FUN_00750D40(HBCoord* where, struct BA2AudioCtl* audio);
// FUNCTION: GAMEMD 0x4060F0 (read-only here) - clears a five-dword block.
void FUN_004060F0(struct BA2Block5* block, int a, int b);
// GLOBAL: GAMEMD 0xA8E7AC, 0x89C848 (a zero coordinate)
extern int DAT_00A8E7AC;
extern HBCoord DAT_0089C848;
// FUNCTION: GAMEMD 0x4CAC40 (read-only here) - the square root
double __cdecl FUN_004CAC40(double a);
// FUNCTION: GAMEMD 0x7509E0 (read-only here) - plays a sound at a position (the sound id in ECX).
void FUN_007509E0(int sound, HBCoord* where, void* unused);
// FUNCTION: GAMEMD 0x750E20 (read-only here) - plays a sound at a position (the sound id in ECX).
void FUN_00750E20(int sound, HBCoord* where, int unused);
// FUNCTION: GAMEMD 0x49F420 (read-only here) - the scattered coordinate near a point (result buffer in ECX, point in EDX).
HBCoord* FUN_0049F420(HBCoord* out, HBCoord* from, int distance, int flag);




// BEGIN canonical-layout asserts
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6C) == HB_BLD_HEALTH);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_70) == HB_BLD_UNKNOWN_70);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_80) == HB_BLD_NEEDS_REDRAW);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_81) == HB_BLD_IN_LIMBO);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_90) == HB_BLD_IS_ALIVE);
GG_STATIC_ASSERT(offsetof(BA2Building, Location) == HB_BLD_LOCATION);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_AC) == HB_BLD_CURRENT_MISSION);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_BC) == HB_BLD_STATUS);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_E8) == HB_BLD_UNKNOWN_E8);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_114) == HB_BLD_UNKNOWN_114);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_150) == HB_BLD_UNKNOWN_150);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_218) == HB_BLD_UNKNOWN_218);
GG_STATIC_ASSERT(offsetof(BA2Building, Owner) == HB_BLD_OWNER);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_2B4) == HB_BLD_TARGET);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_2C0) == HB_BLD_MIND_CONTROLLED_BY);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_2FC) == HB_BLD_UNKNOWN_2FC);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_30C) == HB_BLD_UNKNOWN_30C);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_33C) == HB_BLD_UNKNOWN_33C);
GG_STATIC_ASSERT(offsetof(BA2Building, Stage) == HB_BLD_STAGE);
GG_STATIC_ASSERT(offsetof(BA2Building, Turret) == HB_BLD_TURRET);
GG_STATIC_ASSERT(offsetof(BA2Building, Facing) == HB_BLD_FACING);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_418) == HB_BLD_UNKNOWN_418);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_41A) == HB_BLD_UNKNOWN_41A);
GG_STATIC_ASSERT(offsetof(BA2Building, Type) == HB_BLD_TYPE);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_524) == HB_BLD_FACTORY);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_528) == HB_BLD_C4_TIMER);
GG_STATIC_ASSERT(offsetof(BA2Building, BState) == HB_BLD_BSTATE);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_53C) == HB_BLD_OWNER_COUNTRY_INDEX);
GG_STATIC_ASSERT(offsetof(BA2Building, Anims) == HB_BLD_ANIMS);
GG_STATIC_ASSERT(offsetof(BA2Building, DamageFireAnims) == HB_BLD_DAMAGE_FIRE_ANIMS);
GG_STATIC_ASSERT(offsetof(BA2Building, LightSource) == HB_BLD_LIGHT_SOURCE);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_660) == HB_BLD_HAS_POWER);
GG_STATIC_ASSERT(offsetof(BA2Building, Audio) == HB_BLD_AUDIO7);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6DD) == HB_BLD_IS_READY_TO_COMMENCE);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6E0) == HB_BLD_NO_CREW);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6E6) == HB_BLD_IS_DAMAGED);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6EB) == HB_BLD_HAS_CLOAKING_DATA);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_6EC) == HB_BLD_CLOAK_RADIUS);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_702) == HB_BLD_UPGRADE_LEVEL);
GG_STATIC_ASSERT(offsetof(BA2Building, unknown_530) == HB_BLD_C4_TIMER + 8);   // the timer's TimeLeft
GG_STATIC_ASSERT(offsetof(BA2Building, UpgradeSlots) == HB_BLD_UPGRADES - 4);   // indexed by the upgrade level 1..3
// END canonical-layout asserts

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A2_VIEWS_H
