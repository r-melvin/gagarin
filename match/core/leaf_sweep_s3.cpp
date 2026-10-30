// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   Receivers that are not bound by RTTI keep a placeholder name derived from the
//   address.
//
// Small leaves between 0x6B0000 and 0x7C4000, worker s3 sweep. Ordered ascending by
// retail address.
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/audio_controller.h"
#include "../_layout/voc_class.h"
#include "../platform/center_window_methods.h"
#include "../ui/input_controls/ui_gadget.h"

// ---------------------------------------------------------------------------
// 0x7518A0: fire an audio event for the table entry at an index.
// GLOBAL: GAMEMD 0xB1D37C
extern "C" VocClass** DAT_00B1D37C;
// GLOBAL: GAMEMD 0xB1D388
extern "C" int DAT_00B1D388;
// FUNCTION: GAMEMD 0x7518A0
// Plays the entry at `index` when it is inside the table.
void __fastcall FUN_007518A0(AudioController* pThis, int index)
{
    if (index >= 0 && index < DAT_00B1D388) {
        AudioController::SetEvent(pThis, 0, DAT_00B1D37C[index]->EventType);
    }
}

// ---------------------------------------------------------------------------
// 0x734F20: does the current table entry's name match a fixed string.
struct NameSlot_00734F20
{
    const char* Name;   // +0x00
    int unknown_04;
    int unknown_08;
    int unknown_0C;
};
GG_STATIC_ASSERT(sizeof(NameSlot_00734F20) == 0x10);
// GLOBAL: GAMEMD 0x845728
extern int Current_00845728;
// GLOBAL: GAMEMD 0x845684
extern NameSlot_00734F20 Slots_00845684[];
// GLOBAL: GAMEMD 0x8457BC
extern const char Match_008457BC[];
// LIBRARY: GAMEMD 0x7C8D20 -- _stricmp.
extern "C" int __cdecl _stricmp(const char* a, const char* b);

// FUNCTION: GAMEMD 0x734F20
// True when the current slot has no name or its name equals the fixed string.
int __cdecl FUN_00734F20()
{
    const char* name = Slots_00845684[Current_00845728].Name;
    if (name == 0) {
        return 1;
    }
    return _stricmp(name, Match_008457BC) == 0;
}

// ---------------------------------------------------------------------------
// 0x6CE570: look a name up in a twelve-entry string table.
// GLOBAL: GAMEMD 0x8425C0
extern const char* const Names_008425C0[12];

// FUNCTION: GAMEMD 0x6CE570
// Index of the table entry equal to `name` (case-insensitive), or -1.
int __fastcall FUN_006CE570(const char* name)
{
    for (int i = 0; i < 12; ++i) {
        if (_stricmp(Names_008425C0[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x777060: centre a window in its owner.
// FUNCTION: GAMEMD 0x777060
// Centres `window` inside its owner window when it has one.
void __fastcall FUN_00777060(HWND window)
{
    HWND owner = (HWND)GetWindowLongA(window, GWL_HWNDPARENT);
    if (owner) {
        Unsorted_CenterWindowIn(window, owner);
    }
}

// ---------------------------------------------------------------------------
// 0x72E820: run two helpers over the shared screen globals.
// GLOBAL: GAMEMD 0xB0FA04
extern int DAT_00B0FA04;
// GLOBAL: GAMEMD 0xB0FB50
extern int DAT_00B0FB50;
// GLOBAL: GAMEMD 0xB0FBCC
extern int DAT_00B0FBCC;
// FUNCTION: GAMEMD 0x72E450 (decl; reloc)
void __stdcall FUN_0072E450(int c);
// FUNCTION: GAMEMD 0x72E730 (decl; reloc)
void __fastcall FUN_0072E730(int a, int b, int x, int y, int z);

// FUNCTION: GAMEMD 0x72E820
// Runs the first helper on `c`, then the second with the three globals.
void __fastcall FUN_0072E820(int a, int b, int c)
{
    FUN_0072E450(c);
    FUN_0072E730(a, b, DAT_00B0FBCC, DAT_00B0FB50, DAT_00B0FA04);
}

// ---------------------------------------------------------------------------
// 0x7767B0: query a control for its child, tell the child to limit text, and
// remember the control and a value.
// GLOBAL: GAMEMD 0xB73080
extern int DAT_00B73080;
// GLOBAL: GAMEMD 0xB730A0
extern HWND DAT_00B730A0;

// FUNCTION: GAMEMD 0x7767B0
// Looks up the control's child (message 0x110F) and sends it 0xC5 with
// `length`; on success records `value` and the control globally.
void __fastcall FUN_007767B0(HWND control, int value, int length)
{
    HWND child = (HWND)SendMessageA(control, 0x110f, 0, 0);
    if (child) {
        SendMessageA(child, 0xc5, length, 0);
        DAT_00B73080 = value;
        DAT_00B730A0 = control;
    }
}

// ---------------------------------------------------------------------------
// 0x776880: show context help for a dialog's window.
struct Dialog_00776880
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    HWND Window;   // +0x0C
    void FUN_00776880();
};
GG_STATIC_ASSERT(offsetof(Dialog_00776880, Window) == 0xC);
// STRING: GAMEMD 0x849E2C
extern const char HelpFile_00849E2C[];

// FUNCTION: GAMEMD 0x776880
// Opens the help file at the window's context help id (HELP_CONTEXTPOPUP).
void Dialog_00776880::FUN_00776880()
{
    HWND window = Window;
    WinHelpA(window, HelpFile_00849E2C, HELP_CONTEXTPOPUP, GetWindowContextHelpId(window));
}

// ---------------------------------------------------------------------------
// 0x763690: index of a letter name; the inverse of FUN_00763610.
// LIBRARY: GAMEMD 0x007C990E
// isalpha
extern "C" int __cdecl isalpha(int ch);
// LIBRARY: GAMEMD 0x007C97D3
// _toupper
extern "C" int __cdecl toupper(int ch);

// FUNCTION: GAMEMD 0x763690
// "A".."Z" give 0..25, "AA" gives 26 and so on; -1 when the text does not start with a letter.
int __fastcall FUN_00763690(const char* name)
{
    int index = -1;
    if (isalpha(name[0])) {
        index = toupper(name[0]) - 'A';
        if (isalpha(name[1])) {
            return toupper(name[1]) + index * 26 - 39;
        }
    }
    return index;
}

// ---------------------------------------------------------------------------
// 0x727CF0: trim control characters and blanks from both ends of a string.
// FUNCTION: GAMEMD 0x727CF0
// Strips leading and trailing bytes up to 0x20 in place; null stays null.
char* __fastcall FUN_00727CF0(char* text)
{
    if (text) {
        char* start = text;
        while (*start && (unsigned char)*start <= 0x20) {
            start++;
        }
        if (start != text) {
            strcpy(text, start);
        }
        int last = strlen(text) - 1;
        while (last >= 0 && *start && (unsigned char)text[last] <= 0x20) {
            text[last] = 0;
            last--;
        }
    }
    return text;
}

// ---------------------------------------------------------------------------
// 0x71FFB0: default-construct a text button.
// FUNCTION: GAMEMD 0x71FFB0
// A zero-sized toggle with no text and print mode 2.
TextButtonClass::TextButtonClass() : ToggleClass(0, 0, 0, 0, 0)
{
    HasOutline = 0;
    Text = 0;
    unknown_3C = 2;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0FA04
int DAT_00B0FA04;
// GLOBAL: GAMEMD 0xB0FB50
int DAT_00B0FB50;
// GLOBAL: GAMEMD 0xB0FBCC
int DAT_00B0FBCC;
// GLOBAL: GAMEMD 0xB73080
int DAT_00B73080;
// GLOBAL: GAMEMD 0xB730A0
HWND DAT_00B730A0;
// GLOBAL: GAMEMD 0x845728
int Current_00845728 = 10;
// GLOBAL: GAMEMD 0x8457BC
extern const char Match_008457BC[] = "e";
// GLOBAL: GAMEMD 0x849E2C
extern const char HelpFile_00849E2C[] = "SUN.HLP";
// END defined globals
