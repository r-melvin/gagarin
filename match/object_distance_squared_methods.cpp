// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5F6500 and 0x5F6560, the squared planar
//   distance siblings of the distance routine at 0x5F6440. Both reach the coordinates through
//   vtable slot 18 (+0x48), which fills a caller buffer and returns a pointer to it.
//
// Address index: 0x5F6500 0x5F6560

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/abstract_class.h"
#include "_layout/coord_struct.h"

// FUNCTION: GAMEMD 0x5F6500
// Squared planar distance to another object; zero for a null object.
int AbstractClass::FUN_005F6500(AbstractClass* that)
{
    if (that == 0) {
        return 0;
    }
    CoordStruct a = vf_18();
    CoordStruct b = that->vf_18();
    int dx = a.X - b.X;
    int dy = a.Y - b.Y;
    return dy * dy + dx * dx;
}

// FUNCTION: GAMEMD 0x5F6560
// Squared planar distance to a coordinate.
int AbstractClass::FUN_005F6560(const CoordStruct& coord)
{
    CoordStruct a = vf_18();
    int dx = a.X - coord.X;
    int dy = a.Y - coord.Y;
    return dy * dy + dx * dx;
}
