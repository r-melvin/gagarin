// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x410B90.

#include "ini_read_names_methods.h"

// FUNCTION: GAMEMD 0x410B90
bool Obj_00410B90::FUN_00410B90(CCINI_00410B90* ini)
{
    ini->FUN_005257C0(Section, 0);
    ini->FUN_00528660(Section, STR_00817854, &Name);

    if (UIName) {
        ini->FUN_00528660(Section, STR_0081784C, &UIName);
    }

    return true;
}
