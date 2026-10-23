// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x452480: on the building `[EDI+0x614]` (light
//   source), the bytes `[EDI+0x6EA]`, `[EDI+0x6EB]`, `[EDI+0x6EC]`,
//   `[EDI+0x269]`, `[EDI+0x80]`, the type at `[EDI+0x520]` and the 21
//   animation pointers from `[EDI+0x55C]`; on the type the bytes
//   `[EAX+0x16C7]`, `[EAX+0x1707]`, `[EAX+0xCD1]`, `[EAX+0x16BE]` and the
//   0x44-byte animation records from `[ECX+0xF8C]` (21 of them: the loop
//   stops at 0x594). Slot +0x418 is a zero-argument virtual. Names cross-
//   checked against YRpp: DisableStuff,
//   LightSource, CloakRadius, Type->CloakGenerator/CloakRadiusInCells/
//   GapGenerator; every offset reconfirmed here.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_DISABLE_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_DISABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"
#include "../_layout/anim_class.h"

// LightSourceClass — only the switch called here.
class LightSourceClass
{
public:
    // FUNCTION: GAMEMD 0x554A80 (decl; reloc) — switch the light source.
    void FUN_00554A80(char on);
};

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_DISABLE_METHODS_H
