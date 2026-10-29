// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//   TunnelLocomotionClass state-completion handlers, read off retail gamemd.exe v1.001.
//   Each runs when the state timer has covered its full duration (progress equals 1.0).
//   Address index: 0x729480, 0x729AA0, 0x7294E0.

#include <new.h>
#include "tunnel_locomotion_w3_methods.h"
#include "tunnel_foot_view_r12.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

// The linked unit's end-of-movement notification.
struct TunnelFootEnd_r12
{
    // FUNCTION: GAMEMD 0x4DF0D0 (decl; reloc)
    void FUN_004DF0D0();
};

// FUNCTION: GAMEMD 0x729480
// When the timer has run its course, return to idle and tell the linked unit.
void TunnelLocomotionClass::FinishIfTimed()
{
    int duration = unknown_34;
    if (duration) {
        int left = Timer_28.GetTimeLeft();
        if ((double)(duration - left) / duration != DAT_007E1718) {
            return;
        }
    }
    State = 0;
    reinterpret_cast<TunnelFootEnd_r12*>(LinkedTo)->FUN_004DF0D0();
}

// FUNCTION: GAMEMD 0x729AA0
// When the timer has run its course, ask the linked unit for its next step; if it is alive, on the
// map and not otherwise engaged, stop moving and go idle.
void TunnelLocomotionClass::FUN_00729AA0()
{
    int duration = unknown_34;
    if (duration) {
        int left = Timer_28.GetTimeLeft();
        if ((double)(duration - left) / duration != DAT_007E1718) {
            return;
        }
    }
    TunnelFootView_r12* foot = reinterpret_cast<TunnelFootView_r12*>(LinkedTo);
    foot->vf_18C(2);
    foot = reinterpret_cast<TunnelFootView_r12*>(LinkedTo);
    if (foot->unknown_90 && !foot->unknown_81 && !foot->unknown_8D) {
        StopMoving();
        State = 0;
        reinterpret_cast<TunnelFootEnd_r12*>(LinkedTo)->FUN_004DF0D0();
    }
}

// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// FUNCTION: GAMEMD 0x7294E0
// Sinks the linked unit step by step until it is 0x100 below the ground, then stops it and moves on
// to state 4.
void TunnelLocomotionClass::FUN_007294E0()
{
    TunnelFootView_r12* foot = reinterpret_cast<TunnelFootView_r12*>(LinkedTo);
    TunnelCoord_r12 where = foot->Location;
    if (where.Z > -0x100) {
        int speed = foot->vf_538();
        int step = (int)(speed * DAT_008871E0->TunnelSpeed);
        if (step <= 5) {
            step = 5;
        }
        where.Z -= step;
        if (where.Z < -0x100) {
            where.Z = -0x100;
        }
        reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_1B4(&where);
    } else {
        foot->vf_124(0);
        State = 4;
    }
}
