// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Flag bisection: a paired /GX probe of every entry in this TU produced the same scores as the
// line above. /GX is omitted because controls_static_button.cpp shows retail has no unwind code.
//
// ShapeButtonClass entries (layout and evidence: ui_gadget.h).
#include "controls_views.h"


// FUNCTION: GAMEMD 0x69DE00
void ShapeButtonClass::vf_34(ShapeHeader* shape, int width, int height)
{
    if (IsShapeLoaded && ShapeData) {
        delete ShapeData;
        ShapeData = 0;
        IsShapeLoaded = false;
        Width = 0;
        Height = 0;
    }
    ShapeData = shape;
    if (shape) {
        Width = shape->Width;
        Height = shape->Height;
    } else {
        Width = 0;
        Height = 0;
    }
    if (width)
        Width = width;
    if (height)
        Height = height;
}

// FUNCTION: GAMEMD 0x69DEB0
// CAPPED at 16.7% (17 of 102 instructions; multiset delta: retail has 2 `xor`, 1 `push`, 1 `pop` more).
// Retail pushes the zero arguments of the shape blitter through XOR'd registers (`xor ecx,ecx` /
// `xor eax,eax`, then `push ecx` x7 and `push eax`) after copying the clip rectangle field by field,
// uses EBP for X and Y, and builds the whole argument list late; ours pushes immediate zeros early in
// between the rectangle copy and the position stores. Stack size (0x20) and the frame/flag
// selection match. Variants tried: field-wise clip copy, the flag word in a local, the clip copy and the
// position in disjoint blocks (the layout that yields the 0x20 frame).
int ShapeButtonClass::Draw(int forced)
{
    if (ControlClass::Draw(forced) && ShapeData) {
        int frame;
        if (IsDisabled)
            frame = 2;
        else if (HasFrames)
            frame = IsToFlash ? (IsOn != 0) + 3 : (IsOn != 0);
        else
            frame = unknown_2C != 0;
        Surface* surface = UsesSidebarSurface ? DAT_00887300 : DAT_00887314;
        Rect clip;
        clip = surface->GetRect();
        {
            Point2D position(X + OffsetX, Y + OffsetY);
            FUN_004AED70(surface, Convert, ShapeData, frame, &position, &clip,
                              unknown_55 ? 0x800 : 0, 0, 0, 0, 0x3E8, 0, 0, 0, Point2D(0, 0));
        }
        unknown_54 = 1;
        return 1;
    }
    return 0;
}
