// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x50C170.

#include <string.h>
#include "house_class_find_index_methods.h"

#pragma intrinsic(strcpy, strcmp)

// FUNCTION: GAMEMD 0x50C170
//
// Walk the global house list comparing each house's name against the caller's
// string; return the index of the first hit or -1. The name is first copied
// into a 20-byte frame buffer (retail's inlined strcpy: REPNE SCASB then REP
// MOVSD/MOVSB), and the comparison is the inlined strcmp byte loop. The count
// is re-read from the global at the end of every iteration.
int __fastcall House_0050C170::FindIndexByName(const char* name)
{
    char buf[20];

    for (int i = 0; i < DAT_00A80238; i++) {
        strcpy(buf, DAT_00A8022C[i]->PlainName);
        if (strcmp(buf, name) == 0) {
            return i;
        }
    }

    return -1;
}
