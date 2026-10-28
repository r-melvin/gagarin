// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x52D5B0 (a dialog procedure that only reacts to WM_COMMAND).
//
// Three-button dialog procedure. Address index: 0x52D5B0.
#include <windows.h>

// FUNCTION: GAMEMD 0x52D5B0
// Close the dialog with a result per button: control 2 (cancel) gives 0, 0x53A gives 1 and
// 0x53B gives 2. Everything else is left to the default handling.
BOOL CALLBACK FUN_0052D5B0(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_COMMAND) {
        switch (wParam) {
        case 2:
            EndDialog(hwnd, 0);
            break;
        case 0x53A:
            EndDialog(hwnd, 1);
            return 0;
        case 0x53B:
            EndDialog(hwnd, 2);
            return 0;
        }
    }
    return 0;
}
