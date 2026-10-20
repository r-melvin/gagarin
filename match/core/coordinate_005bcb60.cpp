// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original

#include "coordinate_005bcb60.h"

// The temporary point keeps both calculations ahead of the stores, as in retail.
// FUNCTION: GAMEMD 0x5BCB60
Point_005BCB60* Point_005BCB60::Convert(int x, int y)
{
    Point_005BCB60 result;
    result.X = x * ABF1E0 + 10;
    result.Y = y * (ABF1C8 + ABF1D8) + 10;
    *this = result;
    return this;
}
