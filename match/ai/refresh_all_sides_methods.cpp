// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x452D40.

#include "refresh_all_sides_methods.h"

// FUNCTION: GAMEMD 0x452D40
//
// Refresh all four sides of every eligible object, then mark it done.
//
// Exact under the project default /Gr. With the function itself compiled
// as fastcall, cl loads ECX ahead of the immediate push in the call run as
// retail does; the cdecl build of this same body had five load/push
// transpositions (82.2%) that no source spelling moved.
//
// The global suppressor at 0xA8E7AC is tested inside the loop rather than once
// before it -- retail reloads it per object -- so a value that changes mid-pass
// would take effect immediately. That is why it is not hoisted.
void FUN_00452D40()
{
    int i = 0;

    while (i < DAT_00A8EB50) {
        Obj_00452D40* obj = DAT_00A8EB44[i];

        if (obj != 0 && obj->Owner->At_16BE != 0 && DAT_00A8E7AC == 0
            && obj->At_90 != 0 && obj->At_81 == 0) {
            obj->FUN_00452DC0(0);
            obj->FUN_00452DC0(2);
            obj->FUN_00452DC0(4);
            obj->FUN_00452DC0(6);
            obj->FUN_004533A0(1);
        }

        i++;
    }
}
