// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x776D80: the four RECT members `[ESI]`, `[ESI+0x4]`,
//   `[ESI+0x8]`, `[ESI+0xC]`, the IAT slot 0x7E13EC (GetSystemMetrics,
//   called with 0x10 = SM_CXSCREEN and 0x11 = SM_CYSCREEN) and the
//   `RET 4` __stdcall epilogue. The name comes from the YRpp method map
//   (Unsorted::OnWindowMoving, static; consult-only).
#ifndef GG_MATCH_PLATFORM_WINDOW_MOVING_METHODS_H
#define GG_MATCH_PLATFORM_WINDOW_MOVING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rect_00776D80
{
    int left;     // +0x0000
    int top;      // +0x0004
    int right;    // +0x0008
    int bottom;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(Rect_00776D80, right) == 0x8);
GG_STATIC_ASSERT(offsetof(Rect_00776D80, bottom) == 0xC);
GG_STATIC_ASSERT(sizeof(Rect_00776D80) == 0x10);

// GetSystemMetrics via the IAT (indirect call, normalised). IAT 0x7E13EC.
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int nIndex);

// FUNCTION: GAMEMD 0x776D80  (__stdcall)
bool __stdcall OnWindowMoving(Rect_00776D80* rect);

#endif  // GG_MATCH_PLATFORM_WINDOW_MOVING_METHODS_H
