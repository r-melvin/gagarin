// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu234_b_methods.h"

// FUNCTION: GAMEMD 0x6E8750
// Calls other functions. Vtable slot 13 of TaskForceClass (RTTI).
void FUN_006E8750(Obj_006E8750* a1, int a2, Arg1_006E8750* a3)
{
    FUN_00410BE0(a1, a2, a3);
    a3->FUN_004A1D50(a1->unknown_98);
    a3->FUN_004A1D50(a1->unknown_9C);
}
