// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x734D30.

#include "string_table_unload_methods.h"

// FUNCTION: GAMEMD 0x734D30
//
// Release everything the string table owns: the 0xB1CF8C node list (unlinked
// through the global head as it goes), the Values and ExtraValues string
// arrays (each element, then the array), the label block, and the
// LastLoadedString node list (walked through a local cursor). The heads and
// the loaded flag are cleared behind each release.
void StringTable::Unload()
{
    while (DAT_00B1CF8C != 0) {
        StringNode_00734D30* node = DAT_00B1CF8C;
        DAT_00B1CF8C = node->Next;
        FUN_007C8B3D(node);
    }
    DAT_00B1CF8C = 0;

    if (DAT_00B1CF78 != 0) {
        int i;
        for (i = 0; i < DAT_00B1CF70; i++) {
            if (DAT_00B1CF78[i] != 0) {
                FUN_007C8B3D(DAT_00B1CF78[i]);
            }
        }
        FUN_007C8B3D(DAT_00B1CF78);
        DAT_00B1CF78 = 0;
    }

    if (DAT_00B1CF7C != 0) {
        int i;
        for (i = 0; i < DAT_00B1CF70; i++) {
            if (DAT_00B1CF7C[i] != 0) {
                FUN_007C8B3D(DAT_00B1CF7C[i]);
            }
        }
        FUN_007C8B3D(DAT_00B1CF7C);
        DAT_00B1CF7C = 0;
    }

    if (DAT_00B1CF74 != 0) {
        FUN_007C8B3D(DAT_00B1CF74);
        DAT_00B1CF74 = 0;
    }

    StringNode_00734D30* cursor = DAT_00B1CF88;
    while (cursor != 0) {
        StringNode_00734D30* next = cursor->Next;
        FUN_007C8B3D(cursor);
        cursor = next;
    }
    DAT_00B1CF88 = 0;
    DAT_00B1CF80 = 0;
}
