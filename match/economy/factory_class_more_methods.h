// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly of Suspend / GetBuildTimeFrames),
//   cross-checked against the consult-only YRpp FactoryClass.h / StageClass.h /
//   Timer.h / TechnoClass.h (no LICENSE; every offset reconfirmed numerically
//   below). Shares the FactoryClass binding pinned in factory_class_methods.h;
//   re-derived here so this translation unit is self-contained.
//
// FactoryClass — produces units/buildings for a HouseClass. Derives from
// AbstractClass (0x24 bytes; Production.Value lands at this+0x24). Only the
// members reached by Suspend / GetBuildTimeFrames are pinned; the unknown gaps
// are padded and the whole layout is asserted to YRpp's 0x74 total size.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_MORE_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_MORE_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84. Read by the
// inlined FrameTimer when Suspend stamps Production.Timer.StartTime.
#include "../core/frame_counter.h"

// ---------------------------------------------------------------------------
// TechnoClass — only TimeToBuild() is reached (a real retail member at
// 0x6F47A0, called __thiscall on the produced Object). Declared without a body
// so cl emits a (reloc-normalised) CALL.
// ---------------------------------------------------------------------------
struct TechnoClass
{
    int TimeToBuild() const;  // GAMEMD 0x6F47A0 __thiscall
};

// ---------------------------------------------------------------------------
// FrameTimer — empty clock policy whose value is Unsorted::CurrentFrame. As a
// member it occupies a 1-byte slot (4 after alignment) inside CDTimerClass.
// ---------------------------------------------------------------------------
struct FrameTimer
{
    operator int() const { return CurrentFrame; }
};

// ---------------------------------------------------------------------------
// CDTimerClass = TimerStruct<FrameTimer>  (sizeof = 0x0C)
//   +0x00 int        StartTime
//   +0x04 FrameTimer CurrentTime   (1 byte + 3 pad, never written by the ctor)
//   +0x08 int        TimeLeft
// The int ctor sets StartTime = CurrentTime(=CurrentFrame) and TimeLeft, leaving
// CurrentTime uninitialised. When the temporary is copied into Production.Timer
// that uninitialised slot is carried through verbatim — exactly the
// MOV [ECX+0x30],<garbage> store the retail disasm shows.
// ---------------------------------------------------------------------------
struct CDTimerClass
{
    int        StartTime;
    FrameTimer CurrentTime;
    int        TimeLeft;

    CDTimerClass(int duration)
    {
        this->StartTime = this->CurrentTime;
        this->TimeLeft = duration;
    }
};

GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(CDTimerClass) == 0xC);

// ---------------------------------------------------------------------------
// StageClass (YRpp StageClass.h)  (sizeof = 0x1C)
//   +0x00 int          Value
//   +0x04 bool         HasChanged
//   +0x08 CDTimerClass Timer
//   +0x14 int          Rate
//   +0x18 int          Step
// Suspend resets the production timer: Rate first, then a CDTimerClass(0)
// temporary copied into Timer.
// ---------------------------------------------------------------------------
struct StageClass
{
    int          Value;       // +0x00
    bool         HasChanged;  // +0x04
    CDTimerClass Timer;       // +0x08
    int          Rate;        // +0x14
    int          Step;        // +0x18

    void Start(int rate)
    {
        // Source orders the Timer copy before Rate so cl schedules the retail
        // pattern: hold &Timer in ESI, write Rate via this (ECX) between the
        // LEA and the timer stores. (cl re-emits the Rate store first.)
        this->Timer = CDTimerClass(rate);
        this->Rate = rate;
    }
};

GG_STATIC_ASSERT(offsetof(StageClass, Timer) == 0x08);
GG_STATIC_ASSERT(offsetof(StageClass, Rate) == 0x14);
GG_STATIC_ASSERT(sizeof(StageClass) == 0x1C);

// ---------------------------------------------------------------------------
// FactoryClass : AbstractClass (0x24)  (sizeof = 0x74)
// ---------------------------------------------------------------------------
struct FactoryClass
{
    char         _abstract_base[0x24];  // +0x00  AbstractClass (vtable + members)
    StageClass   Production;            // +0x24  progress timer
    char         _queued[0x18];         // +0x40  DynamicVectorClass QueuedObjects
    TechnoClass* Object;                // +0x58  item currently in production
    char         _pad5c[0x14];          // +0x5C  OnHold/IsDifferent/Balance/...
    bool         IsSuspended;           // +0x70
    bool         IsManual;              // +0x71
    char         _pad72[2];             // +0x72  padding_72[2]

    // Declared ascending by retail address (reccmp/isle TU discipline).
    bool Suspend(bool manual);             // GAMEMD 0x4C9E60 __thiscall
    int  GetBuildTimeFrames() const;       // GAMEMD 0x4C9FB0 __thiscall
};

GG_STATIC_ASSERT(offsetof(FactoryClass, Production) == 0x24);
GG_STATIC_ASSERT(offsetof(FactoryClass, Production.Timer) == 0x2C);
GG_STATIC_ASSERT(offsetof(FactoryClass, Production.Rate) == 0x38);
GG_STATIC_ASSERT(offsetof(FactoryClass, Object) == 0x58);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsSuspended) == 0x70);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsManual) == 0x71);
GG_STATIC_ASSERT(sizeof(FactoryClass) == 0x74);

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_MORE_METHODS_H
