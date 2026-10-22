// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6ABC60.

#include "sidebar_class_tab_methods.h"

// FUNCTION: GAMEMD 0x6ABC60  SidebarClass::FUN_006ABC60 (__fastcall, static)
// Which sidebar tab a buildable belongs in. Written as an if-chain, not a
// switch: VC6 turns a switch over these values into a jump table (2% match),
// while retail is a straight compare chain in source order with the fallthrough
// -1 emitted before the return blocks.
int SidebarClass::FUN_006ABC60(int abs, int idxType, int unused)
{
    if (abs == ABS_INFANTRYTYPE || abs == ABS_UNITTYPE)
        return 2;

    if (abs == ABS_UNIT || abs == ABS_INFANTRY || abs == ABS_AIRCRAFT || abs == ABS_BUILDING)
        return 3;

    if (abs == ABS_BUILDINGTYPE || abs == ABS_AIRCRAFTTYPE)
        return GetCurrentSidebarContext() == 5;

    if (abs == ABS_BUILDINGTYPE2 || abs == ABS_ABSTRACTTYPE || abs == ABS_SUPERWEAPON)
        return 1;

    return -1;
}
