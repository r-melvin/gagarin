// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Reconstructed from retail entry-point instructions, supplemented by REA
//   ev_81531b090284a3fa964156f10f60a83c0de7ce17835e1d6af8a95506fb7bf057.
//   The method's original name is not established; retain its address name.

#include "aircraft_mission_004155f0.h"

// FUNCTION: GAMEMD 0x4155F0
// PARTIAL: 98.6% (142/144 instructions). All instructions and registers match;
// only JG at +0x116 and JZ at +0x177 select the two cold epilogues in the
// opposite order. Retail chooses +0x1A7/+0x1BA, VC6 +0x1BA/+0x1A7.
// Source control-flow/comparison variants, /Og- and /G6 bisection, and a
// five-minute targeted permuter run produced no full match (branch scoring on).
// No assembly workaround is used.
int Aircraft_004155F0::FUN_004155F0()
{
    int distance = DistanceFrom(Target);
    if (!Target) {
        (this->*Vptr->SetDestination)(0, 1);
        (this->*Vptr->QueueMission)(4, 0);
    } else if (!Destination) {
        (this->*Vptr->SetDestination)(Target, 1);
    } else if (distance <= (this->*Vptr->GetWeapon)(0)->Type->Range) {
        (this->*Vptr->At_48C)(0, 0, 0, 0);
        (this->*Vptr->At_488)(0, 0, 0, 0, (this->*Vptr->GetWeapon)(0)->Type->Damage);
        Coord_004155F0 coords = Location;
        MapInstance_004155F0.FUN_00567DA0(&coords, 0, LastSightRange + 3, 0);
        coords = Location;
        FUN_007509E0(RulesInstance_004155F0->Sound, &coords, 0);
    }

    if (distance <= 0x300) {
        (this->*Vptr->QueueMission)(0x1F, 0);
        IsLocked = 1;
        int side = Owner->FUN_0050DAC0();
        Cell_004155F0 out;
        Cell_004155F0 cell = *MapInstance_004155F0.PickCell(&out,
            side, &EmptyCell_004155F0, &EmptyCell_004155F0, 4, 1, 0);
        if (cell != EmptyCell_004155F0) {
            (this->*Vptr->SetDestination)(MapInstance_004155F0.GetCellAt(&cell), 1);
            return RulesInstance_004155F0->At_290;
        } else {
            return RulesInstance_004155F0->At_290;
        }
    } else {
        return RulesInstance_004155F0->At_290;
    }
}
