// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc26_methods.h"

// FUNCTION: GAMEMD 0x408560
// A zero divisor yields zero rather than faulting - the guard is on the
// divisor, before any of the arithmetic.
__int64 Obj_00408560::FUN_00408560(int value) const
{
    int divisor = Divisor;

    if (divisor != 0) {
        return (__int64)value * 1000 / divisor;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x433C30
// The looked-up record is stored whether or not it was found; only the two
// fields copied out of it and the follow-up call are conditional.
bool Obj_00433C30::FUN_00433C30(Src_00433C30* src)
{
    Rec_00433C30* rec = src->FUN_00433990();

    unknown_04 = rec;

    if (rec) {
        unknown_18 = rec->at04;
        unknown_1C = rec->at0C;

        FUN_00434700(this);

        return true;
    }

    return false;
}
