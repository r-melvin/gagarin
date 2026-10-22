// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x471F90.

#include "remove_last_matching_methods.h"

// FUNCTION: GAMEMD 0x471F90
//
// Walk the table from the last entry down to the first and, for every entry
// whose first word equals the key, free it and close the gap by shifting the
// later entries down one slot. Always reports success.
//
// (Revalidated against retail: the earlier single-probe, void-returning form
// missed the backward loop and the `MOV AL,1` result.)
bool Obj_00471F90::FUN_00471F90(void* key)
{
    for (int index = Count - 1; index >= 0; index--) {
        void* item = Items[index];

        if (*(void**)item == key) {
            if (item) {
                FUN_007C8B3D(item);
            }

            if (index < Count) {
                int last = Count - 1;

                Count = last;

                for (int j = index; j < Count; j++) {
                    Items[j] = Items[j + 1];
                }
            }
        }
    }

    return true;
}
