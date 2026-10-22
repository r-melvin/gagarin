// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x487D70.

#include "cell_class_jumpjet_methods.h"

// FUNCTION: GAMEMD 0x487D70  CellClass::TryAssignJumpjet (__thiscall, ret 0x4)
// Claim or release the cell's single jumpjet slot. A null argument releases it;
// otherwise the claim succeeds only if the slot is free or already held by the
// same object.
//
// PARTIAL, 97.7% (42/43). Retail's inlined checked downcast for the release
// call reads the flag as a byte (`MOV CL,[EAX+0x14]; AND CL,4`); reading the
// int flag word here gives `MOV ECX,[EAX+0x14]`, the single differing
// instruction.

// The AbstractFlags bit-2 probe on the int flag word, null-safe.
static __inline bool is_foot(ObjectClass* object)
{
    return object != 0 && (object->AbstractFlags & ABSFLAGS_ISFOOT) != 0;
}

// The engine's checked downcast, null case first.
static __inline ObjectClass* foot_cast(ObjectClass* object)
{
    ObjectClass* foot;
    if (object == 0)
        foot = 0;
    else
        foot = (object->AbstractFlags & ABSFLAGS_ISFOOT) ? object : 0;
    return foot;
}

bool CellClass::TryAssignJumpjet(ObjectClass* object)
{
    if (object == 0) {
        if (is_foot(Jumpjet))
            Jumpjet_OccupyCell(foot_cast(Jumpjet), JumpjetClearCoords);
        Jumpjet = 0;
        return true;
    }
    if (Jumpjet != 0 && Jumpjet != object)
        return false;
    Jumpjet = object;
    if (is_foot(object))
        Jumpjet_OccupyCell(object, MapCoords);
    return true;
}
