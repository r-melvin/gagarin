// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x438060.

#include "small_misc30_methods.h"

// FUNCTION: GAMEMD 0x438060
// The pending length is cleared and the second flush runs whether or not the
// first one did - both early-outs land on the clear, not on the return.
int Obj_00438060::FUN_00438060()
{
    int written = 0;

    int length = PendingLen;

    if (length > 0 && unknown_0C != 0) {
        written = FUN_00631D10(Pending, length);
    }

    PendingLen = 0;

    return FUN_00631D30() + written;
}
