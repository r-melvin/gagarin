// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The former hand-written scalar deleting destructors were removed: they are
// compiler output, emitted from the classes' virtual destructors elsewhere.

#include "deleting_dtor_methods.h"

// FUNCTION: GAMEMD 0x408E00
void Obj_00408E00::FUN_00408E00()
{
    if (unknown_10) {
        FUN_007C8B3D(unknown_10);
    }

    FUN_007C8B3D(this);
}
