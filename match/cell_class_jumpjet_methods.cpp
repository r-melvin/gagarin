// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x487D70.

#include "cell_class_jumpjet_methods.h"

// FUNCTION: GAMEMD 0x487D70  CellClass::TryAssignJumpjet (__thiscall, ret 0x4)
// Claim or release the cell's single jumpjet slot. A null argument releases it;
// otherwise the claim succeeds only if the slot is free or already held by the
// same object.
//
// Retail's inlined checked downcast reads the flag as a byte
// (`MOV CL,[EAX+0x14]; AND CL,4`), which the bit-field flag byte reproduces.

// The IsFoot (bit 2) probe on the flag byte, null-safe.
static __inline bool is_foot(ObjectClass* object)
{
    return object != 0 && object->Flags.IsFoot;
}

// The engine's checked downcast, null case first.
static __inline ObjectClass* foot_cast(ObjectClass* object)
{
    ObjectClass* foot;
    if (object == 0)
        foot = 0;
    else
        foot = object->Flags.IsFoot ? object : 0;
    return foot;
}

bool CellClass::TryAssignJumpjet(ObjectClass* object)
{
    if (object == 0) {
        if (is_foot((ObjectClass*)Jumpjet))
            Jumpjet_OccupyCell(foot_cast((ObjectClass*)Jumpjet), JumpjetClearCoords);
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

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x89E748
CellStruct JumpjetClearCoords;
// END defined globals
