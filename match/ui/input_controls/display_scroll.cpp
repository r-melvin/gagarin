// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// ScrollClass entries (layout and evidence: display_scroll.h).

#include "display_scroll.h"

// FUNCTION: GAMEMD 0x692290
// Expansion row (neighbour, not an assigned address): VC6 emits the vtables and the scalar deleting destructor 0x6938F0
// only in a translation unit that defines a constructor, so the constructor is taken here.
ScrollClass::ScrollClass()
    : unknown_5548(0), unknown_554C(false), unknown_5550(0), unknown_5554(0), unknown_5558(false), unknown_5559(true), unknown_555A(false)
{
}

// SYNTHETIC: GAMEMD 0x6938F0
// ScrollClass scalar deleting destructor, emitted from the implicit destructor (ui_display_chain.h).

// FUNCTION: GAMEMD 0x6922E0
void ScrollClass::vf_10(int* key, Point2D* where)
{
    FUN_00692F30();
    TabClass::vf_10(key, where);
}

// FUNCTION: GAMEMD 0x693060
bool ScrollClass::vf_26()
{
    if (!unknown_555A && !DisplayFlag_00A8ED9C)
    {
        if (!DisplayTactical_00887324 || DisplayTactical_00887324->unknown_0D8 == 0.0f)
            return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x693840
void ScrollClass::vf_49(int arg)
{
    if (unknown_5558)
    {
        vf_18(0, DisplayFlag_00884D44);
        unknown_5558 = false;
    }
    else
    {
        DisplayClass::vf_49(arg);
    }
}

// FUNCTION: GAMEMD 0x693880
void ScrollClass::vf_44(const Point2D* where)
{
    if (!DisplayFlag_00A8ED9C)
    {
        DisplayClass::vf_44(where);
        unknown_5550 = where->X;
        unknown_5554 = where->Y;
        unknown_5558 = false;
        WWMouseClassInstance->vf_4();
    }
}

// FUNCTION: GAMEMD 0x6938C0
void ScrollClass::vf_35()
{
    DisplayClass::vf_35();
    unknown_555A = false;
    if (GetCapture() == DisplayCaptureWindow_00B73550)
        ReleaseCapture();
}
