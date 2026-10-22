// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu002_b_methods.h"

// FUNCTION: GAMEMD 0x407080
// Tail-forwards to another function.
void FUN_00407080(Obj_00407080* a1, int a2)
{
    FUN_00407170(a1, a2);
}
