// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at each
//   annotated address. Receiver is IsometricTileTypeClass (retail RTTI, see
//   iso_tile_type_class_tile_data_methods.h); the slot +0x9C call is GetTileData.
//
// Address index: 0x547150
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
#include "iso_tile_type_class_tile_data_methods.h"

// Tile-image header fields beyond the ones TileImageHeader names; a view over the same record.
struct TileHeaderView_r21
{
    int Width;           // +0x00
    int Height;          // +0x04
    int unknown_08;      // +0x08
    int unknown_0C;      // +0x0C
    void* SubTiles[1];   // +0x10
};
GG_STATIC_ASSERT(offsetof(TileHeaderView_r21, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(TileHeaderView_r21, SubTiles) == 0x10);

// Sub-tile image fields beyond the ones SubTileImage names; a view over the same record.
struct SubTileView_r21
{
    int           unknown_00;
    int           unknown_04;
    char          Pad_08[0x10];
    int           unknown_18;
    char          Pad_1C[0x08];
    unsigned int  unknown_24;
};
GG_STATIC_ASSERT(offsetof(SubTileView_r21, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(SubTileView_r21, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(SubTileView_r21, unknown_24) == 0x24);

// FUNCTION: GAMEMD 0x547150
// Offsets of the sub-tile at `idx` (wrapped on the sub-tile count): outA gets the header's
// +0x08 value; outB gets the +0x0C value, shifted by the sub-tile's own extent when its
// bit 0 flag is set. False when the tile set is unavailable.
bool IsometricTileTypeClass::FUN_00547150(int idx, int* outA, int* outB)
{
    TileHeaderView_r21* data = (TileHeaderView_r21*)(this->*this->Vfptr->At_9C)();
    if (data != 0) {
        SubTileView_r21* tile = (SubTileView_r21*)data->SubTiles[idx % (data->Height * data->Width)];
        *outA = data->unknown_08;
        int b = data->unknown_0C;
        *outB = b;
        if (tile != 0 && (tile->unknown_24 & 1)) {
            *outB = tile->unknown_04 - tile->unknown_18 + b;
        }
        return true;
    }
    return false;
}
