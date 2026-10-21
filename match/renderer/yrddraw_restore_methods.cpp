// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x4A44F0.

#include <windows.h>
#include <stdio.h>
#include "yrddraw_restore_methods.h"

// FUNCTION: GAMEMD 0x4A44F0  YRDDraw::Restore
//
// Give the display back: restore the display mode and release the DirectDraw
// object, reporting either failure through the error callback when one is
// installed and through a message box otherwise. The mode record is cleared
// between the two and the object pointer afterwards.
void YRDDraw_Restore()
{
    if (DAT_008A0094 != 0) {
        char text[80];
        long hr = DAT_008A0094->lpVtbl->RestoreDisplayMode(DAT_008A0094);
        int (WINAPI* box)(HWND, LPCSTR, LPCSTR, UINT) = MessageBoxA;
        if (hr != 0) {
            if (DAT_008A00B0 != 0) {
                DAT_008A00B0(hr);
            } else {
                // STRING: GAMEMD 0x81FC7C
                sprintf(text, "DDRAW.DLL Error code = %08X", hr);
                // STRING: GAMEMD 0x81FC70
                box((HWND)DAT_00B73550, text, "Direct X", 0x30);
            }
        }

        DAT_008A00A4 = 0;
        DAT_008A00A8 = 0;
        DAT_008A00AC = 0;

        hr = DAT_008A0094->lpVtbl->Release(DAT_008A0094);
        if (hr != 0) {
            if (DAT_008A00B0 != 0) {
                DAT_008A00B0(hr);
            } else {
                sprintf(text, "DDRAW.DLL Error code = %08X", hr);
                box((HWND)DAT_00B73550, text, "Direct X", 0x30);
            }
        }
        DAT_008A0094 = 0;
    }
}
