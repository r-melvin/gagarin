// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4022C0 and 0x42F180.

#include "small_misc55_methods.h"

// FUNCTION: GAMEMD 0x4022C0
int FUN_004022C0(Obj_004022C0* self)
{
    // The override path is the fall-through: retail's `JZ` at 0x4022CE jumps
    // forward to the node walk, so the guard is written positively.
    Override_004022C0 handler = self->Override;

    if (handler != 0) {
        int handled = handler();

        if (handled != 0) {
            self->CachedB = 0;
            self->CachedC = 0;
            self->CachedA = 0;

            return handled;
        }
    } else {
        Node_004022C0* node = self->Node;

        if (node != 0) {
            node = FUN_00407470(node);

            self->Node = node;

            if (node != 0) {
                // Store, then read the shared value, then its two stores - the
                // same interleave retail uses at 0x402790.
                self->CachedA = node->First;

                int second = node->Second;

                self->CachedB = second;
                self->CachedC = second;

                return 0;
            }
        }

        self->CachedB = 0;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x42F180
void Table_0042F180::FUN_0042F180(Sink_0042F180* sink)
{
    sink->FUN_004A1D50(Count);

    for (int i = 0; i < Count; i++) {
        sink->FUN_004A1D50(Records[i].Value);
        sink->FUN_004A1D30(Records[i].Low);
        sink->FUN_004A1D30(Records[i].High);
    }
}
