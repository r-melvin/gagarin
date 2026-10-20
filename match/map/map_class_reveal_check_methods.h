// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and slots read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x5865F0: the cell's MapCoords at +0x24 and Level
//   at +0x11B (MOVSX), the cell array at 0x87F924 (map instance 0x87F7E8 +
//   0x13C) bounded by the constant 0x40000, the fallback cell at 0xABDC50
//   with its coords at 0xABDC74, the techno vtable slot +0x198 with one
//   pushed argument, and the two callees 0x6565A0 (map singleton, CellStruct*)
//   and 0x47C3D0 (cell, Point2D const&, bool, exclude). YRpp (consult-only,
//   no LICENSE) names RevealCheck, InvalidCell, FindTechnoNearestTo and the
//   vtable map names slot 0x198 DiscoveredBy; every offset reconfirmed here.
#ifndef GG_MATCH_MAP_MAP_CLASS_REVEAL_CHECK_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_REVEAL_CHECK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Cell_005865F0 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(Cell_005865F0) == 0x4);

struct Point_005865F0 { int X; int Y; };
GG_STATIC_ASSERT(sizeof(Point_005865F0) == 0x8);

struct House_005865F0;
struct Vtbl_005865F0;

struct Techno_005865F0
{
    Vtbl_005865F0* Vptr;    // +0x0000
};

typedef bool (Techno_005865F0::*Fn198_005865F0)(House_005865F0* house);

struct Vtbl_005865F0
{
    char _pad000[0x198];           // +0x0000
    Fn198_005865F0 DiscoveredBy;   // +0x0198
};
GG_STATIC_ASSERT(offsetof(Vtbl_005865F0, DiscoveredBy) == 0x198);

struct CellClass_005865F0
{
    char _pad0000[0x24];              // +0x0000
    Cell_005865F0 MapCoords;          // +0x0024
    char _pad0028[0x11B - 0x28];      // +0x0028
    signed char Level;                // +0x011B

    // FUNCTION: GAMEMD 0x47C3D0 (decl; reloc) — CellClass::FindTechnoNearestTo.
    Techno_005865F0* FindTechnoNearestTo(Point_005865F0 const& offset, bool alt,
                                         Techno_005865F0 const* exclude);
};
GG_STATIC_ASSERT(offsetof(CellClass_005865F0, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass_005865F0, Level) == 0x11B);

// GLOBAL: GAMEMD 0xABDC50 — MapClass::InvalidCell (its MapCoords is 0xABDC74).
extern CellClass_005865F0 InvalidCell_005865F0;

struct Map_005865F0
{
    char _pad0000[0x13C];             // +0x0000
    CellClass_005865F0** Cells;       // +0x013C

    // FUNCTION: GAMEMD 0x5865F0 — MapClass::RevealCheck (`this` never read).
    void RevealCheck(CellClass_005865F0* cell, House_005865F0* house, bool redraw);
    // FUNCTION: GAMEMD 0x6565A0 (decl; reloc) — redraw at a cell.
    void FUN_006565A0(Cell_005865F0* cell);
};
GG_STATIC_ASSERT(offsetof(Map_005865F0, Cells) == 0x13C);

// GLOBAL: GAMEMD 0x87F7E8 — the map instance; its Cells member is 0x87F924.
extern Map_005865F0 MapInstance_005865F0;

#endif  // GG_MATCH_MAP_MAP_CLASS_REVEAL_CHECK_METHODS_H
