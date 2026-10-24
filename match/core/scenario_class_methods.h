// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/addresses derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x4AE4C0 / 0x68BD80),
//   cross-checked against YRpp (reconfirmed here).
//
// ScenarioClass — the global scenario/mission record. Only two methods are
// matched here, so the class is hand-padded to the single member they touch
// (the Waypoints array at +0x632); the full layout is P2.
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"
#include "../_layout/object_class.h"
#include "frame_counter.h"
#include "randomizer.h"
#include "type_list.h"
#include "../_layout/elapsed_timer.h"
#include "../_rt/gg_istream.h"

// ---- iterator singleton + cell, used only by UpdateCellLighting ----
#include "../_layout/cell_class.h"

// The global map/radar singleton at 0x87F7E8. UpdateCellLighting drives its
// spiral cell iterator (begin @0x578350, next @0x578290).
class CCINIClass;
class HouseClass;

class WaypointClass;
struct MapInstanceClass
{
    // FUNCTION: GAMEMD 0x5865E0 (decl; reloc). Native returns AL=false, RET4;
    // Tactical6D8FDA/6D965D passes a coordinate snapshot, ECX=87F7E8.
    bool FUN_005865E0(const CoordStruct* coordinate);
    // Declaration: GAMEMD 0x4A94F0, hidden CellStruct result + foundation, RET8
    CellStruct FUN_004A94F0(const CellStruct* foundation) const;
    // Declaration: GAMEMD 0x568300, one cell pointer, AL result, RET4
    bool FUN_00568300(const CellStruct* cell) const;
    // Declaration: GAMEMD 0x56BD40
    void FUN_0056BD40();
    // Declaration: GAMEMD 0x4AC4F0
    void FUN_004AC4F0();
    // FUNCTION: GAMEMD 0x577F30 (decl; 0x6849E7, null house argument).
    void FUN_00577F30(HouseClass* house);
    // FUNCTION: GAMEMD 0x6D0F00 (decl; reloc)
    void FUN_006D0F00();
    // FUNCTION: GAMEMD 0x6AC5F0 (decl; reloc)
    void FUN_006AC5F0(void* item, int value);
    // FUNCTION: GAMEMD 0x6A7590 (decl; reloc)
    void FUN_006A7590(int index);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the height at a coordinate.
    int FUN_00578080(CoordStruct* where);
    // Declaration: GAMEMD 0x586360, reads original waypoint XYZ, AL result, RET4.
    bool FUN_00586360(const WaypointClass* where);
    // FUNCTION: GAMEMD 0x57B790 (decl; reloc)
    void FUN_0057B790(CellStruct* cell);
    // FUNCTION: GAMEMD 0x56BEC0 (decl; reloc)
    bool FUN_0056BEC0(CellStruct cell, int value);
    void FUN_004AD7E0(CCINIClass* ini); // GAMEMD 0x4AD7E0
    // Hidden Cell result precedes fourteen explicit stack arguments at 0x6885B5.
    Cell FUN_0056DC20(const CellStruct& from, int speedType, int a4,
                     int zone, bool alt, int sizeX, int sizeY,
                     bool a9, bool a10, bool a11, bool ignoreOccupied,
                     const CellStruct& closeTo, bool a14, bool buildable); // GAMEMD 0x56DC20
    // FUNCTION: GAMEMD 0x5657a0 (decl; reloc)
    // ?FUN_005657A0@MapInstanceClass@@QAEPAVCellClass@@PBUCellStruct@@@Z
    CellClass* FUN_005657A0(const CellStruct* cell);
    // Declaration: GAMEMD 0x565730, two-int world position, CellClass* result, RET4.
    CellClass* FUN_00565730(const Point2D* location);
    // Same native entry565730: callers6D6DCF/6D72A2 pass a12-byte coordinate;
    // callee consumes only X/Y at0/4, never reads Z or writes the input.
    CellClass* FUN_00565730(const CoordStruct* location);
    void FUN_005BDA80(int a, int b); // GAMEMD 0x5BDA80, __thiscall
    void FUN_004F4480(); // GAMEMD 0x4F4480, __thiscall
    void FUN_00655B20(); // GAMEMD 0x655B20, __thiscall
    void FUN_004F42F0(int value); // GAMEMD 0x4F42F0, __thiscall
    void FUN_00565B00(); // GAMEMD 0x565B00
    void FUN_005BDF50(); // GAMEMD 0x5BDF50
    bool FUN_00578460(const CellStruct* cell, int flag); // GAMEMD 0x578460
    void FUN_006D04F0(int value); // GAMEMD 0x6D04F0
    void FUN_00653F70(CoordStruct* where); // GAMEMD 0x653F70
    void FUN_004ADCD0(int first, int second); // GAMEMD 0x4ADCD0
    void FUN_0056D6E0(); // GAMEMD 0x56D6E0
    void FUN_0056C510(); // GAMEMD 0x56C510
    void FUN_00581F50(); // GAMEMD 0x581F50
    void FUN_00586BF0(); // GAMEMD 0x586BF0
    void FUN_006938C0(); // GAMEMD 0x6938C0, __thiscall
    void       IteratorBegin_578350();   // GAMEMD 0x578350  __thiscall
    CellClass* IteratorNext_578290();    // GAMEMD 0x578290  __thiscall
};

// GLOBAL: GAMEMD 0x87F7E8  MapClass::Instance (the map singleton).
extern MapInstanceClass MapInstance;

// GLOBAL: GAMEMD 0x00B05458  the "undefined" waypoint sentinel cell.
extern CellStruct WaypointUndefined;

// STRING: GAMEMD 0x0083D868
// "Toggle display mode to %d x %d\n"
extern const char STR_0083D868[];
// STRING: GAMEMD 0x0083D924
// "Toggle display mode back to shell res\n"
extern const char STR_0083D924[];
// STRING: GAMEMD 0x0083D824
// "VariableNames"
extern const char STR_0083D824[];
// STRING: GAMEMD 0x00817F70
// ","
extern const char STR_00817F70[];
// STRING: GAMEMD 0x00817F6C
// "%d"
extern const char STR_00817F6C[];
// STRING: GAMEMD 0x0083DE1C
// "%s,%d"
extern const char STR_0083DE1C[];
// STRING: GAMEMD 0x0082DB0C
// "Waypoints"
extern const char STR_0082DB0C[];
// STRING: GAMEMD 0x00889F64
// ""
extern const char STR_00889F64[];


// The scenario's mission timer at +0x11E8 (a frame timer; the middle dword is
// not initialised by the constructor taking a duration).
struct ScenarioTimer
{
    int StartTime;
    int unknown_04;
    int TimeLeft;
    ScenarioTimer() {}
    explicit ScenarioTimer(int duration)
    {
        StartTime = CurrentFrame;
        TimeLeft = duration;
    }
    int GetTimeLeft() const
    {
        int left = TimeLeft;
        if (StartTime != -1) {
            int elapsed = CurrentFrame - StartTime;
            return (elapsed < left) ? left - elapsed : 0;
        }
        return left;
    }
    bool IsOn() const
    {
        return StartTime != -1;
    }
    bool IsOff() const
    {
        return StartTime == -1;
    }
    void Start()
    {
        if (StartTime == -1) {
            StartTime = CurrentFrame;
        }
    }
    void Stop()
    {
        if (StartTime != -1) {
            TimeLeft = GetTimeLeft();
            StartTime = -1;
        }
    }
};

GG_STATIC_ASSERT(offsetof(ScenarioTimer, StartTime) == 0);
GG_STATIC_ASSERT(offsetof(ScenarioTimer, TimeLeft) == 8);
GG_STATIC_ASSERT(sizeof(ScenarioTimer) == 12);

struct ScenarioRecord
{
    char unknown_00[40];
    unsigned char unknown_28;
};
GG_STATIC_ASSERT(sizeof(ScenarioRecord) == 41);
GG_STATIC_ASSERT(offsetof(ScenarioRecord, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(ScenarioRecord, unknown_28) == 40);

class INIClass;
class CCINIClass;

// The first byte is cleared between frame-timer member constructions at
// 0x683313. The next member starts at +0x1218, bounding this storage to32 bytes.
struct ScenarioText32
{
    char unknown_00[32];
    ScenarioText32() { unknown_00[0] = 0; }
    explicit ScenarioText32(const AbstractNoInit&) {}
};
GG_STATIC_ASSERT(offsetof(ScenarioText32, unknown_00) == 0);
GG_STATIC_ASSERT(sizeof(ScenarioText32) == 32);

class TechnoTypeClass;

struct ScenarioClass
{
    ScenarioClass();
    explicit ScenarioClass(const AbstractNoInit& noInit);
    void FUN_00683610(); // GAMEMD 0x683610
    void FUN_006B8AE0(); // GAMEMD 0x6B8AE0
    void FUN_0068AD70(CCINIClass* ini, bool flag); // GAMEMD 0x68AD70
    void FUN_00689310(Gg_IStream* stream);
    void FUN_00689470(Gg_IStream* stream); // FUNCTION: GAMEMD 0x689470 (decl)
    bool FUN_0053A100(); // GAMEMD 0x53A100
    // Declaration: GAMEMD 0x68B940
    void FUN_0068B940(Obj_004A1D30* crc);
    // ---- matched methods (ascending by retail address) ----
    static void UpdateCellLighting();        // GAMEMD 0x4AE4C0  (free/static)
    CellStruct GetWaypointCoords(int idx);   // GAMEMD 0x68BCC0  __thiscall
    bool IsDefinedWaypoint(int idx);         // GAMEMD 0x68BD80  __thiscall

    unsigned char FUN_00689670(unsigned int index, unsigned char value);
    unsigned char FUN_00689910(unsigned int index, unsigned char value);
    int FUN_00689820(const char* text);
    bool FUN_00689790(const char* text, unsigned char* value);
    int FUN_00689AC0(const char* text);
    bool FUN_00689A30(const char* text, unsigned char* value);
    unsigned char FUN_006896C0(const char* text, unsigned char value);
    unsigned char FUN_00689960(const char* text, unsigned char value);
    void FUN_0068BDC0(INIClass* ini);
    void FUN_0068BE90(INIClass* ini);
    CoordStruct FUN_0068BD00(int index);
    bool FUN_00689880(INIClass* ini);
    bool FUN_00689B20(INIClass* ini);
    bool FUN_00689C60(INIClass* ini);
    void FUN_00686700(const char* text);
    bool FUN_00689760(int index, unsigned char* value);
    bool FUN_00689A00(int index, unsigned char* value);
    int FUN_00689CF0();
    int FUN_00689D10();
    CellClass* FUN_0068BCE0(int index);
    CellClass* FUN_0068BF70(int index);
    void FUN_0068BD60();
    const char* FUN_0068BF90();
    void FUN_0068BF30(int index);
    void FUN_0068BF50(int index, CellStruct value);

    // ---- members touched by the matched methods ----
    unsigned int unknown_0000; // bit tests0x688BF8/0x688D51
    char unknown_0004[0x20C - 4];
    int unknown_020C; // 0x684CB1 waypoint selector
    int unknown_0210; // 0x684CA9 alternate waypoint selector
    int unknown_0214;
    Randomizer unknown_0218;
    int Difficulty;
    int unknown_0610;
    ScenarioElapsedTimer unknown_0614;
    ScenarioElapsedTimer unknown_0620;
    int unknown_062C;
    unsigned char unknown_0630;
    char unknown_0631;
    CellStruct Waypoints[702];        // 0x632  valid range [0..701]
    char unknown_112A[0x11E8 - 0x112A];
    ScenarioTimer Timer_11E8;
    const wchar_t* unknown_11F4;
    ScenarioText32 unknown_11F8;
    ScenarioTimer unknown_1218, unknown_1224, unknown_1230, unknown_123C, unknown_1248;
    int unknown_1254;
    int unknown_1258;
    char unknown_125C[260];
    wchar_t unknown_1360[(0x13BA - 0x1360) / 2];
    char unknown_13BA[0x13DA - 0x13BA];
    wchar_t unknown_13DA[(0x1434 - 0x13DA) / 2];
    int unknown_1434;
    int unknown_1438;
    int unknown_143C;
    int unknown_1440;
    int unknown_1444;
    int unknown_1448;
    int unknown_144C;
    wchar_t unknown_1450[(0x1C50 - 0x1450) / 2];
    char unknown_1C50[0x20];
    int unknown_1C70;
    int unknown_1C74;
    double unknown_1C78;
    int unknown_1C80;
    int unknown_1C84;
    ScenarioRecord unknown_1C88[50];
    ScenarioRecord unknown_248A[100];
    // 0x684CBE..0x684D03 copies the packed waypoint through four cells.
    CellStruct unknown_348E, unknown_3492, unknown_3496, unknown_349A;
    char unknown_349E[2];
    int unknown_34A0;
    bool unknown_34A4;
    bool unknown_34A5, unknown_34A6, unknown_34A7, unknown_34A8;
    char unknown_34A9;
    bool unknown_34AA;
    bool unknown_34AB, unknown_34AC, unknown_34AD, unknown_34AE;
    bool unknown_34AF, unknown_34B0, unknown_34B1;
    bool unknown_34B2; // byte load/test0x684F02
    bool unknown_34B3, unknown_34B4;
    char unknown_34B5[3];
    int unknown_34B8; // store0x6847C3
    bool unknown_34BC;
    bool unknown_34BD;
    char unknown_34BE[2];
    ScenarioTimer unknown_34C0;
    int unknown_34CC;
    int unknown_34D0;
    TypeList<TechnoTypeClass*> unknown_34D4;
    TypeList<int> unknown_34F0;
    TypeList<int> unknown_350C;
    int unknown_3528;
    int unknown_352C;
    int unknown_3530, unknown_3534, unknown_3538, unknown_353C;
    int unknown_3540, unknown_3544, unknown_3548, unknown_354C;
    int unknown_3550, unknown_3554, unknown_3558, unknown_355C;
    char unknown_3560[0x3598 - 0x3560];
    bool unknown_3598;
    char unknown_3599[0x35A2 - 0x3599];
    unsigned char unknown_35A2;
    char unknown_35A3;
    int unknown_35A4, unknown_35A8, unknown_35AC;
    char unknown_35B0;
    char unknown_35B1[30];
    char unknown_35CF;
    char unknown_35D0[30];
    char unknown_35EE;
    char unknown_35EF[30];
    char unknown_360D;
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0610) == 0x0610);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1434) == 0x1434);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1C74) == 0x1C74);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1C78) == 0x1C78);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1C80) == 0x1C80);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1C84) == 0x1C84);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34A0) == 0x34A0);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34A4) == 0x34A4);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AC) == 0x34AC);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AD) == 0x34AD);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AE) == 0x34AE);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AF) == 0x34AF);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34B0) == 0x34B0);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34B1) == 0x34B1);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34B3) == 0x34B3);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34B4) == 0x34B4);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34BC) == 0x34BC);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_352C) == 0x352C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3540) == 0x3540);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3544) == 0x3544);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3548) == 0x3548);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_354C) == 0x354C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3550) == 0x3550);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3554) == 0x3554);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3558) == 0x3558);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_355C) == 0x355C);

GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0214) == 0x214);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_35A4) == 0x35A4);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_35A8) == 0x35A8);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_35AC) == 0x35AC);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_35B0) == 0x35B0);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_35CF) == 0x35CF);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_35EE) == 0x35EE);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_360D) == 0x360D);
GG_STATIC_ASSERT(offsetof(ScenarioClass, Difficulty) == 0x60C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, Timer_11E8) == 0x11E8);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34A5) == 0x34A5);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34A8) == 0x34A8);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3528) == 0x3528);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3530) == 0x3530);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3534) == 0x3534);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3538) == 0x3538);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_353C) == 0x353C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34A6) == 0x34A6);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34A7) == 0x34A7);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0614) == 0x614);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0620) == 0x620);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0630) == 0x630);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_062C) == 0x62C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, Waypoints) == 0x632);

GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1254) == 0x1254);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1258) == 0x1258);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_125C) == 0x125C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1C88) == 0x1C88);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_248A) == 0x248A);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AA) == 0x34AA);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34CC) == 0x34CC);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_35A2) == 0x35A2);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0000) == 0x0000);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0218) == 0x0218);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_11F4) == 0x11F4);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_11F8) == 0x11F8);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1218) == 0x1218);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1224) == 0x1224);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1230) == 0x1230);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_123C) == 0x123C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1248) == 0x1248);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1360) == 0x1360);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_13BA) == 0x13BA);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_13DA) == 0x13DA);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1450) == 0x1450);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1C50) == 0x1C50);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0000) == 0);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1438) == 0x1438); // 0x683AB0 access
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1444) == 0x1444); // 0x683AB0 access
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1C70) == 0x1C70); // 0x683AB0 access
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34D0) == 0x34D0); // 0x683AB0 access
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34CC) == 0x34CC);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_348E) == 0x348E);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_020C) == 0x020C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0210) == 0x0210);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3492) == 0x3492);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3496) == 0x3496);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_349A) == 0x349A);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34B2) == 0x34B2);

GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34B8) == 0x34B8);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34BD) == 0x34BD);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34C0) == 0x34C0);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34D4) == 0x34D4);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34F0) == 0x34F0);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_350C) == 0x350C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3598) == 0x3598);
GG_STATIC_ASSERT(sizeof(Randomizer) == 0x3F4);
#endif


GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0004) == 4);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0004) + 0x104 == 0x108);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_143C) == 0x143C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1440) == 0x1440);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1448) == 0x1448);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_144C) == 0x144C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AB) + 1 == 0x34AC);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AB) + 3 == 0x34AE);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AB) + 4 == 0x34AF);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34AB) + 5 == 0x34B0);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1C88) + sizeof(ScenarioRecord) + offsetof(ScenarioRecord, unknown_28) == 0x1CD9);

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H
