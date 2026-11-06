// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x5BC370 (0x4B bytes, plain RET).
#include <windows.h>
#include "runtime_misc_globals.h"
#include "_layout/obj_005bcc40.h"

// GLOBAL: GAMEMD 0xABF234
extern HWND DAT_00ABF234;
// GLOBAL: GAMEMD 0xABF238
extern bool DAT_00ABF238;
// GLOBAL: GAMEMD 0xABF240
extern HWND DAT_00ABF240;
// FUNCTION: GAMEMD 0x5BC530 (decl; reloc)
void FUN_005BC530();

// GLOBAL: GAMEMD 0xABF168
extern int DAT_00ABF168[8];
// GLOBAL: GAMEMD 0xABF230
extern HINSTANCE DAT_00ABF230;
// GLOBAL: GAMEMD 0xABF23C
extern int DAT_00ABF23C;

// FUNCTION: GAMEMD 0x5BC180
// Creates the eight text grids (80 by 25 blank cells, window covering the whole grid), makes the
// first one active, blanks and redraws all of them, and shows the log window when a show was
// requested earlier.
void __fastcall FUN_005BC180(HINSTANCE instance, HWND window, bool enabled)
{
    DAT_00ABF230 = instance;
    DAT_00ABF234 = window;
    DAT_00ABF238 = enabled;
    for (int n = 0; n < 8; n++) {
        DAT_00ABF168[n] = (int)new Obj_005BCC40(n);
    }
    DAT_00ABF23C = DAT_00ABF168[0];
    for (int m = 0; m < 8; m++) {
        Obj_005BCC40* grid = (Obj_005BCC40*)DAT_00ABF168[m];
        grid->Clear();
    }
    if (DAT_00ABF239 && DAT_00ABF238) {
        if (DAT_00ABF240 == 0) {
            FUN_005BC530();
        }
        DAT_00ABF23A = true;
        ShowWindow(DAT_00ABF240, 1);
        SetFocus(DAT_00ABF234);
    }
}

// FUNCTION: GAMEMD 0x5BC370
// Show the debug window and focus its owner. With no owner window yet, only
// remember that a show was requested.
void FUN_005BC370()
{
    if (DAT_00ABF234 == 0) {
        DAT_00ABF239 = true;
        return;
    }
    if (DAT_00ABF238) {
        if (DAT_00ABF240 == 0) {
            FUN_005BC530();
        }
        DAT_00ABF23A = true;
        ShowWindow(DAT_00ABF240, 1);
        SetFocus(DAT_00ABF234);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABF234
HWND DAT_00ABF234;
// GLOBAL: GAMEMD 0xABF238
bool DAT_00ABF238;
// GLOBAL: GAMEMD 0xABF239
bool DAT_00ABF239;
// GLOBAL: GAMEMD 0xABF23A
bool DAT_00ABF23A;
// GLOBAL: GAMEMD 0xABF240
HWND DAT_00ABF240;
// END defined globals
