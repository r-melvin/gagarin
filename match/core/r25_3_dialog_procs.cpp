// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below.
//
// Address index: 0x773E30

#include <windows.h>

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog message handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);
// FUNCTION: GAMEMD 0x60C4A0 (decl; reloc) -- scale the dialog's children to the display (lParam: reference size).
void __fastcall FUN_0060C4A0(void* hWnd, long lParam);

// FUNCTION: GAMEMD 0x773E30
// Dialog procedure: let the shared handler answer; on WM_INITDIALOG that it left unhandled, scale the
// children from the 800x600 reference layout.
int __stdcall FUN_00773E30(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        if (msg == WM_INITDIALOG) {
            int size[2];
            size[0] = 800;
            size[1] = 600;
            FUN_0060C4A0(h, (long)size);
        }
        r = 0;
    }
    return r;
}
