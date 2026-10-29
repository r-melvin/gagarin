// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x509CD0: `[ESI+0x5600]` compared with -1 and otherwise
//   indexing the Items pointer at 0xA8022C (`MOV ECX,[ECX+EAX*4]`), the
//   CellStruct at `[ESI+0x54F0]` compared word-wise with the sentinel at
//   0xA8EF98/0xA8EF9A, `[ESI+0x54EC]` compared with 1 and otherwise passed
//   to 0x50D170 (PickTargetByType) with a stack out buffer; on the chosen
//   house `[ECX+0x5494]` compared word-wise with the sentinel and either it
//   or `[ECX+0x5490]` copied into the cell local; the map object 0x87F7E8
//   receiving CALL 0x56DC20 (NearByLocation) with fifteen pushed arguments
//   (out buffer, &cell, 0, -1, 0, 0, 5, 5, 0, 0, 0, 1, &zero cell, 0, 0)
//   whose result gets `ADD word ptr,2` on both halves; the super-weapon
//   vector at `[ESI+0x254]` whose slot `[EAX+0x10]` (FindItemIndex) receives
//   the *address* of the parameter slot, and CALL 0x4FAE50 (Fire_SW) taking
//   the index and the cell by pointer. Names are YRpp's HouseClass::
//   Fire_ParaDrop / GetBaseCenter / BaseSpawnCell / BaseCenter /
//   PreferredTargetType / PreferredTargetCell / EnemyHouseIndex /
//   PickTargetByType / Fire_SW and MapClass::NearByLocation (names only).
#ifndef GG_MATCH_AI_HOUSE_CLASS_PARADROP_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_PARADROP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"

// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern HouseClass** DAT_00A8022C;

// MapClass — only the nearby-cell search is reached.
struct Map_00509CD0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x56DC20 (decl; reloc) — MapClass::NearByLocation.
    Cell* NearByLocation(Cell* out, const Cell& position,
                         int speedType, int a4, int movementZone, bool alt,
                         int spaceSizeX, int spaceSizeY, bool a9, bool a10,
                         bool a11, bool ignoreOccupied,
                         const Cell& closeTo, bool a14, bool buildable);
};
// GLOBAL: GAMEMD 0x87F7E8 — the map instance.
extern Map_00509CD0 MapInstance_00509CD0;

#endif  // GG_MATCH_AI_HOUSE_CLASS_PARADROP_METHODS_H
