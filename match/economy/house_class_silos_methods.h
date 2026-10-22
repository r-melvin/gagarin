// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4F9970: `LEA ECX,[EDI+0x2FC]` (OwnedTiberium, the
//   StorageClass whose GetTotalAmount @0x6C9650 is already matched),
//   `FIDIV [EDI+0x310]` (TotalStorage), the building list `[EDI+0x6C]` with
//   its count `[EDI+0x78]`, the building's `[ECX+0x81]` InLimbo and
//   `[ECX+0x520]` Type, the type's `[EDX+0x16A8]` flag, and the building's
//   slot `[EAX+0x124]` (Mark) called with 2. Names from YRpp
//   (names only).
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_SILOS_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_SILOS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "storage_class.h"   // StorageClass (0x10), GetTotalAmount @0x6C9650

// BuildingTypeClass — only the flag at +0x16A8 is read.
struct BuildingType_004F9970
{
    char          _pad000[0x16A8];    // +0x0000
    unsigned char At_16A8;            // +0x16A8
};
GG_STATIC_ASSERT(offsetof(BuildingType_004F9970, At_16A8) == 0x16A8);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct BuildingVtbl_004F9970;

struct Building_004F9970
{
    char                    _pad000[0x81];            // +0x0000
    unsigned char           InLimbo;                  // +0x0081
    char                    _pad082[0x520 - 0x82];    // +0x0082
    BuildingType_004F9970*  Type;                     // +0x0520
};
GG_STATIC_ASSERT(offsetof(Building_004F9970, InLimbo) == 0x81);
GG_STATIC_ASSERT(offsetof(Building_004F9970, Type)    == 0x520);

typedef int (Building_004F9970::*Fn124_Silos)(int mark);

struct BuildingVtbl_004F9970
{
    char        _pad000[0x124];    // +0x0000
    Fn124_Silos Mark;              // +0x0124
};
GG_STATIC_ASSERT(offsetof(BuildingVtbl_004F9970, Mark) == 0x124);

// HouseClass — the owned-building vector head at 0x68 (Items @0x6C,
// Count @0x78), the tiberium store and the storage cap.
struct House_004F9970
{
    char                  _pad000[0x6C];            // +0x0000
    Building_004F9970**   BuildingItems;            // +0x006C
    char                  _pad070[0x8];             // +0x0070
    int                   unknown_78;            // +0x0078
    char                  _pad07C[0x2FC - 0x7C];    // +0x007C
    StorageClass          OwnedTiberium;            // +0x02FC
    int                   Balance;                  // +0x030C
    int                   TotalStorage;             // +0x0310

    // FUNCTION: GAMEMD 0x4F9970
    void UpdateAllSilos(int prevStorage, int prevTotalStorage);
};
GG_STATIC_ASSERT(offsetof(House_004F9970, BuildingItems) == 0x6C);
GG_STATIC_ASSERT(offsetof(House_004F9970, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(House_004F9970, OwnedTiberium) == 0x2FC);
GG_STATIC_ASSERT(offsetof(House_004F9970, TotalStorage)  == 0x310);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_SILOS_METHODS_H
