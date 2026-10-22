// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x632D10 and
//   0x6330C0. Ordered ascending by retail address.

#include "observable_node_link_methods.h"

// FUNCTION: GAMEMD 0x632D10
//
// Re-point the slot at a node. Setting the slot to what it already holds is a
// no-op. Otherwise the new node is first detached from whatever slot currently
// owns it (a virtual call on its back-pointer, then the back-pointer cleared),
// the outgoing node's back-pointer is cleared, and the slot is rewired: it
// takes the node, records itself as the owner, and publishes the address of
// its embedded subobject both to itself and to the node.
void LinkSlotA::SetTarget(LinkNodeA* newTarget)
{
    if (Target != newTarget) {
        if (newTarget != 0 && newTarget->Back != 0) {
            newTarget->Back->Detach(0);
            newTarget->Back = 0;
        }
        if (Target != 0) {
            Target->Back = 0;
        }
        Target = newTarget;
        if (newTarget != 0) {
            newTarget->Back = (LinkBackA*)&Embedded;
        }
        Owner = this;
        BackRef = &Embedded;
    }
}

// FUNCTION: GAMEMD 0x6330C0
//
// The second instance. Two differences from 0x632D10, both visible in the
// bytes: the detach lands on vtable slot 1 rather than slot 3, and the node's
// back-pointer is set to the slot itself rather than to its embedded
// subobject. The statement order differs with it: here the conditional store
// into the node comes last, after the slot has finished rewiring itself, which
// is what lets cl hoist the `LEA` for BackRef and both unconditional stores
// above the test. With the conditional store written first, as at 0x632D10,
// the whole tail schedules the other way round and ESI and EDI swap roles
// across the entire body (51.7%).
void LinkSlotB::SetTarget(LinkNodeB* newTarget)
{
    if (Target != newTarget) {
        if (newTarget != 0 && newTarget->Back != 0) {
            newTarget->Back->Detach(0);
            newTarget->Back = 0;
        }
        if (Target != 0) {
            Target->Back = 0;
        }
        Target = newTarget;
        Owner = this;
        BackRef = &Embedded;
        if (newTarget != 0) {
            newTarget->Back = (LinkBackB*)this;
        }
    }
}
