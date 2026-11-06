// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit SerialEd.cpp. The name is the source-file string at 0x83ec28
//   in retail gamemd.exe v1.001, passed by the assert at 0x695f23 inside this object's
//   code range (0x6954e0-0x696d1f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <new.h>
#include "mathtbl_init_shapes.h"
#include <windows.h>
#include "ui_updated_methods.h"
#include "_rt/gg_static_assert.h"
#include "_layout/dialog_005d3490.h"
#include "vector_class_operations.h"
#include "vector_add_item_free.h"
#include "serial_ed_dialog.h"

// GLOBAL: GAMEMD 0x7F1180
extern const double DAT_007F1180;
// GLOBAL: GAMEMD 0xB05768
extern double DAT_00B05768;
// GLOBAL: GAMEMD 0xB057A0
extern double DAT_00B057A0;
// GLOBAL: GAMEMD 0xB057B8
extern double DAT_00B057B8;

// SYNTHETIC: GAMEMD 0x00695510
// dynamic initializer for DAT_00B057B8

// GLOBAL: GAMEMD 0x00B057B8
double DAT_00B057B8 = DAT_00B05768 / DAT_007F1180;

// SYNTHETIC: GAMEMD 0x00695530
// dynamic initializer for DAT_00B057A0

// GLOBAL: GAMEMD 0x00B057A0
double DAT_00B057A0 = 1.0 / DAT_00B057B8;

// SYNTHETIC: GAMEMD 0x006956B0
// GLOBAL: GAMEMD 0x00B057A8
MathTblCoord DAT_00B057A8;

// FUNCTION: GAMEMD 0x622650 (decl; reloc) -- UI::BeginDialog.
HWND __fastcall UI_BeginDialog(unsigned short id, int (__stdcall* proc)(HWND, unsigned int, unsigned int, long),
                               int param);
// FUNCTION: GAMEMD 0x622800 (decl; reloc) -- UI::FocusOnWindow.
void __fastcall UI_FocusOnWindow(HWND window);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void __fastcall FUN_00622720(HWND window);
// FUNCTION: GAMEMD 0x532100 (decl; reloc)
void __fastcall FUN_00532100(bool flag);
// FUNCTION: GAMEMD 0x695760 (decl; reloc) -- the dialog procedure.
int __stdcall FUN_00695760(HWND window, unsigned int message, unsigned int wParam, long lParam);

// FUNCTION: GAMEMD 0x6956D0
// Run the editor on a copy of the settings: the dialog stores its result (1 = accepted)
// in the object; on accept the edited settings are copied back to the caller.
bool SerialEdDialog_006956D0::FUN_006956D0(SerialSettings_006956D0* settings)
{
    Result = -1;
    Window = UI_BeginDialog(0xED, FUN_00695760, 0);
    if (Window) {
        SetWindowLongA(Window, DWL_USER, (LONG)this);
        FUN_00695FD0(settings);
        UI_FocusOnWindow(Window);
        while (Result < 0 && UI::Updated() != 1) {
            FUN_00532100(false);
        }
        FUN_00622720(Window);
        if (Result == 1) {
            *settings = Settings;
        }
    }
    bool accepted = Result == 1;
    return accepted;
}

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- StringTable::LoadString.
const wchar_t* __fastcall FUN_00734E60(const char* label, int* index, const char* file, int line);
// FUNCTION: GAMEMD 0x776E10 (decl; reloc) -- the combo entry whose data matches (window in ECX, -1 in EDX).
int __fastcall FUN_00776E10(HWND list, int start, int data);
// FUNCTION: GAMEMD 0x727CF0 (decl; reloc) -- normalise a text field in place.
void FUN_00727CF0(char* text);

// GLOBAL: GAMEMD 0x889F64 -- the empty string.
extern char DAT_00889F64[];
// GLOBAL: GAMEMD 0xA8DB68 -- the four entries offered by the list.
extern int* DAT_00A8DB68;
// GLOBAL: GAMEMD 0xA8DB4C -- the entries the list offers (strings).
extern DynamicVectorClass<char*> DAT_00A8DB4C;
// GLOBAL: GAMEMD 0x83EB58 -- the six baud labels.
extern const char* DAT_0083EB58[6];

// FUNCTION: GAMEMD 0x695FD0
// Take a copy of the settings, default the unset fields, and fill every control from them.
void SerialEdDialog_006956D0::FUN_00695FD0(SerialSettings_006956D0* settings)
{
    Settings = *settings;
    if (Settings.Port == 0) {
        Settings.Port = 0x2F8;
    }
    if (Settings.unknown_04 == -1) {
        Settings.unknown_04 = 3;
    }
    if (Settings.Baud == -1) {
        Settings.Baud = 0xE100;
    }
    FUN_00696200();
    FUN_006964C0();
    FUN_00696590();
    FUN_006966D0();
    if (DAT_00A8DB4C.Count == 0) {
        char* initial = new char[8];
        strcpy(initial, "ATZ");
        DynamicVectorAddItemFree(&DAT_00A8DB4C, initial);
        Settings.unknown_10 = 0;
    }
    FUN_00696610();
    HWND box = GetDlgItem(Window, 0x3EB);
    if (box) {
        SendMessageA(box, 0xF1, settings->unknown_18[0] != 0, 0);
    }
    box = GetDlgItem(Window, 0x3EA);
    if (box) {
        SendMessageA(box, 0xF1, settings->unknown_18[1] != 0, 0);
    }
}

// FUNCTION: GAMEMD 0x6964C0
// Fill the baud combo and select the entry for the settings' baud rate.
void SerialEdDialog_006956D0::FUN_006964C0()
{
    HWND combo = GetDlgItem(Window, 0x658);
    if (combo) {
        SendMessageA(combo, 0x14B, 0, 0);
        for (int i = 0; i < 6; i++) {
            const char* label = DAT_0083EB58[i];
            WPARAM added = SendMessageA(combo, 0x4C2, 0, (LPARAM)label);
            SendMessageA(combo, 0x151, added, i);
        }
        int data;
        switch (Settings.Baud) {
        case 0x3840:
            data = 0;
            break;
        case 0x4B00:
            data = 1;
            break;
        case 0x7080:
            data = 2;
            break;
        case 0xE100:
            data = 4;
            break;
        case 0x1C200:
            data = 5;
            break;
        default:
            data = 3;
            break;
        }
        int found = FUN_00776E10(combo, -1, data);
        SendMessageA(combo, 0x14E, found, 0);
    }
}

// FUNCTION: GAMEMD 0x696590
// Fill the four-entry list control and select the entry that matches the current selection.
void SerialEdDialog_006956D0::FUN_00696590()
{
    HWND list = GetDlgItem(Window, 0x659);
    if (list) {
        SendMessageA(list, 0x14B, 0, 0);
        int i = 0;
        do {
            int entry = DAT_00A8DB68[i];
            WPARAM added = SendMessageA(list, 0x4C2, 0, entry);
            SendMessageA(list, 0x151, added, i);
            i++;
        } while (i < 4);
        WPARAM found = FUN_00776E10(list, 0xFFFFFFFF, Settings.unknown_14);
        SendMessageA(list, 0x14E, found, 0);
    }
}

// FUNCTION: GAMEMD 0x696610
// Refill the list control (id 0x65E) from the global entries, then keep the remembered
// selection when it is still in range and otherwise reset it.
void SerialEdDialog_006956D0::FUN_00696610()
{
    HWND list = GetDlgItem(Window, 0x65E);
    if (list) {
        SendMessageA(list, 0x184, 0, 0);
        for (int i = 0; i < DAT_00A8DB4C.Count; i++) {
            SendMessageA(list, 0x4C8, 0, (LPARAM)DAT_00A8DB4C.Items[i]);
        }
        if (SendMessageA(list, 0x18B, 0, 0) == 0 || Settings.unknown_10 < -1) {
            Settings.unknown_10 = -1;
        } else if (Settings.unknown_10 >= SendMessageA(list, 0x18B, 0, 0)) {
            Settings.unknown_10 = 0;
        }
        if (Settings.unknown_10 != -1) {
            SendMessageA(list, 0x186, Settings.unknown_10, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x6966D0
// Set the two radio buttons (0x65C, 0x65B) from the mode selector: 0 selects the first, anything else the second.
void SerialEdDialog_006956D0::FUN_006966D0()
{
    bool first = Settings.unknown_0C == 0;
    HWND button = GetDlgItem(Window, 0x65C);
    if (button) {
        SendMessageA(button, 0xF1, first == 1, 0);
    }
    button = GetDlgItem(Window, 0x65B);
    if (button) {
        SendMessageA(button, 0xF1, !first, 0);
    }
}

// FUNCTION: GAMEMD 0x696740
// Show and enable a text control, filling it with the part of the entered text after the '-'.
void SerialEdDialog_006956D0::FUN_00696740(int id)
{
    HWND control = GetDlgItem(Window, id);
    if (control) {
        ShowWindow(control, 5);
        EnableWindow(control, 1);
        char* suffix = strchr(Text, '-');
        if (suffix) {
            suffix++;
            FUN_00727CF0(suffix);
        } else {
            suffix = DAT_00889F64;
        }
        SendMessageA(control, 0x4B4, 0, (LPARAM)suffix);
        SetFocus(control);
    }
}

// FUNCTION: GAMEMD 0x6967B0
// Take the typed port text: a known address or COM name selects its combo entry, any other text becomes a custom
// entry, and a COM name with an impossible number is refused.
void SerialEdDialog_006956D0::FUN_006967B0()
{
    HWND combo = GetDlgItem(Window, 0x657);
    HWND edit = GetDlgItem(Window, 0x65F);
    if (combo && edit) {
        ShowWindow(edit, 0);
        EnableWindow(edit, 0);
        SendMessageA(edit, 0x4B5, 0x40, (LPARAM)Text);
        Text[0x3F] = 0;
        FUN_00727CF0(Text);
        _strupr(Text);
        int data;
        if (_stricmp(Text, "3F8") != 0) {
            if (_stricmp(Text, "2F8") == 0) {
                data = 1;
            } else if (_stricmp(Text, "3E8") == 0) {
                data = 2;
            } else if (_stricmp(Text, "2E8") == 0) {
                data = 3;
            } else {
                if (strncmp(Text, "COM", 3) == 0) {
                    // Retail's jump table (0x69693C) sends '1'..'4' to the blocks of the 3F8/2F8/3E8/2E8 tests
                    // (0x69691B, 0x696844, 0x696860, 0x69687C), so the cases share them.
                    switch (Text[3]) {
                    case '1':
                        data = 0;
                        goto selected;
                    case '2':
                        data = 1;
                        goto selected;
                    case '3':
                        data = 2;
                        goto selected;
                    case '4':
                        data = 3;
                        goto selected;
                    default:
                        if (Text[3] > '9' || Text[3] <= '0') {
                            Dialog_005D3490 dialog;
                            dialog.FUN_005D3490(
                                FUN_00734E60("TXT_INVALID_PORT_ADDRESS", 0, "D:\\ra2mdpost\\SerialEd.cpp", 0x440),
                                FUN_00734E60("TXT_OK", 0, "D:\\ra2mdpost\\SerialEd.cpp", 0x440), 0, 0, 0);
                            return;
                        }
                        Text[4] = 0;
                        break;
                    }
                }
                FUN_006969C0(0x657, 4, Text);
                return;
            }
        } else {
            data = 0;
        }
    selected:
        int found = FUN_00776E10(combo, -1, data);
        SendMessageA(combo, 0x14E, found, 0);
    }
}

// FUNCTION: GAMEMD 0x696950
// Hide and disable the text control, read its text back into the entered text and refresh the list.
void SerialEdDialog_006956D0::FUN_00696950()
{
    HWND control = GetDlgItem(Window, 0x65A);
    if (control) {
        ShowWindow(control, 0);
        EnableWindow(control, 0);
        char* text = Text;
        SendMessageA(control, 0x4B5, 0x10, (LPARAM)text);
        Text[15] = 0;
        FUN_00727CF0(text);
        _strupr(text);
        FUN_006969C0(0x659, 3, text);
    }
}

// FUNCTION: GAMEMD 0x6969C0
// Relabel the combo entry holding the given data as custom, with the text after it, unless that text is already
// the part after its '-'.
void SerialEdDialog_006956D0::FUN_006969C0(int id, int data, char* text)
{
    HWND list = GetDlgItem(Window, id);
    if (list) {
        WPARAM index = FUN_00776E10(list, -1, data);
        char buffer[0x80];
        SendMessageA(list, 0x4BD, index, (LPARAM)buffer);
        char* dash = strchr(buffer, '-');
        if (dash) {
            if (_stricmp(text, dash + 1) != 0) {
                sprintf(buffer, "%ls ", FUN_00734E60("TXT_CUSTOM", 0, "D:\\ra2mdpost\\SerialEd.cpp", 0x4A3));
                strcat(buffer, text);
                SendMessageA(list, 0x144, index, 0);
                index = SendMessageA(list, 0x4BC, 0, (LPARAM)buffer);
                SendMessageA(list, 0x151, index, data);
                SendMessageA(list, 0x14E, index, 0);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x696AE0
// Take the typed list text: select the matching entry, adding it to the list when it is new.
void SerialEdDialog_006956D0::FUN_00696AE0()
{
    HWND edit = GetDlgItem(Window, 0x65D);
    HWND list = GetDlgItem(Window, 0x65E);
    if (edit == 0) {
        return;
    }
    if (list == 0) {
        return;
    }
    SendMessageA(edit, 0x4B5, 0x80, (LPARAM)Text);
    SendMessageA(edit, 0x4B4, 0, (LPARAM)DAT_00889F64);
    FUN_00727CF0(Text);
    if (strlen(Text) == 0) {
        return;
    }
    _strupr(Text);
    int index = SendMessageA(list, 0x4C4, -1, (LPARAM)Text);
    if (index == -1) {
        char* copy = new char[0x29];
        strcpy(copy, Text);
        index = SendMessageA(list, 0x4C8, 0, (LPARAM)copy);
        if (index == -1) {
            return;
        }
        DynamicVectorAddItemFree(&DAT_00A8DB4C, copy);
    }
    SendMessageA(list, 0x186, index, 0);
    SendMessageA(list, 0x197, index, 0);
    Settings.unknown_10 = index;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F1180
extern const double DAT_007F1180 = 60.0;
// END defined globals
