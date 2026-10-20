// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7B1D10.

#include "winsock_discard_methods.h"

// The drain, written once and expanded twice. Each head packet is either
// handed back to the game heap or merely un-marked, then unlinked with the
// inlined DynamicVectorClass::RemoveItem(0) -- bounds check, decrement, shift
// the tail down. The in-use counter and the static-buffer cursor are zeroed
// at the end rather than trusted to have reached zero.
//
// The queue and its two counters arrive by reference: with `this`-relative
// members VC6 hoists the second queue's entry test above the first queue's
// two zeroing stores (it can prove the offsets disjoint, 47.3%), whereas
// through references it must keep the load after the stores -- which is
// retail's `MOV [..],EBX; MOV [..],EBX; CMP [ESI+0x48],EBX` order.
static inline void DiscardQueue(WinsockPacket_007B1D10**& items, int& count,
                                int& inUse, int& pos)
{
    while (count != 0)
    {
        WinsockPacket_007B1D10* packet = items[0];

        if (packet->Allocated != 0)
        {
            GameDeallocate(packet);
        }
        else
        {
            packet->InUse = 0;
            inUse--;
        }

        if (count > 0)
        {
            count--;
            for (int i = 0; i < count; i++)
                items[i] = items[i + 1];
        }
    }

    inUse = 0;
    pos = 0;
}

// Drain both outbound queues: OutBuffers first, then AltOutBuffers.
// FUNCTION: GAMEMD 0x7B1D10  WinsockInterfaceClass::DiscardOutBuffers (__thiscall)
void WinsockInterfaceClass_007B1D10::DiscardOutBuffers()
{
    DiscardQueue(OutItems, OutCount, StaticOutBuffersInUse, StaticOutBufferPos);
    DiscardQueue(AltOutItems, AltOutCount, StaticAltOutBuffersInUse, StaticAltOutBufferPos);
}
