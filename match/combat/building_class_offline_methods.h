// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x452360: on the building the bytes `[ESI+0x660]`
//   (cleared) and `[ESI+0x80]` (set), the owner at `[ESI+0x21C]` and the type
//   at `[ESI+0x520]`; on the type `[EAX+0xEE4]` (int, compared > 0), the
//   bytes `[EAX+0x1573]` and `[EAX+0xCCE]`, and `[EAX+0xEB8]` (int, pushed);
//   on the owner the bytes `[ECX+0x5778]`, `[EDX+0x5779]` and `[ECX+0x1FC]`.
//   Callees: 0x452480 (BuildingClass::DisableStuff, __thiscall), 0x50B6F0
//   (HouseClass::IsControlledByCurrentPlayer, __thiscall, byte result),
//   0x752700 (VoxClass::Play, __fastcall: ECX=name, EDX=-1, pushed -1) and
//   0x509140 (HouseClass::Update_FactoriesQueues, __thiscall, three pushed
//   args). Names cross-checked against YRpp BuildingClass::GoOffline /
//   and the committed spines
//   match/_layout/object_class.h (NeedsRedraw @0x80), techno_class.h (Owner
//   @0x21C), techno_type_class.h (Naval @0xCCE), building_type_class_layout.h
//   (Factory @0xEB8, PowerDrain @0xEE4) and match/economy/
//   house_class_power_methods.h (the two @0x5778/@0x5779 bytes) — re-derived.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_OFFLINE_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_OFFLINE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"
#include "../_layout/house_class.h"

struct VoxClass_00452360
{
    // FUNCTION: GAMEMD 0x752700 (decl; reloc) — VoxClass::Play.
    static void Play(const char* name, int a, int b);
};

// STRING: GAMEMD 0x819108 — "EVA_BuildingOffLine".
extern const char EvaBuildingOffLine[];

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_OFFLINE_METHODS_H
