// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu002_c_methods.h"

// FUNCTION: GAMEMD 0x4080B0
// Tail-forwards to another function.
void Obj_004080B0::FUN_004080B0()
{
    FUN_00407170(unknown_14 + 0x10, 0x4000);
}
