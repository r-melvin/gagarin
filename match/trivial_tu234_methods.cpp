// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu234_methods.h"
#include "_layout/task_force_class.h"

// FUNCTION: GAMEMD 0x6E87D0
// Returns a constant. Vtable slot 11 of TaskForceClass (RTTI).
int TaskForceClass::vf_11()
{
    return 0x21;
}

// FUNCTION: GAMEMD 0x6E87E0
// Returns a constant. Vtable slot 12 of TaskForceClass (RTTI).
int TaskForceClass::vf_12()
{
    return 0xD4;
}
