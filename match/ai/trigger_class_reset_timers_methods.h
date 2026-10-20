// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x726400: TriggerClass::Type at [ESI+0x24], the
//   type's FirstEvent at [EAX+0xAC]; per event NextEvent [EDI+0x28],
//   EventKind [EDI+0x2C] (compared with 0xD and 0x33) and Value [EDI+0x34];
//   the trigger's Timer at ESI+0x34 (written as frame / an uninitialised
//   stack dword / value*15 at 0x726431..0x72643F) and the event bitmask at
//   [ESI+0x40] (`AND` with `~(1 << CL)`). 0xA8ED84 is the frame counter,
//   0xA8B230 ScenarioClass::Instance whose Randomizer sits at +0x218
//   (`LEA ECX,[EAX+0x218]` before CALL 0x65C7E0 with 0 and the value
//   pushed). Names cross-checked against YRpp TriggerClass.h /
//   TriggerTypeClass.h / TEventClass.h / ScenarioClass.h (consult-only; NO
//   LICENSE; every offset reconfirmed above). Type @0x24 agrees with
//   match/ai/trigger_class_methods.h (not edited).
#ifndef GG_MATCH_AI_TRIGGER_CLASS_RESET_TIMERS_METHODS_H
#define GG_MATCH_AI_TRIGGER_CLASS_RESET_TIMERS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

// A frame-clocked countdown (YRpp CDTimerClass). The clock slot at +0x04 is
// never written by the constructor, which is exactly what retail shows: the
// temporary's middle dword is copied out of an uninitialised stack slot.
struct CDTimer_00726400
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    explicit CDTimer_00726400(int duration)
    {
        StartTime = CurrentFrame;
        TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_00726400, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimer_00726400) == 0x0C);

// The scenario randomizer; only the ranged draw is called.
struct Random_00726400
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) — Randomizer::RandomRanged.
    int RandomRanged(int min, int max);
};

// ScenarioClass — only Random @0x218 is touched.
struct Scenario_00726400
{
    char             _pad000[0x218];    // +0x0000
    Random_00726400  Random;            // +0x0218
};
GG_STATIC_ASSERT(offsetof(Scenario_00726400, Random) == 0x218);

// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_00726400* DAT_00A8B230;

// TEventClass — one node of the trigger type's event list.
struct TEvent_00726400
{
    char              _pad000[0x28];    // +0x0000
    TEvent_00726400*  NextEvent;        // +0x0028
    int               EventKind;        // +0x002C  (13 = elapsed time, 51 = random delay)
    char              _pad030[4];       // +0x0030
    int               Value;            // +0x0034
};
GG_STATIC_ASSERT(offsetof(TEvent_00726400, NextEvent) == 0x28);
GG_STATIC_ASSERT(offsetof(TEvent_00726400, EventKind) == 0x2C);
GG_STATIC_ASSERT(offsetof(TEvent_00726400, Value) == 0x34);

// TriggerTypeClass — only FirstEvent @0xAC is read.
struct TriggerType_00726400
{
    char              _pad000[0xAC];    // +0x0000
    TEvent_00726400*  FirstEvent;       // +0x00AC
};
GG_STATIC_ASSERT(offsetof(TriggerType_00726400, FirstEvent) == 0xAC);

struct TriggerClass
{
    char                   _pad000[0x24];    // +0x0000
    TriggerType_00726400*  Type;             // +0x0024
    char                   _pad028[0x34 - 0x28];
    CDTimer_00726400       Timer;            // +0x0034
    unsigned int           OccuredEvents;    // +0x0040  one bit per event

    // FUNCTION: GAMEMD 0x726400
    void ResetTimers();
};
GG_STATIC_ASSERT(offsetof(TriggerClass, Type) == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, Timer) == 0x34);
GG_STATIC_ASSERT(offsetof(TriggerClass, OccuredEvents) == 0x40);

#endif  // GG_MATCH_AI_TRIGGER_CLASS_RESET_TIMERS_METHODS_H
