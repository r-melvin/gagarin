// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x74D670.

#include <stdlib.h>
#include "veinhole_monster_eligible_methods.h"
#include "veinhole_monster_methods.h"

// FUNCTION: GAMEMD 0x74EF00
// Retained in its original address-named helper view because the source return
// type of RulesClass::VeinholeTypeClass at +0xFF4 remains unresolved.
void* VeinholeMonsterView_0074CDF0::GetTerrainType()
{
    return RulesInstance->VeinholeTerrainType;
}
