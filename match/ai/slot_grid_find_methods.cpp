// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x431170.

#include "slot_grid_find_methods.h"

// FUNCTION: GAMEMD 0x431170
//
// Find the first eligible entry in the grid, optionally matching a key. A key of
// -1 means "any", which is why that test short-circuits ahead of the comparison
// against the entry's own key.
//
// The whole search is skipped when +0x60 is clear — the guard is on the object,
// not on the grid contents, so an empty grid is not the same as a disabled one.
Entry_00431170* Grid_00431170::FUN_00431170(int key)
{
    if (this->At_60 == 0) {
        return 0;
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 3; col++) {
            Entry_00431170* entry = this->Slots[row][col];
            if (entry != 0 && (entry->Flags & 2)
                && (key == -1 || key == entry->Key)) {
                return entry;
            }
        }
    }

    return 0;
}
