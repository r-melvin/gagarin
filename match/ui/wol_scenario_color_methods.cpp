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
// PARTIAL (69.8%, 44/63) — register naming only. The mnemonic multiset is
// identical to retail's, instruction for instruction; retail parks the receiver
// in EDI and the control handle in EBX, and VC6 8804 hands them out the other
// way round, which reads as 19 divergent instructions plus the knock-on choice
// of temporary for the colour value in the two repaint arms. See the companion
// note on OnColorSelChanged for the variants tried; both functions are the same
// ESI/EDI-class tie-break already catalogued at 0x5B40B0 and 0x65C7E0.
void WolScenarioColorDlgClass::UpdateColorCombo()
{
    HWND_ dialog = this->Dialog;
    HWND_ control = GetDlgItem(dialog, 0x405);
    if (control != 0) {
        int selection = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
        if (selection != -1) {
            int taken = this->ColorIndex;
            if (selection == taken) {
                selection = taken + 1;
                if (selection > 7) {
                    selection = 0;
                }
                SendMessageA(control, GG_CB_SETCURSEL, selection, 0);
            }

            PlayerColor = selection;
            this->OptionsChanged = true;
            this->unknown_08 = true;

            if (selection >= 0 && selection < 8) {
                SendMessageA(control, GG_CBM_SETCOLOR, 0,
                             ColorSchemes[selection]);
            } else {
                SendMessageA(control, GG_CBM_SETCOLOR, 0, DefaultSchemeColor);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5B9450
//
// The colour combo's selection changed. The tail is the same publish-and-repaint
// run as the reconcile above, without the advance-past-our-own-colour step.
//
// PARTIAL (70.2%, 33/47) — register naming only; the mnemonic multiset is
// identical. Retail keeps `this` in ESI and the control handle in EDI; VC6 8804
// reverses them.
//
// Eleven materially different phrasings were measured, all at 70.2% or worse:
// early-return guards instead of nesting (66.0%), the colour value taken into a
// local before the send (66.0%), `this` parked in a local pointer (66.0%) or
// bound to a reference (70.2%), the range test spelled out-of-range-first
// (66.0%), the dirty bytes written before the global publish (61.7%), the range
// test with the clauses swapped (57.4%), a `__fastcall` free function with an
// explicit receiver parameter (70.2%), and the control re-taken into a fresh
// local for the repaint arms (70.2%). A flag sweep over /G3 /G5 /G6 /Ox /O1
// /Ob2 /Oa /Ow /Gf and dropping /GX moved nothing (/G6 and /O1 are worse).
//
// One thing the sweep did buy: hoisting `this->Dialog` into its own local is
// what makes VC6 reuse the dead selection register for the table load, exactly
// as retail does. Without it the table load lands in a fresh register and the
// score is 66.0%. The hoist is kept for that reason even though the receiver
// naming stays wrong.
void WolScenarioColorDlgClass::OnColorSelChanged()
{
    HWND_ dialog = this->Dialog;
    HWND_ control = GetDlgItem(dialog, 0x405);
    if (control != 0) {
        int selection = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
        if (selection != -1) {
            PlayerColor = selection;
            this->OptionsChanged = true;
            this->unknown_08 = true;

            if (selection >= 0 && selection < 8) {
                SendMessageA(control, GG_CBM_SETCOLOR, 0,
                             ColorSchemes[selection]);
            } else {
                SendMessageA(control, GG_CBM_SETCOLOR, 0, DefaultSchemeColor);
            }
        }
    }
}
