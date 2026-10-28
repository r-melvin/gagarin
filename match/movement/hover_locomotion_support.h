// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001, confirmed from Hover entry instructions, | YRpp-cross-check
// call sites and pinned PE data. This file contains only Hover-prefixed
// address-local views and does not claim complete linked-object layouts.
#ifndef GG_MATCH_MOVEMENT_HOVER_LOCOMOTION_SUPPORT_H
#define GG_MATCH_MOVEMENT_HOVER_LOCOMOTION_SUPPORT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_interfaces.h"
#include "loco_foot.h"                 // canonical DAT_0087F7E8 declaration
#include "../map/pair_0042d490.h"       // canonical Pair_0042D490 and DAT_0089F688

// Two-short cell-coordinate value used by Hover bodies and out-parameter calls.
struct HoverCellCoord
{
    short X;
    short Y;

    HoverCellCoord() {}
    HoverCellCoord(short x, short y) : X(x), Y(y) {}
    explicit HoverCellCoord(const LocoCoord& coord)
        : X((short)(coord.X / 256)), Y((short)(coord.Y / 256)) {}
    bool operator==(const HoverCellCoord& other) const
    { return X == other.X && Y == other.Y; }
    // FUNCTION: GAMEMD 0x50E470 (decl; reloc)
    bool FUN_0050E470(const HoverCellCoord* other);
};
GG_STATIC_ASSERT(offsetof(HoverCellCoord, X) == 0x00);
GG_STATIC_ASSERT(offsetof(HoverCellCoord, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(HoverCellCoord) == 0x04);
GG_STATIC_ASSERT(offsetof(Pair_0042D490, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Pair_0042D490, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(Pair_0042D490) == 0x04);

// One-dword facing value returned through the hidden pointer at the called slot.
struct HoverDirView
{
    unsigned int Raw;
    HoverDirView() {}
    HoverDirView(unsigned long raw) : Raw(raw) {}
};
GG_STATIC_ASSERT(offsetof(HoverDirView, Raw) == 0x00);
GG_STATIC_ASSERT(sizeof(HoverDirView) == 0x04);

// Opaque 0x18-byte facing subobject; only Hover-used operations are declared.
struct HoverFacingView
{
    char unknown_000[0x18];
    // FUNCTION: GAMEMD 0x4C91C0 (decl; reloc)
    HoverFacingView();
    // FUNCTION: GAMEMD 0x4C91E0 (decl; reloc)
    HoverFacingView(int rate);
    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc)
    HoverDirView Current();
    // FUNCTION: GAMEMD 0x4C9220 (decl; reloc)
    void SetDesired(const HoverDirView* direction);
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc)
    void Set(const HoverDirView* direction);
};
GG_STATIC_ASSERT(offsetof(HoverFacingView, unknown_000) == 0x00);
GG_STATIC_ASSERT(sizeof(HoverFacingView) == 0x18);

// House prefix: Hover only reads the dword pointer at Foot +0x21C and byte +0x16BD.
struct HoverHouseView
{
    char unknown_000[0x16BD];
    unsigned char unknown_16BD;
    // FUNCTION: GAMEMD 0x53A130 (decl; reloc)
    bool IonSensitivesShouldBeOffline() const;
};
GG_STATIC_ASSERT(offsetof(HoverHouseView, unknown_16BD) == 0x16BD);
GG_STATIC_ASSERT(sizeof(HoverHouseView) == 0x16BE); // accessed prefix only

struct HoverObjectView;
struct HoverTypeView;

// Slot declarations preserve only Hover's called object slots; other entries are
// placeholders needed to keep the observed slot indices.
struct HoverObjectVirtuals
{

    virtual void Slot_000();
    virtual void Slot_004();
    virtual void Slot_008();
    virtual void Slot_00C();
    virtual void Slot_010();
    virtual void Slot_014();
    virtual void Slot_018();
    virtual void Slot_01C();
    virtual void Slot_020();
    virtual void Slot_024();
    virtual void Slot_028();
    virtual int Slot_02C();
    virtual void Slot_030();
    virtual void Slot_034();
    virtual void Slot_038();
    virtual void Slot_03C();
    virtual void Slot_040();
    virtual void Slot_044();
    virtual void Slot_048();
    virtual LocoCoord* Slot_04C(LocoCoord* out, FootClass* foot);
};
GG_STATIC_ASSERT(sizeof(HoverObjectVirtuals) == 0x04);

struct HoverObjectView : HoverObjectVirtuals
{
    // FUNCTION: GAMEMD 0x486920 (decl; reloc)
    void FUN_00486920();
    // FUNCTION: GAMEMD 0x47C520 (decl; reloc)
    HoverObjectView* FUN_0047C520();
    char unknown_004[0x09C - 0x004];
    LocoCoord Location;
    char unknown_0A8[0x0EC - 0x0A8];
    int unknown_0EC;
    char unknown_0F0[0x11C - 0x0F0];
    unsigned char SlopeIndex;
    char unknown_11D[0x140 - 0x11D];
    unsigned int Flags;
    char unknown_144[0x520 - 0x144];
    HoverHouseView* unknown_520;
};
GG_STATIC_ASSERT(offsetof(HoverObjectView, Location) == 0x09C);
GG_STATIC_ASSERT(offsetof(HoverObjectView, unknown_0EC) == 0x0EC);
GG_STATIC_ASSERT(offsetof(HoverObjectView, SlopeIndex) == 0x11C);
GG_STATIC_ASSERT(offsetof(HoverObjectView, Flags) == 0x140);
GG_STATIC_ASSERT(offsetof(HoverObjectView, unknown_520) == 0x520);
GG_STATIC_ASSERT(sizeof(HoverObjectView) == 0x524); // accessed prefix only

struct HoverTypeVirtuals
{

    virtual void Slot_000();
    virtual void Slot_004();
    virtual void Slot_008();
    virtual void Slot_00C();
    virtual void Slot_010();
    virtual void Slot_014();
    virtual void Slot_018();
    virtual void Slot_01C();
    virtual void Slot_020();
    virtual void Slot_024();
    virtual void Slot_028();
    virtual void Slot_02C();
    virtual void Slot_030();
    virtual void Slot_034();
    virtual void Slot_038();
    virtual void Slot_03C();
    virtual void Slot_040();
    virtual void Slot_044();
    virtual void Slot_048();
    virtual void Slot_04C();
    virtual void Slot_050();
    virtual void Slot_054();
    virtual void Slot_058();
    virtual void Slot_05C();
    virtual void Slot_060();
    virtual void Slot_064();
    virtual void Slot_068();
    virtual void Slot_06C();
    virtual void Slot_070();
    virtual void Slot_074();
    virtual void Slot_078();
    virtual void Slot_07C();
    virtual void Slot_080();
    virtual HoverTypeView* Slot_084();
};
GG_STATIC_ASSERT(sizeof(HoverTypeVirtuals) == 0x04);

struct HoverTypeView : HoverTypeVirtuals
{
    char unknown_004[0x360 - 0x004];
    double unknown_360;
    double unknown_368;
    char unknown_370[0x71C - 0x370];
    int unknown_71C;
};
GG_STATIC_ASSERT(offsetof(HoverTypeView, unknown_360) == 0x360);
GG_STATIC_ASSERT(offsetof(HoverTypeView, unknown_368) == 0x368);
GG_STATIC_ASSERT(offsetof(HoverTypeView, unknown_71C) == 0x71C);
GG_STATIC_ASSERT(sizeof(HoverTypeView) == 0x720); // accessed prefix only

// Rules prefix used for the pointer read at +0x94.
struct HoverRulesView
{ char unknown_000[0x94]; void* unknown_094; };
GG_STATIC_ASSERT(offsetof(HoverRulesView, unknown_094) == 0x94);
GG_STATIC_ASSERT(sizeof(HoverRulesView) == 0x98); // accessed prefix only

// Animation object call used by Hover Process; no complete owner layout is claimed.
struct HoverAnimView
{
    char unknown_000[0x1C8];
    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc)
    HoverAnimView(void* type, LocoCoord* coord, int a, int b, int c, int d, char e);
};
GG_STATIC_ASSERT(sizeof(HoverAnimView) == 0x1C8);

struct HoverRandomView
{
    char unknown_000[0x04];
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc)
    int RandomRanged(int minval, int maxval);
};
GG_STATIC_ASSERT(sizeof(HoverRandomView) == 0x04);
struct HoverScenarioView
{ char unknown_000[0x218]; HoverRandomView Random; };
GG_STATIC_ASSERT(offsetof(HoverScenarioView, Random) == 0x218);
GG_STATIC_ASSERT(sizeof(HoverScenarioView) == 0x21C); // accessed prefix only

// Method-only Map prefix view. The singleton itself is the canonical LocoMap
// object declared in loco_foot.h; Hover accesses its same storage through this view.
struct HoverMapView
{
    char unknown_000[0x04];
    // FUNCTION: GAMEMD 0x565730 (decl; reloc)
    HoverObjectView* GetCellAt(const LocoCoord* coord);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    HoverObjectView* GetCellAtCell(const HoverCellCoord* cell);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc)
    int GetHeightAt(const LocoCoord* coord);
};
GG_STATIC_ASSERT(offsetof(HoverMapView, unknown_000) == 0x00);
GG_STATIC_ASSERT(sizeof(HoverMapView) == 0x04);
inline HoverMapView& HoverMap()
{ return *(HoverMapView*)(void*)&DAT_0087F7E8; }

// FootClass slots called by Hover. Unused slots are placeholders only, keeping
// the observed vtable indices; only Hover-used signatures carry arguments/results.
struct HoverFootVirtuals
{

    virtual void Slot_000();
    virtual void Slot_004();
    virtual void Slot_008();
    virtual void Slot_00C();
    virtual void Slot_010();
    virtual void Slot_014();
    virtual void Slot_018();
    virtual void Slot_01C();
    virtual void Slot_020();
    virtual void Slot_024();
    virtual void Slot_028();
    virtual void Slot_02C();
    virtual void Slot_030();
    virtual void Slot_034();
    virtual void Slot_038();
    virtual void Slot_03C();
    virtual void Slot_040();
    virtual void Slot_044();
    virtual void Slot_048();
    virtual void Slot_04C();
    virtual void Slot_050();
    virtual void Slot_054();
    virtual void Slot_058();
    virtual void Slot_05C();
    virtual void Slot_060();
    virtual void Slot_064();
    virtual void Slot_068();
    virtual void Slot_06C();
    virtual void Slot_070();
    virtual void Slot_074();
    virtual void Slot_078();
    virtual void Slot_07C();
    virtual void Slot_080();
    virtual HoverTypeView* Slot_084();
    virtual void Slot_088();
    virtual void Slot_08C();
    virtual void Slot_090();
    virtual void Slot_094();
    virtual void Slot_098();
    virtual void Slot_09C();
    virtual void Slot_0A0();
    virtual void Slot_0A4();
    virtual void Slot_0A8();
    virtual void Slot_0AC();
    virtual void Slot_0B0();
    virtual void Slot_0B4();
    virtual void Slot_0B8();
    virtual void Slot_0BC();
    virtual bool Slot_0C0();
    virtual void Slot_0C4();
    virtual void Slot_0C8();
    virtual void Slot_0CC();
    virtual void Slot_0D0();
    virtual void Slot_0D4();
    virtual void Slot_0D8();
    virtual void Slot_0DC();
    virtual void Slot_0E0();
    virtual void Slot_0E4();
    virtual void Slot_0E8();
    virtual void Slot_0EC();
    virtual void Slot_0F0(LocoCoord* coord);
    virtual void Slot_0F4(const LocoCoord* coord);
    virtual void Slot_0F8();
    virtual void Slot_0FC();
    virtual void Slot_100();
    virtual void Slot_104();
    virtual void Slot_108();
    virtual void Slot_10C();
    virtual void Slot_110();
    virtual void Slot_114();
    virtual void Slot_118();
    virtual void Slot_11C();
    virtual void Slot_120();
    virtual void Slot_124(int arg);
    virtual void Slot_128();
    virtual void Slot_12C();
    virtual void Slot_130();
    virtual void Slot_134();
    virtual void Slot_138();
    virtual void Slot_13C();
    virtual void Slot_140();
    virtual void Slot_144();
    virtual void Slot_148();
    virtual void Slot_14C();
    virtual void Slot_150();
    virtual void Slot_154();
    virtual void Slot_158();
    virtual void Slot_15C();
    virtual void Slot_160();
    virtual void Slot_164();
    virtual void Slot_168();
    virtual void Slot_16C();
    virtual void Slot_170();
    virtual void Slot_174();
    virtual void Slot_178();
    virtual void Slot_17C();
    virtual void Slot_180();
    virtual void Slot_184();
    virtual void Slot_188();
    virtual void Slot_18C(int arg);
    virtual void Slot_190();
    virtual void Slot_194();
    virtual void Slot_198();
    virtual void Slot_19C();
    virtual void Slot_1A0();
    virtual void Slot_1A4();
    virtual void Slot_1A8();
    virtual int Slot_1AC(HoverObjectView* cell, int a, int b, int c, int d);
    virtual void Slot_1B0();
    virtual void Slot_1B4(LocoCoord* coord);
    virtual HoverCellCoord* Slot_1B8(HoverCellCoord* out);
    virtual HoverObjectView* Slot_1BC();
    virtual void Slot_1C0();
    virtual void Slot_1C4();
    virtual int Slot_1C8();
    virtual void Slot_1CC();
    virtual int Slot_1D0();
    virtual void Slot_1D4();
    virtual void Slot_1D8();
    virtual void Slot_1DC();
    virtual void Slot_1E0();
    virtual void Slot_1E4();
    virtual void Slot_1E8();
    virtual void Slot_1EC();
    virtual void Slot_1F0();
    virtual void Slot_1F4();
    virtual void Slot_1F8();
    virtual void Slot_1FC();
    virtual void Slot_200();
    virtual void Slot_204();
    virtual void Slot_208();
    virtual void Slot_20C();
    virtual void Slot_210();
    virtual void Slot_214();
    virtual void Slot_218();
    virtual void Slot_21C();
    virtual void Slot_220();
    virtual void Slot_224();
    virtual void Slot_228();
    virtual void Slot_22C();
    virtual void Slot_230();
    virtual void Slot_234();
    virtual void Slot_238();
    virtual void Slot_23C();
    virtual void Slot_240();
    virtual void Slot_244();
    virtual void Slot_248();
    virtual void Slot_24C();
    virtual void Slot_250();
    virtual void Slot_254();
    virtual void Slot_258();
    virtual void Slot_25C();
    virtual void Slot_260();
    virtual void Slot_264();
    virtual void Slot_268();
    virtual void Slot_26C();
    virtual void Slot_270();
    virtual void Slot_274();
    virtual void Slot_278();
    virtual void Slot_27C();
    virtual void Slot_280();
    virtual void Slot_284();
    virtual void Slot_288();
    virtual void Slot_28C();
    virtual void Slot_290();
    virtual void Slot_294();
    virtual void Slot_298();
    virtual void Slot_29C();
    virtual void Slot_2A0();
    virtual void Slot_2A4();
    virtual void Slot_2A8();
    virtual void Slot_2AC();
    virtual void Slot_2B0();
    virtual void Slot_2B4();
    virtual void Slot_2B8();
    virtual void Slot_2BC();
    virtual void Slot_2C0();
    virtual void Slot_2C4();
    virtual void Slot_2C8();
    virtual void Slot_2CC();
    virtual void Slot_2D0();
    virtual void Slot_2D4();
    virtual void Slot_2D8();
    virtual void Slot_2DC();
    virtual void Slot_2E0();
    virtual void Slot_2E4();
    virtual void Slot_2E8();
    virtual void Slot_2EC();
    virtual void Slot_2F0();
    virtual void Slot_2F4();
    virtual void Slot_2F8();
    virtual void Slot_2FC();
    virtual void Slot_300();
    virtual void Slot_304();
    virtual void Slot_308();
    virtual void Slot_30C();
    virtual void Slot_310();
    virtual void Slot_314();
    virtual void Slot_318();
    virtual void Slot_31C();
    virtual void Slot_320();
    virtual void Slot_324();
    virtual void Slot_328();
    virtual void Slot_32C();
    virtual void Slot_330();
    virtual void Slot_334();
    virtual void Slot_338();
    virtual void Slot_33C();
    virtual void Slot_340();
    virtual void Slot_344();
    virtual void Slot_348();
    virtual void Slot_34C();
    virtual void Slot_350();
    virtual void Slot_354();
    virtual void Slot_358();
    virtual void Slot_35C();
    virtual void Slot_360();
    virtual void Slot_364();
    virtual void Slot_368();
    virtual void Slot_36C();
    virtual void Slot_370();
    virtual void Slot_374();
    virtual void Slot_378();
    virtual void Slot_37C();
    virtual bool Slot_380();
    virtual void Slot_384();
    virtual void Slot_388();
    virtual void Slot_38C();
    virtual void Slot_390();
    virtual void Slot_394();
    virtual void Slot_398();
    virtual void Slot_39C();
    virtual void Slot_3A0();
    virtual void Slot_3A4();
    virtual void Slot_3A8();
    virtual bool Slot_3AC(HoverObjectView* arg);
    virtual void Slot_3B0();
    virtual void Slot_3B4();
    virtual void Slot_3B8();
    virtual void Slot_3BC();
    virtual void Slot_3C0();
    virtual void Slot_3C4();
    virtual void Slot_3C8();
    virtual void Slot_3CC();
    virtual void Slot_3D0();
    virtual void Slot_3D4();
    virtual void Slot_3D8();
    virtual void Slot_3DC();
    virtual void Slot_3E0();
    virtual void Slot_3E4();
    virtual void Slot_3E8();
    virtual void Slot_3EC();
    virtual void Slot_3F0();
    virtual void Slot_3F4();
    virtual void Slot_3F8();
    virtual void Slot_3FC();
    virtual void Slot_400();
    virtual void Slot_404();
    virtual void Slot_408();
    virtual void Slot_40C();
    virtual void Slot_410();
    virtual void Slot_414();
    virtual void Slot_418();
    virtual void Slot_41C();
    virtual void Slot_420();
    virtual void Slot_424();
    virtual void Slot_428();
    virtual void Slot_42C();
    virtual void Slot_430();
    virtual void Slot_434();
    virtual void Slot_438();
    virtual void Slot_43C();
    virtual void Slot_440();
    virtual void Slot_444();
    virtual void Slot_448();
    virtual void Slot_44C();
    virtual void Slot_450();
    virtual void Slot_454();
    virtual void Slot_458();
    virtual void Slot_45C();
    virtual void Slot_460();
    virtual void Slot_464();
    virtual void Slot_468();
    virtual void Slot_46C();
    virtual void Slot_470();
    virtual void Slot_474();
    virtual void Slot_478();
    virtual void Slot_47C();
    virtual void Slot_480(int a, int b);
    virtual void Slot_484();
    virtual void Slot_488();
    virtual void Slot_48C();
    virtual void Slot_490();
    virtual void Slot_494();
    virtual void Slot_498();
    virtual void Slot_49C();
    virtual void Slot_4A0();
    virtual void Slot_4A4();
    virtual void Slot_4A8();
    virtual void Slot_4AC();
    virtual void Slot_4B0();
    virtual void Slot_4B4();
    virtual void Slot_4B8();
    virtual void Slot_4BC();
    virtual void Slot_4C0();
    virtual void Slot_4C4();
    virtual void Slot_4C8();
    virtual void Slot_4CC();
    virtual void Slot_4D0();
    virtual void Slot_4D4();
    virtual void Slot_4D8();
    virtual void Slot_4DC();
    virtual void Slot_4E0();
    virtual void Slot_4E4();
    virtual void Slot_4E8();
    virtual void Slot_4EC();
    virtual void Slot_4F0();
    virtual void Slot_4F4();
    virtual void Slot_4F8();
    virtual void Slot_4FC();
    virtual void Slot_500();
    virtual void Slot_504();
    virtual void Slot_508();
    virtual void Slot_50C();
    virtual void Slot_510();
    virtual void Slot_514();
    virtual void Slot_518();
    virtual void Slot_51C();
    virtual void Slot_520();
    virtual void Slot_524();
    virtual void Slot_528();
    virtual void Slot_52C();
    virtual void Slot_530();
    virtual void Slot_534();
    virtual int Slot_538();
    virtual void Slot_53C();
    virtual void Slot_540();
    virtual void Slot_544(double arg);
};
GG_STATIC_ASSERT(sizeof(HoverFootVirtuals) == 0x04);

struct HoverFootView : HoverFootVirtuals
{
    // FUNCTION: GAMEMD 0x5F6060 (decl; reloc)
    void FUN_005F6060(int value);
    // FUNCTION: GAMEMD 0x65AE30 (decl; reloc)
    bool FUN_0065AE30();
    // FUNCTION: GAMEMD 0x65AD30 (decl; reloc)
    HoverObjectView* FUN_0065AD30(int index);
    char unknown_004[0x074 - 0x004];
    unsigned char unknown_074;
    char unknown_075[0x081 - 0x075];
    bool unknown_081;
    char unknown_082[0x08C - 0x082];
    bool unknown_08C;
    bool unknown_08D;
    char unknown_08E[0x090 - 0x08E];
    bool unknown_090;
    char unknown_091[0x09C - 0x091];
    LocoCoord Location;
    char unknown_0A8[0x0AC - 0x0A8];
    int unknown_0AC;
    char unknown_0B0[0x21C - 0x0B0];
    HoverHouseView* House;
    char unknown_220[0x2B4 - 0x220];
    HoverObjectView* unknown_2B4;
    char unknown_2B8[0x328 - 0x2B8];
    float AngleSideways;
    float AngleForwards;
    char unknown_330[0x388 - 0x330];
    HoverFacingView PrimaryFacing;
    char unknown_3A0[0x5A4 - 0x3A0];
    HoverObjectView* unknown_5A4;
    char unknown_5A8[0x5E0 - 0x5A8];
    int PathDirection0;
    char unknown_5E4[0x684 - 0x5E4];
    char unknown_684;
    char unknown_685[0x6B6 - 0x685];
    unsigned char unknown_6B6;
    unsigned char unknown_6B7;
};
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_074) == 0x074);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_081) == 0x081);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_08C) == 0x08C);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_08D) == 0x08D);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_090) == 0x090);
GG_STATIC_ASSERT(offsetof(HoverFootView, Location) == 0x09C);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_0AC) == 0x0AC);
GG_STATIC_ASSERT(offsetof(HoverFootView, House) == 0x21C);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_2B4) == 0x2B4);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_5A4) == 0x5A4);
GG_STATIC_ASSERT(offsetof(HoverFootView, AngleSideways) == 0x328);
GG_STATIC_ASSERT(offsetof(HoverFootView, AngleForwards) == 0x32C);
GG_STATIC_ASSERT(offsetof(HoverFootView, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(offsetof(HoverFootView, PathDirection0) == 0x5E0);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_684) == 0x684);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_6B6) == 0x6B6);
GG_STATIC_ASSERT(offsetof(HoverFootView, unknown_6B7) == 0x6B7);
GG_STATIC_ASSERT(sizeof(HoverFootView) == 0x6B8); // modeled accessed prefix, not complete FootClass size

// Offset ledger for the Foot vtable slots dispatched by this Hover cluster.
struct HoverFootSlotOffsets
{
    char unknown_000[0x084 - 0x000];
    void* slot_084;
    char unknown_088[0x0C0 - 0x088];
    void* slot_0C0;
    char unknown_0C4[0x0EC - 0x0C4];
    void* slot_0EC;
    void* slot_0F0;
    void* slot_0F4;
    char unknown_0F8[0x124 - 0x0F8];
    void* slot_124;
    char unknown_128[0x18C - 0x128];
    void* slot_18C;
    char unknown_190[0x1AC - 0x190];
    void* slot_1AC;
    char unknown_1B0[0x1B4 - 0x1B0];
    void* slot_1B4;
    void* slot_1B8;
    void* slot_1BC;
    char unknown_1C0[0x1C8 - 0x1C0];
    void* slot_1C8;
    char unknown_1CC[0x1D0 - 0x1CC];
    void* slot_1D0;
    char unknown_1D4[0x380 - 0x1D4];
    void* slot_380;
    char unknown_384[0x480 - 0x384];
    void* slot_480;
    char unknown_484[0x538 - 0x484];
    void* slot_538;
    char unknown_53C[0x544 - 0x53C];
    void* slot_544;
};
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_084) == 0x084);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_0C0) == 0x0C0);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_0EC) == 0x0EC);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_0F0) == 0x0F0);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_0F4) == 0x0F4);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_124) == 0x124);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_18C) == 0x18C);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_1AC) == 0x1AC);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_1B4) == 0x1B4);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_1B8) == 0x1B8);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_1BC) == 0x1BC);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_1C8) == 0x1C8);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_1D0) == 0x1D0);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_380) == 0x380);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_480) == 0x480);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_538) == 0x538);
GG_STATIC_ASSERT(offsetof(HoverFootSlotOffsets, slot_544) == 0x544);
GG_STATIC_ASSERT(sizeof(HoverFootSlotOffsets) == 0x548);

#include "matrix3d_native_helpers.h"
double __cdecl HoverSqrt(double value); // FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl HoverSin(double angle); // FUNCTION: GAMEMD 0x4CACB0 (decl; reloc)
double __cdecl HoverCos(double angle); // FUNCTION: GAMEMD 0x4CAD00 (decl; reloc)
double __cdecl HoverAtan2(double y, double x); // FUNCTION: GAMEMD 0x4CAE30 (decl; reloc)

#endif  // GG_MATCH_MOVEMENT_HOVER_LOCOMOTION_SUPPORT_H
