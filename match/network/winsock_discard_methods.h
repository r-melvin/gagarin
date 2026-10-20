// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x7B1D10: the two queues as `[ESI+0x24]`/`[ESI+0x30]`
//   (Items/Count of the out vector) and `[ESI+0x3C]`/`[ESI+0x48]` (the
//   alternate out vector), the four far counters `[ESI+0x3F060]`,
//   `[ESI+0x3F054]`, `[ESI+0x3F064]`, `[ESI+0x3F058]`, and the packet flag
//   bytes `CMP byte ptr [EAX+0x16],BL` / `MOV byte ptr [EAX+0x15],BL`.
//   0x007C8B3D is the game-heap deallocator already bound in
//   match/network/winsock_interface_discard_methods.h. Member names follow
//   YRpp WinsockInterfaceClass.h (consult-only; names only).
//
// Sister of DiscardInBuffers (0x7B1CA0, matched): the same drain written out
// twice, once for OutBuffers and once for AltOutBuffers.
#ifndef GG_MATCH_NETWORK_WINSOCK_DISCARD_METHODS_H
#define GG_MATCH_NETWORK_WINSOCK_DISCARD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) -- the game-heap deallocator.
void __cdecl GameDeallocate(void* ptr);

// A queued packet. Only the two flag bytes are touched: +0x16 (Allocated in
// YRpp's naming) selects the free path, +0x15 (InUse) is cleared otherwise.
struct WinsockPacket_007B1D10
{
    char          _pad00[0x15];  // +0x00
    unsigned char InUse;         // +0x15
    unsigned char Allocated;     // +0x16
};
GG_STATIC_ASSERT(offsetof(WinsockPacket_007B1D10, InUse)     == 0x15);
GG_STATIC_ASSERT(offsetof(WinsockPacket_007B1D10, Allocated) == 0x16);

struct WinsockInterfaceClass_007B1D10
{
    char                     _pad00[0x24];                 // +0x00000
    WinsockPacket_007B1D10** OutItems;                     // +0x00024  OutBuffers.Items
    char                     _pad28[0x30 - 0x28];          // +0x00028
    int                      OutCount;                     // +0x00030  OutBuffers.Count
    char                     _pad34[0x3C - 0x34];          // +0x00034
    WinsockPacket_007B1D10** AltOutItems;                  // +0x0003C  AltOutBuffers.Items
    char                     _pad40[0x48 - 0x40];          // +0x00040
    int                      AltOutCount;                  // +0x00048  AltOutBuffers.Count
    char                     _pad4C[0x3F054 - 0x4C];       // +0x0004C
    int                      StaticOutBufferPos;           // +0x3F054
    int                      StaticAltOutBufferPos;        // +0x3F058
    char                     _pad3F05C[0x3F060 - 0x3F05C]; // +0x3F05C
    int                      StaticOutBuffersInUse;        // +0x3F060
    int                      StaticAltOutBuffersInUse;     // +0x3F064

    // FUNCTION: GAMEMD 0x7B1D10
    void DiscardOutBuffers();
};
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass_007B1D10, OutItems)                 == 0x24);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass_007B1D10, OutCount)                 == 0x30);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass_007B1D10, AltOutItems)              == 0x3C);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass_007B1D10, AltOutCount)              == 0x48);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass_007B1D10, StaticOutBufferPos)       == 0x3F054);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass_007B1D10, StaticAltOutBufferPos)    == 0x3F058);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass_007B1D10, StaticOutBuffersInUse)    == 0x3F060);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass_007B1D10, StaticAltOutBuffersInUse) == 0x3F064);

#endif  // GG_MATCH_NETWORK_WINSOCK_DISCARD_METHODS_H
