// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// REA/Ghidra entry-origin analysis confirms 0x486840..0x486889, including
// RET 4 at 0x486886. Retail primary table 0x7E4EEC has this entry at +0x48.
// Signed word reads at this+24/+26 establish the cell coordinate fields;
// the output stores establish CoordStruct's three dwords and hidden result.
// The shared CellClass layout keeps explicit vptr fields, so this binds the
// body using a nonvirtual member symbol. It does not reconstruct the full table.
#include "../_layout/cell_class.h"
#include "../_layout/geometry2d.h"

GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(CellStruct, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x08);
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0x0C);

// Partial slot view only; no complete CellClass vtable is emitted or claimed.
struct CellCoordsVtablePrefix
{
    void* unknown_00[18];
    void* GetCoords;
};
GG_STATIC_ASSERT(offsetof(CellCoordsVtablePrefix, GetCoords) == 0x48);

// FUNCTION: GAMEMD 0x486840
CoordStruct CellClass::GetCoords() const
{
    int x = MapCoords.X * 256 + 128;
    int y = MapCoords.Y * 256 + 128;
    Point2D center = { x, y };
    int z = GetFloorHeight(center);
    CoordStruct result = { x, y, z };
    return result;
}
