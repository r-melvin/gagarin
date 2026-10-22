// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu230_b_methods.h"

// FUNCTION: GAMEMD 0x6E2C20
// Calls other functions.
bool __stdcall FUN_006E2C20(int a1, int a2, int a3, int a4)
{
    DAT_0087F7E8.FUN_00588AC0();
    DAT_0087F7E8.FUN_004F42F0(1);
    return true;
}
