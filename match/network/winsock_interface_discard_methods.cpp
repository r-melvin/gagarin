// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7B1CA0.

#include "winsock_interface_discard_methods.h"

// FUNCTION: GAMEMD 0x7B1CA0  WinsockInterfaceClass::DiscardInBuffers (__thiscall)
// Drain the inbound queue. Each head packet is either handed back to the game
// heap or merely un-marked, then unlinked with DynamicVectorClass::RemoveItem(0)
// written out inline — bounds check, decrement, shift the tail down. Both
// counters are zeroed at the end rather than trusted to have reached zero.
void WinsockInterfaceClass::DiscardInBuffers()
{
    while (Count != 0)
    {
        WinsockPacket* packet = Items[0];

        if (packet->unknown_16 != 0)
        {
            GameDeallocate(packet);
        }
        else
        {
            packet->unknown_15 = 0;
            unknown_3F05C--;
        }

        if (Count > 0)
        {
            Count--;
            for (int i = 0; i < Count; i++)
                Items[i] = Items[i + 1];
        }
    }

    unknown_3F05C = 0;
    unknown_3F050 = 0;
}
