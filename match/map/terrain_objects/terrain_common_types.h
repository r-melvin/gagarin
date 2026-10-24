// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   Small value types and inline helpers shared by every class of the terrain-objects module
//   (OverlayClass, OverlayTypeClass, SmudgeClass, SmudgeTypeClass, TerrainClass, TerrainTypeClass).
//   Each is declared once, here, with the union of the members and constructors the module's bodies
//   use. Layouts were read from the retail gamemd.exe v1.001 (the object and type constructors and
//   the INI readers of the three families).
//
// Naming: the three families were first recovered independently under Overlay* / Smudge* / Terrain*
// prefixes. Everything the families share lives under the MapObj* prefix.
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_TYPES_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_TYPES_H

#include <stddef.h>
#include <stdlib.h>
#include <new.h>
#include <objidl.h>   // IStream, IPersistStream, CLSID, HRESULT (VC98 SDK, LIBRARY)
#include "../../_rt/gg_static_assert.h"

class OverlayClass;
class OverlayTypeClass;
class SmudgeClass;
class SmudgeTypeClass;
class TerrainClass;
class TerrainTypeClass;

// Marker for the no-initialisation constructors (Load's placement new re-runs the vptr stores).
struct MapObjNoInit {};

// Three-dword world coordinate (a lepton triple).
struct MapObjCoord
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08

    MapObjCoord() {}
    MapObjCoord(int x, int y, int z) : X(x), Y(y), Z(z) {}
};
GG_STATIC_ASSERT(offsetof(MapObjCoord, X) == 0);
GG_STATIC_ASSERT(offsetof(MapObjCoord, Y) == 4);
GG_STATIC_ASSERT(offsetof(MapObjCoord, Z) == 8);
GG_STATIC_ASSERT(sizeof(MapObjCoord) == 0xC);

// Map cell coordinate pair: two 16-bit halves (read as `MOVSX word [p]` / `MOVSX word [p+2]`). The user
// constructors make it a non-POD, so a by-value return goes through a hidden pointer exactly as the
// retail slot 110 does.
struct MapObjCell
{
    short X;   // +0x00
    short Y;   // +0x02

    MapObjCell() {}
    MapObjCell(short x, short y) : X(x), Y(y) {}

    // The address of this (typically a temporary): MapObjCell().Address() is the compiler-made buffer
    // that receives a hidden-pointer return, with the lifetime a by-value return would give it.
    MapObjCell* Address() { return this; }
};
GG_STATIC_ASSERT(offsetof(MapObjCell, X) == 0);
GG_STATIC_ASSERT(offsetof(MapObjCell, Y) == 2);
GG_STATIC_ASSERT(sizeof(MapObjCell) == 4);

// A screen position (x, y).
struct MapObjPoint
{
    int X;   // +0x00
    int Y;   // +0x04

    MapObjPoint() {}
    MapObjPoint(int x, int y) : X(x), Y(y) {}
    MapObjPoint operator+(const MapObjPoint& b) const { return MapObjPoint(X + b.X, Y + b.Y); }
    MapObjPoint operator-(const MapObjPoint& b) const { return MapObjPoint(X - b.X, Y - b.Y); }
};
GG_STATIC_ASSERT(offsetof(MapObjPoint, X) == 0);
GG_STATIC_ASSERT(offsetof(MapObjPoint, Y) == 4);
GG_STATIC_ASSERT(sizeof(MapObjPoint) == 8);

// Clip rectangle handed to the draw slots (x, y, width, height).
struct MapObjRect
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(MapObjRect, X) == 0);
GG_STATIC_ASSERT(offsetof(MapObjRect, Y) == 4);
GG_STATIC_ASSERT(offsetof(MapObjRect, Width) == 8);
GG_STATIC_ASSERT(offsetof(MapObjRect, Height) == 0xC);
GG_STATIC_ASSERT(sizeof(MapObjRect) == 0x10);

// A 24-bit colour (three bytes, no padding; copied as a word plus a byte).
struct MapObjColor
{
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02

    MapObjColor() {}
    MapObjColor(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b) {}
};
GG_STATIC_ASSERT(sizeof(MapObjColor) == 3);

// Cell coordinate addition (inline in retail: two 16-bit adds into a temporary).
inline MapObjCell operator+(const MapObjCell& a, const MapObjCell& b)
{
    MapObjCell r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    return r;
}

// A cell shifted by a pair of integer offsets (inline in retail: two 16-bit adds into a temporary).
inline MapObjCell MapObjCellShifted(const MapObjCell& a, int x, int y)
{
    MapObjCell r;
    r.X = a.X + x;
    r.Y = a.Y + y;
    return r;
}

// The map cell a lepton coordinate lies in (inline in retail: two signed divisions by 256 into a
// temporary).
template<class Coordinate>
inline MapObjCell MapObjCoordToCell(const Coordinate& coord)
{
    MapObjCell r;
    r.X = (short)(coord.X / 256);
    r.Y = (short)(coord.Y / 256);
    return r;
}

// The lepton coordinate at the centre of a cell (inline in retail).
inline MapObjCoord MapObjCellToCoord(const MapObjCell& cell)
{
    MapObjCoord coord;
    coord.X = cell.X * 256 + 128;
    coord.Y = cell.Y * 256 + 128;
    coord.Z = 0;
    return coord;
}

// A rectangle moved by a pair of offsets (inline in retail: two adds into a temporary).
inline MapObjRect MapObjRectShifted(const MapObjRect& r, int x, int y)
{
    MapObjRect out;
    out.X = r.X + x;
    out.Y = r.Y + y;
    out.Width = r.Width;
    out.Height = r.Height;
    return out;
}

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_TYPES_H
