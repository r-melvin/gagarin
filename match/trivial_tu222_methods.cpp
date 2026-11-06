// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include <string.h>
#include <new.h>
#include "trivial_tu222_methods.h"
#include "vector_big_006c8870.h"

// FUNCTION: GAMEMD 0x6C6AF0
// Empty function.
void __cdecl FUN_006C6AF0()
{
}

// GLOBAL: GAMEMD 0xB0BD50 -- the pending-entry array (defined in global_block_release_methods.cpp).
extern VectorBig_006C8870 DAT_00B0BD50;

// FUNCTION: GAMEMD 0x6C6D00
// Removes the first entry (shifting the rest down) and halves the allocation once it is under a third full.
void __cdecl FUN_006C6D00()
{
    int index = 0;
    if (DAT_00B0BD50.Count != 0) {
        if (DAT_00B0BD50.Count <= 0) {
            index = DAT_00B0BD50.Count - 1;
        }
        memmove(&DAT_00B0BD50.Items[index], &DAT_00B0BD50.Items[index + 1],
                (DAT_00B0BD50.Count - (index + 1)) * sizeof(BigEntry_006C6B00));
        DAT_00B0BD50.Count--;
        if (DAT_00B0BD50.Count * 3 <= DAT_00B0BD50.Capacity) {
            int size = DAT_00B0BD50.Capacity / 2;
            if (size < 10) {
                size = 10;
            }
            if (size < DAT_00B0BD50.Capacity) {
                BigEntry_006C6B00* entries = (BigEntry_006C6B00*)operator new(size * sizeof(BigEntry_006C6B00));
                if (DAT_00B0BD50.Items) {
                    memcpy(entries, DAT_00B0BD50.Items, DAT_00B0BD50.Count * sizeof(BigEntry_006C6B00));
                }
                operator delete(DAT_00B0BD50.Items);
                DAT_00B0BD50.Items = entries;
                DAT_00B0BD50.Capacity = size;
            }
        }
    }
}
