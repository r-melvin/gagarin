// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off retail gamemd.exe v1.001 at 0x509EC0: the preferred
//   defensive cells at +0x54F4/+0x54F8 and their start time at +0x54FC (see house_class.h),
//   the RulesClass pointer at 0x8871E0 (+0xEE0) and the frame counter at 0xA8ED84.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT

#include "../_layout/house_class.h"
#include "../core/frame_counter.h"


// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0xA8EF98 -- the "no cell" sentinel.
extern CellStruct NoCell_00A8EF98;

// FUNCTION: GAMEMD 0x509EC0
// Fire the given super weapon at the house's preferred defensive cell. The
// second cell wins when it is set; otherwise the first one is used, but only
// once its start time plus the rules delay has passed.
void HouseClass::FUN_00509EC0(SuperClass* super)
{
    CellStruct cell = NoCell_00A8EF98;

    if (PreferredDefensiveCell2.X != NoCell_00A8EF98.X) goto have;
    if (PreferredDefensiveCell2.Y != NoCell_00A8EF98.Y) goto have;
    if (PreferredDefensiveCell.X == NoCell_00A8EF98.X && PreferredDefensiveCell.Y == NoCell_00A8EF98.Y) {
        return;
    }
    if (PreferredDefensiveCellStartTime + DAT_008871E0->unknown_EE0 <= CurrentFrame) {
        return;
    }
    cell = PreferredDefensiveCell;
    goto join;
have:
    cell = PreferredDefensiveCell2;
join:
    if (cell.X != NoCell_00A8EF98.X || cell.Y != NoCell_00A8EF98.Y) {
        Fire_SW(Supers.FindItemIndex(super), cell);
    }
}
