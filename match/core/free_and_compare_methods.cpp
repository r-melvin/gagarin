// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "free_and_compare_methods.h"
#include <string.h>

// FUNCTION: GAMEMD 0x4084C0
// Release the owned buffer, then the record itself. Freeing `this` is what
// makes this a destroy helper rather than a destructor.
void Obj_00408400::FUN_004084C0()
{
    if (unknown_00) {
        FUN_007C8B3D(unknown_00);
    }

    FUN_007C8B3D(this);
}

// FUNCTION: GAMEMD 0x4085A0
// `REP STOSD` of eight dwords is the inlined memset, not a hand-written loop:
// /O2 turns a constant-size memset into the string instruction directly.
void Obj_00408500::FUN_004085A0()
{
    memset(this, 0, sizeof(*this));
}

// FUNCTION: GAMEMD 0x410A40
// `NEG EAX; SBB EAX,EAX; INC EAX` after the call is the bool form of `== 0`,
// so the comparison is an equality test rather than an ordering one. Argument
// order is (other, Name) — the pushes put the caller's string first.
bool Obj_00410A00::FUN_00410A40(const char* other) const
{
    return FUN_007C8D20(other, Name) == 0;
}
