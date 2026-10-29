// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x52D870 (0x129 bytes, RET 0x10).
#include <windows.h>
#include "../_layout/obj_005fbf80.h"

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);

// GLOBAL: GAMEMD 0xA8EB60 -- the options object.
extern Obj_005FBF80 DAT_00A8EB60;
// GLOBAL: GAMEMD 0x825C80 -- the list selection remembered between visits.
extern int DAT_00825C80;

// FUNCTION: GAMEMD 0x52D870
// Dialog procedure for a list-pick dialog: fill the list on init and
// reselect the remembered row, and on a pick (or double click) store the
// chosen row's item data through the window's user data.
int __stdcall FUN_0052D870(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    bool picked = false;
    HWND list = GetDlgItem(h, 0x744);
    int r = FUN_00622B50(h, msg, w, l);
    if (r != 0) {
        return r;
    }
    LRESULT* data = (LRESULT*)GetWindowLongA(h, 8);
    switch (msg) {
    case 0x497:
        if (list != 0) {
            DAT_00A8EB60.FUN_005FC000(list);
            if (SendMessageA(list, 0x186, DAT_00825C80, 0) == -1) {
                SendMessageA(list, 0x186, 0, 0);
            }
            break;
        }
        if (data == 0) {
            return 0;
        }
        *data = -1;
        return 0;
    case 0x111: {
        switch (w & 0xFFFF) {
        case 0x686:
            if (data != 0) {
                *data = -1;
            }
            break;
        case 0x744:
            {
                unsigned short notify = (unsigned short)(w >> 16);
                if (notify == 0) {
                    picked = true;
                }
            }
            break;
        case 0x745:
            picked = true;
            break;
        }
        break;
    }
    }
    if (list != 0 && picked) {
        DAT_00825C80 = SendMessageA(list, 0x188, 0, 0);
        if (DAT_00825C80 != -1) {
            LRESULT item = SendMessageA(list, 0x199, DAT_00825C80, 0);
            if (item != 0 && data != 0) {
                *data = item;
            }
        }
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x825C80
int DAT_00825C80 = -1;
// END defined globals
