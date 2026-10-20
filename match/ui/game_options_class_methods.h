// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, the table address and the member offset read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x5FB2E0. Class and member
//   names cross-checked against YRpp GameOptionsClass.h (consult-only, no
//   LICENSE), whose first member is `int GameSpeed` — the `MOV ECX,[ECX]` the
//   retail body opens with.
#ifndef GG_MATCH_UI_GAME_OPTIONS_CLASS_METHODS_H
#define GG_MATCH_UI_GAME_OPTIONS_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x00832CEC — the animation-rate lookup, indexed
// [rate * 8 + GameSpeed] (retail folds both terms into one LEA before scaling
// by 4). Eight game-speed columns per rate row; only rates 1..4 are tabulated.
extern int AnimSpeedTable[];

struct GameOptionsClass
{
    int GameSpeed;    // +0x00

    int GetAnimSpeed(int rate);   // GAMEMD 0x5FB2E0 __thiscall
};
GG_STATIC_ASSERT(offsetof(GameOptionsClass, GameSpeed) == 0x00);

#endif  // GG_MATCH_UI_GAME_OPTIONS_CLASS_METHODS_H
