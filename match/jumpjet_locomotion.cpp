// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /Ob2
//
// JumpjetLocomotionClass (layout and tables in _layout/jumpjet_locomotion_class.h).
// The COM / IPiggyback bodies below are the shapes DriveLocomotionClass uses
// (movement/drive_locomotion.cpp). Load's placement new of the no-init
// constructor stores the three vptrs, so VC6 emits Jumpjet's tables here and,
// with them, the ILocomotion (+4) and IPiggyback (+0x18) adjustor thunks.

#include <new.h>
#include "_layout/jumpjet_locomotion_class.h"
#include "_layout/rules_class.h"
#include "drive_support_views.h"
#include "_layout/cell_class.h"
#include "_layout/foot_class.h"
#include "cell_step_tables.h"

// GLOBAL: GAMEMD 0xABC5A8 - the empty coordinate this TU compares against.
extern "C" LocoCoord DAT_00ABC5A8;
// GLOBAL: GAMEMD 0xABC588 - the empty cell this TU compares against (shorts at 0xABC588 / 0xABC58A).
extern "C" CellStruct DAT_00ABC588;
// GLOBAL: GAMEMD 0xABC5E8 - minimum jump height unit; Height is clamped to twice it (LinkToObject 0x54AD30).
extern "C" int DAT_00ABC5E8;
// GLOBAL: GAMEMD 0xABC5DC - height subtracted over a bridge cell (InWhichLayer 0x54B8D0).
extern "C" int DAT_00ABC5DC;

// Address-local views of the linked FootClass, scoped to the Jumpjet bodies;
// every offset is read from an entry-origin instruction cited beside it.
struct JumpjetFacingView : FacingClass
{
    // FUNCTION: GAMEMD 0x4C91E0 (decl; reloc) - __thiscall constructor, one stack argument (rate of turn).
    JumpjetFacingView(int rate);
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc) - __thiscall, DoTurn 0x54B6E0.
    void FUN_004C9300(const unsigned long* dir);
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc) - same entry, LinkToObject passes its DirStruct local.
    void FUN_004C9300(const DirStruct* dir);
};

struct JumpjetTypeView
{
    char          unknown_000[0x5EC];
    unsigned char unknown_5EC;           // +0x5EC EndPiggyback `CMP [EAX+0x5EC],BL`
    char          unknown_5ED[0xD70 - 0x5ED];
    int           JumpjetTurnRate;       // +0xD70 LinkToObject @0x54AD49
    int           JumpjetSpeed;          // +0xD74 @0x54AD5C
    float         JumpjetClimb;          // +0xD78 @0x54AD6F
    float         JumpjetCrash;          // +0xD7C @0x54AD82
    int           JumpjetHeight;         // +0xD80 @0x54AD9B
    float         JumpjetAccel;          // +0xD84 @0x54ADB6
    float         JumpjetWobbles;        // +0xD88 @0x54ADC9
    char          JumpjetNoWobbles;      // +0xD8C @0x54ADEF
    char          unknown_D8D[3];
    int           unknown_D90;           // +0xD90 @0x54ADDC
};
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetTurnRate) == 0xD70);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetSpeed) == 0xD74);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetClimb) == 0xD78);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetCrash) == 0xD7C);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetHeight) == 0xD80);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetAccel) == 0xD84);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetWobbles) == 0xD88);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetNoWobbles) == 0xD8C);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, unknown_D90) == 0xD90);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, unknown_5EC) == 0x5EC);

struct JumpjetPathView
{
    char          unknown_000[0x1EC];
    unsigned char unknown_1EC;           // +0x1EC EndPiggyback `CMP [EDX+0x1EC],BL`
    // FUNCTION: GAMEMD 0x53A130 (decl; reloc) - __thiscall on the owner house, bool result.
    bool FUN_0053A130();
};
GG_STATIC_ASSERT(offsetof(JumpjetPathView, unknown_1EC) == 0x1EC);

struct JumpjetFootVirtuals
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
    virtual int vf_02C();
    virtual void vf_030();
    virtual void vf_034();
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual LocoCoord* vf_048(LocoCoord* out);
    virtual void vf_04C();
    virtual void vf_050();
    virtual bool vf_054();
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
    virtual JumpjetTypeView* vf_084();
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
    virtual void vf_0F0();
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
    virtual void vf_198(JumpjetPathView* house);
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
    virtual int vf_1C8();
    virtual void vf_1CC();
    virtual void vf_1D0();
    virtual void vf_1D4();
    virtual void vf_1D8();
    virtual void vf_1DC();
    virtual void vf_1E0();
    virtual void vf_1E4();
    virtual void vf_1E8(int a, int b);
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
    virtual CellStruct* vf_2F4(CellStruct* out);
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
    virtual void vf_3B8();
    virtual void vf_3BC();
    virtual void vf_3C0();
    virtual void vf_3C4();
    virtual void vf_3C8();
    virtual void vf_3CC();
    virtual void vf_3D0();
    virtual void vf_3D4();
    virtual void vf_3D8();
    virtual void vf_3DC(int arg);
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
    virtual void vf_480();
    virtual void vf_484();
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
    virtual void vf_538();
    virtual void vf_53C();
    virtual void vf_540();
    virtual void vf_544(double value);
    virtual void vf_548();
    virtual void vf_54C();
    virtual void vf_550();
    virtual void vf_554();
    virtual void vf_558(int a, int b, int c);
};

struct JumpjetFootView : JumpjetFootVirtuals
{
    char              unknown_004[0x083 - 0x004];
    unsigned char     unknown_083;  // +0x083 Process @0x54B080
    char              unknown_084[0x08C - 0x084];
    unsigned char     unknown_08C;  // +0x08C InWhichLayer `[EAX+0x8C]`
    unsigned char     unknown_08D;  // +0x08D InWhichLayer `[EDX+0x8D]`
    char              unknown_08E[0x090 - 0x08E];
    unsigned char     unknown_090;  // +0x090 Process @0x54AEF8
    char              unknown_091[0x09C - 0x091];
    LocoCoord         Location;  // +0x09C HeadToCoord 0x54D9B0
    char              unknown_0A8[0x21C - 0x0A8];
    JumpjetPathView*  unknown_21C;  // +0x21C EndPiggyback `MOV EDX,[ECX+0x21C]`
    char              unknown_220[0x388 - 0x220];
    JumpjetFacingView PrimaryFacing;  // +0x388 DoTurn `ADD ECX,0x388`
    char              unknown_3A0[0x41B - 0x3A0];
    unsigned char     unknown_41B;  // +0x41B Process @0x54B115
    char              unknown_41C[0x425 - 0x41C];
    unsigned char     unknown_425;  // +0x425 Process @0x54AF33
    char              unknown_426[0x428 - 0x426];
    int               unknown_428;  // +0x428 EndPiggyback
    int               unknown_42C;  // +0x42C EndPiggyback
    char              unknown_430[0x6AD - 0x430];
    unsigned char     unknown_6AD;  // +0x6AD IsOkToEnd / EndPiggyback / Process @0x54AFE0
    unsigned char     unknown_6AE;  // +0x6AE IsOkToEnd / EndPiggyback
};
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_083) == 0x083);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_08C) == 0x08C);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_08D) == 0x08D);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_090) == 0x090);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, Location) == 0x09C);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_41B) == 0x41B);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_425) == 0x425);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_428) == 0x428);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_42C) == 0x42C);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_6AD) == 0x6AD);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_6AE) == 0x6AE);

// GLOBAL: GAMEMD 0xA83D4C - HouseClass::CurrentPlayer.
extern "C" JumpjetPathView* DAT_00A83D4C;

// Aircraft tracker at 0x887888; only the add entry is called (thiscall, one stack argument).
struct JumpjetTracker
{
    // FUNCTION: GAMEMD 0x4134A0 (decl; reloc) - AircraftTrackerClass::Add.
    void FUN_004134A0(JumpjetFootView* foot);
};
// GLOBAL: GAMEMD 0x887888 - the tracker.
extern "C" JumpjetTracker DAT_00887888;

// Scenario object at 0xA8B230; only its first dword (flags) is read.
struct JumpjetScenario
{
    unsigned int unknown_000;            // +0x000 0x54AEC0 `MOV EAX,[ECX]; TEST AH,0x10`
};
// GLOBAL: GAMEMD 0xA8B230 - the scenario pointer.
extern "C" JumpjetScenario* DAT_00A8B230;

static inline FootClass* JumpjetObject(JumpjetLocomotionClass* self)
{
    return (FootClass*)self->LinkedTo;
}

static inline JumpjetFootView* JumpjetFoot(JumpjetLocomotionClass* self)
{
    return (JumpjetFootView*)self->LinkedTo;
}

static inline bool JumpjetIsSet(const LocoCoord& c)
{
    return c.X != DAT_00ABC5A8.X || c.Y != DAT_00ABC5A8.Y || c.Z != DAT_00ABC5A8.Z;
}

// FUNCTION: GAMEMD 0x54AC40
JumpjetLocomotionClass::JumpjetLocomotionClass()
    : DestCoord(DAT_00ABC5A8),
      unknown_4C(0),
      unknown_50(0),
      LocomotionFacing(RulesInstance->unknown_40C),
      unknown_70(0),
      unknown_78(0),
      unknown_80(0),
      unknown_88(0),
      unknown_90(0),
      unknown_91(0),
      Piggybackee(0)
{
    {
        DirStruct turn(0x4000);
        LocomotionFacing.SetDesired(turn);
    }
    {
        DirStruct turn(0x4000);
        LocomotionFacing.FUN_004C9300(&turn);
    }
}

static inline LocoCoord JumpjetStepped(const LocoCoord& c, const Point2D& step)
{
    LocoCoord r;
    r.X = c.X + step.X;
    r.Y = c.Y + step.Y;
    r.Z = c.Z;
    return r;
}

// LIBRARY: OLE32!OleLoadFromStream, IAT 0x7E15F8 (declared by <ole2.h>).

// FUNCTION: GAMEMD 0x54AD00
JumpjetLocomotionClass::~JumpjetLocomotionClass() {}

// FUNCTION: GAMEMD 0x54AD30 (partial 82.6%: retail CSEs the facing address into EAX for SetDesired and recomputes it for 0x4C9300)
HRESULT __stdcall JumpjetLocomotionClass::LinkToObject(FootClass* object)
{
    JumpjetFootView* foot = (JumpjetFootView*)object;
    TurnRate = foot->vf_084()->JumpjetTurnRate;
    Speed = foot->vf_084()->JumpjetSpeed;
    Climb = foot->vf_084()->JumpjetClimb;
    Crash = foot->vf_084()->JumpjetCrash;
    int height = foot->vf_084()->JumpjetHeight;
    int floor = DAT_00ABC5E8 + DAT_00ABC5E8;
    Height = height > floor ? height : floor;
    Accel = foot->vf_084()->JumpjetAccel;
    Wobbles = foot->vf_084()->JumpjetWobbles;
    unknown_38 = foot->vf_084()->unknown_D90;
    NoWobbles = foot->vf_084()->JumpjetNoWobbles;
    LocomotionFacing = JumpjetFacingView(TurnRate);
    {
        DirStruct turn;
        turn.Raw = 0x4000;
        LocomotionFacing.SetDesired(turn);
    }
    {
        DirStruct turn;
        turn.Raw = 0x4000;
        ((JumpjetFacingView&)LocomotionFacing).FUN_004C9300(&turn);
    }
    return LocomotionClass::LinkToObject(object);
}

// FUNCTION: GAMEMD 0x54AE60
LocoCoord __stdcall JumpjetLocomotionClass::Destination()
{
    LocoCoord c;
    if (IsMoving()) {
        c.X = DestCoord.X;
        c.Y = DestCoord.Y;
        c.Z = DestCoord.Z;
        return c;
    }
    c.X = DAT_00ABC5A8.X;
    c.Y = DAT_00ABC5A8.Y;
    c.Z = DAT_00ABC5A8.Z;
    return c;
}

// FUNCTION: GAMEMD 0x54AEC0 (partial 94.7%: same 228-instruction multiset; retail packs the locals into a 0x20-byte frame and its jump table has a seventh entry for state 6)
bool __stdcall JumpjetLocomotionClass::Process()
{
    int layer = InWhichLayer();
    if (IsMoving() || IsMovingNow()) {
        FUN_0054D0F0();
        if (!JumpjetFoot(this)->unknown_090)
            return false;
        if (JumpjetFoot(this)->unknown_21C->FUN_0053A130() && unknown_50 != 0 && unknown_50 != 5)
            JumpjetFoot(this)->vf_3DC(0);
        if (JumpjetFoot(this)->unknown_425 && unknown_50 != 5 && unknown_50 != 6
            && JumpjetFoot(this)->vf_1C8() > 0) {
            LocoCoord buf;
            LocoCoord first = *JumpjetFoot(this)->vf_048(&buf);
            LocoCoord* got2 = JumpjetFoot(this)->vf_048(&buf);
            CellStruct cell;
            cell.X = (short)(got2->X / 256);
            cell.Y = (short)(got2->Y / 256);
            CellStruct probe = cell;
            LocoCoord center = DAT_0087F7E8.FUN_005657A0(&probe)->vf_18();
            if (JumpjetFoot(this)->unknown_6AD && !(first.X == center.X && first.Y == center.Y)) {
                DestCoord = center;
            } else {
                unknown_80 = -5;
                unknown_50 = 5;
                if (JumpjetFoot(this)->vf_02C() == 0xF)
                    JumpjetFoot(this)->vf_558(0x22, 0, 0);
            }
        }
        switch (unknown_50) {
        case 0: FUN_0054B980(); break;
        case 1: FUN_0054BA30(); break;
        case 2: FUN_0054BD30(); break;
        case 3: FUN_0054BFF0(); break;
        case 4: FUN_0054C550(); break;
        case 5: FUN_0054CA90(); break;
        case 6: break;
        }
        if (JumpjetFoot(this)->unknown_083 && JumpjetFoot(this)->unknown_21C != DAT_00A83D4C) {
            LocoCoord here = JumpjetFoot(this)->Location;
            bool seen = DAT_0087F7E8.IsLocationShrouded(here);
            if (!seen && (DAT_00A8B230->unknown_000 & 0x1000)) {
                LocoCoord there = JumpjetFoot(this)->Location;
                seen = DAT_0087F7E8.IsLocationFogged(&there);
            }
            if (seen)
                JumpjetFoot(this)->vf_150();
        }
        if (!JumpjetFoot(this)->unknown_41B && JumpjetFoot(this)->unknown_21C != DAT_00A83D4C) {
            LocoCoord here = JumpjetFoot(this)->Location;
            if (!DAT_0087F7E8.IsLocationShrouded(here))
                JumpjetFoot(this)->vf_198(DAT_00A83D4C);
        }
    }
    if (JumpjetFoot(this)->unknown_090 && InWhichLayer() != layer)
        DAT_0087F7E8.FUN_004A9720(JumpjetObject(this));
    return false;
}

// FUNCTION: GAMEMD 0x54B6E0
void __stdcall JumpjetLocomotionClass::DoTurn(unsigned long dir)
{
    unsigned long desired = dir;
    JumpjetFoot(this)->PrimaryFacing.FUN_004C9300(&desired);
}

// FUNCTION: GAMEMD 0x54B750
HRESULT __stdcall JumpjetLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) JumpjetLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x54B7E0
// Saves the base locomotor, then a flag byte and, when a locomotor is piggybacked,
// that locomotor as an OLE persistent stream.
HRESULT __stdcall JumpjetLocomotionClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = LocomotionClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        bool hasPiggyback;
        if (Piggybackee != 0) {
            hasPiggyback = true;
            pStm->Write(&hasPiggyback, 1, 0);
            IPersistStreamPtr persist(Piggybackee);
            return OleSaveToStream(persist, pStm);
        }
        hasPiggyback = false;
        pStm->Write(&hasPiggyback, 1, 0);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x54B8D0
int __stdcall JumpjetLocomotionClass::InWhichLayer()
{
    int height = JumpjetFoot(this)->vf_1C8();
    if (!JumpjetFoot(this)->unknown_08C) {
        LocoCoord here = JumpjetFoot(this)->Location;
        if (DriveMap().FUN_00565730(&here)->Flags & 0x100) {
            if (height >= DAT_00ABC5DC && !JumpjetFoot(this)->unknown_08D)
                height -= DAT_00ABC5DC;
        }
    }
    if (!JumpjetFoot(this)->vf_054())
        return 2;
    if (height == 0)
        return 2;
    return (height >= Height) + 3;
}

// FUNCTION: GAMEMD 0x54B980 (partial 85.5%: same multiset; retail keeps the foot in ECX for the facing call and picks ECX/EDX for the Height copy)
void JumpjetLocomotionClass::FUN_0054B980()
{
    if (IsMoving()) {
        JumpjetFoot(this)->vf_544(1.0);
        {
            DirStruct turn;
            DirStruct* cur = JumpjetFoot(this)->PrimaryFacing.FUN_004C93D0(&turn);
            LocomotionFacing.FUN_004C9300(cur);
        }
        unknown_70 = 0;
        unknown_78 = 0;
        unknown_80 = Height;
        if (!JumpjetFoot(this)->unknown_21C->FUN_0053A130()) {
            CellStruct cell;
            CellStruct* at = JumpjetFoot(this)->vf_2F4(&cell);
            if (at->X == DAT_00ABC588.X && at->Y == DAT_00ABC588.Y)
                DAT_00887888.FUN_004134A0(JumpjetFoot(this));
            unknown_50 = 1;
        }
    }
}

// FUNCTION: GAMEMD 0x54D6D0
CoordStruct* JumpjetLocomotionClass::FUN_0054D6D0(CoordStruct* out, const CoordStruct* cell)
{
    LocoCoord result;
    if (JumpjetFoot(this) != 0 && JumpjetFoot(this)->vf_02C() == 1) {
        result = DAT_0087F7E8.FUN_00565730(cell)->vf_18();
        if (JumpjetIsSet(result)) {
            result.Z = DAT_0087F7E8.FUN_00578080(&result);
            if (DAT_0087F7E8.FUN_00565730(&result)->Flags & 0x100)
                result.Z += DAT_00ABC5DC;
        }
    } else {
        LocoCoord picked;
        result = *DAT_0087F7E8.FUN_004ACA10(&picked, cell, false);
        if (JumpjetIsSet(result)) {
            result.Z = DAT_0087F7E8.FUN_00578080(&result);
            if (DAT_0087F7E8.FUN_00565730(&result)->Flags & 0x100)
                result.Z += DAT_00ABC5DC;
        }
    }
    *out = result;
    return out;
}

// FUNCTION: GAMEMD 0x54D820
int JumpjetLocomotionClass::FUN_0054D820()
{
    LocoCoord here = JumpjetFoot(this)->Location;
    int height = DAT_0087F7E8.FUN_00565730(&here)->FUN_00485080();
    if (DAT_0087F7E8.FUN_00565730(&here)->Flags & 0x100)
        height += DAT_00ABC5DC;
    if (unknown_70 > 0.0) {
        DirStruct turn;
        DirStruct* facing = LocomotionFacing.FUN_004C93D0(&turn);
        unsigned int step = (((facing->Whole >> 12) + 1) >> 1) & 7;
        here = JumpjetStepped(here, DAT_0089F6D8[step]);
        int ahead = DAT_0087F7E8.FUN_00565730(&here)->FUN_00485080();
        if (DAT_0087F7E8.FUN_00565730(&here)->Flags & 0x100)
            height += DAT_00ABC5DC;
        if (ahead > height)
            return ahead;
        return (ahead + height) / 2;
    }
    return height;
}

// FUNCTION: GAMEMD 0x54D930
// The virtual call returns the coordinate through a hidden buffer and hands back its address; retail
// copies the three fields out of that returned address into the local before comparing.
void __stdcall JumpjetLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (mark == 0) {
        LocoCoord head;
        LocoCoord* got = &HeadToCoord();
        head.X = got->X;
        head.Y = got->Y;
        head.Z = got->Z;
        if (JumpjetIsSet(head) && (unknown_50 == 0 || unknown_90)) {
            JumpjetFoot(this)->vf_0F4(&head);
            unknown_90 = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x54D9B0
LocoCoord __stdcall JumpjetLocomotionClass::HeadToCoord()
{
    LocoCoord c;
    if (unknown_50 == 0) {
        LocoCoord here = JumpjetFoot(this)->Location;
        c.X = here.X;
        c.Y = here.Y;
        c.Z = here.Z;
        return c;
    }
    c.X = DestCoord.X;
    c.Y = DestCoord.Y;
    c.Z = DestCoord.Z;
    return c;
}

// FUNCTION: GAMEMD 0x54DA00
HRESULT __stdcall JumpjetLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x54DA50
HRESULT __stdcall JumpjetLocomotionClass::EndPiggyback(ILocomotion** out)
{
    if (!out)
        return E_POINTER;
    if (JumpjetFoot(this)) {
        if (JumpjetFoot(this)->unknown_6AD || JumpjetFoot(this)->unknown_6AE) {
            JumpjetFoot(this)->unknown_6AD = 0;
            JumpjetFoot(this)->unknown_6AE = 0;
            if (!JumpjetFoot(this)->unknown_21C->unknown_1EC
                && JumpjetFoot(this)->vf_084()->unknown_5EC)
                JumpjetFoot(this)->vf_1E8(10, 0);
        }
        JumpjetFoot(this)->unknown_428 = 0;
        JumpjetFoot(this)->unknown_42C = 0;
    }
    if (Piggybackee) {
        *out = Piggybackee;
        Piggybackee.Detach();
        return S_OK;
    }
    return S_FALSE;
}

// FUNCTION: GAMEMD 0x54DB00
bool __stdcall JumpjetLocomotionClass::IsOkToEnd()
{
    if (!IsMoving() && Piggybackee != 0 && !unknown_91
        && (!JumpjetFoot(this)->unknown_6AD || JumpjetFoot(this)->unknown_6AE))
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x54DB50
HRESULT __stdcall JumpjetLocomotionClass::PiggybackCLSID(CLSID* out)
{
    if (!out)
        return E_POINTER;
    if (Piggybackee) {
        IPersistPtr persist(Piggybackee);
        if (persist == 0)
            return E_FAIL;
        return persist->GetClassID(out);
    }
    IPersistPtr persist(static_cast<LocomotionClass*>(this));
    if (persist == 0)
        return E_FAIL;
    return persist->GetClassID(out);
}

// FUNCTION: GAMEMD 0x54DC60
HRESULT __stdcall JumpjetLocomotionClass::QueryInterface(REFIID riid, void** ppv)
{
    HRESULT hr = LocomotionClass::QueryInterface(riid, ppv);
    if (hr == E_NOINTERFACE) {
        if (riid == IID_IPiggyback)
            *ppv = static_cast<IPiggyback*>(this);
        if (*ppv == 0)
            return E_NOINTERFACE;
        AddRef();
        hr = S_OK;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x0054DF50
ULONG __stdcall JumpjetLocomotionClass::AddRef()
{
    return LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x0054DF60
ULONG __stdcall JumpjetLocomotionClass::Release()
{
    return LocomotionClass::Release();
}

// SYNTHETIC: GAMEMD 0x54DFA0 -- compiler-generated scalar deleting destructor.
// SYNTHETIC: GAMEMD 0x54DFF0 -- compiler-generated ILocomotion QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E000 -- compiler-generated ILocomotion AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E010 -- compiler-generated ILocomotion Release adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E020 -- compiler-generated IPiggyback QI adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x54E030 -- compiler-generated IPiggyback AddRef adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x54E040 -- compiler-generated IPiggyback Release adjustor thunk (this -= 0x18).
