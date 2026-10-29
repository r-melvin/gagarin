// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Globals and the 64-bit return pair read numerically off the user's retail
//   gamemd.exe v1.001 through the local Ghidra CLI at 0x4093F0.
#ifndef GG_MATCH_CORE_TICK_SNAPSHOT_METHODS_H
#define GG_MATCH_CORE_TICK_SNAPSHOT_METHODS_H

#include "../_rt/gg_static_assert.h"

typedef unsigned long (__stdcall *TickFn_004093F0)();
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

// GLOBAL: GAMEMD 0x87E84C — bumped on entry and re-read to detect an update
// that lands while the pair below is being read. Volatile with binary
// evidence: this function is reached through the 0x4093B0 dispatcher both from
// the thread procedure FUN_004095B0 (created by FUN_00409470) and
// from main-thread callers, so the counter is shared between threads. The
// CreateThread call is 0x409511, the thread calls the dispatcher at 0x4095FB,
// and the guard is read at 0x4093F4 and written at 0x4093FA.
extern volatile int DAT_0087E84C;
// GLOBAL: GAMEMD 0x7E1764 — points at the high half of the running count.
extern int* const DAT_007E1764;
// GLOBAL: GAMEMD 0x7E1760 — points at the low half.
extern unsigned int* const DAT_007E1760;
// GLOBAL: GAMEMD 0x816320 — the 64-bit value handed back.
extern __int64 DAT_00816320;

GG_STATIC_ASSERT(sizeof(DAT_0087E84C) == 4);
GG_STATIC_ASSERT(sizeof(DAT_007E1764) == 4);
GG_STATIC_ASSERT(sizeof(DAT_007E1760) == 4);
GG_STATIC_ASSERT(sizeof(DAT_00816320) == 8);

// FUNCTION: GAMEMD 0x4093F0
__int64 FUN_004093F0();

#endif  // GG_MATCH_CORE_TICK_SNAPSHOT_METHODS_H
