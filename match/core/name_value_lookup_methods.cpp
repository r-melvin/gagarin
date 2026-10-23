// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x40DCE0 and 0x45DD50.

#include "name_value_lookup_methods.h"

// FUNCTION: GAMEMD 0x40DCE0
//
// Linear scan; an unknown name is zero rather than an error.
//
// Retail carries both a walking pointer and a live index - the bound test is
// `CMP ESI,0x817130` on the pointer while the hit reads `[EDI*8 + 0x816EE4]`
// through the index. That is VC6's own strength reduction of a plain indexed
// `for`, per the induction-loop rule: writing the pointer walk by hand costs an
// LEA and loses the indexed load.
int FUN_0040DCE0(const char* name)
{
    for (int i = 0; i < 74; i++) {
        if (FUN_007C8D20(DAT_00816EE0[i].Name, name) == 0) {
            return DAT_00816EE0[i].Value;
        }
    }

    return 0;
}

