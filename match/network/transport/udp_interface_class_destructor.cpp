// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI
// Entry-origin retail destructor spans confirm the two address-release loops,
// shared shutdown/base destructor calls, and vector-member destruction.
// VC6FLAGS: /nologo /c /O2 /Ob2 /DNDEBUG /Gy
#include <new>
#include "udp_interface_class.h"

// Source helper expanded into each retail loop; no standalone entry is claimed.
static inline void DeleteAddresses(DynamicVectorClass<unsigned char*>& addresses)
{
    while (addresses.ActiveCount != 0)
    {
        operator delete(addresses.Items[0]);
        if (addresses.ActiveCount > 0)
        {
            addresses.ActiveCount--;
            for (int i = 0; i < addresses.ActiveCount; i++)
                addresses.Items[i] = addresses.Items[i + 1];
        }
    }
}

// FUNCTION: GAMEMD 0x7B2E50
UDPInterfaceClass::~UDPInterfaceClass()
{
    DeleteAddresses(BroadcastAddresses);
    DeleteAddresses(LocalAddresses);
    ShutdownWinsock();
}

// SYNTHETIC: GAMEMD 0x7B4170
// Scalar deleting destructor emitted naturally with /Ob2 in this real TU.
