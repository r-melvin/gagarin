// SPDX-License-Identifier: GPL-3.0-or-later
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
#include "../_rt/gg_static_assert.h"


#include "../_layout/geometry2d.h"

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

#include "trivial_tu202_methods.h"

// VTABLE: GAMEMD 0x7E4AB8
class CampaignEndScoreClass
{
public:
    ~CampaignEndScoreClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7E4AAC
class CampaignScoreClass
{
public:
    ~CampaignScoreClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7F0EDC
class ScoreAnimClass
{
public:
    ~ScoreAnimClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007F0EC8
class ScoreTimeClass : public ScoreAnimClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007F0EB4
class ScorePrintClass : public ScoreAnimClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

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
// GLOBAL: GAMEMD 0xB05558
extern double DAT_00B05558;
// GLOBAL: GAMEMD 0xB05568
extern int DAT_00B05568;
// GLOBAL: GAMEMD 0xB0556C
extern int DAT_00B0556C;
// GLOBAL: GAMEMD 0xB05570
extern int DAT_00B05570;
// GLOBAL: GAMEMD 0xB05578
extern double DAT_00B05578;

// FUNCTION: GAMEMD 0x68CB60
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0068CB60()
{
    DAT_00B05578 = DAT_00B05510 / DAT_007F0EA0;
}

// FUNCTION: GAMEMD 0x68CB80
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0068CB80()
{
    DAT_00B05558 = DAT_007E1718 / DAT_00B05578;
}

// FUNCTION: GAMEMD 0x68CD00
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0068CD00()
{
    DAT_00B05570 = 0;
    DAT_00B05568 = 0x80;
    DAT_00B0556C = 0x80;
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


struct Obj_00690EF0;

// FUNCTION: GAMEMD 0x407000 (decl; reloc)
int __cdecl FUN_00407000();
// FUNCTION: GAMEMD 0x7D5408 (decl; reloc)
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x690FE0 -- ScoreAnimClass scalar deleting destructor
void* ScoreAnimClass::DeletingDtor(unsigned int flags)
{
    this->~ScoreAnimClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x691000 -- ScoreTimeClass scalar deleting destructor
void* ScoreTimeClass::DeletingDtor(unsigned int flags)
{
    this->~ScoreTimeClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x691020 -- ScorePrintClass scalar deleting destructor
void* ScorePrintClass::DeletingDtor(unsigned int flags)
{
    this->~ScorePrintClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
