// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5F6500 and 0x5F6560, the squared planar
//   distance siblings of the distance routine at 0x5F6440. Both reach the coordinates through
//   vtable slot 18 (+0x48), which fills a caller buffer and returns a pointer to it.
//
// Address index: 0x5F6500 0x5F6560

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Coord3_005F6500
{
    int X;
    int Y;
    int Z;
};

// Placeholder receiver: slots 0..17 are not touched here.
struct AbstractView_005F6500
{
    virtual void vf_00();
    virtual void vf_01();
    virtual void vf_02();
    virtual void vf_03();
    virtual void vf_04();
    virtual void vf_05();
    virtual void vf_06();
    virtual void vf_07();
    virtual void vf_08();
    virtual void vf_09();
    virtual void vf_10();
    virtual void vf_11();
    virtual void vf_12();
    virtual void vf_13();
    virtual void vf_14();
    virtual void vf_15();
    virtual void vf_16();
    virtual void vf_17();
    virtual Coord3_005F6500 GetCoords();   // slot 18, +0x48

    int FUN_005F6500(AbstractView_005F6500* that);
    int FUN_005F6560(const Coord3_005F6500* coord);
};

// FUNCTION: GAMEMD 0x5F6500
// Squared planar distance to another object; zero for a null object.
int AbstractView_005F6500::FUN_005F6500(AbstractView_005F6500* that)
{
    if (that == 0) {
        return 0;
    }
    Coord3_005F6500 a = GetCoords();
    Coord3_005F6500 b = that->GetCoords();
    int dx = a.X - b.X;
    int dy = a.Y - b.Y;
    return dy * dy + dx * dx;
}

// FUNCTION: GAMEMD 0x5F6560
// Squared planar distance to a coordinate.
int AbstractView_005F6500::FUN_005F6560(const Coord3_005F6500* coord)
{
    Coord3_005F6500 a = GetCoords();
    int dx = a.X - coord->X;
    int dy = a.Y - coord->Y;
    return dy * dy + dx * dx;
}
