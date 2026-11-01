// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// FindOrAllocate, ordered ascending by retail address, written out longhand per
// the family rule.
//
// The whole body sits inside one positive guard so that the single `return 0`
// lands in the trailing block, where retail has it at the very end. Written as
// three early `return 0` statements it scores 15.8% - every rejection gets its
// own inline epilogue and everything after shifts.

#include "find_or_allocate_methods.h"

// FUNCTION: GAMEMD 0x41CEF0
char* FUN_0041CEF0(const char* name)
{
    if (FUN_007C8D20(STR_00817474, name) != 0
        && FUN_007C8D20(STR_00817694, name) != 0) {

        for (int i = 0; i < DAT_00A8B228; i++) {
            if (FUN_007C8D20(DAT_00A8B21C[i] + 0x24, name) == 0) {
                return DAT_00A8B21C[i];
            }
        }

        void* item = FUN_007C8E17(0xE10);

        if (item != 0) {
            return ((Item*)item)->FUN_0041C8B0(name);
        }
    }

    return 0;
}

