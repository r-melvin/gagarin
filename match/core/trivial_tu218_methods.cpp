// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu218_methods.h"

// FUNCTION: GAMEMD 0x6B7C40
// Branching.
unsigned char Obj_006B7C40::FUN_006B7C40()
{
    if (unknown_6C != 0)
    {
        unknown_68 = unknown_6C;
        unknown_6C = 0;
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6B8120
// Returns a constant. Vtable slot 12 of SpawnManagerClass (RTTI).
int Obj_006B8120::FUN_006B8120() const
{
    return 0x74;
}

// FUNCTION: GAMEMD 0x6B8130
// Returns a constant. Vtable slot 11 of SpawnManagerClass (RTTI).
int Obj_006B8130::FUN_006B8130() const
{
    return 0x41;
}
