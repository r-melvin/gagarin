// Provenance: own-binary-via-Ghidra
// A blinking text cursor drawn by a __thiscall member (`ret 8`, x and y on
// the stack) of a class whose only touched members are a surface pointer at
// +0x08 and a colour at +0x18. A function-local static countdown timer
// (guard bit 0 of 0xB054F0, object at 0xB05528, empty atexit thunk 0x690150)
// toggles the visible flag 0xB05560 every 5 ticks. The clock member's
// GetTime is 0x6C8C40 (`timeGetTime() >> 4`, __thiscall on the clock word).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct RectangleStruct
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};

struct Point2D
{
    int X;        // +0x00
    int Y;        // +0x04
};

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
