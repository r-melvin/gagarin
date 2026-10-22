// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu188_b_methods.h"

// FUNCTION: GAMEMD 0x659550
// Stores its argument in a member; pops its stack arguments.
void Obj_00659550::FUN_00659550(unsigned char a1)
{
    unknown_58 = a1;
}
