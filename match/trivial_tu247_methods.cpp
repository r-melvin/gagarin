// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu247_methods.h"

// FUNCTION: GAMEMD 0x7236E0
// Returns a constant. Vtable slot 12 of TiberiumClass (RTTI).
int Obj_007236E0::FUN_007236E0() const
{
    return 0x128;
}

// FUNCTION: GAMEMD 0x7236F0
// Returns a constant. Vtable slot 11 of TiberiumClass (RTTI).
int Obj_007236F0::FUN_007236F0() const
{
    return 0x2E;
}

// FUNCTION: GAMEMD 0x723700
// Member getter (dword). Vtable slot 16 of TiberiumClass (RTTI).
int Obj_00723700::FUN_00723700() const
{
    return unknown_98;
}
