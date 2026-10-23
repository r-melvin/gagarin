// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Existing option-control layout from 0x5B9650..0x5B9A56. Native
// 0x69B560/0x69B5B0 transfer exactly 0x12C bytes; the loader stores -1
// at +4 after its payload read. Native callers 0x67E3D3/0x67F744 pass
// 0xA8B250, the Session receiver +0x18. Untouched regions stay opaque.
#ifndef GG_MATCH_LAYOUT_GAME_MODE_OPTIONS_H
#define GG_MATCH_LAYOUT_GAME_MODE_OPTIONS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct IStream;
struct GameModeOptionsClass_Opt
{
    int   unknown_00;        // +0x00  (MP mode index)
    int   unknown_04;        // +0x04  (scenario index)
    bool  Bases;             // +0x08
    char  unknown_09[3];     // +0x09  alignment before the int at +0x0C
    int   Money;             // +0x0C
    bool  BridgeDestruction; // +0x10
    bool  Crates;            // +0x11
    bool  ShortGame;         // +0x12
    bool  SWAllowed;         // +0x13
    bool  unknown_14;        // +0x14  (build-off-ally)
    char  unknown_15[3];     // +0x15  alignment before the int at +0x18
    int   GameSpeed;         // +0x18
    bool  MultiEngineer;     // +0x1C
    unsigned char unknown_1D; // native698EDA byte atSession35
    char unknown_1E[2];
    int   UnitCount;         // +0x20
    int   AIPlayers;         // +0x24
    int   AIDifficulty;      // +0x28
    char  unknown_2C[0x4C - 0x2C];
    int   unknown_4C[8]; // native 0x69B540; Session+0x64
    int   unknown_6C[8]; // native 0x69B540; Session+0x84
    char  unknown_8C[0xCC - 0x8C];
    bool  unknown_CC;        // +0xCC  (allies-allowed)
    bool  HarvesterTruce;    // +0xCD
    bool  unknown_CE;        // +0xCE  (capture the flag)
    bool  FogOfWar;          // +0xCF
    bool  MCVRedeploy;       // +0xD0
    char  unknown_D1[0x12C - 0xD1];

    // Declaration: GAMEMD 0x69B540
    void Clear();
    // Declaration: GAMEMD 0x69B560
    bool FUN_0069B560(IStream* stream);
    // Declaration: GAMEMD 0x69B5B0
    bool FUN_0069B5B0(IStream* stream);
};
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, Bases) == 0x08);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, Money) == 0x0C);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, BridgeDestruction) == 0x10);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, Crates) == 0x11);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, ShortGame) == 0x12);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, SWAllowed) == 0x13);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, GameSpeed) == 0x18);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, MultiEngineer) == 0x1C);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, UnitCount) == 0x20);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, AIPlayers) == 0x24);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->AIPlayers) == 4);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, AIDifficulty) == 0x28);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, HarvesterTruce) == 0xCD);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, FogOfWar) == 0xCF);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, MCVRedeploy) == 0xD0);

// GLOBAL: GAMEMD 0xA8B250
extern GameModeOptionsClass_Opt GameModeOptions;

GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, unknown_00) == 0x0);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->unknown_00) == 0x4);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, unknown_04) == 0x4);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->unknown_4C) == 0x20);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->unknown_6C) == 0x20);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, unknown_D1) == 0xD1);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->unknown_D1) == 0x5B);
GG_STATIC_ASSERT(sizeof(GameModeOptionsClass_Opt) == 0x12C);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, unknown_1D) == 0x1D);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->unknown_1D) == 1);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->Bases) == 1);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->Money) == 4);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->BridgeDestruction) == 1);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->Crates) == 1);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->UnitCount) == 4);
GG_STATIC_ASSERT(sizeof(((GameModeOptionsClass_Opt*)0)->AIDifficulty) == 4);
#endif
