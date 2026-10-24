// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#ifndef GG_MATCH_LAYOUT_WAYPOINT_CLASS_H
#define GG_MATCH_LAYOUT_WAYPOINT_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// Native DynamicVectorClass<WaypointClass> RTTI encodes V (class), not U.
// The existing byte-checked vector element member shapes are retained here.
class WaypointClass
{
public:
    int X;
    int Y;
    int Z; // signed height: planning projection FILD/AdjustForZ in6DAD60
    WaypointClass(int a = 0, int b = 0, int c = 0) : X(a), Y(b), Z(c) {}
    ~WaypointClass() {}
    bool operator==(const WaypointClass& other) const
    { return X == other.X && Y == other.Y && Z == other.Z; }
    bool operator!=(const WaypointClass& other) const { return !(*this == other); }
};
GG_STATIC_ASSERT(offsetof(WaypointClass, X) == 0);
GG_STATIC_ASSERT(offsetof(WaypointClass, Y) == 4);
GG_STATIC_ASSERT(offsetof(WaypointClass, Z) == 8);
GG_STATIC_ASSERT(sizeof(WaypointClass) == 0xC);
#endif
