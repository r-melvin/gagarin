// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4348F0.

#include "bit_font_lock_methods.h"

// FUNCTION: GAMEMD 0x4348F0
//
// Bind the font to a surface for drawing: lock the surface's pixels at the
// origin, note its stride in 16-bit words, and settle the clip rectangle. With
// no clip set (all four edges zero) the whole surface becomes the clip;
// otherwise the existing clip is intersected with the surface rectangle.
//
// Two phrasing facts carry the match. The origin is a by-value Point2D built
// member by member, which is what puts each zero in its own register for the
// two pushes; the rectangle's zero edges are assigned after the pitch call so
// they stay immediate stores placed before the width call. The clip copy is
// member-wise: a whole-struct assignment moves the same dwords but addresses
// them through the LEA'd pointer instead of `this`.
void BitFont::Lock(Surface* surface)
{
    LTRBStruct rect;
    Point2D origin;

    origin.X = 0;
    origin.Y = 0;
    pGraphBuffer = static_cast<short*>(surface->Lock(origin));
    PitchDiv2 = surface->GetPitch() >> 1;

    rect.Left = 0;
    rect.Top = 0;
    rect.Right = surface->GetWidth() - 1;
    rect.Bottom = surface->GetHeight() - 1;

    if ((Bounds.Right | Bounds.Bottom | Bounds.Top | Bounds.Left) == 0) {
        Bounds.Left = rect.Left;
        Bounds.Top = rect.Top;
        Bounds.Right = rect.Right;
        Bounds.Bottom = rect.Bottom;
    } else {
        Intersect(&Bounds, &Bounds, &rect);
    }
}
