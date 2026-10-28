// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Original translation unit ModemGst.cpp. The name is the source-file string at 0x82c534
//   in retail gamemd.exe v1.001, passed by the assert at 0x5b4f73 inside this object's
//   code range (0x5b47c0-0x5b75ef). Functions are in ascending retail address order.

#include "wol_scenario_color_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EDF58
extern const double DAT_007EDF58;
// GLOBAL: GAMEMD 0xABF030
extern double DAT_00ABF030;
// GLOBAL: GAMEMD 0xABF068
extern double DAT_00ABF068;
// GLOBAL: GAMEMD 0xABF070
extern int DAT_00ABF070;
// GLOBAL: GAMEMD 0xABF074
extern int DAT_00ABF074;
// GLOBAL: GAMEMD 0xABF078
extern int DAT_00ABF078;
// GLOBAL: GAMEMD 0xABF080
extern double DAT_00ABF080;

// FUNCTION: GAMEMD 0x5B59B0
//
// Reconcile the colour combo with the colour this slot already holds. If the
// selection still points at the slot's own colour it is advanced by one, wrapped
// past the last of the eight, and written back into the combo; otherwise the
// selection stands. Either way the resulting index is published and the combo is
// repainted in its colour, falling back to the default RGB when the index is out
// of range.
//
// EXACT (63/63 instructions, raw bytes identical apart from relocation slots).
// Flat early returns plus the repaint colour chosen into one local before a
// single SendMessage reproduce retail's register naming (receiver in EDI,
// control handle in EBX).
void WolScenarioColorDlgClass::FUN_005B59B0()
{
    HWND_ dialog = this->Dialog;
    HWND_ control = GetDlgItem(dialog, 0x405);
    if (control == 0) return;
    int selection = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
    if (selection == -1) return;
    if (selection == this->ColorIndex) {
        selection = this->ColorIndex + 1;
        if (selection > 7) selection = 0;
        SendMessageA(control, GG_CB_SETCURSEL, selection, 0);
    }
    PlayerColor = selection;
    this->OptionsChanged = true;
    this->unknown_08 = true;
    unsigned color = (selection >= 0 && selection < 8) ? DAT_008316A8[selection] : DefaultSchemeColor;
    SendMessageA(control, GG_CBM_SETCOLOR, 0, color);
}

// Prints a coloured line into the dialog's text control (id 0x53F): the line is
// "[name] text" built into a 256-wide-character buffer, and the colour is looked
// up by index in the table of eight colours at 0x8316A8 (the default scheme
// colour when the index is out of range).
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);
// FUNCTION: GAMEMD 0x5E2820 (decl; reloc) -- appends a coloured line to a text control.
void FUN_005E2820(int color, const wchar_t* text, HWND_ window);
struct Obj_005B6EB0 {
    HWND_ unknown_00;
    void FUN_005B6EB0(const wchar_t* name, int index, const wchar_t* text);
};
// FUNCTION: GAMEMD 0x005B6EB0
void Obj_005B6EB0::FUN_005B6EB0(const wchar_t* name, int index, const wchar_t* text)
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
