// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Original translation unit ModemHst.cpp. The name is the source-file string at 0x82c9a4
//   in retail gamemd.exe v1.001, passed by the assert at 0x5b841d inside this object's
//   code range (0x5b75f0-0x5bbf8f). Functions are in ascending retail address order.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
//   Depth-first registry search for a subkey holding a given string value.
//
// The nine tail-jump thunks, ordered ascending by retail address.

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include <windows.h>
#include <string.h>

// Opens subkey name under root; returns 0 on failure.
HKEY FUN_007741c0(HKEY root, const char* name, int flags);

#include "../core/tail_jmp_thunk_sweep.h"

#include "wol_scenario_color_methods.h"

#include "wol_scenario_option_handlers.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EDF68
extern const double DAT_007EDF68;
// GLOBAL: GAMEMD 0xABF0B0
extern double DAT_00ABF0B0;
// GLOBAL: GAMEMD 0xABF0E8
extern double DAT_00ABF0E8;
// GLOBAL: GAMEMD 0xABF0F0
extern int DAT_00ABF0F0;
// GLOBAL: GAMEMD 0xABF0F4
extern int DAT_00ABF0F4;
// GLOBAL: GAMEMD 0xABF0F8
extern int DAT_00ABF0F8;
// GLOBAL: GAMEMD 0xABF100
extern double DAT_00ABF100;

// FUNCTION: GAMEMD 0x5B7620
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005B7620()
{
    DAT_00ABF100 = DAT_00ABF0B0 / DAT_007EDF68;
}

// FUNCTION: GAMEMD 0x5B7640
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005B7640()
{
    DAT_00ABF0E8 = DAT_007E1718 / DAT_00ABF100;
}

// FUNCTION: GAMEMD 0x5B77C0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_005B77C0()
{
    DAT_00ABF0F8 = 0;
    DAT_00ABF0F0 = 0x80;
    DAT_00ABF0F4 = 0x80;
}

// FUNCTION: GAMEMD 0x5B9450
//
// The colour combo's selection changed. The tail is the same publish-and-repaint
// run as the reconcile above, without the advance-past-our-own-colour step.
//
// EXACT (47/47 instructions); same spelling as FUN_005B59B0.
void WolScenarioColorDlgClass::OnColorSelChanged()
{
    HWND_ dialog = this->Dialog;
    HWND_ control = GetDlgItem(dialog, 0x405);
    if (control == 0) return;
    int selection = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
    if (selection == -1) return;
    PlayerColor = selection;
    this->OptionsChanged = true;
    this->unknown_08 = true;
    unsigned color = (selection >= 0 && selection < 8) ? DAT_008316A8[selection] : DefaultSchemeColor;
    SendMessageA(control, GG_CBM_SETCOLOR, 0, color);
}

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

// Prints a coloured line into the dialog's text control (id 0x53F): the line is
// "[name] text" built into a 256-wide-character buffer, and the colour is looked
// up by index in the table of eight colours at 0x8316A8 (the default scheme
// colour when the index is out of range).
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);
// FUNCTION: GAMEMD 0x5E2820 (decl; reloc) -- appends a coloured line to a text control.
void FUN_005E2820(int color, const wchar_t* text, HWND_ window);
struct Obj_005BAA80 {
    HWND_ unknown_00;
    void FUN_005BAA80(const wchar_t* name, int index, const wchar_t* text);
};
// FUNCTION: GAMEMD 0x005BAA80
void Obj_005BAA80::FUN_005BAA80(const wchar_t* name, int index, const wchar_t* text)
{
    wchar_t line[256];
    if (text != 0) {
        HWND_ control = GetDlgItem(unknown_00, 0x53F);
        if (control != 0) {
            int color = (index >= 0 && index < 8) ? DAT_008316A8[index] : DefaultSchemeColor;
            swprintf(line, L"[%s] %s", name, text);
            FUN_005E2820(color, line, control);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5BB560
void* Obj_5BB560::FUN_5BB560(unsigned int flags)
{
    FUN_006406F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005bb580
// Returns the first subkey (searched depth-first below root) whose string
// value valueName equals match, still open; 0 when none is found.
HKEY FUN_005bb580(HKEY root, const char* valueName, const char* match)
{
    DWORD size = 256;
    DWORD index = 0;
    char* name = new char[size];
    DWORD dataSize = size;
    char* data = new char[dataSize];
    DWORD nameSize = size;
    FILETIME stamp;
    for (;;) {
        nameSize = 256;
        if (RegEnumKeyExA(root, index++, name, &nameSize, 0, 0, 0, &stamp) != ERROR_SUCCESS) {
            break;
        }
        HKEY sub = FUN_007741c0(root, name, 0);
        if (sub == 0) {
            continue;
        }
        DWORD type;
        dataSize = 256;
        if (RegQueryValueExA(sub, valueName, 0, &type, (LPBYTE)data, &dataSize) == ERROR_SUCCESS
            && type == REG_SZ && strcmp(data, match) == 0) {
            delete name;
            delete data;
            return sub;
        }
        HKEY found = FUN_005bb580(sub, valueName, match);
        RegCloseKey(sub);
        if (found != 0) {
            delete name;
            delete data;
            return found;
        }
    }
    delete name;
    delete data;
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5BBED0
void FUN_005BBED0(void* self)
{
    FUN_005BBEE0(self);
}
