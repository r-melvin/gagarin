// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The flyer's per-frame step. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
#include "fly_locomotion_process_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x8B3C78 — the engine's unset coordinate.
// GLOBAL: GAMEMD 0x7E1718 — double 1.0, the full ramp.

// ILocomotion slot +0x40 — one frame of flight. A flyer that is neither
// landing nor taking off and is already at full ramp takes its cruising speed
// from its type once; a flyer with travel left and neither state set is asked
// whether it wants to do something about it. The touchdown spin and the two
// per-frame housekeeping members then run, and the shared move step decides
// whether the rest of the frame happens at all: the destination is re-aimed
// while it is set and travel remains, the approach runs while travel remains,
// and the answer is whether the flyer still casts a shadow.
// One lever, and the whole score hung on it. Retail issues three loads then
// three stores into the pushed argument block through a callee-saved base
// register (`MOV EBX,ESP`), which costs the prologue a fourth push and every
// epilogue a fourth pop; passing the destination member by value gives the
// whole-struct copy instead - two loads, the base in ECX, a third load
// between the stores - and no EBX, which shifts every byte after the prologue
// and scores 1.7% on an otherwise correct body. Building the argument through
// a three-integer constructor is what produces retail's form. Adding a
// user-declared constructor to the coordinate on its own changes nothing.
// FUNCTION: GAMEMD 0x4CCB40
char __stdcall FlyLocoProcess::Process()
{
    if (this->IsLanding == 0 && this->IsTakingOff == 0 && this->Ramp >= 1.0 &&
        this->Speed == 0) {
        FootType_004CCB40* type =
            (this->LinkedTo->*this->LinkedTo->Vtbl->At_84)();
        this->Speed = (type->*type->Vtbl->At_BC)();
    }

    Foot_004CCB40* client = this->LinkedTo;
    if (client->Remaining > 0 && this->IsLanding == 0 &&
        this->IsTakingOff == 0 && (client->*client->Vtbl->At_200)() != 0) {
        Foot_004CCB40* again = this->LinkedTo;
        (again->*again->Vtbl->At_1EC)();
    }

    FlyLocoObj_004CCB40* self = (FlyLocoObj_004CCB40*)((char*)this - 4);
    self->ProcessSpin();
    self->FUN_004CD600();

    if (GG_FLY_SELF_B(this, 0x60) == 0) {
        return 0;
    }

    Foot_004CCB40* alive = this->LinkedTo;
    if (alive->IsAlive == 0) {
        return 0;
    }

    if (alive->Remaining > 0) {
        if ((this->Destination.X != UnsetCoord_008B3C78.X ||
             this->Destination.Y != UnsetCoord_008B3C78.Y ||
             this->Destination.Z != UnsetCoord_008B3C78.Z) &&
            this->IsLanding == 0 && this->IsTakingOff == 0 &&
            (alive->*alive->Vtbl->At_1C8)() > 0) {
            self->FUN_004CEFB0(1, Coord_004CCB40(this->Destination.X,
                                                 this->Destination.Y,
                                                 this->Destination.Z));
        }
    }

    Foot_004CCB40* last = this->LinkedTo;
    if (last->Remaining > 0) {
        self->FUN_004CD2A0();
    }
    self->FUN_004CD510();

    return GG_FLY_SELF_B(this, 0x10);
}
