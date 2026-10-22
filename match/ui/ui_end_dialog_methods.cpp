// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x622720.

#include <windows.h>
#include <string.h>
#include "ui_end_dialog_methods.h"

#pragma function(memcpy)

// FUNCTION: GAMEMD 0x622720  UI::EndDialog
//
// Tear a dialog down: reset input, detach its gadgets, destroy the window,
// then pull its entry out of the open-dialog stack (sliding the later ones
// down and clearing the freed slot). Whatever is now on top becomes the
// current dialog and takes focus; with the stack empty the main window does.
//
// The search is a plain `for` whose bound is the count global read in the
// condition (VC6 hoists it into EDX itself) with a `goto` out to the found
// block, so the not-found path is the loop's own fall-through into the
// epilogue and the found block sits after it. A `count` local swaps the
// count and pointer registers (82.1%); a pointer local costs EBX; the
// do/while and while forms rotate the loop the wrong way round.
void UI_EndDialog(void* hWnd)
{
    DAT_0087F770->DoSomething();
    FUN_00608070(hWnd);
    DestroyWindow((HWND)hWnd);

    int i;
    for (i = 0; i < DAT_00B72F50; ++i) {
        if (DAT_00B72D28[i].Window == hWnd)
            goto found;
    }
    return;

found:
    {
        memcpy(&DAT_00B72D28[i], &DAT_00B72D28[i + 1],
               (DAT_00B72F50 - (i + 1)) * sizeof(DialogEntry_00622720));
        DAT_00B72D28[DAT_00B72F50 - 1].Window = 0;
        DAT_00B72D28[DAT_00B72F50 - 1].Id = 0;
        DAT_00B72F50--;

        if (DAT_00B72F50 > 0) {
            DAT_00B72F44 = DAT_00B72D28[DAT_00B72F50 - 1].Window;
            DAT_00B72F48 = DAT_00B72D28[DAT_00B72F50 - 1].Id;
            SetForegroundWindow((HWND)DAT_00B72F44);
            SetFocus((HWND)DAT_00B72F44);
        } else {
            DAT_00B72F44 = 0;
            DAT_00B72F48 = 0;
            SetForegroundWindow((HWND)DAT_00B73550);
            SetFocus((HWND)DAT_00B73550);
        }
    }
}
