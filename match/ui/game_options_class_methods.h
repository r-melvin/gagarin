// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, the table address and the member offset read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x5FB2E0. Class and member
//   names cross-checked against YRpp, whose first member is `int GameSpeed` — the `MOV ECX,[ECX]` the
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
    int Difficulty;         // +0x04 the slider 0x50F of the game-controls dialog (0x4E1DE0)
    int CampDifficulty;     // +0x08
    int ScrollMethod;       // +0x0C
    int ScrollRate;         // +0x10 the slider 0x52A (0x4E1DE0)
    bool AutoScroll;        // +0x14
    unsigned char unknown_15[3];   // +0x15
    int DetailLevel;        // +0x18 the slider 0x52B (0x4E1DE0)
    bool SidebarOnRight;    // +0x1C
    bool SidebarCameoText;  // +0x1D
    bool UnitActionLines;   // +0x1E check box 0x601
    bool ShowHidden;        // +0x1F check box 0x604
    bool ToolTips;          // +0x20 check box 0x602
    unsigned char unknown_21[3];   // +0x21
    int ScreenWidth;        // +0x24
    int ScreenHeight;       // +0x28
    unsigned char unknown_2C[8];   // +0x2C
    bool StretchMovies;     // +0x34
    bool AllowHiResModes;   // +0x35
    bool AllowVRAMSidebar;  // +0x36
    unsigned char unknown_37;      // +0x37
    float SoundVolume;      // +0x38 SetSoundVolume 0x5FA510
    float VoiceVolume;      // +0x3C SetVoiceVolume 0x5FA590
    float ScoreVolume;      // +0x40 SetScoreVolume 0x5FA4A0
    bool IsScoreRepeat;     // +0x44
    bool InGameMusic;       // +0x45
    bool IsScoreShuffle;    // +0x46
    unsigned char unknown_47;      // +0x47
    unsigned short SoundLatency;   // +0x48
    unsigned short Socket;  // +0x4A
    int NetID[2];           // +0x4C
    int NetCard;            // +0x54
    char DestNet[0x40];     // +0x58 (0x58..0x97)
    char unknown_98[0x20];  // +0x98 the constructor 0x5FA350 stores up to +0xB4; the next global is 0xABCF28

    // FUNCTION: GAMEMD 0x5FA350 (decl; reloc)
    GameOptionsClass();
    void FUN_005FB160(); // GAMEMD 0x5FB160; caller0x683E02
    int GetAnimSpeed(int rate);   // GAMEMD 0x5FB2E0 __thiscall
    // FUNCTION: GAMEMD 0x5FAD10 (decl; reloc)
    void FUN_005FAD10();
    // FUNCTION: GAMEMD 0x5FA620 -- reads the [Options], [Video], [Audio] and [Network] settings.
    void FUN_005FA620();
    // FUNCTION: GAMEMD 0x5FB050 (decl; reloc)
    void FUN_005FB050();
    // FUNCTION: GAMEMD 0x5FA4A0
    void SetScoreVolume(float volume, bool unused);
    // FUNCTION: GAMEMD 0x5FA510
    void SetSoundVolume(float volume, bool playSample);
    // FUNCTION: GAMEMD 0x5FA590
    void SetVoiceVolume(float volume, bool playSample);
};
GG_STATIC_ASSERT(offsetof(GameOptionsClass, GameSpeed) == 0x00);
GG_STATIC_ASSERT(sizeof(((GameOptionsClass*)0)->GameSpeed) == 4);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, Difficulty) == 0x04);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, CampDifficulty) == 0x08);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, ScrollMethod) == 0x0C);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, ScrollRate) == 0x10);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, AutoScroll) == 0x14);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, DetailLevel) == 0x18);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, SidebarOnRight) == 0x1C);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, SidebarCameoText) == 0x1D);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, UnitActionLines) == 0x1E);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, ShowHidden) == 0x1F);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, ToolTips) == 0x20);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, ScreenWidth) == 0x24);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, ScreenHeight) == 0x28);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, StretchMovies) == 0x34);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, AllowHiResModes) == 0x35);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, AllowVRAMSidebar) == 0x36);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, SoundVolume) == 0x38);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, VoiceVolume) == 0x3C);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, ScoreVolume) == 0x40);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, IsScoreRepeat) == 0x44);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, InGameMusic) == 0x45);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, IsScoreShuffle) == 0x46);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, SoundLatency) == 0x48);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, Socket) == 0x4A);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, NetID) == 0x4C);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, NetCard) == 0x54);
GG_STATIC_ASSERT(offsetof(GameOptionsClass, DestNet) == 0x58);
GG_STATIC_ASSERT(sizeof(GameOptionsClass) == 0xB8);

#endif  // GG_MATCH_UI_GAME_OPTIONS_CLASS_METHODS_H
