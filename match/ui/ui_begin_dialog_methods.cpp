// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x622650.

#include <windows.h>
#include "ui_begin_dialog_methods.h"

// FUNCTION: GAMEMD 0x622650  UI::BeginDialog (__fastcall, ret 4)
//
// Open a modeless dialog from an embedded DIALOG resource. The template is
// looked up by id; a fresh slot is reserved on top of the open-dialog stack
// (cleared first), and the window is created with the main window as its
// parent and a small {id, param} block as the LPARAM. On failure the reserved
// slot is given back; on success it is filled in, the window is registered,
// and it becomes the current dialog.
//
// The slot is addressed as `DAT_00B72D28[i].Window` / `.Id` through an int
// index local, which is what keeps the two LEAs (EDI/EBX) apart and live
// across the call; a `DialogEntry*` local folds them into one base register
// (19.7%). The count bump is a standalone `DAT_00B72F50++` after the two
// zero-stores: `int i = DAT_00B72F50++` copies the index first (29.9%) and
// `DAT_00B72F50 = i + 1` becomes an LEA (83.3%); only the standalone
// increment INCs the already-consumed index register in place.
void* __fastcall UI_BeginDialog(unsigned short id, DlgProc_00622650 proc, int param)
{
    void* tmpl = FUN_004A3B40(id, (const char*)5);
    if (tmpl == 0)
        return 0;

    int i = DAT_00B72F50;
    DAT_00B72D28[i].Window = 0;
    DAT_00B72D28[i].Id = 0;
    DAT_00B72F50++;

    DialogInit_00622650 init;
    init.Id = id;
    init.Param = param;

    void* hWnd = CreateDialogIndirectParamA((HINSTANCE)DAT_00B732F0, (LPCDLGTEMPLATEA)tmpl,
                                            (HWND)DAT_00B73550, (DLGPROC)proc, (LPARAM)&init);
    if (hWnd == 0) {
        DAT_00B72F50--;
        return 0;
    }

    DAT_00B72D28[i].Window = hWnd;
    DAT_00B72D28[i].Id = id;
    FUN_005D4E70(hWnd);
    DAT_00B72F44 = hWnd;
    DAT_00B72F48 = id;
    return hWnd;
}
