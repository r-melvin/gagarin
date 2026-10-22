// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu189_methods.h"

// FUNCTION: GAMEMD 0x65AAA0
// Calls other functions. Vtable slot 158 of RadioClass (RTTI) and 6 derived vtable(s).
void Obj_0065AAA0::FUN_0065AAA0(int a1, int a2)
{
    vf_159(a1, DAT_00A8EC30, a2);
}
