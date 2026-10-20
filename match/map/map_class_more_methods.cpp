// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Signatures
//   cross-checked against YRpp MapClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4F42D0  MapClass::FUN_004F42D0      (__thiscall)
//   FUNCTION: GAMEMD 0x4F42F0  MapClass::RedrawSidebar     (__thiscall)
//   FUNCTION: GAMEMD 0x55BAA0  MapClass::AddObject         (__thiscall)
//   FUNCTION: GAMEMD 0x568300  MapClass::CoordinatesLegal  (__thiscall)

#include "map_class_more_methods.h"

// Globals reconfirmed numerically from the disasm.
extern SidebarRedrawTarget* SidebarRedrawPtr;  // @ 0x00887324
extern GScreenClass         GScreenInstance;   // @ 0x0087F7E8

// FUNCTION: GAMEMD 0x4F42D0  (__thiscall)
// Unconditionally force the bitfield to the "full redraw" state (2), unlike
// RedrawSidebar below which only sets it when not already 2.
void MapClass::FUN_004F42D0()
{
    this->Bitfield = 2;
}

// FUNCTION: GAMEMD 0x4F42F0  (__thiscall)
// Flag the sidebar for redraw, latch the display command, and mark the shared
// screen object for repaint.
void MapClass::RedrawSidebar(int mode)
{
    if (SidebarRedrawPtr)
    {
        SidebarRedrawPtr->NeedsRedraw = 1;
    }
    if (mode != 0)
    {
        if (this->Bitfield != 2)
        {
            this->Bitfield = mode;
        }
        GScreenInstance.MarkToRedraw();
    }
}

// FUNCTION: GAMEMD 0x55BAA0  (__thiscall)
// If the object is already in logic, succeed immediately; otherwise submit it
// and, on success, latch its in-logic flag.
bool MapClass::AddObject(ObjectClass* pObject, bool sorted)
{
    if (pObject->IsInLogic)
    {
        return true;
    }
    if (this->SubmitObject(pObject, sorted))
    {
        pObject->IsInLogic = 1;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x568300  (__thiscall)
// Diamond-bounds test in iso cell coordinates against MapRect.Width / Height.
bool MapClass::CoordinatesLegal(const CellStruct& cell) const
{
    int x = cell.X;
    int y = cell.Y;
    int w = this->MapRectWidth;
    bool legal = (x + y) > w
        && (x - y) < w
        && (y - x) < w
        && (x + y) <= w + 2 * this->MapRectHeight;
    return legal;
}
