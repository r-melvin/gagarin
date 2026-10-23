// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | linear objdump decode of the retail bytes
//   Address-scoped views for the "building-a3" worker of the house/building module (BuildingClass bodies at
//   0x43E940, 0x4415F0, 0x443410, 0x445F80, 0x44B780, 0x44C980, 0x44D880). Every field and slot below is a
//   [reg+disp] operand or a call [reg+disp] read from those bodies in the retail gamemd.exe v1.001. The views are
//   NOT the canonical BuildingClass / BuildingTypeClass: they are sparse, BA3-prefixed and meant to be consolidated
//   later. Slots are retail primary-table indices (byte offset / 4, table 0x7E3EBC); the virtual
//   declarations named vt_XXX only position the slots actually used.
//   Maintained by hand since the module consolidation; shared types come from house_building_common_types.h.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A3_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A3_VIEWS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "house_building_layout.h"
#include "house_building_views.h"
#include "house_building_views.h"
#include "house_building_views.h"
#include "../../core/vector_class.h"

class BA3ObjView;
struct BA3Chain1View;
class BA3UnitTypeView;
class BA3TechnoView;
class BA3UnitView;
struct BA3LightView;
struct BA3SuperView;
struct BA3SpotView;
class BA3TypeView;
class BA3HouseView;
class BuildingA3View;
class ParticleSystemTypeClass;
class BA3AnimTypeView;

// LIBRARY: GAMEMD 0x7DC720 (read-only here) - raises a COM error (HRESULT on the stack).
void __stdcall FUN_007DC720(long hr);

// Eight bytes passed by value (a double of the original, copied dword-wise).
struct BA3Eight
{
    int Lo;   // +0x00
    int Hi;   // +0x04
};
GG_STATIC_ASSERT(sizeof(BA3Eight) == 8);

// A target reference (a 32-bit value and one tag byte; copied member-wise as five bytes, passed in eight).
#pragma pack(push, 1)
// Not merged: takes this cluster's BuildingClass view (see house_building_views.h).
struct BA3TargetRef
{
    int           Value;   // +0x00
    unsigned char Tag;     // +0x04
    // FUNCTION: GAMEMD 0x6E6AB0 (read-only here) - the constructor from a building / from an object.
    BA3TargetRef(BuildingA3View* b);
    BA3TargetRef(BA3ObjView* o);
};
#pragma pack(pop)
GG_STATIC_ASSERT(sizeof(BA3TargetRef) == 5);

// A queued network event (0x6F bytes; opaque here).
struct BA3Event
{
    unsigned char bytes[0x6F];
    BA3Event() {}
    // The same constructors written as real constructors (a temporary event).
    BA3Event(int owner, int kind, BA3TargetRef target);
    BA3Event(int owner, int kind, BA3TargetRef a, BA3TargetRef b);
    // FUNCTION: GAMEMD 0x4C65E0 (read-only here) - the event constructor, returns the event.
    BA3Event* FUN_004C65E0(int owner, int kind, BA3TargetRef target);
    // FUNCTION: GAMEMD 0x4C6780 (read-only here)
    BA3Event* FUN_004C6780(int owner, int kind, BA3TargetRef a, BA3TargetRef b);
};
GG_STATIC_ASSERT(sizeof(BA3Event) == 0x6F);

// The outgoing event ring buffer (0x80 events) with its timestamps.
struct BA3EventQueue
{
    int     Count;          // +0x00
    int     unknown_04;     // +0x04
    int     Head;           // +0x08
    BA3Event List[128];     // +0x0C
    unsigned long unknown_378C[128];   // +0x378C
};
GG_STATIC_ASSERT(offsetof(BA3EventQueue, Head) == 0x08);
GG_STATIC_ASSERT(offsetof(BA3EventQueue, List) == 0x0C);
GG_STATIC_ASSERT(offsetof(BA3EventQueue, unknown_378C) == 0x378C);

// Second link of the chain read at BuildingClass +0x38 (partial).
struct BA3Chain2View
{
    char _pad_0000[0x30];   // +0x0000
    int unknown_30;   // +0x0030
};
GG_STATIC_ASSERT(offsetof(BA3Chain2View, unknown_30) == 0x30);

// First link of the chain read at BuildingClass +0x38 (partial).
struct BA3Chain1View
{
    char _pad_0000[0x28];   // +0x0000
    BA3Chain2View* unknown_28;   // +0x0028
};
GG_STATIC_ASSERT(offsetof(BA3Chain1View, unknown_28) == 0x28);

// The facing member at BuildingClass +0x370 (partial).
struct BA3FacingView
{
    // FUNCTION: GAMEMD 0x4C93D0 (read-only here)
    HBDir FUN_004C93D0();
    // FUNCTION: GAMEMD 0x4C9220 (read-only here)
    void FUN_004C9220(HBDir* dir);
};

// Weapon type (first member of a weapon slot): only the flag byte tested.
struct BA3WeaponTypeView
{
    char _pad_0000[0xA0];   // +0x0000
    int unknown_A0;   // +0x00A0
    int unknown_A4;   // +0x00A4
    char _pad_00A8[0x4];   // +0x00A8
    int unknown_AC;   // +0x00AC
    char _pad_00B0[0xC];   // +0x00B0
    DynamicVectorClass<int> unknown_BC;   // +0x00BC
    char _pad_00D4[0x5B];   // +0x00D4
    unsigned char unknown_12F;   // +0x012F
    char _pad_0130[0x19];   // +0x0130
    unsigned char unknown_149;   // +0x0149
};
GG_STATIC_ASSERT(offsetof(BA3WeaponTypeView, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(BA3WeaponTypeView, unknown_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(BA3WeaponTypeView, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(BA3WeaponTypeView, unknown_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(BA3WeaponTypeView, unknown_12F) == 0x12F);
GG_STATIC_ASSERT(offsetof(BA3WeaponTypeView, unknown_149) == 0x149);

// What BuildingClass slot 254 returns: weapon type pointer and the muzzle height at +0xC.
struct BA3WeaponSlotView
{
    BA3WeaponTypeView* First;   // +0x0000
    char _pad_0004[0x8];   // +0x0004
    int unknown_0C;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(BA3WeaponSlotView, First) == 0x0);
GG_STATIC_ASSERT(offsetof(BA3WeaponSlotView, unknown_0C) == 0xC);

// A target / object seen through a slot (partial).
class BA3ObjView
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
    virtual HBCoord vf_18();   // slot 18, +0x48

    char _pad_0004[0x13C];   // +0x0004
    unsigned int unknown_140;   // +0x0140
    char _pad_0144[0x16C];   // +0x0144
    unsigned char unknown_2B0;   // +0x02B0
    char _pad_02B1[0x3];   // +0x02B1
    int unknown_2B4;   // +0x02B4
};
GG_STATIC_ASSERT(offsetof(BA3ObjView, unknown_140) == 0x140);
GG_STATIC_ASSERT(offsetof(BA3ObjView, unknown_2B0) == 0x2B0);
GG_STATIC_ASSERT(offsetof(BA3ObjView, unknown_2B4) == 0x2B4);

// An animation object (AnimClass, name YRpp-cross-checked; 0x1C8 bytes by the allocation in 0x4415F0; partial).
class BA3AnimView
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

    char _pad_0004[0xD0];   // +0x0004
    int unknown_D4;   // +0x00D4
    char _pad_00D8[0x4];   // +0x00D8
    char unknown_DC[0x20];   // +0x00DC
    char _pad_00FC[0x4];   // +0x00FC
    int unknown_100;   // +0x0100
    char _pad_0104[0x99];   // +0x0104
    unsigned char unknown_19D;   // +0x019D
    char _pad_019E[0x2A];   // +0x019E
    // FUNCTION: GAMEMD 0x424C90 (read-only here)
    void FUN_00424C90(void* other);
    // FUNCTION: GAMEMD 0x424CA0 (read-only here)
    void FUN_00424CA0(BA3HouseView* owner);
};
GG_STATIC_ASSERT(offsetof(BA3AnimView, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(BA3AnimView, unknown_DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(BA3AnimView, unknown_100) == 0x100);
GG_STATIC_ASSERT(offsetof(BA3AnimView, unknown_19D) == 0x19D);
GG_STATIC_ASSERT(sizeof(BA3AnimView) == 0x1C8);

// Raw storage for one animation object; the constructor body is the member below.
struct BA3AnimMem
{
    char _pad_0000[0x1C8];   // +0x0000
    // FUNCTION: GAMEMD 0x421EA0 (read-only here) - the animation constructor, returns the object.
    BA3AnimView* FUN_00421EA0(const BA3AnimTypeView* type, HBCoord* where, int delay, int loops, int flags, int a, int b);
};
GG_STATIC_ASSERT(sizeof(BA3AnimMem) == 0x1C8);

// Raw storage for one particle system object (0x100 bytes by the allocation in 0x4415F0).
struct BA3ParticleMem
{
    char _pad_0000[0x100];   // +0x0000
    // FUNCTION: GAMEMD 0x62DC50 (read-only here) - the particle system constructor, returns the object.
    struct BA3ParticleView* FUN_0062DC50(const ParticleSystemTypeClass* type, HBCoord* where, int a, BuildingA3View* owner, HBCoord* b, int c);
};
GG_STATIC_ASSERT(sizeof(BA3ParticleMem) == 0x100);

// A particle system type (ParticleSystemTypeClass, name YRpp-cross-checked; one flag byte read).
struct BA3ParticleTypeView
{
    char _pad_0000[0x2B4];   // +0x0000
    int unknown_2B4;   // +0x02B4
};
GG_STATIC_ASSERT(offsetof(BA3ParticleTypeView, unknown_2B4) == 0x2B4);

// A particle system object (opaque).
struct BA3ParticleView
{
};

// A map cell (partial).
struct BA3MapCellView
{
    char _pad_0000[0x44];   // +0x0000
    int unknown_44;   // +0x0044
    // FUNCTION: GAMEMD 0x487190 (read-only here)
    void FUN_00487190(int a, int b);
};
GG_STATIC_ASSERT(offsetof(BA3MapCellView, unknown_44) == 0x44);

// The map object (partial).
struct BA3MapView
{
    // FUNCTION: GAMEMD 0x578080 (read-only here)
    void FUN_00578080(const HBCoord& where);
    // FUNCTION: GAMEMD 0x4F42F0 (read-only here)
    void FUN_004F42F0(int arg);
    // FUNCTION: GAMEMD 0x565730 (read-only here)
    BA3MapCellView* FUN_00565730(HBCoord* where);
    // FUNCTION: GAMEMD 0x6A60E0 (read-only here)
    void FUN_006A60E0(int arg);
    // FUNCTION: GAMEMD 0x567DA0 (read-only here)
    void FUN_00567DA0(HBCoord* where, int a, int b, int c);
    // FUNCTION: GAMEMD 0x56D230 (read-only here)
    int FUN_0056D230(HBCell* out, int zone, char flag);
    // FUNCTION: GAMEMD 0x56DC20 (read-only here) - the cell search; 15 stack arguments.
    HBCell* FUN_0056DC20(HBCoord* start, HBCell* cell, int a, int b, int c, char d, int e, int f, char g, char h, char i, char j, HBCell* k, char l, char m);
    // FUNCTION: GAMEMD 0x5657A0 (read-only here)
    BA3ObjView* FUN_005657A0(HBCell* cell);
    // FUNCTION: GAMEMD 0x4ACA10 (read-only here)
    HBCoord* FUN_004ACA10(HBCoord* out, HBCoord* in, char flag);
};

// Object behind the global at 0x8871E0 (partial).
struct BA3RulesView
{
    char _pad_0000[0x98];   // +0x0000
    BA3AnimTypeView* unknown_98;   // +0x0098
    char _pad_009C[0x1D8];   // +0x009C
    int unknown_274;   // +0x0274
    char _pad_0278[0x350];   // +0x0278
    int unknown_5C8;   // +0x05C8
    char _pad_05CC[0x11C];   // +0x05CC
    int unknown_6E8;   // +0x06E8
    char _pad_06EC[0x2C];   // +0x06EC
    int unknown_718;   // +0x0718
    char _pad_071C[0x440];   // +0x071C
    BA3UnitTypeView** unknown_B5C;   // +0x0B5C
    char _pad_0B60[0x448];   // +0x0B60
    int unknown_FA8;   // +0x0FA8
    char _pad_0FAC[0x55C];   // +0x0FAC
    double unknown_1508;   // +0x1508
    char _pad_1510[0x1A8];   // +0x1510
    int unknown_16B8;   // +0x16B8
    char _pad_16BC[0x2C];   // +0x16BC
    double unknown_16E8;   // +0x16E8
    double unknown_16F0;   // +0x16F0
    double unknown_16F8;   // +0x16F8
    double unknown_1700;   // +0x1700
    char _pad_1708[0xE0];   // +0x1708
    unsigned char unknown_17E8;   // +0x17E8
};
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_274) == 0x274);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_5C8) == 0x5C8);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_6E8) == 0x6E8);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_718) == 0x718);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_B5C) == 0xB5C);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_FA8) == 0xFA8);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_1508) == 0x1508);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_16B8) == 0x16B8);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_16E8) == 0x16E8);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_16F0) == 0x16F0);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_16F8) == 0x16F8);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_1700) == 0x1700);
GG_STATIC_ASSERT(offsetof(BA3RulesView, unknown_17E8) == 0x17E8);

// A float accumulator member (partial).
struct BA3FloatView
{
    // FUNCTION: GAMEMD 0x6C9650 (read-only here)
    float FUN_006C9650();
    // FUNCTION: GAMEMD 0x6C9820 (read-only here)
    int FUN_006C9820();
    // FUNCTION: GAMEMD 0x6C96B0 (read-only here)
    float FUN_006C96B0(float value, int index);
};

// Sub-object at the owning house +0x24: COM style slots taking the object pointer on the stack.
class BA3IntervalView
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual int __stdcall vf_6();   // slot 6, +0x18

};

// The owning house, BuildingClass +0x21C (partial; the HouseClass name is YRpp-cross-checked).
struct BA3HouseView
{
    char _pad_0000[0x24];   // +0x0000
    BA3IntervalView unknown_24;   // +0x0024
    char _pad_0028[0x44];   // +0x0028
    BuildingA3View** unknown_6C;   // +0x006C
    char _pad_0070[0x8];   // +0x0070
    int unknown_78;   // +0x0078
    char _pad_007C[0xE8];   // +0x007C
    int unknown_164;   // +0x0164
    int unknown_168;   // +0x0168
    char _pad_016C[0x80];   // +0x016C
    unsigned char unknown_1EC;   // +0x01EC
    char _pad_01ED[0xF];   // +0x01ED
    unsigned char unknown_1FC;   // +0x01FC
    char _pad_01FD[0x5B];   // +0x01FD
    BA3SuperView** unknown_258;   // +0x0258
    char _pad_025C[0x8];   // +0x025C
    int unknown_264;   // +0x0264
    char _pad_0268[0x6C];   // +0x0268
    int unknown_2D4;   // +0x02D4
    char _pad_02D8[0x1C];   // +0x02D8
    int unknown_2F4;   // +0x02F4
    char _pad_02F8[0x4];   // +0x02F8
    BA3FloatView unknown_2FC;   // +0x02FC
    char _pad_02FD[0x508F];   // +0x02FD
    int unknown_538C;   // +0x538C
    char _pad_5390[0x154];   // +0x5390
    unsigned int unknown_54E4;   // +0x54E4
    char _pad_54E8[0x68];   // +0x54E8
    HBListView unknown_5550;   // +0x5550
    char _pad_5551[0x227];   // +0x5551
    unsigned char unknown_5778;   // +0x5778
    unsigned char unknown_5779;   // +0x5779
    char _pad_577A[0x6];   // +0x577A
    HBCell unknown_5780;   // +0x5780
    HBCell unknown_5784;   // +0x5784
    // FUNCTION: GAMEMD 0x50B6F0 (read-only here)
    bool FUN_0050B6F0();
    // FUNCTION: GAMEMD 0x50B730 (read-only here)
    bool FUN_0050B730();
    // FUNCTION: GAMEMD 0x4F9A50 (read-only here)
    bool FUN_004F9A50(BA3HouseView* other);
    // FUNCTION: GAMEMD 0x4F9950 (read-only here)
    void FUN_004F9950(int value);
    // FUNCTION: GAMEMD 0x53A130 (read-only here)
    bool FUN_0053A130();
};
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_164) == 0x164);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_168) == 0x168);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_1EC) == 0x1EC);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_1FC) == 0x1FC);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_258) == 0x258);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_264) == 0x264);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_2D4) == 0x2D4);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_2F4) == 0x2F4);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_538C) == 0x538C);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_54E4) == 0x54E4);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_5550) == 0x5550);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_5778) == 0x5778);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_5779) == 0x5779);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_5780) == 0x5780);
GG_STATIC_ASSERT(offsetof(BA3HouseView, unknown_5784) == 0x5784);

// Sub-object at BuildingTypeClass +0x510 (only a field at +0x10 is read).
struct BA3TypeSubView
{
    char _pad_0000[0x10];   // +0x0000
    int unknown_10;   // +0x0010
};
GG_STATIC_ASSERT(offsetof(BA3TypeSubView, unknown_10) == 0x10);

// A frame timer: start frame, one word the setter leaves alone, duration.
// Not merged: cluster timers differ in constructors and inline bodies (see house_building_views.h).
struct BA3Timer
{
    int Start;   // +0x0000
    int unknown_04;   // +0x0004
    int Delay;   // +0x0008
    // FUNCTION: GAMEMD 0x426630 (read-only here) - non-zero while the timer is still running.
    int FUN_00426630();
};
GG_STATIC_ASSERT(offsetof(BA3Timer, Start) == 0x0);
GG_STATIC_ASSERT(offsetof(BA3Timer, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(BA3Timer, Delay) == 0x8);

// Type of a super weapon (partial).
struct BA3SuperTypeView
{
    char _pad_0000[0xB4];   // +0x0000
    int unknown_B4;   // +0x00B4
};
GG_STATIC_ASSERT(offsetof(BA3SuperTypeView, unknown_B4) == 0xB4);

// A super weapon object of the owning house (partial).
struct BA3SuperView
{
    char _pad_0000[0x28];   // +0x0000
    BA3SuperTypeView* unknown_28;   // +0x0028
    char _pad_002C[0x4];   // +0x002C
    int unknown_30;   // +0x0030
    char _pad_0034[0x4];   // +0x0034
    int unknown_38;   // +0x0038
};
GG_STATIC_ASSERT(offsetof(BA3SuperView, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(BA3SuperView, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(BA3SuperView, unknown_38) == 0x38);

// A light / spotlight object (opaque); one method is reached.
struct BA3LightView
{
    // FUNCTION: GAMEMD 0x554A60 (read-only here)
    void FUN_00554A60(char arg);
};

// Raw storage for one light object (0x4C bytes by the allocation in 0x445F80).
struct BA3LightMem
{
    char _pad_0000[0x4C];   // +0x0000
    // FUNCTION: GAMEMD 0x554760 (read-only here) - the constructor, returns the object.
    BA3LightView* FUN_00554760(HBCoord where, int a, int b, int c, int d, int e);
};
GG_STATIC_ASSERT(sizeof(BA3LightMem) == 0x4C);

// A unit type (the free unit of the building type; partial).
class BA3UnitTypeView
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
    virtual int vf_43();   // slot 43, +0xAC
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual int vf_46(BA3HouseView* owner, int flag);   // slot 46, +0xB8

    char _pad_0004[0x5B0];   // +0x0004
    int unknown_5B4;   // +0x05B4
};
GG_STATIC_ASSERT(offsetof(BA3UnitTypeView, unknown_5B4) == 0x5B4);

// A unit object created for the building (partial).
class BA3UnitView
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
    virtual bool vf_54(const HBCoord& where, int arg);   // slot 54, +0xD8
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
    virtual void vf_115(int arg);   // slot 115, +0x1CC
    virtual void vt_1D0();
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
    virtual int vf_158(int a, void* o);   // slot 158, +0x278

    char _pad_0004[0x6C0];   // +0x0004
    BA3UnitTypeView* unknown_6C4;   // +0x06C4
    // FUNCTION: GAMEMD 0x417FD0 (read-only here)
    int FUN_00417FD0();
};
GG_STATIC_ASSERT(offsetof(BA3UnitView, unknown_6C4) == 0x6C4);

// Raw storage for one unit object (0x8E8 bytes by the allocation in 0x445F80).
struct BA3UnitMem
{
    char _pad_0000[0x8E8];   // +0x0000
    // FUNCTION: GAMEMD 0x7353C0 (read-only here) - the constructor, returns the object.
    BA3UnitView* FUN_007353C0(BA3UnitTypeView* type, BA3HouseView* owner);
};
GG_STATIC_ASSERT(sizeof(BA3UnitMem) == 0x8E8);

// Raw storage for one spawned object (0x6D8 bytes by the allocation in 0x445F80).
struct BA3SpawnMem
{
    char _pad_0000[0x6D8];   // +0x0000
    // FUNCTION: GAMEMD 0x413D20 (read-only here) - the constructor, returns the object.
    BA3UnitView* FUN_00413D20(BA3UnitTypeView* type, BA3HouseView* owner);
};
GG_STATIC_ASSERT(sizeof(BA3SpawnMem) == 0x6D8);

// Object at BuildingClass +0x580 (partial).
struct BA3SpotView
{
    char _pad_0000[0xAC];   // +0x0000
    int unknown_AC;   // +0x00AC
    char _pad_00B0[0x14];   // +0x00B0
    int unknown_C4;   // +0x00C4
};
GG_STATIC_ASSERT(offsetof(BA3SpotView, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(BA3SpotView, unknown_C4) == 0xC4);

// Member of BuildingClass at +0x114 (partial).
struct BA3Obj114View
{
    int Count;   // +0x0000
    // FUNCTION: GAMEMD 0x473430 (read-only here)
    BA3TechnoView* FUN_00473430();
    // FUNCTION: GAMEMD 0x4733A0 (read-only here)
    void FUN_004733A0(BA3TechnoView* item);
};
GG_STATIC_ASSERT(offsetof(BA3Obj114View, Count) == 0x0);

// A COM style interface of a techno (stdcall slots; only the used ones).
class BA3ComUnk
{
public:
    virtual long __stdcall QueryInterface(const void* iid, void** out);   // slot 0, +0x0
    virtual unsigned long __stdcall AddRef();   // slot 1, +0x4
    virtual unsigned long __stdcall Release();   // slot 2, +0x8
    virtual long __stdcall vf_3(void* arg);   // slot 3, +0xC
    virtual bool __stdcall vf_4();   // slot 4, +0x10
    virtual void vt_014();
    virtual void vt_018();
    virtual bool __stdcall vf_7();   // slot 7, +0x1C
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
    virtual bool __stdcall vf_22();   // slot 22, +0x58
    virtual void __stdcall vf_23();   // slot 23, +0x5C
    virtual bool __stdcall vf_24();   // slot 24, +0x60
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual long __stdcall vf_28(int arg, HBCoord where);   // slot 28, +0x70

};

// The piggy-back interface of a locomotor (COM style slots, this on the stack).
class BA3PiggyIface
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual unsigned long __stdcall Release();   // slot 2, +0x8
    virtual void vt_00C();
    virtual void __stdcall vf_4(struct BA3ComPtr* loco);   // slot 4, +0x10
    virtual void vt_014();
    virtual void vt_018();
    virtual bool __stdcall vf_7();   // slot 7, +0x1C

};

// A smart pointer to a COM interface: dereferencing a null pointer raises E_POINTER.
struct BA3ComPtr
{
    BA3ComUnk* p;   // +0x0000
    BA3ComUnk* operator->() const { if (!p) FUN_007DC720(0x80004003); return p; }
    // FUNCTION: GAMEMD 0x45AEA0 (read-only here) - the converting constructor (QueryInterface).
    long FUN_0045AEA0(const BA3ComPtr* other);
    // FUNCTION: GAMEMD 0x45AF20 (read-only here) - the converting constructor for the piggy-back interface.
    long FUN_0045AF20(const BA3ComPtr* other);
    // FUNCTION: GAMEMD 0x41C250 (read-only here) - CreateInstance.
    long FUN_0041C250(const void* clsid, void* outer, unsigned long context);
    // FUNCTION: GAMEMD 0x45A050 (read-only here) - operator-> (out of line).
    BA3ComUnk* FUN_0045A050();
    // FUNCTION: GAMEMD 0x45A160 / 0x45A170 (read-only here) - _Release (out of line).
    void FUN_0045A160();
    // FUNCTION: GAMEMD 0x45A170 (read-only here)
    void FUN_0045A170();
};
GG_STATIC_ASSERT(offsetof(BA3ComPtr, p) == 0x0);

// The flash member of a techno at +0x150 (partial).
struct BA3FlashView
{
    // FUNCTION: GAMEMD 0x74FFF0 (read-only here)
    bool FUN_0074FFF0();
    // FUNCTION: GAMEMD 0x750090 (read-only here)
    void FUN_00750090(char arg);
    // FUNCTION: GAMEMD 0x7500B0 (read-only here)
    void FUN_007500B0(char arg);
};

// Type of a techno (partial).
struct BA3PassTypeView
{
    char _pad_0000[0xA0];   // +0x0000
    int unknown_A0;   // +0x00A0
    char _pad_00A4[0x5D8];   // +0x00A4
    int unknown_67C;   // +0x067C
    char _pad_0680[0x6A4];   // +0x0680
    unsigned char unknown_D24;   // +0x0D24
};
GG_STATIC_ASSERT(offsetof(BA3PassTypeView, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(BA3PassTypeView, unknown_67C) == 0x67C);
GG_STATIC_ASSERT(offsetof(BA3PassTypeView, unknown_D24) == 0xD24);

// A techno object seen from a building (passenger / target; partial).
class BA3TechnoView
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
    virtual HBCoord vf_18();   // slot 18, +0x48
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
    virtual BA3PassTypeView* vf_33();   // slot 33, +0x84
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
    virtual bool vf_54(const HBCoord& where, int facing);   // slot 54, +0xD8
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
    virtual void vf_71();   // slot 71, +0x11C
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
    virtual void vf_91(int* target, int a, int b, int c, int d, int e, int f);   // slot 91, +0x16C
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
    virtual void vt_198();
    virtual void vt_19C();
    virtual void vf_104(int arg);   // slot 104, +0x1A0
    virtual void vt_1A4();
    virtual void vt_1A8();
    virtual int vf_107(void* cell, int dir, int a, int b, int c);   // slot 107, +0x1AC
    virtual void vt_1B0();
    virtual void vt_1B4();
    virtual HBCell* vf_110(HBCell* out);   // slot 110, +0x1B8
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
    virtual void vf_205();   // slot 205, +0x334
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
    virtual void vt_3FC();
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
    virtual void vf_288(void* target, int arg);   // slot 288, +0x480
    virtual void vf_289(bool flag, int unused);   // slot 289, +0x484
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
    virtual void vt_4E8();
    virtual void vt_4EC();
    virtual void vt_4F0();
    virtual void vt_4F4();
    virtual void vt_4F8();
    virtual void vt_4FC();
    virtual void vt_500();
    virtual void vt_504();
    virtual void vt_508();
    virtual void vt_50C();
    virtual void vt_510();
    virtual void vt_514();
    virtual void vt_518();
    virtual void vt_51C();
    virtual void vt_520();
    virtual void vt_524();
    virtual void vt_528();
    virtual void vt_52C();
    virtual void vt_530();
    virtual void vt_534();
    virtual void vt_538();
    virtual void vt_53C();
    virtual void vt_540();
    virtual void vf_337(double value);   // slot 337, +0x544

    char _pad_0004[0x10];   // +0x0004
    unsigned char unknown_14;   // +0x0014
    char _pad_0015[0x57];   // +0x0015
    int unknown_6C;   // +0x006C
    char _pad_0070[0xE0];   // +0x0070
    BA3FlashView unknown_150;   // +0x0150
    char _pad_0151[0xC7];   // +0x0151
    BA3ObjView* unknown_218;   // +0x0218
    BA3HouseView* unknown_21C;   // +0x021C
    char _pad_0220[0x1B0];   // +0x0220
    unsigned char unknown_3D0;   // +0x03D0
    char _pad_03D1[0x67];   // +0x03D1
    unsigned char unknown_438;   // +0x0438
    unsigned char unknown_439;   // +0x0439
    char _pad_043A[0xC6];   // +0x043A
    int unknown_500;   // +0x0500
    char _pad_0504[0xA0];   // +0x0504
    int unknown_5A4;   // +0x05A4
    char _pad_05A8[0xCC];   // +0x05A8
    BA3ComPtr unknown_674;   // +0x0674
    char _pad_0678[0x17];   // +0x0678
    unsigned char unknown_68F;   // +0x068F
    // FUNCTION: GAMEMD 0x70C610 (read-only here)
    void FUN_0070C610(int arg);
    // FUNCTION: GAMEMD 0x4DF0D0 (read-only here)
    void FUN_004DF0D0();
    // FUNCTION: GAMEMD 0x5F5C60 (read-only here) - the health ratio.
    double FUN_005F5C60();
};
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_150) == 0x150);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_218) == 0x218);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_3D0) == 0x3D0);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_438) == 0x438);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_439) == 0x439);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_500) == 0x500);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_5A4) == 0x5A4);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_674) == 0x674);
GG_STATIC_ASSERT(offsetof(BA3TechnoView, unknown_68F) == 0x68F);

// Launch parameters of a super weapon (partial).
struct BA3LaunchInfoView
{
    char _pad_0000[0xA0];   // +0x0000
    int unknown_A0;   // +0x00A0
    int unknown_A4;   // +0x00A4
    char _pad_00A8[0x4];   // +0x00A8
    int unknown_AC;   // +0x00AC
};
GG_STATIC_ASSERT(offsetof(BA3LaunchInfoView, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(BA3LaunchInfoView, unknown_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(BA3LaunchInfoView, unknown_AC) == 0xAC);

// Entry of the table at 0xA8E334 (partial).
struct BA3LaunchHolderView
{
    char _pad_0000[0x9C];   // +0x0000
    BA3LaunchInfoView* unknown_9C;   // +0x009C
};
GG_STATIC_ASSERT(offsetof(BA3LaunchHolderView, unknown_9C) == 0x9C);

// The missile object created for the launch (partial).
class BA3MissileView
{
public:
    virtual void vt_000();
    virtual void vt_004();
    virtual void __stdcall vf_2();   // slot 2, +0x8
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vf_8(int flag);   // slot 8, +0x20
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
    virtual void vf_53();   // slot 53, +0xD4
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
    virtual bool vf_124(HBCoord* from, double* velocity);   // slot 124, +0x1F0

    // FUNCTION: GAMEMD 0x46B260 (read-only here)
    void FUN_0046B260(BA3LaunchInfoView* info);
};

// Object reached from the building type at +0xED4 (partial): a cell offset at +0x28.
struct BA3OffsetHolderView
{
    char _pad_0000[0x28];   // +0x0000
    HBCell unknown_28;   // +0x0028
};
GG_STATIC_ASSERT(offsetof(BA3OffsetHolderView, unknown_28) == 0x28);

// The object at BuildingClass +0x520 (BuildingTypeClass, name YRpp-cross-checked; touched members only).
class BA3TypeView
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
    virtual int vf_33(BA3HouseView* owner);   // slot 33, +0x84

    char _pad_0004[0x1F4];   // +0x0004
    char unknown_1F8[1];   // +0x01F8
    char _pad_01F9[0x1CF];   // +0x01F9
    BA3Eight unknown_3C8;   // +0x03C8
    char _pad_03D0[0x140];   // +0x03D0
    BA3TypeSubView unknown_510;   // +0x0510
    char _pad_0524[0xCA];   // +0x0524
    unsigned char unknown_5EE;   // +0x05EE
    char _pad_05EF[0x8D];   // +0x05EF
    int unknown_67C;   // +0x067C
    char _pad_0680[0x4];   // +0x0680
    int unknown_684;   // +0x0684
    char _pad_0688[0xA4];   // +0x0688
    DynamicVectorClass<const BA3AnimTypeView*> unknown_72C;   // +0x072C
    char _pad_0744[0x4];   // +0x0744
    DynamicVectorClass<const BA3AnimTypeView*> unknown_748;   // +0x0748
    char _pad_0760[0x34];   // +0x0760
    DynamicVectorClass<const ParticleSystemTypeClass*> unknown_794;   // +0x0794
    char _pad_07AC[0x14];   // +0x07AC
    HBCoord unknown_7C0;   // +0x07C0
    char _pad_07CC[0x34];   // +0x07CC
    int unknown_800;   // +0x0800
    char _pad_0804[0x49E];   // +0x0804
    unsigned char unknown_CA2;   // +0x0CA2
    char _pad_0CA3[0x2B];   // +0x0CA3
    unsigned char unknown_CCE;   // +0x0CCE
    char _pad_0CCF[0x2];   // +0x0CCF
    unsigned char unknown_CD1;   // +0x0CD1
    char unknown_CD2;   // +0x0CD2
    char unknown_CD3;   // +0x0CD3
    char _pad_0CD4[0x1];   // +0x0CD4
    unsigned char unknown_CD5;   // +0x0CD5
    char _pad_0CD6[0x3F];   // +0x0CD6
    unsigned char unknown_D15;   // +0x0D15
    char _pad_0D16[0x1B];   // +0x0D16
    unsigned char unknown_D31;   // +0x0D31
    char _pad_0D32[0x9E];   // +0x0D32
    char unknown_DD0;   // +0x0DD0
    char _pad_0DD1[0x1F];   // +0x0DD1
    int unknown_DF0;   // +0x0DF0
    char _pad_0DF4[0x3C];   // +0x0DF4
    int unknown_E30;   // +0x0E30
    int unknown_E34;   // +0x0E34
    int unknown_E38;   // +0x0E38
    int unknown_E3C;   // +0x0E3C
    int unknown_E40;   // +0x0E40
    char _pad_0E44[0x5C];   // +0x0E44
    BA3UnitTypeView* unknown_EA0;   // +0x0EA0
    char _pad_0EA4[0x14];   // +0x0EA4
    int unknown_EB8;   // +0x0EB8
    char _pad_0EBC[0x18];   // +0x0EBC
    BA3OffsetHolderView* unknown_ED4;   // +0x0ED4
    char _pad_0ED8[0x10];   // +0x0ED8
    int unknown_EE8;   // +0x0EE8
    char _pad_0EEC[0x12C];   // +0x0EEC
    char unknown_1018[16];   // +0x1018
    char unknown_1028[16];   // +0x1028
    char unknown_1038[16];   // +0x1038
    char _pad_1048[0x14];   // +0x1048
    char unknown_105C[16];   // +0x105C
    char unknown_106C[16];   // +0x106C
    char _pad_107C[0x24];   // +0x107C
    char unknown_10A0[16];   // +0x10A0
    char unknown_10B0[16];   // +0x10B0
    char _pad_10C0[0x24];   // +0x10C0
    char unknown_10E4[16];   // +0x10E4
    char unknown_10F4[16];   // +0x10F4
    char _pad_1104[0x24];   // +0x1104
    char unknown_1128[16];   // +0x1128
    char unknown_1138[16];   // +0x1138
    char _pad_1148[0x24];   // +0x1148
    char unknown_116C[16];   // +0x116C
    char unknown_117C[16];   // +0x117C
    char _pad_118C[0x24];   // +0x118C
    char unknown_11B0[16];   // +0x11B0
    char _pad_11C0[0x20];   // +0x11C0
    HBPoint2D unknown_11E0;   // +0x11E0
    char _pad_11E8[0xC];   // +0x11E8
    char unknown_11F4[16];   // +0x11F4
    char unknown_1204[16];   // +0x1204
    char _pad_1214[0x68];   // +0x1214
    char unknown_127C[16];   // +0x127C
    char unknown_128C[16];   // +0x128C
    char _pad_129C[0x68];   // +0x129C
    char unknown_1304[16];   // +0x1304
    char unknown_1314[16];   // +0x1314
    char unknown_1324[16];   // +0x1324
    char _pad_1334[0x58];   // +0x1334
    char unknown_138C[16];   // +0x138C
    char unknown_139C[16];   // +0x139C
    char unknown_13AC[16];   // +0x13AC
    char _pad_13BC[0x58];   // +0x13BC
    char unknown_1414[16];   // +0x1414
    char unknown_1424[16];   // +0x1424
    char unknown_1434[16];   // +0x1434
    char _pad_1444[0x10A];   // +0x1444
    unsigned char unknown_154E;   // +0x154E
    char _pad_154F[0x11];   // +0x154F
    int unknown_1560;   // +0x1560
    int unknown_1564;   // +0x1564
    int unknown_1568;   // +0x1568
    char _pad_156C[0x7];   // +0x156C
    unsigned char unknown_1573;   // +0x1573
    char _pad_1574[0x130];   // +0x1574
    unsigned char unknown_16A4;   // +0x16A4
    char _pad_16A5[0x4];   // +0x16A5
    unsigned char unknown_16A9;   // +0x16A9
    unsigned char unknown_16AA;   // +0x16AA
    unsigned char unknown_16AB;   // +0x16AB
    char _pad_16AC[0x2];   // +0x16AC
    unsigned char unknown_16AE;   // +0x16AE
    unsigned char unknown_16AF;   // +0x16AF
    char _pad_16B0[0x9];   // +0x16B0
    unsigned char unknown_16B9;   // +0x16B9
    unsigned char unknown_16BA;   // +0x16BA
    unsigned char unknown_16BB;   // +0x16BB
    char _pad_16BC[0x1];   // +0x16BC
    unsigned char unknown_16BD;   // +0x16BD
    unsigned char unknown_16BE;   // +0x16BE
    char _pad_16BF[0x2];   // +0x16BF
    unsigned char unknown_16C1;   // +0x16C1
    unsigned char unknown_16C2;   // +0x16C2
    unsigned char unknown_16C3;   // +0x16C3
    char _pad_16C4[0x1];   // +0x16C4
    unsigned char unknown_16C5;   // +0x16C5
    char _pad_16C6[0x1];   // +0x16C6
    unsigned char unknown_16C7;   // +0x16C7
    unsigned char unknown_16C8;   // +0x16C8
    char _pad_16C9[0x2];   // +0x16C9
    unsigned char unknown_16CB;   // +0x16CB
    unsigned char unknown_16CC;   // +0x16CC
    char _pad_16CD[0x23];   // +0x16CD
    int unknown_16F0;   // +0x16F0
    char _pad_16F4[0x13];   // +0x16F4
    unsigned char unknown_1707;   // +0x1707
    char _pad_1708[0x78];   // +0x1708
    int unknown_1780;   // +0x1780
    // FUNCTION: GAMEMD 0x45EC90 (read-only here)
    int FUN_0045EC90();
    // FUNCTION: GAMEMD 0x45ECA0 (read-only here)
    int FUN_0045ECA0(int arg);
};
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1F8) == 0x1F8);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_3C8) == 0x3C8);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_510) == 0x510);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_5EE) == 0x5EE);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_67C) == 0x67C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_684) == 0x684);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_72C) == 0x72C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_748) == 0x748);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_794) == 0x794);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_7C0) == 0x7C0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_800) == 0x800);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_CA2) == 0xCA2);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_CCE) == 0xCCE);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_CD1) == 0xCD1);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_CD2) == 0xCD2);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_CD3) == 0xCD3);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_CD5) == 0xCD5);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_D15) == 0xD15);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_D31) == 0xD31);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_DD0) == 0xDD0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_DF0) == 0xDF0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_E30) == 0xE30);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_E34) == 0xE34);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_E38) == 0xE38);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_E3C) == 0xE3C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_E40) == 0xE40);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_EA0) == 0xEA0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_EB8) == 0xEB8);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_ED4) == 0xED4);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_EE8) == 0xEE8);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1018) == 0x1018);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1028) == 0x1028);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1038) == 0x1038);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_105C) == 0x105C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_106C) == 0x106C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_10A0) == 0x10A0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_10B0) == 0x10B0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_10E4) == 0x10E4);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_10F4) == 0x10F4);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1128) == 0x1128);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1138) == 0x1138);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_116C) == 0x116C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_117C) == 0x117C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_11B0) == 0x11B0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_11E0) == 0x11E0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_11F4) == 0x11F4);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1204) == 0x1204);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_127C) == 0x127C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_128C) == 0x128C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1304) == 0x1304);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1314) == 0x1314);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1324) == 0x1324);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_138C) == 0x138C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_139C) == 0x139C);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_13AC) == 0x13AC);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1414) == 0x1414);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1424) == 0x1424);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1434) == 0x1434);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_154E) == 0x154E);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1560) == 0x1560);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1564) == 0x1564);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1568) == 0x1568);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1573) == 0x1573);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16A4) == 0x16A4);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16A9) == 0x16A9);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16AA) == 0x16AA);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16AB) == 0x16AB);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16AE) == 0x16AE);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16AF) == 0x16AF);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16B9) == 0x16B9);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16BA) == 0x16BA);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16BB) == 0x16BB);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16BD) == 0x16BD);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16BE) == 0x16BE);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16C1) == 0x16C1);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16C2) == 0x16C2);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16C3) == 0x16C3);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16C5) == 0x16C5);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16C7) == 0x16C7);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16C8) == 0x16C8);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16CB) == 0x16CB);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16CC) == 0x16CC);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_16F0) == 0x16F0);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1707) == 0x1707);
GG_STATIC_ASSERT(offsetof(BA3TypeView, unknown_1780) == 0x1780);

// Object returned by FUN_005F6360 (partial).
struct BA3ProbeView
{
    // FUNCTION: GAMEMD 0x48AB90 (read-only here)
    int FUN_0048AB90(double radius);
};

// A stage counter (StageClass, name YRpp-cross-checked): current stage, "changed" flag, timer, rate and step.
struct BA3StageView
{
    int Stage;   // +0x0000
    unsigned char Changed;   // +0x0004
    char _pad_0005[0x3];   // +0x0005
    BA3Timer Timer;   // +0x0008
    int Rate;   // +0x0014
    int Step;   // +0x0018
};
GG_STATIC_ASSERT(offsetof(BA3StageView, Stage) == 0x0);
GG_STATIC_ASSERT(offsetof(BA3StageView, Changed) == 0x4);
GG_STATIC_ASSERT(offsetof(BA3StageView, Timer) == 0x8);
GG_STATIC_ASSERT(offsetof(BA3StageView, Rate) == 0x14);
GG_STATIC_ASSERT(offsetof(BA3StageView, Step) == 0x18);

// A 0x20 byte member of BuildingClass (two of them at +0x3D8 / +0x3F8; partial).
struct BA3RecoilView
{
    char _pad_0000[0x20];   // +0x0000
    // FUNCTION: GAMEMD 0x70ECE0 (read-only here)
    void FUN_0070ECE0();
};
GG_STATIC_ASSERT(sizeof(BA3RecoilView) == 0x20);

// A countdown member of BuildingClass at +0x350 (partial).
struct BA3Stage350View
{
    char _pad_0000[0x1C];   // +0x0000
    // FUNCTION: GAMEMD 0x4A51B0 (read-only here)
    bool FUN_004A51B0();
    // FUNCTION: GAMEMD 0x4A51D0 (read-only here)
    bool FUN_004A51D0();
    // FUNCTION: GAMEMD 0x4A51F0 (read-only here)
    void FUN_004A51F0(BA3Eight duration);
    // FUNCTION: GAMEMD 0x4A5240 (read-only here)
    void FUN_004A5240(BA3Eight duration);
};
GG_STATIC_ASSERT(sizeof(BA3Stage350View) == 0x1C);

// Partial BuildingClass view (sizeof not modelled).
class BuildingA3View
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
    virtual int vf_14();   // slot 14, +0x38
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual HBCoord vf_18();   // slot 18, +0x48
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
    virtual BA3TypeView* vf_33();   // slot 33, +0x84
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual void vt_0A8();
    virtual HBCoord* vf_43(HBCoord* out);   // slot 43, +0xAC
    virtual HBCoord vf_44(int zero, HBCoord offset);   // slot 44, +0xB0
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
    virtual void vt_0FC();
    virtual void vf_64(BA3TechnoView* who, HBCell b);   // slot 64, +0x100
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
    virtual bool vf_81(int mode, BA3ObjView* target, int unused);   // slot 81, +0x144
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
    virtual HBCell* vf_110(HBCell* out);   // slot 110, +0x1B8
    virtual void vt_1BC();
    virtual void vt_1C0();
    virtual void vt_1C4();
    virtual int vf_114();   // slot 114, +0x1C8
    virtual void vt_1CC();
    virtual void vt_1D0();
    virtual void vt_1D4();
    virtual void vt_1D8();
    virtual void vt_1DC();
    virtual void vt_1E0();
    virtual int vf_121();   // slot 121, +0x1E4
    virtual void vf_122(int mission, int arg);   // slot 122, +0x1E8
    virtual void vt_1EC();
    virtual bool vf_124(HBCoord* from, double* velocity);   // slot 124, +0x1F0
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
    virtual int vf_143();   // slot 143, +0x23C
    virtual void vt_240();
    virtual void vt_244();
    virtual void vt_248();
    virtual int vf_147();   // slot 147, +0x24C
    virtual int vf_148();   // slot 148, +0x250
    virtual void vt_254();
    virtual void vt_258();
    virtual void vt_25C();
    virtual void vt_260();
    virtual void vt_264();
    virtual void vt_268();
    virtual void vt_26C();
    virtual void vt_270();
    virtual int vf_157(int arg);   // slot 157, +0x274
    virtual int vf_158(int a, void* o);   // slot 158, +0x278
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
    virtual HBDir vf_178(BA3ObjView* target);   // slot 178, +0x2C8
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
    virtual HBCoord vf_192(int zero);   // slot 192, +0x300
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
    virtual void vf_222(int a, BA3ObjView* target, int c, int d);   // slot 222, +0x378
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
    virtual void vf_243(void* target, int arg);   // slot 243, +0x3CC
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
    virtual BA3WeaponSlotView* vf_254(int which);   // slot 254, +0x3F8
    virtual bool vf_255();   // slot 255, +0x3FC
    virtual void vt_400();
    virtual void vt_404();
    virtual int vf_258();   // slot 258, +0x408
    virtual void vt_40C();
    virtual void vf_260(int arg);   // slot 260, +0x410
    virtual void vf_261();   // slot 261, +0x414
    virtual void vf_262();   // slot 262, +0x418
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
    virtual void vf_288(void* target, int arg);   // slot 288, +0x480
    virtual void vf_289(bool flag, int unused);   // slot 289, +0x484
    virtual void vf_290(int a, int b, int c, BA3HouseView* house, int d);   // slot 290, +0x488
    virtual void vf_291(int a, int b, int c, BA3HouseView* house);   // slot 291, +0x48C
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
    virtual HBCell* vf_309(HBCell* out, BA3TechnoView* who, HBCell cell);   // slot 309, +0x4D4
    virtual int vf_310(BA3TechnoView* who);   // slot 310, +0x4D8
    virtual void vf_311(char flag);   // slot 311, +0x4DC
    virtual void vt_4E0();
    virtual void vt_4E4();
    virtual HBDir vf_314(void* target);   // slot 314, +0x4E8
    virtual void vf_315(int unused, int a, char flag, short* list);   // slot 315, +0x4EC
    virtual void vt_4F0();
    virtual void vf_317(const HBCell& cell);   // slot 317, +0x4F4
    virtual void vt_4F8();
    virtual void vf_319(const HBCell& cell);   // slot 319, +0x4FC

    char _pad_0004[0x34];   // +0x0004
    BA3Chain1View* unknown_38;   // +0x0038
    char _pad_003C[0x30];   // +0x003C
    int unknown_6C;   // +0x006C
    char _pad_0070[0x10];   // +0x0070
    unsigned char unknown_80;   // +0x0080
    unsigned char unknown_81;   // +0x0081
    char _pad_0082[0x1A];   // +0x0082
    HBCoord Location;   // +0x009C
    char _pad_00A8[0x14];   // +0x00A8
    int Status;   // +0x00BC
    char _pad_00C0[0x28];   // +0x00C0
    int unknown_E8;   // +0x00E8
    char _pad_00EC[0x14];   // +0x00EC
    HBCoord unknown_100;   // +0x0100
    int unknown_10C;   // +0x010C
    char _pad_0110[0x4];   // +0x0110
    BA3Obj114View unknown_114;   // +0x0114
    char _pad_0118[0xF8];   // +0x0118
    int unknown_210;   // +0x0210
    char _pad_0214[0x4];   // +0x0214
    BA3ObjView* unknown_218;   // +0x0218
    BA3HouseView* Owner;   // +0x021C
    char _pad_0220[0x40];   // +0x0220
    int unknown_260;   // +0x0260
    char _pad_0264[0x4];   // +0x0264
    unsigned char unknown_268;   // +0x0268
    char _pad_0269[0x3];   // +0x0269
    int unknown_26C;   // +0x026C
    char _pad_0270[0x8C];   // +0x0270
    int unknown_2FC;   // +0x02FC
    int unknown_300;   // +0x0300
    char _pad_0304[0x1C];   // +0x0304
    BA3ParticleView* unknown_320;   // +0x0320
    char _pad_0324[0x18];   // +0x0324
    BA3FloatView unknown_33C;   // +0x033C
    char _pad_033D[0x13];   // +0x033D
    BA3Stage350View unknown_350;   // +0x0350
    char _pad_036C[0x4];   // +0x036C
    BA3FacingView Facing370;   // +0x0370
    char _pad_0371[0x17];   // +0x0371
    BA3FacingView Facing388;   // +0x0388
    char _pad_0389[0x4F];   // +0x0389
    BA3RecoilView unknown_3D8;   // +0x03D8
    BA3RecoilView unknown_3F8;   // +0x03F8
    unsigned char unknown_418;   // +0x0418
    char _pad_0419[0x1];   // +0x0419
    unsigned char unknown_41A;   // +0x041A
    char _pad_041B[0x105];   // +0x041B
    BA3TypeView* Type;   // +0x0520
    char _pad_0524[0x4];   // +0x0524
    HBCoord unknown_528;   // +0x0528
    char _pad_0534[0xC];   // +0x0534
    BA3ObjView* C4AppliedBy;   // +0x0540
    char _pad_0544[0x8];   // +0x0544
    BA3AnimView* unknown_54C;   // +0x054C
    char _pad_0550[0x2C];   // +0x0550
    int unknown_57C;   // +0x057C
    BA3SpotView* unknown_580;   // +0x0580
    char _pad_0584[0x4];   // +0x0584
    int unknown_588;   // +0x0588
    int unknown_58C;   // +0x058C
    char _pad_0590[0x38];   // +0x0590
    BA3AnimView* DamageFireAnims[8];   // +0x05C8
    char _pad_05E8[0x10];   // +0x05E8
    int unknown_5F8;   // +0x05F8
    int unknown_5FC;   // +0x05FC
    char _pad_0600[0x14];   // +0x0600
    BA3LightView* LightSource;   // +0x0614
    char _pad_0618[0x8];   // +0x0618
    BA3StageView unknown_620;   // +0x0620
    char _pad_063C[0x2D];   // +0x063C
    unsigned char unknown_669;   // +0x0669
    char _pad_066A[0x66];   // +0x066A
    BA3Timer unknown_6D0;   // +0x06D0
    char _pad_06DC[0x1];   // +0x06DC
    unsigned char unknown_6DD;   // +0x06DD
    char _pad_06DE[0x2];   // +0x06DE
    unsigned char unknown_6E0;   // +0x06E0
    char _pad_06E1[0x3];   // +0x06E1
    unsigned char unknown_6E4;   // +0x06E4
    char _pad_06E5[0x6];   // +0x06E5
    unsigned char unknown_6EB;   // +0x06EB
    unsigned char unknown_6EC;   // +0x06EC
    char _pad_06ED[0x3];   // +0x06ED
    int unknown_6F0;   // +0x06F0
    // FUNCTION: GAMEMD 0x70BCB0 (read-only here)
    HBCoord FUN_0070BCB0();
    // FUNCTION: GAMEMD 0x5F6360 (read-only here)
    BA3ProbeView* FUN_005F6360(BA3ObjView* target);
    // FUNCTION: GAMEMD 0x70D590 (read-only here)
    char FUN_0070D590(int arg);
    // FUNCTION: GAMEMD 0x6FDA00 (read-only here)
    HBDir FUN_006FDA00(BA3ObjView* target);
    // FUNCTION: GAMEMD 0x452A40 (read-only here)
    void FUN_00452A40(int arg);
    // FUNCTION: GAMEMD 0x443860 (read-only here)
    void FUN_00443860(const HBCell& cell, int flag);
    // FUNCTION: GAMEMD 0x442D90 (read-only here)
    void FUN_00442D90(BA3ObjView* arg);
    // FUNCTION: GAMEMD 0x707CB0 (read-only here) - inherited body.
    void FUN_00707CB0(int arg);
    // FUNCTION: GAMEMD 0x5F5C60 (read-only here) - the health ratio.
    double FUN_005F5C60();
    // FUNCTION: GAMEMD 0x451890 (read-only here)
    void FUN_00451890(const char* name, int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x451E40 (read-only here)
    void FUN_00451E40(int arg);
    // FUNCTION: GAMEMD 0x4533A0 (read-only here)
    void FUN_004533A0(char arg);
    // FUNCTION: GAMEMD 0x4547C0 (read-only here)
    void FUN_004547C0();
    // FUNCTION: GAMEMD 0x65AD30 (read-only here) - the passenger with the given index.
    BA3TechnoView* FUN_0065AD30(int index);
    // FUNCTION: GAMEMD 0x65AE30 (read-only here)
    bool FUN_0065AE30();
    // FUNCTION: GAMEMD 0x447780 (read-only here)
    void FUN_00447780(int arg);
    // FUNCTION: GAMEMD 0x458E50 (read-only here)
    void FUN_00458E50();
    // FUNCTION: GAMEMD 0x5B3A00 (read-only here)
    HBPriceView* FUN_005B3A00();
    // FUNCTION: GAMEMD 0x457DE0 (read-only here)
    void FUN_00457DE0(int a, int b);
    // FUNCTION: GAMEMD 0x449540 (read-only here)
    bool FUN_00449540();
    // FUNCTION: GAMEMD 0x5F5F00 (read-only here)
    int FUN_005F5F00();
};
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_81) == 0x81);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Status) == 0xBC);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_E8) == 0xE8);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_100) == 0x100);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_10C) == 0x10C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_210) == 0x210);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_218) == 0x218);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_260) == 0x260);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_268) == 0x268);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_26C) == 0x26C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_300) == 0x300);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_320) == 0x320);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_33C) == 0x33C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_350) == 0x350);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Facing370) == 0x370);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Facing388) == 0x388);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_3D8) == 0x3D8);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_3F8) == 0x3F8);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_418) == 0x418);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_41A) == 0x41A);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_528) == 0x528);
GG_STATIC_ASSERT(offsetof(BuildingA3View, C4AppliedBy) == 0x540);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_54C) == 0x54C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_57C) == 0x57C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_580) == 0x580);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_588) == 0x588);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_58C) == 0x58C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, DamageFireAnims) == 0x5C8);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_5F8) == 0x5F8);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_5FC) == 0x5FC);
GG_STATIC_ASSERT(offsetof(BuildingA3View, LightSource) == 0x614);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_620) == 0x620);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_669) == 0x669);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6D0) == 0x6D0);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6DD) == 0x6DD);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6E0) == 0x6E0);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6E4) == 0x6E4);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6EB) == 0x6EB);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6EC) == 0x6EC);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6F0) == 0x6F0);


// GLOBAL: GAMEMD 0xA802C8 (the outgoing event queue)
extern BA3EventQueue DAT_00A802C8;
// IMPORT: GAMEMD 0x7E1530 (winmm timeGetTime)
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// LIBRARY: GAMEMD 0x7C91D0 -- strncpy.
extern "C" char* __cdecl strncpy(char*, const char*, unsigned int);

// The inline constructor of DynamicVectorClass (identical to the one in vector_class_operations.h, which this
// header does not include): the base constructor stays an out-of-line call (retail 0x45AD80 for the particle
// system type pointers).
template<class T> DynamicVectorClass<T>::DynamicVectorClass(int capacity, T* pMem)
    : VectorClass<T>(capacity, pMem)
{
    this->CapacityIncrement = 10;
    this->Count = 0;
}

// DynamicVectorClass::AddItem as the original expanded it inline: one short-circuit condition, the growth call
// goes through the object's SetCapacity slot.
template<class T> inline bool BA3AddItem(DynamicVectorClass<T>& v, const T& item)
{
    int cap = v.Capacity;
    if (v.Count < cap
        || ((v.IsAllocated || cap == 0) && v.CapacityIncrement > 0 && v.SetCapacity(v.CapacityIncrement + cap, 0))) {
        v.Items[v.Count++] = item;
        return true;
    }
    return false;
}

// GLOBAL: GAMEMD 0xA83D4C (the local player's house), 0xA8ED84, 0xA8B230 (random source), 0x89C848 (zero coordinate)
extern BA3HouseView* DAT_00A83D4C;
extern int DAT_00A8ED84;
extern HBSourceView* DAT_00A8B230;
extern HBCoord DAT_0089C848;
// GLOBAL: GAMEMD 0x818CB8..0x818CC8 - four int offsets scanned by 0x4415F0; 0xA83D84 / 0x8B4154 - object / anim type tables
extern int DAT_00818CB8[4];
extern BA3ObjView** DAT_00A83D84;
extern const BA3AnimTypeView** DAT_008B4154;
// STRING: GAMEMD 0x818E00 - "FIRE3"
extern const char s_FIRE3_00818E00[];
// GLOBAL: GAMEMD 0x7E2AC8 - float constant
extern const float DAT_007E2AC8;
// FUNCTION: GAMEMD 0x6B59A0 / 0x6B5C90 (read-only here) - ECX/EDX in registers, two more on the stack.
void FUN_006B59A0(const HBCoord& where, int a, int b, char c);
void FUN_006B5C90(const HBCoord& where, int a, int b, char c);
// FUNCTION: GAMEMD 0x49F420 / 0x49F550 (read-only here) - results come back through a hidden pointer in ECX.
HBCoord* FUN_0049F420(HBCoord* out, HBCoord* from, int distance, char flag);
HBCoord* FUN_0049F550(HBCoord* out, HBCoord* from, int distance);
// FUNCTION: GAMEMD 0x427CB0 (read-only here) - looks an anim type up by name: one register argument.
int FUN_00427CB0(const char* name);
// FUNCTION: GAMEMD 0x48DED0 (read-only here) - an empty body; the count is in ECX.
void FUN_0048DED0(int count);
// FUNCTION: GAMEMD 0x750E20 (read-only here) - ECX/EDX in registers, one more on the stack.
void FUN_00750E20(int a, HBCoord* where, int b);
// GLOBAL: GAMEMD 0x87F7E8 (the map object, its address is loaded into ECX), 0x8871E0 (rules), 0x887324.
extern BA3MapView DAT_0087F7E8;
extern BA3RulesView* RulesInstance;
extern HBPairXformView* DAT_00887324;
// GLOBAL: GAMEMD 0x7E1718 / 0x7E4418 / 0x7E4410 - double constants.
extern const double DAT_007E1718;
extern const double DAT_007E4418;
extern const double DAT_007E4410;
// FUNCTION: GAMEMD 0x4CAC40 / 0x4CAD80 / 0x4CAE30 (read-only here) - cdecl, double arguments.
double __cdecl FUN_004CAC40(double a);
double __cdecl FUN_004CAD80(double a);
double __cdecl FUN_004CAE30(double a, double b);
// FUNCTION: GAMEMD 0x48A8D0 (read-only here) - first two arguments in ECX/EDX, the rest on the stack (ret 0x14).
bool FUN_0048A8D0(char flag, int a, int b, int z, double radius, HBDir* out);
// GLOBAL: GAMEMD 0xA8E7AC / 0xA8ED6B / 0xA8B538 / 0xA8B238 and the index array 0xA83CBC
extern int DAT_00A8E7AC;
extern unsigned char DAT_00A8ED6B;
extern int DAT_00A8B538;
extern int DAT_00A8B238;
extern HBIdxView** DAT_00A83CBC;
// GLOBAL: GAMEMD 0x89F698 (a cell offset), 0x89C818 (the "no cell" marker), 0x7F4890 (a table of 32 values), 0x818D7C (a suffix)
extern HBCell DAT_0089F698;
extern HBCell DAT_0089C818;
extern int DAT_007F4890[32];
extern const char DAT_00818D7C[];
// STRING: GAMEMD 0x818F00 / 0x818EE8 / 0x818ED0 / 0x818E78 / 0x818EB0 / 0x818E94 - the EVA speech names of the super weapons.
extern const char s_EVA_NuclearSiloDetected_00818F00[];
extern const char s_EVA_IronCurtainDetected_00818EE8[];
extern const char s_EVA_WeatherDeviceReady_00818ED0[];
extern const char s_EVA_ChronosphereDetected_00818E78[];
extern const char s_EVA_PsychicDominatorDetected_00818EB0[];
extern const char s_EVA_GeneticMutatorDetected_00818E94[];
// FUNCTION: GAMEMD 0x752700 (read-only here) - the string in ECX, two further arguments (EDX and the stack).
void FUN_00752700(const char* name, int a, int b);
// FUNCTION: GAMEMD 0x65FA70 (read-only here) - ECX carries a small integer, one cell on the stack.
struct BA3EvaView { bool FUN_0065FA70(HBCell cell); };
// LIBRARY: GAMEMD intrinsics (/Oi expands them inline)
extern "C" char* __cdecl strcpy(char*, const char*);
extern "C" char* __cdecl strcat(char*, const char*);
extern "C" unsigned int __cdecl strlen(const char*);

// GLOBAL: GAMEMD 0x7E27F8 - double constant
extern const double DAT_007E27F8;
// FUNCTION: GAMEMD 0x7509E0 (read-only here) - plays a sound at a position.
void FUN_007509E0(int sound, HBCoord* where, void* unused);
// STRING: GAMEMD 0x81905C / 0x819044 / 0x818F18 - EVA speech names.
extern const char s_EVA_UnitRepaired_0081905C[];
extern const char s_EVA_InsufficientFunds_00819044[];
extern const char s_EVA_Repairing_00818F18[];

// GLOBAL: GAMEMD 0x7E9A40 / 0x7E9AB0 - two class ids compared with the one of a techno's persistent state
extern const unsigned char DAT_007E9A40[16];
extern const unsigned char DAT_007E9AB0[16];
extern "C" int __cdecl memcmp(const void*, const void*, unsigned int);

// GLOBAL: GAMEMD 0xA8E334 (table of launch holders), 0x886B88 (a random source)
extern BA3LaunchHolderView** DAT_00A8E334;
extern HBCounterView DAT_00886B88;
// GLOBAL: GAMEMD 0x7E44A8 / 0x7E2810 / 0x7E2800 / 0x7E2820 / 0x7E2818 - double constants (unit scale, radians per direction step, zero, direction conversion)
extern const double DAT_007E44A8;
extern const double DAT_007E2810;
extern const double DAT_007E2800;
extern const double DAT_007E2820;
extern const double DAT_007E2818;
// FUNCTION: GAMEMD 0x4CACB0 / 0x4CAD00 (read-only here) - cdecl, double argument.
double __cdecl FUN_004CACB0(double a);
double __cdecl FUN_004CAD00(double a);
// FUNCTION: GAMEMD 0x46B050 (read-only here) - ECX/EDX in registers, five more on the stack; creates the missile.
BA3MissileView* FUN_0046B050(int a, BA3ObjView* cell, BuildingA3View* owner, int b, int c, int speed, char flag);
// FUNCTION: GAMEMD 0x422B20 (read-only here) - looks an anim type up by name: one register argument.
int FUN_00422B20(const char* name);
// STRING: GAMEMD 0x81907C / 0x819070 - "PSIWARN" / "PULSBALL"
extern const char s_PSIWARN_0081907C[];
extern const char s_PULSBALL_00819070[];
extern "C" int __cdecl abs(int);

// GLOBAL: GAMEMD 0x89F688 - eight cell offsets (the neighbours in direction order)
extern HBCell DAT_0089F688[8];
// FUNCTION: GAMEMD 0x4068E0 (read-only here) - an empty body taking a pointer (cdecl).
void __cdecl FUN_004068E0(const void* arg);
// GLOBAL: GAMEMD 0x7E9A50 / 0x7E9A90 / 0x7E9A30 - class ids of locomotors, and the interface id at 0x819088
extern const unsigned char DAT_007E9A50[16];
extern const unsigned char DAT_007E9A90[16];
extern const unsigned char DAT_007E9A30[16];
extern const unsigned char DAT_00819088[16];

// The announcement that closes most states: a name picked by the health of the building (two name slots of the
// building type), played when it is not empty. A code expansion of the original's inline pair.
#define BA3_PLAY_NAME(b, healthy, damaged, id)                    \
    {                                                             \
        double ratio = (b)->FUN_005F5C60();                       \
        const char* name;                                         \
        int low;                                                  \
        if (ratio <= RulesInstance->unknown_1700) {               \
            name = (b)->Type->damaged;                            \
            low = 1;                                              \
        } else {                                                  \
            name = (b)->Type->healthy;                            \
            low = 0;                                              \
        }                                                         \
        if (name && *name) {                                      \
            (b)->FUN_00451890(name, id, low, 0, 0);               \
        }                                                         \
    }

// A double stored in a view as raw bytes (a double member in a virtual view class would move its first member).
inline double BA3DoubleOf(const unsigned char* bytes)
{
    return *(const double*)bytes;
}

extern const unsigned char DAT_00819098[];

// The queueing of an event as the original expanded it inline: the event is built first, then added to the ring buffer when
// there is room.
inline void BA3QueueEvent(const BA3Event& e)
{
    if (DAT_00A802C8.Count < 128) {
        DAT_00A802C8.List[DAT_00A802C8.Head] = e;
        DAT_00A802C8.unknown_378C[DAT_00A802C8.Head] = timeGetTime();
        DAT_00A802C8.Count++;
        DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 0x7F;
    }
}
// The same with the head advanced first (the second inline copy in the original stores in that order).
inline void BA3QueueEventHeadFirst(const BA3Event& e)
{
    if (DAT_00A802C8.Count < 128) {
        DAT_00A802C8.List[DAT_00A802C8.Head] = e;
        DAT_00A802C8.unknown_378C[DAT_00A802C8.Head] = timeGetTime();
        DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 0x7F;
        DAT_00A802C8.Count++;
    }
}




// BEGIN canonical-layout asserts
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_38) == HB_BLD_UNKNOWN_38);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6C) == HB_BLD_HEALTH);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_80) == HB_BLD_NEEDS_REDRAW);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_81) == HB_BLD_IN_LIMBO);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Location) == HB_BLD_LOCATION);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Status) == HB_BLD_STATUS);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_E8) == HB_BLD_UNKNOWN_E8);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_114) == HB_BLD_UNKNOWN_114);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_210) == HB_BLD_UNKNOWN_210);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_218) == HB_BLD_UNKNOWN_218);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Owner) == HB_BLD_OWNER);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_268) == HB_BLD_UNKNOWN_268);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_2FC) == HB_BLD_UNKNOWN_2FC);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_33C) == HB_BLD_UNKNOWN_33C);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_350) == HB_BLD_STAGE);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Facing370) == HB_BLD_TURRET);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Facing388) == HB_BLD_FACING);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_418) == HB_BLD_UNKNOWN_418);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_41A) == HB_BLD_UNKNOWN_41A);
GG_STATIC_ASSERT(offsetof(BuildingA3View, Type) == HB_BLD_TYPE);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_528) == HB_BLD_C4_TIMER);
GG_STATIC_ASSERT(offsetof(BuildingA3View, C4AppliedBy) == HB_BLD_C4_APPLIED_BY);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_54C) == HB_BLD_PSI_WARN_ANIM);
GG_STATIC_ASSERT(offsetof(BuildingA3View, DamageFireAnims) == HB_BLD_DAMAGE_FIRE_ANIMS);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_5FC) == HB_BLD_UNKNOWN_5FC);
GG_STATIC_ASSERT(offsetof(BuildingA3View, LightSource) == HB_BLD_LIGHT_SOURCE);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6D0) == HB_BLD_CASH_PRODUCTION_TIMER);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6DD) == HB_BLD_IS_READY_TO_COMMENCE);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6E0) == HB_BLD_NO_CREW);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6E4) == HB_BLD_ACTUALLY_PLACED_ON_MAP);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6EB) == HB_BLD_HAS_CLOAKING_DATA);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_6EC) == HB_BLD_CLOAK_RADIUS);
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_57C) == HB_BLD_ANIMS + 4 * 8);   // Anims[8]
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_580) == HB_BLD_ANIMS + 4 * 9);   // Anims[9]
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_588) == HB_BLD_ANIMS + 4 * 11);   // Anims[11]
GG_STATIC_ASSERT(offsetof(BuildingA3View, unknown_58C) == HB_BLD_ANIMS + 4 * 12);   // Anims[12]
// END canonical-layout asserts

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A3_VIEWS_H
