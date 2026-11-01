// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

// 0x4080B0 passes [ECX+0x14]+0x10 to timer entry 0x407170.
#include "trivial_tu002_c_methods.h"

// FUNCTION: GAMEMD 0x4080B0
// Tail-forwards to another function.
void Obj_004080B0::FUN_004080B0()
{
    FUN_00407170(reinterpret_cast<Timer_00401000*>(unknown_14 + 0x10), 0x4000);
}
