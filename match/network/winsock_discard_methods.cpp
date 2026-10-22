// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
#include "winsock_discard_methods.h"

static inline void DiscardQueue(WinsockInterfaceClass::WinsockBufferType**& items, int& count,
                                int& inUse, int& pos)
{
    while (count != 0)
    {
        WinsockInterfaceClass::WinsockBufferType* packet = items[0];

        if (packet->IsAllocated != 0)
        {
            operator delete(packet);
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

// FUNCTION: GAMEMD 0x7B1D10  WinsockInterfaceClass::DiscardOutBuffers (slot 6)
void WinsockInterfaceClass::DiscardOutBuffers()
{
    DiscardQueue(OutBuffers.Items, OutBuffers.Count, StaticOutBuffersInUse, StaticOutBufferPos);
    DiscardQueue(AltOutBuffers.Items, AltOutBuffers.Count, StaticAltOutBuffersInUse,
                 StaticAltOutBufferPos);
}
