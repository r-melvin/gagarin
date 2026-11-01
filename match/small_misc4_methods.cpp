// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc4_methods.h"

// FUNCTION: GAMEMD 0x407040
// Release. Nothing happens at zero, and the teardown runs only on the
// transition to zero - a second release of an already-idle count is inert.
void __cdecl FUN_00407040()
{
    if (DAT_0087E730 != 0) {
        if (--DAT_0087E730 == 0) {
            FUN_0040A950();
        }
    }
}

// FUNCTION: GAMEMD 0x408080
void Obj_00408080::FUN_00408080(int fill)
{
    FUN_007C91D0(Buffer, fill, sizeof(Buffer));

    Buffer[sizeof(Buffer) - 1] = 0;
}

// FUNCTION: GAMEMD 0x4080D0
// True when the flag is set and the inner pair disagree.
int Obj_00408000c::FUN_004080D0() const
{
    return (Flags & 1) && unknown_14->at14 != unknown_14->at18;
}

// FUNCTION: GAMEMD 0x4085E0
void Obj_004085E0::FUN_004085E0(int a, int b)
{
    unknown_10 = b;
    unknown_0C = a;

    FUN_004072D0b(this);

    unknown_14 = 0;
}

