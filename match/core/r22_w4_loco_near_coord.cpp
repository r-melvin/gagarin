// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Locomotor coordinate proximity test read off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI.
//   Address index: 0x75CA80.

#include <stdlib.h>
#include "../_layout/coord_struct.h"
#include "../_layout/cell.h"

// A COM locomotor interface: only slot 6 (the current coordinate) is used here.
struct ILocomotion_0075CA80 {
    virtual void __stdcall vf_000();
    virtual void __stdcall vf_001();
    virtual void __stdcall vf_002();
    virtual void __stdcall vf_003();
    virtual void __stdcall vf_004();
    virtual void __stdcall vf_005();
    virtual CoordStruct* __stdcall vf_006(CoordStruct* out);
};

// GLOBAL: GAMEMD 0xB45C28
extern int DAT_00B45C28;

// FUNCTION: GAMEMD 0x75CA80
// True when the locomotor's coordinate lies in the same cell column and row as (x, y) and within
// the height tolerance of z.
bool __stdcall FUN_0075CA80(ILocomotion_0075CA80* loco, int x, int y, int z)
{
    CoordStruct tmp;
    CoordStruct cur = *loco->vf_006(&tmp);
    CellStruct want;
    want.X = x / 256;
    want.Y = y / 256;
    CellStruct cell;
    cell.X = cur.X / 256;
    cell.Y = cur.Y / 256;
    if (cell.X == want.X && cell.Y == want.Y && abs(cur.Z - z) <= DAT_00B45C28) {
        return true;
    }
    return false;
}
