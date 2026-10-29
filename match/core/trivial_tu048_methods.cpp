// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu048_methods.h"

// FUNCTION: GAMEMD 0x4790A0
// Tail-calls a method on a member object.
void Obj_004790A0::FUN_004790A0()
{
    FUN_004A80D0(DAT_0089E414, this);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x89E414
int DAT_0089E414;
// END defined globals
