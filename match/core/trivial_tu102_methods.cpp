// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu102_methods.h"

// FUNCTION: GAMEMD 0x52D610
// Empty function.
void __cdecl FUN_0052D610()
{
}

// FUNCTION: GAMEMD 0x52D620
// Empty function.
void __cdecl FUN_0052D620()
{
}

// FUNCTION: GAMEMD 0x52D630
// Empty function.
void __cdecl FUN_0052D630()
{
}

// FUNCTION: GAMEMD 0x52F610
// Stores, then tail-calls.
void Obj_0052F610::FUN_0052F610()
{
    FUN_0075A790();
    FUN_0075A7D0(0);
}

// FUNCTION: GAMEMD 0x532140
// Empty function.
void __cdecl FUN_00532140()
{
}

// FUNCTION: GAMEMD 0x5355C0
// Calls other functions.
void FUN_005355C0(int a1, int a2)
{
    FUN_00721210(DAT_00A83D10, a2, DAT_008263A8);
}
