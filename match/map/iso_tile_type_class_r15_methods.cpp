// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and the table address read off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI at each annotated address. Receiver is IsometricTileTypeClass
//   (retail RTTI, see iso_tile_type_class_tile_data_methods.h); the slot +0x9C call is
//   GetTileData.
//
// Address index: 0x544BE0 0x544C80 0x549A60
#include "iso_tile_type_class_tile_data_methods.h"

// Sub-tile image fields beyond the ones SubTileImage names; a view over the same record.
struct SubTileView_r15
{
    int           unknown_00;
    int           unknown_04;
    char          Pad_08[0x10];
    int           unknown_18;
    char          Pad_1C[0x08];
    unsigned int  unknown_24;
    char          Pad_28;
    signed char   unknown_29;
};
GG_STATIC_ASSERT(offsetof(SubTileView_r15, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(SubTileView_r15, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(SubTileView_r15, unknown_29) == 0x29);

// GLOBAL: GAMEMD 0x8288E4 -- value table indexed by the sub-tile's +0x29 byte.
extern int DAT_008288E4[];

// FUNCTION: GAMEMD 0x544BE0
// Table value for the sub-tile at `idx` (wrapped on the sub-tile count), or zero.
int IsometricTileTypeClass::FUN_00544BE0(int idx)
{
    TileImageHeader* data = (this->*this->Vfptr->At_9C)();

    if (data != 0) {
        SubTileView_r15* tile = (SubTileView_r15*)data->SubTiles[idx % (data->Height * data->Width)];
        if (tile != 0) {
            return DAT_008288E4[tile->unknown_29];
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x544C80
// Loads the tile set on first use and reports whether it is present.
bool IsometricTileTypeClass::FUN_00544C80()
{
    if (this->unknown_A4 == 0 && this->TileDataLoadable) {
        this->LoadTileData();
    }
    return this->unknown_A4 != 0;
}

// FUNCTION: GAMEMD 0x549A60
// For a sub-tile with bit 0 of its flag word set, the span +0x18 minus +0x04; else zero.
int IsometricTileTypeClass::FUN_00549A60(int idx)
{
    TileImageHeader* data = (this->*this->Vfptr->At_9C)();

    if (data != 0 && idx < data->Height * data->Width) {
        SubTileView_r15* tile = (SubTileView_r15*)data->SubTiles[idx];
        if (tile != 0 && (tile->unknown_24 & 1)) {
            return tile->unknown_18 - tile->unknown_04;
        }
    }
    return 0;
}
