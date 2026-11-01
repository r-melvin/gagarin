// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Reconstructed from retail entry-point instructions, supplemented by REA
//   ev_81531b090284a3fa964156f10f60a83c0de7ce17835e1d6af8a95506fb7bf057.
//   The method's original name is not established; retain its address name.
//   0x4157C0, 0x415A50, 0x4195A0 and 0x41A940 (same vtable 0x7E22A4; mission and landing helpers) were read
//   from retail entry instructions, REA ev_00b091f659be091747205c8d1ded968e0fb868469484884f4e9122c932716973.

#include "aircraft_mission_004155f0.h"

// GLOBAL: GAMEMD 0x817A78 -- the eight facings tried in order.
extern const unsigned int DAT_00817A78[8];

// FUNCTION: GAMEMD 0x4155F0
// PARTIAL: 98.6% (142/144 instructions). All instructions and registers match;
// only JG at +0x116 and JZ at +0x177 select the two cold epilogues in the
// opposite order. Retail chooses +0x1A7/+0x1BA, VC6 +0x1BA/+0x1A7.
// Source control-flow/comparison variants, /Og- and /G6 bisection, and a
// five-minute targeted permuter run produced no full match (branch scoring on).
// No assembly workaround is used.
int Aircraft_004155F0::FUN_004155F0()
{
    int distance = FUN_005F6440(Target);
    if (!Target) {
        (this->*Vptr->SetDestination)(0, 1);
        (this->*Vptr->QueueMission)(4, 0);
    } else if (!Destination) {
        (this->*Vptr->SetDestination)(Target, 1);
    } else if (distance <= (this->*Vptr->GetWeapon)(0)->Type->Range) {
        (this->*Vptr->At_48C)(0, 0, 0, 0);
        (this->*Vptr->At_488)(0, 0, 0, 0, (this->*Vptr->GetWeapon)(0)->Type->Damage);
        Coord_004155F0 coords = Location;
        DAT_0087F7E8.FUN_00567DA0(&coords, 0, LastSightRange + 3, 0);
        coords = Location;
        FUN_007509E0(RulesInstance_004155F0->Sound, &coords, 0);
    }

    if (distance <= 0x300) {
        (this->*Vptr->QueueMission)(0x1F, 0);
        IsLocked = 1;
        int side = Owner->FUN_0050DAC0();
        Cell_004155F0 out;
        Cell_004155F0 cell = *DAT_0087F7E8.FUN_004AA440(&out,
            side, &DAT_00889E68, &DAT_00889E68, 4, 1, 0);
        if (cell != DAT_00889E68) {
            (this->*Vptr->SetDestination)(DAT_0087F7E8.FUN_005657A0(cell), 1);
            return RulesInstance_004155F0->At_290;
        } else {
            return RulesInstance_004155F0->At_290;
        }
    } else {
        return RulesInstance_004155F0->At_290;
    }
}

// FUNCTION: GAMEMD 0x4157C0
int Aircraft_004155F0::FUN_004157C0()
{
    int distance = FUN_005F6440(Target);
    if (distance <= (this->*Vptr->GetWeapon)(0)->Type->Range) {
        (this->*Vptr->At_48C)(0, 0, 0, 0);
        (this->*Vptr->At_488)(0, 0, 0, 0, (this->*Vptr->GetWeapon)(0)->Type->Damage);
        Coord_004155F0 coords = Location;
        DAT_0087F7E8.FUN_00567DA0(&coords, 0, LastSightRange + 3, 0);
    }
    if (!Destination) {
        int side = Owner->FUN_0050DAC0();
        Cell_004155F0 out;
        Cell_004155F0 cell = *DAT_0087F7E8.FUN_004AA440(&out,
            side, &DAT_00889E68, &DAT_00889E68, 4, 1, 0);
        if (cell != DAT_00889E68)
            (this->*Vptr->SetDestination)(DAT_0087F7E8.FUN_005657A0(cell), 1);
    }
    return 3;
}

// FUNCTION: GAMEMD 0x4195A0
// The first facing of the table at 0x817A78 whose neighbouring cell (of this one's cell) is on the map, is not
// the cell `other` stands over, and is clear to move into; its coordinate is left in `out` (the empty cell when
// none).
int Aircraft_004155F0::FUN_004195A0(Aircraft_004155F0* other, Cell_004155F0* out)
{
    Coord_004155F0 scratch;
    *out = DAT_00889E68;
    Coord_004155F0* c = (this->*Vptr->GetCoords)(&scratch);
    Cell_004155F0 base;
    base.X = c->X / 256;
    base.Y = c->Y / 256;
    int i;
    for (i = 0; i < 8; ++i) {
        Cell_004155F0 next;
        const CellStruct& step = DAT_0089F688[DAT_00817A78[i] & 7];
        next.X = base.X + step.X;
        next.Y = base.Y + step.Y;
        *out = next;
        if (DAT_0087F7E8.FUN_00568300(out)) {
            Coord_004155F0* here = (other->*other->Vptr->GetCoords)(&scratch);
            Cell_004155F0 hereCell;
            hereCell.X = here->X / 256;
            hereCell.Y = here->Y / 256;
            if (!(hereCell != *out))
                break;
            if (static_cast<CellClass*>(DAT_0087F7E8.FUN_005657A0(*out))->IsClearToMove(0, false, false, -1, 0, -1, true))
                break;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x415A50
int Aircraft_004155F0::FUN_00415A50()
{
    if (Destination == 0) {
        int side = Owner->At_1E0;
        if (side < 0 || side > 3)
            side = Owner->FUN_0050DA80();
        Cell_004155F0 out;
        Cell_004155F0 cell = *DAT_0087F7E8.FUN_004AA440(&out,
            side, &DAT_00889E68, &DAT_00889E68, 4, 1, 0);
        if (cell != DAT_00889E68) {
            (this->*Vptr->SetDestination)(DAT_0087F7E8.FUN_005657A0(cell), 1);
            return 3;
        }
    } else {
        if (Destination == (this->*Vptr->At_1BC)())
            (this->*Vptr->SetDestination)(0, 1);
    }
    return 3;
}

// FUNCTION: GAMEMD 0x41A940
int Aircraft_004155F0::FUN_0041A940()
{
    int mine = (Type->*Type->Vptr->At_BC)();
    if ((this->*Vptr->At_1C8)() == mine) {
        if (At_5D4 == 0)
            (this->*Vptr->At_484)(0, 1);
        return 1;
    }
    if (At_2FC == 0) {
        if ((this->*Vptr->At_2AC)() != 0) {
            if (!FUN_0065AE30())
                (this->*Vptr->At_484)(0, 1);
        }
    }
    if (Target != 0) {
        (this->*Vptr->QueueMission)(1, 0);
        return 1;
    }
    return FUN_004D6AA0();
}
