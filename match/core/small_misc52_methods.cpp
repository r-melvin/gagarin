// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x417F80 and 0x447AC0.

#include "small_misc52_methods.h"

// FUNCTION: GAMEMD 0x417F80
int AircraftClass_00417F80::FUN_00417F80(int first, int second, int third)
{
    if (!FUN_0050B6F0(Owner)) {
        return 0;
    }

    int answer = FUN_004DDDE0(first, second, third);

    if (answer == 5) {
        if (vt_3F8(0)->Occupant == 0) {
            answer = 0;
        }
    }

    return answer;
}

// FUNCTION: GAMEMD 0x447AC0
//
// The object's centre in world units: both cell dimensions are scaled by 128
// and pulled back half a cell, then added to the coordinate triple at +0x9C.
//
// MATCHED 100% (27/27). Two levers together, neither sufficient alone:
//   * copy the whole +0x9C member struct into a local first
//     (`Point_00447AC0 c = Cell;`). That is what makes cl advance the base
//     register with `ADD EDI,0x9C` instead of keeping
//     `[edi+0x9C/0xA0/0xA4]` displacements - the fold previously written off
//     as unreachable from source. It alone took the out-parameter form from
//     22.2% to 55.6%.
//   * return the result BY VALUE (`Point_00447AC0` with a user-declared empty
//     ctor) rather than through an out parameter. The hidden-return pointer is
//     then read into EAX and copied to its own base register
//     (`MOV EAX,[ESP+0xC]; MOV ESI,EAX`), and the three sums stay in ECX/EDX/EDI
//     instead of collapsing into an LEA.
// Operand order in the sums is irrelevant here (cl folds the commute).
Point_00447AC0 BuildingClass_00447AC0::FUN_00447AC0()
{
    int height = Settings->FUN_0045ECA0(0) * 128 - 128;
    int width  = Settings->FUN_0045EC90() * 128 - 128;

    Point_00447AC0 c = Cell;

    Point_00447AC0 temp;
    temp.X = width + c.X;
    temp.Y = height + c.Y;
    temp.Z = c.Z;
    return temp;
}
