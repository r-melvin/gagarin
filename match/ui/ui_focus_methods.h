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

// The object behind the pointer at 0x0087F770, whose method at 0x0054F720 the
// focus path pokes after raising the window. Declared opaque: only the
// `MOV ECX,[0x87F770]; CALL 0x54F720` shape matters here.
struct WindowFocusSink
{
    void OnWindowFocused();     // GAMEMD 0x54F720 __thiscall (declared; reloc)
};

// GLOBAL: GAMEMD 0x0087F770
extern WindowFocusSink* WindowFocusSinkPtr;

// Bring the game window up and hand it the foreground.
void __fastcall UI_FocusOnWindow(HWND hWnd);   // GAMEMD 0x622800

#endif  // GG_MATCH_UI_UI_FOCUS_METHODS_H
