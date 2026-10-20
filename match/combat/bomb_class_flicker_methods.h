// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x438A00: `CMP [ECX+0x30],1` and `MOV EDX,[ECX+0x34]`.
//   Name and member identities cross-checked against YRpp BombClass.h
//   (consult-only, no LICENSE); the AbstractClass base size of 0x24 is the
//   committed value in match/_layout/abstract_class.h, which places YRpp's
//   DeathBomb at +0x30 and PlantingFrame at +0x34 exactly where retail reads.
//
// BombClass::GetCurrentFlickerFrame @0x438A00 — which frame of the ticking-bomb
// animation to draw.
#ifndef GG_MATCH_COMBAT_BOMB_CLASS_FLICKER_METHODS_H
#define GG_MATCH_COMBAT_BOMB_CLASS_FLICKER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter (`MOV EDI,[0xA8ED84]`).
extern int CurrentFrame;

// RulesClass singleton pointer @0x8871E0. Two timing fields are read here and
// neither is bound by YRpp at a computable offset, so both keep placeholder
// names: +0xFD0 is divided by three to give the tick period, +0xFD8 is the
// flicker half-period. Their roles are clear from the arithmetic; their
// [General] INI keys are not, so they are not guessed at.
struct RulesClass
{
    char _pad000[0xFD0];   // +0x0000
    int  field_FD0;        // +0x0FD0
    char _padFD4[0x4];     // +0x0FD4
    int  field_FD8;        // +0x0FD8
};
GG_STATIC_ASSERT(offsetof(RulesClass, field_FD0) == 0xFD0);
GG_STATIC_ASSERT(offsetof(RulesClass, field_FD8) == 0xFD8);
extern RulesClass* Rules;   // GLOBAL: GAMEMD 0x8871E0

// ---------------------------------------------------------------------------
// BombClass — AbstractClass spine (sizeof 0x24) plus the bomb's own fields.
// Only the two this method reads are modelled; the rest are P2.
// ---------------------------------------------------------------------------
struct BombClass
{
    char _pad00[0x30];      // +0x0000  AbstractClass 0x24, then Owner/OwnerHouse/Target
    int  DeathBomb;         // +0x0030  BOOL
    int  PlantingFrame;     // +0x0034

    // FUNCTION: GAMEMD 0x438A00
    int GetCurrentFlickerFrame() const;
};
GG_STATIC_ASSERT(offsetof(BombClass, DeathBomb) == 0x30);
GG_STATIC_ASSERT(offsetof(BombClass, PlantingFrame) == 0x34);

#endif  // GG_MATCH_COMBAT_BOMB_CLASS_FLICKER_METHODS_H
