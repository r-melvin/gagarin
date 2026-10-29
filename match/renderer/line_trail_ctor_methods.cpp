// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x556A20: colour bytes
//   +0..+2, Owner +4, Decrement +8, ActiveSlot +0xC, then the 32 ring entries
//   from +0x10 (x,y,z,flag); the global trail list is at 0xABCB78.

#include "../core/vector_class_operations.h"
#include "../core/header_init_shapes.h"
#include "line_trail.h"

// GLOBAL: GAMEMD 0xABCB50 -- the "no point" coordinate stamped into unused ring entries.
extern HeaderCoordInit DAT_00ABCB50;
// GLOBAL: GAMEMD 0xABCB78 -- every live trail (LineTrail::Array).
extern DynamicVectorClass<LineTrail*> DAT_00ABCB78;

// FUNCTION: GAMEMD 0x556A20
// A new trail is mid-grey, ownerless, fades by 16 per step, has every ring
// entry blank, and is registered in the global list.
LineTrail::LineTrail()
{
    Color[0] = 0x80;
    Color[1] = 0x80;
    Color[2] = 0x80;
    Owner = 0;
    Decrement = 0x10;
    ActiveSlot = 0;
    for (int i = 0; i < 32; i++) {
        Trails[i].Position = DAT_00ABCB50;
        Trails[i].unknown_0C = 0;
    }
    DAT_00ABCB78.AddItem(this);
}

// FUNCTION: GAMEMD 0x556AD0
// Detach from the owner, if any, and drop out of the global list (the
// storage itself is freed by the caller).
LineTrail::~LineTrail()
{
    if (Owner != 0) {
        Owner->AttachedTrail = 0;
        Owner = 0;
    }
    LineTrail* self = this;
    DAT_00ABCB78.RemoveItem(self);
}

// FUNCTION: GAMEMD 0x556D40
// Step every trail, newest first. A trail that has lost its owner and whose
// current ring entry has faded out is removed from the list and freed; the
// others are drawn.
void __cdecl LineTrail::UpdateAll()
{
    int i = DAT_00ABCB78.Count;
    while (--i >= 0) {
        LineTrail* trail = DAT_00ABCB78.Items[i];
        trail->FUN_00556B70();
        if (trail->Owner == 0 && trail->Trails[trail->ActiveSlot].unknown_0C == 0) {
            if (trail != 0) {
                LineTrail* removed = trail;
                DAT_00ABCB78.RemoveItem(removed);
                GameDelete(trail);
            }
        } else {
            trail->FUN_00556C00();
        }
    }
}
