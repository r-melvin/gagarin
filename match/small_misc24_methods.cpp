// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc24_methods.h"

// FUNCTION: GAMEMD 0x422B80
void FUN_00422B80(void* key)
{
    if (key == 0) {
        return;
    }

    for (int i = 0; i < DAT_00A8E9B8; i++) {
        Rec_00422B80* rec = DAT_00A8E9AC[i];

        if (rec->atCC == key) {
            rec->at195 = 0;
        }
    }
}
