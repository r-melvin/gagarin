// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu084_methods.h"

// FUNCTION: GAMEMD 0x4D0390
// Returns a constant. Vtable slot 9 of FlyLocomotionClass (RTTI).
int Obj_004D0390::FUN_004D0390() const
{
    return 0x60;
}
