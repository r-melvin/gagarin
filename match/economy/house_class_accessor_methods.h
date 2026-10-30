// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Every offset below was read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI, from the member-access instructions in the
//   seven functions this header serves (addresses in the comments). Member and
//   method *names* are cross-checked against YRpp
//   (`IsHumanPlayer`/`IsInPlayerControl`); each is confirmed by the byte
//   flag the method reads in the disassembly cited beside it.
//
// HouseClass accessor leaves — seven independent small methods spanning the
// money, alliance, control, shroud, self-heal, and powered-centre surfaces.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_ACCESSOR_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_ACCESSOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"
#include "../_layout/house_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/session_class.h"

class HouseClass;
class TechnoTypeClass;


// ---------------------------------------------------------------------------
// HouseClass — only the members these seven methods touch are modelled; the
// full AbstractClass-derived layout is P2. Offsets confirmed numerically:
//   InfantrySelfHeal    @0x0164  int   (IMUL [ECX+0x164]  @0x50D9E0)
//   UnitsSelfHeal       @0x0168  int   (IMUL [ECX+0x168]  @0x50D9F0)
//   IsHumanPlayer       @0x01EC  bool  (MOV AL,[ECX+0x1EC] @0x50B730)
//   IsInPlayerControl   @0x01ED  bool  (MOV AL,[ECX+0x1ED] @0x50B730)
//   PoweredUnitCenters  @0x02D8  int   (TEST/SETG [ECX+0x2D8] @0x50E1B0)
//   Balance             @0x030C  int   (ADD [ECX+0x30C]   @0x4F9950)
//   SpySatActive        @0x577A  bool  (MOV AL,[ECX+0x577A] @0x50BD10)
// ---------------------------------------------------------------------------


GG_STATIC_ASSERT(offsetof(HouseClass, InfantrySelfHeal)   == 0x164);
GG_STATIC_ASSERT(offsetof(HouseClass, UnitsSelfHeal)      == 0x168);
GG_STATIC_ASSERT(offsetof(HouseClass, IsHumanPlayer)      == 0x1EC);
GG_STATIC_ASSERT(offsetof(HouseClass, IsInPlayerControl)  == 0x1ED);
GG_STATIC_ASSERT(offsetof(HouseClass, PoweredUnitCenters) == 0x2D8);
GG_STATIC_ASSERT(offsetof(HouseClass, Balance)            == 0x30C);
GG_STATIC_ASSERT(offsetof(HouseClass, SpySatActive)       == 0x577A);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_ACCESSOR_METHODS_H
