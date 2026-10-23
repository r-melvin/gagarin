// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x422B20 and 0x428DE0.

#include "small_misc49_methods.h"

// FUNCTION: GAMEMD 0x422B20
int FUN_00422B20(const char* name)
{
    if (name != 0 && FUN_007C8D20(name, STR_00817474) != 0) {
        for (int i = 0; i < DAT_008B4160; i++) {
            if (FUN_007C8D20(DAT_008B4154[i] + 0x24, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x428DE0
void FUN_00428DE0(Obj_00428DE0* self)
{
    if (self->Enabled && self->Image && self->Loaded) {
        FUN_004068E0(STR_00818688, self->Name);

        FUN_007C8B3D(self->Image);

        self->Image      = 0;
        self->ImageValid = 0;
    }
}

