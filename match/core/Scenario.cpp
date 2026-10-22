// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Scenario.CPP. The name is the source-file string at 0x83d838
//   in retail gamemd.exe v1.001, passed by the assert at 0x6835e1 inside this object's
//   code range (0x683070-0x68cb2f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   0x68BD80). Names cross-checked against YRpp (every offset/address reconfirmed against the user's binary).
//
//   GLOBAL:   GAMEMD 0x87F7E8   MapClass::Instance
//   GLOBAL:   GAMEMD 0x00B05458 undefined-waypoint sentinel cell
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.

#include "scenario_class_methods.h"

#include "scenario_class_start_points_methods.h"

#include "trivial_tu201_methods.h"

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
struct Cell_0050DEF0
{
    short X;
    short Y;

    Cell_0050DEF0() {}
    bool operator==(const Cell_0050DEF0& other) const
    {
        return X == other.X && Y == other.Y;
    }
};
GG_STATIC_ASSERT(sizeof(Cell_0050DEF0) == 4);

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A8EF98
extern "C" Cell_0050DEF0 DAT_00A8EF98;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

struct Team_005095D0
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[4];
    void* unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Team_005095D0, unknown_2C) == 0x2C);

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

struct Obj_005095D0
{
    int FUN_005095D0(int kind);
};


struct Obj_0050DA10
{
    char Pad_00[0x5490];
    Cell_0050DEF0 unknown_5490;
    Cell_0050DEF0 unknown_5494;
    char Pad_5498[0x54F0 - 0x5498];
    Cell_0050DEF0 unknown_54F0;
    Cell_0050DEF0 unknown_54F4;
    Cell_0050DEF0 unknown_54F8;
    int unknown_54FC;
    char Pad_5500[0x577C - 0x5500];
    int unknown_577C;

    void FUN_0050DA10();
    void FUN_0050DA50();
    int FUN_0050DA80() const;
    Cell_0050DEF0 FUN_0050DEF0() const;
    void FUN_0050DFF0();
};
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_5490) == 0x5490);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54F0) == 0x54F0);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54FC) == 0x54FC);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_577C) == 0x577C);

struct Obj_0053ECB0
{
    unsigned char unknown_0[10];

    Obj_0053ECB0();
};

struct Triple_0053EDA0
{
    short unknown_0;
    short unknown_2;
    short unknown_4;
};
GG_STATIC_ASSERT(sizeof(Triple_0053EDA0) == 6);

struct Obj_0053EDA0
{
    int unknown_0;
    Triple_0053EDA0 unknown_4;

    void FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0053EDA0, unknown_4) == 4);

struct Obj_005402B0
{
    void FUN_005402B0(int value);
};

struct Obj_00542FC0
{
    char Pad_00[0x48];
    Obj_005402B0* unknown_48;

    void FUN_00542FC0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00542FC0, unknown_48) == 0x48);

struct Entry_005657A0
{
    char Pad_00[0x24];
    Cell_0050DEF0 unknown_24;
};

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

struct Obj_005657A0
{
    char Pad_00[0x13C];
    Entry_005657A0** unknown_13C;

    Entry_005657A0* FUN_005657A0(const Cell_0050DEF0& cell) const;
};
GG_STATIC_ASSERT(offsetof(Obj_005657A0, unknown_13C) == 0x13C);

struct Obj_005B3700
{
    int unknown_0;
    char unknown_4;
    char unknown_5;
    char unknown_6;
    char unknown_7;
    char unknown_8;
    char unknown_9;
    char Pad_0A[6];
    double unknown_10;
    double unknown_18;

    Obj_005B3700();
};
GG_STATIC_ASSERT(offsetof(Obj_005B3700, unknown_10) == 0x10);

struct Slot_005B3A00
{
    char Bytes[0x20];
};

// GLOBAL: GAMEMD 0x00A8E3A8 (32-byte records)
extern "C" Slot_005B3A00 DAT_00A8E3A8[];

struct Obj_005B3A00
{
    char Pad_00[0xAC];
    int unknown_AC;
};
GG_STATIC_ASSERT(offsetof(Obj_005B3A00, unknown_AC) == 0xAC);

struct Iface_005BF500
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3(int value) = 0;
};

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

struct Vector_005C6120
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3() = 0;

    void** unknown_4;
    int Pad_08;
    int Pad_0C;
    int unknown_10;

    void FUN_005C6120();
};

struct Obj_005F9710
{
    char unknown_0;
    char unknown_1;
};

struct Quad_00645C30
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;

    Quad_00645C30(int a, int b, int c, int d);
};

struct Record_00656580
{
    char Bytes[0x18];
};

struct Key_00656580
{
    char Pad_00[0xEF0];
    int unknown_EF0;
};
GG_STATIC_ASSERT(offsetof(Key_00656580, unknown_EF0) == 0xEF0);

struct Obj_00656580
{
    Record_00656580 unknown_0[1];

    Record_00656580* FUN_00656580(const Key_00656580* key);
};


struct Obj_0065AD30
{
    char Pad_00[0xE4];
    int* unknown_E4;

    int FUN_0065AD30(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0065AD30, unknown_E4) == 0xE4);

struct Pair_0065C890
{
    int unknown_0;
    int unknown_4;

    Pair_0065C890(int a, int b);
};

struct Obj_0068BCB0
{
    char Pad_00[0x214];
    int unknown_214;
};
GG_STATIC_ASSERT(offsetof(Obj_0068BCB0, unknown_214) == 0x214);

struct Obj_0068C030
{
    char Pad_00[0x1180];
    int unknown_1180[16];

    int FUN_0068C030(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0068C030, unknown_1180) == 0x1180);

struct Owner_006915D0
{
    char Pad_00[0xA0];
    unsigned int unknown_A0;
};
GG_STATIC_ASSERT(offsetof(Owner_006915D0, unknown_A0) == 0xA0);

struct Cursor_006915D0
{
    char Pad_00[0x24];
    Owner_006915D0* unknown_24;
    char Pad_28[4];
    unsigned int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Cursor_006915D0, unknown_2C) == 0x2C);

#pragma pack(push, 1)
struct Obj_00696F10
{
    char Pad_00[0x4B];
    int unknown_4B;
    int unknown_4F;
    int unknown_53;
    int unknown_57;
    int unknown_5B;
    int unknown_5F;
    int unknown_63;
    int unknown_67;

    int FUN_00696F10() const;
    int FUN_00696F20() const;
    int FUN_00696F50() const;
    int FUN_00696F70() const;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_67) == 0x67);

struct Obj_0069B540
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[0x4C - 0x28];
    int unknown_4C[8];
    int unknown_6C[8];
};
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_6C) == 0x6C);

struct Obj_0069BBE0
{
    char Pad_00[0x30D8];
    char unknown_30D8;
};
GG_STATIC_ASSERT(offsetof(Obj_0069BBE0, unknown_30D8) == 0x30D8);

struct Type_006A46D0
{
    char Pad_00[0x24];
    char unknown_24[1];
};

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

#include "../renderer/color_scheme_find_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0E38
extern const double DAT_007F0E38;
// GLOBAL: GAMEMD 0xB05460
extern double DAT_00B05460;
// GLOBAL: GAMEMD 0xB054A8
extern double DAT_00B054A8;
// GLOBAL: GAMEMD 0xB054B0
extern int DAT_00B054B0;
// GLOBAL: GAMEMD 0xB054B4
extern int DAT_00B054B4;
// GLOBAL: GAMEMD 0xB054B8
extern int DAT_00B054B8;
// GLOBAL: GAMEMD 0xB054C0
extern double DAT_00B054C0;

// FUNCTION: GAMEMD 0x6830A0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006830A0()
{
    DAT_00B054C0 = DAT_00B05460 / DAT_007F0E38;
}

// FUNCTION: GAMEMD 0x6830C0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006830C0()
{
    DAT_00B054A8 = DAT_007E1718 / DAT_00B054C0;
}

// FUNCTION: GAMEMD 0x683240
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00683240()
{
    DAT_00B054B8 = 0;
    DAT_00B054B0 = 0x80;
    DAT_00B054B4 = 0x80;
}

// FUNCTION: GAMEMD 0x6832B0
// Empty function.
void __cdecl FUN_006832B0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x689D30
//
// Read the scenario header's start position, map size and starting-point
// counts, then the numbered waypoints that hold the multiplayer start
// cells. Every field keeps its current value as the INI default, and the
// waypoint table is cleared first so an absent entry reads back as zero.
//
// PARTIAL (94.0%, 94/100 by position; multiset identical; was 8.0%). Two
// levers took it from 8.0%: the clear loop assigns a constructed two-int cell
// (`*clear = Cell(0, 0)`) instead of storing two named zero locals, which is
// what gives retail's two separate zero registers filled in the prologue and
// the plain `TEST ECX,ECX` count test; and the waypoint loop is a counted `for`
// whose key uses `i + 1`, so the increment folds onto the key's `LEA`
// (`MOV EAX,EBX`). What is left is the order inside the loop tail: retail loads
// both halves of the returned cell, stores both, then re-reads the count and
// advances the cursor (`MOV ECX,[EAX]; MOV EAX,[EAX+4]; MOV [EDI],ECX;
// MOV [EDI+4],EAX; ... ADD EDI,8`), where cl stores the first half, advances
// the cursor and stores the second half at `[EDI-4]`. Tried: cursor advance
// before/after the index bump, an indexed `Waypoints[i]` target, a POD cell
// with an inline maker (same 94.0%), a named copy of the returned cell, a
// member-wise copy and a const reference to the returned cell (82.2%).
bool Scenario_00689D30::ReadStartPoints(CCINI_00689D30* ini)
{
    Cell_00689D30* slot = Waypoints;

    StartX = -1;
    StartY = -1;
    Width = -1;
    Height = -1;
    NumberStartingPoints = -1;

    Cell_00689D30* clear = slot;
    for (int n = 8; n != 0; n--) {
        *clear = Cell_00689D30(0, 0);
        clear++;
    }

    StartX = ini->ReadInteger(STR_0083DE68, STR_0083DE70, StartX);
    StartY = ini->ReadInteger(STR_0083DE68, STR_0083DE60, StartY);
    Width = ini->ReadInteger(STR_0083DE68, STR_0082BBE4, Width);
    Height = ini->ReadInteger(STR_0083DE68, STR_0081A7A8, Height);
    NumberStartingPoints =
        ini->ReadInteger(STR_0083DE68, STR_0083DE48, NumberStartingPoints);
    NumCoopHumanStartSpots =
        ini->ReadInteger(STR_0083DE68, STR_0083DE30, NumCoopHumanStartSpots);

    for (int i = 0; i < NumberStartingPoints; i++) {
        char key[12];
        gg_sprintf(key, STR_0083DE24, i + 1);
        *slot = ini->ReadWaypoint(STR_0083DE68, key, *slot);
        slot++;
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0068BCB0
int __fastcall FUN_0068BCB0(Obj_0068BCB0* self)
{
    return ++self->unknown_214;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x68BCC0  ScenarioClass::GetWaypointCoords (__thiscall, ret 0x8)
// Returns the 4-byte CellStruct by value, so retail's RET 0x8 covers the hidden
// return-buffer pointer plus the index. No bounds check — callers are expected
// to have asked IsDefinedWaypoint first.
CellStruct ScenarioClass::GetWaypointCoords(int idx)
{
    return Waypoints[idx];
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x68BD80  (__thiscall)
// True iff waypoint `idx` is in range [0..701] and its stored cell differs from
// the sentinel "undefined" cell. The first mismatching coordinate short-circuits
// to true; an exact match (both X and Y equal the sentinel) is "not defined".
bool ScenarioClass::IsDefinedWaypoint(int idx)
{
    if (idx < 702 && idx >= 0 &&
        (Waypoints[idx].X != WaypointUndefined.X ||
         Waypoints[idx].Y != WaypointUndefined.Y))
    {
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0068C030
// Entry `index` of the sixteen at +0x1180, or -1 out of range.
int Obj_0068C030::FUN_0068C030(int index) const
{
    if (index >= 0 && index < 16) {
        return unknown_1180[index];
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x68C9C0  ColorScheme::FindByName (__fastcall, static)
// Return the index of the scheme matching this name and shade, creating it
// first if it does not exist. The create path does not return the new object —
// it falls back into the scan, which then finds it. Writing that as an outer
// `for (;;)` is what produces retail's two backward jumps to 0x68C9D3.
//
// The constructor is declared `throw()`: `new` with a throwing constructor
// makes VC6 emit an SEH frame that retail does not have (§4.6).
//
// Argument order to _stricmp is (name, candidate), read off the push order —
// the opposite of HouseTypeClass::FindIndexOfName's inner compare. Getting it
// backwards costs two instructions and 3.8%.
int __fastcall ColorScheme::FindByName(const char* name, HSVClass* hsv,
                                       PaletteClass* pal1, PaletteClass* pal2,
                                       int shade)
{
    for (;;)
    {
        for (int i = 0; i < ColorSchemeArray.Count; i++)
        {
            if (_stricmp(name, ((ColorScheme**)ColorSchemeArray.Items)[i]->Name) == 0
             && ((ColorScheme**)ColorSchemeArray.Items)[i]->unknown_310 == shade)
            {
                return i;
            }
        }

        new ColorScheme(name, hsv, pal1, pal2, shade, true);
    }
}
