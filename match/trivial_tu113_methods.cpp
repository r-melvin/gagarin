// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu113_methods.h"

// FUNCTION: GAMEMD 0x54EE50
// Empty function.
void __cdecl FUN_0054EE50()
{
}

// FUNCTION: GAMEMD 0x54EFF0
// Returns a comparison result.
bool FUN_0054EFF0(int a1)
{
    return (unsigned char)a1 == 0xA;
}
