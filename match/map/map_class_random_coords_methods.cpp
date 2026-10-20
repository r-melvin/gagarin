// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x49F420.

#include "map_class_random_coords_methods.h"

// FUNCTION: GAMEMD 0x49F420
//
// A point at the given distance from a coordinate in a random direction:
// one random byte becomes the facing, converted to radians, and the offset
// is laid out with the table sin/cos. A result off the 512-cell map falls
// back to the source; with `center` the point snaps to its cell centre.
//
// PARTIAL (77.2%, 71/92, identical instruction multiset). Load-bearing and
// matched: the direction is built through an address-taken alias so the
// zeroed 16-bit value is stored before the random draw and the int
// container read back for the bit-field insert (`AND DH,0; OR`), the two
// conversions to double are spilled around the sin call, the result is
// copy-initialised from a constructor temporary so the working copy lives
// in registers (fallback and centre snap as register ops), and the Y result
// reuses the distance parameter's slot. Residual, all naming and frame
// placement: retail copies the container to EAX before `MOVSX EAX,AX`; it
// places the constructor temporary at frame+0 over the direction and angle
// (hidden pointer +0xC, the two doubles +0x10/+0x18) where cl 8804 puts the
// temporary over the dead second double at +0x14 (hidden pointer +8); and
// the centre-snap masks take EAX/EDX the other way round. Tried: the
// direction as a plain union / int-container bit-field / ctor plus setter /
// named draw (each folds the memory round trip), by-value and by-pointer
// conversion helpers, a named short, an inline random-angle helper, the
// result declared first with the arithmetic in a block, fx/fy declaration
// order, and Z read before or after the draw.
Coord_0049F420 __fastcall MapClass_GetRandomCoordsNear(const Coord_0049F420& coords,
                                                       int distance, bool center)
{
    int x;
    int y;
    int z;
    {
        Dir_0049F420 dir;
        Dir_0049F420* p = &dir;
        p->Bits.High = DAT_00A8B230->Random.Random();
        z = coords.Z;
        double angle = (double)(dir.Signed - 0x3FFF) * DAT_007E2810;
        y = (int)(coords.Y - FUN_004CACB0(angle) * distance);
        x = (int)(FUN_004CAD00(angle) * distance + coords.X);
    }

    Coord_0049F420 result = Coord_0049F420(x, y, z);
    if ((unsigned)(result.X / 256) >= 512 || (unsigned)(result.Y / 256) >= 512) {
        result.X = coords.X;
        result.Y = coords.Y;
        result.Z = coords.Z;
    }
    if (center) {
        int fx = result.X & 0xFF;
        int fy = result.Y & 0xFF;
        result.X -= fx;
        result.Y -= fy;
        result.X += 0x80;
        result.Y += 0x80;
    }
    return result;
}
