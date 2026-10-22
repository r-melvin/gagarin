// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Entry-point disassembly of retail gamemd.exe v1.001 at 0x7B8A00, 0x7B90C0, 0x7B92D0, 0x7B9750, 0x7B9930,
//   0x7B9A60 and 0x7B9C30, all reached through the WWMouseClass vtable 0x7F7B2C (layout, slot and global evidence:
//   mouse_ww_mouse_class.h). Strings: 'Capture_Mouse()\n' 0x84E690, 'Release_Mouse()\n' 0x84E6A4.

#include "mouse_ww_mouse_lock.h"

// The save-under restore that vf_3, vf_5 and SetCursor share: copy the saved background back onto the
// screen at the cursor rectangle.
inline void WWMouseClass::RestoreUnder()
{
    LockMouse();
    if (UnderRect.IsPositive() && Screen && Under) {
        RectangleStruct dest = UnderRect;
        dest.X += Bounds.X;
        dest.Y += Bounds.Y;
        RectangleStruct src = { 0, 0, dest.Width, dest.Height };
        Screen->Blt(dest, Under, src, 0, 1);
    }
    UnlockMouse();
}

// The draw step that vf_4 and CaptureMouse share: save the background under the cursor rectangle into
// Under and refresh the screen.
inline void WWMouseClass::DrawCursorBlock()
{
    LockMouse();
    if (Method_7B8C60() && Screen) {
        CursorRect rect(0, 0, 0, 0);
        if (unknown_4) {
            // Retail calls the out-of-line lock here (0x7B9813) instead of expanding it inline.
            LockMouseCall();
            rect = unknown_4->GetFrameRect(CursorFrame);
            rect.X += Position.X - unknown_3C.X;
            rect.Y += Position.Y - unknown_3C.Y;
            UnlockMouse();
        }
        UnderRect = rect;
        RectangleStruct src = rect;
        src.X += Bounds.X;
        src.Y += Bounds.Y;
        Under->Blt(CursorRect(0, 0, src.Width, src.Height), Screen, src, 0, 1);
    }
    Method_7B93F0(Screen, 0, 0);
    UnlockMouse();
}

// FUNCTION: GAMEMD 0x7B8A00
void WWMouseClass::SetCursor(const Point2D* hotspot, MouseShapeView* shape, int frame)
{
    if (shape) {
        if (IsCaptured()) {
            LockMouse();
            if (!IsMouseHidden())
                RestoreUnder();
            unknown_4 = shape;
            CursorFrame = frame;
            unknown_3C = *hotspot;
            if (!IsMouseHidden()) {
                LockMouse();
                if (Method_7B8C60() && Screen) {
                    UnderRect = Method_7B8E80();
                    RectangleStruct src = UnderRect;
                    src.X += Bounds.X;
                    src.Y += Bounds.Y;
                    {
                        RectangleStruct dest = { 0, 0, src.Width, src.Height };
                        Under->Blt(dest, Screen, src, 0, 1);
                    }
                }
                Method_7B93F0(Screen, 0, 0);
                UnlockMouse();
            }
            UnlockMouse();
        } else {
            unknown_4 = shape;
            CursorFrame = frame;
            unknown_3C = *hotspot;
        }
    }
}

// FUNCTION: GAMEMD 0x7B90C0
void WWMouseClass::DrawMouseOnto(MouseSurfaceView* surface, bool useCache2)
{
    if (IsMouseHidden() || !IsCaptured() || !surface || surface == Screen)
        return;
    int offset;
    MouseSurfaceView* cache;
    CursorRect* rect;
    if (useCache2) {
        offset = MouseDrawFlag ? -MouseViewBoundWidth : 0;
        cache = Cache2;
        rect = &Cache2Rect;
    } else {
        offset = MouseDrawFlag ? 0
                               : ((-MouseSidebarSurface->GetWidth() > surface->GetWidth() - MouseViewOffset)
                                      ? -MouseSidebarSurface->GetWidth()
                                      : surface->GetWidth() - MouseViewOffset);
        cache = Cache1;
        rect = &Cache1Rect;
    }
    if (!cache || !Under) {
        rect->Width = 0;
        return;
    }
    LockMouse();
    *rect = UnderRect;
    rect->X += offset;
    {
        RectangleStruct dest = { 0, 0, rect->Width, rect->Height };
        cache->Blt(dest, surface, *rect, 0, 1);
    }
    if (useCache2 && rect->X < 0 && -rect->X < Under->GetWidth()) {
        RectangleStruct left = { 0, rect->Y, rect->Width, rect->Height };
        RectangleStruct right = { -rect->X, 0, rect->Width, rect->Height };
        Under->Blt(right, surface, left, 0, 1);
    } else {
        RectangleStruct all = { 0, 0, rect->Width, rect->Height };
        Under->Blt(all, surface, *rect, 0, 1);
    }
    Method_7B93F0(surface, offset, 0);
    UnlockMouse();
}

// FUNCTION: GAMEMD 0x7B92D0
void WWMouseClass::DrawCachedOnto(MouseSurfaceView* surface, bool useCache2)
{
    if (IsMouseHidden() || !IsCaptured() || !surface || surface == Screen)
        return;
    MouseSurfaceView* cache = Cache1;
    if (!cache || !Cache2)
        return;
    RectangleStruct rect;
    if (useCache2) {
        cache = Cache2;
        rect = Cache2Rect;
    } else {
        rect = Cache1Rect;
    }
    if (!cache)
        return;
    LockMouse();
    RectangleStruct zero = { 0, 0, rect.Width, rect.Height };
    surface->Blt(rect, cache, zero, 0, 1);
    UnlockMouse();
}

// FUNCTION: GAMEMD 0x7B9750
void WWMouseClass::vf_4()
{
    if (unknown_C == 0)
        return;
    LockMouse();
    if (++unknown_C == 0) {
        if (IsCaptured()) {
            DrawCursorBlock();
        } else {
            while (ShowCursor(TRUE) < 0)
                ;
        }
    }
    if (unknown_C > 0)
        unknown_C = 0;
    UnlockMouse();
}

// FUNCTION: GAMEMD 0x7B9930
void WWMouseClass::vf_3()
{
    LockMouse();
    if (unknown_C == 0) {
        if (IsCaptured()) {
            RestoreUnder();
        } else {
            while (ShowCursor(FALSE) >= 0)
                ;
        }
    }
    unknown_C--;
    UnlockMouse();
}

// FUNCTION: GAMEMD 0x7B9A60
// Retail tests the receiver for null before anything else (`TEST ESI,ESI; JE`), here and in vf_5.
void WWMouseClass::CaptureMouse()
{
    if (!this || IsCaptured())
        return;
    FUN_004068E0("Capture_Mouse()\n");
    LockMouse();
    Captured = true;
    if (!IsMouseHidden())
        DrawCursorBlock();
    ShowCursor(FALSE);
    UnlockMouse();
}

// FUNCTION: GAMEMD 0x7B9C30
void WWMouseClass::vf_5()
{
    if (!this || !IsCaptured())
        return;
    FUN_004068E0("Release_Mouse()\n");
    LockMouse();
    Captured = false;
    if (!IsMouseHidden()) {
        RestoreUnder();
        while (ShowCursor(TRUE) < 0)
            ;
    }
    UnlockMouse();
}
