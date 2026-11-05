// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check | behaviour-confirmed-name
//
//   Two colour-combo methods of the WOL scenario-setup dialog, at 0x5B59B0 and
//   0x5B9450. Both read the current selection out of the player-colour combo
//   box, publish it into the global player-colour index, mark the dialog dirty,
//   and then push the matching RGB value back into the combo so it repaints in
//   the chosen colour.
//
//   Every address, control id, message id and offset was read numerically off
//   the user's retail gamemd.exe v1.001 through the local Ghidra CLI. The
//   grouping and the "colour" reading came from the user's own behavioural
//   reimplementation (`ui/wol_scenario_setup_color.cpp`), which is a
//   64-bit reimplementation and contributed no bytes, layout or conventions.
//   The global 0xA8B394 is YRpp's `PlayerColor` (cross-check); its
//   use here is confirmed independently by the two `MOV [0xa8b394],<sel>` stores.
//
//   The dialog class is modelled independently in this TU so the file stands
//   alone; the members it shares with
//   match/wol_scenario_option_handlers.h agree offset for offset (it is the same
//   dialog object; the two TUs model the members each needs and are given
//   distinct type names so the definitions cannot collide).
#ifndef GG_MATCH_UI_WOL_SCENARIO_COLOR_METHODS_H
#define GG_MATCH_UI_WOL_SCENARIO_COLOR_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "shared_constants_globals.h"
#include "scenario_session_globals.h"

struct HWND__;
typedef HWND__* HWND_;

extern "C" __declspec(dllimport) HWND_ __stdcall GetDlgItem(HWND_ dlg, int id);
extern "C" __declspec(dllimport) long __stdcall SendMessageA(HWND_ wnd,
                                                             unsigned int msg,
                                                             unsigned int wParam,
                                                             long lParam);

// From the retail immediates: 0x147 = CB_GETCURSEL, 0x14E = CB_SETCURSEL.
// 0x498 is a private combo message carrying an RGB value in lParam.
#define GG_CB_GETCURSEL 0x147
#define GG_CB_SETCURSEL 0x14E
#define GG_CBM_SETCOLOR 0x498
#define GG_CB_GETITEMDATA 0x150
#define GG_CBM_SETTEXT 0x4B2

// GLOBAL: GAMEMD 0x7EEF44 — the RGB value used when the index is out of range.
extern const unsigned long DefaultSchemeColor;

// ---------------------------------------------------------------------------
// The dialog receiver. Offsets confirmed numerically:
//   [ESI]      the dialog HWND, pushed straight into GetDlgItem (0x5B945A).
//   [ESI+0x8]  a byte flag set to 1 alongside the dirty flag (0x5B948C).
//   [ESI+0x9]  the options-changed byte flag (0x5B9489).
//   [ESI+0x48] an int colour index compared against the combo selection
//              (`MOV EAX,dword ptr [EDI + 0x48]; CMP ESI,EAX` at 0x5B59E3).
struct WolScenarioColorDlgClass
{
    HWND_ Dialog;           // +0x00
    char  unknown_04[4];    // +0x04
    bool  unknown_08;       // +0x08  second dirty byte, always set with +0x09
    bool  OptionsChanged;   // +0x09
    char  unknown_0A[2];    // +0x0A
    unsigned int LastSendTime;   // +0x0C  `MOV [ESI+0xC],EDI` at 0x5B5F6A
    char  unknown_10[0xC];  // +0x10
    unsigned int LastPingTime;   // +0x1C  `MOV [ESI+0x1C],EDI` at 0x5B6002
    wchar_t Handle[20];     // +0x20  wcscpy target at 0x5B5AE8 (`LEA ECX,[ESI+0x20]`)
    int   ColorIndex;       // +0x48
    int   SlotIndex;        // +0x4C  `MOV [ESI+0x4C],EDI` at 0x5B5B3E
    int   unknown_50;       // +0x50  read at 0x5B6CEC
    int   unknown_54;       // +0x54  read at 0x5B6CE7
    int   unknown_58;       // +0x58  read at 0x5B6CEF

    // FUNCTION: GAMEMD 0x5B59B0
    void FUN_005B59B0();
    // FUNCTION: GAMEMD 0x5B9F30
    void FUN_005B9F30(bool force);
    // FUNCTION: GAMEMD 0x5BA660 (decl; reloc)
    void FUN_005BA660();
    // FUNCTION: GAMEMD 0x5B5EF0
    void FUN_005B5EF0(bool force);
    // FUNCTION: GAMEMD 0x5B6CD0
    void FUN_005B6CD0();
    // FUNCTION: GAMEMD 0x5B5AD0
    void FUN_005B5AD0(const wchar_t* handle, int color, int slot);
    // FUNCTION: GAMEMD 0x5B9450
    void OnColorSelChanged();
    // FUNCTION: GAMEMD 0x5B5960
    void FUN_005B5960();
    // FUNCTION: GAMEMD 0x5B93F0
    void FUN_005B93F0();
    // FUNCTION: GAMEMD 0x5B5E90
    void FUN_005B5E90();
    // FUNCTION: GAMEMD 0x5B5A50
    void FUN_005B5A50(char mode);
    // FUNCTION: GAMEMD 0x5B56F0
    void FUN_005B56F0();
    // FUNCTION: GAMEMD 0x5B7090
    bool FUN_005B7090(char skip);
};
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, Dialog) == 0x00);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, OptionsChanged) == 0x09);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, LastSendTime) == 0x0C);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, LastPingTime) == 0x1C);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, Handle) == 0x20);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, ColorIndex) == 0x48);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, SlotIndex) == 0x4C);

#endif  // GG_MATCH_UI_WOL_SCENARIO_COLOR_METHODS_H
