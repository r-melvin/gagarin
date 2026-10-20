// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5FB2E0.

#include "game_options_class_methods.h"

// FUNCTION: GAMEMD 0x5FB2E0  GameOptionsClass::GetAnimSpeed (__thiscall, ret 0x4)
// Rates 1..4 come out of the tuned table; anything faster is computed instead,
// as eight ticks divided by the game speed (plus one, so speed 0 is safe). Rate
// 0 means "no animation" and short-circuits.
//
// The original assigns back into the `rate` parameter and falls out of the
// bottom, which is why the rate-0 exit shares the trailing RET with the
// computed path instead of getting its own. A separate `result` local scores
// 6.7% and an early `return 0;` 13.3%.
//
// MATCHED (100%, 14/14). The last two instructions were the index register:
// retail computes the table index into EDX (`LEA EDX,[ECX+EAX*8]`) and cl put
// it in EAX. It is not the subscript that chooses this but the *scope of the
// game-speed local*. Hoisting `GameSpeed` into a named `speed` above the
// rate<5 branch makes it live across both arms, so cl recycles EAX for the
// address; reading the member inline in the table path and naming `speed`
// only inside the divide path, where the `+1` needs it, gives retail's EDX
// exactly. Eight other spellings all sat at 85.7%: a named index, a named row
// pointer, a named element pointer, the addition written speed-first, the
// result assigned back through `rate`, a two-armed assignment with one
// fallthrough return, a 2D row cast, a shift instead of the multiply, an
// unsigned index, char-scaled address arithmetic, and volatile reads of both
// the member and the table.
int GameOptionsClass::GetAnimSpeed(int rate)
{
    if (rate != 0) {
        if (rate < 5)
            return AnimSpeedTable[rate * 8 + GameSpeed];

        int speed = GameSpeed;
        rate = (rate * 8) / (speed + 1);
    }
    return rate;
}
