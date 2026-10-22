// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//
//   The WOL scenario-setup dialog's option-control change
//   handlers: sixteen small __thiscall methods at 0x5B9650-0x5B9A56 that read a
//   trackbar position or a checkbox state out of a dialog control and publish
//   it into the global game-mode option block, then mark the dialog dirty.
//
//   Every address, control id, message id, member offset and global offset
//   below was read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI (`ghidra disasm`). The names used here are taken from
//   the global each body stores to, cross-checked against YRpp's
//   GameModeOptionsClass.
//
//   Convention: each body opens `PUSH ESI; MOV ESI,ECX` and returns with a bare
//   `RET` after popping, so the receiver arrives in ECX and there is no stack
//   argument — __thiscall with no parameters.
//
//   Imports (indirect through the IAT, so declared __declspec(dllimport)):
//     0x7E14A8 GetDlgItem, 0x7E14A4 SendMessageA, 0x7E1490 SendDlgItemMessageA.
#ifndef GG_MATCH_UI_WOL_SCENARIO_OPTION_HANDLERS_H
#define GG_MATCH_UI_WOL_SCENARIO_OPTION_HANDLERS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HWND__;
typedef HWND__* HWND_;

extern "C" __declspec(dllimport) HWND_ __stdcall GetDlgItem(HWND_ dlg, int id);
extern "C" __declspec(dllimport) long __stdcall SendMessageA(HWND_ wnd,
                                                             unsigned int msg,
                                                             unsigned int wParam,
                                                             long lParam);
extern "C" __declspec(dllimport) long __stdcall SendDlgItemMessageA(HWND_ dlg,
                                                                    int id,
                                                                    unsigned int msg,
                                                                    unsigned int wParam,
                                                                    long lParam);

// Window messages used below, from the retail immediates:
//   0x400 = TBM_GETPOS (WM_USER), 0xF0 = BM_GETCHECK, 0xF1 = BM_SETCHECK.
#define GG_TBM_GETPOS   0x400
#define GG_BM_GETCHECK  0xF0
#define GG_BM_SETCHECK  0xF1

// ---------------------------------------------------------------------------
// The global game-mode option block.
//
// GLOBAL: GAMEMD 0xA8B250
//
// Modelled as one struct because every field this family touches lies inside a
// single contiguous run, and addressing a field through a modelled global keeps
// the displacement inside the relocation slot, which the differ normalises. The
// base 0xA8B250 is a YRpp cross-check (GameModeOptionsClass::Instance); every
// offset below is confirmed numerically from the stores in this TU:
//
//   0xA8B258 Bases              (0x5B97C0 `MOV [0xa8b258],AL`)          +0x08
//   0xA8B25C Money              (0x5B96B0 `MOV [0xa8b25c],EAX`)         +0x0C
//   0xA8B260 BridgeDestruction  (0x5B98B0 `MOV byte [0xa8b260],CL`)     +0x10
//   0xA8B261 Crates             (0x5B9830 `MOV byte [0xa8b261],CL`)     +0x11
//   0xA8B262 ShortGame          (0x5B9930 `MOV byte [0xa8b262],CL`)     +0x12
//   0xA8B263 SWAllowed          (0x5B99A0 `MOV byte [0xa8b263],CL`)     +0x13
//   0xA8B268 GameSpeed          (0x5B9710 `MOV [0xa8b268],ECX`)         +0x18
//   0xA8B26C MultiEngineer      (0x5B9A20 `MOV byte [0xa8b26c],CL`)     +0x1C
//   0xA8B270 UnitCount          (0x5B9650 `MOV [0xa8b270],EAX`)         +0x20
//   0xA8B274 AIPlayers          (0x5B96E0 `MOV [0xa8b274],EAX`)         +0x24
//   0xA8B278 AIDifficulty       (0x5B9750 `MOV [0xa8b278],EAX`)         +0x28
//   0xA8B31D HarvesterTruce     (0x5B98F0 `MOV byte [0xa8b31d],CL`)     +0xCD
//   0xA8B31F FogOfWar           (0x5B9870 `MOV byte [0xa8b31f],CL`)     +0xCF
//   0xA8B320 MCVRedeploy        (0x5B9780 `MOV byte [0xa8b320],CL`)     +0xD0
//
// The 0x14/0x64-wide holes are never referenced by this family; they carry the
// build-off-ally flag and the per-slot AI arrays and are left as named gaps.
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
    char  unknown_1D[3];     // +0x1D  alignment before the int at +0x20
    int   UnitCount;         // +0x20
    int   AIPlayers;         // +0x24
    int   AIDifficulty;      // +0x28
    char  unknown_2C[0xA0];  // +0x2C  per-slot AI arrays, untouched here
    bool  unknown_CC;        // +0xCC  (allies-allowed)
    bool  HarvesterTruce;    // +0xCD
    bool  unknown_CE;        // +0xCE  (capture the flag)
    bool  FogOfWar;          // +0xCF
    bool  MCVRedeploy;       // +0xD0
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
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, AIDifficulty) == 0x28);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, HarvesterTruce) == 0xCD);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, FogOfWar) == 0xCF);
GG_STATIC_ASSERT(offsetof(GameModeOptionsClass_Opt, MCVRedeploy) == 0xD0);

extern GameModeOptionsClass_Opt GameModeOptions;

// GLOBAL: GAMEMD 0x822CF4 — the scenario tech level, a standalone int outside
// the option block (0x5B9680 `MOV [0x822cf4],EAX`).
extern int TechLevel;

// ---------------------------------------------------------------------------
// The dialog receiver.
//
// Only two members are exercised by this family, both confirmed numerically:
//   [ESI]      the dialog HWND, pushed straight into GetDlgItem /
//              SendDlgItemMessageA (`MOV EAX,dword ptr [ESI]; PUSH EAX;
//              CALL dword ptr [0x7e14a8]` at 0x5B9658). It cannot be a vftable
//              pointer, because it is the handle argument itself.
//   [ESI+0x9]  a one-byte dirty flag set to 1 on every path that reached a
//              control (`MOV byte ptr [ESI + 0x9],0x1` at 0x5B967A and in all
//              sixteen bodies).
// +0x04..+0x08 are never touched here and stay a named gap.
struct WolScenarioSetupClass
{
    HWND_ Dialog;          // +0x00
    char  unknown_04[5];   // +0x04
    bool  OptionsChanged;  // +0x09

    // FUNCTION: GAMEMD 0x5B9650
    void OnUnitCountChanged();
    // FUNCTION: GAMEMD 0x5B9680
    void OnTechLevelChanged();
    // FUNCTION: GAMEMD 0x5B96B0
    void OnMoneyChanged();
    // FUNCTION: GAMEMD 0x5B96E0
    void OnAIPlayersChanged();
    // FUNCTION: GAMEMD 0x5B9710
    void OnGameSpeedChanged();
    // FUNCTION: GAMEMD 0x5B9750
    void OnAIDifficultyChanged();
    // FUNCTION: GAMEMD 0x5B9780
    void OnMCVRedeployChanged();
    // FUNCTION: GAMEMD 0x5B97C0
    void OnBasesChanged();
    // FUNCTION: GAMEMD 0x5B9830
    void OnCratesChanged();
    // FUNCTION: GAMEMD 0x5B9870
    void OnFogOfWarChanged();
    // FUNCTION: GAMEMD 0x5B98B0
    void OnBridgeDestructionChanged();
    // FUNCTION: GAMEMD 0x5B98F0
    void OnHarvesterTruceChanged();
    // FUNCTION: GAMEMD 0x5B9930
    void OnShortGameChanged();
    // FUNCTION: GAMEMD 0x5B99A0
    void OnSWAllowedChanged();
    // FUNCTION: GAMEMD 0x5B99E0
    void OnShortGameChangedAlt();
    // FUNCTION: GAMEMD 0x5B9A20
    void OnMultiEngineerChanged();
};
GG_STATIC_ASSERT(offsetof(WolScenarioSetupClass, Dialog) == 0x00);
GG_STATIC_ASSERT(offsetof(WolScenarioSetupClass, OptionsChanged) == 0x09);

#endif  // GG_MATCH_UI_WOL_SCENARIO_OPTION_HANDLERS_H
