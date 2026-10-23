// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The event ring buffers. The run-time initialisers 0x4E7EA0 (128 events at
//   0xA802C8), 0x4E7ED0 (0x4000 at 0x8B41F8) and 0x4E7F00 (0x100 at
//   0xA83ED0) clear each event's type byte (stride 0x6F) and then the three
//   leading dwords; the append inlined at 0x4E1E59 stores the event at
//   +0x0C + Head * 0x6F and its send time at +0x0C + N * 0x6F + Head * 4.
#ifndef GG_MATCH_NETWORK_EVENT_QUEUE_H
#define GG_MATCH_NETWORK_EVENT_QUEUE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "event_class_ctors.h"

template<int N>
struct EventQueue
{
    int           Count;        // +0x00
    int           unknown_04;   // +0x04
    int           Head;         // +0x08
    EventClass    List[N];      // +0x0C
    unsigned long Time[N];      // +0x0C + N * 0x6F

    // FUNCTION: GAMEMD 0x652540 (decl; reloc)
    // EventQueue<128>::FUN_00652540
    int FUN_00652540();

    EventQueue()
    {
        Count = 0;
        unknown_04 = 0;
        Head = 0;
    }
};

#endif  // GG_MATCH_NETWORK_EVENT_QUEUE_H
