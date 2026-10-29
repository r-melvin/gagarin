// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.

#include "../_layout/ebolt_class.h"
#include "../_layout/unit_class.h"
#include "../core/vector_class_operations.h"

void __cdecl operator delete(void*);

// FUNCTION: GAMEMD 0x4C29E0
//
// Destroy every live bolt, unhooking each from the object it is linked to, then
// free the list's storage if it owns it and reset the list.
void FUN_004C29E0()
{
    for (int i = 0; i < DAT_008A0E88.Count; i++) {
        EBolt* bolt = DAT_008A0E88.Items[i];
        if (bolt != 0) {
            if (bolt->Owner != 0) {
                bolt->Owner->ElectricBolt = 0;
                bolt->Owner = 0;
            }
            delete bolt;
        }
    }
    DAT_008A0E88.Clear();
}
