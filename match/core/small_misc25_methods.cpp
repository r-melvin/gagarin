// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x45ADD0.

#include "small_misc25_methods.h"

// FUNCTION: GAMEMD 0x45ADD0
// An index at or past the count fails; removing the last element succeeds with
// no copying at all, since the count drop alone is enough.
//
// The slide is written with the increment *after* the move. Retail's loop reads
// `INC EAX; MOV ESI,[EDX+EAX*4]; MOV [EDX+EAX*4-4],ESI`, which looks like a
// pre-incremented `Items[i-1] = Items[i]` - but writing it that way makes VC6
// compute the store address with a separate LEA. Written post-incremented the
// compiler performs that induction rewrite itself and lands on retail's form.
// Four phrasings tried; only this one closes it.
bool Vector_0045ADD0::FUN_0045ADD0(int index)
{
    int count = Count;

    if (index < count) {
        count--;
        Count = count;

        if (index < count) {
            do {
                Items[index] = Items[index + 1];

                index++;
            } while (index < Count);
        }

        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x45AE10
bool Vector_0045ADD0::FUN_0045AE10(int index)
{
    int count = Count;

    if (index < count) {
        count--;
        Count = count;

        if (index < count) {
            do {
                Items[index] = Items[index + 1];

                index++;
            } while (index < Count);
        }

        return true;
    }

    return false;
}

// PEEPHOLE DELTA (status partial, 13.3% - 2/15). Retail emits
// `DEC EAX; TEST EAX,EAX; MOV [mem],EAX; JGE` - a redundant TEST before the
// store, then a signed branch. We emit `DEC; MOV; JNS`, reusing DEC's flags and
// dropping the TEST, which shifts everything after it. The same shape and the
// same residual as FUN_00401F90, and this is the same compiler build that
// produced retail, so a source form must exist. Fourteen phrasings have been
// probed and none produces it. The closest is `if (v <= -1)`, which gets the
// *structure* right - comparison before the store, branch after - but encodes
// as `CMP EAX,-1 / JG` rather than `TEST EAX,EAX / JGE`. Every `< 0` form
// tested folds into DEC's flags and emits `JNS` with no compare at all; the
// only way found to force a real TEST is `v & 0x80000000`, which encodes as
// `TEST EAX,0x80000000` and is five bytes rather than two. Left here so the
// next attempt starts past the dead ends.
// The score badly understates the delta: two instructions differ per
// decrement and the rest are merely displaced.
//
// FUNCTION: GAMEMD 0x408E70
void Obj_00408E70::FUN_00408E70()
{
    // Both decrements are written twice - once as the value stored, once in the
    // comparison - which is what keeps retail's `TEST` after each `DEC`. See
    // section 4.6; the volatile stores this used to carry are unnecessary once
    // the arithmetic is duplicated.
    int value = unknown_1C;

    unknown_1C = value - 1;

    if (value - 1 < 0) {
        unknown_1C = 0;
    }

    Owner_00408E70* owner = Owner;

    int count = owner->at98;

    owner->at98 = count - 1;

    if (count - 1 < 0) {
        Owner->at98 = 0;
    }
}
