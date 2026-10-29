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
#include "../_layout/bomb_class.h"

// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter (`MOV EDI,[0xA8ED84]`).
#include "../core/frame_counter.h"

extern RulesClass* Rules;   // GLOBAL: GAMEMD 0x8871E0


#endif  // GG_MATCH_COMBAT_BOMB_CLASS_FLICKER_METHODS_H
