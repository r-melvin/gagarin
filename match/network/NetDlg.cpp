// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit NetDlg.CPP. The name is the source-file string at 0x831214
//   in retail gamemd.exe v1.001, passed by the assert at 0x5da7ba inside this object's
//   code range (0x5da4d0-0x5dacef). Functions are in ascending retail address order.

#include "../core/init_misc_methods.h"
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
// GLOBAL: GAMEMD 0xABFF48
extern double DAT_00ABFF48;
// GLOBAL: GAMEMD 0xABFF50
extern int DAT_00ABFF50;
// GLOBAL: GAMEMD 0xABFF54
extern int DAT_00ABFF54;
// GLOBAL: GAMEMD 0xABFF58
extern int DAT_00ABFF58;
// GLOBAL: GAMEMD 0xABFF60
extern double DAT_00ABFF60;

// FUNCTION: GAMEMD 0x5DA500
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005DA500()
{
    DAT_00ABFF60 = DAT_00ABFF10 / DAT_007EEEF8;
}

// FUNCTION: GAMEMD 0x5DA520
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005DA520()
{
    DAT_00ABFF48 = DAT_007E1718 / DAT_00ABFF60;
}

// FUNCTION: GAMEMD 0x5DA6A0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_005DA6A0()
{
    DAT_00ABFF58 = 0;
    DAT_00ABFF50 = 0x80;
    DAT_00ABFF54 = 0x80;
}

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

// GLOBAL: GAMEMD 0x887628 -- the packet interface (WinsockInterfaceClass).
extern WinsockInterfaceClass* Interface_00887628;
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
