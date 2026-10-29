// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off retail gamemd.exe v1.001 at 0x50DF30: BaseSpawnCell +0x5490 and
//   BaseCenter +0x5494 (see house_class.h), the "no cell" sentinel at 0xA8EF98, the empty
//   coordinate at 0xA8EFF8, MapClass::GetCellAt 0x5657A0 on the map at 0x87F7E8, and CellClass
//   vtable slot 18 (+0x48) which returns the cell's coordinate through a hidden pointer.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT

#include "../_layout/house_class.h"
#include "../_layout/cell_class.h"

// GLOBAL: GAMEMD 0xA8EF98 -- the "no cell" sentinel.
extern CellStruct NoCell_00A8EF98;
// GLOBAL: GAMEMD 0xA8EFF8 -- the coordinate used when no base cell is set.
extern CoordStruct EmptyCoord_00A8EFF8;

// The map instance (0x87F7E8) as this call sees it.
struct MapView_0050DF30
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- MapClass::GetCellAt.
    CellClass* FUN_005657A0(const CellStruct* cell);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapView_0050DF30 MapInstance_0087F7E8_0050DF30;

// FUNCTION: GAMEMD 0x50DF30
// The map-space coordinate of the house's base: the centre cell if set, otherwise the spawn
// cell; the empty coordinate when neither is set.
CoordStruct HouseClass::FUN_0050DF30() const
{
    CellStruct base;
    if (BaseCenter.X == NoCell_00A8EF98.X && BaseCenter.Y == NoCell_00A8EF98.Y) {
        base = BaseSpawnCell;
    } else {
        base = BaseCenter;
    }
    CellStruct cell = base;
    if (cell.X == NoCell_00A8EF98.X && cell.Y == NoCell_00A8EF98.Y) {
        return EmptyCoord_00A8EFF8;
    }
    return MapInstance_0087F7E8_0050DF30.FUN_005657A0(&cell)->vf_18();
}
