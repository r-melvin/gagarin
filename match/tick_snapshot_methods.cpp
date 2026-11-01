// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at 0x4093F0.

#include "tick_snapshot_methods.h"

// GLOBAL: GAMEMD 0x816320
__int64 DAT_00816320 = 0x100000000i64;
// GLOBAL: GAMEMD 0x87E84C
volatile int DAT_0087E84C;
// Retail read-only pointer slots contain 0x816320 and 0x816324; entry
// 0x4093F0 reads and writes those two native 32-bit halves.
// GLOBAL: GAMEMD 0x7E1760
unsigned int* const DAT_007E1760 = (unsigned int*)&DAT_00816320;
// GLOBAL: GAMEMD 0x7E1764
int* const DAT_007E1764 = (int*)((char*)&DAT_00816320 + 4);

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

    source = timeGetTime;
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
