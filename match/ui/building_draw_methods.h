// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   BuildingClass virtual slots 65, 69 and 70 (primary table 0x7E3EBC, RTTI
//   .?AVBuildingClass@@): their entries are 0x43CEA0, 0x43D290 and 0x43D030,
//   read at 0x7E3FC0, 0x7E3FD0 and 0x7E3FD4 of that table. Each body was read
//   from its entry to its RET (0x43CEA0..0x43D022, 0x43D030..0x43D28A,
//   0x43D290..0x43DA7F). Callee conventions come from the call sites and the
//   callees' RET counts. The classes are the canonical _layout headers; this
//   header holds only views of external objects that no canonical header
//   models yet (the shape header, the rules object, the cell map, the screen
//   transform) and the retail helpers called from here.
#ifndef GG_MATCH_UI_BUILDING_DRAW_METHODS_H
#define GG_MATCH_UI_BUILDING_DRAW_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"
#include "../_layout/anim_class.h"

// Cell coordinate. The user-declared constructor is what makes VC6 return it
// through a hidden pointer, as slot 110 (0x41BEA0, RET 4) does; other
// translation units define the same four bytes the same way.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

#include "../_layout/shp_struct.h"

#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"

// The screen transform at 0x887324 (RTTI .?AVTactical@@).
#include "../_layout/tactical.h"

// The production factory as seen from the draw code (RTTI .?AVFactoryClass@@).
#include "../_layout/factory_class.h"

// GLOBAL: GAMEMD 0xA8ED6B, 0xB73550 -- flags gating the redraw test in 0x43CEA0.
extern unsigned char DAT_00A8ED6B;
extern int DAT_00B73550;
// GLOBAL: GAMEMD 0x886FA0 -- the visible tactical rectangle.
extern RectangleStruct DAT_00886FA0;
// GLOBAL: GAMEMD 0x89DDBC
extern int DAT_0089DDBC;

#include "../_layout/rectangle_operations.h"
// FUNCTION: GAMEMD 0x4BBC90 (decl; reloc) -- no arguments.
int FUN_004BBC90();
// FUNCTION: GAMEMD 0x6D20E0 (decl; reloc) -- ECX = the value returned by slot 116.
int FUN_006D20E0(int value);

#endif  // GG_MATCH_UI_BUILDING_DRAW_METHODS_H
