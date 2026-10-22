// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset below is read from the user's retail gamemd.exe v1.001 with
//   the local Ghidra CLI.
//
//   Slot identity was taken from the binary, not from a document. The
//   AircraftClass vtable at 0x7E22A4 is proven by RTTI:
//     ghidra memory read 0x7E22A0 4    -> COL 0x007FB4C0
//     ghidra memory read 0x007FB4C0 16 -> +0xC type descriptor 0x00817B90
//     ghidra memory read 0x00817B90 40 -> ".?AVAircraftClass@@"
//   and it carries 0x007099E0 at slot +0x474. AircraftClass overrides the two
//   later slots, so +0x480 = 0x00709A30 and +0x484 = 0x00709A40 are the base
//   assignments; the bodies
//   here are pinned by their addresses regardless of slot.
//
//   Member offsets confirmed numerically from the three bodies:
//     +0x168  IdleActionTimer   CDTimerClass  (`MOV EDX,[ECX+0x168]` StartTime,
//                               `MOV EAX,[ECX+0x170]` TimeLeft = +0x168+8)
//     +0x274  TemporalImUsing   (`MOV ECX,[ESI+0x274]`)
//   Both agree with the committed spine match/_layout/techno_class.h (lines
//   207 and 252).
//
//   0x007099E0 is not a reload predicate: the timer it reads is at +0x168,
//   which the TechnoClass constructor and the committed spine both give as
//   IdleActionTimer (the reload timer is a different member).
#ifndef GG_MATCH_CORE_TECHNO_CLASS_IDLE_ACTION_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_IDLE_ACTION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class AbstractClass;
class TechnoClass;
struct TechnoIdleVtbl;

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84.
// GLOBAL: GAMEMD 0xA8ED84
#include "../core/frame_counter.h"

// CDTimerClass — the engine's countdown timer (sizeof 0xC). StartTime == -1
// means "stopped", and the remaining time is then simply the stored duration.
#ifndef GG_MATCH_CDTIMERCLASS_IDLE_DEFINED
#define GG_MATCH_CDTIMERCLASS_IDLE_DEFINED
struct CDTimerClass
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    int GetTimeLeft() const
    {
        if (this->StartTime == -1) {
            return this->TimeLeft;
        }
        {
            int elapsed = CurrentFrame - this->StartTime;
            if (elapsed < this->TimeLeft) {
                return this->TimeLeft - elapsed;
            }
        }
        return 0;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass)             == 0x0C);
#endif

// TemporalClass — the Chrono-legionnaire erase state. Only its target link and
// its detach entry point are reached from this TU.
class TemporalClass
{
public:
    // FUNCTION: GAMEMD 0x71ABC0 (decl; reloc) — TemporalClass::LetGo
    void LetGo();

    char  _pad_000[0x28];    // +0x00
    void* Target;            // +0x28
};
GG_STATIC_ASSERT(offsetof(TemporalClass, Target) == 0x28);

class TechnoClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    bool IsTimeForIdleAction();                          // GAMEMD 0x7099E0
    void SetDestination(AbstractClass* dest, bool now);  // GAMEMD 0x709A30
    bool EnterIdleMode(bool initial, bool unused);       // GAMEMD 0x709A40

    // FUNCTION: GAMEMD 0x6385C0 (decl; reloc) — the planning-token step this
    // body runs once both idle gates agree.
    void TryNextPlanningTokenNode();

    TechnoIdleVtbl* Vfptr;                    // +0x000
    char            _pad_004[0x168 - 0x004];
    CDTimerClass    IdleActionTimer;          // +0x168 (0xC)
    char            _pad_174[0x274 - 0x174];
    TemporalClass*  TemporalImUsing;          // +0x274
};
GG_STATIC_ASSERT(offsetof(TechnoClass, Vfptr)           == 0x000);
GG_STATIC_ASSERT(offsetof(TechnoClass, IdleActionTimer) == 0x168);
GG_STATIC_ASSERT(offsetof(TechnoClass, TemporalImUsing) == 0x274);

// The class has to be complete before these typedefs, or VC6 falls back to the
// multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef bool (TechnoClass::*PredicateFn)();

struct TechnoIdleVtbl
{
    char        _pad_000[0x430];
    PredicateFn At_430;                       // +0x430
    char        _pad_434[0x4D0 - 0x434];
    PredicateFn At_4D0;                       // +0x4D0
};
GG_STATIC_ASSERT(offsetof(TechnoIdleVtbl, At_430) == 0x430);
GG_STATIC_ASSERT(offsetof(TechnoIdleVtbl, At_4D0) == 0x4D0);

#endif // GG_MATCH_CORE_TECHNO_CLASS_IDLE_ACTION_METHODS_H
