// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x6F6F60 and 0x6F70E0 in retail gamemd.exe v1.001 (Techno.CPP range): both turn
//   the height difference between the cells under two objects into a range bonus using the
//   ElevationIncrement fields of the rules object at 0x8871E0.

#include "../_layout/techno_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"

extern float __cdecl FUN_004CAC40(double value);

// GLOBAL: GAMEMD 0xB0EB34
extern int DAT_00B0EB34;

static inline CellStruct CoordToCell(const CoordStruct& coord)
{
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

static inline double ElevationCap()
{
    return Rules->ElevationBonusCap;
}

// FUNCTION: GAMEMD 0x6F6F60
// Range bonus for an arcing shot: the height difference of the two cells (never negative) is
// turned into a vertical lepton figure, and the result combines it with the same figure
// scaled by DAT_00B0EB34 into a diagonal distance.
int TechnoClass::FUN_006F6F60(AbstractClass* target)
{
    if (IsOnFloor() && target->IsOnFloor()) {
        CellStruct hereCell = CoordToCell(vf_18());
        CellStruct thereCell = CoordToCell(target->vf_18());
        CellClass* hereCellObj = DAT_0087F7E8.FUN_005657A0(&hereCell);
        CellClass* thereCellObj = DAT_0087F7E8.FUN_005657A0(&thereCell);
        int height;
        if (hereCellObj->FUN_00487D50() - thereCellObj->FUN_00487D50() < 0) {
            height = 0;
        } else {
            height = hereCellObj->FUN_00487D50() - thereCellObj->FUN_00487D50();
        }
        int steps = height / Rules->ElevationIncrement;
        double bonus = steps * Rules->ElevationIncrementBonus;
        if (bonus >= ElevationCap()) {
            bonus = ElevationCap();
        }
        int vertical = DAT_00B0EB34 * height;
        int rise = (int)bonus << 8;
        return (int)FUN_004CAC40((double)(rise * rise + vertical * vertical));
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6F70E0
// The vertical part of the same bonus, in leptons (the result of 0x6F6F60 without the diagonal).
int TechnoClass::FUN_006F70E0(AbstractClass* target)
{
    if (IsOnFloor() && target->IsOnFloor()) {
        CellStruct hereCell = CoordToCell(vf_18());
        CellStruct thereCell = CoordToCell(target->vf_18());
        CellClass* hereCellObj = DAT_0087F7E8.FUN_005657A0(&hereCell);
        CellClass* thereCellObj = DAT_0087F7E8.FUN_005657A0(&thereCell);
        int height;
        if (hereCellObj->FUN_00487D50() - thereCellObj->FUN_00487D50() < 0) {
            height = 0;
        } else {
            height = hereCellObj->FUN_00487D50() - thereCellObj->FUN_00487D50();
        }
        int steps = height / Rules->ElevationIncrement;
        double bonus = steps * Rules->ElevationIncrementBonus;
        if (bonus >= ElevationCap()) {
            bonus = ElevationCap();
        }
        return (int)bonus << 8;
    }
    return 0;
}
