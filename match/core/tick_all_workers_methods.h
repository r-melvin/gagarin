// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x408270. Imports read from the IAT thunks at 0x7E11E8
//   (EnterCriticalSection) and 0x7E11EC (LeaveCriticalSection); the same pair
//   already recorded in small_misc28.
#ifndef GG_MATCH_CORE_TICK_ALL_WORKERS_METHODS_H
#define GG_MATCH_CORE_TICK_ALL_WORKERS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// KERNEL32, dllimport so the calls go indirect through the IAT.
struct CRITICAL_SECTION_ { char opaque[24]; };
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION_*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION_*);

// GLOBAL: GAMEMD 0x87E7F8 — the section guarding the worker list.
extern CRITICAL_SECTION_ DAT_0087E7F8;

struct Entry_00408270
{
    char _pad000[0xC];      // +0x0000
    int  Flags;             // +0x000C  bit 0 requested, bit 1 running
    char _pad010[0x4];      // +0x0010
    int  Worker;            // +0x0014
    char _pad018[0x68];     // +0x0018
    int  Ticks;             // +0x0080
};
GG_STATIC_ASSERT(offsetof(Entry_00408270, Flags) == 0xC);
GG_STATIC_ASSERT(offsetof(Entry_00408270, Worker) == 0x14);
GG_STATIC_ASSERT(offsetof(Entry_00408270, Ticks) == 0x80);

struct List_00408270 { char opaque[0xC]; };

// GLOBAL: GAMEMD 0x87E810 — the worker list.
extern List_00408270 DAT_0087E810;
// GLOBAL: GAMEMD 0x87E81C — nonzero once the list is live.
extern int DAT_0087E81C;

// FUNCTION: GAMEMD 0x4073C0 — first entry, or null.
Entry_00408270* FUN_004073C0(List_00408270* list);
// FUNCTION: GAMEMD 0x4073E0 — next entry, or null.
Entry_00408270* FUN_004073E0(Entry_00408270* entry);
// FUNCTION: GAMEMD 0x402600 — kick one worker.
void FUN_00402600(int worker);

// FUNCTION: GAMEMD 0x408270
void FUN_00408270();

#endif  // GG_MATCH_CORE_TICK_ALL_WORKERS_METHODS_H
