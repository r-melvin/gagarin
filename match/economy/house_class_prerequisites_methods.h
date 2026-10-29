// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x505360: the techno type's Prerequisite list
//   `[ECX+0x63C]` (Items) / `[EAX+0x648]` (Count), the owned-building
//   vector's Items `[EBP+0x4]`, BuildingTypeClass::Array.Items at 0xA83C6C,
//   and the six generic prerequisite lists on RulesClass 0x8871E0 reached
//   through a jump table on the negative index (-1 +0x8C8, -2 +0x938,
//   -3 +0x900, -4 +0xA34, -5 +0x91C, -6 +0x8E4), each read through Count
//   +0x10 and vtable slot +0x18 (one pushed index). `this` (ECX) is unused;
//   YRpp still models the method as a member. Names cross-checked against
//   YRpp.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_PREREQUISITES_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_PREREQUISITES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/building_type_class_layout.h"

// GLOBAL: GAMEMD 0xA83C6C — BuildingTypeClass::Array.Items.
extern BuildingTypeClass** DAT_00A83C6C;

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_PREREQUISITES_METHODS_H
