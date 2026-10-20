// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x63DB20.

#include "rect_contains_point_methods.h"

// FUNCTION: GAMEMD 0x63DB20
//
// Point-in-rectangle test: the X range is checked first (`pt->X >= this->X`
// then `pt->X < this->X + this->Width`), and only when it passes is the Y
// range checked at all -- the nested `if` (not a single `&&` chain across
// both axes) is what keeps the Y-range load and compare out of the X-only
// failure path, matching retail's two independent short-circuit exits to the
// same `xor eax,eax` tail. The point's own field has to be the *left*
// operand of the comparison (`pt->X >= this->X`, not `this->X <= pt->X`) --
// otherwise cl loads the rectangle field into EAX and the point field into
// EDX (the mirror of retail) and flips `JL` to `JG`, cascading through every
// register role in the rest of the axis. The return value is a plain `int`
// (`MOV EAX,1` / `XOR EAX,EAX`), not a `bool` (`MOV AL,1`).
int Rect_0063DB20::Contains(const Point_0063DB20* pt) const
{
    if (pt->X >= this->X && pt->X < this->X + this->Width) {
        if (pt->Y >= this->Y && pt->Y < this->Y + this->Height) {
            return 1;
        }
    }
    return 0;
}
