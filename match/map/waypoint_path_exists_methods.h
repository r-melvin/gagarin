// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x763A50: the waypoint vector's count is `[EDI+0x38]`
//   and its items `[EDI+0x2C]` (a DynamicVectorClass at +0x28), walked with a
//   12-byte stride (`ADD EDI,0xC`), each element's first two ints signed-
//   divided by 256 (`CDQ; AND EDX,0xFF; ADD; SAR 8`) and compared as 16-bit
//   values (`CMP SI,BX` / `CMP AX,BP`); the found index is stored to
//   `[EAX+0x24]`. The argument is read the same way (`[ESI]`, `[ESI+4]`), so
//   it is a 3-int coordinate rather than YRpp's 8-byte WaypointClass. Name
//   cross-checked against YRpp WaypointPathClass::WaypointExistsAt.
#ifndef GG_MATCH_MAP_WAYPOINT_PATH_EXISTS_METHODS_H
#define GG_MATCH_MAP_WAYPOINT_PATH_EXISTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 3D lepton coordinate; only X and Y are read here, the stride pins Z.
#include "../_layout/coord_struct.h"
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

// 2D short cell coordinate (sizeof == 4): X@0, Y@2. The 16-bit compares in
// the loop come from comparing two of these.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

inline bool operator==(CellStruct const& a, CellStruct const& b)
{
    return a.X == b.X && a.Y == b.Y;
}

// Lepton coordinate -> cell coordinate (signed divide by 256 on each axis).
inline CellStruct Coord2Cell(CoordStruct const* coord)
{
    CellStruct cell;
    cell.X = (short)(coord->X / 256);
    cell.Y = (short)(coord->Y / 256);
    return cell;
}

class WaypointPathClass
{
public:
    char         _pad000[0x24];   // +0x0000
    int          FoundIndex;      // +0x0024  written on a hit
    void*        VectorVtbl;      // +0x0028  DynamicVectorClass<CoordStruct> vptr
    CoordStruct* Waypoints;       // +0x002C  .Items
    int          Capacity;        // +0x0030
    int          IsAllocated;     // +0x0034
    int          WaypointCount;   // +0x0038  .Count

    // FUNCTION: GAMEMD 0x763A50
    bool WaypointExistsAt(CoordStruct const* coords);
};
GG_STATIC_ASSERT(offsetof(WaypointPathClass, FoundIndex) == 0x24);
GG_STATIC_ASSERT(offsetof(WaypointPathClass, Waypoints) == 0x2C);
GG_STATIC_ASSERT(offsetof(WaypointPathClass, WaypointCount) == 0x38);

#endif  // GG_MATCH_MAP_WAYPOINT_PATH_EXISTS_METHODS_H
