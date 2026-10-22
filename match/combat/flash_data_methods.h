// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4CC770. Names cross-checked against YRpp
//   `struct FlashData`.
//
// FlashData — the damage/selection flash timer embedded in TechnoClass. Note it
// has no vtable: retail reads `[ECX]` as the countdown itself, which is what
// pins DurationRemaining to +0x00.
#ifndef GG_MATCH_COMBAT_FLASH_DATA_METHODS_H
#define GG_MATCH_COMBAT_FLASH_DATA_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct FlashData
{
    int  DurationRemaining;   // +0x00
    bool FlashingNow;         // +0x04

    bool Update();            // GAMEMD 0x4CC770
};

GG_STATIC_ASSERT(offsetof(FlashData, DurationRemaining) == 0x00);
GG_STATIC_ASSERT(offsetof(FlashData, FlashingNow)       == 0x04);

#endif  // GG_MATCH_COMBAT_FLASH_DATA_METHODS_H
