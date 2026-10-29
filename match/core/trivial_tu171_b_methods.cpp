// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu171_b_methods.h"

// FUNCTION: GAMEMD 0x603DF0
// Calls other functions.
bool Obj_00603DF0::FUN_00603DF0()
{
    return (SendMessageA(this, 0x4E7, 0, 0) != 0) ? true : false;
}

// FUNCTION: GAMEMD 0x60A230
// Calls other functions.
int Obj_0060A230::FUN_0060A230()
{
    DAT_00AC1CAC = 0;
    EnumChildWindows(this, 0x60A180, 0);
    return DAT_00AC1CAC;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAC1CAC
int DAT_00AC1CAC;
// END defined globals
