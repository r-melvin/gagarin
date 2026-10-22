// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu104_methods.h"

// FUNCTION: GAMEMD 0x539560
// Stores to a global.
void __cdecl FUN_00539560()
{
    DAT_00A9F9CC = DAT_00A9F9F8;
}

// FUNCTION: GAMEMD 0x539570
// Stores to a global.
void __cdecl FUN_00539570()
{
    DAT_00A9FA48 = DAT_00A9F9F8;
}

// FUNCTION: GAMEMD 0x539EA0
// Stores to a global.
void FUN_00539EA0(int a1)
{
    DAT_00A9FAB4 = a1;
}

// FUNCTION: GAMEMD 0x53A110
// Returns a comparison result.
bool __cdecl FUN_0053A110()
{
    return DAT_00A9FABC == 1;
}

// FUNCTION: GAMEMD 0x53A120
// Returns a comparison result.
bool __cdecl FUN_0053A120()
{
    return DAT_00A9FABC == 2;
}

// FUNCTION: GAMEMD 0x53B3F0
// Empty function.
void __cdecl FUN_0053B3F0()
{
}

// FUNCTION: GAMEMD 0x53B400
// Returns a comparison result.
bool __cdecl FUN_0053B400()
{
    return (DAT_00A9FAC0 != 0) ? true : false;
}
