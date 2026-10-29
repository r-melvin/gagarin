// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembled from retail gamemd.exe v1.001 at 0x52B9B0: dialog control 0x71A is looked up with
//   GetDlgItem (IAT 0x7E14A8), moved with SetWindowPos (IAT 0x7E13F0) and sent two messages
//   (SendMessageA, IAT 0x7E14A4). The display mode width/height are the globals 0x8A00A4/0x8A00A8.
//   FUNCTION: GAMEMD 0x52B9B0

#include <windows.h>
#include "center_window_methods.h"

// FUNCTION: GAMEMD 0x52B9B0
// Centres the banner control (id 0x71A) of a dialog on screens larger than 800x600, then sends it two
// messages: 1 as wParam of 0x4E3, and the name of the artwork set to use (the 640-wide set when the
// display is 640 pixels wide) with 0x4E4.
void __fastcall FUN_0052B9B0(HWND dialog)
{
    HWND banner = GetDlgItem(dialog, 0x71A);
    if (banner != 0) {
        int x;
        if (DAT_008A00A4 <= 800)
            x = 0;
        else
            x = (DAT_008A00A4 - 800) / 2;
        int y;
        if (DAT_008A00A8 <= 600)
            y = 0;
        else
            y = (DAT_008A00A8 - 600) / 2;
        SetWindowPos(banner, 0, x, y, -1, -1, 0xD);
        SendMessageA(banner, 0x4E3, 1, 0);
        if (DAT_008A00A4 == 640) {
            // STRING: GAMEMD 0x825CE8
            SendMessageA(banner, 0x4E4, 0, (LPARAM) "Ra2ts_s");
        } else {
            // STRING: GAMEMD 0x825CE0
            SendMessageA(banner, 0x4E4, 0, (LPARAM) "Ra2ts_l");
        }
    }
}
