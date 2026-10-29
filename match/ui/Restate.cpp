// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Restate.cpp. The name is the source-file string at 0x839740
//   in retail gamemd.exe v1.001, passed by the assert at 0x65f611 inside this object's
//   code range (0x65f330-0x65f79f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include <windows.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0970
extern const double DAT_007F0970;
// GLOBAL: GAMEMD 0xB04CC8
extern double DAT_00B04CC8;
// GLOBAL: GAMEMD 0xB04D00
extern double DAT_00B04D00;
// GLOBAL: GAMEMD 0xB04D18
extern double DAT_00B04D18;

// SYNTHETIC: GAMEMD 0x0065F360
// dynamic initializer for DAT_00B04D18

// GLOBAL: GAMEMD 0x00B04D18
double DAT_00B04D18 = DAT_00B04CC8 / DAT_007F0970;

// SYNTHETIC: GAMEMD 0x0065F380
// dynamic initializer for DAT_00B04D00

// GLOBAL: GAMEMD 0x00B04D00
double DAT_00B04D00 = DAT_007E1718 / DAT_00B04D18;

// SYNTHETIC: GAMEMD 0x0065F500
// GLOBAL: GAMEMD 0x00B04D08
MathTblCoord DAT_00B04D08;

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog message handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);

// GLOBAL: GAMEMD 0xB04CA0
extern int DAT_00B04CA0;

// FUNCTION: GAMEMD 0x65F710
// Dialog procedure: after the shared handler declines, a command from control
// 0x423 with a zero notification code stores 0x423 in the result slot kept in
// the window's user data; on init message 0x497 the stored text is put on
// control 0x6E7.
int __stdcall FUN_0065F710(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int handled = FUN_00622B50(h, msg, w, l);
    if (handled != 0) {
        return handled;
    }
    switch (msg) {
    case 0x497: {
        HWND item = GetDlgItem(h, 0x6E7);
        SendMessageA(item, 0x4B2, 0, DAT_00B04CA0);
        return 0;
    }
    case 0x111:
        if (GetDlgCtrlID((HWND)l) == 0x423 && HIWORD(w) == 0) {
            int* pResult = (int*)GetWindowLongA(h, 8);
            *pResult = 0x423;
        }
        break;
    }
    return 0;
}
