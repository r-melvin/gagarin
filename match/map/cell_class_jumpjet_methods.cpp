// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x487D70.

#include "cell_class_jumpjet_methods.h"

// FUNCTION: GAMEMD 0x487D70  CellClass::TryAssignJumpjet (__thiscall, ret 0x4)
// Claim or release the cell's single jumpjet slot. A null argument releases it;
// otherwise the claim succeeds only if the slot is free or already held by the
// same object.
//
// Retail runs the engine's null-safe checked downcast inline for the release
// call (`TEST EAX,EAX; JNZ; XOR ECX,ECX; JMP` / `MOV CL,[EAX+0x14]; AND CL,4;
// NEG CL; SBB ECX,ECX; AND ECX,EAX`) right after a guard that already tested
// the same object. VC6 folds that re-test into the guard unless both halves are
// opaque to its propagation: the guard must test the member (`Jumpjet`) while
// the cast tests its own parameter, and the guard must read the int flag word
// while the cast reads the byte alias. With a local `current` shared by both,
// or both reads at one width, the block collapses to `MOV ECX,EAX` (16.3%);
// splitting only the width keeps the AND/NEG/SBB but loses the null re-test
// (14.0%); splitting only the variable keeps the shape but reads a dword in the
// cast (97.7%).

// The AbstractFlags bit-2 probe on the int flag word, null-safe.
static __inline bool is_foot(ObjectClass* object)
{
    return object != 0 && (object->AbstractFlags & ABSFLAGS_ISFOOT) != 0;
}

// The engine's checked downcast, null case first, on the byte alias.
static __inline ObjectClass* foot_cast(ObjectClass* object)
{
    ObjectClass* foot;
    if (object == 0)
        foot = 0;
    else
        foot = (object->AbstractFlagsLow & ABSFLAGS_ISFOOT) ? object : 0;
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
