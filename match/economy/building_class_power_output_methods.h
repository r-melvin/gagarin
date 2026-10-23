// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and the vtable slot read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x44E7B0: `[ESI+0x520]`
//   (Type), `[EAX+0xEE0]` / `[EAX+0xEE8]` off it (PowerBonus /
//   ExtraPowerBonus), the two type flag bytes `[EAX+0x16AE]` / `[EAX+0x16AF]`,
//   `[ESI+0x668]` (HasExtraPowerBonus), `[ESI+0x114]` (Passengers count),
//   `[ESI+0x702]` (UpgradeLevel), `LEA ECX,[ESI+0x5EC]` with a 3-count
//   (Upgrades[3]), `[ESI+0x660]` (HasPower), and the virtual `CALL
//   [EDX+0x1D4]` (ObjectClass::IsBeingWarpedOut, the
//   techno vtable slot at +0x1D4). Names for the method, the
//   members and the health-ratio callee 0x5F5C60 (ObjectClass::
//   GetHealthPercentage, between AttachTrigger 0x5F5B50 and
//   SetHealthPercentage 0x5F5C80 in match/_layout/object_class.h) are
//   YRpp's; every offset is reconfirmed here. The two type
//   flag bytes keep placeholder names: YRpp's adjacent UnitAbsorb /
//   InfantryAbsorb pair is the likely identity but their offsets were not
//   re-derived.
//
// BuildingClass::GetPowerOutput -- the structure's power production.
// Sister of GetPowerDrain (0x44E880, match/economy/building_class_power_methods)
// but written in C++ rather than a naked body.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_OUTPUT_METHODS_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_OUTPUT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_OUTPUT_METHODS_H
