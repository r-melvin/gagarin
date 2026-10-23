// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
#include "winsock_interface_discard_methods.h"

// FUNCTION: GAMEMD 0x7B1CA0  WinsockInterfaceClass::DiscardInBuffers (slot 5)
// Drain the inbound queue. Each head packet is either handed back to the game
// heap or merely un-marked, then unlinked with DynamicVectorClass::RemoveItem(0)
// written out inline: bounds check, decrement, shift the tail down. Both
// counters are zeroed at the end rather than trusted to have reached zero.
void WinsockInterfaceClass::DiscardInBuffers()
{
    while (InBuffers.Count != 0)
    {
        WinsockBufferType* packet = InBuffers.Items[0];

        if (packet->IsAllocated != 0)
        {
            operator delete(packet);
        }
        else
        {
            packet->InUse = 0;
            StaticInBuffersInUse--;
        }

        if (InBuffers.Count > 0)
        {
            InBuffers.Count--;
            for (int i = 0; i < InBuffers.Count; i++)
                InBuffers.Items[i] = InBuffers.Items[i + 1];
        }
    }

    StaticInBuffersInUse = 0;
    StaticInBufferPos = 0;
}

// The drain, written once and expanded twice. The queue and its two counters
// arrive by reference: with `this`-relative members VC6 hoists the second
// queue's entry test above the first queue's two zeroing stores, whereas
// through references it must keep the load after the stores, which is retail's
// `MOV [..],EBX; MOV [..],EBX; CMP [ESI+0x48],EBX` order.
