// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu225_methods.h"

// FUNCTION: GAMEMD 0x6CC2A0
// Member getter (byte).
unsigned char Obj_006CC2A0::FUN_006CC2A0() const
{
    return unknown_28->unknown_E6;
}

// FUNCTION: GAMEMD 0x6CDE80
// Empty function that pops its stack arguments.
void __stdcall FUN_006CDE80(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x6CE200
// Returns a constant. Vtable slot 11 of SuperClass (RTTI).
int Obj_006CE200::FUN_006CE200() const
{
    return 0x39;
}

// FUNCTION: GAMEMD 0x6CE210
// Returns a constant. Vtable slot 12 of SuperClass (RTTI).
int Obj_006CE210::FUN_006CE210() const
{
    return 0x80;
}
