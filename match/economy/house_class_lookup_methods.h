// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets + global addresses derived from the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI (member-access disassembly), cross-checked against
//   YRpp
//   (every offset/address reconfirmed numerically from the disasm).
//
// HouseClass lookup/query leaves:
//   0x502D30  HouseClass::FindByCountryIndex      (static __fastcall)
//   0x50B6F0  HouseClass::IsControlledByCurrentPlayer (__thiscall)
//
// Only the members/globals these two methods actually touch are modelled here;
// the full HouseClass / HouseTypeClass / DynamicVectorClass layouts are P2 work.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_LOOKUP_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_LOOKUP_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"

// ---------------------------------------------------------------------------
// HouseTypeClass — only ArrayIndex2 @0xB8 is touched (the loop key in
// 0x502D30: `CMP [EBX+0xB8], ECX`, where EBX = house->Type).
// AbstractTypeClass base = 0x98; FixedString<25> ParentCountry @0x98 + 3 align,
// int ArrayIndex @0xB4, int ArrayIndex2 @0xB8 (YRpp).
// ---------------------------------------------------------------------------
class HouseTypeClass
{
public:
    char _pad_base[0xB8];          // AbstractTypeClass + ParentCountry/ArrayIndex (P2)
    int  ArrayIndex2;              // +0xB8
};
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex2) == 0xB8);

// ---------------------------------------------------------------------------
// HouseClass — touched members:
//   Type             @0x34  (HouseTypeClass*; `MOV EBX,[EAX+0x34]` in 0x502D30)
//   IsHumanPlayer    @0x1EC (bool;  `MOV AL,[ECX+0x1EC]` in 0x50B6F0)
//   IsInPlayerControl@0x1ED (bool;  `MOV AL,[ECX+0x1ED]` in 0x50B6F0)
// ---------------------------------------------------------------------------

GG_STATIC_ASSERT(offsetof(HouseClass, Type) == 0x34);
GG_STATIC_ASSERT(offsetof(HouseClass, IsHumanPlayer) == 0x1EC);
GG_STATIC_ASSERT(offsetof(HouseClass, IsInPlayerControl) == 0x1ED);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_LOOKUP_METHODS_H
