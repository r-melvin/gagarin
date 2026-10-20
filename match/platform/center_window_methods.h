// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and imports read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x777080: the child window in ECX and the
//   parent in EDX (__fastcall), the main window at 0xB73550 and the display
//   mode width/height at 0x8A00A4/0x8A00A8 substituted for the parent's
//   client extent, the IAT slots 0x7E14C4 (GetClientRect, loaded once into
//   EBP), 0x7E14B8 (ClientToScreen, loaded once into ESI) and 0x7E13F0
//   (SetWindowPos, called through the IAT with SWP_NOSIZE|SWP_NOZORDER = 5).
//   The name comes from the YRpp method map (Unsorted::CenterWindowIn,
//   static; consult-only).
#ifndef GG_MATCH_PLATFORM_CENTER_WINDOW_METHODS_H
#define GG_MATCH_PLATFORM_CENTER_WINDOW_METHODS_H

#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xB73550 -- the main window (Unsorted::hWnd).
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x8A00A4 / 0x8A00A8 -- display mode width and height.
extern int DAT_008A00A4;
extern int DAT_008A00A8;

// FUNCTION: GAMEMD 0x777080 -- Unsorted::CenterWindowIn (static, __fastcall).
void __fastcall Unsorted_CenterWindowIn(HWND child, HWND parent);

#endif  // GG_MATCH_PLATFORM_CENTER_WINDOW_METHODS_H
