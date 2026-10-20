// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x409D90.

#include "bounded_copy_methods.h"

// FUNCTION: GAMEMD 0x409D90
//
// A zero-length copy is still a success: retail's early exit sets EAX to 1 the
// same as the copying path, it just skips the move and the two writebacks.
int __fastcall FUN_00409D90(void* unused, void* destination,
                            int* destinationLength,
                            const void* source, int* sourceLength)
{
    int count = *destinationLength;

    if (count > *sourceLength) {
        count = *sourceLength;
    }

    if (count != 0) {
        memcpy(destination, source, count);

        *destinationLength = count;
        *sourceLength      = count;
    }

    return 1;
}
