// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

// 0x407080 tail-forwards ECX to timer entry 0x407170.
#include "trivial_tu002_b_methods.h"

// FUNCTION: GAMEMD 0x407080
// Tail-forwards to another function.
void FUN_00407080(Obj_00407080* a1, int a2)
{
    FUN_00407170(reinterpret_cast<Timer_00401000*>(a1), a2);
}
