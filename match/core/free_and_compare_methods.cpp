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

