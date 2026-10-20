// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x71ABC0.

#include "temporal_class_let_go_methods.h"

// FUNCTION: GAMEMD 0x71ABC0  TemporalClass::LetGo
//
// Release the warp target. A temporal at the head of a chain hands the
// target (and its accumulated warp) to the next in line; the last one lets
// the target go for real: its back-link and warping flag clear, a building
// makes its house recount power and its tech tree, and the target is
// re-marked. A temporal in the middle or at the tail just unlinks itself.
// Every path ends by clearing the five link/target fields; each branch
// carries its own copy of that tail, as retail does.
//
// PARTIAL (85.5%, 71/83; mnemonic multiset identical). Retail keeps the
// previous link in EAX and the next one in ECX; VC6 assigns them the other
// way round, and every use of the two follows. Declaration order, testing
// the members instead of the locals, and dropping either local in favour of
// member re-reads (64.3% for prev-only) do not flip it — the same
// two-local naming tie-break as 0x4E15A0.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, ESI on
// both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void Temporal_0071ABC0::LetGo()
{
    Temporal_0071ABC0* next = NextTemporal;
    Temporal_0071ABC0* prev = PrevTemporal;

    if (prev == 0) {
        Techno_0071ABC0* target = Target;
        if (next != 0) {
            if (target != 0)
                target->TemporalTargetingMe = next;
            NextTemporal->PrevTemporal = 0;
            NextTemporal->At_48 = At_48;
            Target = 0;
            NextTemporal = 0;
            PrevTemporal = 0;
            At_3C = 0;
            At_38 = 0;
            return;
        }
        if (target != 0) {
            target->TemporalTargetingMe = 0;
            Target->BeingWarpedOut = 0;
            if ((Target->*Target->Vptr->WhatAmI)() == 6) {
                Techno_0071ABC0* building = Target;
                building->Owner->PowerBlackoutWasActivated = 1;
                building->FUN_00452210();
                building->Owner->RecheckTechTree = 1;
            }
            (Target->*Target->Vptr->Mark)(2);
            Target = 0;
            NextTemporal = 0;
            PrevTemporal = 0;
            At_3C = 0;
            At_38 = 0;
            return;
        }
    } else if (next != 0) {
        next->PrevTemporal = prev;
        if (PrevTemporal != 0) {
            PrevTemporal->NextTemporal = NextTemporal;
            Target = 0;
            NextTemporal = 0;
            PrevTemporal = 0;
            At_3C = 0;
            At_38 = 0;
            return;
        }
    } else {
        prev->NextTemporal = 0;
    }

    Target = 0;
    NextTemporal = 0;
    PrevTemporal = 0;
    At_3C = 0;
    At_38 = 0;
}
