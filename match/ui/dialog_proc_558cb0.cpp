// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x558CB0 (0x115 bytes, RET 0x10).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
#include <windows.h>

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);
// FUNCTION: GAMEMD 0x607FD0 (decl; reloc)
void FUN_00607FD0(HWND h);
// FUNCTION: GAMEMD 0x776D80 (decl; reloc) -- the WM_MOVING clamp (ECX=window, EDX=edge, rect on the stack).
#include "../platform/window_moving_methods.h"

// FUNCTION: GAMEMD 0x558CB0
// Dialog procedure: after the shared handler, clamp the window while it is
// being moved, repaint, set the result code for two buttons and prime the
// list control's three settings.
int __stdcall FUN_00558CB0(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        switch (msg) {
        case 0x111: {
            unsigned int notify = w >> 16;
            int* data = (int*)GetWindowLongA(h, 8);
            switch (w & 0xFFFF) {
            case 0x686:
                if (notify == 0) {
                    data[6] = 2;
                    return 0;
                }
                break;
            case 0x6C8:
                if (notify == 0) {
                    data[6] = 1;
                    return 0;
                }
                break;
            }
            break;
        }
        case 0xF:
            FUN_00607FD0(h);
            return 1;
        case 0x216:
            return OnWindowMoving(h, w, (Rect_00776D80*)l);
        case 0x497:
            SendDlgItemMessageA(h, 0x528, 0x4A6, 0xF9, 2);
            SendDlgItemMessageA(h, 0x528, 0x4A6, 0x38, 0xFF);
            SendDlgItemMessageA(h, 0x528, 0x4A6, 0, 0x13B);
            break;
        }
        r = 0;
    }
    return r;
}
