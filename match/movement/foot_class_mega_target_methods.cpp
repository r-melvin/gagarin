// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.
//   MegaDestination +0x5C8 and MegaTarget +0x5CC are pinned in foot_class.h.

#include "foot_class_move_to_weed_methods.h"

// Coordinate to cell (256 leptons per cell); inlined at the call site.
static inline Cell CellOfCoord(const CoordStruct& coord)
{
    Cell cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x4DF280
// Replaces the mega target with the map cell it stands on as the mega destination.
void FootClass::FUN_004DF280()
{
    if (MegaTarget) {
        Cell cell = CellOfCoord(((AbstractClass*)MegaTarget)->vf_18());
        MegaDestination = DAT_0087F7E8.FUN_005657A0(&cell);
        MegaTarget = 0;
        return;
    }
    MegaDestination = 0;
    MegaTarget = 0;
}
