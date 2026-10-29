// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x501540: on the house `[EDI+0x30]` / `[ESI+0x30]`
//   (ArrayIndex), `[ESI+0x5788]` (Allies bitfield dword), `[EDI+0x34]`
//   (Type), `[ESI+0x1F5]` (Defeated byte); on the house type `[ECX+0xBC]`
//   (ArrayIndex2) and `[ECX+0x1A6]` (MultiplayPassive byte); the globals
//   0xA8022C / 0xA80238 (HouseClass::Array Items / Count), 0xA8B238
//   (SessionClass GameMode) and 0xA8E7AC (ScenarioInit); the "Civilian"
//   house-type index lookup 0x6A46D0 with the name in ECX. Names cross-checked
//   against YRpp.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_CAN_ALLY_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_CAN_ALLY_METHODS_H

#include <stddef.h>
#include "../_layout/session_class.h"
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/house_class_allied_inline.h"

// The house-type name whose index the civilian test compares against; the
// lookup takes the name in ECX.
struct HouseTypeName_00501540
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x6A46D0 (decl; reloc) — HouseTypeClass::FindIndex.
    int FindIndex();
};
// STRING: GAMEMD 0x818164 — "Civilian".
extern HouseTypeName_00501540 DAT_00818164;

// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern HouseClass** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238 — HouseClass::Array.Count.
extern int DAT_00A80238;
// GLOBAL: GAMEMD 0xA8E7AC — Unsorted::ScenarioInit.
extern int DAT_00A8E7AC;

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_CAN_ALLY_METHODS_H
