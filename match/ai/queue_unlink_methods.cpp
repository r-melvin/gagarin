// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41DC80.

#include "queue_unlink_methods.h"

// FUNCTION: GAMEMD 0x41DC80
//
// Unlink a node from a singly-linked queue. The head is a special case; anything
// else is found by walking, and the walk is capped at 0x65 steps so a corrupt
// list cannot spin forever.
//
// After a successful unlink the cursor is set to null rather than advanced, which
// ends the walk immediately — the node can only be in the list once, so there is
// nothing left to find. That is written as an explicit `else` on the advance
// rather than by zeroing the lookahead: retail zeroes the cursor in the match
// branch and jumps over the advance (0x41DCDF/0x41DCE1), where zeroing the
// lookahead lets VC6 merge both paths into one unconditional advance.
//
// The cap is written `steps <= 0x64`, not `steps < 0x65`: retail compares
// against 0x64 with `JG`, and the other spelling gives `CMP 0x65; JGE`.
//
// MATCHED 100% (47/47). The residual was an adjacent store/load swap in the
// idle-stamp block, not a register choice: both builds load the counter into
// EDX, but retail issues that load *before* the first flag-byte store and cl
// issued it between the two. Writing the stamp store first in the source is
// what fixes it — the two flag bytes then follow, and cl schedules the byte
// stores around the load exactly as retail does. (The earlier note here read
// the delta as an EAX-vs-EDX encoding choice; that reading was wrong.)
// Measured in one compile against this address: the stamp store first 100%,
// the stamp between the flag stores 95.7%, the stamp read through a local
// 93.6%, through a volatile local 93.6%, volatile flag-byte stores 95.7%, and
// a volatile stamp store 95.7%.
//
// Emptying the queue stamps the frame counter and clears the two flag bytes, so
// a caller can tell how long it has been idle.
void Owner_0041DC80::FUN_0041DC80(Node_0041DC80* node)
{
    int zero = 0;
    int steps = 0;
    Node_0041DC80* cursor = this->Head;

    if (cursor == node) {
        this->Head = node->Next;
        node->Next = 0;
        this->Active = this->Active - 1;
        node->At_294 = zero;
    } else {
        do {
            if (cursor == (Node_0041DC80*)zero) {
                break;
            }

            Node_0041DC80* next = cursor->Next;
            if (next == node) {
                cursor->Next = node->Next;
                node->Next = 0;
                cursor = 0;
                this->Active = this->Active - 1;
                node->At_294 = zero;
            } else {
                cursor = next;
            }

            steps++;
        } while (steps <= 0x64);
    }

    if (this->Active <= zero) {
        this->field_40 = DAT_00A8ED84;
        this->field_3C = (char)zero;
        this->field_3D = (char)zero;
    }
}
