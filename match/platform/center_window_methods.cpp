// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x777080.

#include "center_window_methods.h"

// FUNCTION: GAMEMD 0x777080
//
// Centre `child` inside `parent`. Both client rectangles are taken to screen
// space and reduced to (origin, extent); when the parent is the main game
// window its extent is the display mode rather than the client rectangle
// (full-screen DirectDraw leaves the client rectangle meaningless). The
// resulting offset is clamped at zero on each axis and applied without a
// resize or a z-order change.
void Unsorted_CenterWindowIn(HWND child, HWND parent)
{
    RECT outer;
    RECT inner;

    GetClientRect(parent, &outer);
    if (parent == DAT_00B73550) {
        outer.right  = DAT_008A00A4;
        outer.bottom = DAT_008A00A8;
    }
    ClientToScreen(parent, (POINT*)&outer.left);
    ClientToScreen(parent, (POINT*)&outer.right);
    outer.right  -= outer.left;
    outer.bottom -= outer.top;

    GetClientRect(child, &inner);
    ClientToScreen(child, (POINT*)&inner.left);
    ClientToScreen(child, (POINT*)&inner.right);
    inner.right  -= inner.left;
    inner.bottom -= inner.top;

    int x = (outer.right - inner.right + 1) / 2;
    int y = (outer.bottom - inner.bottom + 1) / 2;
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    SetWindowPos(child, 0, x, y, -1, -1, SWP_NOSIZE | SWP_NOZORDER);
}
