// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The flyer's take-off switch. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
#include "fly_locomotion_takeoff_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x8B3C58 — the engine's unset cell.
// GLOBAL: GAMEMD 0x887888 — the list a cell-less client is registered with.

// Put the flyer into its take-off state. Four gates on the client can refuse
// it outright; past them the landing flag clears, the take-off flag sets, a
// client that is standing on no cell is registered, the cruising speed is
// taken from the type, a client with no travel left is turned to face where
// it wants to face, and the type's take-off sound plays where it stands.
// Two levers. The cell test reads both components off one returned hidden
// pointer, so it has to be a whole-cell comparison; two component
// comparisons written out call the slot twice (22.1%). And the sound's
// coordinate is copied into a frame local whose address is then passed: with
// that copy as its own statement cl schedules it before the argument push and
// re-derives the address at the call (74.7%, one instruction short and every
// byte after it shifted), while writing it inside the argument list puts it
// where right-to-left evaluation does - after the last argument's push, before
// the first argument's own call - and retail then holds the address in the
// dead receiver's register across that call. Naming the address as a local,
// copying through it, and copy-constructing a temporary into a reference
// parameter were all measured at 74.7%.
// FUNCTION: GAMEMD 0x4CF950
void FlyLocoTakeOff::BeginTakeOff()
{
    Foot_004CF950* a = this->LinkedTo;
    if ((a->*a->Vtbl->At_37C)() != 0) {
        return;
    }
    Foot_004CF950* b = this->LinkedTo;
    if ((b->*b->Vtbl->At_380)() != 0) {
        return;
    }
    Foot_004CF950* c = this->LinkedTo;
    if ((c->*c->Vtbl->At_1D4)() != 0) {
        return;
    }
    Foot_004CF950* d = this->LinkedTo;
    if ((d->*d->Vtbl->At_1D8)() != 0) {
        return;
    }

    Foot_004CF950* client = this->LinkedTo;
    this->IsLanding = 0;
    this->IsTakingOff = 1;
    if ((client->*client->Vtbl->At_2F4)() == UnsetCell_008B3C58) {
        Registry_00887888_Instance.Add(this->LinkedTo);
    }

    Foot_004CF950* e = this->LinkedTo;
    FootType_004CF950* type = (e->*e->Vtbl->At_84)();
    this->Speed = (type->*type->Vtbl->At_BC)();

    Foot_004CF950* f = this->LinkedTo;
    if ((f->*f->Vtbl->At_1C8)() == 0) {
        Dir_004CF950 wanted;
        this->LinkedTo->PrimaryFacing.Assign(
            this->LinkedTo->SecondaryFacing.Desired(&wanted));
    }

    Foot_004CF950* g = this->LinkedTo;
    Coord_004CF950 where;
    VocClass_PlayAt_004CF950((g->*g->Vtbl->At_84)()->TakeOffSound,
                             (where = g->Location, &where), 0);
}
