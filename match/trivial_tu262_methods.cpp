// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu262_methods.h"
#include "_layout/veinhole_monster_class.h"

// FUNCTION: GAMEMD 0x74F310
// Returns a constant. Vtable slot 11 of VeinholeMonsterClass (RTTI).
int VeinholeMonsterClass::vf_11()
{
    return 0x3F;
}

// FUNCTION: GAMEMD 0x74F320
// Returns a constant. Vtable slot 12 of VeinholeMonsterClass (RTTI).
int VeinholeMonsterClass::vf_12()
{
    return 0x108;
}

// FUNCTION: GAMEMD 0x750080
// Stores its argument in a member; pops its stack arguments.
void Obj_00750080::FUN_00750080(int a1)
{
    unknown_00 = 0;
}
