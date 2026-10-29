// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x776D80 (name from the
//   YRpp method map).

#include "window_moving_methods.h"

// FUNCTION: GAMEMD 0x776D80
//
// WM_MOVING handler: clamp the proposed window rectangle to the primary
// screen, preserving its size. A negative left/top is shifted to zero; a
// right/bottom beyond the screen slides the rectangle back so its far edge
// sits on the screen edge. Returns whether anything was adjusted. Each
// GetSystemMetrics result is re-queried rather than cached, as retail does.
// Retail's callers load ECX/EDX before the call and push the RECT*, so the
// real convention is __fastcall with two unused register parameters; declared
// that way the body matches 100% (as __stdcall(rect) it stopped at 95.1%).
bool __fastcall OnWindowMoving(HWND__* hwnd, unsigned int edge, Rect_00776D80* rect)
{
    bool moved = false;

    if (rect->left < 0) {
        rect->right -= rect->left;
        rect->left = 0;
        moved = true;
    }
    if (rect->top < 0) {
        rect->bottom -= rect->top;
        rect->top = 0;
        moved = true;
    }
    if (rect->right > GetSystemMetrics(0x10)) {
        rect->left += GetSystemMetrics(0x10) - rect->right;
        rect->right = GetSystemMetrics(0x10);
        moved = true;
    }
    if (rect->bottom > GetSystemMetrics(0x11)) {
        rect->top += GetSystemMetrics(0x11) - rect->bottom;
        rect->bottom = GetSystemMetrics(0x11);
        return true;
    }
    return moved;
}
