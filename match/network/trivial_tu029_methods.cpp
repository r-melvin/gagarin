// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu029_methods.h"

// FUNCTION: GAMEMD 0x430580
// Empty function that pops its stack arguments.
void __stdcall FUN_00430580(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
}

// FUNCTION: GAMEMD 0x430600
// Empty function.
void __cdecl FUN_00430600()
{
}

// FUNCTION: GAMEMD 0x430610
// Updates one member in place.
void Obj_00430610::FUN_00430610()
{
    unknown_0C &= 0xFE;
}
