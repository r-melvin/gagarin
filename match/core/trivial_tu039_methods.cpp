// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu039_methods.h"

// FUNCTION: GAMEMD 0x45B1B0
// Tail-forwards to another function.
void Obj_0045B1B0::FUN_0045B1B0()
{
    FUN_0045B1C0();
}

// FUNCTION: GAMEMD 0x45C2F0
// Tail-forwards to another function.
void Obj_0045C2F0::FUN_0045C2F0()
{
    FUN_0045C300();
}

// FUNCTION: GAMEMD 0x45EC80
// Empty function.
void __cdecl FUN_0045EC80()
{
}

// FUNCTION: GAMEMD 0x465D80
// Returns its receiver.
Obj_00465D80* Obj_00465D80::FUN_00465D80()
{
    return this;
}
