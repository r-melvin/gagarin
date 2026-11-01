// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu172_methods.h"

// FUNCTION: GAMEMD 0x628DD0
// Calls other functions.
Obj_00628DD0* Obj_00628DD0::FUN_00628DD0(int a1, Arg2_00628DD0* a2)
{
    FUN_004F4C70(a1);
    unknown_100 = a2->unknown_00;
    return this;
}
