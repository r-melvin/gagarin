// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at 0x4585C0.

#include "building_class_kill_occupants_methods.h"

// FUNCTION: GAMEMD 0x4585C0  BuildingClass::KillOccupants (__thiscall, ret 4)
//
// Empty a garrisonable building of its occupants. With no killer the
// occupants simply run their own slot +0xF8 destruction; with a killer, each
// occupant's firing port is projected to client space, an AnimClass is spawned
// at that point offset by the building's own coordinate, the killer is
// credited with the kill and the occupant is destroyed. Afterwards the
// occupant vector is cleared and re-sized to its old capacity and the
// building's recomputed slot +0x1BC value is applied.
//
// Two levers carried most of this: the killer == 0 arm has to be the source's
// `if` body (retail lays it inline and the killer arm as the far block — the
// reverse spelling inverts the whole layout), and the coordinate sum has to be
// staged in its own struct and assigned whole (`sum.X = origin->X + where.X;
// … where = sum;`), which keeps the three component loads together ahead of
// the three stores instead of sinking each add to its store (72.6% -> 85.5%).
// Binding the animation type to a local inside the allocation arm is what puts
// the `MOV EAX,[EAX]` deref ahead of the `MOV ECX,<anim>`.
//
// PARTIAL (85.5%, 100/117): the instruction multiset is identical. The residual
// is (a) retail storing the +0x69C counter before loading the occupant count
// where cl emits the load first, (b) the client point's two components: retail
// loads Y then X before storing either, cl loads and stores X then Y, and
// (c) three EAX/ECX naming swaps around the slot +0xAC and Construct calls.
// Variants tried: the client point staged in its own struct and assigned whole
// (14.3% — it forces a real second frame slot), the Y component bound to a
// local before the X store (14.4%), and the original arm order (72.6%).
void Building_004585C0::KillOccupants(Killer_004585C0* killer)
{
    this->Unknown_69C = 0;

    int i;
    if (killer == 0)
    {
        for (i = this->Occupants.Count - 1; i >= 0; i--)
        {
            Occupant_004585C0* dying = this->Occupants.Items[i];
            (dying->*dying->Vptr->At_F8)();
        }
    }
    else
    {
        for (i = this->Occupants.Count - 1; i >= 0; i--)
        {
            Point_004585C0  pt;
            Coord_004585C0  where;
            Point_004585C0* client = DAT_00887324->CoordsToClient(
                &pt, this->Type->OccupantOffsets[i]);
            where.X = client->X;
            where.Y = client->Y;
            where.Z = 0;

            Coord_004585C0  self;
            Coord_004585C0* origin = (this->*this->Vptr->At_AC)(&self);
            Coord_004585C0 sum;
            sum.X = origin->X + where.X;
            sum.Y = origin->Y + where.Y;
            sum.Z = origin->Z + where.Z;
            where = sum;

            Anim_004585C0* anim =
                (Anim_004585C0*)KillOccOperatorNew(0x1C8);
            if (anim) {
                AnimType_004585C0* type =
                    (*(killer->*killer->Vptr->At_3F8)(
                         0, &where, 0, 1, 0x600, 0, 0))->AnimType;
                anim = anim->Construct(type);
            } else {
                anim = 0;
            }
            anim->Unknown_100 = 0xFFFFFF38;

            Occupant_004585C0* victim = this->Occupants.Items[i];
            (killer->*killer->Vptr->At_E0)(victim);

            Occupant_004585C0* dying = this->Occupants.Items[i];
            (dying->*dying->Vptr->At_F8)();
        }
    }

    int capacity = this->Occupants.Capacity;
    (this->Occupants.*this->Occupants.Vptr->Clear)();
    (this->Occupants.*this->Occupants.Vptr->Resize)(capacity, 0);

    this->FUN_0070F6E0((this->*this->Vptr->At_1BC)());
}
