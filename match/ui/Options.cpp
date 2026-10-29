// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
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

// GLOBAL: GAMEMD 0x7EF378
extern const double DAT_007EF378;
// GLOBAL: GAMEMD 0xAC14B0
extern double DAT_00AC14B0;
// GLOBAL: GAMEMD 0xAC14F0
extern int DAT_00AC14F0;
// GLOBAL: GAMEMD 0xAC14F4
extern int DAT_00AC14F4;
// GLOBAL: GAMEMD 0xAC14F8
extern int DAT_00AC14F8;

// SYNTHETIC: GAMEMD 0x005FA100
// dynamic initializer for DAT_00AC1500
// GLOBAL: GAMEMD 0x00AC1500
double DAT_00AC1500 = DAT_00AC14B0 / DAT_007EF378;

// SYNTHETIC: GAMEMD 0x005FA120
// dynamic initializer for DAT_00AC14E8
// GLOBAL: GAMEMD 0x00AC14E8
double DAT_00AC14E8 = 1.0 / DAT_00AC1500;

GG_STATIC_ASSERT(sizeof(DAT_00AC1500) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00AC14E8) == 8);

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

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log (format, args...).
void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x407150 (decl; reloc) -- set a channel's volume (fastcall: channel, value).
struct Obj_00401000;
void __fastcall FUN_00407150(Obj_00401000* channel, int value);

// FUNCTION: GAMEMD 0x752AB0 (decl; reloc) -- set the global voice level.
void __fastcall FUN_00752AB0(int level);

// Score jukebox object at 0xA83D10; its level setter is 0x721290.
struct ScoreJukebox_00721290
{
    // FUNCTION: GAMEMD 0x721290 (decl; reloc)
    void FUN_00721290(int level);
};

// GLOBAL: GAMEMD 0xA83D10
extern ScoreJukebox_00721290 DAT_00A83D10;
// GLOBAL: GAMEMD 0x87E740 -- voice channel.
extern Obj_00401000* DAT_0087E740;
// GLOBAL: GAMEMD 0x87E744 -- score channel.
extern Obj_00401000* DAT_0087E744;
// GLOBAL: GAMEMD 0x87E748 -- sound channel.
extern Obj_00401000* DAT_0087E748;

// GLOBAL: GAMEMD 0x7E1718 -- 1.0.
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EAA50 -- level scale (double).
extern const double DAT_007EAA50;

// STRING: GAMEMD 0x832F9C -- "ScoreVolume = %f\n"
extern char STR_00832F9C[];
// STRING: GAMEMD 0x832FB0 -- "SoundVolume = %f\n"
extern char STR_00832FB0[];
// STRING: GAMEMD 0x832FC4 -- "VoiceVolume = %f\n"
extern char STR_00832FC4[];

// Rules view: the sound index played as feedback when a volume changes.
struct OptionsRulesView_005FA510
{
    char unknown_00[0x710];
    int  VolumeFeedback;   // +0x710
};
GG_STATIC_ASSERT(offsetof(OptionsRulesView_005FA510, VolumeFeedback) == 0x710);
// GLOBAL: GAMEMD 0x8871E0 -- rules.
extern OptionsRulesView_005FA510* DAT_008871E0;

// VocClass::PlayGlobal 0x750920, called with a sound index, pan and volume.
#include "../audio/voc_class_play_global_methods.h"

// FUNCTION: GAMEMD 0x5FA4A0
// Clamp and store the score volume, push it to the score channel and the jukebox, log it.
void GameOptionsClass::SetScoreVolume(float volume, bool unused)
{
    ScoreVolume = volume < DAT_007E1718 ? volume : DAT_007E1718;
    FUN_00407150(DAT_0087E744, (int)(ScoreVolume * 16384.0f));
    DAT_00A83D10.FUN_00721290((int)(ScoreVolume * DAT_007EAA50));
    FUN_004068E0(STR_00832F9C, (double)ScoreVolume);
}

// FUNCTION: GAMEMD 0x5FA510
// Clamp and store the sound volume, push it to the sound channel, play the feedback sample, log it.
void GameOptionsClass::SetSoundVolume(float volume, bool playSample)
{
    SoundVolume = volume < DAT_007E1718 ? volume : DAT_007E1718;
    FUN_00407150(DAT_0087E748, (int)(SoundVolume * 16384.0f));
    if (playSample)
        VocClass::PlayGlobal(DAT_008871E0->VolumeFeedback, 1.0f, 0x2000, 0);
    FUN_004068E0(STR_00832FB0, (double)SoundVolume);
}

// FUNCTION: GAMEMD 0x5FA590
// Clamp and store the voice volume, push it to the voice level and channel, play the feedback sample, log it.
void GameOptionsClass::SetVoiceVolume(float volume, bool playSample)
{
    VoiceVolume = volume < DAT_007E1718 ? volume : DAT_007E1718;
    FUN_00752AB0((int)(VoiceVolume * DAT_007EAA50));
    FUN_00407150(DAT_0087E740, (int)(VoiceVolume * 16384.0f));
    if (playSample)
        VocClass::PlayGlobal(DAT_008871E0->VolumeFeedback, VoiceVolume, 0x2000, 0);
    FUN_004068E0(STR_00832FC4, (double)VoiceVolume);
}
