// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu251_methods.h"

// FUNCTION: GAMEMD 0x727CA0
// Returns a constant. Vtable slot 11 of TriggerTypeClass (RTTI).
int TriggerTypeClass::vf_11()
{
    return 0x27;
}

// FUNCTION: GAMEMD 0x727CB0
// Returns a constant. Vtable slot 12 of TriggerTypeClass (RTTI).
int TriggerTypeClass::vf_12()
{
    return 0xB4;
}

// FUNCTION: GAMEMD 0x727CC0
// Member getter (dword). Vtable slot 16 of TriggerTypeClass (RTTI).
int Obj_00727CC0::FUN_00727CC0() const
{
    return unknown_98;
}
