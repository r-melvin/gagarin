// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit NetDlg.CPP. The name is the source-file string at 0x831214
//   in retail gamemd.exe v1.001, passed by the assert at 0x5da7ba inside this object's
//   code range (0x5da4d0-0x5dacef). Functions are in ascending retail address order.

#include "../core/init_misc_methods.h"
#include "../core/mathtbl_init_shapes.h"
#include "transport/winsock_interface_class.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EEEF8
extern const double DAT_007EEEF8;
// GLOBAL: GAMEMD 0xABFF10
extern double DAT_00ABFF10;

// SYNTHETIC: GAMEMD 0x005DA500
// GLOBAL: GAMEMD 0x00ABFF60
double DAT_00ABFF60 = DAT_00ABFF10 / DAT_007EEEF8;

// SYNTHETIC: GAMEMD 0x005DA520
// GLOBAL: GAMEMD 0x00ABFF48
double DAT_00ABFF48 = DAT_007E1718 / DAT_00ABFF60;

// SYNTHETIC: GAMEMD 0x005DA6A0
// GLOBAL: GAMEMD 0x00ABFF50
MathTblCoord DAT_00ABFF50;

// FUNCTION: GAMEMD 0x5DA6C0
//
// Bring up the network layer. If the 0xA8E9C0 object fails to start, report
// false. Otherwise, unless the session is mode 4 or the 0xA8D5FC flag is
// clear, pull the first dword and the 6-byte record out of 0xA8D600 and hand
// the dword on to the 0xA8E9C0 object; report true either way.
bool __cdecl FUN_005DA6C0()
{
    int            first;
    Rec6_005DA6C0  rest;

    if (Manager_00A8E9C0.Init() == 0) {
        return false;
    }

    if (DAT_00A8B238 != 4 && DAT_00A8D5FC != 0) {
        DAT_00A8D600.FUN_0053EDA0(&first, &rest);
        Manager_00A8E9C0.FUN_00542FC0(&first);
    }

    return true;
}

// GLOBAL: GAMEMD 0xA8D610
extern unsigned short DAT_00A8D610;

// FUNCTION: GAMEMD 0x5DA720
//
// Tear down the packet interface: clear the 0xA8D610 word, delete the interface if there is one
// and forget it.
void __cdecl FUN_005DA720()
{
    DAT_00A8D610 = 0;
    if (Interface_00887628 != 0) {
        delete Interface_00887628;
    }
    Interface_00887628 = 0;
}
