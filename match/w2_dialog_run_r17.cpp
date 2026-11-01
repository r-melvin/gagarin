// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x55FA30 and 0x5FBEF0. Each opens a modal dialog
//   (UI::BeginDialog 0x622650), stores the address of a result word in the window's extra data, and
//   pumps the UI (0x623120 / 0x532100) until a dialog procedure fills the result in.
//
// Address index: 0x55FA30 0x5FBEF0

#include <windows.h>
#include "ui_begin_dialog_methods.h"

// FUNCTION: GAMEMD 0x55F980 (decl; reloc) -- the dialog procedure.
BOOL CALLBACK FUN_0055F980(HWND, UINT, WPARAM, LPARAM);
// FUNCTION: GAMEMD 0x5FB320 (decl; reloc) -- the dialog procedure.
BOOL CALLBACK FUN_005FB320(HWND, UINT, WPARAM, LPARAM);
// FUNCTION: GAMEMD 0x622800 (decl; reloc) -- UI::FocusOnWindow.
void __fastcall FUN_00622800(HWND window);
// FUNCTION: GAMEMD 0x622720 (decl; reloc) -- UI::EndDialog.
void __fastcall FUN_00622720(HWND window);
// FUNCTION: GAMEMD 0x623120 (decl; reloc) -- UI::Updated.
char __cdecl FUN_00623120();
// FUNCTION: GAMEMD 0x532100 (decl; reloc)
void __fastcall FUN_00532100(bool flag);

// GLOBAL: GAMEMD 0xA8E9A0
extern bool DAT_00A8E9A0;

// FUNCTION: GAMEMD 0x55FA30
// Run dialog 0xD9 until it reports a result; true when the result is 1.
bool __cdecl FUN_0055FA30()
{
    int result = -1;
    HWND window = UI_BeginDialog(0xD9, FUN_0055F980, 0);
    if (window != 0) {
        SetWindowLongA(window, 8, (LONG)&result);
        FUN_00622800(window);
        while (result < 0 && !FUN_00623120()) {
            FUN_00532100(false);
        }
        FUN_00622720(window);
    }
    return result == 1;
}

// FUNCTION: GAMEMD 0x5FBEF0
// Run dialog 0xA3; the UI being updated cancels it with result 2. Always true.
bool __cdecl FUN_005FBEF0()
{
    int result = -1;
    HWND window = UI_BeginDialog(0xA3, FUN_005FB320, 0);
    if (window != 0) {
        SetWindowLongA(window, 8, (LONG)&result);
        FUN_00622800(window);
        while (result < 0) {
            if (FUN_00623120() == 1) {
                result = 2;
            }
            if (!DAT_00A8E9A0) {
                FUN_00532100(false);
            }
        }
        FUN_00622720(window);
    }
    return true;
}
