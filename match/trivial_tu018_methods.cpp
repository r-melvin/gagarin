// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu018_methods.h"

// FUNCTION: GAMEMD 0x4129B0
// Calls other functions.
void Obj_004129B0::FUN_004129B0()
{
    FUN_004068E0(this);
}

// FUNCTION: GAMEMD 0x413590
// Returns a constant.
int __cdecl FUN_00413590()
{
    return 0x2EE;
}
