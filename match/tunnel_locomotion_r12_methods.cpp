// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TunnelLocomotionClass state-completion handlers, read off retail gamemd.exe v1.001.
//   Each runs when the state timer has covered its full duration (progress equals 1.0).
//   Address index: 0x729370, 0x729480, 0x729AA0, 0x7294E0.

#include <new.h>
#include "tunnel_locomotion_w3_methods.h"
#include "tunnel_foot_view_r12.h"
#include "_layout/anim_class.h"
#include "_layout/coord_struct.h"
#include "_layout/voc_class.h"
#include "_layout/rules_class.h"
#include "ui_display_chain.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

// GLOBAL: GAMEMD 0x8871E0
extern RulesClass* DAT_008871E0;

// GLOBAL: GAMEMD 0x7F5B18
extern const double DAT_007F5B18;

// The linked unit's end-of-movement notification.
struct TunnelFootEnd_r12
{
    // FUNCTION: GAMEMD 0x4DF0D0 (decl; reloc)
    void FUN_004DF0D0();
};

// FUNCTION: GAMEMD 0x729370
// When the timer has run its course, finish the surfacing: the linked unit is told to settle, the
// state moves on to 3, the dig sound and animation are played where the unit stands, and the unit
// is released.
void TunnelLocomotionClass::FUN_00729370()
{
    int duration = unknown_34;
    if (duration) {
        int left = Timer_28.GetTimeLeft();
        if ((double)(duration - left) / duration != DAT_007E1718) {
            return;
        }
    }
    reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_544(1.0);
    State = 3;
    TunnelFootView_r12* foot = reinterpret_cast<TunnelFootView_r12*>(LinkedTo);
    {
        CoordStruct where = foot->Location;
        VocClass::PlayAt(DAT_008871E0->DigSound, &where, 0);
    }
    void* storage = ::operator new(sizeof(AnimClass));
    if (storage != 0) {
        foot = reinterpret_cast<TunnelFootView_r12*>(LinkedTo);
        CoordStruct at = foot->Location;
        new (storage) AnimClass(DAT_008871E0->Dig, at, 0, 1, 0x600, 0, false);
    }
    reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_0DC(0);
}

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

// FUNCTION: GAMEMD 0x7298F0
// Raises the linked unit step by step up to the ground; once there, the unit is released and the
// timer is set from the unit's type.
void TunnelLocomotionClass::FUN_007298F0()
{
    TunnelFootView_r12* foot = reinterpret_cast<TunnelFootView_r12*>(LinkedTo);
    CoordStruct where = foot->Location;
    int ground = Map_0087F7E8.GetZPos(&where);
    if (where.Z < ground) {
        int before = reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_1C8();
        int speed = reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_538();
        int step = (int)(speed * DAT_008871E0->TunnelSpeed);
        if (step <= 5) {
            step = 5;
        }
        where.Z += step;
        if (where.Z > ground) {
            where.Z = ground;
        }
        reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_1B4(&where);
        if (before <= -0x32 && reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_1C8() > -0x32) {
            {
                CoordStruct at = reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->Location;
                VocClass::PlayAt(DAT_008871E0->DigSound, &at, 0);
            }
            void* storage = ::operator new(sizeof(AnimClass));
            if (storage != 0) {
                CoordStruct at = reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->Location;
                new (storage) AnimClass(DAT_008871E0->Dig, at, 0, 1, 0x600, 0, false);
            }
        }
    } else {
        reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_120(0, 0);
        int duration = (int)(DAT_007F5B18 / reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_084()->unknown_71C);
        Timer_28.StartTime = CurrentFrame;
        Timer_28.TimeLeft = duration;
        unknown_34 = duration;
        reinterpret_cast<TunnelFootView_r12*>(LinkedTo)->vf_544(0.0);
        State = 6;
    }
}

// FUNCTION: GAMEMD 0x7294E0
// Sinks the linked unit step by step until it is 0x100 below the ground, then stops it and moves on
// to state 4.
void TunnelLocomotionClass::FUN_007294E0()
{
    TunnelFootView_r12* foot = reinterpret_cast<TunnelFootView_r12*>(LinkedTo);
    CoordStruct where = foot->Location;
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
