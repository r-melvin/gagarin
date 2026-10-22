// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu164_methods.h"

// FUNCTION: GAMEMD 0x5F3440
// Returns zero; pops its stack arguments.
int __stdcall FUN_005F3440(int a1)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F3520
// Returns zero; pops its stack arguments. Vtable slot 5 of NullModemClass (RTTI).
int Obj_005F3520::FUN_005F3520(int a1) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F3530
// Returns zero; pops its stack arguments. Vtable slot 6 of NullModemClass (RTTI).
int Obj_005F3530::FUN_005F3530(int a1) const
{
    return 0;
}
