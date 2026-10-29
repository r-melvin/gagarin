// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x52D640 (0x148 bytes, RET 0x10).
#include <windows.h>
#include "../_layout/load_options_class.h"

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);

// FUNCTION: GAMEMD 0x52D640
// Dialog procedure for the main-menu style screen: on init enable the "load game" button only
// when the save directory holds saves, and on a button command store its result code through the
// window's user data.
int __stdcall FUN_0052D640(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        int* data = (int*)GetWindowLongA(h, 8);
        switch (msg) {
        case 0x111: {
            int id = w & 0xFFFF;
            switch (id) {
            case 0x686:
                *data = 0x12;
                return 0;
            case 0x579:
                *data = 0xB;
                return 0;
            case 0x688:
                *data = 8;
                return 0;
            case 0x68A:
                *data = 0xA;
                return 0;
            case 0x689:
                *data = 9;
                return 0;
            }
            break;
        }
        case 0xF:
        {
            HWND item = GetDlgItem(h, 0x71A);
            SendMessageA(item, 0x4F0, 0, 0);
            break;
        }
        case 0x497: {
            HWND button = GetDlgItem(h, 0x689);
            if (button != 0) {
                bool hasSaves = LoadOptionsClass().FUN_00559C20();
                EnableWindow(button, hasSaves);
                return 0;
            }
            break;
        }
        }
        r = 0;
    }
    return r;
}
