// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and IAT slots read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x622800. The two indirect calls were resolved from the
//   binary's own import labels: 0x007E1498 is PTR_ShowWindow and 0x007E14D0 is
//   PTR_SetForegroundWindow. Signature cross-checked against YRpp UI.h
//   (`static void __fastcall FocusOnWindow(HWND)`, consult-only, no LICENSE).
#ifndef GG_MATCH_UI_UI_FOCUS_METHODS_H
#define GG_MATCH_UI_UI_FOCUS_METHODS_H

typedef struct HWND__* HWND;
#include "../platform/input_manager_class_methods.h"

// Bring the game window up and hand it the foreground.
// FUNCTION: GAMEMD 0x622800 (decl; reloc)
void __fastcall UI_FocusOnWindow(HWND hWnd);

#endif  // GG_MATCH_UI_UI_FOCUS_METHODS_H
