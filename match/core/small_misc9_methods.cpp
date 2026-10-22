// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc9_methods.h"

// FUNCTION: GAMEMD 0x4071A0
// The stored ratio is a 16.16 fixed-point reciprocal: the value is shifted up
// sixteen bits before an *unsigned* divide, so a divisor of zero faults rather
// than trapping to a signed-overflow path.
void Obj_00407100b::FUN_004071A0(unsigned int v, unsigned int divisor, int extra)
{
    unknown_10 = divisor;
    unknown_0C = (v << 16) / divisor;
    unknown_14 = extra;
}

// FUNCTION: GAMEMD 0x437F10
Pair2i Pair2i::FUN_00437F10(const Pair2i* other) const
{
    Pair2i result;

    result.x = other->x + x;
    result.y = other->y + y;

    return result;
}

// FUNCTION: GAMEMD 0x41A590
void AircraftClass_0041A590::FUN_0041A590(int, int, int)
{
    if (FUN_005B3A00(this)->at9) {
        vt_484(0, 1);
    }
}

// FUNCTION: GAMEMD 0x42EB20
// Look the key up and turn the index into a record pointer; a miss yields null
// rather than the first record.
char* Obj_0042EB20::FUN_0042EB20(int key)
{
    int index = FUN_0042EB50(key);

    if (index != -1) {
        return Items + index * 16;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x45DD20
void* FUN_0045DD20(int key)
{
    for (int i = 0; i < 6; i++) {
        if (DAT_00819288[i].Key == key) {
            return DAT_00819288[i].Value;
        }
    }

    return DAT_00819288[0].Value;
}
