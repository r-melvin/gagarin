// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Entry-point disassembly of retail gamemd.exe v1.001 at 0x7B89F0, 0x7B9D70, 0x7B9D90 and 0x7BA320..0x7BA38E,
//   all reached through the WWMouseClass vtable 0x7F7B2C (layout and slot evidence: mouse_ww_mouse_class.h).

#include "mouse_ww_mouse_lock.h"

// FUNCTION: GAMEMD 0x7B89F0
int WWMouseClass::GetHideCount()
{
    return unknown_C;
}

// FUNCTION: GAMEMD 0x7B9D70
// Slot 8 takes four stack arguments (RET 0x10), ignores them and calls slot 3 (vf_3).
void WWMouseClass::vf_8(int, int, int, int)
{
    vf_3();
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
