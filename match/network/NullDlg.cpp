// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit NullDlg.CPP. The name is the source-file string at 0x831e84
//   in retail gamemd.exe v1.001, passed by the assert at 0x5ef768 inside this object's
//   code range (0x5ef2f0-0x5f13cf). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include <windows.h>
#include "../_rt/gg_static_assert.h"
#include "null_modem_class_methods.h"

// GLOBAL: GAMEMD 0x7EEFB8
extern const double DAT_007EEFB8;
// GLOBAL: GAMEMD 0xAC1210
extern double DAT_00AC1210;
// GLOBAL: GAMEMD 0xAC1248
extern double DAT_00AC1248;
// GLOBAL: GAMEMD 0xAC1260
extern double DAT_00AC1260;

// SYNTHETIC: GAMEMD 0x005EF320
// dynamic initializer for DAT_00AC1260

// GLOBAL: GAMEMD 0x00AC1260
double DAT_00AC1260 = DAT_00AC1210 / DAT_007EEFB8;

// SYNTHETIC: GAMEMD 0x005EF340
// dynamic initializer for DAT_00AC1248

// GLOBAL: GAMEMD 0x00AC1248
double DAT_00AC1248 = 1.0 / DAT_00AC1260;

// SYNTHETIC: GAMEMD 0x005EF4C0
// GLOBAL: GAMEMD 0x00AC1250
MathTblCoord DAT_00AC1250;

// GLOBAL: GAMEMD 0xA8DAC0 -- the serial settings chosen in the null-modem dialog.
extern SerialSettings_005F19E0 DAT_00A8DAC0;

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog message handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);

// FUNCTION: GAMEMD 0x5EFF70
// Enable or disable the three connect buttons (0x653-0x655): they are enabled
// only when a port, a baud rate and a modem are chosen and the port is usable.
void __fastcall FUN_005EFF70(HWND dialog)
{
    bool enable = true;
    if (DAT_00A8DAC0.Port != 0 && DAT_00A8DAC0.unknown_04 != -1 && DAT_00A8DAC0.Baud != -1) {
        if (DAT_00A8EA70.FUN_005F19E0(&DAT_00A8DAC0) != 0) {
            enable = false;
        }
    } else {
        enable = false;
    }
    HWND button = GetDlgItem(dialog, 0x653);
    if (button != 0) {
        EnableWindow(button, enable);
    }
    button = GetDlgItem(dialog, 0x654);
    if (button != 0) {
        EnableWindow(button, enable);
    }
    button = GetDlgItem(dialog, 0x655);
    if (button != 0) {
        EnableWindow(button, enable);
    }
}

// FUNCTION: GAMEMD 0x5EFF00
// Dialog procedure: after the shared handler declines, a command of 2 or 0x652-0x655
// is stored in the result slot kept in the window's user data; on init message
// 0x497 the connect buttons are refreshed.
int __stdcall FUN_005EFF00(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int handled = FUN_00622B50(h, msg, w, l);
    if (handled != 0) {
        return handled;
    }
    switch (msg) {
    case 0x497:
        FUN_005EFF70(h);
        return 0;
    case 0x111: {
        unsigned int* pResult = (unsigned int*)GetWindowLongA(h, 8);
        if (w == 2 || (w > 0x651 && w <= 0x655)) {
            *pResult = w;
        }
        break;
    }
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8DAC0
SerialSettings_005F19E0 DAT_00A8DAC0;
// GLOBAL: GAMEMD 0x7EEFB8
extern const double DAT_007EEFB8 = 60.0;
// END defined globals
