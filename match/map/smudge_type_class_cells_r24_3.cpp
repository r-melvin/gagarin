// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at 0x6B6080 (SmudgeTypeClass, layout in
//   terrain_objects/smudge_type_class.h).
//
//   Address index: 0x6B6080

#include "terrain_objects/smudge_type_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"


// One tile type of the theater table at 0xA8ED2C; only its placement flag is read here.
struct IsoTileTypeView_006B5F80
{
    char unknown_000[0x2E0];
    bool CanHoldSmudge;    // +0x2E0
};
GG_STATIC_ASSERT(offsetof(IsoTileTypeView_006B5F80, CanHoldSmudge) == 0x2E0);
// GLOBAL: GAMEMD 0xA8ED2C / 0xA8ED38 -- the tile type table's items and count.
extern IsoTileTypeView_006B5F80** DAT_00A8ED2C;
extern int DAT_00A8ED38;

// The map's cell lookup, taking the coordinate by value (as retail's inline wrapper does).
static __inline CellClass* CellAt(CellStruct cell)
{
    return DAT_0087F7E8.FUN_005657A0(&cell);
}

// FUNCTION: GAMEMD 0x6B6080
// Stamp this smudge type onto every cell of its Width x Height footprint starting
// at `cell`, numbering the cells row by row, and redraw each one.
void SmudgeTypeClass::Method_6B6080(const MapObjCell* cell)
{
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            CellStruct at;
            at.X = cell->X + x;
            at.Y = cell->Y + y;
            CellClass* target = CellAt(at);
            target->SmudgeTypeIndex = ArrayIndex;
            target->SmudgeData = y * Width + x;
            target->MarkForRedraw();
        }
    }
}

// FUNCTION: GAMEMD 0x6B5F80
// Can this smudge type be placed with its top corner at `cell`? Every cell of the
// footprint must be free of a smudge, overlay and (unless `flag`) building, and
// sit on a tile type that accepts smudges.
bool SmudgeTypeClass::Method_6B5F80(const MapObjCell* cell, bool flag)
{
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            CellStruct at;
            at.X = cell->X + x;
            at.Y = cell->Y + y;
            CellClass* target = CellAt(at);
            if (!DAT_0087F7E8.FUN_00568300(cell)
                || target->SlopeIndex != 0
                || target->SmudgeTypeIndex != -1
                || target->OverlayTypeIndex != -1)
                return false;
            if (!flag && target->GetBuilding() != 0)
                return false;
            int tile = target->IsoTileTypeIndex;
            if (tile < 0 || tile >= DAT_00A8ED38)
                tile = 0;
            if (!DAT_00A8ED2C[tile]->CanHoldSmudge)
                return false;
        }
    }
    return true;
}
