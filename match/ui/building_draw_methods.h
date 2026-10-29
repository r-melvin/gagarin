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

// Rules object behind the pointer at 0x8871E0 (used prefix only).
struct Rules_008871E0
{
    char unknown_0000[0x1700];
    double unknown_1700;             // health-ratio threshold (compared with GetHealthPercentage)
    char unknown_1708[0x16C];
    unsigned char unknown_1874[16][3];   // colour table, three bytes per entry
    int unknown_18A4;                // table index, airstrike tint
    char unknown_18A8[8];
    int unknown_18B0;                // table index, force-shield tint
};
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_1700) == 0x1700);
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_1874) == 0x1874);
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_18A4) == 0x18A4);
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_18B0) == 0x18B0);

// GLOBAL: GAMEMD 0x8871E0 -- pointer to the rules object.
extern Rules_008871E0* DAT_008871E0;

// Map cell as far as these bodies read it.
struct MapCell_0043D290
{
    char unknown_000[0x10A];
    short unknown_10A;               // read with a sign-extending load
};
GG_STATIC_ASSERT(offsetof(MapCell_0043D290, unknown_10A) == 0x10A);

// The map instance at 0x87F7E8 (RTTI .?AVMapClass@@).
class MapClass
{
public:
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- the cell at a cell coordinate; RET 4.
    MapCell_0043D290* FUN_005657A0(const CellStruct& cell);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapClass DAT_0087F7E8;

// The screen transform at 0x887324 (RTTI .?AVTactical@@).
#include "../_layout/tactical.h"
// GLOBAL: GAMEMD 0x887324 -- pointer to the transform.
extern Tactical* DAT_00887324;

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
// FUNCTION: GAMEMD 0x487950 (decl; reloc) -- the cell's shroud test, ECX = cell.
bool FUN_00487950(MapCell_0043D290* cell);
// FUNCTION: GAMEMD 0x4BBC90 (decl; reloc) -- no arguments.
int FUN_004BBC90();
// FUNCTION: GAMEMD 0x6D20E0 (decl; reloc) -- ECX = the value returned by slot 116.
int FUN_006D20E0(int value);

#endif  // GG_MATCH_UI_BUILDING_DRAW_METHODS_H
