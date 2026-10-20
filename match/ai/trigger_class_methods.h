// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x7263A0-0x7263F9), cross-checked
//   against YRpp TriggerClass.h (consult-only; reconfirmed numerically here).
//
// TriggerClass — a map trigger instance. NotifyGlobalChanged/NotifyLocalChanged
// walk the trigger's NextTrigger list and, for any trigger whose TriggerType
// references the changed global/local, reset that trigger's event timers.
#ifndef GG_MATCH_AI_TRIGGER_CLASS_METHODS_H
#define GG_MATCH_AI_TRIGGER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// TriggerTypeClass — the trigger's static type. Both Notify* methods query it
// (ecx = [TriggerClass+0x24]) with the changed index and return a bool in AL.
// The query bodies (@0x727010 / @0x727050) are matched elsewhere; declared here
// so cl emits the calls (relocations, normalised by the differ).
struct TriggerTypeClass
{
    // GAMEMD 0x727010 __thiscall — has a Global Set/Cleared event for idxGlobal.
    bool HasGlobalChangedEvent(int idxGlobal);
    // GAMEMD 0x727050 __thiscall — has a Local Set/Cleared event for idxLocal.
    bool HasLocalChangedEvent(int idxLocal);
};

struct TriggerClass
{
    void NotifyGlobalChanged(int idxGlobal); // GAMEMD 0x7263A0 __thiscall
    void NotifyLocalChanged(int idxLocal);   // GAMEMD 0x7263D0 __thiscall

    // ResetTimers (@0x726400, __thiscall) — matched elsewhere; declared so the
    // body emits a call (reloc). Re-arms every Elapsed-Time/Random-Delay event.
    void ResetTimers();

    // AbstractClass base occupies [0x00..0x23]; full decomposition is P2.
    char               _abstract_base[0x24]; // +0x00
    TriggerTypeClass*  Type;                 // +0x24
    TriggerClass*      NextTrigger;          // +0x28
};

GG_STATIC_ASSERT(offsetof(TriggerClass, Type)        == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, NextTrigger) == 0x28);

#endif  // GG_MATCH_AI_TRIGGER_CLASS_METHODS_H
