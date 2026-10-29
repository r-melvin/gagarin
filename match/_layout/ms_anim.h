// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Canonical MSAnim hierarchy (the map-stage screen animations), read from the retail gamemd.exe v1.001.
//   RTTI (complete object locators at vtable-4):
//     0x7EE8E8 .?AVMSAnim@@                      (root, 9 slots)
//     0x7EE910 .?AVMSShapeAnim@@          : MSAnim
//     0x7EE938 .?AVMSFadeAnim@@           : MSShapeAnim
//     0x7EE960 .?AVMSOverlayAnim@@        : MSFadeAnim
//     0x7F7104 .?AVMSFrameAnim@@          : MSAnim
//     0x7F7354 .?AVAnim@Voices@WorldDominationTour@@ : MSAnim
//   The base vtable 0x7EE8E8: slot 0 0x5CEB60 (scalar deleting destructor), 1 0x5CEAC0 SetEnabled, 2 0x5CEAD0
//   PauseTimer, 3 0x5CEB20 ResumeTimer, 4/5/6 0x4C9150 (pure: Update, Draw, GetRect), 7 0x5CEB40 and 8 0x5CEB50.
//   Base layout (0x1C bytes): vptr; +0x04 / +0x08 the position; +0x0C Enabled; +0x10..+0x18 a timer
//   (StartTime, a clock word whose GetTime 0x6C8C40 is called with its address, Remaining).
//   The constructors expand the base constructor inline and store no base vptr: the timer member's
//   constructor (clock stamp, nothing banked) is what makes VC6 drop the base vptr store, and each derived
//   vptr is stored after the member initialisers and before the body. The base destructor 0x5CB6C0 is out of
//   line (`MOV [ECX],0x7EE8E8; RET`).
//   MSShapeAnim 0x40 bytes: Buffer (+0x1C, the shape loaded through 0x4A3970 with the ownership flag +0x3C),
//   +0x20/+0x24 the caller's numbers, Frame (+0x28), +0x2C, LastFrame (+0x30, frame count minus one), a flag at
//   +0x34, Flags (+0x38). MSFadeAnim adds +0x40/+0x44 (0x48 bytes); MSOverlayAnim adds a byte at +0x48 (0x4C).
#ifndef GG_MATCH_LAYOUT_MS_ANIM_H
#define GG_MATCH_LAYOUT_MS_ANIM_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "geometry2d.h"

// The clock member's tick reader. FUNCTION: GAMEMD 0x6C8C40 (decl; reloc).
struct MSClockClass
{
    // The clock is one dword; retail takes the address of this member and calls the reader.
    int Value;   // +0x00

    int GetTime();
};
GG_STATIC_ASSERT(sizeof(MSClockClass) == 4);

// The animations pass the engine's RectangleStruct (X, Y, Width, Height) around by value.
class MouseSurfaceView;

// The decoded shape file MSShapeAnim owns at +0x1C: a short header carrying the frame size and count.
struct MSShapeFile
{
    short Unknown0;   // +0x00
    short Width;      // +0x02
    short Height;     // +0x04
    short Frames;     // +0x06

    // FUNCTION: GAMEMD 0x69E7E0 (decl; reloc) -- the rectangle of one frame, written to the caller's buffer
    // and handed back.
    RectangleStruct* GetFrameRect(RectangleStruct* out, unsigned int frame);
};
GG_STATIC_ASSERT(offsetof(MSShapeFile, Width) == 2 && offsetof(MSShapeFile, Frames) == 6);

// FUNCTION: GAMEMD 0x4A3970 (decl; reloc) -- load a shape by name; the ownership flag arrives in EDX and is
// cleared before the lookup.
MSShapeFile* __fastcall MSLoadShape(const char* name, bool* owned);

// The three dwords MSAnim carries at +0x10..+0x18. The constructor stamps the clock and banks nothing.
struct MSTimer
{
    int          StartTime;   // +0x00
    MSClockClass Clock;       // +0x04
    int          Remaining;   // +0x08

    MSTimer()
    {
        StartTime = Clock.GetTime();
        Remaining = 0;
    }

    // A clock stamped now with the given interval banked (0x5D2410 builds one with an interval of 1).
    MSTimer(int remaining)
    {
        StartTime = Clock.GetTime();
        Remaining = remaining;
    }

    // The time still on the clock: zero once the interval has run out, the whole interval while paused
    // (a paused timer stamps its start as -1).
    int TimeLeft()
    {
        int left = Remaining;
        if (StartTime != -1) {
            int elapsed = Clock.GetTime() - StartTime;
            if (elapsed < left) {
                left -= elapsed;
            } else {
                left = 0;
            }
        }
        return left;
    }
};
GG_STATIC_ASSERT(sizeof(MSTimer) == 0xC);

// VTABLE: GAMEMD 0x7EE8E8
class MSAnim
{
public:
    MSAnim() : Field04(0), Field08(0), Enabled(false) {}
    MSAnim(int x, int y) : Field04(x), Field08(y), Enabled(true) {}
    virtual ~MSAnim();                                     // slot 0, 0x5CEB60 (body 0x5CB6C0)
    virtual void SetEnabled(bool on);                      // slot 1, 0x5CEAC0
    virtual void PauseTimer();                             // slot 2, 0x5CEAD0
    virtual void ResumeTimer();                            // slot 3, 0x5CEB20
    virtual bool Update(MouseSurfaceView* context, RectangleStruct* out) = 0;     // slot 4, 0x4C9150 (pure)
    virtual void Draw(MouseSurfaceView* context, RectangleStruct* area) = 0;      // slot 5, 0x4C9150 (pure)
    virtual RectangleStruct GetRect() = 0;                          // slot 6, 0x4C9150 (pure)
    virtual bool vf_7();                                   // slot 7, 0x5CEB40
    virtual void Attach(void* target);                     // slot 8, 0x5CEB50

    // The time still on the clock; forced inline into MSPrintAnim::Update (0x5CDC50), defined with it.
    __forceinline int TimeLeft();

    int     Field04;    // +0x04
    int     Field08;    // +0x08
    bool    Enabled;    // +0x0C
    MSTimer Timer;      // +0x10 .. +0x18
};
GG_STATIC_ASSERT(sizeof(MSAnim) == 0x1C
              && offsetof(MSAnim, Field04) == 0x04
              && offsetof(MSAnim, Field08) == 0x08
              && offsetof(MSAnim, Enabled) == 0x0C
              && offsetof(MSAnim, Timer) == 0x10);

// VTABLE: GAMEMD 0x7EE910
class MSShapeAnim : public MSAnim
{
public:
    // FUNCTION: GAMEMD 0x5CB6D0
    MSShapeAnim(const char* name, int x, int y, int field20, int field24, bool field34, unsigned int flags);
    // slot 0, 0x5CEB80 (scalar deleting), out of line 0x5CB750: hand the decoded buffer back only when this object owns it.
    virtual ~MSShapeAnim();
    virtual bool Update(MouseSurfaceView* context, RectangleStruct* out);         // slot 4, 0x5CB880
    virtual void Draw(MouseSurfaceView* context, RectangleStruct* area);          // slot 5, 0x5CBB80
    virtual RectangleStruct GetRect();                              // slot 6, 0x5CBCB0
    // FUNCTION: GAMEMD 0x5CB790 -- jump to a frame, redrawing the area it covered.
    void SetFrame(unsigned int frame);
    // FUNCTION: GAMEMD 0x5CB840 -- store +0x2C, clamped below the frame count.
    void FUN_005CB840(unsigned int value);
    // FUNCTION: GAMEMD 0x5CB860 -- store LastFrame, clamped below the frame count.
    void FUN_005CB860(unsigned int value);

    MSShapeFile* Buffer;     // +0x1C
    int          Field20;    // +0x20
    int          Field24;    // +0x24
    unsigned int Frame;      // +0x28 current frame
    int          Field2C;    // +0x2C
    int          LastFrame;  // +0x30 frame count minus one
    bool         Field34;    // +0x34
    unsigned int Flags;      // +0x38 (bit 9: centre on the frame)
    bool         OwnsBuffer; // +0x3C
};
GG_STATIC_ASSERT(offsetof(MSShapeAnim, Buffer) == 0x1C
              && offsetof(MSShapeAnim, Frame) == 0x28
              && offsetof(MSShapeAnim, LastFrame) == 0x30
              && offsetof(MSShapeAnim, Field34) == 0x34
              && offsetof(MSShapeAnim, Flags) == 0x38
              && offsetof(MSShapeAnim, OwnsBuffer) == 0x3C
              && sizeof(MSShapeAnim) == 0x40);

// VTABLE: GAMEMD 0x7EE938
class MSFadeAnim : public MSShapeAnim
{
public:
    // FUNCTION: GAMEMD 0x5CBD20
    MSFadeAnim(const char* name, int x, int y, int field20, int field24, int field38, int field44);
    // FUNCTION: GAMEMD 0x5CC690 -- clear +0x40.
    void FUN_005CC690();
    // FUNCTION: GAMEMD 0x5CC6A0 -- clear +0x40 and set the frame.
    void FUN_005CC6A0(int frame);
    virtual ~MSFadeAnim() {}                               // slot 0, 0x5CEBD0 (scalar deleting)
    virtual bool Update(MouseSurfaceView* context, RectangleStruct* out);         // slot 4, 0x5CBDA0
    virtual void Draw(MouseSurfaceView* context, RectangleStruct* area);          // slot 5, 0x5CC110

    unsigned int unknown_40;   // +0x40
    int unknown_44;            // +0x44
};
GG_STATIC_ASSERT(offsetof(MSFadeAnim, unknown_40) == 0x40
              && offsetof(MSFadeAnim, unknown_44) == 0x44
              && sizeof(MSFadeAnim) == 0x48);

// VTABLE: GAMEMD 0x7EE960
class MSOverlayAnim : public MSFadeAnim
{
public:
    // FUNCTION: GAMEMD 0x5CC250
    MSOverlayAnim(const char* name, int x, int y, int field20, int field24, int field44,
                  unsigned char field48, int frame, bool quick);
    virtual ~MSOverlayAnim() {}                            // slot 0, 0x5CEC20 (scalar deleting)
    virtual bool Update(MouseSurfaceView* context, RectangleStruct* out);         // slot 4, 0x5CC330
    virtual void Draw(MouseSurfaceView* context, RectangleStruct* area);          // slot 5, 0x5CC550
    virtual bool vf_7();                                   // slot 7, 0x5CC740
    virtual void Attach(void* target);                     // slot 8, 0x5CC6C0

    unsigned char unknown_48;   // +0x48
};
GG_STATIC_ASSERT(offsetof(MSOverlayAnim, unknown_48) == 0x48 && sizeof(MSOverlayAnim) == 0x4C);

// VTABLE: GAMEMD 0x7F7104
class MSFrameAnim : public MSAnim
{
public:
    // FUNCTION: GAMEMD 0x767E90
    MSFrameAnim();
    virtual ~MSFrameAnim() {}                          // slot 0, 0x769BD0 (scalar deleting)
    virtual bool   Update(MouseSurfaceView* context, RectangleStruct* out);   // slot 4, 0x767ED0
    virtual void   Draw(MouseSurfaceView* context, RectangleStruct* area);    // slot 5, 0x767EF0
    virtual RectangleStruct GetRect();                          // slot 6, 0x767F80
};
GG_STATIC_ASSERT(sizeof(MSFrameAnim) == 0x1C);

// The object the voice animation forwards its draw-side slots to (the member at +0x1C). Only the helper those
// slots run is named; the name is the helper's address.
// Slot 1 reaches a stopwatch at +0x3AC, a polymorphic member at +0x3C0 (its slot 3 is run) and a count at +0x3D0.
struct Obj_00771620_Sub3C0
{
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
};

struct Obj_00771620
{
    // FUNCTION: GAMEMD 0x771620 (decl; reloc)
    void FUN_00771620();

    char                unknown_000[0x3AC];
    MSTimer             Stopwatch;      // +0x3AC
    char                unknown_3B8[8];
    Obj_00771620_Sub3C0 Sub3C0;         // +0x3C0
    char                unknown_3C4[12];
    int                 Count;          // +0x3D0
};
GG_STATIC_ASSERT(offsetof(Obj_00771620, Stopwatch) == 0x3AC && offsetof(Obj_00771620, Sub3C0) == 0x3C0
              && offsetof(Obj_00771620, Count) == 0x3D0);

// The world-domination-tour voice animation (RTTI .?AVAnim@Voices@WorldDominationTour@@, vtable 0x7F7354):
// it overrides every non-destructor slot of MSAnim and adds one word at +0x1C.
namespace WorldDominationTour {
namespace Voices {


// VTABLE: GAMEMD 0x7F7354
class Anim : public MSAnim
{
public:
    // FUNCTION: GAMEMD 0x771850
    Anim(Obj_00771620* owner);
    virtual ~Anim();                                   // slot 0, 0x771A30 (scalar deleting); out of line 0x771890
    virtual void SetEnabled(bool on);                  // slot 1, 0x7718A0
    virtual void PauseTimer();                         // slot 2, 0x771900
    virtual void ResumeTimer();                        // slot 3, 0x771950
    virtual bool Update(MouseSurfaceView* context, RectangleStruct* out);     // slot 4, 0x771970
    virtual void Draw(MouseSurfaceView* context, RectangleStruct* area);      // slot 5, 0x771980
    virtual RectangleStruct GetRect();                          // slot 6, 0x771990
    virtual bool vf_7();                               // slot 7, 0x7719C0
    virtual void Attach(void* target);                 // slot 8, 0x7719D0

    Obj_00771620* Owner;   // +0x1C
};
GG_STATIC_ASSERT(offsetof(Anim, Owner) == 0x1C && sizeof(Anim) == 0x20);

}  // namespace Voices
}  // namespace WorldDominationTour

#endif  // GG_MATCH_LAYOUT_MS_ANIM_H
