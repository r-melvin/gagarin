// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc8_methods.h"

// FUNCTION: GAMEMD 0x4092F0
// Always resets with zero, then again with the stored value if there is one.
// The constant returned is a fixed status rather than anything computed.
int Obj_004092F0::FUN_004092F0()
{
    FUN_004091C0(this, 0);

    int value = unknown_08;

    if (value) {
        FUN_004091C0(this, value);
    }

    return 0x80040000;
}

// FUNCTION: GAMEMD 0x41CAF0
void __cdecl FUN_0041CAF0()
{
    DAT_00889F5C = FUN_005B40B0(DAT_00817FE4, 0);
    DAT_00889F60 = FUN_005B40B0(DAT_00817FD8, 0);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x889F5C
Obj_005B40B0* DAT_00889F5C;
// GLOBAL: GAMEMD 0x889F60
Obj_005B40B0* DAT_00889F60;
// END defined globals
