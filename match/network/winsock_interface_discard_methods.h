// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x7B1CA0. 0x007C8B3D is the game-heap deallocator
//   already bound in match/combat/veinhole_monster_deleteall_methods.h.
//
// The receiver embeds its queue at +0x0C/+0x18 (Items/Count of a vector) and
// keeps two counters far out at +0x3F050 and +0x3F05C, past the fixed-size
// packet storage.
#ifndef GG_MATCH_NETWORK_WINSOCK_INTERFACE_DISCARD_METHODS_H
#define GG_MATCH_NETWORK_WINSOCK_INTERFACE_DISCARD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// YR game-heap deallocator @0x007C8B3D (__cdecl, single pointer argument).
void __cdecl GameDeallocate(void* ptr);

// A queued inbound packet. Only the two flag bytes are read; they keep
// placeholder names because the bytes fix their offsets, not their meaning.
struct WinsockPacket
{
    char          _pad00[0x15];  // +0x00
    unsigned char unknown_15;    // +0x15  cleared on the retained path
    unsigned char unknown_16;    // +0x16  non-zero selects the free path
};
GG_STATIC_ASSERT(offsetof(WinsockPacket, unknown_15) == 0x15);
GG_STATIC_ASSERT(offsetof(WinsockPacket, unknown_16) == 0x16);

struct WinsockInterfaceClass
{
    char            _pad00[0x0C];              // +0x00000
    WinsockPacket** Items;                     // +0x0000C
    char            _pad10[0x18 - 0x10];       // +0x00010
    int             Count;                     // +0x00018
    char            _pad1C[0x3F050 - 0x1C];    // +0x0001C
    int             unknown_3F050;             // +0x3F050
    char            _pad3F054[0x3F05C - 0x3F054];
    int             unknown_3F05C;             // +0x3F05C  decremented per retained packet

    void DiscardInBuffers();                   // GAMEMD 0x7B1CA0
};
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, Items)         == 0x0C);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, Count)         == 0x18);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, unknown_3F050) == 0x3F050);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, unknown_3F05C) == 0x3F05C);

#endif  // GG_MATCH_NETWORK_WINSOCK_INTERFACE_DISCARD_METHODS_H
