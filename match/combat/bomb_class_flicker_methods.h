// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x438A00: `CMP [ECX+0x30],1` and `MOV EDX,[ECX+0x34]`.
//   Name and member identities cross-checked against YRpp
//   the AbstractClass base size of 0x24 is the
//   committed value in match/_layout/abstract_class.h, which places YRpp's
//   DeathBomb at +0x30 and PlantingFrame at +0x34 exactly where retail reads.
//
// BombClass::GetCurrentFlickerFrame @0x438A00 — which frame of the ticking-bomb
// animation to draw.
#ifndef GG_MATCH_COMBAT_BOMB_CLASS_FLICKER_METHODS_H
#define GG_MATCH_COMBAT_BOMB_CLASS_FLICKER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/rules_class.h"

// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter (`MOV EDI,[0xA8ED84]`).
#include "../core/frame_counter.h"

extern RulesClass* Rules;   // GLOBAL: GAMEMD 0x8871E0

// ---------------------------------------------------------------------------
// BombClass — AbstractClass spine (sizeof 0x24) plus the bomb's own fields.
// Only the two this method reads are modelled; the rest are P2.
// ---------------------------------------------------------------------------
class BombClass
{
public:
    char _pad00[0x30];      // +0x0000  AbstractClass 0x24, then Owner/OwnerHouse/Target
    int  DeathBomb;         // +0x0030  BOOL
    int  PlantingFrame;     // +0x0034

    // FUNCTION: GAMEMD 0x438A00
    int GetCurrentFlickerFrame() const;
};
GG_STATIC_ASSERT(offsetof(BombClass, DeathBomb) == 0x30);
GG_STATIC_ASSERT(offsetof(BombClass, PlantingFrame) == 0x34);

#endif  // GG_MATCH_COMBAT_BOMB_CLASS_FLICKER_METHODS_H
