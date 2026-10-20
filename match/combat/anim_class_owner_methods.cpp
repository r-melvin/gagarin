// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x424B50.

#include "anim_class_owner_methods.h"

// FUNCTION: GAMEMD 0x424B50  AnimClass::SetOwnerObject (__thiscall, ret 4)
//
// Re-parent an animation. The old owner keeps its "has an anim" flag only if
// some other animation in the global array still points at it, so the array is
// scanned for a second referrer before the flag is dropped and the owner's
// +0x17C virtual is run. The animation is pulled out of the display list
// around each coordinate change and re-submitted afterwards, and the move onto
// the new owner is reported to slot +0x1B4 as the delta between the old and
// the new coordinates.
//
// PARTIAL (83.7%, 87/104; mnemonic multiset identical -- scheduling and
// register naming only). Two residual clusters, both ordering-only: (a) in the
// first half retail interleaves the `PUSH ESI` of the display-list Remove
// between the X and Y loads off the returned coordinate pointer, where VC6
// issues all three loads and the Z spill first; (b) retail's spilled old-Z
// temporary lands at [ESP+0x24] -- inside the now-dead GetCoords buffer --
// while VC6 merges it into the parameter's home slot at [ESP+0x38], so every
// displacement in that pair of instructions differs. Frame size, instruction
// count and mnemonic multiset all agree. Variants tried: member-wise `from`
// construction with the delta written X/Y/Z (80.8%); delta written X/Z/Y
// (82.7%); the three `now->` reads bound to locals ahead of the subtractions
// (83.7%, kept); the local declarations reversed to Z/Y/X and Y/Z/X, both of
// which drop the old-Z spill entirely (69.2%); `where` written as a whole
// struct copy `Coord where = *here;` (83.7%, same schedule); explicit pointer
// locals taken before the last member store to hoist the two LEAs (83.7%, the
// LEA folds back down); and `volatile int oldZ` (81.7%), which does put the
// old Z in memory and X/Y in EBX/EBP as retail has them but sinks the delta.X
// store above the reload and reorders the three now-> loads.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// ESI, EDI on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void Anim_00424B50::SetOwnerObject(Owner_00424B50* owner)
{
    Owner_00424B50* old = OwnerObject;

    if (old != 0)
    {
        char wasListed = unknown_74;
        if (wasListed)
            DAT_0087F7E8.Remove(this);

        int count = DAT_00A8E9B8;
        int i = 0;
        if (count > 0)
        {
            Anim_00424B50** p = DAT_00A8E9AC;
            do
            {
                if (*p != this && (*p)->OwnerObject == OwnerObject)
                    break;
                i++;
                p++;
            } while (i < count);
        }

        if (i == count)
        {
            (old->*old->Vptr->At_17C)();
            old->unknown_84 = 0;
        }

        Coord_00424B50 buf;
        Coord_00424B50* here = (this->*Vptr->GetCoords)(&buf);
        Coord_00424B50 where;
        where.X = here->X;
        where.Y = here->Y;
        where.Z = here->Z;
        OwnerObject = 0;
        (this->*Vptr->At_1B4)(&where);

        if (wasListed)
            DAT_0087F7E8.Submit(this);
    }

    if (owner != 0)
    {
        Coord_00424B50 buf;
        Coord_00424B50* here = (this->*Vptr->GetCoords)(&buf);
        int oldX = here->X;
        int oldY = here->Y;
        int oldZ = here->Z;

        DAT_0087F7E8.Remove(this);
        owner->unknown_84 = 1;
        OwnerObject = owner;

        Coord_00424B50 buf2;
        Coord_00424B50* now = (owner->*owner->Vptr->GetCoords)(&buf2);
        Coord_00424B50 delta;
        int nx = now->X;
        int nz = now->Z;
        int ny = now->Y;
        delta.X = oldX - nx;
        delta.Z = oldZ - nz;
        delta.Y = oldY - ny;
        (this->*Vptr->At_1B4)(&delta);

        DAT_0087F7E8.Submit(this);
    }
}
