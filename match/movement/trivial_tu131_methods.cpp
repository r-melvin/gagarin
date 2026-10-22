// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu131_methods.h"

// FUNCTION: GAMEMD 0x5AE4F0
// Returns zero; pops its stack arguments.
int __stdcall FUN_005AE4F0(int a1)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5AE570
// Empty function that pops its stack arguments.
void __stdcall FUN_005AE570(int a1)
{
}

// FUNCTION: GAMEMD 0x5AE580
// Empty function that pops its stack arguments.
void __stdcall FUN_005AE580(int a1)
{
}

// FUNCTION: GAMEMD 0x5AE590
// Empty function that pops its stack arguments. Vtable slot 1 of MSEngine (RTTI) and 2 derived vtable(s).
void Obj_005AE590::FUN_005AE590(int a1)
{
}
