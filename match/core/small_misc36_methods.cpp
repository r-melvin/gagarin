// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4115F0, 0x4587D0 and
//   0x43E900.

#include "small_misc36_methods.h"

// FUNCTION: GAMEMD 0x4115F0
int BSurface_004115F0::FUN_004115F0(int scaleA, int scaleB)
{
    ++Counter;

    int base = Base;

    // The two products stay inside the return expression. Naming them as
    // locals is what breaks this: VC6 then loads Base early into EBX, leaves
    // EDI free for the first product, and re-associates the sum as
    // (first + second) + base -- 63.6% across five spellings of that shape.
    // With only `base` held, EDI carries the counter and is reused for Base
    // after the store, EBX takes the first product, and the tail comes out as
    // retail's `ADD EDI,EBX; ADD EAX,EDI`.
    return base + vt_070() * scaleA + vt_074() * scaleB;
}

// FUNCTION: GAMEMD 0x4587D0
bool Obj_004587D0::FUN_004587D0(Arg_004587D0* other)
{
    int derived = other->vt_08C(Owner);

    void* context = DAT_0089C818;
    bool accepted = vt_100(derived, context) != 0;

    return accepted;
}

// FUNCTION: GAMEMD 0x43E900
int BuildingClass_0043E900::FUN_0043E900()
{
    int value = -FUN_006D20E0(vt_1D0());

    BuildingTypeClass_0043E900* settings = Settings;

    if (settings->Enabled) {
        return settings->Adjustment + value;
    }

    return value;
}
