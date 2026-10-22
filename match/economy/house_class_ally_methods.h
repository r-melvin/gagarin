// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4F9A10-0x4F9ADE), cross-checked
//   against YRpp (reconfirmed here).
//
// HouseClass::IsAlliedWith overload trio. Only the two members these methods
// touch are modelled (ArrayIndex@0x30, Allies bitfield dword@0x5788). Other
// fields remain outside this sparse view. The object overload uses the shared
// explicit-vptr ObjectClass layout and the confirmed +0x3C owning-house slot.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/object_class.h"

// ---------------------------------------------------------------------------
// HouseClass — only ArrayIndex (+0x30) and the Allies bitfield dword (+0x5788)
// are touched by the three IsAlliedWith overloads. The rest of the (huge)
// HouseClass body is opaque padding here; full layout is P2.
// ---------------------------------------------------------------------------
class HouseClass
{
public:
    bool IsAlliedWith(int idxHouse) const;             // GAMEMD 0x4F9A10 __thiscall
    bool IsAlliedWith(HouseClass const* pHouse) const; // GAMEMD 0x4F9A50 __thiscall
    bool IsAlliedWith(ObjectClass const* pObject) const; // GAMEMD 0x4F9A90 __thiscall

    char unknown_00[0x30];     // [0x00..0x2F] opaque base — P2
    int  ArrayIndex;      // +0x30
    char unknown_34[0x5788 - (0x30 + 4)]; // [0x34..0x5787] opaque — P2
    int  Allies;          // +0x5788  (IndexBitfield dword 0; one bit per house)
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(HouseClass, Allies)     == 0x5788);
#endif

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_METHODS_H
