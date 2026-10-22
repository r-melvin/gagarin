// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc11_methods.h"

// FUNCTION: GAMEMD 0x4026C0
// Notify, set the bit, notify again - the second notification is a tail call.
//
// PARTIAL: the flag update is an ordinary `|= 0x10`. VC6 narrows it to
// `OR AL,0x10` and hoists the dispatch load between the read and the store,
// where retail keeps the full dword operation ahead of the load. A volatile
// lvalue that forced retail's form was removed as match steering.
void Obj_004026C0::FUN_004026C0()
{
    DISP(this, 0x28);

    Flags |= 0x10;

    DISP(this, 0x2C);
}

// FUNCTION: GAMEMD 0x4026F0
// The clearing twin of 0x4026C0, with the same accepted difference (PARTIAL).
void Obj_004026C0::FUN_004026F0()
{
    DISP(this, 0x28);

    Flags &= ~0x10;

    DISP(this, 0x2C);
}

// FUNCTION: GAMEMD 0x4085B0
// The product is stored first and then halved twice for modes 1 and 2 alike -
// both land on the same shift, so this is a two-value case rather than a
// per-mode scale.
void Obj_004085B0::FUN_004085B0()
{
    int value = unknown_10 * unknown_0C * unknown_08;

    unknown_14 = value;

    if (Mode == 1 || Mode == 2) {
        unknown_14 = value >> 2;
    }
}
