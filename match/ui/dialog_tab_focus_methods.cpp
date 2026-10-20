// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x600C70.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x600C70  FUN_00600C70 (__fastcall)
//   GLOBAL:   GAMEMD 0x7E14EC  __imp__GetParent
//   GLOBAL:   GAMEMD 0x7E14F0  __imp__GetNextDlgTabItem
//   GLOBAL:   GAMEMD 0x7E13CC  __imp__SetFocus

#include "dialog_tab_focus_methods.h"

// FUNCTION: GAMEMD 0x600C70  FUN_00600C70 (__fastcall)
// Move the dialog keyboard focus one tab stop away from `hCtl`, forwards or
// (with `bPrevious`) backwards, and report whether the focus actually moved.
// When the control is the only tab stop in its parent, GetNextDlgTabItem hands
// back the same window and the focus is left alone.
bool __fastcall FUN_00600C70(GG_HWND hCtl, unsigned char bPrevious)
{
    // GetParent must be its own statement: nested inside the argument list it
    // costs the whole register assignment (4.8%), because cl then widens the
    // flag before the call instead of holding it raw in ESI across it.
    GG_HWND hParent = GetParent(hCtl);
    GG_HWND hNext = GetNextDlgTabItem(hParent, hCtl, bPrevious);

    if (hNext != hCtl)
    {
        SetFocus(hNext);
        return true;
    }

    return false;
}
