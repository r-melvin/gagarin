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
#include "vector_class.h"

struct CellStruct;
class IsometricTileTypeClass;
class IsometricTileClass;
class ObjectClass;
class HouseClass;
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
    // Added with GAMEMD 0x547370.
    CellStruct* FUN_00547370();

    IsoTileTypeVtbl* Vfptr;                    // +0x000
    char             _pad_004[0x024 - 0x004];
    char             ID[0x19];                 // +0x024 type name (AbstractTypeClass::ID)
    char             _pad_03D[0x0A4 - 0x03D];
    TileImageHeader* unknown_A4;                 // +0x0A4
    char             _pad_0A8[0x294 - 0x0A8];
    int              unknown_294;              // +0x294 copied into CellClass +0x38 at 0x5A6C10
    int              unknown_298;              // +0x298 ctor = 0xFFFF @0x5447E4
    int              unknown_29C;              // +0x29C ctor = 0xFFFF @0x5447EA
    int              unknown_2A0;              // +0x2A0 ctor = 0 @0x5447F0
    DynamicVectorClassLayout unknown_vec_2A4;  // +0x2A4 (0x18) DynamicVectorClass<unsigned short*>: vptr 0x7ECCEC (RTTI .?AV?$DynamicVectorClass@PAG@@) @0x544811,
                                               //   Count 0 @0x544825, CapacityIncrement 0xA @0x54481B
    int              unknown_2BC;              // +0x2BC ctor = 0 @0x544868
    int              unknown_2C0;              // +0x2C0 ctor @0x544836
    int              unknown_2C4;              // +0x2C4 ctor @0x54483C
    int              unknown_2C8;              // +0x2C8 ctor @0x544842
    int              unknown_2CC;              // +0x2CC ctor = 0xFFFF @0x544830
    int              unknown_2D0;              // +0x2D0 ctor @0x544848
    int              unknown_2D4;              // +0x2D4 ctor @0x544852
    int              unknown_2D8;              // +0x2D8 ctor = 0 @0x54486E
    int              unknown_2DC;              // +0x2DC ctor stores its fourth argument (low byte) @0x544874
    unsigned char    unknown_2E0;              // +0x2E0 ctor = 0 @0x54487A
    unsigned char    unknown_2E1;              // +0x2E1 ctor = 0 @0x544880
    unsigned char    unknown_2E2;              // +0x2E2 ctor = 1 @0x544886
    unsigned char    unknown_2E3;              // +0x2E3 ctor = 0 @0x54488D
    int              unknown_2E4;              // +0x2E4 sub-tile columns (loop bound in 0x5A7E90 / 0x5A7FA0)
    int              unknown_2E8;              // +0x2E8 sub-tile rows
    int              unknown_2EC;              // +0x2EC ctor stores its fifth argument (low byte) @0x54489F
    int              unknown_2F0;              // +0x2F0 ctor = 1 @0x5448A5
    unsigned char    TileDataLoadable;         // +0x2F4
    unsigned char    unknown_2F5;              // +0x2F5 ctor = 0 @0x5449C5
    char             _pad_2F6[0x305 - 0x2F6];
    unsigned char    unknown_305;              // +0x305 ctor = 1 @0x5448B5
    unsigned char    unknown_306;              // +0x306 ctor = 0 @0x5448BC
    char             _pad_307[1];              // +0x307
    int              unknown_308;              // +0x308 ctor = 0 @0x5448C2
};
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, Vfptr)            == 0x000);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, ID)                 == 0x024);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_A4)         == 0x0A4);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_294)        == 0x294);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_2E4)        == 0x2E4);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_2E8)        == 0x2E8);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_298)        == 0x298);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_vec_2A4)    == 0x2A4);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_2BC)        == 0x2BC);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_2D8)        == 0x2D8);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_2E0)        == 0x2E0);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_2EC)        == 0x2EC);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, TileDataLoadable) == 0x2F4);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_305)        == 0x305);
GG_STATIC_ASSERT(offsetof(IsometricTileTypeClass, unknown_308)        == 0x308);
// sizeof from the allocation `PUSH 0x30C; CALL 0x7C8E17` at 0x6C2FBC.
GG_STATIC_ASSERT(sizeof(IsometricTileTypeClass)                        == 0x30C);

// The class has to be complete before this typedef, or VC6 falls back to the
// multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef TileImageHeader* (IsometricTileTypeClass::*GetTileDataFn)();

// Slot 35 (CreateObject, 0x549AE0) takes the owning house; FUN_00549AE0 declares it with an int and its own result type.
typedef ObjectClass* (IsometricTileTypeClass::*CreateObjectFn)(HouseClass*);

struct IsoTileTypeVtbl
{
    char           _pad_000[0x8C];
    CreateObjectFn At_8C;   // +0x8C slot 35
    char           _pad_090[0x9C - 0x90];
    GetTileDataFn  At_9C;   // +0x9C
};
GG_STATIC_ASSERT(offsetof(IsoTileTypeVtbl, At_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(IsoTileTypeVtbl, At_9C) == 0x9C);

#endif  // GG_MATCH_LAYOUT_ISO_TILE_TYPE_CLASS_H
