// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Globals and the 64-bit return pair read numerically off the user's retail
//   gamemd.exe v1.001 through the local Ghidra CLI at 0x4093F0.
#ifndef GG_MATCH_CORE_TICK_SNAPSHOT_METHODS_H
#define GG_MATCH_CORE_TICK_SNAPSHOT_METHODS_H

typedef unsigned int (*TickFn_004093F0)();

// GLOBAL: GAMEMD 0x87E84C — bumped on entry and re-read to detect an update
// that lands while the pair below is being read; volatile is what forces the
// repeated loads retail performs.
extern volatile int DAT_0087E84C;
// GLOBAL: GAMEMD 0x7E1764 — points at the high half of the running count.
extern int* DAT_007E1764;
// GLOBAL: GAMEMD 0x7E1760 — points at the low half.
extern unsigned int* DAT_007E1760;
// GLOBAL: GAMEMD 0x7E1530 — the raw counter source.
extern TickFn_004093F0 DAT_007E1530;
// GLOBAL: GAMEMD 0x816320 — the 64-bit value handed back.
extern __int64 DAT_00816320;

// FUNCTION: GAMEMD 0x4093F0
__int64 FUN_004093F0();

#endif  // GG_MATCH_CORE_TICK_SNAPSHOT_METHODS_H
