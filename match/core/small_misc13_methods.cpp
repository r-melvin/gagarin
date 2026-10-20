// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc13_methods.h"

// FUNCTION: GAMEMD 0x406F40
// Shutdown chain, ending in a guarded tail call.
void __cdecl FUN_00406F40()
{
    FUN_00753510();
    FUN_00753620();
    FUN_00751080b();
    FUN_00405040b();

    if (DAT_0087E728b) {
        FUN_004037C0b(DAT_0087E728b, 1);
    }
}

// FUNCTION: GAMEMD 0x426DD0
// Two fields of the same record combined: the second, plus twice the first,
// plus a fixed eight.
int Obj_00426DD0::FUN_00426DD0(int index) const
{
    return Records[index].b + Records[index].a * 2 + 8;
}

// FUNCTION: GAMEMD 0x42D510
ShortPair2 ShortPair2::FUN_0042D510(const ShortPair2* other) const
{
    ShortPair2 result;

    result.x = other->x + x;
    result.y = other->y + y;

    return result;
}

// FUNCTION: GAMEMD 0x43AE80
// Only the free is guarded; the clears run either way, as at 0x43AE50.
void Owned_0043AE80::FUN_0043AE80()
{
    if (IsAllocated) {
        FUN_007C8B3D(Buffer);
    }

    Buffer = 0;
    Length = 0;
    IsAllocated = 0;
}
