// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Options.CPP. The name is the source-file string at 0x833370
//   in retail gamemd.exe v1.001, passed by the assert at 0x5fbb56 inside this object's
//   code range (0x5fa0d0-0x5fc16f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.

#include "../core/empty_function_family_methods.h"

#include "../core/trivial_tu167_methods.h"

#include "game_options_class_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EF378
extern const double DAT_007EF378;
// GLOBAL: GAMEMD 0xAC14B0
extern double DAT_00AC14B0;
// GLOBAL: GAMEMD 0xAC14E8
extern double DAT_00AC14E8;
// GLOBAL: GAMEMD 0xAC14F0
extern int DAT_00AC14F0;
// GLOBAL: GAMEMD 0xAC14F4
extern int DAT_00AC14F4;
// GLOBAL: GAMEMD 0xAC14F8
extern int DAT_00AC14F8;
// GLOBAL: GAMEMD 0xAC1500
extern double DAT_00AC1500;

// FUNCTION: GAMEMD 0x5FA100
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005FA100()
{
    DAT_00AC1500 = DAT_00AC14B0 / DAT_007EF378;
}

// FUNCTION: GAMEMD 0x5FA120
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005FA120()
{
    DAT_00AC14E8 = DAT_007E1718 / DAT_00AC1500;
}

// FUNCTION: GAMEMD 0x5FA2A0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_005FA2A0()
{
    DAT_00AC14F8 = 0;
    DAT_00AC14F0 = 0x80;
    DAT_00AC14F4 = 0x80;
}

// FUNCTION: GAMEMD 0x005FA430
void FUN_005FA430()
{
}

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

// FUNCTION: GAMEMD 0x5FBF70
// Member getter (dword).
int Obj_005FBF70::FUN_005FBF70() const
{
    return unknown_0C;
}
