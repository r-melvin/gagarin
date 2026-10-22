// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu183_methods.h"

// FUNCTION: GAMEMD 0x643E60
// Returns a comparison result.
bool Obj_00643E60::FUN_00643E60() const
{
    return unknown_64 != 0;
}

// FUNCTION: GAMEMD 0x643E70
// Stores its argument in a member.
void Obj_00643E70::FUN_00643E70()
{
    unknown_64 = 0;
}
