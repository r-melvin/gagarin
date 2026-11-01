// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x439110.

#include "small_misc35_methods.h"

// FUNCTION: GAMEMD 0x439110
// Reset both halves the same way: read the saved pointer first, dispatch the
// no-argument slot, then hand the saved pointer back through the two-argument
// one. The 0x2D written to +0x30 happens once, before either half.
void Obj_00439110::FUN_00439110()
{
    void* saved = Saved;

    unknown_30 = 0x2D;

    vt_00C();
    vt_008(saved, 0);

    Node_00439110* sub = &Sub;
    void* subSaved = sub->Saved;

    sub->vt_00C();
    sub->vt_008(subSaved, 0);
}
