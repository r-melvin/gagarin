// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x7263A0-0x7263F9), cross-checked
//   against YRpp TriggerClass.h (consult-only; reconfirmed numerically here).
//
// The shared TriggerClass declaration owns NotifyGlobalChanged/NotifyLocalChanged; these
// walk the trigger's NextTrigger list and, for any trigger whose TriggerType
// references the changed global/local, reset that trigger's event timers.
#ifndef GG_MATCH_AI_TRIGGER_CLASS_METHODS_H
#define GG_MATCH_AI_TRIGGER_CLASS_METHODS_H

#include <stddef.h>
#include "../_layout/trigger_class.h"
#include "../_rt/gg_static_assert.h"

// TriggerTypeClass — the trigger's static type. Both Notify* methods query it
// (ecx = [TriggerClass+0x24]) with the changed index and return a bool in AL.
// The query bodies (@0x727010 / @0x727050) are matched elsewhere; declared here
// so cl emits the calls (relocations, normalised by the differ).
class TriggerTypeClass
{
public:
    // GAMEMD 0x727010 __thiscall — has a Global Set/Cleared event for idxGlobal.
    bool HasGlobalChangedEvent(int idxGlobal);
    // GAMEMD 0x727050 __thiscall — has a Local Set/Cleared event for idxLocal.
    bool HasLocalChangedEvent(int idxLocal);
};



GG_STATIC_ASSERT(offsetof(TriggerClass, Type)        == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, NextTrigger) == 0x28);

#endif  // GG_MATCH_AI_TRIGGER_CLASS_METHODS_H
