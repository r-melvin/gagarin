// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x5D36A0 (0xB3 bytes, RET 0x10).
#include <windows.h>

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);
// FUNCTION: GAMEMD 0x776D80 (decl; reloc) -- the WM_MOVING clamp (ECX=window, EDX=edge, rect on the stack).
#include "../platform/window_moving_methods.h"

// FUNCTION: GAMEMD 0x5D36A0
// Dialog procedure: after the shared handler, store the result code for the
// buttons through the window's user data and clamp the window while it moves.
int __stdcall FUN_005D36A0(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        switch (msg) {
        case 0x111: {
            unsigned int notify = w >> 16;
            unsigned int* data = (unsigned int*)GetWindowLongA(h, 8);
            int id = w & 0xFFFF;
            switch (id) {
            case 0x5AE:
                if (notify == 0) {
                    *data = 0;
                    return 0;
                }
                break;
            case 0x5AF:
                if (notify == 0) {
                    *data = 2;
                }
                break;
            case 1:
            case 2:
                if (notify == 0) {
                    *data = 1;
                    return 0;
                }
                break;
            }
            break;
        }
        case 0x216:
            return OnWindowMoving(h, w, (Rect_00776D80*)l);
        }
        r = 0;
    }
    return r;
}
