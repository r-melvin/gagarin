// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5DA6C0.

#include "init_misc_methods.h"

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
