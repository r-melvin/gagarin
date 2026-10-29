// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Original translation unit PhoneEd.cpp. The name is the source-file string at 0x836778
//   in retail gamemd.exe v1.001, passed by the assert at 0x630f61 inside this object's
//   code range (0x6309a0-0x631c7f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include <windows.h>
#include "../ui/ui_updated_methods.h"
#include "../_layout/session_class.h"
#include "../_rt/gg_static_assert.h"

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
// FUNCTION: GAMEMD 0x630C10 (decl; reloc) -- the phone-entry dialog procedure.
int __stdcall FUN_00630C10(HWND window, unsigned int message, unsigned int wParam, long lParam);
// FUNCTION: GAMEMD 0x631760 (decl; reloc) -- the phone-book dialog procedure.
int __stdcall FUN_00631760(HWND window, unsigned int message, unsigned int wParam, long lParam);

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

// The serial settings block copied into the dialog: 0x70 bytes.
struct PhoneSettings_00631B20
{
    int Port;                       // +0x00 zero = not set
    int unknown_04;                 // +0x04 -1 = not set
    int Baud;                       // +0x08 -1 = not set
    int unknown_0C[0x19];           // +0x0C
};
GG_STATIC_ASSERT(sizeof(PhoneSettings_00631B20) == 0x70);

// A phone-book entry: the serial settings, then its name and number strings.
struct PhoneEntry_00631B20
{
    PhoneSettings_00631B20 Serial;  // +0x00
    char Name[0x2A];                // +0x70
    char Number[1];                 // +0x9A
};
GG_STATIC_ASSERT(offsetof(PhoneEntry_00631B20, Name) == 0x70);
GG_STATIC_ASSERT(offsetof(PhoneEntry_00631B20, Number) == 0x9A);

// GLOBAL: GAMEMD 0xA8DAC0 -- the default serial settings.
extern PhoneSettings_00631B20 DAT_00A8DAC0;

// The phone-book dialog object.
struct PhoneBookDialog_006316E0
{
    HWND Window;                    // +0x00
    int Result;                     // +0x04 1 = accepted, set by the dialog procedure
    PhoneEntry_00631B20* Book;      // +0x08 the entry being edited
    PhoneSettings_00631B20 Settings;// +0x0C
    // FUNCTION: GAMEMD 0x631B20
    void FUN_00631B20();
    // FUNCTION: GAMEMD 0x6316E0
    bool FUN_006316E0(PhoneEntry_00631B20* book);
};
GG_STATIC_ASSERT(offsetof(PhoneBookDialog_006316E0, Result) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneBookDialog_006316E0, Book) == 0x8);
GG_STATIC_ASSERT(offsetof(PhoneBookDialog_006316E0, Settings) == 0xC);

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
