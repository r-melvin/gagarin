// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4265B0.

#include "angle_from_points_methods.h"

// FUNCTION: GAMEMD 0x4265B0
Angle_004265B0* Angle_004265B0::FUN_004265B0(Point_004265B0* from,
                                             Point_004265B0* to)
{
    if (from->X == to->X && from->Y == to->Y) {
        Value = 0;
    }

    // The differences are taken *on the FPU*, not in integer registers: retail
    // is `FILD [ECX]; FISUB [EAX]`, which is what `(double)x - y` gives with the
    // right-hand side left as an int. Converting the whole difference -
    // `(double)(x - y)` - subtracts in EDX first and loses both instructions.
    double radians = FUN_004CAE30((double)from->Y - to->Y,
                                  (double)to->X - from->X);

    Angle_004265B0 result;

    result.Value = (short)((radians - 1.5707963267948966) * -10430.060040584269);

    *this = result;

    return this;
}

// FUNCTION: GAMEMD 0x41C2E0
//
// SCHEDULING DELTA (status partial, 88.6% - 39/44). The FPU sequence, both
// calls, the constants and the two-byte store are exact. One instruction is out
// of place: retail reads the height's high dword (`MOV EDX,[ESI+0x14]`) before
// storing the square root, and we read it after the two stack reloads - a
// three-instruction rotation that the scorer counts five times. Hoisting the
// height into a local ahead of the call is much worse (0%): it loads both
// halves early and re-orders the whole argument setup.
Angle16_0041C2E0 Vector_0041C2E0::FUN_0041C2E0()
{
    double distance = FUN_004CAC40(X * X + Z * Z);

    double radians = FUN_004CAE30(Height, distance);

    Angle16_0041C2E0 result;

    result.Value = (short)((radians - 1.5707963267948966) * -10430.060040584269);

    return result;
}
