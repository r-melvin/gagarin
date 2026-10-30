// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu244_methods.h"
#include "../ai/tevent_class_methods.h"

// FUNCTION: GAMEMD 0x71FA40
// Stores its argument in a member; pops its stack arguments.
void Obj_0071FA40::FUN_0071FA40(int a1)
{
    unknown_54 = a1;
}

// FUNCTION: GAMEMD 0x71FA50
// Returns a constant. Vtable slot 12 of TEventClass (RTTI).
int TEventClass::vf_12()
{
    return 0x58;
}

// FUNCTION: GAMEMD 0x71FA60
// Returns a constant. Vtable slot 11 of TEventClass (RTTI).
int TEventClass::vf_11()
{
    return 0x30;
}

// FUNCTION: GAMEMD 0x71FA70
// Member getter (dword). Vtable slot 16 of TEventClass (RTTI).
int Obj_0071FA70::FUN_0071FA70() const
{
    return unknown_24;
}
