// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Score.CPP. The name is the source-file string at 0x83e3c4
//   in retail gamemd.exe v1.001, passed by the assert at 0x68d646 inside this object's
//   code range (0x68cb30-0x6911af). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// A blinking text cursor drawn by a __thiscall member (`ret 8`, x and y on
// the stack) of a class whose only touched members are a surface pointer at
// +0x08 and a colour at +0x18. A function-local static countdown timer
// (guard bit 0 of 0xB054F0, object at 0xB05528, empty atexit thunk 0x690150)
// toggles the visible flag 0xB05560 every 5 ticks. The clock member's
// GetTime is 0x6C8C40 (`timeGetTime() >> 4`, __thiscall on the clock word).
//
// Score screen animation and campaign score classes.
//
// Scalar deleting destructors of classes whose destructor is empty. Each one
// stores the vtable of the class that declares the destructor (the derived
// classes add nothing to it), frees the object when bit 0 of the flag is set,
// and returns `this`. Retail's 32-byte shape:
//
//     MOV AL,[ESP+4]; PUSH ESI; MOV ESI,ECX; TEST AL,1; MOV [ESI],<vtable>
//     JZ +9; PUSH ESI; CALL 0x7C8B3D; ADD ESP,4; MOV EAX,ESI; POP ESI; RET 4
//
// Class names and the base relation come from the retail RTTI descriptors;
// the owning class of each body is the class whose vtable slot 0 holds it.
// Slot 0 is modelled as an ordinary virtual holding the deleting wrapper, as
// FileClass does in match/core/ram_file_class.h: these classes are never
// constructed in this translation unit, so cl would not emit their tables or
// a compiler-generated `??_G`. The classes are opaque views; no member is
// touched, so there is no layout to assert.

#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"


#include "../_layout/geometry2d.h"
#include "../_layout/score_font_class.h"
#include "../_layout/ms_anim.h"

// Draw surface: slot +0x08 is a rectangle copy, slot +0x30 a line draw.
class Surface_0068FFE0
{
public:
    virtual ~Surface_0068FFE0();                                   // +0x00
    virtual void vslot_04();                                       // +0x04
    virtual int vf_2(RectangleStruct& dest, Surface_0068FFE0* source,
                          RectangleStruct& source_rect, int trans, int blit); // +0x08
    virtual void vslot_0C();                                       // +0x0C
    virtual void vslot_10();                                       // +0x10
    virtual void vslot_14();                                       // +0x14
    virtual void vslot_18();                                       // +0x18
    virtual void vslot_1C();                                       // +0x1C
    virtual void vslot_20();                                       // +0x20
    virtual void vslot_24();                                       // +0x24
    virtual void vslot_28();                                       // +0x28
    virtual void vslot_2C();                                       // +0x2C
    virtual int vf_12(Point2D& start, Point2D& end, int color); // +0x30
};

// GLOBAL: GAMEMD 0x88730C
extern Surface_0068FFE0* DAT_0088730c;
// GLOBAL: GAMEMD 0x887310
extern Surface_0068FFE0* DAT_00887310;
// GLOBAL: GAMEMD 0xB05588
extern int DAT_00b05588;
// GLOBAL: GAMEMD 0xB05560
extern int DAT_00b05560;

class FrameClock_006C8C40
{
public:
    int unknown_00;   // +0x00

    // FUNCTION: GAMEMD 0x6C8C40 (decl; reloc)
    int GetTime() const;
};

class CountdownTimer_0068FFE0
{
public:
    int Started;                  // +0x00
    FrameClock_006C8C40 Clock;    // +0x04
    int TimeLeft;                 // +0x08

    CountdownTimer_0068FFE0(int time = 0) { Started = Clock.GetTime(); TimeLeft = time; }
    ~CountdownTimer_0068FFE0() {}

    int Time() const
    {
        int left = TimeLeft;
        if (Started != -1) {
            int elapsed = Clock.GetTime() - Started;
            if (elapsed >= left) return 0;
            left -= elapsed;
        }
        return left;
    }
};
GG_STATIC_ASSERT(offsetof(CountdownTimer_0068FFE0, Started) == 0x00);
GG_STATIC_ASSERT(offsetof(CountdownTimer_0068FFE0, Clock) == 0x04);
GG_STATIC_ASSERT(offsetof(CountdownTimer_0068FFE0, TimeLeft) == 0x08);

class BlinkCursorHost_0068FFE0
{
public:
    void* vtable_00;                    // +0x00
    int unknown_04;                     // +0x04
    Surface_0068FFE0* Surface;          // +0x08
    int unknown_0C;                     // +0x0C
    int unknown_10;                     // +0x10
    int unknown_14;                     // +0x14
    int CursorColor;                    // +0x18

    void FUN_0068FFE0(int x, int y);
};
GG_STATIC_ASSERT(offsetof(BlinkCursorHost_0068FFE0, Surface) == 0x08);
GG_STATIC_ASSERT(offsetof(BlinkCursorHost_0068FFE0, CursorColor) == 0x18);

#include "../core/trivial_tu202_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0EA0
extern const double DAT_007F0EA0;
// GLOBAL: GAMEMD 0xB05510
extern double DAT_00B05510;

// SYNTHETIC: GAMEMD 0x0068CB60
// GLOBAL: GAMEMD 0x00B05578
double DAT_00B05578 = DAT_00B05510 / DAT_007F0EA0;

// SYNTHETIC: GAMEMD 0x0068CB80
// GLOBAL: GAMEMD 0x00B05558
double DAT_00B05558 = DAT_007E1718 / DAT_00B05578;

// SYNTHETIC: GAMEMD 0x0068CD00
// GLOBAL: GAMEMD 0x00B05568
MathTblCoord DAT_00B05568;

#include "../_layout/house_class.h"
#include "../_layout/house_interfaces.h"

// The score screen object; the efficiency calculation reads nothing of its own.
struct ScoreHost_0068ED80
{
    // FUNCTION: GAMEMD 0x68ED80
    int FUN_0068ED80(HouseClass* house);
};


// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x68ED80
// PARTIAL: 95.0% (instruction multiset identical, 120 of 120). Deltas: the two loads of StartingCredits and
// HarvestedCredits ahead of the denominator come out in the opposite order (EAX/EDX swapped), and the denominator and
// the vf_06 result swap their two stack slots ([esp+0x1c] / [esp+0x14]) in the money branch.
// The mission efficiency of a house and its allies: the share of what was built that is still standing,
// averaged with the share of the money that is still held, as a percentage.
int ScoreHost_0068ED80::FUN_0068ED80(HouseClass* house)
{
    int remaining = 0;
    int total = 0;
    for (int i = 0; i < HouseClass_Array.Count; i++) {
        HouseClass* other = HouseClass_Array.Items[i];
        if ((house->IsAlliedWith(other) && other->IsAlliedWith(house)) || house == other) {
            remaining += other->ActiveBuildingTypes.FUN_0049FB60();
            remaining += other->ActiveUnitTypes.FUN_0049FB60();
            remaining += other->ActiveInfantryTypes.FUN_0049FB60();
            remaining += other->ActiveAircraftTypes.FUN_0049FB60();
            total += other->TotalKilledBuildings + other->TotalKilledUnits;
        }
    }
    total += remaining;
    FUN_004068E0("Remaining: %ld, Total: %ld\n", remaining, total);
    float buildEconomy;
    if (total > 0)
        buildEconomy = (float)remaining / total;
    else
        buildEconomy = 0;
    FUN_004068E0("BuildEconomy = %f\n", buildEconomy);
    FUN_004068E0("Money: %ld, Harvested: %ld, Initial: %ld\n", house->vf_06(), house->HarvestedCredits, house->StartingCredits);
    int spent = house->StartingCredits;
    spent += house->HarvestedCredits;
    float moneyEconomy;
    if (spent > 0)
        moneyEconomy = (float)house->vf_06() / spent;
    else
        moneyEconomy = 0;
    FUN_004068E0("MoneyEconomy = %f\n", moneyEconomy);
    int efficiency = (int)(100.0 * ((buildEconomy + moneyEconomy) * 0.5));
    FUN_004068E0("Efficiency: %ld\n", efficiency);
    return efficiency;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x68FFE0
void BlinkCursorHost_0068FFE0::FUN_0068FFE0(int x, int y)
{
    static CountdownTimer_0068FFE0 blink;
    RectangleStruct rect;

    y += 14;
    if (x != DAT_00b05588) {
        rect.X = DAT_00b05588;
        rect.Y = y;
        rect.Width = 11;
        rect.Height = 1;
        DAT_0088730c->vf_2(rect, DAT_00887310, rect, 0, 1);
        DAT_00b05588 = x;
    }

    if (DAT_00b05560) {
        Point2D start;
        Point2D end;
        end.X = x + 10;
        end.Y = y;
        start.X = x;
        start.Y = y;
        DAT_0088730c->vf_12(start, end, CursorColor);
    } else {
        rect.X = x;
        rect.Y = y;
        rect.Width = 11;
        rect.Height = 1;
        DAT_0088730c->vf_2(rect, Surface, rect, 0, 1);
    }

    if (blink.Time() == 0) {
        DAT_00b05560 ^= 1;
        blink = CountdownTimer_0068FFE0(5);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x690150
// Empty function.
void __cdecl FUN_00690150()
{
}


#include "../_layout/score_full_font_class.h"
#include "../_layout/score_big_font_class.h"
#include "../platform/ccfile_class.h"

// FUNCTION: GAMEMD 0x690640 (decl; reloc) -- loads the shared glyph tables, ECX = font.
void __fastcall FUN_00690640(ScoreFontClass* font);
// GLOBAL: GAMEMD 0xB0558C -- number of live fonts.
extern int DAT_00B0558C;
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc), ECX=path, DL=force.
void* __fastcall FUN_005B40B0(const char* path, bool force);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// The 0x690580 body, expanded inline into the derived font constructors.
inline ScoreFontClass::ScoreFontClass(const InlineInit&)
    : unknown_04(0), unknown_08(0), unknown_0C(0), unknown_14(0)
{
    FUN_00690640(this);
    DAT_00B0558C++;
}


// GLOBAL: GAMEMD 0xB0558C -- number of live fonts.
extern int DAT_00B0558C;

struct SharedGlyphSlot_00B05590
{
    void* Table;     // +0x00
    bool Loaded;     // +0x04
    char unknown_05[3];
};
// GLOBAL: GAMEMD 0xB05590 -- the three shared glyph tables.
extern SharedGlyphSlot_00B05590 DAT_00B05590[3];

// FUNCTION: GAMEMD 0x690580
ScoreFontClass::ScoreFontClass()
    : unknown_04(0), unknown_08(0), unknown_0C(0), unknown_14(0)
{
    FUN_00690640(this);
    DAT_00B0558C++;
}

// FUNCTION: GAMEMD 0x6905B0
ScoreFontClass::ScoreFontClass(int a1, int a2, int a3, int a4)
    : unknown_04(a1), unknown_08(a2), unknown_0C(a3), unknown_14(a4)
{
    FUN_00690640(this);
    DAT_00B0558C++;
}

// FUNCTION: GAMEMD 0x6905F0
ScoreFontClass::~ScoreFontClass()
{
    if (unknown_0C != 0 && unknown_10 == 1) {
        operator delete((void*)unknown_0C);
        unknown_0C = 0;
        unknown_10 = 0;
    }
    DAT_00B0558C--;
    if (DAT_00B0558C == 0) {
        for (int i = 0; i < 3; i++) {
            DAT_00B05590[i].Table = 0;
            DAT_00B05590[i].Loaded = false;
        }
    }
}
// SYNTHETIC: GAMEMD 0x691040 -- ScoreFontClass::`scalar deleting destructor' (vtable 0x7F0EF0 slot 0).

// FUNCTION: GAMEMD 0x6907A0
int ScoreFontClass::vf_2(const unsigned short* text)
{
    int width = 0;
    unsigned short ch = *text;
    while (ch != 0) {
        text++;
        width += vf_1(ch) + 1;
        ch = *text;
    }
    return width;
}

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

// GLOBAL: GAMEMD 0xA8ED80 -- set once the pending operation has completed.
extern bool DAT_00A8ED80;

// FUNCTION: GAMEMD 0x5D4D50 (decl; reloc) -- pump pending window messages.
void FUN_005D4D50();

// A child object stored in the host's list (only vtable slots 1 and 2 are used here).
struct Child_006904C0 {
    virtual void Slot0();
    virtual void Begin();
    virtual void End();
};

struct Host_006904C0 {
    char _pad00[0x20];
    Child_006904C0** Children;   // +0x20
    char _pad24[0x08];
    int ChildCount;              // +0x2C

    // FUNCTION: GAMEMD 0x6904C0 (__thiscall)
    void FUN_006904C0();
};

// FUNCTION: GAMEMD 0x6904C0
// Tell every child to begin, wait (pumping messages) until the completion flag is set, then
// tell every child to end. Does nothing when the flag is already set.
void Host_006904C0::FUN_006904C0()
{
    if (DAT_00A8ED80 != true) {
        for (int i = 0; i < ChildCount; i++) {
            Children[i]->Begin();
        }
        while (!DAT_00A8ED80) {
            Sleep(500);
            FUN_005D4D50();
        }
        for (int j = 0; j < ChildCount; j++) {
            Children[j]->End();
        }
    }
}

extern "C" int __cdecl _stricmp(const char*, const char*);

// FUNCTION: GAMEMD 0x407000 (decl; reloc) -- true once the session object exists.
int SessionExists();

struct NamedEntry_00690530 {
    const char* Name;   // +0x00
};

struct NameList_00690530 {
    char unknown_00[0x38];
    NamedEntry_00690530** Items;   // +0x38
    char unknown_3C[8];
    int Count;                     // +0x44

    // FUNCTION: GAMEMD 0x690530 (__thiscall)
    void Find(const char* name, int unused);
};

// FUNCTION: GAMEMD 0x690530
// Walk the entry list comparing names case-insensitively until one matches.
void NameList_00690530::Find(const char* name, int unused)
{
    if (name != 0 && SessionExists()) {
        for (int i = 0; i < Count; i++) {
            const char* entry = Items[i]->Name;
            if (_stricmp(name, entry) == 0)
                break;
        }
    }
}

// FUNCTION: GAMEMD 0x690A10
// The full-size score font: its shape comes from the mix files, else from disk.
ScoreFullFontClass::ScoreFullFontClass(ConvertClass* convert) : ScoreFontClass(InlineInit())
{
    unknown_10 = 0;
    unknown_0C = (int)FUN_005B40B0("FULLFNT3.SHP", false);
    if (unknown_0C == 0) {
        CCFileClass file("FULLFNT3.SHP");
        unknown_0C = (int)file.ReadWholeFile();
        unknown_10 = 1;
        file.Close();
        FUN_004068E0("ScoreScreen: Loaded FULLFNT3.SHP\n");
    }
    unknown_04 = 0xb;
    unknown_14 = (int)convert;
    unknown_08 = 0x15;
}

// FUNCTION: GAMEMD 0x690AE0
// The big score font, loaded the same way.
ScoreBigFontClass::ScoreBigFontClass(ConvertClass* convert) : ScoreFontClass(InlineInit())
{
    unknown_10 = 0;
    unknown_0C = (int)FUN_005B40B0("BIGFONT.SHP", false);
    if (unknown_0C == 0) {
        CCFileClass file("BIGFONT.SHP");
        unknown_0C = (int)file.ReadWholeFile();
        unknown_10 = 1;
        file.Close();
        FUN_004068E0("ScoreScreen: Loaded BIGFONT.SHP\n");
    }
    unknown_04 = 0x14;
    unknown_14 = (int)convert;
    unknown_08 = 0x23;
}


struct Obj_00690EF0;

// FUNCTION: GAMEMD 0x407000 (decl; reloc)
int __cdecl FUN_00407000();
// LIBRARY: GAMEMD 0x7D5408 (decl; reloc)
int __cdecl FUN_007D5408(int);

struct Obj_00690EF0
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    unsigned char unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x690EF0
    Obj_00690EF0* FUN_00690EF0(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_00690EF0, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00690EF0, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00690EF0, unknown_08) == 0x8);

// VTABLE: GAMEMD 0x7F0EDC
class ScoreAnimClass
{
public:
    ScoreAnimClass(int x, int y, int param);
    virtual ~ScoreAnimClass() {}

    int     X;       // +0x04
    int     Y;       // +0x08
    MSTimer Timer;   // +0x0C
    int     Param;   // +0x18
};
GG_STATIC_ASSERT(offsetof(ScoreAnimClass, X) == 0x4);
GG_STATIC_ASSERT(offsetof(ScoreAnimClass, Y) == 0x8);
GG_STATIC_ASSERT(offsetof(ScoreAnimClass, Timer) == 0xC);
GG_STATIC_ASSERT(offsetof(ScoreAnimClass, Param) == 0x18);
GG_STATIC_ASSERT(sizeof(ScoreAnimClass) == 0x1C);

// VTABLE: GAMEMD 0x7F0EC8
class ScoreTimeClass : public ScoreAnimClass
{
public:
    ScoreTimeClass(int x, int y, int param, int a, int b, int c);
    virtual ~ScoreTimeClass() {}

    int Field1C;   // +0x1C
    int Field20;   // +0x20
    int Field24;   // +0x24
    int Field28;   // +0x28
};
GG_STATIC_ASSERT(offsetof(ScoreTimeClass, Field1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(ScoreTimeClass, Field28) == 0x28);
GG_STATIC_ASSERT(sizeof(ScoreTimeClass) == 0x2C);

// VTABLE: GAMEMD 0x7F0EB4
class ScorePrintClass : public ScoreAnimClass
{
public:
    ScorePrintClass(int a, int b, int c, int d, char e);
    virtual ~ScorePrintClass() {}

    int  Field1C;   // +0x1C
    int  Field20;   // +0x20
    char Field24;   // +0x24
    int  Field28;   // +0x28
};
GG_STATIC_ASSERT(offsetof(ScorePrintClass, Field1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(ScorePrintClass, Field24) == 0x24);
GG_STATIC_ASSERT(offsetof(ScorePrintClass, Field28) == 0x28);
GG_STATIC_ASSERT(sizeof(ScorePrintClass) == 0x2C);

// FUNCTION: GAMEMD 0x690BB0
// Builds the timed score animation: the base fields, then the three extra words.
ScoreTimeClass::ScoreTimeClass(int x, int y, int param, int a, int b, int c)
    : ScoreAnimClass(x, y, param), Field1C(0), Field20(a), Field24(b), Field28(c)
{
}

// FUNCTION: GAMEMD 0x690D10
// Builds the printed score animation (first argument is the base parameter).
ScorePrintClass::ScorePrintClass(int a, int b, int c, int d, char e)
    : ScoreAnimClass(b, c, a), Field1C(0), Field20(0), Field24(e), Field28(d)
{
}

// FUNCTION: GAMEMD 0x690EF0
// Branching.
Obj_00690EF0* Obj_00690EF0::FUN_00690EF0(int a1, int a2)
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
    int c0 = FUN_00407000();
    if (c0 != 0)
    {
        int c1 = FUN_007D5408(a1);
        unknown_00 = c1;
        return this;
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x690F20
// Branching.
void Obj_00690F20::FUN_00690F20()
{
    if (unknown_00 != 0)
    {
        FUN_007C93E8(unknown_00);
    }
}

// FUNCTION: GAMEMD 0x690F30
// Stamps the clock and stores the position and parameter.
ScoreAnimClass::ScoreAnimClass(int x, int y, int param) : X(x), Y(y), Param(param)
{
}

// Compiler-generated scalar deleting destructors, emitted with the vtables above.
// SYNTHETIC: GAMEMD 0x690FE0
// SYNTHETIC: GAMEMD 0x691000
// SYNTHETIC: GAMEMD 0x691020

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB05560
int DAT_00b05560;
// GLOBAL: GAMEMD 0xB05588
int DAT_00b05588;
// GLOBAL: GAMEMD 0x7F0EA0
extern const double DAT_007F0EA0 = 60.0;
// GLOBAL: GAMEMD 0x887310
Surface_0068FFE0* DAT_00887310;
// GLOBAL: GAMEMD 0xB0558C
int DAT_00B0558C;
// GLOBAL: GAMEMD 0xB05590
SharedGlyphSlot_00B05590 DAT_00B05590[3];
// END defined globals
