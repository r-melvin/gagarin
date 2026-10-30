// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies disassembled from retail gamemd.exe v1.001 at the addresses below.
//
// Address index:
//   0x775B50  FUN_00775B50
//   0x7768A0  FUN_007768A0
//   0x776CD0  FUN_00776CD0
//   0x776E10  FUN_00776E10

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/ini_class.h"

// GLOBAL: GAMEMD 0xB732F0 -- the module instance handle.
extern HINSTANCE DAT_00b732f0;

// FUNCTION: GAMEMD 0x775B50
// Measures a dialog template: creates it modelessly, reads its client size, destroys it.
int __fastcall FUN_00775B50(unsigned int templateId, DLGPROC proc, int unused, LONG* size)
{
    HWND dialog = CreateDialogParamA(DAT_00b732f0, (LPCSTR)(templateId & 0xFFFF), 0, proc, 0);
    RECT rect;
    GetClientRect(dialog, &rect);
    DestroyWindow(dialog);
    size[0] = rect.right;
    size[1] = rect.bottom;
    return 1;
}

// STRING: GAMEMD 0x849E2C -- "SUN.HLP"
extern const char HelpFile_00849E2C[];

// FUNCTION: GAMEMD 0x7768A0
// Shows the context-menu help for a control: its id and its context help id.
void __fastcall FUN_007768A0(HWND window)
{
    DWORD ids[4] = {0, 0, 0, 0};
    ids[0] = GetWindowLongA(window, GWL_ID);
    ids[1] = GetWindowContextHelpId(window);
    WinHelpA(window, HelpFile_00849E2C, HELP_CONTEXTMENU, (DWORD)ids);
}

// STRING: GAMEMD 0x84968C -- "X"
extern const char Key_0084968C[];
// STRING: GAMEMD 0x849E64 -- "Y"
extern const char Key_00849E64[];
// GLOBAL: GAMEMD 0xB73098 -- the section the child enumeration writes into.
extern const char* DAT_00B73098;

// FUNCTION: GAMEMD 0x776B40 (decl; reloc) -- EnumChildWindows callback.
BOOL CALLBACK FUN_00776B40(HWND window, LPARAM param);

// FUNCTION: GAMEMD 0x776CD0
// Saves a window's position into `ini` under `section`, then enumerates its children.
void __fastcall FUN_00776CD0(const char* section, HWND window, INIClass* ini)
{
    if (window != 0) {
        RECT rect;
        GetWindowRect(window, &rect);
        ini->WriteInteger(section, Key_0084968C, rect.left, 0);
        ini->WriteInteger(section, Key_00849E64, rect.top, 0);
        DAT_00B73098 = section;
        EnumChildWindows(window, FUN_00776B40, (LPARAM)ini);
    }
}

// FUNCTION: GAMEMD 0x776E10
// Index (from `start`) of the combo-box entry whose item data equals `data`, or -1.
int __fastcall FUN_00776E10(HWND combo, int start, int data)
{
    int count = SendMessageA(combo, CB_GETCOUNT, 0, 0);
    for (; start < count; start++) {
        if (SendMessageA(combo, CB_GETITEMDATA, start, 0) == data)
            return start;
    }
    return -1;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x84968C
extern const char Key_0084968C[] = "X";
// GLOBAL: GAMEMD 0x849E64
extern const char Key_00849E64[] = "Y";
// END defined globals
