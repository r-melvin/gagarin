// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x5BC370 (0x4B bytes, plain RET).
#include <windows.h>

// GLOBAL: GAMEMD 0xABF234
extern HWND DAT_00ABF234;
// GLOBAL: GAMEMD 0xABF238
extern bool DAT_00ABF238;
// GLOBAL: GAMEMD 0xABF239
extern bool DAT_00ABF239;
// GLOBAL: GAMEMD 0xABF23A
extern bool DAT_00ABF23A;
// GLOBAL: GAMEMD 0xABF240
extern HWND DAT_00ABF240;
// FUNCTION: GAMEMD 0x5BC530 (decl; reloc)
void FUN_005BC530();

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
