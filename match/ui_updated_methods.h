// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + behaviour derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (disasm at 0x623120), cross-checked against YRpp
//   (every global/branch reconfirmed from the disasm).
//
// UI::Updated — the per-frame "should we keep pumping the main loop?" gate used
// by the modeless reconnect/wait dialogs. It is a static (no `this`) bool that
// reads four engine globals and two helper predicates. Only that one method is
// modelled here; no instance members are touched.
#ifndef GG_MATCH_UI_UPDATED_METHODS_H
#define GG_MATCH_UI_UPDATED_METHODS_H

struct UI
{
    static bool Updated();
};

#endif // GG_MATCH_UI_UPDATED_METHODS_H
