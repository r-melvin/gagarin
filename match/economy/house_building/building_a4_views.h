// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Address-scoped partial views for the "building-a4" cluster of the house/building module: the six
//   BuildingClass virtual bodies at 0x43DA80, 0x43F180, 0x440580, 0x445880, 0x448260 and 0x44ACF0 (primary-table
//   slots 313, 73, 54, 53, 245 and 132 of .?AVBuildingClass@@, type descriptor 0x818D60, table 0x7E3EBC).
//   Every field below is a [reg+disp] operand read from the retail gamemd.exe v1.001 in one of those bodies;
//   the views are NOT the canonical classes and are sparse. Slots are retail primary-table indices
//   (byte offset / 4); virtuals named vt_XXX only position the slots actually used.
//   Maintained by hand since the module consolidation; shared types come from house_building_common_types.h.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A4_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A4_VIEWS_H

#include <stddef.h>
#include "../../_layout/session_class.h"
#include "../../_rt/gg_static_assert.h"
#include "house_building_layout.h"
#include "../../core/cell_step_tables.h"
#include "house_building_common_types.h"
#include "house_building_common_types.h"
#include "house_building_common_types.h"

class BA4Object;
class BA4Type;
class BA4House;
class BA4Building;
struct BA4Screen;
struct BA4TypeEntry;
class BA4AnimInfo;
class BA4Country;
class BA4OverlayType;
struct BA4Session;
struct BA4Sub350;
struct BA4Difficulty;
struct BA4HouseSub;
struct BA4HouseSub2;
class BA4Factory;
struct BA4Op38;
struct BA4Obj33;
class BA4Spotlight;
class BA4Tracker;
class BA4Light;
struct BA4MapCell;

// A pointer-sized vector (vptr, Items, Capacity, IsInitialized, IsAllocated, Count, CapacityIncrement; 0x18 bytes). Only
// slot 2 (SetCapacity) is reached by the inlined AddItem.
template <class T> class BA4Vector
{
public:
    BA4Vector(int size, T* mem);   // FUNCTION: GAMEMD 0x45AE50 (read-only here)
    virtual ~BA4Vector() { if (Items && IsAllocated) delete [] Items; }   // slot 0
    virtual bool vt_1();
    virtual bool SetCapacity(int capacity, T* mem);   // slot 2
    virtual void vt_3();
    virtual int FindItemIndex(T* item);               // slot 4

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
GG_STATIC_ASSERT(sizeof(BA4Vector<int*>) == 0x18);

// The audio/EVA entry points used by the owner-change body (read-only here).
// FUNCTION: GAMEMD 0x752700 (read-only here) - the speech name in ECX, two further arguments (EDX and the stack).
void FUN_00752700(const char* name, int a, int b);
// FUNCTION: GAMEMD 0x752480 (read-only here)
void FUN_00752480(int id, int a, int b);
// FUNCTION: GAMEMD 0x65FA70 (read-only here)
bool FUN_0065FA70(int a, HBCell cell);
extern const char s_EVA_BuildingCaptured_00818FAC[];
extern const char s_EVA_TechBuildingLost_00818FC4[];

// Allocated with the game's operator new (0x7C8E17) at 0x4C, 0x100 and 0xE8 bytes (opaque here).
class BA4Light
{
public:
    // FUNCTION: GAMEMD 0x554760 (read-only here) - thiscall, a coordinate by value and five ints.
    BA4Light(HBCoordPod where, int a, int b, int c, int d, int e);
    // FUNCTION: GAMEMD 0x554A60 (read-only here)
    void FUN_00554A60(char flag);
    static void* operator new(unsigned int size);
};
class BA4Tracker
{
public:
    // FUNCTION: GAMEMD 0x62DC50 (read-only here)
    BA4Tracker(int type, HBCoordPod* where, BA4MapCell* cell, int a, int* table, int b);
    static void* operator new(unsigned int size);
};

// An entry of the list gathered while changing owner: an object and one flag byte (8 bytes, allocated with the game's operator new).
struct BA4Held
{
    BA4Object*    Object;   // +0x00
    unsigned char Flag;     // +0x04
    BA4Held(BA4Object* object, unsigned char flag) { Object = object; Flag = flag; }
    static void* operator new(unsigned int size);
};

// The local list of BA4Held* of the owner-change body: base constructor out of line, growth set by the derived part.
class BA4HeldList : public BA4Vector<BA4Held*>
{
public:
    BA4HeldList() : BA4Vector<BA4Held*>(0, 0) { Count = 0; CapacityIncrement = 10; }
};

// A target reference (a 32-bit value and one tag byte; copied member-wise as five bytes).
#pragma pack(push, 1)
// Not merged: takes this cluster's BuildingClass view (see house_building_views.h).
struct BA4TargetRef
{
    int           Value;   // +0x00
    unsigned char Tag;     // +0x04
    // FUNCTION: GAMEMD 0x6E6AB0 (read-only here) - builds the reference to a building in place.
    BA4TargetRef* FUN_006E6AB0(BA4Building* b);
};
#pragma pack(pop)
GG_STATIC_ASSERT(sizeof(BA4TargetRef) == 5);

// The facing member at BuildingClass +0x388 (partial; size not known, only its address is used).
struct BA4Facing
{
    // FUNCTION: GAMEMD 0x4C9480 (read-only here)
    bool FUN_004C9480();
    // FUNCTION: GAMEMD 0x4C93D0 (read-only here) - returned by value through a hidden pointer.
    HBDir FUN_004C93D0();
    // FUNCTION: GAMEMD 0x4C9300 (read-only here)
    void FUN_004C9300(HBDir* dir);
    // FUNCTION: GAMEMD 0x4C9220 (read-only here)
    void FUN_004C9220(HBDir* dir);
};


// A colour of three bytes.
struct BA4Rgb
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};
GG_STATIC_ASSERT(sizeof(BA4Rgb) == 3);

// A 3x4 matrix of floats (rotation 3x3 with the translation in column 3), 12 floats, without a constructor.
struct BA4MatrixTemp
{
    float M[12];
    // FUNCTION: GAMEMD 0x754BE0 (read-only here) - sets this to the default matrix and returns it.
    BA4MatrixTemp* FUN_00754BE0();
};
struct BA4Matrix : public BA4MatrixTemp
{
    // FUNCTION: GAMEMD 0x5AE860 (read-only here) - makes the identity.
    BA4Matrix();
    // FUNCTION: GAMEMD 0x5AE8F0 (read-only here) - applies a translation.
    void FUN_005AE8F0(float* v);
    // FUNCTION: GAMEMD 0x5AE980 (read-only here)
    void FUN_005AE980(float angle);
    // FUNCTION: GAMEMD 0x5AF080 (read-only here)
    void FUN_005AF080(float angle);
    // FUNCTION: GAMEMD 0x5AF1A0 (read-only here)
    void FUN_005AF1A0(float angle);
};
GG_STATIC_ASSERT(sizeof(BA4Matrix) == 0x30);
// FUNCTION: GAMEMD 0x5AF980 (read-only here) - dest in ECX, the second operand in EDX, the first on the stack.
BA4MatrixTemp* FUN_005AF980(BA4MatrixTemp* dest, BA4MatrixTemp* b, BA4MatrixTemp* a);

// A voxel-set record of the type (a set pointer and its frame list).
struct BA4Frames
{
    char unknown_00[8];
    int  unknown_08;   // +0x08 the frame count
};
struct BA4VoxelDef
{
    int        unknown_00;   // +0x00 the voxel set
    BA4Frames* unknown_04;   // +0x04 its frame list
};
GG_STATIC_ASSERT(sizeof(BA4VoxelDef) == 8);
struct BA4VoxelOpts
{
    char bytes[0x14];
};

// One 0x44-byte entry of the per-type table at BuildingTypeClass +0xF4C (partial).
struct BA4TypeEntry
{
    char     unknown_00[0x10];   // +0x00 a name copied with strncpy
    char     unknown_10[0x20];   // +0x10
    HBCoordPod unknown_30;         // +0x30 an offset coordinate
    char     unknown_3C[4];      // +0x3C
    unsigned char unknown_40;    // +0x40
    char     unknown_41[3];      // +0x41
};
GG_STATIC_ASSERT(offsetof(BA4TypeEntry, unknown_30) == 0x30);
GG_STATIC_ASSERT(sizeof(BA4TypeEntry) == 0x44);

// The object created by the ctor at 0x5FC380 (0xB0 bytes allocated, opaque here).
class BA4Spawned
{
public:
    BA4Spawned(BA4OverlayType* type, HBCell* cell, int value);
    static void* operator new(unsigned int size);
};

// The object at an anim +0xC8 (partial).
struct BA4AnimInfo
{
    char _pad_0000[0x35C];   // +0x0000
    unsigned char unknown_35C;   // +0x035C
};
GG_STATIC_ASSERT(offsetof(BA4AnimInfo, unknown_35C) == 0x35C);

// An object reached through a pointer array of a building (partial).
class BA4Object
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
    virtual int vf_11();   // slot 11, +0x2C
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual HBCoordPod* vf_18(HBCoordPod* out);   // slot 18, +0x48
    virtual HBCoordPod* vf_19(HBCoordPod* out, int a);   // slot 19, +0x4C
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
    virtual HBCoordPod* vf_43(HBCoordPod* out);   // slot 43, +0xAC
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
    virtual bool vf_54(HBCoordPod* where, int a);   // slot 54, +0xD8
    virtual void vt_0DC();
    virtual void vt_0E0();
    virtual void vt_0E4();
    virtual void vt_0E8();
    virtual void vt_0EC();
    virtual void vt_0F0();
    virtual void vt_0F4();
    virtual void vf_62();   // slot 62, +0xF8
    virtual void vt_0FC();
    virtual void vt_100();
    virtual void vf_65(void* what, int a, int b);   // slot 65, +0x104
    virtual void vt_108();
    virtual void vt_10C();
    virtual void vt_110();
    virtual void vf_69(HBCoordPod* where, int clip);   // slot 69, +0x114
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
    virtual void vf_109(HBCoordPod* where);   // slot 109, +0x1B4
    virtual void vt_1B8();
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
    virtual void vt_308();
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
    virtual bool vf_245(BA4House* newOwner, int announce);   // slot 245, +0x3D4

    char _pad_0004[0x10];   // +0x0004
    unsigned char unknown_14;   // +0x0014
    char _pad_0015[0x6C];   // +0x0015
    unsigned char unknown_81;   // +0x0081
    char _pad_0082[0x1A];   // +0x0082
    HBCoordPod Location;   // +0x009C
    char _pad_00A8[0x20];   // +0x00A8
    BA4AnimInfo* unknown_C8;   // +0x00C8
    char _pad_00CC[0x8];   // +0x00CC
    int unknown_D4;   // +0x00D4
    char _pad_00D8[0x24];   // +0x00D8
    int unknown_FC;   // +0x00FC
    char _pad_0100[0x78];   // +0x0100
    unsigned char unknown_178;   // +0x0178
    char _pad_0179[0x24];   // +0x0179
    unsigned char unknown_19D;   // +0x019D
    char _pad_019E[0x27A];   // +0x019E
    unsigned char unknown_418;   // +0x0418
    // FUNCTION: GAMEMD 0x425270 (read-only here)
    void FUN_00425270();
};
GG_STATIC_ASSERT(offsetof(BA4Object, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BA4Object, unknown_81) == 0x81);
GG_STATIC_ASSERT(offsetof(BA4Object, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(BA4Object, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(BA4Object, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(BA4Object, unknown_FC) == 0xFC);
GG_STATIC_ASSERT(offsetof(BA4Object, unknown_178) == 0x178);
GG_STATIC_ASSERT(offsetof(BA4Object, unknown_19D) == 0x19D);
GG_STATIC_ASSERT(offsetof(BA4Object, unknown_418) == 0x418);

// The type object at BuildingTypeClass +0xE58 (partial).
class BA4OverlayType
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
    virtual BA4Object* vf_35(BA4House* owner);   // slot 35, +0x8C

    char _pad_0004[0x290];   // +0x0004
    int unknown_294;   // +0x0294
};
GG_STATIC_ASSERT(offsetof(BA4OverlayType, unknown_294) == 0x294);

// The object at HouseClass +0x34 (partial).
struct BA4Country
{
    char _pad_0000[0xB8];   // +0x0000
    int unknown_B8;   // +0x00B8
    char _pad_00BC[0xEA];   // +0x00BC
    unsigned char unknown_1A6;   // +0x01A6
};
GG_STATIC_ASSERT(offsetof(BA4Country, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(BA4Country, unknown_1A6) == 0x1A6);

// The object at HouseClass +0x5700 (partial).
struct BA4HouseSub
{
    // FUNCTION: GAMEMD 0x42F260 (read-only here)
    void FUN_0042F260(BA4Building* b);
};

// The object at HouseClass +0x4368 (partial).
struct BA4HouseSub2
{
    // FUNCTION: GAMEMD 0x749020 (read-only here)
    void FUN_00749020(int a);
};

// HouseClass seen from a building (partial).
struct BA4House
{
    char _pad_0000[0x30];   // +0x0000
    int unknown_30;   // +0x0030
    BA4Country* unknown_34;   // +0x0034
    char _pad_0038[0x18];   // +0x0038
    BA4Vector<BA4Building*> unknown_50;   // +0x0050
    BA4Vector<BA4Building*> unknown_68;   // +0x0068
    BA4Vector<BA4Building*> unknown_80;   // +0x0080
    BA4Vector<BA4Building*> unknown_98;   // +0x0098
    BA4Vector<BA4Building*> unknown_B0;   // +0x00B0
    BA4Vector<BA4Building*> unknown_C8;   // +0x00C8
    BA4Vector<BA4Building*> unknown_E0;   // +0x00E0
    BA4Vector<BA4Building*> unknown_F8;   // +0x00F8
    BA4Vector<BA4Building*> unknown_110;   // +0x0110
    BA4Vector<BA4Building*> unknown_128;   // +0x0128
    BA4Vector<BA4Building*> unknown_140;   // +0x0140
    char _pad_0158[0xC];   // +0x0158
    int unknown_164;   // +0x0164
    int unknown_168;   // +0x0168
    char _pad_016C[0x90];   // +0x016C
    unsigned char unknown_1FC;   // +0x01FC
    char _pad_01FD[0xD7];   // +0x01FD
    int unknown_2D4;   // +0x02D4
    char _pad_02D8[0x4090];   // +0x02D8
    BA4HouseSub2 unknown_4368;   // +0x4368
    char _pad_4369[0x1023];   // +0x4369
    int unknown_538C;   // +0x538C
    char _pad_5390[0x150];   // +0x5390
    BA4Building* unknown_54E0;   // +0x54E0
    unsigned int unknown_54E4;   // +0x54E4
    char _pad_54E8[0x210];   // +0x54E8
    unsigned char unknown_56F8;   // +0x56F8
    char _pad_56F9[0x7];   // +0x56F9
    BA4HouseSub unknown_5700;   // +0x5700
    char _pad_5701[0x77];   // +0x5701
    unsigned char unknown_5778;   // +0x5778
    unsigned char unknown_5779;   // +0x5779
    // FUNCTION: GAMEMD 0x4FF980 (read-only here)
    void FUN_004FF980(BA4Building* b);
    // FUNCTION: GAMEMD 0x4FD150 (read-only here)
    void FUN_004FD150();
    // FUNCTION: GAMEMD 0x509130 (read-only here)
    void FUN_00509130();
    // FUNCTION: GAMEMD 0x509140 (read-only here)
    void FUN_00509140(int a, bool b, int c);
    // FUNCTION: GAMEMD 0x50A490 (read-only here)
    void FUN_0050A490(BA4Building* b);
    // FUNCTION: GAMEMD 0x4FCE80 (read-only here)
    void FUN_004FCE80(HBCell* cell, char flag);
    // FUNCTION: GAMEMD 0x4FFA50 (read-only here)
    void FUN_004FFA50(BA4Building* b);
    // FUNCTION: GAMEMD 0x50B1D0 (read-only here)
    void FUN_0050B1D0();
    // FUNCTION: GAMEMD 0x50B730 (read-only here)
    bool FUN_0050B730();
    // FUNCTION: GAMEMD 0x50BF60 (read-only here)
    void FUN_0050BF60();
    // FUNCTION: GAMEMD 0x50B6F0 (read-only here)
    bool FUN_0050B6F0();
    // FUNCTION: GAMEMD 0x4F9950 (read-only here)
    void FUN_004F9950(int a);
    // FUNCTION: GAMEMD 0x4FCE30 (read-only here)
    double FUN_004FCE30();
};
GG_STATIC_ASSERT(offsetof(BA4House, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_E0) == 0xE0);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_F8) == 0xF8);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_110) == 0x110);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_128) == 0x128);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_140) == 0x140);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_164) == 0x164);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_168) == 0x168);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_1FC) == 0x1FC);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_2D4) == 0x2D4);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_4368) == 0x4368);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_538C) == 0x538C);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_54E0) == 0x54E0);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_54E4) == 0x54E4);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_56F8) == 0x56F8);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_5700) == 0x5700);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_5778) == 0x5778);
GG_STATIC_ASSERT(offsetof(BA4House, unknown_5779) == 0x5779);

// BuildingTypeClass seen from a building (partial).
class BA4Type
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
    virtual HBCoordPod* vf_27(HBCoordPod* out, HBCoordPod* in);   // slot 27, +0x6C
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual void vt_08C();
    virtual HBCell* vf_36(int a);   // slot 36, +0x90
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual void vt_0A8();
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual int vf_46(BA4House* owner, int a);   // slot 46, +0xB8

    char _pad_0004[0x20];   // +0x0004
    char unknown_24;   // +0x0024
    char _pad_0025[0x93];   // +0x0025
    BA4VoxelDef unknown_B8v;   // +0x00B8
    BA4VoxelDef unknown_C0;   // +0x00C0
    char _pad_00C8[0x130];   // +0x00C8
    char unknown_1F8;   // +0x01F8
    char _pad_01F9[0x4B];   // +0x01F9
    BA4VoxelOpts unknown_244[4];   // +0x0244
    char _pad_0294[0x174];   // +0x0294
    int unknown_408;   // +0x0408
    char _pad_040C[0x1DC];   // +0x040C
    int unknown_5E8;   // +0x05E8
    unsigned char unknown_5EC;   // +0x05EC
    char _pad_05ED[0x47];   // +0x05ED
    int unknown_634;   // +0x0634
    char _pad_0638[0x44];   // +0x0638
    int unknown_67C;   // +0x067C
    char _pad_0680[0x9C];   // +0x0680
    int unknown_71C;   // +0x071C
    int unknown_720;   // +0x0720
    char _pad_0724[0x40];   // +0x0724
    int unknown_764;   // +0x0764
    HBCoordPod unknown_768;   // +0x0768
    char _pad_0774[0x55A];   // +0x0774
    bool unknown_CCE;   // +0x0CCE
    char _pad_0CCF[0x2];   // +0x0CCF
    unsigned char unknown_CD1;   // +0x0CD1
    char _pad_0CD2[0x3];   // +0x0CD2
    unsigned char unknown_CD5;   // +0x0CD5
    char _pad_0CD6[0x5B];   // +0x0CD6
    unsigned char unknown_D31;   // +0x0D31
    char _pad_0D32[0xC6];   // +0x0D32
    int unknown_DF8;   // +0x0DF8
    char _pad_0DFC[0x34];   // +0x0DFC
    int unknown_E30;   // +0x0E30
    int unknown_E34;   // +0x0E34
    int unknown_E38;   // +0x0E38
    int unknown_E3C;   // +0x0E3C
    int unknown_E40;   // +0x0E40
    char _pad_0E44[0x10];   // +0x0E44
    BA4OverlayType* unknown_E54;   // +0x0E54
    BA4OverlayType* unknown_E58;   // +0x0E58
    char _pad_0E5C[0x2C];   // +0x0E5C
    char unknown_E88;   // +0x0E88
    char _pad_0E89[0x2F];   // +0x0E89
    int unknown_EB8;   // +0x0EB8
    char _pad_0EBC[0x28];   // +0x0EBC
    int unknown_EE4;   // +0x0EE4
    char _pad_0EE8[0x18];   // +0x0EE8
    int unknown_F00;   // +0x0F00
    int unknown_F04;   // +0x0F04
    int unknown_F08;   // +0x0F08
    char _pad_0F0C[0x40];   // +0x0F0C
    BA4TypeEntry unknown_F4C[21];   // +0x0F4C
    int unknown_14E0;   // +0x14E0
    char _pad_14E4[0x28];   // +0x14E4
    int unknown_150C;   // +0x150C
    char _pad_1510[0x3B];   // +0x1510
    unsigned char unknown_154B;   // +0x154B
    char _pad_154C[0x6];   // +0x154C
    unsigned char unknown_1552;   // +0x1552
    char _pad_1553[0x1];   // +0x1553
    int unknown_1554;   // +0x1554
    int unknown_1558;   // +0x1558
    char _pad_155C[0x4];   // +0x155C
    int unknown_1560;   // +0x1560
    int unknown_1564;   // +0x1564
    int unknown_1568;   // +0x1568
    char _pad_156C[0x5];   // +0x156C
    unsigned char unknown_1571;   // +0x1571
    char _pad_1572[0x1];   // +0x1572
    unsigned char unknown_1573;   // +0x1573
    char _pad_1574[0x7];   // +0x1574
    unsigned char unknown_157B;   // +0x157B
    char _pad_157C[0x128];   // +0x157C
    unsigned char unknown_16A4;   // +0x16A4
    char _pad_16A5[0x2];   // +0x16A5
    unsigned char unknown_16A7;   // +0x16A7
    char _pad_16A8[0x1];   // +0x16A8
    unsigned char unknown_16A9;   // +0x16A9
    char _pad_16AA[0x1];   // +0x16AA
    unsigned char unknown_16AB;   // +0x16AB
    unsigned char unknown_16AC;   // +0x16AC
    unsigned char unknown_16AD;   // +0x16AD
    unsigned char unknown_16AE;   // +0x16AE
    unsigned char unknown_16AF;   // +0x16AF
    unsigned char unknown_16B0;   // +0x16B0
    char _pad_16B1[0x6];   // +0x16B1
    unsigned char unknown_16B7;   // +0x16B7
    unsigned char unknown_16B8;   // +0x16B8
    unsigned char unknown_16B9;   // +0x16B9
    char _pad_16BA[0x3];   // +0x16BA
    unsigned char unknown_16BD;   // +0x16BD
    unsigned char unknown_16BE;   // +0x16BE
    unsigned char unknown_16BF;   // +0x16BF
    char _pad_16C0[0x5];   // +0x16C0
    unsigned char unknown_16C5;   // +0x16C5
    unsigned char unknown_16C6;   // +0x16C6
    unsigned char unknown_16C7;   // +0x16C7
    unsigned char unknown_16C8;   // +0x16C8
    char _pad_16C9[0x1];   // +0x16C9
    unsigned char unknown_16CA;   // +0x16CA
    unsigned char unknown_16CB;   // +0x16CB
    unsigned char unknown_16CC;   // +0x16CC
    unsigned char unknown_16CD;   // +0x16CD
    char _pad_16CE[0x1E];   // +0x16CE
    int unknown_16EC;   // +0x16EC
    char _pad_16F0[0xC];   // +0x16F0
    int unknown_16FC;   // +0x16FC
    unsigned char unknown_1700;   // +0x1700
    char _pad_1701[0x6];   // +0x1701
    unsigned char unknown_1707;   // +0x1707
    char _pad_1708[0x4];   // +0x1708
    int unknown_170C;   // +0x170C
    char _pad_1710[0x53];   // +0x1710
    unsigned char unknown_1763;   // +0x1763
    char _pad_1764[0x1C];   // +0x1764
    int unknown_1780;   // +0x1780
    // FUNCTION: GAMEMD 0x45EC90 (read-only here)
    int FUN_0045EC90();
    // FUNCTION: GAMEMD 0x45ECA0 (read-only here)
    int FUN_0045ECA0(bool a);
    // FUNCTION: GAMEMD 0x712130 (read-only here)
    bool FUN_00712130();
};
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_B8v) == 0xB8);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_C0) == 0xC0);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1F8) == 0x1F8);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_244) == 0x244);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_408) == 0x408);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_5E8) == 0x5E8);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_5EC) == 0x5EC);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_634) == 0x634);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_67C) == 0x67C);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_71C) == 0x71C);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_720) == 0x720);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_764) == 0x764);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_768) == 0x768);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_CCE) == 0xCCE);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_CD1) == 0xCD1);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_CD5) == 0xCD5);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_D31) == 0xD31);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_DF8) == 0xDF8);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_E30) == 0xE30);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_E34) == 0xE34);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_E38) == 0xE38);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_E3C) == 0xE3C);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_E40) == 0xE40);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_E54) == 0xE54);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_E58) == 0xE58);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_E88) == 0xE88);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_EB8) == 0xEB8);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_EE4) == 0xEE4);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_F00) == 0xF00);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_F04) == 0xF04);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_F08) == 0xF08);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_F4C) == 0xF4C);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_14E0) == 0x14E0);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_150C) == 0x150C);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_154B) == 0x154B);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1552) == 0x1552);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1554) == 0x1554);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1558) == 0x1558);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1560) == 0x1560);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1564) == 0x1564);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1568) == 0x1568);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1571) == 0x1571);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1573) == 0x1573);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_157B) == 0x157B);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16A4) == 0x16A4);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16A7) == 0x16A7);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16A9) == 0x16A9);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16AB) == 0x16AB);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16AC) == 0x16AC);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16AD) == 0x16AD);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16AE) == 0x16AE);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16AF) == 0x16AF);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16B0) == 0x16B0);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16B7) == 0x16B7);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16B8) == 0x16B8);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16B9) == 0x16B9);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16BD) == 0x16BD);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16BE) == 0x16BE);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16BF) == 0x16BF);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16C5) == 0x16C5);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16C6) == 0x16C6);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16C7) == 0x16C7);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16C8) == 0x16C8);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16CA) == 0x16CA);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16CB) == 0x16CB);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16CC) == 0x16CC);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16CD) == 0x16CD);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16EC) == 0x16EC);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_16FC) == 0x16FC);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1700) == 0x1700);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1707) == 0x1707);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_170C) == 0x170C);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1763) == 0x1763);
GG_STATIC_ASSERT(offsetof(BA4Type, unknown_1780) == 0x1780);

// A map cell (partial).
struct BA4MapCell
{
    char _pad_0000[0x24];   // +0x0000
    HBCell unknown_24;   // +0x0024
    char _pad_0028[0x10];   // +0x0028
    int unknown_38;   // +0x0038
    char _pad_003C[0x8];   // +0x003C
    int unknown_44;   // +0x0044
    int unknown_48;   // +0x0048
    char _pad_004C[0x4];   // +0x004C
    int unknown_50;   // +0x0050
    char _pad_0054[0x98];   // +0x0054
    int unknown_EC;   // +0x00EC
    char _pad_00F0[0x1A];   // +0x00F0
    short unknown_10A;   // +0x010A
    char _pad_010C[0x12];   // +0x010C
    unsigned char unknown_11E;   // +0x011E
    unsigned char unknown_11F;   // +0x011F
    char _pad_0120[0x2];   // +0x0120
    unsigned char unknown_122;   // +0x0122
    char _pad_0123[0x9];   // +0x0123
    unsigned char unknown_12C;   // +0x012C
    char _pad_012D[0x13];   // +0x012D
    unsigned int unknown_140;   // +0x0140
    // FUNCTION: GAMEMD 0x480630 (read-only here)
    void FUN_00480630(char a);
    // FUNCTION: GAMEMD 0x480CB0 (read-only here)
    void FUN_00480CB0(int a);
    // FUNCTION: GAMEMD 0x47C620 (read-only here)
    bool FUN_0047C620(int a, BA4Type* type, BA4House* owner);
    // FUNCTION: GAMEMD 0x4852D0 (read-only here)
    void FUN_004852D0();
    // FUNCTION: GAMEMD 0x486E70 (read-only here)
    void FUN_00486E70();
    // FUNCTION: GAMEMD 0x47C520 (read-only here)
    BA4Building* FUN_0047C520();
    // FUNCTION: GAMEMD 0x487950 (read-only here)
    bool FUN_00487950();
};
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_EC) == 0xEC);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_10A) == 0x10A);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_11E) == 0x11E);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_11F) == 0x11F);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_122) == 0x122);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_12C) == 0x12C);
GG_STATIC_ASSERT(offsetof(BA4MapCell, unknown_140) == 0x140);

// The map object at 0x87F7E8 (partial).
struct BA4Map
{
    // FUNCTION: GAMEMD 0x5657A0 (read-only here) - the cell at a coordinate.
    BA4MapCell* FUN_005657A0(const HBCell& cell);
    // FUNCTION: GAMEMD 0x4F42F0 (read-only here)
    void FUN_004F42F0(int a);
    // FUNCTION: GAMEMD 0x5687F0 (read-only here)
    void FUN_005687F0(HBCell* cell, BA4Building* b);
    // FUNCTION: GAMEMD 0x5683C0 (read-only here)
    void FUN_005683C0(HBCell* cell, BA4Building* b);
    // FUNCTION: GAMEMD 0x5678E0 (read-only here)
    void FUN_005678E0(HBCoordPod* where, int a, BA4House* house, char b, char c, char d, char e, char f);
    // FUNCTION: GAMEMD 0x565730 (read-only here) - the cell at a world coordinate.
    BA4MapCell* FUN_00565730(HBCoordPod* where);
    // FUNCTION: GAMEMD 0x4AA290 (read-only here)
    BA4Building* FUN_004AA290(HBCell* cell, HBPoint2D* out);
    // FUNCTION: GAMEMD 0x4A8BF0 (read-only here)
    void FUN_004A8BF0(int a);
    // FUNCTION: GAMEMD 0x5865E0 (read-only here)
    bool FUN_005865E0(HBCoordPod* where);
};

// An entry of the table at *0xA83D84 (partial).
struct BA4MapInfo
{
    char _pad_0000[0x2A8];   // +0x0000
    unsigned char unknown_2A8;   // +0x02A8
};
GG_STATIC_ASSERT(offsetof(BA4MapInfo, unknown_2A8) == 0x2A8);

// An entry of the table at *0xA8EC1C (partial): a footprint of w by h cells.
struct BA4Placed
{
    char _pad_0000[0x298];   // +0x0000
    int unknown_298;   // +0x0298
    int unknown_29C;   // +0x029C
};
GG_STATIC_ASSERT(offsetof(BA4Placed, unknown_298) == 0x298);
GG_STATIC_ASSERT(offsetof(BA4Placed, unknown_29C) == 0x29C);

// The object at *0x887324 (partial).
struct BA4Screen
{
    // FUNCTION: GAMEMD 0x6D2790 (read-only here) - the object pointer in ECX is not read.
    void FUN_006D2790(HBRect r, char flag);
    // FUNCTION: GAMEMD 0x6D2360 (read-only here) - the object pointer in ECX is not read.
    HBCoordPod* FUN_006D2360(HBCoordPod* out, HBCoordPod* entry);
    // FUNCTION: GAMEMD 0x6D2140 (read-only here) - returned by value through a hidden pointer.
    HBCoordPod FUN_006D2140(const HBCoordPod& in);
};

// The game/session object at *0x8871E0 (partial): the building-type pointers at +0x86C..+0x87C.
struct BA4Game
{
    char _pad_0000[0x498];   // +0x0000
    BA4Type* unknown_498;   // +0x0498
    char _pad_049C[0x4];   // +0x049C
    int unknown_4A0;   // +0x04A0
    char _pad_04A4[0x3C8];   // +0x04A4
    BA4Type* unknown_86C;   // +0x086C
    BA4Type* unknown_870;   // +0x0870
    BA4Type* unknown_874;   // +0x0874
    BA4Type* unknown_878;   // +0x0878
    BA4Type* unknown_87C;   // +0x087C
    char _pad_0880[0x30];   // +0x0880
    BA4Type** unknown_8B0;   // +0x08B0
    char _pad_08B4[0x8];   // +0x08B4
    int unknown_8BC;   // +0x08BC
    char _pad_08C0[0xE40];   // +0x08C0
    double unknown_1700;   // +0x1700
    char _pad_1708[0x16C];   // +0x1708
    BA4Rgb unknown_1874[16];   // +0x1874
    int unknown_18A4;   // +0x18A4
    char _pad_18A8[0x8];   // +0x18A8
    int unknown_18B0;   // +0x18B0
};
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_498) == 0x498);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_4A0) == 0x4A0);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_86C) == 0x86C);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_870) == 0x870);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_874) == 0x874);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_878) == 0x878);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_87C) == 0x87C);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_8B0) == 0x8B0);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_8BC) == 0x8BC);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_1700) == 0x1700);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_1874) == 0x1874);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_18A4) == 0x18A4);
GG_STATIC_ASSERT(offsetof(BA4Game, unknown_18B0) == 0x18B0);

// The object at BuildingClass +0x294 (partial).
struct BA4Target
{
    char _pad_0000[0x50];   // +0x0000
    unsigned int unknown_50;   // +0x0050
};
GG_STATIC_ASSERT(offsetof(BA4Target, unknown_50) == 0x50);

// The object at BuildingClass +0x38 (partial).
struct BA4Op38
{
    // FUNCTION: GAMEMD 0x4389B0 (read-only here)
    void FUN_004389B0();
};

// The object at BuildingClass +0x524 (partial).
class BA4Factory
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
    virtual void vf_8(int a);   // slot 8, +0x20

    // FUNCTION: GAMEMD 0x4C9FF0 (read-only here)
    void FUN_004C9FF0();
};

// The object returned by slot 33 of a building (partial).
struct BA4Obj33
{
    char _pad_0000[0xC9F];   // +0x0000
    unsigned char unknown_C9F;   // +0x0C9F
};
GG_STATIC_ASSERT(offsetof(BA4Obj33, unknown_C9F) == 0xC9F);


// The object returned by 0x5B3A00 (partial).
struct BA4Difficulty
{
    char _pad_0000[0x18];   // +0x0000
    double unknown_18;   // +0x0018
};
GG_STATIC_ASSERT(offsetof(BA4Difficulty, unknown_18) == 0x18);

// The member at BuildingClass +0x350 (partial; size not known).
struct BA4Sub350
{
    // FUNCTION: GAMEMD 0x4A5110 (read-only here)
    bool FUN_004A5110();
    // FUNCTION: GAMEMD 0x4A5130 (read-only here)
    bool FUN_004A5130();
    // FUNCTION: GAMEMD 0x4A51B0 (read-only here)
    bool FUN_004A51B0();
    // FUNCTION: GAMEMD 0x4A51D0 (read-only here)
    bool FUN_004A51D0();
    // FUNCTION: GAMEMD 0x4A52F0 (read-only here)
    double FUN_004A52F0();
};

// The object at BuildingClass +0x600 (partial; allocated with the game operator new, 0xE8 bytes).
class BA4Spotlight
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
    virtual void vf_62();   // slot 62, +0xF8

    // FUNCTION: GAMEMD 0x435820 (read-only here)
    BA4Spotlight(BA4Building* owner);
    static void* operator new(unsigned int size);
};

// BuildingClass (partial).
class BA4Building
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
    virtual int vf_11();   // slot 11, +0x2C
    virtual void vt_030();
    virtual void vt_034();
    virtual int vf_14();   // slot 14, +0x38
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual HBCoordPod* vf_18(HBCoordPod* out);   // slot 18, +0x48
    virtual HBCoordPod* vf_19(HBCoordPod* out, int a);   // slot 19, +0x4C
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual int vf_26(int a, int b);   // slot 26, +0x68
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual bool vf_32();   // slot 32, +0x80
    virtual BA4Obj33* vf_33();   // slot 33, +0x84
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual HBCoordPod* vf_42(HBCoordPod* out, BA4Object* other);   // slot 42, +0xA8
    virtual HBCoordPod* vf_43(HBCoordPod* out);   // slot 43, +0xAC
    virtual HBCoordPod* vf_44(HBCoordPod* out, int a, HBCoordPod offset);   // slot 44, +0xB0
    virtual void vt_0B4();
    virtual void vt_0B8();
    virtual void vt_0BC();
    virtual void vt_0C0();
    virtual void vt_0C4();
    virtual void vt_0C8();
    virtual void vt_0CC();
    virtual void vt_0D0();
    virtual bool vf_53();   // slot 53, +0xD4
    virtual bool vf_54(HBCoordPod* where, int dir);   // slot 54, +0xD8
    virtual void vt_0DC();
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
    virtual void vf_69(HBCoordPod* where, int clip);   // slot 69, +0x114
    virtual void vt_118();
    virtual void vt_11C();
    virtual void vt_120();
    virtual bool vf_73(int mark);   // slot 73, +0x124
    virtual void vt_128();
    virtual HBRect* vf_75(HBRect* out);   // slot 75, +0x12C
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
    virtual bool vf_88();   // slot 88, +0x160
    virtual void vt_164();
    virtual int vf_90(int a);   // slot 90, +0x168
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
    virtual void vf_102(BA4House* house);   // slot 102, +0x198
    virtual void vt_19C();
    virtual void vf_104(int a);   // slot 104, +0x1A0
    virtual void vt_1A4();
    virtual void vt_1A8();
    virtual int vf_107(BA4MapCell* cell, int a, int b, int c, int d);   // slot 107, +0x1AC
    virtual void vt_1B0();
    virtual void vf_109(HBCoordPod* where);   // slot 109, +0x1B4
    virtual HBCell* vf_110(HBCell* out);   // slot 110, +0x1B8
    virtual BA4MapCell* vf_111();   // slot 111, +0x1BC
    virtual void vt_1C0();
    virtual void vt_1C4();
    virtual void vt_1C8();
    virtual void vt_1CC();
    virtual int vf_116();   // slot 116, +0x1D0
    virtual void vt_1D4();
    virtual void vt_1D8();
    virtual void vt_1DC();
    virtual void vt_1E0();
    virtual int vf_121();   // slot 121, +0x1E4
    virtual void vf_122(int a, int b);   // slot 122, +0x1E8
    virtual void vf_123();   // slot 123, +0x1EC
    virtual void vt_1F0();
    virtual void vt_1F4();
    virtual void vt_1F8();
    virtual void vt_1FC();
    virtual void vt_200();
    virtual void vt_204();
    virtual void vt_208();
    virtual void vt_20C();
    virtual int vf_132();   // slot 132, +0x210
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
    virtual void vf_157(int a);   // slot 157, +0x274
    virtual int vf_158(int what, BA4Object* target);   // slot 158, +0x278
    virtual void vt_27C();
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
    virtual int vf_185(BA4Object* t);   // slot 185, +0x2E4
    virtual void vt_2E8();
    virtual void vt_2EC();
    virtual void vt_2F0();
    virtual void vt_2F4();
    virtual void vt_2F8();
    virtual void vt_2FC();
    virtual void vt_300();
    virtual void vt_304();
    virtual void vt_308();
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
    virtual int vf_240(BA4Object* t, int a, int b);   // slot 240, +0x3C0
    virtual void vt_3C4();
    virtual void vf_242(int a);   // slot 242, +0x3C8
    virtual void vf_243(BA4Object* t, int a);   // slot 243, +0x3CC
    virtual void vt_3D0();
    virtual bool vf_245(BA4House* newOwner, bool announce);   // slot 245, +0x3D4
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
    virtual void vf_260(int a);   // slot 260, +0x410
    virtual void vf_261();   // slot 261, +0x414
    virtual void vf_262();   // slot 262, +0x418
    virtual void vt_41C();
    virtual void vt_420();
    virtual void vt_424();
    virtual void vt_428();
    virtual void vt_42C();
    virtual bool vf_268();   // slot 268, +0x430
    virtual void vt_434();
    virtual void vt_438();
    virtual void vt_43C();
    virtual void vt_440();
    virtual void vf_273(void* voxel, int frame, int flags, void* opts, int clip, HBPoint2D* where, BA4MatrixTemp* matrix, int facing, int color, int unused);   // slot 273, +0x444
    virtual void vt_448();
    virtual void vt_44C();
    virtual void vt_450();
    virtual void vt_454();
    virtual void vt_458();
    virtual void vf_279(int a);   // slot 279, +0x45C
    virtual void vt_460();
    virtual int vf_281(int a);   // slot 281, +0x464
    virtual void vt_468();
    virtual void vt_46C();
    virtual void vt_470();
    virtual void vt_474();
    virtual void vt_478();
    virtual void vt_47C();
    virtual void vt_480();
    virtual void vt_484();
    virtual void vf_290(int a, int b, int c, int d, int e);   // slot 290, +0x488
    virtual void vf_291(int a, int b, int c, int d);   // slot 291, +0x48C
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
    virtual void vf_311(int a);   // slot 311, +0x4DC
    virtual void vt_4E0();
    virtual void vf_313(HBPoint2D* pos, int clip);   // slot 313, +0x4E4
    virtual HBDir* vf_314(HBDir* out, BA4Object* t);   // slot 314, +0x4E8
    virtual void vt_4EC();
    virtual void vt_4F0();
    virtual void vt_4F4();
    virtual void vf_318(int a);   // slot 318, +0x4F8
    virtual void vt_4FC();
    virtual void vf_320(int a);   // slot 320, +0x500

    char _pad_0004[0x34];   // +0x0004
    BA4Op38* unknown_38;   // +0x0038
    char _pad_003C[0x44];   // +0x003C
    unsigned char unknown_80;   // +0x0080
    unsigned char unknown_81;   // +0x0081
    char _pad_0082[0xE];   // +0x0082
    unsigned char unknown_90;   // +0x0090
    char _pad_0091[0xB];   // +0x0091
    HBCoordPod Location;   // +0x009C
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
    char _pad_00EC[0xC];   // +0x00EC
    int unknown_F8;   // +0x00F8
    char _pad_00FC[0x4C];   // +0x00FC
    int unknown_148;   // +0x0148
    BA4House* unknown_14C;   // +0x014C
    char _pad_0150[0x74];   // +0x0150
    int unknown_1C4;   // +0x01C4
    char _pad_01C8[0x48];   // +0x01C8
    unsigned int unknown_210;   // +0x0210
    char _pad_0214[0x8];   // +0x0214
    BA4House* Owner;   // +0x021C
    char _pad_0220[0x74];   // +0x0220
    BA4Target* unknown_294;   // +0x0294
    char _pad_0298[0x1C];   // +0x0298
    BA4Object* Target;   // +0x02B4
    char _pad_02B8[0x34];   // +0x02B8
    int unknown_2EC;   // +0x02EC
    char _pad_02F0[0x4];   // +0x02F0
    int unknown_2F4;   // +0x02F4
    char _pad_02F8[0x14];   // +0x02F8
    BA4Tracker* unknown_30C;   // +0x030C
    char _pad_0310[0x40];   // +0x0310
    BA4Sub350 unknown_350;   // +0x0350
    char _pad_0351[0x1F];   // +0x0351
    BA4Facing unknown_370;   // +0x0370
    char _pad_0371[0x17];   // +0x0371
    BA4Facing Facing;   // +0x0388
    char _pad_0389[0x4A];   // +0x0389
    unsigned char unknown_3D3;   // +0x03D3
    char _pad_03D4[0x18];   // +0x03D4
    float unknown_3EC;   // +0x03EC
    int unknown_3F0;   // +0x03F0
    char _pad_03F4[0x18];   // +0x03F4
    float unknown_40C;   // +0x040C
    int unknown_410;   // +0x0410
    char _pad_0414[0x4];   // +0x0414
    unsigned char unknown_418;   // +0x0418
    char _pad_0419[0x1];   // +0x0419
    unsigned char unknown_41A;   // +0x041A
    unsigned char unknown_41B;   // +0x041B
    char _pad_041C[0x104];   // +0x041C
    BA4Type* Type;   // +0x0520
    BA4Factory* unknown_524;   // +0x0524
    char _pad_0528[0x1C];   // +0x0528
    int unknown_544;   // +0x0544
    char _pad_0548[0x14];   // +0x0548
    BA4Object* Anims[21];   // +0x055C
    char _pad_05B0[0x18];   // +0x05B0
    BA4Object* DamageFireAnims[8];   // +0x05C8
    BA4Type* Upgrades[4];   // +0x05E8
    char _pad_05F8[0x8];   // +0x05F8
    BA4Spotlight* Spotlight;   // +0x0600
    char _pad_0604[0x10];   // +0x0604
    BA4Light* unknown_614;   // +0x0614
    int unknown_618;   // +0x0618
    char _pad_061C[0x48];   // +0x061C
    int unknown_664;   // +0x0664
    char _pad_0668[0x63];   // +0x0668
    unsigned char unknown_6CB;   // +0x06CB
    unsigned char unknown_6CC;   // +0x06CC
    char _pad_06CD[0x3];   // +0x06CD
    HBCoordPod unknown_6D0;   // +0x06D0
    char _pad_06DC[0x1];   // +0x06DC
    unsigned char unknown_6DD;   // +0x06DD
    char _pad_06DE[0x5];   // +0x06DE
    unsigned char unknown_6E3;   // +0x06E3
    unsigned char unknown_6E4;   // +0x06E4
    char _pad_06E5[0x3];   // +0x06E5
    unsigned char unknown_6E8;   // +0x06E8
    char _pad_06E9[0x1];   // +0x06E9
    unsigned char unknown_6EA;   // +0x06EA
    unsigned char unknown_6EB;   // +0x06EB
    unsigned char unknown_6EC;   // +0x06EC
    char unknown_6ED;   // +0x06ED
    char _pad_06EE[0x12];   // +0x06EE
    short unknown_700;   // +0x0700
    char unknown_702;   // +0x0702
    char _pad_0703[0x1];   // +0x0703
    int unknown_704;   // +0x0704
    HBCoordPod unknown_708;   // +0x0708
    int unknown_714;   // +0x0714
    // FUNCTION: GAMEMD 0x452A40 (read-only here)
    void FUN_00452A40(int a);
    // FUNCTION: GAMEMD 0x4561F0 (read-only here)
    void FUN_004561F0();
    // FUNCTION: GAMEMD 0x6F6AC0 (read-only here) - the base-class removal.
    bool FUN_006F6AC0();
    // FUNCTION: GAMEMD 0x6F4A70 (read-only here) - the base-class mark.
    bool FUN_006F4A70(int mark);
    // FUNCTION: GAMEMD 0x70E360 (read-only here)
    int FUN_0070E360(int value);
    // FUNCTION: GAMEMD 0x6F6CA0 (read-only here) - the base-class unlimbo.
    bool FUN_006F6CA0(HBCoordPod* where, int dir);
    // FUNCTION: GAMEMD 0x457AA0 (read-only here)
    void FUN_00457AA0(int a, int b, int c);
    // FUNCTION: GAMEMD 0x455F10 (read-only here)
    void FUN_00455F10(int a);
    // FUNCTION: GAMEMD 0x452DC0 (read-only here)
    void FUN_00452DC0(int a);
    // FUNCTION: GAMEMD 0x4533A0 (read-only here)
    void FUN_004533A0(int a);
    // FUNCTION: GAMEMD 0x448070 (read-only here)
    void FUN_00448070(int a);
    // FUNCTION: GAMEMD 0x451400 (read-only here)
    void FUN_00451400();
    // FUNCTION: GAMEMD 0x65AD30 (read-only here)
    BA4Object* FUN_0065AD30(int index);
    // FUNCTION: GAMEMD 0x7014A0 (read-only here) - the base-class owner change.
    void FUN_007014A0(BA4House* newOwner, int a);
    // FUNCTION: GAMEMD 0x459F40 (read-only here)
    unsigned int FUN_00459F40();
    // FUNCTION: GAMEMD 0x451F60 (read-only here)
    void FUN_00451F60(int a, int b);
    // FUNCTION: GAMEMD 0x452170 (read-only here)
    void FUN_00452170(int a);
    // FUNCTION: GAMEMD 0x451690 (read-only here)
    void FUN_00451690();
    // FUNCTION: GAMEMD 0x705D60 (read-only here)
    void FUN_00705D60();
    // FUNCTION: GAMEMD 0x70DE70 (read-only here)
    void FUN_0070DE70(int a);
    // FUNCTION: GAMEMD 0x70E000 (read-only here)
    void FUN_0070E000(int a);
    // FUNCTION: GAMEMD 0x5F5C60 (read-only here)
    double FUN_005F5C60();
    // FUNCTION: GAMEMD 0x451E40 (read-only here)
    void FUN_00451E40(int a);
    // FUNCTION: GAMEMD 0x451890 (read-only here)
    void FUN_00451890(const char* text, int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x70FEC0 (read-only here)
    bool FUN_0070FEC0();
    // FUNCTION: GAMEMD 0x5B3A00 (read-only here)
    BA4Difficulty* FUN_005B3A00();
    // FUNCTION: GAMEMD 0x65AD40 (read-only here)
    BA4Object* FUN_0065AD40(int index);
    // FUNCTION: GAMEMD 0x705E00 (read-only here)
    void FUN_00705E00(int a, int b, HBPoint2D* pos, int clip, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n);
    // FUNCTION: GAMEMD 0x458810 (read-only here)
    BA4MatrixTemp* FUN_00458810(BA4MatrixTemp* out);
};
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_81) == 0x81);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(BA4Building, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_E8) == 0xE8);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_F8) == 0xF8);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_148) == 0x148);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_14C) == 0x14C);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_1C4) == 0x1C4);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_210) == 0x210);
GG_STATIC_ASSERT(offsetof(BA4Building, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_294) == 0x294);
GG_STATIC_ASSERT(offsetof(BA4Building, Target) == 0x2B4);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_2EC) == 0x2EC);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_2F4) == 0x2F4);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_30C) == 0x30C);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_350) == 0x350);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_370) == 0x370);
GG_STATIC_ASSERT(offsetof(BA4Building, Facing) == 0x388);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_3D3) == 0x3D3);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_3EC) == 0x3EC);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_3F0) == 0x3F0);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_40C) == 0x40C);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_410) == 0x410);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_418) == 0x418);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_41A) == 0x41A);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_41B) == 0x41B);
GG_STATIC_ASSERT(offsetof(BA4Building, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_524) == 0x524);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_544) == 0x544);
GG_STATIC_ASSERT(offsetof(BA4Building, Anims) == 0x55C);
GG_STATIC_ASSERT(offsetof(BA4Building, DamageFireAnims) == 0x5C8);
GG_STATIC_ASSERT(offsetof(BA4Building, Upgrades) == 0x5E8);
GG_STATIC_ASSERT(offsetof(BA4Building, Spotlight) == 0x600);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_614) == 0x614);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_618) == 0x618);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_664) == 0x664);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6CB) == 0x6CB);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6CC) == 0x6CC);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6D0) == 0x6D0);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6DD) == 0x6DD);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6E3) == 0x6E3);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6E4) == 0x6E4);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6E8) == 0x6E8);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6EA) == 0x6EA);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6EB) == 0x6EB);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6EC) == 0x6EC);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6ED) == 0x6ED);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_700) == 0x700);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_702) == 0x702);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_704) == 0x704);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_708) == 0x708);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_714) == 0x714);

// The map object, the session object, the global tables and flags touched by the bodies.
extern BA4Map DAT_0087F7E8;
extern BA4Game* DAT_008871E0;
extern BA4MapInfo** DAT_00A83D84;
extern BA4Screen* DAT_00887324;
extern int DAT_0089C818;
extern BA4House* DAT_00A83D4C;
extern unsigned char DAT_00880CF4;
extern int DAT_00A8E7AC;
extern unsigned char DAT_00A8E9A0;
extern BA4Placed** DAT_00A8EC1C;
extern BA4House** DAT_00A8022C;
#include "../../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;
extern int DAT_0089C848;
// LIBRARY: GAMEMD 0x7C8D20 (LIBRARY: _stricmp) / 0x7C91D0 (LIBRARY: strncpy)
extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" char* __cdecl strncpy(char* dest, const char* src, unsigned int count);
extern int DAT_00A8ED84;
extern int DAT_0088098C;
extern int DAT_00880990;
extern int DAT_00880994;
extern const double DAT_007E27F8;
extern const double DAT_007E1718;
// FUNCTION: GAMEMD 0x4CAC40 (read-only here)
double __cdecl FUN_004CAC40(double a);
// LIBRARY: GAMEMD 0x7C5F00 is the compiler's float-to-int helper (LIBRARY: _ftol)
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)

// The inline "is it this kind of object" cast of the original: the pointer or null, by the RTTI id of slot 11.
template <class T> inline T* BA4As(T* p, int id)
{
    return p ? (p->vf_11() == id ? p : 0) : 0;
}
extern int DAT_00B73550;
extern unsigned char DAT_00A8ED6B;
extern unsigned char DAT_00887418;
extern int DAT_00818CB0;
extern unsigned char DAT_00818CB4;
extern char DAT_00886FA0[];
extern const double DAT_007E4408;
// FUNCTION: GAMEMD 0x4BBC90 (read-only here) - the pixel-format code of the display.
int __cdecl FUN_004BBC90();
// FUNCTION: GAMEMD 0x6D20E0 (read-only here)
int FUN_006D20E0(int key);




// BEGIN canonical-layout asserts
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_38) == HB_BLD_UNKNOWN_38);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_80) == HB_BLD_NEEDS_REDRAW);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_81) == HB_BLD_IN_LIMBO);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_90) == HB_BLD_IS_ALIVE);
GG_STATIC_ASSERT(offsetof(BA4Building, Location) == HB_BLD_LOCATION);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_AC) == HB_BLD_CURRENT_MISSION);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_B4) == HB_BLD_UNKNOWN_B4);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_BC) == HB_BLD_STATUS);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_C4) == HB_BLD_UNKNOWN_C4);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_E8) == HB_BLD_UNKNOWN_E8);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_210) == HB_BLD_UNKNOWN_210);
GG_STATIC_ASSERT(offsetof(BA4Building, Owner) == HB_BLD_OWNER);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_294) == HB_BLD_UNKNOWN_294);
GG_STATIC_ASSERT(offsetof(BA4Building, Target) == HB_BLD_TARGET);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_30C) == HB_BLD_UNKNOWN_30C);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_350) == HB_BLD_STAGE);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_370) == HB_BLD_TURRET);
GG_STATIC_ASSERT(offsetof(BA4Building, Facing) == HB_BLD_FACING);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_3D3) == HB_BLD_UNKNOWN_3D3);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_418) == HB_BLD_UNKNOWN_418);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_41A) == HB_BLD_UNKNOWN_41A);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_41B) == HB_BLD_UNKNOWN_41B);
GG_STATIC_ASSERT(offsetof(BA4Building, Type) == HB_BLD_TYPE);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_524) == HB_BLD_FACTORY);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_544) == HB_BLD_UNKNOWN_544);
GG_STATIC_ASSERT(offsetof(BA4Building, Anims) == HB_BLD_ANIMS);
GG_STATIC_ASSERT(offsetof(BA4Building, DamageFireAnims) == HB_BLD_DAMAGE_FIRE_ANIMS);
GG_STATIC_ASSERT(offsetof(BA4Building, Spotlight) == HB_BLD_SPOTLIGHT);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_614) == HB_BLD_LIGHT_SOURCE);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_618) == HB_BLD_LASER_FENCE_FRAME);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6CB) == HB_BLD_SHOULD_REBUILD);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6CC) == HB_BLD_HAS_ENGINEER);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6D0) == HB_BLD_CASH_PRODUCTION_TIMER);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6DD) == HB_BLD_IS_READY_TO_COMMENCE);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6E3) == HB_BLD_HAS_BEEN_CAPTURED);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6E4) == HB_BLD_ACTUALLY_PLACED_ON_MAP);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6E8) == HB_BLD_IS_BEING_REPAIRED);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6EA) == HB_BLD_STUFF_ENABLED);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6EB) == HB_BLD_HAS_CLOAKING_DATA);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6EC) == HB_BLD_CLOAK_RADIUS);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_6ED) == HB_BLD_TRANSLUCENCY);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_700) == HB_BLD_UNKNOWN_700);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_702) == HB_BLD_UPGRADE_LEVEL);
GG_STATIC_ASSERT(offsetof(BA4Building, unknown_714) == HB_BLD_UNKNOWN_714);
GG_STATIC_ASSERT(offsetof(BA4Building, Upgrades) == HB_BLD_UPGRADES - 4);   // indexed by the upgrade level 1..3
// END canonical-layout asserts

#endif
