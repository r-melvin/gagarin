// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x407170.

#include "small_misc34_methods.h"

// 0x4093B0 takes no arguments (its entry reads only a global hook and
// returns EDX:EAX); declaring a phantom ECX argument pinned one comparand
// to ECX and cost the two register choices of the compare.
//
// FUNCTION: GAMEMD 0x407170
// Clear the armed bit, refresh the 64-bit stamp only when the two counters have
// converged, and store the new rate shifted into the high half. The rate store
// happens on both paths - the JNZ lands on it, not on the return.
void FUN_00407170c(Obj_00407170* obj, int rate)
{
    obj->Flags &= ~1;

    if (obj->unknown_08 == obj->unknown_04) {
        obj->unknown_18 = FUN_004093B0();
    }

    obj->unknown_08 = rate << 16;
}
