// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x46FB50.

#include "dialog_enable_methods.h"

// FUNCTION: GAMEMD 0x46FB50
//
// Enable or disable two dialog controls according to how full the list is.
// Below capacity, the first control is disabled and the second enabled; at
// capacity, only the first is touched and its state comes from the current
// slot's own flag.
//
// Both controls are fetched before either is tested, so the second lookup
// happens even on the path that never uses it.
void __fastcall FUN_0046FB50(HWND_ dlg)
{
    HWND_ first = GetDlgItem(dlg, 0x6D1);
    HWND_ second = GetDlgItem(dlg, 0x5C0);

    if (first == 0) {
        return;
    }

    if (DAT_00A8DA84 < DAT_00A8D580) {
        EnableWindow(first, 0);
        if (second == 0) {
            return;
        }
        EnableWindow(second, 1);
        return;
    }

    if (DAT_0089E000[DAT_00A8DA8C]) {
        EnableWindow(first, 0);
        return;
    }

    EnableWindow(first, 1);
}
