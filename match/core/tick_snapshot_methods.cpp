// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at 0x4093F0.

#include "tick_snapshot_methods.h"

// FUNCTION: GAMEMD 0x4093F0
//
// Read the running 64-bit count without tearing. The guard is re-read until it
// stops moving, the raw source is sampled, the high half is carried when the
// low half wraps, and the pair is written back; a guard change during the write
// restarts the sample.
__int64 FUN_004093F0()
{
    int guard;
    int high;
    unsigned int low;
    TickFn_004093F0 source;
    unsigned int now;

    DAT_0087E84C = DAT_0087E84C + 1;
    guard = DAT_0087E84C;

    high = *DAT_007E1764;
    low = *DAT_007E1760;

    while (guard != DAT_0087E84C) {
        guard = DAT_0087E84C;
    }

    source = DAT_007E1530;
    for (;;) {
        now = source();
        if (now < low) {
            high++;
        }
        *DAT_007E1764 = high;
        *DAT_007E1760 = now;
        if (guard == DAT_0087E84C) {
            break;
        }
        guard = DAT_0087E84C;
    }

    return DAT_00816320;
}
