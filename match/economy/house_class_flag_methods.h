// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4FC060), cross-checked against
//   YRpp (every offset reconfirmed
//   numerically from the disassembly below).
//
// HouseClass-flag — the flag-capture handler:
//   PickedUpFlag   a unit picks up this house's flag (CTF logic)
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/unit_class.h"   // the flag carrier: InLimbo @0x81, FlagAttach 0x740DF0
#include "../_layout/house_class.h"

typedef unsigned long DWORD;

// ---------------------------------------------------------------------------
// HouseTypeClass shim — only the index @0xB8 is touched.
//
// Confirmed from 0x4FC060: MOV EDX,[ESI+0x34] (HouseClass::Type), then
// MOV EAX,[EDX+0xB8] — the value handed to the carrier as its owner/colour
// index. Full AbstractTypeClass-derived layout is P2.
// ---------------------------------------------------------------------------
class HouseTypeClass
{
public:
    char _layout_pad_P2[0xB8];   // +0x0000
    int  ColorSchemeIndex_B8;    // +0x00B8  (MOV EAX,[EDX+0xB8])
};
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ColorSchemeIndex_B8) == 0xB8);

// ---------------------------------------------------------------------------
// HouseClass — only the members PickedUpFlag touches are modelled; the full
// AbstractClass-derived layout is P2. Each offset is asserted and confirmed
// numerically from the disassembly.
//   Type        @0x34    HouseTypeClass*  (MOV EDX,[ESI+0x34])
//   OurFlagCarrier  @0x53DC  UnitClass*       (MOV/[ESI+0x53DC] read & write)
// ---------------------------------------------------------------------------

GG_STATIC_ASSERT(offsetof(HouseClass, Type)       == 0x34);
GG_STATIC_ASSERT(offsetof(HouseClass, OurFlagCarrier) == 0x53DC);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_METHODS_H
