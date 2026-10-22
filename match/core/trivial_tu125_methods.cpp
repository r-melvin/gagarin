// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu125_methods.h"

// FUNCTION: GAMEMD 0x55CC00
// Stores to a global.
void __cdecl FUN_0055CC00()
{
    DAT_00ABCD58 = 1;
}

// FUNCTION: GAMEMD 0x55CC10
// Stores to a global.
void __cdecl FUN_0055CC10()
{
    DAT_00ABCD58 = 0;
}

// FUNCTION: GAMEMD 0x55E410
// Empty function.
void __cdecl FUN_0055E410()
{
}
