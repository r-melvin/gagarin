// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu296_methods.h"

// FUNCTION: GAMEMD 0x7BF220
// Empty function.
void __cdecl FUN_007BF220()
{
}

// FUNCTION: GAMEMD 0x7C36C0
// Returns the address of a global.
void* __cdecl FUN_007C36C0()
{
    return DAT_0084E7C0;
}

// FUNCTION: GAMEMD 0x7C3740
// Returns the address of a global.
void* __cdecl FUN_007C3740()
{
    return DAT_0084E7C4;
}

// FUNCTION: GAMEMD 0x7C3950
// Updates one member in place.
void FUN_007C3950(Obj_007C3950* a1, int a2)
{
    a1->unknown_148 += a2;
}
