// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. A small tactical-map helper
//   from the 0x6D8000 range.
//
// Address index: 0x6D84D0

#include "../_layout/geometry2d.h"

// FUNCTION: GAMEMD 0x6D8640 (decl; reloc) -- adjusts a coordinate in place, reporting whether it did.
bool __stdcall FUN_006D8640(Point2D* point);

// GLOBAL: GAMEMD 0xA8ED6B -- when set, coordinates are left alone.
extern bool DAT_00A8ED6B;

// FUNCTION: GAMEMD 0x6D84D0
// PARTIAL: 80.6% -- identical instruction multiset; retail copies the two words into the temporary
// before taking its address, this order takes the address first (field-wise, constructor and
// aggregate copies tried).
// The adjusted copy of a coordinate, or the coordinate unchanged when the adjustment fails or is disabled.
Point2D __stdcall FUN_006D84D0(const Point2D* point)
{
    int x = point->X;
    int y = point->Y;
    Point2D adjusted(x, y);
    if (FUN_006D8640(&adjusted) && !DAT_00A8ED6B) {
        return adjusted;
    }
    return *point;
}
