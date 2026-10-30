// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, globals and callees read off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI at the address in each annotation.
//
// Round 17 CellClass bodies, ascending by retail address.
// Address index: 0x480180 0x4801F0
#include "../_layout/cell_class.h"
#include "../_layout/tactical.h"

// The tile-type record drawn by the cell code. A view over IsometricTileTypeClass
// (retail layout in iso_tile_type_class_tile_data_methods.h) naming only the draw call.
struct IsoTileView_r17
{
    // FUNCTION: GAMEMD 0x547CF0 (decl; reloc)
    void FUN_00547CF0(int a, int b, int surface, int x, int y, RectangleStruct clip, int level,
                      int tint, int f1, int f2, int f3, int f4, int f5, int f6);
};

extern IsoTileView_r17** DAT_00A8ED2C;   // GAMEMD 0x00A8ED2C, the tile-type table
extern int DAT_00887314;                 // GAMEMD 0x00887314, draw surface/target
extern int* DAT_0087F69C;                // GAMEMD 0x0087F69C

// FUNCTION: GAMEMD 0x480180
// Draws the first tile type at this cell's level and terrain intensity.
void CellClass::FUN_00480180(const Point2D* point, const RectangleStruct* clip)
{
    (*DAT_00A8ED2C)->FUN_00547CF0(*DAT_0087F69C, 0, DAT_00887314, point->X, point->Y, *clip,
                                  Level, (short)Intensity_Terrain, 1, 0, 0, 1, 0, 0);
}

// GLOBAL: GAMEMD 0x00887324 -- the tactical view.
extern Tactical* DAT_00887324;

#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;
#include "../_layout/house_class.h"
extern HouseClass* DAT_00A83D4C;

// FUNCTION: GAMEMD 0x4801F0
// Refreshes the cell's visibility and fog levels from the tactical view and draws
// the matching edge overlays.
void CellClass::FUN_004801F0(const Point2D* point, const RectangleStruct* clip)
{
    signed char vis = DAT_00887324->FUN_006D8700(&MapCoords, 0);
    Visibility = vis;
    int level = vis;
    if (level == -2)
        level = 15;
    else if (level == -1)
        level = 0;
    FUN_0047EFE0(point, clip, level);
    signed char fog = DAT_00887324->FUN_006D8700(&MapCoords, 1);
    Foggedness = fog;
    if ((DAT_00A8B230->unknown_0000 & 0x1000) && !DAT_00A83D4C->Defeated) {
        level = fog;
        if (level == -2)
            level = 15;
        else if (level == -1)
            level = 0;
        FUN_0047F250(point, clip, level);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87F69C
int* DAT_0087F69C;
// GLOBAL: GAMEMD 0xA8ED2C
IsoTileView_r17** DAT_00A8ED2C;
// GLOBAL: GAMEMD 0x887314
int DAT_00887314;
// END defined globals
