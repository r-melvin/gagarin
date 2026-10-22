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
    int GameSpeed;          // +0x00
    int unknown_04;         // +0x04 the slider 0x50F of the game-controls dialog (0x4E1DE0)
    int unknown_08;         // +0x08
    int unknown_0C;         // +0x0C
    int unknown_10;         // +0x10 the slider 0x52A (0x4E1DE0)
    int unknown_14;         // +0x14
    int unknown_18;         // +0x18 the slider 0x52B (0x4E1DE0)
    unsigned char unknown_1C[2];   // +0x1C
    bool unknown_1E;        // +0x1E check box 0x601
    bool unknown_1F;        // +0x1F check box 0x604
    bool unknown_20;        // +0x20 check box 0x602

    // FUNCTION: GAMEMD 0x5FA350 (decl; reloc)
    GameOptionsClass();
    int GetAnimSpeed(int rate);   // GAMEMD 0x5FB2E0 __thiscall
    // FUNCTION: GAMEMD 0x5FAD10 (decl; reloc)
    void FUN_005FAD10();
};
GG_STATIC_ASSERT(offsetof(GameOptionsClass, GameSpeed) == 0x00);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, unknown_1E) == 0x1E);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, unknown_20) == 0x20);

#endif  // GG_MATCH_UI_GAME_OPTIONS_CLASS_METHODS_H
