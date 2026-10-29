// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "guarded_forward_methods.h"
#include "../platform/pk_blow_pipes.h"

// FUNCTION: GAMEMD 0x437FC0
BlockCipherView::~BlockCipherView()
{
    if (Interface) {
        IFACE_CALL(Interface, 0x8);
    }
}

