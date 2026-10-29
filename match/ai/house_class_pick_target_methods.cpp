// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x50D170.
//   FUNCTION: GAMEMD 0x645BB0   target type -> ThreatType mask (callee; reloc)
//   FUNCTION: GAMEMD 0x6EC3D0   TeamClass member pick          (callee; reloc)

#include "house_class_pick_target_methods.h"

// FUNCTION: GAMEMD 0x50D170
//
// Picks a super-weapon target cell of the given target type for this house.
// The first team owned by the house lends one of its members; that member's
// GreatestThreat search (with the type mapped to a ThreatType mask, from the
// member's own position, enemies of the house only) names the target, whose
// position is converted from leptons to a cell. No team or no target gives
// the "no cell" sentinel. The result is a CellStruct returned through the
// hidden pointer.
Cell HouseClass::PickTargetByType(int targetType)
{
    int threat = FUN_00645BB0(targetType);

    Team_0050D170* team = 0;
    for (int i = 0; i < DAT_008B40E8.Count; i++) {
        team = DAT_008B40E8[i];
        if (team->Owner == this) {
            break;
        }
    }

    if (team != 0 && team->Owner == this) {
        Obj_0050D170* member = team->FUN_006EC3D0();
        Coord_0050D170 coord;
        Obj_0050D170* target = (member->*member->Vtbl->GreatestThreat)(
            threat, (member->*member->Vtbl->GetCoords)(&coord), 1);
        if (target != 0) {
            Coord_0050D170* p = (target->*target->Vtbl->GetCoords)(&coord);
            Cell cell;
            cell.X = (short)(p->X / 256);
            cell.Y = (short)(p->Y / 256);
            return cell;
        }
        return DAT_00A8EF98;
    }
    return DAT_00A8EF98;
}
