// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   WWMouseClass cursor-position read, disassembled from the user's retail gamemd.exe v1.001.
//   Address index: 0x7B9DF0.

#include <windows.h>
#include "mouse_ww_mouse_class.h"

// FUNCTION: GAMEMD 0x7B9DF0
// Reads the OS cursor position into *x / *y, then converts it through vtable slot 17 (ConvertCoords).
void WWMouseClass::Method_7B9DF0(int* x, int* y)
{
    POINT p;
    GetCursorPos(&p);
    *x = p.x;
    *y = p.y;
    ConvertCoords(x, y);
}
