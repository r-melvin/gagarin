// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly @0x42F380 and @0x4F6E70),
//   cross-checked against YRpp (every
//   offset reconfirmed below against the user's binary).
//
// HouseClass economy/base helpers:
//   BaseClass::FailedToPlaceNode  (operates on a BaseNodeClass* argument)
//   HouseClass::GetStoragePercentage
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_STORAGE_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_STORAGE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "storage_class.h"   // StorageClass (0x10), GetTotalAmount @0x6C9650

#include "../_layout/base_node_class.h"

// ---------------------------------------------------------------------------
// BaseClass — holds a player's AI base. FailedToPlaceNode is a __thiscall
// member whose body ignores `this` and works solely through its Node argument
// (RET 0x4 cleans the single stack arg). No members of BaseClass are touched,
// so it is modelled empty.
// ---------------------------------------------------------------------------
class BaseClass
{
public:
    int FailedToPlaceNode(BaseNodeClass* Node);   // GAMEMD 0x42F380 __thiscall
};

// ---------------------------------------------------------------------------
// HouseClass (partial) — only the members GetStoragePercentage touches.
// From 0x4F6E70: `LEA EDI,[ESI+0x2fc]` => &OwnedTiberium (StorageClass, 0x10),
// `FIDIV dword[ESI+0x310]` => int TotalStorage. Balance (int@0x30C) sits
// between them per YRpp; modelled for spacing. Base padded to 0x2FC (P2).
// ---------------------------------------------------------------------------
class HouseClass
{
public:
    char         _pad0[0x2FC];   // AbstractClass + HouseClass head (+0x00..)
    StorageClass OwnedTiberium;  // +0x2FC
    int          Balance;        // +0x30C
    int          TotalStorage;   // +0x310

    double GetStoragePercentage();   // GAMEMD 0x4F6E70 __thiscall
};

GG_STATIC_ASSERT(offsetof(HouseClass, OwnedTiberium) == 0x2FC);
GG_STATIC_ASSERT(offsetof(HouseClass, TotalStorage) == 0x310);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_STORAGE_H
