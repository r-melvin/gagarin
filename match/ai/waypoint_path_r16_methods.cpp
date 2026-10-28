// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   WaypointPathClass members read off retail gamemd.exe v1.001, round 16. The path object is
//   seen through WaypointPathView_r16, which carries only the members these bodies touch (the
//   vector of waypoint coordinates at +0x28 is reached through a cast).
//   Address index: 0x7639A0.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../_layout/coord_struct.h"
#include "../core/vector_class_operations.h"

inline bool operator==(const CoordStruct& a, const CoordStruct& b)
{
    return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
}
inline bool operator!=(const CoordStruct& a, const CoordStruct& b)
{
    return !(a == b);
}

inline CellStruct Coord2Cell(const CoordStruct* coord)
{
    CellStruct cell;
    cell.X = (short)(coord->X / 256);
    cell.Y = (short)(coord->Y / 256);
    return cell;
}

inline CoordStruct CellToCoord(const CellStruct& cell)
{
    CoordStruct result;
    result.X = cell.X * 256 + 128;
    result.Y = cell.Y * 256 + 128;
    result.Z = 0;
    return result;
}

class WaypointPathView_r16
{
public:
    bool FUN_007639A0(CoordStruct* where);

    char unknown_00[0x24];
    int SearchIndex;   // +0x24
};
GG_STATIC_ASSERT(offsetof(WaypointPathView_r16, SearchIndex) == 0x24);

// FUNCTION: GAMEMD 0x7639A0
// Append a waypoint, snapped to the centre of its cell, unless the path has a search index set.
bool WaypointPathView_r16::FUN_007639A0(CoordStruct* where)
{
    CellStruct cell = Coord2Cell(where);
    CoordStruct snapped = CellToCoord(cell);
    snapped.Z = where->Z;
    if (SearchIndex == -1) {
        reinterpret_cast<DynamicVectorClass<CoordStruct>*>((char*)this + 0x28)->AddItem(snapped);
    }
    return true;
}
