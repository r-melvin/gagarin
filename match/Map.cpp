// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Map (class-inferred: the object holds the MapClass methods between the MainOpt and
//   MapGen objects; no source-file string names it). Retail expands GetCellAt (0x5657A0) at 92 sites in 25 functions
//   and the cell walk rewind (0x578350) at 11 sites, and keeps one out-of-line copy of each; other objects call those
//   copies. So both are plain member definitions in this file, not header inlines: VC6 /Ob2 expands a definition
//   that appears later in the same object, so the file keeps ascending retail address order.
//   The next-cell step of the walk (0x578290) is held at 70.6%, so only its declaration is in ui_display_chain.h.

#include "ui_display_chain.h"
#include "_layout/cell_class.h"
#include "_layout/house_class.h"
#include "_layout/player_ptr_00a83d4c.h"


// STRING: GAMEMD 0x82AD48 -- "We tried to reset the shroud without an owner".
extern const char DAT_0082AD48[];


// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x5657A0
CellClass* MapClass::GetCellAt(const CellStruct& cell)
{
    int index = (cell.Y << 9) + cell.X;
    if (index >= 0 && index < 0x40000) {
        CellClass* found = Owned[index];
        if (found)
            return found;
    }
    InvalidCell.MapCoords = cell;
    return &InvalidCell;
}

// FUNCTION: GAMEMD 0x56BCD0 (this unused)
// Resolve the live cell for `cell` (an empty or out-of-range slot gives the invalid cell stamped with the requested
// coordinate), reduce its MapCoords to a 4x4 quadrant per axis, and return the house's threat estimate for it.
int MapClass::GetThreatPosed(const CellStruct& cell, HouseClass* pHouse) const
{
    CellClass* pCell = Map_0087F7E8.GetCellAt(cell);
    CellStruct mc = pCell->MapCoords;
    int qy = mc.Y / 4;
    int qx = mc.X / 4;
    return pHouse->ThreatPosedEstimates[qy + 1][qx + 1];
}

// FUNCTION: GAMEMD 0x577AB0
void MapClass::Reshroud(HouseClass* house)
{
    if (house != 0)
        HouseClass_Array.Items[house->ArrayIndex]->MapIsClear = 0;

    if (house == DAT_00A83D4C || house == 0) {
        if (house == 0)
            FUN_004068E0(DAT_0082AD48);

        Map_0087F7E8.FUN_004ADEE0(0, 0);

        FUN_00578350();
        CellClass* cell = FUN_00578290();
        while (cell != 0) {
            cell->AltFlags &= ~0x18;
            cell->ShroudCounter = 1;
            cell->GapsCoveringThisCell = 0;
            cell->Flags &= ~3;
            cell = FUN_00578290();
        }

        Map_0087F7E8.FUN_004ADCD0(0, 0);
        DAT_00A83D4C->Visionary = 0;
        Map_0087F7E8.FUN_00657CE0();
        FlagToRedraw(2);
    }
}

// FUNCTION: GAMEMD 0x577BB0
void MapClass::FUN_00577BB0(HouseClass* house)
{
    if (house != 0)
        HouseClass_Array.Items[house->ArrayIndex]->MapIsClear = 0;

    if (house == DAT_00A83D4C || house == 0) {
        if (house == 0)
            FUN_004068E0(DAT_0082AD48);

        FUN_00578350();
        CellClass* cell = FUN_00578290();
        while (cell != 0) {
            cell->AltFlags &= ~0x18;
            cell->Flags &= ~3;
            cell = FUN_00578290();
        }

        Map_0087F7E8.FUN_004ADFF0(0, 0);
        DAT_00A83D4C->Visionary = 0;
        Map_0087F7E8.FUN_00657CE0();
        FlagToRedraw(2);
    }
}

// FUNCTION: GAMEMD 0x578350
void MapClass::FUN_00578350()
{
    int width = MapRect.Width;
    unknown_10C = 1;
    unknown_110 = width;
    unknown_114 = width - 1;
    unknown_118 = &Owned.Items[(width << 9) + 1];
}

// FUNCTION: GAMEMD 0x578850
void MapClass::FUN_00578850()
{
    unknown_11C = LocalRect.X + LocalRect.Y + 1;
    unknown_120 = MapRect.Width - LocalRect.X + LocalRect.Y;
}
