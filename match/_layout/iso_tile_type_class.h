// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RE-findings-cross-check | behaviour-confirmed-name
//   IsometricTileTypeClass (retail RTTI .?AVIsometricTileTypeClass@@, vtable base 0x7ECC48) as modelled so far:
//   the lazy tile-set loader and its accessors (0x544BE0, 0x544CB0, 0x5471B0, 0x5471F0, 0x549A60) and the
//   TileInsertType element named by the retail vector RTTI. Offsets are read from those bodies; see
//   match/map/iso_tile_type_class_tile_data_methods.h for the evidence.
#ifndef GG_MATCH_LAYOUT_ISO_TILE_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_ISO_TILE_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class IsometricTileTypeClass;
class IsometricTileClass;
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
GG_STATIC_ASSERT(offsetof(TileImageHeader, Width) == 0x00);
GG_STATIC_ASSERT(offsetof(TileImageHeader, Height) == 0x04);
GG_STATIC_ASSERT(offsetof(TileImageHeader, SubTiles) == 0x10);

class IsometricTileTypeClass
{
public:
    struct TileInsertType; // nested pointer type attested by TU110 vector RTTI

    // Declared ascending by retail address (reccmp/isle TU discipline).
    TileImageHeader* GetTileData();          // GAMEMD 0x544CB0  slot +0x9C
    int              GetMorphType(int idx);   // GAMEMD 0x5471B0
    bool             GetConnectFlag(int idx); // GAMEMD 0x5471F0

    // FUNCTION: GAMEMD 0x547020 (decl; reloc) — the lazy tile-set loader.
    void LoadTileData();

    // Round 15 additions (GAMEMD 0x544BE0, 0x544C80, 0x549A60).
    int              FUN_00544BE0(int idx);
    bool             FUN_00544C80();
    int              FUN_00549A60(int idx);
    // Round 21 addition (GAMEMD 0x547150).
    bool             FUN_00547150(int idx, int* outA, int* outB);
    // Round 19 additions (GAMEMD 0x544C20, 0x544CE0).
    bool             FUN_00544C20(int idx, bool load);
    static int       FUN_00544CE0(const char* name);
    // Round 25 addition (GAMEMD 0x549AE0).
    IsometricTileClass* FUN_00549AE0(int unused);

    IsoTileTypeVtbl* Vfptr;                    // +0x000
    char             _pad_004[0x024 - 0x004];
    char             ID[0x19];                 // +0x024 type name (AbstractTypeClass::ID)
    char             _pad_03D[0x0A4 - 0x03D];
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
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, ID)                 == 0x024);
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

#endif  // GG_MATCH_LAYOUT_ISO_TILE_TYPE_CLASS_H
