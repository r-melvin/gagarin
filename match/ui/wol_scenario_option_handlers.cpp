// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5B9650-0x5B9A56.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX

#include "wol_scenario_option_handlers.h"

// FUNCTION: GAMEMD 0x5B9650
//
// The unit-count trackbar moved. Read its thumb position and publish it as the
// starting unit count, then mark the dialog dirty. A missing control skips both.
void WolScenarioSetupClass::OnUnitCountChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x669);
    if (control != 0) {
        GameModeOptions.UnitCount = SendMessageA(control, GG_TBM_GETPOS, 0, 0);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B9680
//
// The tech-level trackbar moved. Same shape as the unit-count handler, but the
// destination is the standalone tech-level global rather than the option block.
void WolScenarioSetupClass::OnTechLevelChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x550);
    if (control != 0) {
        TechLevel = SendMessageA(control, GG_TBM_GETPOS, 0, 0);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B96B0
//
// The starting-credits trackbar moved.
void WolScenarioSetupClass::OnMoneyChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x402);
    if (control != 0) {
        GameModeOptions.Money = SendMessageA(control, GG_TBM_GETPOS, 0, 0);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B96E0
//
// The AI-player-count trackbar moved.
void WolScenarioSetupClass::OnAIPlayersChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x552);
    if (control != 0) {
        GameModeOptions.AIPlayers = SendMessageA(control, GG_TBM_GETPOS, 0, 0);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B9710
//
// The game-speed trackbar moved. The slider runs fastest-to-slowest while the
// stored speed runs the other way, so the position is subtracted from six.
void WolScenarioSetupClass::OnGameSpeedChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x529);
    if (control != 0) {
        GameModeOptions.GameSpeed = 6 - SendMessageA(control, GG_TBM_GETPOS, 0, 0);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B9750
//
// The AI-difficulty trackbar moved.
void WolScenarioSetupClass::OnAIDifficultyChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x553);
    if (control != 0) {
        GameModeOptions.AIDifficulty = SendMessageA(control, GG_TBM_GETPOS, 0, 0);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B9780
//
// The MCV-redeploy checkbox was clicked. A checkbox reports its state as a
// three-way value, so the flag is the equality against "checked" rather than
// the raw result.
void WolScenarioSetupClass::OnMCVRedeployChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x66B);
    if (control != 0) {
        GameModeOptions.MCVRedeploy =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B97C0
//
// The bases checkbox was clicked. Turning bases off forces the short-game
// option off with it, both in the option block and in its own checkbox, because
// a short game without bases has no win condition. The forced clear is guarded
// by that control existing, and the dirty flag is set once at the end for both
// paths.
void WolScenarioSetupClass::OnBasesChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x66A);
    if (control != 0) {
        if (!(GameModeOptions.Bases =
                  (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1))) {
            if (GetDlgItem(this->Dialog, 0x54E) != 0) {
                GameModeOptions.ShortGame = false;
                SendDlgItemMessageA(this->Dialog, 0x54E, GG_BM_SETCHECK, 0, 0);
            }
        }
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B9830
//
// The crates checkbox was clicked.
void WolScenarioSetupClass::OnCratesChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x54C);
    if (control != 0) {
        GameModeOptions.Crates =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B9870
//
// The fog-of-war checkbox was clicked.
void WolScenarioSetupClass::OnFogOfWarChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x54D);
    if (control != 0) {
        GameModeOptions.FogOfWar =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B98B0
//
// The bridge-destruction checkbox was clicked.
void WolScenarioSetupClass::OnBridgeDestructionChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x624);
    if (control != 0) {
        GameModeOptions.BridgeDestruction =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B98F0
//
// The harvester-truce checkbox was clicked.
void WolScenarioSetupClass::OnHarvesterTruceChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x596);
    if (control != 0) {
        GameModeOptions.HarvesterTruce =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B9930
//
// The short-game checkbox was clicked: the mirror of the bases handler. Turning
// short game on forces bases on. Unlike the bases handler the dirty flag is set
// before the dependent update, and the stored flag is re-read from the option
// block rather than kept in a register, so the store and the test are separate
// statements here.
void WolScenarioSetupClass::OnShortGameChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x54E);
    if (control != 0) {
        GameModeOptions.ShortGame =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
        if (GameModeOptions.ShortGame) {
            if (GetDlgItem(this->Dialog, 0x66A) != 0) {
                GameModeOptions.Bases = true;
                SendDlgItemMessageA(this->Dialog, 0x66A, GG_BM_SETCHECK, 1, 0);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5B99A0
//
// The superweapons checkbox was clicked.
void WolScenarioSetupClass::OnSWAllowedChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x69A);
    if (control != 0) {
        GameModeOptions.SWAllowed =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B99E0
//
// The short-game checkbox on the second dialog template. Same option, different
// control id, and no dependent update.
void WolScenarioSetupClass::OnShortGameChangedAlt()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x69D);
    if (control != 0) {
        GameModeOptions.ShortGame =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
    }
}

// FUNCTION: GAMEMD 0x5B9A20
//
// The multi-engineer checkbox was clicked.
void WolScenarioSetupClass::OnMultiEngineerChanged()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x551);
    if (control != 0) {
        GameModeOptions.MultiEngineer =
            (SendMessageA(control, GG_BM_GETCHECK, 0, 0) == 1);
        this->OptionsChanged = true;
    }
}
