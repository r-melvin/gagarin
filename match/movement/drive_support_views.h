// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Address-local views used by the DriveLocomotionClass bodies only. Every
//   member offset and slot below is read from an entry-origin instruction of a
//   Drive body (cited beside it); none of them claims a complete FootClass,
//   CellClass, TechnoTypeClass or MapClass layout.
#ifndef GG_MATCH_MOVEMENT_DRIVE_SUPPORT_VIEWS_H
#define GG_MATCH_MOVEMENT_DRIVE_SUPPORT_VIEWS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_interfaces.h"
#include "loco_com.h"
#include "loco_foot.h"                 // canonical DAT_0087F7E8 declaration

struct DriveFootView;

// Two-short cell coordinate: IsMovingHere 0x4B4920 converts both sides with
// `CDQ; AND EDX,0xFF; ADD; SAR 8` and compares the low words (`CMP SI,CX`).
struct DriveCellCoord
{
    short X;
    short Y;
    DriveCellCoord(int x, int y) : X((short)(x / 256)), Y((short)(y / 256)) {}
    bool operator==(const DriveCellCoord& other) const
    { return X == other.X && Y == other.Y; }
};
GG_STATIC_ASSERT(sizeof(DriveCellCoord) == 4);

// Map cell prefix: SlopeIndex read by Unlimbo 0x4B04D0 (`[EAX+0x11C]`), the
// flag word by MoveTo 0x4AFD40 (`TEST [EAX+0x141],1`).
struct DriveCellView
{
    char          unknown_000[0x11C];
    unsigned char SlopeIndex;            // +0x11C
    char          unknown_11D[0x140 - 0x11D];
    unsigned int  Flags;                 // +0x140
    // FUNCTION: GAMEMD 0x481A00 (decl; reloc) - __thiscall, one stack argument (the foot).
    bool FUN_00481A00(DriveFootView* foot);
};
GG_STATIC_ASSERT(offsetof(DriveCellView, SlopeIndex) == 0x11C);
GG_STATIC_ASSERT(offsetof(DriveCellView, Flags) == 0x140);

// Type prefix: the byte StopMoving 0x4AFE00 reads at `[EAX+0xC94]`.
struct DriveTypeView
{
    char          unknown_000[0xC94];
    unsigned char unknown_C94;           // +0xC94
};
GG_STATIC_ASSERT(offsetof(DriveTypeView, unknown_C94) == 0xC94);

// Facing subobject at foot +0x388 (0x18 bytes).
struct DriveFacingView
{
    char unknown_000[0x18];
    // FUNCTION: GAMEMD 0x4C9220 (decl; reloc) - __thiscall, DoTurn 0x4B0EF0.
    void FUN_004C9220(const unsigned long* dir);
    // FUNCTION: GAMEMD 0x4C9480 (decl; reloc) - __thiscall, IsMovingNow 0x4AFC20.
    bool FUN_004C9480();
};
GG_STATIC_ASSERT(sizeof(DriveFacingView) == 0x18);

// Map object at 0x87F7E8 (an immediate ECX in MoveTo, ForceTrack and 0x4B4800).
struct DriveMapView
{
    char unknown_000[4];
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) - __thiscall, coordinate pointer.
    DriveCellView* FUN_00565730(const LocoCoord* coord);
    // FUNCTION: GAMEMD 0x578AD0 (decl; reloc) - __thiscall, foot then a stack-argument pointer.
    void FUN_00578AD0(DriveFootView* foot, const void* arg);
};
// The singleton is the canonical DAT_0087F7E8 (loco_foot.h); Drive calls its
// methods through this method-only view.
inline DriveMapView& DriveMap()
{ return *(DriveMapView*)(void*)&DAT_0087F7E8; }

// Foot slots called by Drive bodies (__thiscall through `[reg+slot]`); the
// other entries are placeholders that keep the observed slot offsets.
struct DriveFootVirtuals
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual void vf_020();
    virtual void vf_024();
    virtual void vf_028();
    virtual void vf_02C();
    virtual void vf_030();
    virtual void vf_034();
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual void vf_048();
    virtual void vf_04C();
    virtual void vf_050();
    virtual void vf_054();
    virtual void vf_058();
    virtual void vf_05C();
    virtual void vf_060();
    virtual void vf_064();
    virtual void vf_068();
    virtual void vf_06C();
    virtual void vf_070();
    virtual void vf_074();
    virtual void vf_078();
    virtual void vf_07C();
    virtual void vf_080();
    virtual DriveTypeView* vf_084();
    virtual void vf_088();
    virtual void vf_08C();
    virtual void vf_090();
    virtual void vf_094();
    virtual void vf_098();
    virtual void vf_09C();
    virtual void vf_0A0();
    virtual void vf_0A4();
    virtual void vf_0A8();
    virtual void vf_0AC();
    virtual void vf_0B0();
    virtual void vf_0B4();
    virtual void vf_0B8();
    virtual void vf_0BC();
    virtual void vf_0C0();
    virtual void vf_0C4();
    virtual void vf_0C8();
    virtual void vf_0CC();
    virtual void vf_0D0();
    virtual void vf_0D4();
    virtual void vf_0D8();
    virtual void vf_0DC();
    virtual void vf_0E0();
    virtual void vf_0E4();
    virtual void vf_0E8();
    virtual void vf_0EC();
    virtual void vf_0F0(LocoCoord* coord);
    virtual void vf_0F4(const LocoCoord* coord);
    virtual void vf_0F8();
    virtual void vf_0FC();
    virtual void vf_100();
    virtual void vf_104();
    virtual void vf_108();
    virtual void vf_10C();
    virtual void vf_110();
    virtual void vf_114();
    virtual void vf_118();
    virtual void vf_11C();
    virtual void vf_120();
    virtual void vf_124();
    virtual void vf_128();
    virtual void vf_12C();
    virtual void vf_130();
    virtual void vf_134();
    virtual void vf_138();
    virtual void vf_13C();
    virtual void vf_140();
    virtual void vf_144();
    virtual void vf_148();
    virtual void vf_14C();
    virtual void vf_150();
    virtual void vf_154();
    virtual void vf_158();
    virtual void vf_15C();
    virtual void vf_160();
    virtual void vf_164();
    virtual void vf_168();
    virtual void vf_16C();
    virtual void vf_170();
    virtual void vf_174();
    virtual void vf_178();
    virtual void vf_17C();
    virtual void vf_180();
    virtual void vf_184();
    virtual void vf_188();
    virtual void vf_18C();
    virtual void vf_190();
    virtual void vf_194();
    virtual void vf_198();
    virtual void vf_19C();
    virtual void vf_1A0();
    virtual void vf_1A4();
    virtual void vf_1A8();
    virtual void vf_1AC();
    virtual void vf_1B0();
    virtual void vf_1B4();
    virtual void vf_1B8();
    virtual DriveCellView* vf_1BC();
    virtual void vf_1C0();
    virtual void vf_1C4();
    virtual void vf_1C8();
    virtual void vf_1CC();
    virtual int vf_1D0();
    virtual bool vf_1D4();
    virtual bool vf_1D8();
    virtual void vf_1DC();
    virtual void vf_1E0();
    virtual void vf_1E4();
    virtual void vf_1E8();
    virtual void vf_1EC();
    virtual void vf_1F0();
    virtual void vf_1F4();
    virtual void vf_1F8();
    virtual void vf_1FC();
    virtual void vf_200();
    virtual void vf_204();
    virtual void vf_208();
    virtual void vf_20C();
    virtual void vf_210();
    virtual void vf_214();
    virtual void vf_218();
    virtual void vf_21C();
    virtual void vf_220();
    virtual void vf_224();
    virtual void vf_228();
    virtual void vf_22C();
    virtual void vf_230();
    virtual void vf_234();
    virtual void vf_238();
    virtual void vf_23C();
    virtual void vf_240();
    virtual void vf_244();
    virtual void vf_248();
    virtual void vf_24C();
    virtual void vf_250();
    virtual void vf_254();
    virtual void vf_258();
    virtual void vf_25C();
    virtual void vf_260();
    virtual void vf_264();
    virtual void vf_268();
    virtual void vf_26C();
    virtual void vf_270();
    virtual void vf_274();
    virtual void vf_278();
    virtual void vf_27C();
    virtual void vf_280();
    virtual void vf_284();
    virtual void vf_288();
    virtual void vf_28C();
    virtual void vf_290();
    virtual void vf_294();
    virtual void vf_298();
    virtual void vf_29C();
    virtual void vf_2A0();
    virtual void vf_2A4();
    virtual void vf_2A8();
    virtual void vf_2AC();
    virtual void vf_2B0();
    virtual void vf_2B4();
    virtual void vf_2B8();
    virtual void vf_2BC();
    virtual void vf_2C0();
    virtual void vf_2C4();
    virtual void vf_2C8();
    virtual void vf_2CC();
    virtual void vf_2D0();
    virtual void vf_2D4();
    virtual void vf_2D8();
    virtual void vf_2DC();
    virtual void vf_2E0();
    virtual void vf_2E4();
    virtual void vf_2E8();
    virtual void vf_2EC();
    virtual void vf_2F0();
    virtual void vf_2F4();
    virtual void vf_2F8();
    virtual void vf_2FC();
    virtual void vf_300();
    virtual void vf_304();
    virtual void vf_308();
    virtual void vf_30C();
    virtual void vf_310();
    virtual void vf_314();
    virtual void vf_318();
    virtual void vf_31C();
    virtual void vf_320();
    virtual void vf_324();
    virtual void vf_328();
    virtual void vf_32C();
    virtual void vf_330();
    virtual void vf_334();
    virtual void vf_338();
    virtual void vf_33C();
    virtual void vf_340();
    virtual void vf_344();
    virtual void vf_348();
    virtual void vf_34C();
    virtual void vf_350();
    virtual void vf_354();
    virtual void vf_358();
    virtual void vf_35C();
    virtual void vf_360();
    virtual void vf_364();
    virtual void vf_368();
    virtual void vf_36C();
    virtual void vf_370();
    virtual void vf_374();
    virtual void vf_378();
    virtual bool vf_37C();
    virtual bool vf_380();
    virtual void vf_384();
    virtual void vf_388();
    virtual void vf_38C();
    virtual void vf_390();
    virtual void vf_394();
    virtual void vf_398();
    virtual void vf_39C();
    virtual void vf_3A0();
    virtual void vf_3A4();
    virtual void vf_3A8();
    virtual void vf_3AC();
    virtual void vf_3B0();
    virtual void vf_3B4();
    virtual void vf_3B8();
    virtual void vf_3BC();
    virtual void vf_3C0();
    virtual void vf_3C4();
    virtual void vf_3C8();
    virtual void vf_3CC();
    virtual void vf_3D0();
    virtual void vf_3D4();
    virtual void vf_3D8();
    virtual void vf_3DC();
    virtual void vf_3E0();
    virtual void vf_3E4();
    virtual void vf_3E8();
    virtual void vf_3EC();
    virtual void vf_3F0();
    virtual void vf_3F4();
    virtual void vf_3F8();
    virtual void vf_3FC();
    virtual void vf_400();
    virtual void vf_404();
    virtual void vf_408();
    virtual void vf_40C();
    virtual void vf_410();
    virtual void vf_414();
    virtual void vf_418();
    virtual void vf_41C();
    virtual void vf_420();
    virtual void vf_424();
    virtual void vf_428();
    virtual void vf_42C();
    virtual void vf_430();
    virtual void vf_434();
    virtual void vf_438();
    virtual void vf_43C();
    virtual void vf_440();
    virtual void vf_444();
    virtual void vf_448();
    virtual void vf_44C();
    virtual void vf_450();
    virtual void vf_454();
    virtual void vf_458();
    virtual void vf_45C();
    virtual void vf_460();
    virtual void vf_464();
    virtual void vf_468();
    virtual void vf_46C();
    virtual void vf_470();
    virtual void vf_474();
    virtual void vf_478();
    virtual void vf_47C();
    virtual void vf_480(int a, int b);
    virtual bool vf_484(int a, int b);
    virtual void vf_488();
    virtual void vf_48C();
    virtual void vf_490();
    virtual void vf_494();
    virtual void vf_498();
    virtual void vf_49C();
    virtual void vf_4A0();
    virtual void vf_4A4();
    virtual void vf_4A8();
    virtual void vf_4AC();
    virtual void vf_4B0();
    virtual void vf_4B4();
    virtual void vf_4B8();
    virtual void vf_4BC();
    virtual void vf_4C0();
    virtual void vf_4C4();
    virtual void vf_4C8();
    virtual void vf_4CC();
    virtual void vf_4D0();
    virtual void vf_4D4();
    virtual void vf_4D8();
    virtual void vf_4DC();
    virtual void vf_4E0();
    virtual void vf_4E4();
    virtual void vf_4E8();
    virtual void vf_4EC();
    virtual void vf_4F0();
    virtual void vf_4F4();
    virtual void vf_4F8();
    virtual void vf_4FC();
    virtual void vf_500();
    virtual void vf_504();
    virtual void vf_508();
    virtual void vf_50C();
    virtual void vf_510();
    virtual void vf_514();
    virtual void vf_518();
    virtual void vf_51C();
    virtual void vf_520();
    virtual void vf_524();
    virtual void vf_528();
    virtual void vf_52C();
    virtual void vf_530();
    virtual void vf_534();
    virtual int vf_538();
};
GG_STATIC_ASSERT(sizeof(DriveFootVirtuals) == 4);

struct DriveFootView : DriveFootVirtuals
{
    char            unknown_004[0x081 - 0x004];
    unsigned char   unknown_081;         // +0x081 ForceTrack `[EAX+0x81]`
    char            unknown_082[0x090 - 0x082];
    unsigned char   unknown_090;         // +0x090 ForceTrack `[EAX+0x90]`
    char            unknown_091[0x09C - 0x091];
    LocoCoord       Location;            // +0x09C IsMoving / HeadToCoord
    char            unknown_0A8[0x328 - 0x0A8];
    float           unknown_328;         // +0x328 0x4AFED0 `FLD [ECX+0x328]`
    float           unknown_32C;         // +0x32C 0x4AFED0 `FLD [ECX+0x32C]`
    char            unknown_330[0x388 - 0x330];
    DriveFacingView PrimaryFacing;       // +0x388 DoTurn `ADD ECX,0x388`
    char            unknown_3A0[0x598 - 0x3A0];
    int             unknown_598;         // +0x598 0x4B4890 `[ECX+0x598]`
    char            unknown_59C[0x5E0 - 0x59C];
    int             unknown_5E0;         // +0x5E0 WillJumpTracks `[EAX+0x5E0]`
    char            unknown_5E4[0x674 - 0x5E4];
    ILocomotionPtr  Locomotor;           // +0x674 StopMoving `[ESI+0x674]`
    char            unknown_678[0x6AD - 0x678];
    unsigned char   unknown_6AD;         // +0x6AD IsOkToEnd `[EDX+0x6AD]`
    char            unknown_6AE[0x6C8 - 0x6AE];
    DriveFootView*  unknown_6C8;         // +0x6C8 StopMoving chain link
    char            unknown_6CC[0x6D0 - 0x6CC];
    unsigned char   unknown_6D0;         // +0x6D0 StopMoving `[EAX+0x6D0]`

    // Inline by-value read of Location: IsMoving 0x4AFB80 copies all three
    // dwords to a stack temporary once per use.
    LocoCoord GetLocation() const { return Location; }

    // FUNCTION: GAMEMD 0x4DF0D0 (decl; reloc) - __thiscall, 0x4B4890.
    void FUN_004DF0D0();
};
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_081) == 0x081);
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_090) == 0x090);
GG_STATIC_ASSERT(offsetof(DriveFootView, Location) == 0x09C);
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_328) == 0x328);
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_32C) == 0x32C);
GG_STATIC_ASSERT(offsetof(DriveFootView, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_598) == 0x598);
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_5E0) == 0x5E0);
GG_STATIC_ASSERT((size_t)&reinterpret_cast<const char&>(((DriveFootView*)0)->Locomotor) == 0x674);
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_6AD) == 0x6AD);
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_6C8) == 0x6C8);
GG_STATIC_ASSERT(offsetof(DriveFootView, unknown_6D0) == 0x6D0);

// Track tables. 0x7E7B28: 12-byte entries indexed by TrackNumber
// (`LEA ECX,[EAX+EAX*2]; MOVSX EAX,[ECX*4+0x7E7B28]` at 0x4B0B1F).
struct DriveTrackEntry
{
    char         unknown_0;              // +0 control index (0x4B0B22)
    char         unknown_1;              // +1 short-track control index (0x4B4B35)
    char         unknown_2[2];
    unsigned char unknown_4;             // +4 facing nibble (0x4B4B44)
    char         unknown_5[3];
    unsigned int unknown_8;              // +8 flag bits 1/2/4 (0x4B4787)
};
GG_STATIC_ASSERT(offsetof(DriveTrackEntry, unknown_4) == 4);
GG_STATIC_ASSERT(offsetof(DriveTrackEntry, unknown_8) == 8);
GG_STATIC_ASSERT(sizeof(DriveTrackEntry) == 12);

// One point of a control track: X, Y and a facing (0x4B0B50 reads +8).
struct DriveTrackPoint
{
    int X;
    int Y;
    int Facing;
};
GG_STATIC_ASSERT(sizeof(DriveTrackPoint) == 12);

// 0x7E7A28: 16-byte entries (`SHL EAX,4; MOV ECX,[EAX+0x7E7A28]` at 0x4B0B32).
struct DriveTrackControl
{
    DriveTrackPoint* Points;             // +0x0
    int              unknown_4;          // +0x4 (0x4B4B5E)
    int              unknown_8;          // +0x8 (0x4B4B8F)
    int              unknown_C;          // +0xC jump point index (0x4B0B3B)
};
GG_STATIC_ASSERT(offsetof(DriveTrackControl, unknown_C) == 0xC);
GG_STATIC_ASSERT(sizeof(DriveTrackControl) == 0x10);

// GLOBAL: GAMEMD 0x7E7B28
extern DriveTrackEntry DriveTrackEntries_007E7B28[];
// GLOBAL: GAMEMD 0x7E7A28
extern DriveTrackControl DriveTrackControls_007E7A28[];

#endif  // GG_MATCH_MOVEMENT_DRIVE_SUPPORT_VIEWS_H
