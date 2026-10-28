// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
//   Bytes matched against retail gamemd.exe v1.001 at 0x50DA20, 0x50DAA0 and 0x50DAC0
//   (small HouseClass members between the cell helpers of House.cpp).
#include "../_layout/house_class.h"
#include "../core/frame_counter.h"

// FUNCTION: GAMEMD 0x50DA20
// Remember a preferred defensive cell and the frame it was chosen on.
void HouseClass::FUN_0050DA20(CellStruct cell)
{
    PreferredDefensiveCell = cell;
    PreferredDefensiveCellStartTime = CurrentFrame;
}

// FUNCTION: GAMEMD 0x50DAA0
// The house's starting edge when it is a valid edge index (0..3), else 0.
int HouseClass::FUN_0050DAA0() const
{
    if (StartingEdge < 0 || StartingEdge > 3) {
        return 0;
    }
    return StartingEdge;
}

// FUNCTION: GAMEMD 0x50DAC0
// The edge opposite the house's current edge.
int HouseClass::FUN_0050DAC0() const
{
    switch (Edge) {
    case 0:
        return 2;
    case 1:
        return 3;
    case 2:
        return 0;
    case 3:
        return 1;
    }
    return 0;
}
