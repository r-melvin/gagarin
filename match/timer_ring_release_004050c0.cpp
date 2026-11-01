// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, globals and call targets read off retail gamemd.exe v1.001 at
//   0x4050C0 via the local Ghidra CLI. The ring is the same one
//   0x405040 walks (header 0x87E180, gate 0x87E2A0).

#include "small_misc43_methods.h"
#include "small_misc45_methods.h"

// FUNCTION: GAMEMD 0x4050C0
// PARTIAL: 87.5%. Same instructions in retail order except two scheduling swaps:
// retail loads the next link before the flag byte, and clears +0x138 before it
// reloads the flag byte (the same delta as FUN_00404DD0). Not steered.
// Release every ring node marked for release (bit 0): the same retirement as
// 0x404DD0, either freeing the block or handing it back to the pool.
void __cdecl FUN_004050C0()
{
    if (DAT_0087E2A0 == 0) {
        return;
    }

    Obj_004053E0* node = DAT_0087E180.Next;

    if (node == &DAT_0087E180) {
        return;
    }

    do {
        Obj_004053E0* next = node->Next;

        if (node->Flags & 1) {
            FUN_00407450(node);
            node->Pending = 0;

            if (node->Flags & 0x80) {
                FUN_007C8B3D(node);
            } else {
                FUN_00407530(DAT_0087E2A8, node);
            }

            DAT_0087E28C--;
        }

        node = next;
    } while (node != &DAT_0087E180);
}
