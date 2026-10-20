// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x622800.

#include "ui_focus_methods.h"

// Win32 imports reached through the IAT (`CALL dword ptr [0x007E1498]` and
// `CALL dword ptr [0x007E14D0]`).
extern "C" __declspec(dllimport) int __stdcall ShowWindow(HWND hWnd, int nCmdShow);
extern "C" __declspec(dllimport) int __stdcall SetForegroundWindow(HWND hWnd);

// FUNCTION: GAMEMD 0x622800  UI::FocusOnWindow (__fastcall)
void __fastcall UI_FocusOnWindow(HWND hWnd)
{
    ShowWindow(hWnd, 1);            // SW_SHOWNORMAL
    SetForegroundWindow(hWnd);
    WindowFocusSinkPtr->OnWindowFocused();
}
