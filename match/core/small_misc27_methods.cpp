// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x433CA0.

#include "small_misc27_methods.h"

// FUNCTION: GAMEMD 0x433CA0
// Copy four fields in, or clear them when there is no source. The clear runs
// back to front, which is what retail emits and is kept as written.
void Obj_00433CA0::FUN_00433CA0(const Quad_00433CA0* src)
{
    if (src != 0) {
        unknown_30 = src->a;
        unknown_34 = src->b;
        unknown_38 = src->c;
        unknown_3C = src->d;

        return;
    }

    unknown_3C = 0;
    unknown_38 = 0;
    unknown_34 = 0;
    unknown_30 = 0;
}
