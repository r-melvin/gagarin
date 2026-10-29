// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x558A30 (0x155 bytes, RET 0x10).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
#include <windows.h>

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);
// FUNCTION: GAMEMD 0x607FD0 (decl; reloc)
void FUN_00607FD0(HWND h);
// FUNCTION: GAMEMD 0x776D80 (decl; reloc) -- the WM_MOVING clamp. Its caller
// sets up the register pair and passes the rectangle pointer on the stack.
bool __fastcall FUN_00776D80(HWND h, WPARAM w, LPARAM rect);

// FUNCTION: GAMEMD 0x558A30
// PARTIAL: 81.2% -- same instruction multiset except two je/jne pairs: retail tests the three
// command ids with forward je branches and bodies out of line; an if-chain nests them
// (a switch on the id adds two register copies, 7.9%).
// Dialog procedure: after the shared handler, repaint, clamp the window while
// it is being moved, record the chosen command and prime the list control.
int __stdcall FUN_00558A30(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        switch (msg) {
        case 0x111: {
            unsigned int notify = w >> 16;
            int id = w & 0xFFFF;
            int* data = (int*)GetWindowLongA(h, 8);
            if (id == 0x40F) {
                if (notify == 0) {
                    data[6] = 0x40F;
                    return 0;
                }
            } else if (id == 0x525) {
                if (notify == 2) {
                    LRESULT count = SendMessageA((HWND)l, 0x18B, 0, 0);
                    if (count > 0) {
                        data[6] = 0x40F;
                        return 0;
                    }
                }
            } else if (id == 0x686) {
                data[6] = 2;
                return 0;
            }
            break;
        }
        case 0xF:
            FUN_00607FD0(h);
            return 1;
        case 0x216:
            return FUN_00776D80(h, w, l);
        case 0x497:
            SendDlgItemMessageA(h, 0x525, 0x4A6, 0xF9, 2);
            SendDlgItemMessageA(h, 0x525, 0x4A6, 0x38, 0xFF);
            SendDlgItemMessageA(h, 0x525, 0x4A6, 0, 0x13B);
            break;
        }
        r = 0;
    }
    return r;
}
