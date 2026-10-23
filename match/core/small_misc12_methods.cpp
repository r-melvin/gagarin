// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc12_methods.h"

// FUNCTION: GAMEMD 0x408500
// Link the node in after the anchor, add its weight to the running total, and
// point it back at the owner.
void Obj_00408500d::FUN_00408500(Node_00408500* node)
{
    ((ListNode*)((char*)this + 8))->FUN_00407420((ListNode*)node);

    Total += node->at10;

    node->at14 = this;
}

// FUNCTION: GAMEMD 0x411650
// Release the inner buffer, install the vtable, then free conditionally.
void* BSurface_00411650::FUN_00411650(unsigned int flags)
{
    Inner.Clear();

    *(char**)this = VT_007E2198;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x437FD0
// The two arguments reach the interface in the opposite order to the one they
// arrive in: retail pushes the first parameter first, so it ends up rightmost.
void Obj_00437FD0::FUN_00437FD0(int a, int b)
{
    if (Ptr == 0) {
        FUN_007DC720(0x80004003);
    }

    IFACE_CALL2(Ptr, 0xC, b, a);
}

