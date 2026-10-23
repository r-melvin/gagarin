// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RE-findings-cross-check | behaviour-confirmed-name
//   Bytes and offsets from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (0x544CB0, 0x5471B0, 0x5471F0).
//
//   RECEIVER PROVED BY RTTI, not taken from a document. 0x00544CB0 has exactly
//   one DATA reference, 0x007ECCE4, and it is the slot the other two bodies
//   dispatch (`CALL [EAX+0x9C]`), so the vtable base is 0x007ECC48:
//     ghidra memory read 0x007ECC44 4   -> complete object locator 0x00804BC0
//     ghidra memory read 0x00804BCC 4   -> type descriptor 0x008290C8
//     ghidra memory read 0x008290C8 64  -> ".?AVIsometricTileTypeClass@@"
//   The retail class name is IsometricTileTypeClass.
//
//   Member offsets confirmed numerically from the bodies:
//     +0x0A4  unknown_A4   `MOV EAX,[ESI+0xa4]`, twice in 0x544CB0
//     +0x2F4  the byte gating the lazy load, `MOV CL,[ESI+0x2f4]`
//   Tile-image header, reached through slot +0x9C:
//     +0x00 / +0x04  the two dimensions, multiplied to give the sub-tile count
//     +0x10          the sub-tile pointer array (`[ECX + EDX*4 + 0x10]`)
//   Sub-tile image:
//     +0x24  flag word, bit 2 is the connect/ramp flag (`SHR EAX,2; AND EAX,1`)
//     +0x2A  the morph/slope byte, read with MOVSX, so signed char
//
//   The morph byte, the connect flag and the modulo are read from the bodies;
//   see the .cpp for the fall-back value.
#ifndef GG_MATCH_MAP_ISO_TILE_TYPE_CLASS_TILE_DATA_METHODS_H
#define GG_MATCH_MAP_ISO_TILE_TYPE_CLASS_TILE_DATA_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class IsometricTileTypeClass;
struct IsoTileTypeVtbl;

// One sub-tile image inside a loaded .tmp tile set.
struct SubTileImage
{
    char         _pad_000[0x24];    // +0x00
    unsigned     unknown_bits : 2;  // +0x24 bits 0-1
    unsigned     ConnectFlag : 1;   // +0x24 bit 2
    unsigned     unknown_hi : 29;   // +0x24 bits 3-31
    signed char  unknown_28;        // +0x28 height level (added to a base, less 4, at 0x5A6C10)
    char         _pad_029[0x2A - 0x29];
    signed char  MorphType;         // +0x2A
};
GG_STATIC_ASSERT(offsetof(SubTileImage, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(SubTileImage, MorphType) == 0x2A);

// The header at the front of a loaded tile set: the two dimensions, then the
// array of sub-tile image pointers at +0x10.
struct TileImageHeader
{
    int           Width;        // +0x00
    int           Height;       // +0x04
    char          _pad_008[0x10 - 0x08];
    SubTileImage* SubTiles[1];  // +0x10
};
GG_STATIC_ASSERT(offsetof(TileImageHeader, SubTiles) == 0x10);

class IsometricTileTypeClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    TileImageHeader* GetTileData();          // GAMEMD 0x544CB0  slot +0x9C
    int              GetMorphType(int idx);   // GAMEMD 0x5471B0
    bool             GetConnectFlag(int idx); // GAMEMD 0x5471F0

    // FUNCTION: GAMEMD 0x547020 (decl; reloc) — the lazy tile-set loader.
    void LoadTileData();

    IsoTileTypeVtbl* Vfptr;                    // +0x000
    char             _pad_004[0x0A4 - 0x004];
    TileImageHeader* unknown_A4;                 // +0x0A4
    char             _pad_0A8[0x294 - 0x0A8];
    int              unknown_294;              // +0x294 copied into CellClass +0x38 at 0x5A6C10
    char             _pad_298[0x2E4 - 0x298];
    int              unknown_2E4;              // +0x2E4 sub-tile columns (loop bound in 0x5A7E90 / 0x5A7FA0)
    int              unknown_2E8;              // +0x2E8 sub-tile rows
    char             _pad_2EC[0x2F4 - 0x2EC];
    unsigned char    TileDataLoadable;         // +0x2F4
};
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, Vfptr)            == 0x000);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_A4)         == 0x0A4);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_294)        == 0x294);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_2E4)        == 0x2E4);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_2E8)        == 0x2E8);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, TileDataLoadable) == 0x2F4);

// The class has to be complete before this typedef, or VC6 falls back to the
// multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef TileImageHeader* (IsometricTileTypeClass::*GetTileDataFn)();

struct IsoTileTypeVtbl
{
    char          _pad_000[0x9C];
    GetTileDataFn At_9C;    // +0x9C
};
GG_STATIC_ASSERT(offsetof(IsoTileTypeVtbl, At_9C) == 0x9C);

#endif // GG_MATCH_MAP_ISO_TILE_TYPE_CLASS_TILE_DATA_METHODS_H
