// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x53AB50. The three bindings were taken from YRpp
//   and reconfirmed against the disassembly:
//   0x53AB50 = LightningStorm::Init, the tail-position callee 0x53C280 =
//   ScenarioClass::UpdateLighting, and the pointer global 0x00A83D4C =
//   HouseClass::CurrentPlayer.
#ifndef GG_MATCH_COMBAT_LIGHTNING_STORM_METHODS_H
#define GG_MATCH_COMBAT_LIGHTNING_STORM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// HouseClass — only the flag Init raises is modelled. It keeps a placeholder
// name: the byte's offset is fixed by `MOV byte ptr [EAX+0x5779],1`, but not its
// meaning. It sits one byte below SpySatActive @0x577A (see
// match/economy/house_class_accessor_methods.h), so it is in the same
// lightning/radar flag cluster.
class HouseClass
{
public:
    char _pad00[0x5779];   // +0x0000
    bool unknown_5779;     // +0x5779
};
GG_STATIC_ASSERT(offsetof(HouseClass, unknown_5779) == 0x5779);

// GLOBAL: GAMEMD 0x00A83D4C — HouseClass::CurrentPlayer, the house driving
// this machine.
extern HouseClass* CurrentPlayer;

struct ScenarioClass
{
    static void UpdateLighting();   // GAMEMD 0x53C280 (declared; reloc)
};

struct LightningStorm
{
    static void Init();   // GAMEMD 0x53AB50
};

#endif  // GG_MATCH_COMBAT_LIGHTNING_STORM_METHODS_H
