// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Original translation unit wwmous.cpp. The name is the source-file string at 0x84e61c
//   in retail gamemd.exe v1.001, passed by the assert at 0x7b8657 inside this object's
//   code range (0x7b7831-0x7ba41f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Entry-point disassembly of retail gamemd.exe v1.001 at 0x7B89F0, 0x7B9D70, 0x7B9D90 and 0x7BA320..0x7BA38E,
//   all reached through the WWMouseClass vtable 0x7F7B2C (layout and slot evidence: mouse_ww_mouse_class.h).
//
//   Entry-point disassembly of retail gamemd.exe v1.001 at 0x7B8A00, 0x7B90C0, 0x7B92D0, 0x7B9750, 0x7B9930,
//   0x7B9A60 and 0x7B9C30, all reached through the WWMouseClass vtable 0x7F7B2C (layout, slot and global evidence:
//   mouse_ww_mouse_class.h). Strings: 'Capture_Mouse()\n' 0x84E690, 'Release_Mouse()\n' 0x84E6A4.

#include "../../core/trivial_tu293_methods.h"



#include "mouse_ww_mouse_lock.h"

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
            static_cast<RectangleStruct&>(rect) = unknown_4->FUN_0069E7E0(CursorFrame);
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

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x7B7D80
// Calls other functions.
void Obj_007B7D80::FUN_007B7D80()
{
    FUN_007CB9B8(unknown_00, 0, 0xA);
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x7B84D0
// Branching.
void FUN_007B84D0(int a1, int a2)
{
    if (DAT_00B7816C == 0)
    {
        if (DAT_00B78164 != 0)
        {
            FUN_007BA090(DAT_00B78164, a2);
        }
    }
}

// FUNCTION: GAMEMD 0x7B88D0
WWMouseClass::~WWMouseClass()
{
    LockMouse();
    if (DAT_00B78164 == this)
        DAT_00B78164 = 0;
    UnlockMouse();
    if (Under) {
        delete Under;
        Under = 0;
    }
    if (Cache1) {
        delete Cache1;
        Cache1 = 0;
    }
    if (Cache2) {
        delete Cache2;
        Cache2 = 0;
    }
}

// FUNCTION: GAMEMD 0x7B89F0
int WWMouseClass::GetHideCount()
{
    return unknown_C;
}

// FUNCTION: GAMEMD 0x7B8A00
void WWMouseClass::SetCursor(const Point2D* hotspot, Obj_0069E430* shape, int frame)
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

// FUNCTION: GAMEMD 0x7B9D70
// Slot 8 takes four stack arguments (RET 0x10), ignores them and calls slot 3 (vf_3).
void WWMouseClass::vf_8(int, int, int, int)
{
    vf_3();
}

// FUNCTION: GAMEMD 0x7B9D80
// Tail-calls a virtual method of its receiver. Vtable slot 9 of WWMouseClass (RTTI).
void WWMouseClass::vf_9()
{
    vf_4();
}

// FUNCTION: GAMEMD 0x7B9D90
void WWMouseClass::ConvertCoords(int* x, int* y)
{
    *x -= Bounds.X;
    *y -= Bounds.Y;
    if (*x < 0)
        *x = 0;
    if (*y < 0 && !MouseConvertFlag)
        *y = 0;
    if (*x >= Bounds.Width)
        *x = Bounds.Width - 1;
    if (*y >= Bounds.Height)
        *y = Bounds.Height - 1;
}

// SYNTHETIC: GAMEMD 0x7BA300
// Mouse scalar deleting destructor.

// FUNCTION: GAMEMD 0x7BA320
bool WWMouseClass::IsMouseHidden()
{
    return unknown_C < 0;
}

// FUNCTION: GAMEMD 0x7BA330
bool WWMouseClass::IsCaptured()
{
    return Captured;
}

// FUNCTION: GAMEMD 0x7BA340
int WWMouseClass::vf_11()
{
    return ReportedPosition.X;
}

// FUNCTION: GAMEMD 0x7BA350
int WWMouseClass::vf_12()
{
    return ReportedPosition.Y;
}

// FUNCTION: GAMEMD 0x7BA360
// Returns its argument (EAX still holds `out` at the RET); the copy goes through a local so both coordinates are loaded
// before either is stored.
Point2D* WWMouseClass::vf_13(Point2D* out)
{
    Point2D position = ReportedPosition;
    *out = position;
    return out;
}

// FUNCTION: GAMEMD 0x7BA380
void WWMouseClass::vf_14(int x, int y)
{
    ReportedPosition.X = x;
    ReportedPosition.Y = y;
}

// SYNTHETIC: GAMEMD 0x7BA3A0
// WWMouseClass scalar deleting destructor.

