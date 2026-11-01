// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu219_methods.h"

// FUNCTION: GAMEMD 0x6B8AE0
// Updates one member in place.
void Obj_006B8AE0::FUN_006B8AE0()
{
    unknown_00 = (unknown_00 & 0xFFF88088) | 0x8088;
}

// FUNCTION: GAMEMD 0x6BA220
// Empty function.
void __cdecl FUN_006BA220()
{
}

// FUNCTION: GAMEMD 0x6BA680
// Returns a constant boolean; pops its stack arguments.
bool __stdcall FUN_006BA680(int a1, int a2, int a3)
{
    return false;
}
