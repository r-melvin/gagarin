// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The single declaration of the three constant step tables built by the
//   header initialisers (defined in header_init_0049f0e0.cpp and
//   header_init_0048e290.cpp). The element types are the constructor-bearing
//   shapes retail needs to emit those initialisers; they derive from the plain
//   CellStruct / CoordStruct, so users read the tables as the plain types.
#ifndef GG_MATCH_CORE_CELL_STEP_TABLES_H
#define GG_MATCH_CORE_CELL_STEP_TABLES_H

#include "header_init_shapes.h"
#include "../_layout/geometry2d.h"

// GLOBAL: GAMEMD 0x89F688 -- the eight one-cell steps indexed by facing, N first, clockwise.
extern HeaderCellInit DAT_0089F688[8];
// GLOBAL: GAMEMD 0x89F6D8 -- the same eight steps in leptons.
extern Point2D DAT_0089F6D8[8];
// GLOBAL: GAMEMD 0x89E9F0 -- the five sub-cell spots: centre, then the four quarter points.
extern HeaderCoordInit DAT_0089E9F0[5];

#endif
