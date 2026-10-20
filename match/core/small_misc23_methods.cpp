// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc23_methods.h"

// FUNCTION: GAMEMD 0x408E20
// Unlink, forget the owner, and back out this node's contribution: one off the
// count, its weight off the total, and the owner's bit 1 cleared.
void Obj_00408E20::FUN_00408E20()
{
    ((ListNode*)this)->FUN_00407450();

    Owner_00408E20* owner = Owner;

    Owner = 0;

    owner->Count--;
    owner->Total -= unknown_1C;
    owner->Flags &= ~2;
}

// FUNCTION: GAMEMD 0x41C380
int Triple3iLen::FUN_0041C380() const
{
    return (int)FUN_004CAC40b((double)a * a + (double)b * b + (double)c * c);
}
