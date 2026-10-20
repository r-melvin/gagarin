// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4A94F0 / 0x4A95A0.

#include "display_class_foundation_methods.h"

// FUNCTION: GAMEMD 0x4A94F0  DisplayClass::FoundationBoundsSize (__thiscall, ret 0x8)
//
// Bounding-box size, in cells, of a foundation offset list. The list is a
// run of CellStruct offsets ended by (0x7FFF, 0x7FFF); each axis's extent is
// max - min + 1 clamped to at least 1. A null list yields (0, 0). The 4-byte
// struct comes back through the hidden return pointer (a member function),
// which is why RET is 8 with `this` unused.
CellStruct DisplayClass::FoundationBoundsSize(CellStruct const* foundation) const
{
    CellStruct size;
    int minX = 0x200;
    int maxX = -0x200;
    int minY = 0x200;
    int maxY = -0x200;

    size.X = 0;
    size.Y = 0;

    if (foundation != 0) {
        while (foundation->X != 0x7FFF || foundation->Y != 0x7FFF) {
            int x = foundation->X;
            int y = foundation->Y;
            maxX = max(maxX, x);
            minX = min(minX, x);
            maxY = max(maxY, y);
            minY = min(minY, y);
            foundation++;
        }
        size.X = (short)max(1, maxX - minX + 1);
        size.Y = (short)max(1, maxY - minY + 1);
    }
    return size;
}

// FUNCTION: GAMEMD 0x4A95A0  DisplayClass::MarkFoundation (__thiscall, ret 0x8)
//
// Set (or clear) the foundation bit on every cell of the current foundation
// placed at `baseCell`. The sentinel base cell at 0x8A03F8 is a no-op; every
// offset in CurrentFoundationData is added to the base, checked for legality
// and, when legal, has bit 1 of its cell's flags word set or cleared.
//
// The post-increment is its own statement: `*data++ + *baseCell` in one
// expression lets VC6 hoist the base-X load ahead of the pointer copy and
// scores 84.6%; naming the element first reproduces retail's "copy pointer,
// load both halves, add both halves" order exactly.
void DisplayClass::MarkFoundation(CellStruct const* baseCell, bool mark)
{
    if (baseCell->X != DAT_008A03F8.X || baseCell->Y != DAT_008A03F8.Y) {
        CellStruct const* data = CurrentFoundationData;
        while (data->X != 0x7FFF || data->Y != 0x7FFF) {
            CellStruct const* offset = data++;
            CellStruct cell = *offset + *baseCell;
            if (CoordinatesLegal(cell)) {
                CellClass* pCell = GetCellAt(cell);
                if (mark) {
                    pCell->Flags |= 2;
                } else {
                    pCell->Flags &= ~2;
                }
            }
        }
    }
}
