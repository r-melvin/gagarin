// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of retail gamemd.exe v1.001 at 0x4F1AA0.
//
// Address index: 0x4F1AA0 EventQueue<128>::FUN_004F1AA0.

#include "event_queue.h"

// WinMM import: GAMEMD 0x007E1530 (timeGetTime).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

// FUNCTION: GAMEMD 0x4F1AA0
// Append `*item` at the head slot, stamp it with the wall-clock time, and
// advance the head (modulo 128). Returns 0 when the queue already holds 128.
template<>
int EventQueue<128>::FUN_004F1AA0(const EventQueueItem* item)
{
    if (Count < 128) {
        List[Head] = *item;
        Time[Head] = timeGetTime();
        Head = (Head + 1) & 0x7F;
        Count++;
        return 1;
    }
    return 0;
}
