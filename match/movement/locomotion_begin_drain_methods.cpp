// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "locomotion_begin_drain_methods.h"

// FUNCTION: GAMEMD 0x70FD70
//
// Begin draining the given target: link the two objects together, mark the
// target's owner, release whatever the target was holding, spawn the drain
// animation and attach it, then refresh this object's display.
//
// The display refresh is a thiscall: retail loads the display pointer from
// this+0x5D4 into ECX and passes owner, -1 and 1 on the stack. Modelling it
// as a free stdcall function omitted the display receiver.
void Drainer_0070FD70::BeginDraining(Target_0070FD70* target)
{
    if (target == 0) {
        return;
    }
    if (FUN_0047C520((this->*this->Vtbl->OccupiedCell)()) != target) {
        return;
    }

    target->DrainedBy = this;
    this->DrainingWhom = target;
    target->Owner->IsDraining = 1;

    if (target->Buffer != 0) {
        FUN_00472140(target->Buffer);
    }

    void* raw = gg_operator_new(0x1C8);
    Anim_0070FD70* anim;
    if (raw != 0) {
        anim = ((Anim_0070FD70*)raw)->Construct(
            RulesInstance->DrainAnim,
            (this->*this->Vtbl->BuildCoord)(0, 1, 0x600, 0, 0));
    } else {
        anim = 0;
    }

    this->DrainAnim = anim;
    if (anim != 0) {
        anim->Attach(this);
    }

    if (this != 0 && (this->Flags & 4) != 0) {
        Display_0070FD70* display = this->Display;
        if (display != 0) {
            display->Refresh(this, -1, 1);
        }
    }
}
