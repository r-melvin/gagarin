// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x4C83E0, 0x4C84E0, 0x4C8FE0 and 0x4C9160.
//   Original translation unit: the exception-handling block that follows the header initialisers
//   at 0x4C81F0 (unnamed in the TU map; sorts between Event.CPP and GameDlg.CPP).
//   Functions in ascending retail address order.

#include <windows.h>
#include <conio.h>
#include "center_window_methods.h"
#include "debug_window_list_methods.h"
#include "streamer_thread_flush_methods.h"
#include "resource_query_methods.h"
#include "window_moving_methods.h"
#include "yrddraw_dispose_methods.h"
#include "composite_surface.h"
#include "ccfile_class.h"

// GLOBAL: GAMEMD 0x8A3A08 -- the exception text buffer.
extern char DAT_008A3A08[];
// GLOBAL: GAMEMD 0x820E5C -- exception nesting count.
extern int DAT_00820E5C;
// GLOBAL: GAMEMD 0x820E60
extern char DAT_00820E60;
// GLOBAL: GAMEMD 0x887624 -- set when the 9x (VWIN32) path is used.
extern char DAT_00887624;
// GLOBAL: GAMEMD 0xB730E8 -- main thread id.
extern DWORD DAT_00B730E8;
// GLOBAL: GAMEMD 0xB732F0
extern HINSTANCE DAT_00B732F0;
// GLOBAL: GAMEMD 0xB72F44
extern void* DAT_00B72F44;

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc)
extern "C" void __cdecl FUN_004068E0(const char* text);
// FUNCTION: GAMEMD 0x4C85E0 (decl; reloc)
void __fastcall FUN_004C85E0(void* info);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void UI_EndDialog(void* window);

// FUNCTION: GAMEMD 0x4C83E0
BOOL __stdcall lpDialogFunc_004C83E0(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_INITDIALOG:
        FUN_004068E0("WM_INITDIALOG\n");
        SetDlgItemTextA(hDlg, 0x484, DAT_008A3A08);
        SetFocus(hDlg);
        if (DAT_00B73550) {
            Unsorted_CenterWindowIn(hDlg, DAT_00B73550);
        }
        ShowWindow(hDlg, 1);
        FUN_0053E3C0(hDlg);
        return 0;
    case WM_CLOSE:
        EndDialog(hDlg, 0x481);
        FUN_0053E420(hDlg);
        return 0;
    case WM_COMMAND:
        switch (wParam & 0xFFFF) {
        case 0x47D:
            MessageBoxA(hDlg,
                        "Sorry, you can only attempt an emergency save if you were in the map editor when the exception occurred.\t",
                        "Bummer", 0x30);
            return 0;
        case 0x481:
            EndDialog(hDlg, 0x481);
            return 0;
        }
        break;
    case WM_MOVING:
        return OnWindowMoving(hDlg, wParam, (Rect_00776D80*)lParam) & 0xFF;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4C84E0
int FUN_004C84E0()
{
    FUN_0053E6B0();
    switch (DAT_00820E5C) {
    case 1:
        if (!AllocConsole()) {
            FreeConsole();
            AllocConsole();
        }
        _cprintf("Error - Recursive exception detected. Program halted.\r\n See EXCEPT.TXT file for details\r\r\n");
        Sleep(4000);
        _getch();
        FreeConsole();
        return 0x481;
    case 2:
        return 0x481;
    case 3:
        ExitProcess(0);
        return 0x481;
    }
    ShowCursor(1);
    void* tmpl = Unsorted_GetResource(0xF7, (const char*)5);
    int r;
    if (tmpl) {
        FUN_004068E0("Resource found\n");
        r = DialogBoxIndirectParamA(DAT_00B732F0, (LPCDLGTEMPLATEA)tmpl, DAT_00B73550,
                                    lpDialogFunc_004C83E0, 0);
    } else {
        FUN_004068E0("Resource not found\n");
        r = DialogBoxParamA(DAT_00B732F0, MAKEINTRESOURCE(0xF7), DAT_00B73550,
                            lpDialogFunc_004C83E0, 0);
    }
    ShowCursor(0);
    return r;
}

// FUNCTION: GAMEMD 0x4C8FE0
int __fastcall FUN_004C8FE0(int unused, void* info)
{
    FUN_004068E0("Exception!\n");
    FUN_0053E6B0();
    if (++DAT_00820E5C == 0) {
        FUN_004C85E0(info);
        HANDLE h = CreateFileA("except.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        if (h != INVALID_HANDLE_VALUE) {
            DWORD written;
            WriteFile(h, DAT_008A3A08, lstrlenA(DAT_008A3A08), &written, 0);
            CloseHandle(h);
        }
    }
    if (((DAT_00887308 && DAT_00887308->IsLocked()) || (DAT_0088730C && DAT_0088730C->IsLocked())
         || (DAT_0088731C && DAT_0088731C->IsLocked()) || (DAT_008872FC && DAT_008872FC->IsLocked())
         || (DAT_00887300 && DAT_00887300->IsLocked()) || (DAT_00887310 && DAT_00887310->IsLocked()))
            && DAT_00887624
        || GetCurrentThreadId() != DAT_00B730E8) {
        FUN_004068E0("Can't bring up exception dialog due to Win16 mutex or threading issues\n");
        return 0;
    }
    FUN_004068E0("Exception_Dialog()\n");
    if (FUN_004C84E0() != 0x481) {
        return 0;
    }
    DAT_00820E60 = 0;
    if (DAT_00820E5C == 0) {
        DAT_00820E5C = -1;
    } else if (DAT_00820E5C == 2) {
        return 0;
    }
    if (DAT_00B72F44) {
        UI_EndDialog(DAT_00B72F44);
    }
    return 1;
}

// FUNCTION: GAMEMD 0x4C9160
bool FUN_004C9160()
{
    CCFileClass file("EXPAND.DAT");
    return file.Exists(0);
}
