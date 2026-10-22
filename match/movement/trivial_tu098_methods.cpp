// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu098_methods.h"

// FUNCTION: GAMEMD 0x517560
// Branching.
int Obj_00517560::FUN_00517560(Arg1_00517560* a1)
{
    return unknown_00 == a1->unknown_00 && unknown_01 == a1->unknown_01 && unknown_02 == a1->unknown_02;
}
