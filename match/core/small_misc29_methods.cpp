// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x40A900.

#include "small_misc29_methods.h"

// FUNCTION: GAMEMD 0x40A900
// The clamp is two separate tests rather than a min/max pair, and each arm
// falls into its own copy of the table load - retail duplicates the tail
// instead of merging the paths.
int __fastcall FUN_0040A900(int value)
{
    int percent = value * 100 / 256;

    if (percent > 100) {
        percent = 100;
    } else if (percent < 0) {
        percent = 0;
    }

    return DAT_00816380[percent];
}
