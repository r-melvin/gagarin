// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4CA1A0: `[ECX+0x58]` (Object), `[ECX+0x24]` compared
//   against 0x36 (Production.Value), `[ECX+0x70]` / `[ECX+0x5D]` byte stores
//   (IsSuspended / IsDifferent), `[ECX+0x68]` (SpecialItem, written -1),
//   `[ECX+0x38]` (Production.Rate), the `LEA EDI,[ECX+0x2C]` timer base with
//   `[EDI]`/`[EDI+4]`/`[EDI+8]` stores (Production.Timer), and the global
//   `[0x00A8ED84]` (Unsorted::CurrentFrame). Names cross-checked against the
//   YRpp (no text copied); the
//   binding agrees with match/economy/factory_class_methods.h and
//   factory_class_more_methods.h, re-derived here so the TU is standalone.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_COMPLETED_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_COMPLETED_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame, the engine frame counter.
#include "../core/frame_counter.h"

class TechnoClass;

// FrameTimer — empty clock policy whose value is CurrentFrame; occupies a
// 1-byte (4 after alignment) slot inside CDTimerClass.

// CDTimerClass = TimerStruct<FrameTimer>  (sizeof = 0x0C)
//   +0x00 int        StartTime
//   +0x04 FrameTimer CurrentTime   (never written by the ctor)
//   +0x08 int        TimeLeft
// The int ctor leaves CurrentTime uninitialised; copying the temporary into
// Production.Timer carries that slot through verbatim, which is the
// `MOV ESI,[ESP+0xC]; MOV [EDI+4],ESI` pair in the retail bytes.
#include "../_layout/frame_timer.h"
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(CDTimerClass) == 0xC);

// StageClass  (sizeof = 0x1C)
class StageClass
{
public:
    int          Value;       // +0x00
    bool         HasChanged;  // +0x04
    CDTimerClass Timer;       // +0x08
    int          Rate;        // +0x14
    int          Step;        // +0x18

    void Start(int rate)
    {
        this->Timer = CDTimerClass(rate);
        this->Rate = rate;
    }
};
GG_STATIC_ASSERT(offsetof(StageClass, Timer) == 0x08);
GG_STATIC_ASSERT(offsetof(StageClass, Rate) == 0x14);
GG_STATIC_ASSERT(sizeof(StageClass) == 0x1C);

// FactoryClass : AbstractClass (0x24)  (sizeof = 0x74)
class FactoryClass
{
public:
    char         _abstract_base[0x24];  // +0x00  AbstractClass (vtable + members)
    StageClass   Production;            // +0x24  progress; Value == 0x36 when done
    char         _queued[0x18];         // +0x40  DynamicVectorClass QueuedObjects
    TechnoClass* Object;                // +0x58  item currently in production
    bool         OnHold;                // +0x5C
    bool         IsDifferent;           // +0x5D
    char         _pad5E[2];             // +0x5E
    int          Balance;               // +0x60
    int          OriginalBalance;       // +0x64
    int          SpecialItem;           // +0x68  special-weapon item; -1 = none
    void*        Owner;                 // +0x6C  HouseClass*
    bool         IsSuspended;           // +0x70
    bool         IsManual;              // +0x71
    char         _pad72[2];             // +0x72

    // FUNCTION: GAMEMD 0x4CA1A0
    bool CompletedProduction();
};
GG_STATIC_ASSERT(offsetof(FactoryClass, Production) == 0x24);
GG_STATIC_ASSERT(offsetof(FactoryClass, Production.Timer) == 0x2C);
GG_STATIC_ASSERT(offsetof(FactoryClass, Production.Rate) == 0x38);
GG_STATIC_ASSERT(offsetof(FactoryClass, Object) == 0x58);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsDifferent) == 0x5D);
GG_STATIC_ASSERT(offsetof(FactoryClass, SpecialItem) == 0x68);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsSuspended) == 0x70);
GG_STATIC_ASSERT(sizeof(FactoryClass) == 0x74);

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_COMPLETED_METHODS_H
