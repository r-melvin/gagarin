// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x417F80.

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
