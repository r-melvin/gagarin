// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001: the static initialisers at 0x579320 and 0x57A9C0
//   fill two arrays of cell offsets with the (short, short) constructor at
//   0x42D470 (see _layout/cell_offset.h). Entries are read from the stores in
//   the initialisers.
//
//   Ordered ascending by retail address.

#include "../_layout/cell_offset.h"

// SYNTHETIC: GAMEMD 0x579320 -- static initialiser of DAT_00ABDDA8
// GLOBAL: GAMEMD 0xABDDA8
CellOffset DAT_00ABDDA8[40] = {
    CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(1, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0)
};

// SYNTHETIC: GAMEMD 0x57A9C0 -- static initialiser of DAT_00ABDB68
// GLOBAL: GAMEMD 0xABDB68
CellOffset DAT_00ABDB68[42] = {
    CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -2),
    CellOffset(-1, -2), CellOffset(-1, -1), CellOffset(-1, -1), CellOffset(-1, 0), CellOffset(-1, 0),
    CellOffset(-1, 0), CellOffset(-1, 0), CellOffset(-2, -1), CellOffset(-2, 0), CellOffset(-1, 0),
    CellOffset(-1, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(-1, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0),
    CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, -1), CellOffset(0, 0),
    CellOffset(0, -1), CellOffset(0, -1), CellOffset(-1, -1), CellOffset(-1, -1), CellOffset(-1, 0),
    CellOffset(-1, 0), CellOffset(0, 0), CellOffset(0, 0), CellOffset(0, -1), CellOffset(0, -1),
    CellOffset(0, 0), CellOffset(0, 0)
};
