// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x56D100.
//
// Zone pre-check of a path: true when the zone is unset, when the start lies outside the usable area but
// inside the map diamond, or when the zones of the two cells agree.
//
// Address index: 0x56D100

#include "../_layout/cell_class.h"
#include "../ui/input_controls/ui_display_chain.h"

// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern MapClass DAT_0087F7E8;

// The cell lies inside the map diamond (the rectangle at +0xEC rotated by 45 degrees).
static inline bool InsideDiamond(const CellStruct* c)
{
    int x = c->X;
    int y = c->Y;
    int sum = y + x;
    return sum > DAT_0087F7E8.MapRect.Width && x - y < DAT_0087F7E8.MapRect.Width
        && y - x < DAT_0087F7E8.MapRect.Width
        && sum <= DAT_0087F7E8.MapRect.Width + DAT_0087F7E8.MapRect.Height * 2;
}

// FUNCTION: GAMEMD 0x56D100
bool MapClass::FUN_0056D100(const CellStruct* from, const CellStruct* to, int zone, bool fromBridge, bool toBridge,
                            bool checkEdge)
{
    if (zone == -1)
        return true;
    bool fromUsable = DAT_0087F7E8.FUN_00578460(*from, true);
    bool fromInside = InsideDiamond(from);
    if (!fromUsable && fromInside)
        return true;
    bool toUsable = DAT_0087F7E8.FUN_00578460(*to, true);
    bool toInside = InsideDiamond(to);
    if (checkEdge && fromUsable && !toUsable && toInside)
        return true;
    int toZone = FUN_0056D230(*to, zone, toBridge);
    return FUN_0056D230(*from, zone, fromBridge) == toZone;
}
