// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4587D0. (0x43E900 moved to
//   match/economy/house_building/building_a_methods_1.cpp.)

#include "small_misc36_methods.h"

// FUNCTION: GAMEMD 0x4587D0
bool Obj_004587D0::FUN_004587D0(Arg_004587D0* other)
{
    int derived = other->vt_08C(Owner);

    // The pointer cast models this call slot's existing ABI view only.
    void* context = (void*)DAT_0089C818.raw_dword;
    bool accepted = vt_100(derived, context) != 0;

    return accepted;
}
