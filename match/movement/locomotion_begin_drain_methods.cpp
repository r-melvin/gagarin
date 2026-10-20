// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "locomotion_begin_drain_methods.h"

// FUNCTION: GAMEMD 0x70FD70
//
// Begin draining the given target: link the two objects together, mark the
// target's owner, release whatever the target was holding, spawn the drain
// animation and attach it, then refresh this object's display.
//
// PARTIAL, 97.0% (64 of 67 instructions; the multiset differs by nothing but
// the register holding the display pointer). Retail loads it into ECX and
// tests ECX; cl uses EAX. Four tail spellings were measured on cloned classes
// and all four score identically: the guard as a three-term conjunction, the
// display named inside a nested block, three separate early returns, and a
// nested test inside the conjunction. The register choice is not reachable
// from the tail's shape.
//
// Three model errors were found and fixed on the way here, each of which
// first read as a codegen problem: the link store was written to the wrong
// object; vtable slot +0x48 returns a coordinate through a hidden buffer and
// takes five arguments, not six; and the display refresh pushes all three of
// its arguments rather than using the register convention. The length was
// also one byte too long, which pulled the next function's first byte into
// the comparison and showed up as a phantom retail-only instruction.
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
        void* display = this->Display;
        if (display != 0) {
            FUN_006EA870(this, -1, 1);
        }
    }
}
