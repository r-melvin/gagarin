// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit PhoneEd.cpp. The name is the source-file string at 0x836778
//   in retail gamemd.exe v1.001, passed by the assert at 0x630f61 inside this object's
//   code range (0x6309a0-0x631c7f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "mathtbl_init_shapes.h"
#include <windows.h>
#include "ui_updated_methods.h"
#include "_layout/session_class.h"
#include "_rt/gg_static_assert.h"
#include "serial_ed_dialog.h"
#include <string.h>
#include <wchar.h>

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EFD90
extern const double DAT_007EFD90;
// GLOBAL: GAMEMD 0xAC4AD0
extern double DAT_00AC4AD0;
// GLOBAL: GAMEMD 0xAC4B08
extern double DAT_00AC4B08;
// GLOBAL: GAMEMD 0xAC4B20
extern double DAT_00AC4B20;

// SYNTHETIC: GAMEMD 0x006309D0
// dynamic initializer for DAT_00AC4B20

// GLOBAL: GAMEMD 0x00AC4B20
double DAT_00AC4B20 = DAT_00AC4AD0 / DAT_007EFD90;

// SYNTHETIC: GAMEMD 0x006309F0
// dynamic initializer for DAT_00AC4B08

// GLOBAL: GAMEMD 0x00AC4B08
double DAT_00AC4B08 = DAT_007E1718 / DAT_00AC4B20;

// SYNTHETIC: GAMEMD 0x00630B70
// GLOBAL: GAMEMD 0x00AC4B10
MathTblCoord DAT_00AC4B10;

// FUNCTION: GAMEMD 0x622650 (decl; reloc) -- UI::BeginDialog.
HWND __fastcall UI_BeginDialog(unsigned short id, int (__stdcall* proc)(HWND, unsigned int, unsigned int, long),
                               int param);
// FUNCTION: GAMEMD 0x622800 (decl; reloc) -- UI::FocusOnWindow.
void __fastcall UI_FocusOnWindow(HWND window);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void __fastcall FUN_00622720(HWND window);
// FUNCTION: GAMEMD 0x532100 (decl; reloc)
void __fastcall FUN_00532100(bool flag);
// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the common dialog handling; non-zero when it consumed the message.
int __fastcall FUN_00622B50(HWND window, unsigned int message, unsigned int wParam, long lParam);
// FUNCTION: GAMEMD 0x630C10 (decl; reloc) -- the phone-entry dialog procedure.
int __stdcall FUN_00630C10(HWND window, unsigned int message, unsigned int wParam, long lParam);
// The phone-book dialog procedure (defined below).
int __stdcall FUN_00631760(HWND window, unsigned int message, unsigned int wParam, long lParam);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- localised text for a label (label, 0, file, line).
const wchar_t* __fastcall FUN_00734E60(const char* label, int* index, const char* file, int line);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log, printf style.
void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x727CF0 (decl; reloc) -- normalise a text field in place.
void __fastcall FUN_00727CF0(char* text);
// FUNCTION: GAMEMD 0x727D60 (decl; reloc) -- normalise a wide text field in place.
void __fastcall FUN_00727D60(wchar_t* text);
// GLOBAL: GAMEMD 0xB73550 -- the main window.
extern HWND DAT_00B73550;

// A phone-book entry: the serial settings, then its name and number strings.
struct PhoneEntry_00631B20
{
    SerialSettings_006956D0 Serial;  // +0x00
    wchar_t Name[21];               // +0x70
    char Number[0x16];              // +0x9A
};
GG_STATIC_ASSERT(offsetof(PhoneEntry_00631B20, Name) == 0x70);
GG_STATIC_ASSERT(offsetof(PhoneEntry_00631B20, Number) == 0x9A);
GG_STATIC_ASSERT(sizeof(PhoneEntry_00631B20) == 0xB0);

// GLOBAL: GAMEMD 0xA8DAC0 -- the default serial settings.
extern SerialSettings_006956D0 DAT_00A8DAC0;

// The phone-book dialog object.
struct PhoneBookDialog_006316E0
{
    HWND Window;                    // +0x00
    int Result;                     // +0x04 1 = accepted, set by the dialog procedure
    PhoneEntry_00631B20* Book;      // +0x08 the entry being edited
    SerialSettings_006956D0 Settings;// +0x0C
    // FUNCTION: GAMEMD 0x6319C0
    void FUN_006319C0();
    // FUNCTION: GAMEMD 0x631B20
    void FUN_00631B20();
    // FUNCTION: GAMEMD 0x6316E0
    bool FUN_006316E0(PhoneEntry_00631B20* book);
};
GG_STATIC_ASSERT(offsetof(PhoneBookDialog_006316E0, Result) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneBookDialog_006316E0, Book) == 0x8);
GG_STATIC_ASSERT(offsetof(PhoneBookDialog_006316E0, Settings) == 0xC);
GG_STATIC_ASSERT(sizeof(PhoneBookDialog_006316E0) == 0x7C);

// The phone-entry editor dialog object.
struct PhoneEditDialog_00630B90
{
    HWND Window;            // +0x00
    int Result;             // +0x04 1 = accepted, set by the dialog procedure
    bool Changed;           // +0x08
    // FUNCTION: GAMEMD 0x631060 (decl; reloc) -- fill the controls.
    void FUN_00631060();
    // FUNCTION: GAMEMD 0x630B90
    bool FUN_00630B90();
};
GG_STATIC_ASSERT(offsetof(PhoneEditDialog_00630B90, Result) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEditDialog_00630B90, Changed) == 0x8);

// FUNCTION: GAMEMD 0x630B90
// Run the phone-entry editor: when it ends with changes the session writes them out.
// Returns whether the dialog was accepted.
bool PhoneEditDialog_00630B90::FUN_00630B90()
{
    Window = UI_BeginDialog(0xEE, FUN_00630C10, 0);
    if (Window) {
        Changed = false;
        Result = -1;
        SetWindowLongA(Window, DWL_USER, (LONG)this);
        FUN_00631060();
        UI_FocusOnWindow(Window);
        while (Result < 0 && UI::Updated() != 1) {
            FUN_00532100(false);
        }
        FUN_00622720(Window);
        if (Changed == 1) {
            Session_00A8B238.FUN_006990A0();
        }
    }
    bool accepted = Result == 1;
    return accepted;
}

// FUNCTION: GAMEMD 0x6316E0
// Run the phone-book dialog on an entry; no entry, no dialog. Returns whether it was accepted.
bool PhoneBookDialog_006316E0::FUN_006316E0(PhoneEntry_00631B20* book)
{
    if (book == 0) {
        return false;
    }
    Window = UI_BeginDialog(0xEF, FUN_00631760, 0);
    if (Window) {
        Book = book;
        Result = -1;
        SetWindowLongA(Window, DWL_USER, (LONG)this);
        FUN_00631B20();
        UI_FocusOnWindow(Window);
        while (Result < 0 && UI::Updated() != 1) {
            FUN_00532100(false);
        }
        FUN_00622720(Window);
    }
    bool accepted = Result == 1;
    return accepted;
}

// FUNCTION: GAMEMD 0x631760
// The phone-book dialog procedure: name/number edits, OK/cancel, and the two serial-settings radios.
int __stdcall FUN_00631760(HWND window, unsigned int message, unsigned int wParam, long lParam)
{
    int handled = FUN_00622B50(window, message, wParam, lParam);
    if (handled == 0) {
        PhoneBookDialog_006316E0* dialog = (PhoneBookDialog_006316E0*)GetWindowLongA(window, DWL_USER);
        wchar_t text[64];
        switch (message) {
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
            case 0x5E5:
                if (HIWORD(wParam) == 0x501 || HIWORD(wParam) == 0x200) {
                    SendMessageA((HWND)lParam, 0x4B3, 0x40, (LPARAM)text);
                    FUN_00727D60(text);
                    SendMessageA((HWND)lParam, 0x4B2, 0, (LPARAM)text);
                    return 0;
                }
                break;
            case 1:
                if (HIWORD(wParam) == 0) {
                    dialog->FUN_006319C0();
                    dialog->Result = 1;
                    return 0;
                }
                break;
            case 2:
                if (HIWORD(wParam) == 0) {
                    dialog->Result = 2;
                    return 0;
                }
                break;
            case 0x5DF:
                if (HIWORD(wParam) == 0x501 || HIWORD(wParam) == 0x200) {
                    SendMessageA((HWND)lParam, 0x4B5, 0x40, (LPARAM)text);
                    FUN_00727CF0((char*)text);
                    SendMessageA((HWND)lParam, 0x4B4, 0, (LPARAM)text);
                    return 0;
                }
                break;
            case 0x663:
                if (HIWORD(wParam) != 0) {
                    SendMessageA((HWND)lParam, 0xF1, 1, 0);
                    SendDlgItemMessageA(window, 0x664, 0xF1, 0, 0);
                }
                break;
            case 0x664:
                if (HIWORD(wParam) != 0) {
                    SendMessageA((HWND)lParam, 0xF1, 1, 0);
                    SendDlgItemMessageA(window, 0x663, 0xF1, 0, 0);
                    UpdateWindow(window);
                    ShowWindow(window, 0);
                    UpdateWindow(DAT_00B73550);
                    SerialEdDialog_006956D0 serial;
                    serial.FUN_006956D0(&dialog->Settings);
                    ShowWindow(window, 5);
                    return 0;
                }
                break;
            }
            break;
        case 0x497:
            SendDlgItemMessageA(window, 0x5E5, 0xC5, 0x14, 0);
            SendDlgItemMessageA(window, 0x5DF, 0xC5, 0x14, 0);
            return 0;
        }
        handled = 0;
    }
    return handled;
}

// Is the radio button or box checked (BM_GETCHECK).
inline bool IsChecked(HWND button)
{
    if (button == 0) {
        return false;
    }
    return SendMessageA(button, 0xF0, 0, 0) == 1;
}

// FUNCTION: GAMEMD 0x6319C0
// Save the controls into the entry: its name (upper-cased, or the default name when empty), its
// number, and either the dialog's serial settings or the unset defaults.
void PhoneBookDialog_006316E0::FUN_006319C0()
{
    HWND item = GetDlgItem(Window, 0x5E5);
    if (item) {
        SendMessageA(item, 0x4B3, 0x15, (LPARAM)Book->Name);
        if (wcslen(Book->Name) > 0) {
            _wcsupr(Book->Name);
        } else {
            wcscpy(Book->Name, FUN_00734E60("TXT_NONAME", 0, "D:\\ra2mdpost\\PhoneEd.cpp", 0x2F5));
        }
    }
    FUN_004068E0("Name: %ls\n", Book->Name);
    item = GetDlgItem(Window, 0x5DF);
    if (item) {
        SendMessageA(item, 0x4B5, 0x15, (LPARAM)Book->Number);
    }
    FUN_004068E0("Number: %s\n", Book->Number);
    item = GetDlgItem(Window, 0x664);
    if (IsChecked(item) == 1) {
        Book->Serial = Settings;
    } else {
        Book->Serial.Port = 0;
        Book->Serial.unknown_04 = -1;
        Book->Serial.Baud = -1;
        Book->Serial.unknown_0C = 0;
        Book->Serial.unknown_10 = -1;
        Book->Serial.unknown_14 = 3;
        Book->Serial.unknown_20 = 0;
    }
    FUN_004068E0("Settings: Port %d, Baud %d\n", Book->Serial.Port, Book->Serial.Baud);
}

// FUNCTION: GAMEMD 0x631B20
// Fill the controls from the entry: its name and number, and either its own settings (when
// it has a port, a second field and a baud rate) or the defaults; the two radio buttons
// 0x664/0x663 show which.
void PhoneBookDialog_006316E0::FUN_00631B20()
{
    HWND item = GetDlgItem(Window, 0x5E5);
    SendMessageA(item, 0x4B2, 0, (LPARAM)Book->Name);
    item = GetDlgItem(Window, 0x5DF);
    SendMessageA(item, 0x4B4, 0, (LPARAM)Book->Number);
    bool own;
    if (Book->Serial.Port != 0 && Book->Serial.unknown_04 != -1 && Book->Serial.Baud != -1) {
        Settings = Book->Serial;
        own = true;
    } else {
        own = false;
        Settings = DAT_00A8DAC0;
    }
    item = GetDlgItem(Window, 0x664);
    if (item) {
        SendMessageA(item, 0xF1, own == 1, 0);
    }
    item = GetDlgItem(Window, 0x663);
    if (item) {
        SendMessageA(item, 0xF1, !own, 0);
    }
}

// LIBRARY: GAMEMD 0x7CA5D3 (decl; reloc) -- CRT wcscmp.
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);

// A list entry: a wide display name at +0x70 and a narrow key at +0x9A.
struct NameEntry_00631C10
{
    char    unknown_00[0x70];
    wchar_t DisplayName[21];   // +0x70
    char    Key[1];            // +0x9A
};
GG_STATIC_ASSERT(offsetof(NameEntry_00631C10, DisplayName) == 0x70);
GG_STATIC_ASSERT(offsetof(NameEntry_00631C10, Key) == 0x9A);

// FUNCTION: GAMEMD 0x631C10
// Order two entries by display name, then by key (qsort comparator over entry pointers).
int __cdecl CompareNameEntries_00631C10(NameEntry_00631C10** a, NameEntry_00631C10** b)
{
    NameEntry_00631C10* left = *a;
    NameEntry_00631C10* right = *b;
    int result = wcscmp(left->DisplayName, right->DisplayName);
    if (result != 0) {
        return result;
    }
    return strcmp(left->Key, right->Key);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EFD90
extern const double DAT_007EFD90 = 60.0;
// END defined globals
