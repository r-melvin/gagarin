// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   RTTI: primary vtable 0x7F5180 (IPersistStream), 0x7F5164 (IRTTITypeInfo,
//   +0x04), 0x7F515C (INoticeSink, +0x08), 0x7F5154 (INoticeSource, +0x0C),
//   stored by every constructor (0x71A450, 0x71A4E0, 0x71A5A0). Size 0x50 from
//   slot 12 (0x71B190 returns 0x50); slot 11 (0x71B1A0) returns 0x46.
//   Fields from the constructor 0x71A4E0 (one argument stored at +0x24, the
//   rest cleared) and from Load 0x71A660, which swizzles the six pointers at
//   +0x24, +0x28, +0x40, +0x44, +0x38 and +0x3C.
//
//   The older address-local views (combat/temporal_class_methods.h,
//   temporal_class_let_go_methods.h, temporal_class_warp_target_methods.h)
//   disagree about which of +0x40 / +0x44 is the forward link; nothing in this
//   header's bodies decides it, so both keep placeholder names here.
//   GetWarpPerStep and Detach are declared under the names their matched
//   definitions in combat/temporal_class_methods.cpp carry, so the calls
//   bind to them. Those bodies cannot move into this unit: under its /Ob2
//   (needed for the initialisers) cl expands GetWarpPerStep into 0x71A760,
//   which retail calls.
#ifndef GG_MATCH_LAYOUT_TEMPORAL_CLASS_H
#define GG_MATCH_LAYOUT_TEMPORAL_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "../core/vector_class.h"
#include "../core/frame_counter.h"

struct Obj_004A1D30;
struct TemporalTechnoView;

struct TemporalCoord
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(TemporalCoord) == 0xC);

// A frame timer: StartTime from the frame counter 0xA8ED84, an unwritten
// clock slot, TimeLeft (the 0x71A450 / 0x71A4E0 stores to +0x2C / +0x34).
struct TemporalTimer
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    TemporalTimer() : StartTime(CurrentFrame), TimeLeft(0) {}
    TemporalTimer(const AbstractNoInit&) {}
};
GG_STATIC_ASSERT(offsetof(TemporalTimer, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(TemporalTimer) == 0xC);

// The weapon entry returned by the owner's slot 0x3F8; its first dword is the
// weapon type, whose +0xA4 dword 0x71A760 caches at TemporalClass+0x4C.
struct TemporalWeaponType
{
    char unknown_00[0xA4];
    int  unknown_A4;         // +0xA4 @0x0071A87B
};
GG_STATIC_ASSERT(offsetof(TemporalWeaponType, unknown_A4) == 0xA4);

struct TemporalWeaponSlot
{
    TemporalWeaponType* Type;   // +0x00 @0x0071A876
};

struct TemporalHouseView
{
    char unknown_000[0x1FC];
    char unknown_1FC;                    // +0x1FC @0x0071AD17
    char unknown_1FD[0x5778 - 0x1FD];
    char unknown_5778;                   // +0x5778 @0x0071AD04

    // FUNCTION: GAMEMD 0x4F93E0 (decl; reloc) -- __thiscall, RET 4.
    void FUN_004F93E0(TemporalTechnoView* building);
};
GG_STATIC_ASSERT(offsetof(TemporalHouseView, unknown_1FC) == 0x1FC);
GG_STATIC_ASSERT(offsetof(TemporalHouseView, unknown_5778) == 0x5778);

class TemporalClass;
struct TemporalHouseView;

// A techno type, as this class reads it (slot 0x84 takes the house).
struct TemporalTypeView
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
    virtual int vf_084(TemporalHouseView* house);   // +0x084

    char unknown_004[0xA0 - 0x04];
    int  unknown_0A0;                    // +0x0A0 @0x0071AFA9
    char unknown_0A4[0x232 - 0xA4];
    char unknown_232;                    // +0x232 @0x0071B07C
    char unknown_233[0xC8E - 0x233];
    char unknown_C8E;                    // +0xC8E @0x0071A922
    char unknown_C8F[0xCD5 - 0xC8F];
    char unknown_CD5;                    // +0xCD5 @0x0071B0FC
    char unknown_CD6[0xE0E - 0xCD6];
    char unknown_E0E;                    // +0xE0E @0x0071AFF1 (a unit type)
};
GG_STATIC_ASSERT(offsetof(TemporalTypeView, unknown_0A0) == 0x0A0);
GG_STATIC_ASSERT(offsetof(TemporalTypeView, unknown_232) == 0x232);
GG_STATIC_ASSERT(offsetof(TemporalTypeView, unknown_C8E) == 0xC8E);
GG_STATIC_ASSERT(offsetof(TemporalTypeView, unknown_CD5) == 0xCD5);
GG_STATIC_ASSERT(offsetof(TemporalTypeView, unknown_E0E) == 0xE0E);

// The object list at TechnoClass+0x114 (0x473430 hands out one entry).
struct TemporalListView
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x473430 (decl; reloc) -- __thiscall.
    TemporalTechnoView* FUN_00473430();
};
// The member at TechnoClass+0x150 (0x74FF50 takes two values).
struct TemporalSink150View
{
    char opaque[1];
    // FUNCTION: GAMEMD 0x74FF50 (decl; reloc) -- __thiscall, RET 8.
    void FUN_0074FF50(int a, int b);
};
struct TemporalObj2BCView
{
    // FUNCTION: GAMEMD 0x472140 (decl; reloc) -- __thiscall.
    void FUN_00472140();
};
struct TemporalObj2D0View
{
    // FUNCTION: GAMEMD 0x6B7100 (decl; reloc) -- __thiscall.
    void FUN_006B7100();
};
struct TemporalObj3CView
{
    // FUNCTION: GAMEMD 0x6CB4D0 (decl; reloc) -- __thiscall, RET 4.
    void FUN_006CB4D0(int a);
};
struct TemporalObj2D8View
{
    // FUNCTION: GAMEMD 0x6B0AE0 (decl; reloc) -- __thiscall, RET 8.
    void FUN_006B0AE0(TemporalTechnoView* owner, int a);
};

// The owner and the target, as this class uses them (a TechnoClass; slot
// offsets are the callers' `CALL [reg+N]` displacements).
struct TemporalTechnoView
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual void vf_020(int a);   // +0x020
    virtual void vf_024();
    virtual void vf_028();
    virtual int WhatAmI();   // +0x02C
    virtual void vf_030();
    virtual void vf_034();
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual TemporalCoord vf_048();   // +0x048
    virtual TemporalCoord vf_04C(int a);   // +0x04C
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
    virtual bool vf_080();   // +0x080
    virtual TemporalTypeView* vf_084();   // +0x084
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
    virtual void vf_0E0(TemporalTechnoView* owner);   // +0x0E0
    virtual void vf_0E4();
    virtual void vf_0E8();
    virtual void vf_0EC();
    virtual void vf_0F0();
    virtual void vf_0F4();
    virtual void vf_0F8();   // +0x0F8
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
    virtual void vf_124(int mark);   // +0x124
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
    virtual void vf_150();   // +0x150
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
    virtual void vf_1BC();
    virtual void vf_1C0();
    virtual void vf_1C4();
    virtual void vf_1C8();
    virtual void vf_1CC();
    virtual void vf_1D0();
    virtual void vf_1D4();
    virtual void vf_1D8();
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
    virtual int vf_2E4(int a);   // +0x2E4
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
    virtual void vf_37C();
    virtual void vf_380();
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
    virtual void vf_3B8(TemporalTechnoView* owner);   // +0x3B8
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
    virtual TemporalWeaponSlot* vf_3F8(int index);   // +0x3F8
    virtual void vf_3FC();
    virtual void vf_400();
    virtual void vf_404();
    virtual int vf_408();   // +0x408
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
    virtual void vf_480();
    virtual void vf_484(int a, int b);   // +0x484

    // FUNCTION: GAMEMD 0x452210 (decl; reloc) -- __thiscall on a building.
    void FUN_00452210();

    // FUNCTION: GAMEMD 0x4521C0 (decl; reloc) -- __thiscall on a building.
    void FUN_004521C0();
    // FUNCTION: GAMEMD 0x4585C0 (decl; reloc) -- __thiscall on a building, RET 4.
    void FUN_004585C0(int a);
    // FUNCTION: GAMEMD 0x4593A0 (decl; reloc) -- __thiscall on a building.
    void FUN_004593A0();
    // FUNCTION: GAMEMD 0x459470 (decl; reloc) -- __thiscall on a building.
    void FUN_00459470();
    // FUNCTION: GAMEMD 0x70E000 (decl; reloc) -- __thiscall, RET 4.
    void FUN_0070E000(int a);

    // The location at +0x9C, by value.
    TemporalCoord Coord_09C() const { return unknown_09C; }

    char                unknown_004[0x82 - 0x004];
    char                unknown_082;      // +0x082 @0x0071A7A8
    char                unknown_083[0x9C - 0x83];
    TemporalCoord       unknown_09C;      // +0x09C @0x0071A8D2 (the location)
    char                unknown_0A8[0x114 - 0xA8];
    TemporalListView    unknown_114;      // +0x114 @0x0071A9BC
    int                 unknown_118;      // +0x118 @0x0071A9B4
    char                unknown_11C[0x150 - 0x11C];
    TemporalSink150View unknown_150;      // +0x150 `ADD ECX,0x150` @0x0071A972
    char                unknown_151[0x21C - 0x151];
    TemporalHouseView*  unknown_21C;      // +0x21C @0x0071ACFE; the owning house
    char                unknown_220[0x270 - 0x220];
    char                unknown_270;      // +0x270 @0x0071ACE5
    char                unknown_271[0x274 - 0x271];
    TemporalClass*      unknown_274;      // +0x274 @0x0071AF50; its own temporal
    TemporalClass*      unknown_278;      // +0x278 @0x0071ACDC; the temporal on it
    char                unknown_27C[0x2BC - 0x27C];
    TemporalObj2BCView* unknown_2BC;      // +0x2BC @0x0071AF3E
    char                unknown_2C0[0x2D0 - 0x2C0];
    TemporalObj2D0View* unknown_2D0;      // +0x2D0 @0x0071AF2F
    char                unknown_2D4[0x2D8 - 0x2D4];
    TemporalObj2D8View* unknown_2D8;      // +0x2D8 @0x0071AA1D
    char                unknown_2DC[0x2E4 - 0x2DC];
    TemporalTechnoView* unknown_2E4;      // +0x2E4 @0x0071A9F1 / @0x0071AA6C
    char                unknown_2E8[0x6C4 - 0x2E8];
    TemporalTypeView*   unknown_6C4;      // +0x6C4 @0x0071AFEB (a unit's type)
};
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_082) == 0x082);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_09C) == 0x09C);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_118) == 0x118);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_150) == 0x150);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_270) == 0x270);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_274) == 0x274);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_278) == 0x278);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_2BC) == 0x2BC);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_2D0) == 0x2D0);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_2D8) == 0x2D8);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_2E4) == 0x2E4);
GG_STATIC_ASSERT(offsetof(TemporalTechnoView, unknown_6C4) == 0x6C4);

// VTABLE: GAMEMD 0x7F5180 (IPersistStream side)
// VTABLE: GAMEMD 0x7F5164 (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7F515C (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7F5154 (INoticeSource side, +0x0C)
class TemporalClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x71A450 (declaration)
    TemporalClass();
    // FUNCTION: GAMEMD 0x71A4E0 (declaration)
    TemporalClass(TemporalTechnoView* owner);
    // FUNCTION: GAMEMD 0x71A5A0 (declaration; no-initialisation constructor)
    TemporalClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x71A5D0 (declaration; destructor; slot 8 = 0x71B1B0)
    virtual ~TemporalClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x71A720
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x71A660
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x71A700
    virtual int vf_11();                                                  // 11  0x71B1A0
    virtual int vf_12();                                                  // 12  0x71B190
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x71A650

    // FUNCTION: GAMEMD 0x71A760 (declaration)
    void FUN_0071A760();
    // FUNCTION: GAMEMD 0x71AB10 (decl; reloc) -- the warp per step of a chain;
    // defined in combat/temporal_class_methods.cpp under this name.
    int GetWarpPerStep(int depth = 0) const;
    // FUNCTION: GAMEMD 0x71AB60 (declaration)
    void FUN_0071AB60(void* object);
    // FUNCTION: GAMEMD 0x71ABC0 (decl; reloc)
    void FUN_0071ABC0();
    // FUNCTION: GAMEMD 0x71ACB0 (declaration)
    void FUN_0071ACB0();
    // FUNCTION: GAMEMD 0x71ACD0 (declaration)
    void FUN_0071ACD0();
    // FUNCTION: GAMEMD 0x71AD30 (declaration)
    void FUN_0071AD30();
    // FUNCTION: GAMEMD 0x71AD40 (decl; reloc) -- defined in
    // combat/temporal_class_methods.cpp under this name.
    void JustLetGo();
    // FUNCTION: GAMEMD 0x71AE50 (decl; reloc) -- can this warp the target.
    bool FUN_0071AE50(TemporalTechnoView* target);
    // FUNCTION: GAMEMD 0x71ADB0 (declaration)
    void FUN_0071ADB0();
    // FUNCTION: GAMEMD 0x71ADE0 (decl; reloc) -- defined in
    // combat/temporal_class_methods.cpp under this name.
    void Detach();
    // FUNCTION: GAMEMD 0x71AF20 (declaration)
    void FUN_0071AF20(TemporalTechnoView* target);

    TemporalTechnoView* Owner;       // +0x24 ctor argument @0x0071A51C
    TemporalTechnoView* Target;      // +0x28 ctor @0x0071A51F; its +0x278 points back
    TemporalTimer       unknown_2C;  // +0x2C ctor @0x0071A529..0x0071A52F
    void*               unknown_38;  // +0x38 ctor @0x0071A58E; swizzled by Load
    TemporalObj3CView*  unknown_3C;  // +0x3C ctor @0x0071A591; swizzled by Load
    TemporalClass*      unknown_40;  // +0x40 ctor @0x0071A532; a chain link
    TemporalClass*      unknown_44;  // +0x44 ctor @0x0071A535; a chain link
    int                 unknown_48;  // +0x48 ctor @0x0071A588
    mutable int         unknown_4C;  // +0x4C ctor @0x0071A58B; cached by 0x71A760 and by the const 0x71AB10

    // GLOBAL: GAMEMD 0xB0EC60
    static DynamicVectorClass<TemporalClass*> Array;
};
GG_STATIC_ASSERT(offsetof(TemporalClass, Owner)      == 0x24);
GG_STATIC_ASSERT(offsetof(TemporalClass, Target)     == 0x28);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(sizeof(TemporalClass) == 0x50);

#endif  // GG_MATCH_LAYOUT_TEMPORAL_CLASS_H
