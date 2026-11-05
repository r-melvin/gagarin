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

#include "deleting_dtor_sweep.h"
#include "winsock_interface_class.h"
#include "_layout/pipe.h"
#include "_layout/straw.h"
#include "house_type_class_find_methods.h"
#include "_layout/rules_class.h"
#include "_layout/voc_class.h"
#include "wol_request_queue.h"
#include "message_list_class_manage_methods.h"

#include <windows.h>
#include <string.h>
#include <stddef.h>
#include "_rt/gg_static_assert.h"

// Opens subkey name under root; returns 0 on failure.
HKEY FUN_007741c0(HKEY root, const char* name, int flags);

#include "tail_jmp_thunk_sweep.h"

#include "wol_scenario_color_methods.h"

#include "wol_scenario_option_handlers.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"

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

// GLOBAL: GAMEMD 0xA8B3AC -- the value the list control at 0x667 hands back for its selection.
extern int DAT_00A8B3AC;
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern RulesClass* DAT_008871E0;

// FUNCTION: GAMEMD 0x5B93F0
//
// The list at control 0x667 changed: take the data value of its selected row and, if the control
// has one, publish it and mark the dialog dirty. No control, no selection or no data changes nothing.
void WolScenarioColorDlgClass::FUN_005B93F0()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x667);
    if (control != 0) {
        unsigned int selection = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
        if (selection != 0xFFFFFFFF) {
            long data = SendMessageA(control, GG_CB_GETITEMDATA, selection, 0);
            if (data != -1) {
                DAT_00A8B3AC = data;
                this->OptionsChanged = true;
                this->unknown_08 = true;
            }
        }
    }
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

// LIBRARY: GAMEMD 0x7CA489 (decl; reloc) -- CRT wcscpy, cdecl.
extern "C" wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
// FUNCTION: GAMEMD 0x7DD0F8 (decl; reloc) -- wide string compare, cdecl; zero when equal.
extern "C" int __cdecl FUN_007DD0F8(const wchar_t* a, const wchar_t* b);
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);

// The slot-label receiver of 0x5B9550: the dialog HWND at +0, the dirty byte at +9, a wide
// handle at +0x22 and two ints at +0x4C / +0x50 (all read off 0x5B9550's instructions).
struct Obj_005B9550 {
    HWND_ Dialog;           // +0x00
    char unknown_04[5];     // +0x04
    bool OptionsChanged;    // +0x09
    char unknown_0A[0x18];  // +0x0A
    wchar_t Handle[20];     // +0x22
    char unknown_4A[2];     // +0x4A
    int Color;              // +0x4C
    int Slot;               // +0x50
    void FUN_005B9550(const wchar_t* handle, int color, int slot);
};
GG_STATIC_ASSERT(offsetof(Obj_005B9550, OptionsChanged) == 0x09);
GG_STATIC_ASSERT(offsetof(Obj_005B9550, Handle) == 0x22);
GG_STATIC_ASSERT(offsetof(Obj_005B9550, Color) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_005B9550, Slot) == 0x50);

// FUNCTION: GAMEMD 0x5B9550
//
// Update a slot's label when its handle, colour or slot index changed: store the new values,
// redraw the label (control 0x668) as "handle [house name]" in the colour, and play the
// options-changed sound. The dirty byte is set either way.
void Obj_005B9550::FUN_005B9550(const wchar_t* handle, int color, int slot)
{
    if (FUN_007DD0F8(Handle, handle) != 0 || Color != color || Slot != slot) {
        wcscpy(Handle, handle);
        Color = color;
        Slot = slot;
        HWND_ label = GetDlgItem(Dialog, 0x668);
        if (label != 0) {
            wchar_t line[80];
            swprintf(line, L"%s [%s]", handle, HouseTypeArray.Items[slot]->UIName);
            SendMessageA(label, GG_CBM_SETTEXT, 0, (long)line);
            unsigned long rgb = (color >= 0 && color < 8) ? DAT_008316A8[color] : DefaultSchemeColor;
            SendMessageA(label, GG_CBM_SETCOLOR, 0, rgb);
        }
        VocClass::PlayGlobal(DAT_008871E0->OptionsChanged, 1.0f, 0x2000, 0);
    }
    OptionsChanged = true;
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

// FUNCTION: GAMEMD 0x5B9F30
//
// Per-tick service of the host dialog; same shape as 0x5B5EF0 with the host status sender
// 0x5BA660 in place of 0x5B6CD0.
void WolScenarioColorDlgClass::FUN_005B9F30(bool force)
{
    DAT_00A8EA70.FUN_005F1C60();
    if ((OptionsChanged == 1 && (unsigned)(MessageTimer.GetValue() - LastSendTime) > 0x1E) || force == 1) {
        FUN_005BA660();
        LastSendTime = MessageTimer.GetValue();
        OptionsChanged = 0;
    }
    if ((unsigned)(MessageTimer.GetValue() - LastPingTime) > 0x28) {
        WolRequest_005B5EF0 request;
        memset(&request, 0, 0xFA);
        request.Code = 0x69;
        request.unknown_9A = DAT_00A8EA70.FUN_005F1EE0();
        request.unknown_18 = (char)DAT_00A8DB30;
        DAT_00A8EA70.FUN_005F1BF0(&request, 0xFA, 0);
        LastPingTime = MessageTimer.GetValue();
    }
}

// FUNCTION: GAMEMD 0x735120 (decl; reloc)
const wchar_t* FUN_00735120(const char* text);
// GLOBAL: GAMEMD 0xA8B380 -- the local player's handle, ANSI.
extern char DAT_00A8B380[];
// FUNCTION: GAMEMD 0x5E2820 (decl; reloc) -- appends a coloured line to a text control.
void FUN_005E2820(int color, const wchar_t* text, HWND_ window);
struct Obj_005BA970 {
    HWND_ unknown_00;
    void FUN_005BA970(const wchar_t* text);
};

// FUNCTION: GAMEMD 0x5BA970
//
// Send a chat line from the host dialog: same request and echo as 0x5B6DA0.
void Obj_005BA970::FUN_005BA970(const wchar_t* text)
{
    if (text != 0) {
        WolChatRequest_005B6DA0 request;
        memset(&request, 0, 0xFA);
        request.Code = 0x68;
        strcpy(request.Handle, DAT_00A8B380);
        request.Color = (char)PlayerColor;
        wcscpy(request.Text, text);
        DAT_00A8EA70.FUN_005F1BF0(&request, 0xFA, 1);
        DAT_00A8EA70.FUN_005F1C60();
        const wchar_t* handle = FUN_00735120(DAT_00A8B380);
        int color = PlayerColor;
        HWND_ control = GetDlgItem(unknown_00, 0x53F);
        if (control != 0) {
            unsigned long rgb = (color >= 0 && color < 8) ? DAT_008316A8[color] : DefaultSchemeColor;
            wchar_t line[256];
            swprintf(line, L"[%s] %s", handle, text);
            FUN_005E2820(rgb, line, control);
        }
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

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised text.
const wchar_t* FUN_00734E60(const char* label, int* index, const char* file, int line);
// FUNCTION: GAMEMD 0x623230 (decl; reloc) -- open the wait dialog; each text line goes out as an LPARAM.
void* FUN_00623230(long line1, long line2, long user);
// FUNCTION: GAMEMD 0x622800 (decl; reloc)
void UI_FocusOnWindow(HWND_ window);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void UI_EndDialog(void* window);
// FUNCTION: GAMEMD 0x48D080 (decl; reloc)
void __cdecl Unsorted_CallBack();
// FUNCTION: GAMEMD 0x5D4D50 (decl; reloc)
void __cdecl FUN_005D4D50();
// FUNCTION: GAMEMD 0x5F0040 (decl; reloc)
void __cdecl FUN_005F0040();
struct Obj_005BAB00 {
    void FUN_005BAB00();
};

// FUNCTION: GAMEMD 0x5BAB00
//
// Send the sign-off request (code 0x66), show the "signing off" wait dialog and pump the queue
// until the matching reply arrives or 300 ticks pass, then close the dialog.
void Obj_005BAB00::FUN_005BAB00()
{
    WolReply_005B6F30 reply;
    WolRequest_005B6F30 request;
    int length;
    memset(&request, 0, 0xFA);
    request.Code = 0x66;
    request.Color = (char)PlayerColor;
    request.unknown_18 = (char)DAT_00A8DB30;
    DAT_00A8EA70.FUN_005F1BF0(&request, 0xFA, 1);
    HWND_ dialog = (HWND_)FUN_00623230((long)FUN_00734E60("TXT_SIGNING_OFF", 0, "D:\\ra2mdpost\\ModemHst.cpp", 0x95E), 0, 0);
    if (dialog != 0) {
        UI_FocusOnWindow(dialog);
    }
    unsigned int start = MessageTimer.GetValue();
    if (DAT_00A8EA70.FUN_005F1EA0() != 0) {
        do {
            if ((unsigned int)(MessageTimer.GetValue() - start) >= 0x12C) {
                break;
            }
            if (DAT_00A8EA70.FUN_005F1C30(&reply, &length) > 0 && reply.Code == 0x66 &&
                (reply.Value & 0xFF) == DAT_00A8DB30) {
                break;
            }
            Unsorted_CallBack();
            FUN_005D4D50();
            DAT_00A8EA70.FUN_005F1C60();
        } while (DAT_00A8EA70.FUN_005F1EA0() != 0);
    }
    FUN_005F0040();
    if (dialog != 0) {
        UI_EndDialog(dialog);
    }
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

// A block of seven owned heap buffers (view name; the owning class is unrecovered).
struct OwnedBuffers_005BBEE0
{
    void* Buffer[7];    // +0x00

    // FUNCTION: GAMEMD 0x5BBEE0
    void FreeAll();
};
GG_STATIC_ASSERT(sizeof(OwnedBuffers_005BBEE0) == 0x1C);

// FUNCTION: GAMEMD 0x5BBEE0
// Free every buffer that is still allocated and clear its pointer.
void OwnedBuffers_005BBEE0::FreeAll()
{
    if (Buffer[0]) { delete Buffer[0]; Buffer[0] = 0; }
    if (Buffer[1]) { delete Buffer[1]; Buffer[1] = 0; }
    if (Buffer[2]) { delete Buffer[2]; Buffer[2] = 0; }
    if (Buffer[3]) { delete Buffer[3]; Buffer[3] = 0; }
    if (Buffer[4]) { delete Buffer[4]; Buffer[4] = 0; }
    if (Buffer[5]) { delete Buffer[5]; Buffer[5] = 0; }
    if (Buffer[6]) { delete Buffer[6]; Buffer[6] = 0; }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x822CF4
int TechLevel = 10;
// END defined globals
