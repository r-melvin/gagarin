// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 instruction reads at +0xA8/+0x14 and virtual dispatches through +0x50/+0xB0 subobject slots).
// REA 4B54E0: ev_1cdb20b4d5406ad7c4d77bbd96adb0909c283189455331b33f219932431e2c87.
#include "gadget_dispatch_004b55a0.h"

// FUNCTION: GAMEMD 0x4B54E0
void GadgetDispatchView_004B55A0::FUN_004B54E0(int x, int y)
{
    GadgetClass::SetPosition(x, y);
    PartB0.SetPosition(x, Part50.unknown_58->unknown_04 + y);
    Part50.SetPosition(Width + x, y);
}

// FUNCTION: GAMEMD 0x4B55A0
int GadgetDispatchView_004B55A0::FUN_004B55A0()
{
    return unknown_34;
}

// FUNCTION: GAMEMD 0x4B55B0
int GadgetDispatchView_004B55A0::FUN_004B55B0()
{
    return PartB0.Slot37();
}

// FUNCTION: GAMEMD 0x4B55D0
void GadgetDispatchView_004B55A0::FUN_004B55D0(int value)
{
    PartB0.GetItem((unsigned)value);
}
