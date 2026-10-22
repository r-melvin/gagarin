// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5B59B0 and 0x5B9450.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX

#include "wol_scenario_color_methods.h"

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
void WolScenarioColorDlgClass::UpdateColorCombo()
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
    unsigned color = (selection >= 0 && selection < 8) ? ColorSchemes[selection] : DefaultSchemeColor;
    SendMessageA(control, GG_CBM_SETCOLOR, 0, color);
}

// FUNCTION: GAMEMD 0x5B9450
//
// The colour combo's selection changed. The tail is the same publish-and-repaint
// run as the reconcile above, without the advance-past-our-own-colour step.
//
// EXACT (47/47 instructions); same spelling as UpdateColorCombo.
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
    unsigned color = (selection >= 0 && selection < 8) ? ColorSchemes[selection] : DefaultSchemeColor;
    SendMessageA(control, GG_CBM_SETCOLOR, 0, color);
}
