// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x52D790 (0xB8 bytes, RET 0x10).
#include <windows.h>

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);

// FUNCTION: GAMEMD 0x52D790
// Dialog procedure: let the shared handler answer first. Otherwise a paint
// message pokes the list control, and the four menu commands store their
// result code through the window's user data.
int __stdcall FUN_0052D790(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        unsigned int* data = (unsigned int*)GetWindowLongA(h, 8);
        switch (msg) {
        case 0x111:
            switch (w & 0xFFFF) {
            case 0x68D:
                *data = 0xD;
                return 0;
            case 0x68E:
                *data = 0xE;
                return 0;
            case 0x68F:
                *data = 0xF;
                return 0;
            case 0x686:
                *data = 0x12;
                return 0;
            }
            break;
        case 0xF:
            {
                HWND item = GetDlgItem(h, 0x71A);
                SendMessageA(item, 0x4F0, 0, 0);
            }
            break;
        }
        r = 0;
    }
    return r;
}
