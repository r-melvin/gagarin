// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x558B90 (0x117 bytes).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
#include <windows.h>

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);
// FUNCTION: GAMEMD 0x607FD0 (decl; reloc)
void FUN_00607FD0(HWND h);
// FUNCTION: GAMEMD 0x776D80 (decl; reloc) -- the WM_MOVING clamp (ECX=window, EDX=edge, rect on the stack).
#include "../platform/window_moving_methods.h"
// FUNCTION: GAMEMD 0x5588E0 (decl; reloc)
void FUN_005588E0(HWND h, unsigned int id, LPARAM control, unsigned int notify);

// FUNCTION: GAMEMD 0x558B90
// Dialog procedure: repaint, clamp the window while it is being moved,
// forward commands, prime both list controls and latch the result code.
int __stdcall FUN_00558B90(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        switch (msg) {
        case 0x111:
            FUN_005588E0(h, w & 0xFFFF, l, w >> 16);
            return 0;
        case 0xF:
            FUN_00607FD0(h);
            return 1;
        case 0x216:
            return OnWindowMoving(h, w, (Rect_00776D80*)l);
        case 0x497: {
            SendMessageA(GetDlgItem(h, 0x526), 0xC5, 0x4F, 0);
            SendDlgItemMessageA(h, 0x527, 0x4A6, 0xF9, 2);
            SendDlgItemMessageA(h, 0x527, 0x4A6, 0x38, 0xFF);
            SendDlgItemMessageA(h, 0x527, 0x4A6, 0, 0x13B);
            break;
        }
        case 0x4DA: {
            int* data = (int*)GetWindowLongA(h, 8);
            data[6] = 1;
            return 0;
        }
        }
        r = 0;
    }
    return r;
}
