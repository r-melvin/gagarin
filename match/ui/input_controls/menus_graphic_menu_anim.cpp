// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// GraphicMenuAnimItem entries (layout and evidence: menus_graphic_menu.h).
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.

#include "menus_graphic_menu.h"

// FUNCTION: GAMEMD 0x4F3090
// Hit test: true when the item is visible and the point lies inside its rectangle.
bool GraphicMenuAnimItem::Slot2(const Point2D* point)
{
    return Visible
        && point->X >= Rect.X && point->X < Rect.X + Rect.Width
        && point->Y >= Rect.Y && point->Y < Rect.Y + Rect.Height;
}

// FUNCTION: GAMEMD 0x4F3070
// Releases the owned animation, then runs the base destructor. (The scalar deleting destructor 0x4F30E0 is
// not reproduced: cl emits ??_G only beside a constructor, and the factory 0x4F2C70 expands it inline.)
GraphicMenuAnimItem::~GraphicMenuAnimItem()
{
    delete Anim;
}

// SYNTHETIC: GAMEMD 0x4F30E0 -- GraphicMenuAnimItem::`scalar deleting destructor' (compiler-generated ??_G beside the out-of-line destructor)
