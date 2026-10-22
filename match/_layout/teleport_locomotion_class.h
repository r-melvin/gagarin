// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TeleportLocomotionClass::TeleportLocomotionClass 0x00718000, which
//   chains the LocomotionClass base constructor 0x0055A6C0 and writes every one
//   of its own fields. Every offset below was read back out of the user's retail
//   gamemd.exe v1.001 from the citing instruction beside it.
//
//   sizeof = 0x4C, proven twice and independently:
//     * the single allocation site - `PUSH 0x4C` @0x006C4C3C, `CALL operator new
//       (0x007C8E17)` @0x006C4C3E, `MOV ECX,EAX`, `CALL 0x00718000` @0x006C4C4C;
//     * the class's own virtual size accessor, persist-vtable (0x007F50CC) slot
//       +0x24 = 0x0071A120, whose entire body is `MOV EAX,0x4C / RET`.
//   The layout CLOSES EXACTLY: the last member is the dword at 0x48
//   (@0x0071805B) and 0x48+4 = 0x4C = sizeof, with no tail.
//
//   RTTI: ".?AVTeleportLocomotionClass@@", type descriptor 0x00844538, THREE
//   complete object locators - 0x0080C1E0 (base offset 0, vtable 0x007F50CC,
//   IPersistStream), 0x0080C178 (base offset 4, vtable 0x007F5000, ILocomotion)
//   and 0x0080C160 (base offset 0x18, vtable 0x007F4FDC, IPiggyback). So 0x18 is
//   a VPTR and this class cannot share FlyLocomotionClass's two-locator base;
//   its own data starts at 0x1C.
//
//   The class is modelled on the shared COM spine of match/movement/loco_base.h
//   (LocomotionClass + IPiggyback), as DropPodLocomotionClass is. Table
//   contents are read from the binary:
//     IPersistStream 0x7F50CC: QI 0x719E30, AddRef 0x71A0E0, Release 0x71A0F0,
//       GetClassID 0x719C60, IsDirty 0x4B4C30 (inherited), Load 0x719CA0, Save
//       0x719D40, GetSizeMax 0x55AB40 (inherited), deleting destructor 0x71A130,
//       Size 0x71A120, then two slots of its own: 10 = 0x719BF0 (__stdcall,
//       RET 4) and 11 = 0x718090 (__thiscall; returns !IsMoving()).
//     ILocomotion 0x7F5000: thunks 0x71A160/0x71A170/0x71A180, IsMoving
//       0x718080, Destination 0x7180A0, Process 0x7192F0, MoveTo 0x718100,
//       StopMoving 0x718230, DoTurn 0x7192C0, InWhichLayer 0x719E20,
//       MarkAllOccupationBits 0x71A090; every other slot is LocomotionClass's.
//     IPiggyback 0x7F4FDC: thunks 0x71A190/0x71A1A0/0x71A1B0, BeginPiggyback
//       0x719E90, EndPiggyback 0x719EE0, IsOkToEnd 0x719F30, PiggybackCLSID
//       0x719F80, IsPiggybacking 0x71A100.
//
//   INTERFACE-RELATIVE READS are marked "(if+N)"; object offset = N+4.
#ifndef GG_MATCH_LAYOUT_TELEPORT_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_TELEPORT_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../movement/loco_base.h"
#include "../movement/loco_com.h"
#include "../core/frame_counter.h"

// The unit's "no coordinate" value: three dwords zeroed by its initialiser
// 0x717FA0 and copied into Destination / unknown_28 by the constructor.
// GLOBAL: GAMEMD 0xB0EBF8
extern LocoCoord DAT_00B0EBF8;

// Coordinate equality, compared member by member through a reference (the
// `LEA EAX,[ESI+0x24]` then [EAX], [EAX+4], [EAX+8] of MoveTo 0x718100).
inline bool TeleportSameCoord(const LocoCoord& a, const LocoCoord& b)
{
    return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
}

// A frame timer (StartTime, an unwritten clock slot, TimeLeft): the
// constructor and Load store the frame counter 0xA8ED84 to +0 and 0 to +8;
// 0x719BF0 reads it back as "frames left".
struct TeleportTimer
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    TeleportTimer() : StartTime(CurrentFrame), TimeLeft(0) {}
    TeleportTimer(int time) : StartTime(CurrentFrame), TimeLeft(time) {}

    int GetTimeLeft() const
    {
        int left = TimeLeft;
        if (StartTime != -1) {
            int elapsed = CurrentFrame - StartTime;
            if (elapsed < left)
                left -= elapsed;
            else
                left = 0;
        }
        return left;
    }
};
GG_STATIC_ASSERT(offsetof(TeleportTimer, StartTime) == 0x00);
GG_STATIC_ASSERT(offsetof(TeleportTimer, TimeLeft)  == 0x08);
GG_STATIC_ASSERT(sizeof(TeleportTimer)              == 0xC);

// The facing at FootClass+0x388 and its direction argument (one dword copied
// to the stack and passed by address to 0x4C9220, see DoTurn 0x7192C0).
struct TeleportDir
{
    unsigned int Raw;   // +0x00
    TeleportDir(unsigned long raw) : Raw(raw) {}
};
GG_STATIC_ASSERT(sizeof(TeleportDir) == 4);

struct TeleportFacingView
{
    char opaque[0x18];

    // FUNCTION: GAMEMD 0x4C9220 (decl; reloc) -- sets the desired facing.
    void SetDesired(const TeleportDir& dir);
};
GG_STATIC_ASSERT(sizeof(TeleportFacingView) == 0x18);

struct TeleportCellView;
struct TeleportHouseView;

// A cell index (X, Y). It has a constructor, so calls return it through a
// hidden pointer (0x56DC20, the foot's slot 0x1B8).
struct TeleportCell
{
    short X;   // +0x00
    short Y;   // +0x02

    TeleportCell() {}
};
GG_STATIC_ASSERT(sizeof(TeleportCell) == 4);

// The cell of a coordinate (lepton / 256 per axis), read through the reference.
inline TeleportCell TeleportCellOf(const LocoCoord& where)
{
    TeleportCell cell;
    cell.X = (short)(where.X / 256);
    cell.Y = (short)(where.Y / 256);
    return cell;
}

inline bool TeleportSameCell(const TeleportCell& a, const TeleportCell& b)
{
    return a.X == b.X && a.Y == b.Y;
}

// An object with a virtual destructor in slot 8 (FootClass+0x2D8 is deleted
// through it: `PUSH 1; CALL [EDX+0x20]`).
struct TeleportDeletable
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual ~TeleportDeletable();

    // FUNCTION: GAMEMD 0x6B0AE0 (decl; reloc) -- __thiscall, RET 8.
    void FUN_006B0AE0(void* a, void* b);
};

// The flags byte at ObjectClass+0x14 (the AbstractClass flags; bit 2 marks a foot).
struct TeleportObjectFlags
{
    bool IsTechno     : 1;   // bit 0
    bool unknown_14_1 : 1;   // bit 1
    bool IsFoot       : 1;   // bit 2
};
GG_STATIC_ASSERT(sizeof(TeleportObjectFlags) == 1);

// A techno type, as this class reads it.
struct TeleportTypeView
{
    char unknown_000[0xA0];
    int  unknown_0A0;                      // +0x0A0 @0x00718349
    char unknown_0A4[0x410 - 0xA4];
    char unknown_410;                      // +0x410 @0x00718887
    char unknown_411[0x574 - 0x411];
    int  unknown_574;                      // +0x574 a sound (@0x007196D2)
    int  unknown_578;                      // +0x578 a sound (@0x007195EE)
    char unknown_57C[0x5B4 - 0x57C];
    int  unknown_5B4;                      // +0x5B4 @0x00718505 (a movement class)
    char unknown_5B8[0x67C - 0x5B8];
    int  unknown_67C;                      // +0x67C @0x00718871
    char unknown_680[0xCCE - 0x680];
    char unknown_CCE;                      // +0xCCE @0x00718821
    char unknown_CCF[0xE0E - 0xCCF];
    char unknown_E0E;                      // +0xE0E @0x00719596 (a unit type)
};
GG_STATIC_ASSERT(offsetof(TeleportTypeView, unknown_0A0) == 0x0A0);
GG_STATIC_ASSERT(offsetof(TeleportTypeView, unknown_410) == 0x410);
GG_STATIC_ASSERT(offsetof(TeleportTypeView, unknown_5B4) == 0x5B4);
GG_STATIC_ASSERT(offsetof(TeleportTypeView, unknown_67C) == 0x67C);
GG_STATIC_ASSERT(offsetof(TeleportTypeView, unknown_CCE) == 0xCCE);
GG_STATIC_ASSERT(offsetof(TeleportTypeView, unknown_574) == 0x574);
GG_STATIC_ASSERT(offsetof(TeleportTypeView, unknown_578) == 0x578);
GG_STATIC_ASSERT(offsetof(TeleportTypeView, unknown_E0E) == 0xE0E);

// The object at FootClass+0x694 and the one it holds at +0x69C (0x62A4A0 is
// called on the latter).
struct TeleportObj69CView
{
    // FUNCTION: GAMEMD 0x62A4A0 (decl; reloc) -- __thiscall.
    void FUN_0062A4A0();
};
struct TeleportObj694View
{
    char                unknown_000[0x69C];
    TeleportObj69CView* unknown_69C;       // +0x69C @0x007195C9
};
GG_STATIC_ASSERT(offsetof(TeleportObj694View, unknown_69C) == 0x69C);

// The linked FootClass, as the bodies of this class use it. Slot offsets are
// the `CALL [reg+N]` displacements of each caller; members carry the offset
// of the instruction that reads them.
struct TeleportFootView
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
    virtual int WhatAmI();   // +0x02C
    virtual void vf_030();
    virtual void vf_034();
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual LocoCoord vf_048();   // +0x048
    virtual LocoCoord vf_04C(int a);   // +0x04C
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
    virtual TeleportTypeView* vf_084();   // +0x084
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
    virtual bool vf_0BC(int a);   // +0x0BC
    virtual void vf_0C0();
    virtual void vf_0C4();
    virtual void vf_0C8();
    virtual void vf_0CC();
    virtual void vf_0D0();
    virtual void vf_0D4();
    virtual void vf_0D8();
    virtual void vf_0DC();
    virtual void vf_0E0(void* a);   // +0x0E0
    virtual void vf_0E4(void* a);   // +0x0E4
    virtual void vf_0E8();
    virtual void vf_0EC();
    virtual void vf_0F0(const LocoCoord* coord);   // +0x0F0
    virtual void vf_0F4(const LocoCoord* coord);   // +0x0F4
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
    virtual void vf_124(int a);   // +0x124
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
    virtual bool vf_160();   // +0x160
    virtual void vf_164();
    virtual void vf_168();
    virtual int vf_16C(int* damage, int a, void* warhead, int b, int c, int d, int e);   // +0x16C
    virtual void vf_170();
    virtual void vf_174();
    virtual void vf_178();
    virtual void vf_17C();
    virtual void vf_180();
    virtual int vf_184();   // +0x184
    virtual void vf_188();
    virtual void vf_18C(int a);   // +0x18C
    virtual void vf_190();
    virtual void vf_194();
    virtual void vf_198();
    virtual void vf_19C();
    virtual void vf_1A0();
    virtual void vf_1A4();
    virtual void vf_1A8();
    virtual int vf_1AC(TeleportCellView* cell, int a, int b, int c, int d);   // +0x1AC
    virtual void vf_1B0();
    virtual void vf_1B4(const LocoCoord* coord);   // +0x1B4
    virtual TeleportCell vf_1B8();   // +0x1B8
    virtual void vf_1BC();
    virtual void vf_1C0();
    virtual void vf_1C4();
    virtual void vf_1C8();
    virtual void vf_1CC(int a);   // +0x1CC
    virtual void vf_1D0();
    virtual bool vf_1D4();   // +0x1D4
    virtual bool vf_1D8();   // +0x1D8
    virtual void vf_1DC();
    virtual void vf_1E0();
    virtual void vf_1E4();
    virtual void vf_1E8();
    virtual void vf_1EC();   // +0x1EC
    virtual void vf_1F0();
    virtual void vf_1F4();
    virtual void vf_1F8();
    virtual void vf_1FC();
    virtual bool vf_200();   // +0x200
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
    virtual bool vf_37C();   // +0x37C
    virtual bool vf_380();   // +0x380
    virtual void vf_384();
    virtual void vf_388();
    virtual void vf_38C();
    virtual void vf_390();
    virtual void vf_394();
    virtual void vf_398();
    virtual void vf_39C();
    virtual void vf_3A0();   // +0x3A0
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
    virtual void vf_480(int a, int b);   // +0x480
    virtual void vf_484(int a, int b);   // +0x484

    // FUNCTION: GAMEMD 0x70F770 (decl; reloc) -- __thiscall, result unused (0x719BF0).
    void FUN_0070F770();
    // FUNCTION: GAMEMD 0x709480 (decl; reloc) -- __thiscall, bool (0x719BF0).
    bool FUN_00709480();
    // FUNCTION: GAMEMD 0x70C610 (decl; reloc) -- __thiscall, RET 4.
    void FUN_0070C610(int a);
    // FUNCTION: GAMEMD 0x70D4A0 (decl; reloc) -- __thiscall.
    void FUN_0070D4A0();

    // The location at +0x9C, by value.
    LocoCoord Coord_09C() const { return Location; }

    char  unknown_004[0x14 - 0x004];
    TeleportObjectFlags Flags;             // +0x014 IsFoot is bit 2 (@0x0071838B)
    char  unknown_015[0x30 - 0x15];
    TeleportFootView* unknown_030;         // +0x030 the next object in the cell (@0x0071842F)
    char  unknown_034[0x8C - 0x34];
    char  unknown_08C;                     // +0x08C @0x007186FA
    char  unknown_08D[0x90 - 0x8D];
    char  unknown_090;                     // +0x090 @0x00719ACC
    char  unknown_091[0x9C - 0x91];
    LocoCoord Location;                    // +0x09C copied by HeadToCoord 0x55ACA0
    char  unknown_0A8[0x1F8 - 0xA8];
    char  unknown_1F8;                     // +0x1F8 MoveTo `MOV AL,[ECX+0x1f8]` @0x0071816F
    char  unknown_1F9[0x21C - 0x1F9];
    TeleportHouseView* unknown_21C;        // +0x21C the owning house (@0x007188A0)
    char  unknown_220[0x270 - 0x220];
    char  unknown_270;                     // +0x270 @0x007197D0
    char  unknown_271;                     // +0x271 0x719BF0 clears it @0x00719C15
    char  unknown_272[0x27C - 0x272];
    char  unknown_27C;                     // +0x27C IsOkToEnd @0x00719F54
    char  unknown_27D[0x280 - 0x27D];
    int   unknown_280;                     // +0x280 @0x00719313
    int   unknown_284;                     // +0x284 @0x00719983
    LocoCoord unknown_288;                 // +0x288 @0x007186BE / @0x0071863D
    char  unknown_294[0x2B4 - 0x294];
    int   unknown_2B4;                     // +0x2B4 0x719BF0 @0x00719C1F
    char  unknown_2B8[0x2D8 - 0x2B8];
    TeleportDeletable* unknown_2D8;        // +0x2D8 @0x00718980
    char  unknown_2DC[0x388 - 0x2DC];
    TeleportFacingView PrimaryFacing;           // +0x388 DoTurn `ADD ECX,0x388` @0x007192D4
    char  unknown_3A0[0x3CD - 0x3A0];
    char  unknown_3CD;                     // +0x3CD @0x0071896B
    char  unknown_3CE[0x3D5 - 0x3CE];
    char  unknown_3D5;                     // +0x3D5 @0x00719A99
    char  unknown_3D6[0x428 - 0x3D6];
    void* unknown_428;                     // +0x428 @0x007189C1
    void* unknown_42C;                     // +0x42C @0x007189DD
    char  unknown_430[0x5A4 - 0x430];
    TeleportFootView* unknown_5A4;         // +0x5A4 MoveTo @0x00718213 (an object; WhatAmI read @0x00718CFC)
    char  unknown_5A8[0x694 - 0x5A8];
    TeleportObj694View* unknown_694;       // +0x694 @0x007195BF
    char  unknown_698[0x6AD - 0x698];
    char  unknown_6AD;                     // +0x6AD IsOkToEnd @0x00719F65
    char  unknown_6AE[0x6C4 - 0x6AE];
    TeleportTypeView* unknown_6C4;         // +0x6C4 a unit's type (@0x00719590)
};
GG_STATIC_ASSERT(offsetof(TeleportFootView, Flags) == 0x014);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_030) == 0x030);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_08C) == 0x08C);
GG_STATIC_ASSERT(offsetof(TeleportFootView, Location) == 0x09C);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_288) == 0x288);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_1F8) == 0x1F8);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_270) == 0x270);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_271) == 0x271);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_27C) == 0x27C);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_2B4) == 0x2B4);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_2D8) == 0x2D8);
GG_STATIC_ASSERT(offsetof(TeleportFootView, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_3CD) == 0x3CD);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_428) == 0x428);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_42C) == 0x42C);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_5A4) == 0x5A4);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_6AD) == 0x6AD);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_090) == 0x090);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_280) == 0x280);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_284) == 0x284);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_3D5) == 0x3D5);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_5A4) == 0x5A4);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_694) == 0x694);
GG_STATIC_ASSERT(offsetof(TeleportFootView, unknown_6C4) == 0x6C4);

// VTABLE: GAMEMD 0x7F50CC (IPersistStream side)
// VTABLE: GAMEMD 0x7F5000 (ILocomotion side, +0x04)
// VTABLE: GAMEMD 0x7F4FDC (IPiggyback side, +0x18)
class TeleportLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
    TeleportLocomotionClass();
    TeleportLocomotionClass(int) : LocomotionClass(0) {}

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0x719E30
    virtual ULONG   __stdcall AddRef();                                   // 0x71A0E0
    virtual ULONG   __stdcall Release();                                  // 0x71A0F0

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 0x719C60
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 0x719CA0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 0x719D40
    virtual int Size();                                                   // 0x71A120
    virtual void __stdcall vf_10();                                       // 0x719BF0
    virtual bool vf_11();                                                 // 0x718090

    virtual bool __stdcall IsMoving();                                    // 0x718080
    virtual LocoCoord __stdcall Destination();                            // 0x7180A0
    virtual bool __stdcall Process();                                     // 0x7192F0
    virtual void __stdcall MoveTo(LocoCoord to);                          // 0x718100
    virtual void __stdcall StopMoving();                                  // 0x718230
    virtual void __stdcall DoTurn(unsigned long dir);                     // 0x7192C0
    virtual int __stdcall InWhichLayer();                                 // 0x719E20
    virtual void __stdcall MarkAllOccupationBits(int mark);               // 0x71A090

    virtual HRESULT __stdcall BeginPiggyback(ILocomotion* loco);          // 0x719E90
    virtual HRESULT __stdcall EndPiggyback(ILocomotion** out);            // 0x719EE0
    virtual bool __stdcall IsOkToEnd();                                   // 0x719F30
    virtual HRESULT __stdcall PiggybackCLSID(CLSID* out);                 // 0x719F80
    virtual bool __stdcall IsPiggybacking();                              // 0x71A100

    // FUNCTION: GAMEMD 0x718260 (declaration)
    bool FUN_00718260(LocoCoord coord, bool flag);
    // FUNCTION: GAMEMD 0x7187A0 (declaration)
    void FUN_007187A0(LocoCoord coord);
    // FUNCTION: GAMEMD 0x718B70 (declaration) -- fills unknown_28 for a move
    // order (called by MoveTo with the target coordinate).
    bool FUN_00718B70(const LocoCoord* to);

    TeleportFootView* Foot() const { return (TeleportFootView*)LinkedTo; }

    LocoCoord      DestCoord;     // +0x1C ctor @0x0071800E; copied out by Destination 0x7180A0
    LocoCoord      unknown_28;    // +0x28 ctor @0x00718023; filled by FUN_00718B70, read by MoveTo
    bool           Moving;        // +0x34 read by IsMoving 0x718080
    char           unknown_35;    // +0x35 ctor @0x00718046; read by IsOkToEnd (if+0x1D)
    char           unknown_36;    // +0x36 ctor @0x00718049; cleared by StopMoving
    int            unknown_38;    // +0x38 ctor @0x0071804C; counted up by 0x719BF0
    TeleportTimer  unknown_3C;    // +0x3C ctor @0x00718055 / @0x00718058
    ILocomotionPtr Piggybackee;   // +0x48 ctor @0x0071805B; last member, 0x48+4 = sizeof
};

GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, DestCoord)    == 0x1C);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_28)   == 0x28);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, Moving)       == 0x34);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_35)   == 0x35);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_36)   == 0x36);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_38)   == 0x38);
GG_STATIC_ASSERT(offsetof(TeleportLocomotionClass, unknown_3C)   == 0x3C);
GG_STATIC_ASSERT((size_t)&reinterpret_cast<const char&>(((TeleportLocomotionClass*)0)->Piggybackee) == 0x48);
GG_STATIC_ASSERT(sizeof(TeleportLocomotionClass) == 0x4C);

#endif  // GG_MATCH_LAYOUT_TELEPORT_LOCOMOTION_CLASS_H
