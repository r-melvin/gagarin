// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu271_methods.h"

// FUNCTION: GAMEMD 0x764FA0
// Calls other functions.
unsigned char Obj_00764FA0::FUN_00764FA0()
{
    return unknown_30 != unknown_0C->FUN_0076BFA0();
}
