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
//   The global 0xA8B394 is YRpp's `PlayerColor` (consult-only cross-check); its
//   use here is confirmed independently by the two `MOV [0xa8b394],<sel>` stores.
//
//   The dialog class is modelled independently in this TU so the file stands
//   alone; the members it shares with
//   match/ui/wol_scenario_option_handlers.h agree offset for offset (it is the same
//   dialog object; the two TUs model the members each needs and are given
//   distinct type names so the definitions cannot collide).
#ifndef GG_MATCH_UI_WOL_SCENARIO_COLOR_METHODS_H
#define GG_MATCH_UI_WOL_SCENARIO_COLOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

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

// GLOBAL: GAMEMD 0xA8B394 — the local player's chosen colour index.
extern int PlayerColor;

// GLOBAL: GAMEMD 0x8316A8 — eight RGB values indexed by colour, addressed as
// `MOV EAX,dword ptr [EAX*0x4 + 0x8316a8]` at 0x5B9496 under a `0 <= i < 8`
// guard, so it is an eight-element array of dwords.
extern const unsigned long DAT_008316A8[8];

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
    char  unknown_0A[0x3E]; // +0x0A
    int   ColorIndex;       // +0x48

    // FUNCTION: GAMEMD 0x5B59B0
    void FUN_005B59B0();
    // FUNCTION: GAMEMD 0x5B9450
    void OnColorSelChanged();
};
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, Dialog) == 0x00);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, OptionsChanged) == 0x09);
GG_STATIC_ASSERT(offsetof(WolScenarioColorDlgClass, ColorIndex) == 0x48);

#endif  // GG_MATCH_UI_WOL_SCENARIO_COLOR_METHODS_H
