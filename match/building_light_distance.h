// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The distance BuildingLightClass expands inline at 0x4361D0 and 0x436DA0, read off the user's retail
//   gamemd.exe v1.001; the two users sit in separate files here.
#ifndef GG_MATCH_BUILDING_LIGHT_DISTANCE_H
#define GG_MATCH_BUILDING_LIGHT_DISTANCE_H

#include "_layout/coord_struct.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- sqrt.
extern "C" double __cdecl FUN_004CAC40(double value);

// The straight-line distance from `from` to `to`, expanded inline at both users.
static inline int DistanceBetween_00436DA0(const CoordStruct& to, const CoordStruct& from)
{
    int dx = to.X - from.X;
    int dy = to.Y - from.Y;
    int dz = to.Z - from.Z;
    double squared = (double)dy * dy + (double)dz * dz + (double)dx * dx;
    return (int)FUN_004CAC40(squared);
}

#endif // GG_MATCH_BUILDING_LIGHT_DISTANCE_H
